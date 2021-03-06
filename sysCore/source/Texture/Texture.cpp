#include <System/System.h>
#include <Texture/TexImg.h>
#include <Texture/Texture.h>
#include <sysCore.h>

void TEXTUREPRINT(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char dest[1024];

    if (sysCon)
    {
        if ("Texture")
            sysCon->print("%s: ", "Texture");
        vsprintf(dest, fmt, args);
        if (strlen(dest))
        {
            sysCon->write(dest, strlen(dest));
        }
    }
}

void TEXTUREHALT(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char dest[1024];
    vsprintf(dest, fmt, args);
    System::halt("c:\\development\\dolphinpiki\\syscore\\texture.cpp", 14, dest);
    // file, line, error
}

Texture::Texture() : GfxObject()
{
    this->dword2C = 0;
    this->m_textures = -1;
    this->dword24 = 0;
    this->dword28 = 0;
}

void Texture::attach()
{
    if (this->m_textures == -1)
    {
        glGenTextures(1, &this->m_textures);
        glBindTexture(GL_TEXTURE_2D, this->m_textures);
        if (this->word6 & 1)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        else
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        if (this->word6 & 0x100)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        else
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        unsigned int unk = 0;
        for (int i = 0; i < 12; i++)
        {
            if (this->m_width == 1 << i)
                unk |= 1;
            if (this->m_height == 1 << i)
                unk |= 2;
        }

        // TODO FIX
        if (unk != 3 || (!gsys->m_textureByteUnk || this->word6 & 4))
        {

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            gluBuild2DMipmaps(GL_TEXTURE_2D, 4, this->m_width, this->m_height, GL_RGBA, GL_UNSIGNED_BYTE,
                              this->m_pixels);
        }
        else
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, 4, this->m_width, this->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                         this->m_pixels);
        }
    }
}

void Texture::detach()
{
    if (this->m_textures >= 0)
    {
        glDeleteTextures(1, &this->m_textures);
        this->m_textures = -1;
    }
}

void Texture::makeResident() {}

void Texture::grabBuffer(GLsizei width, GLsizei height, bool unused1, bool unused2)
{
    glReadPixels(0, glnHeight - width, width, height, GL_RGBA, GL_UNSIGNED_BYTE, this->m_pixels);

    // For perfect decomp, the unused variable has to be zf,
    // which somehow is achieved by doing an ifdef. The question
    // is, what the fuck was the ifdef supposed to be?
    bool unused = this->m_textures == 0;
#ifdef AMBROSIAISGREATOMGLOL
    unused = false;
    printf(unused);
#endif
    glBindTexture(GL_TEXTURE_2D, this->m_textures);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, this->m_pixels);
}

void Texture::createBuffer(int width, int height, int unused, void* buffer)
{
    this->m_pixels = (buffer) ? static_cast<GLuint*>(buffer) : new GLuint[width * height];
    this->m_width = width;
    this->m_height = height;
}

uchar Texture::getAlpha(int unk1, int unk2)
{
    // gets rightmost byte (R G B |A|)
    return this->m_pixels[unk1 + this->m_width * unk2] >> 24;
}

uchar Texture::getRed(int unk1, int unk2)
{
    // gets leftmost byte (|R| G B A)
    return this->m_pixels[unk1 + this->m_width * unk2];
}

int Texture::offsetGXtoGL(int offset)
{
    return this->offsetGXtoGL(this->m_tileSizeX, this->m_tileSizeY, this->m_width, offset);
}

int Texture::offsetGXtoGL(int unk1, int unk2, int unk3, int offset)
{
    return ((unk1 - 1) & offset) + unk3 * (((unk2 * unk1 - 1) & offset) / unk1) +
           unk2 * unk3 * (offset / (unk2 * unk3)) + unk1 * (offset / (unk2 * unk1) % (unk3 / unk1));
}

void Texture::decodeS3TC(int, int, unsigned __int8*, unsigned __int8*) {}

void Texture::decodeData(TexImg* tex)
{
    this->createBuffer(tex->m_width, tex->m_height, tex->m_format, tex->m_buffer);
    if (tex->m_buffer == nullptr)
    {
        TEXTUREPRINT("decoding data %d x %d : %08x\n", tex->m_width, tex->m_height, tex->m_texData);
        switch (tex->m_format)
        {
        case TEX_FMT_RGB565:
        {
            ushort* u16texData = static_cast<ushort*>(tex->m_texData);
            for (int i = 0; i < this->m_width * this->m_height; ++i)
            {
                ushort byteSwap = ((u16texData[i] & 0xFF) << 8) | ((u16texData[i] & 0xFF00) >> 8);

                uchar R = ((byteSwap >> 11) & 0x1F) << 3;
                uchar G = ((byteSwap >> 5) & 0x3F) << 2;
                uchar B = ((byteSwap)&0x1F) << 3;
                uchar A = 0xFF;

                int glOffset = this->offsetGXtoGL(i);
                if (glOffset >= this->m_width * this->m_height)
                {
                    TEXTUREPRINT("too big an offset!\n");
                    glOffset = 0;
                }

                this->m_pixels[glOffset] = A << 24 | B << 16 | G << 8 | R;
            }
        }
        break;
        case TEX_FMT_S3TC:
            this->decodeS3TC(this->m_width, this->m_height, (uchar*)tex->m_texData, (uchar*)this->m_pixels);
            break;
        case TEX_FMT_RGB5A3:
        {
            ushort* u16texData = static_cast<ushort*>(tex->m_texData);
            for (int j = 0; j < this->m_width * this->m_height; ++j)
            {
                ushort byteSwap = ((u16texData[j] & 0xFF00) >> 8) | ((u16texData[j] & 0xFF) << 8);
                uchar R, G, B, A;
                if (byteSwap & 0x8000)
                {
                    R = 8 * ((byteSwap >> 10) & 0x1F);
                    G = 8 * ((byteSwap >> 5) & 0x1F);
                    B = 8 * (((u16texData[j] & 0xFF00) >> 8) & 0x1F);
                    A = -1;
                }
                else
                {
                    R = 16 * (byteSwap >> 8 & 0xF);
                    G = 16 * ((byteSwap >> 4) & 0xF);
                    B = 16 * (byteSwap & 0xF);
                    A = 32 * ((byteSwap >> 12) & 7);
                }

                int glOffset = offsetGXtoGL(j);
                if (glOffset >= this->m_width * this->m_height)
                {
                    TEXTUREPRINT("too big an offset!\n");
                    glOffset = 0;
                }

                this->m_pixels[glOffset] = A << 24 | B << 16 | G << 8 | R;
            }
        }
        break;
        case TEX_FMT_I4:
        {
            uchar* u8texData = static_cast<uchar*>(tex->m_texData);
            for (int k = 0; k < (this->m_width / 2) * this->m_height; ++k)
            {
                unsigned __int8 tex = u8texData[k];
                // TODO:
                this->m_pixels[this->offsetGXtoGL(2 * k)] =
                    (((16 * ((tex & 0xF0) >> 4)) << 16) | 0xFF000000 | ((16 * ((tex & 0xF0) >> 4)) << 8) |
                     (16 * ((tex & 0xF0) >> 4)));
                this->m_pixels[this->offsetGXtoGL(2 * k + 1)] =
                    ((16 * (tex & 0xF)) | ((16 * (tex & 0xF)) << 8) | ((16 * (tex & 0xF)) << 16) | 0xFF000000);
            }
        }
        break;
        case TEX_FMT_I8:
            break;
        case TEX_FMT_IA4:
            break;
        case TEX_FMT_IA8:
            break;
        case TEX_FMT_RGBA8:
            break;
        case 9:
            break;
        default:
            TEXTUREHALT("Unknown texture format\n");
            break;
        }
        tex->m_buffer = this->m_pixels;
    }
}

void Texture::read(RandomAccessStream& stream)
{
    if (!strcmp(stream.filePath + strlen(stream.filePath) - 3, "txe"))
    {
        TexImg* img = new TexImg;
        img->importTxe(this, stream);
    }
    else if (!strcmp(stream.filePath + strlen(stream.filePath) - 3, "bti"))
    {
        TexImg* img = new TexImg;
        img->importBti(this, stream, nullptr);
    }
    else
    {
        TEXTUREHALT("Unknown texture extension (%s)!!\n", stream.filePath + strlen(stream.filePath) - 3);
    }

    gsys->addTexture(this, stream.filePath);
}
