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

Texture::Texture() : GfxObject() { this->m_textures = -1; }

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

        //< TODO FIX
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
    // TODO: figure out what makes the variable below 'zf' not 'ST70_4'
    bool unused = this->m_textures == 0;
    glBindTexture(GL_TEXTURE_2D, this->m_textures);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, this->m_pixels);
}

void Texture::createBuffer(int width, int height, int unused, void* buffer)
{
    this->m_pixels = (buffer) ? static_cast<GLuint*>(buffer) : new GLuint[width * height];
    this->m_width = width;
    this->m_height = height;
}

unsigned __int8 Texture::getAlpha(int unk1, int unk2)
{
    // gets rightmost byte
    return this->m_pixels[unk1 + this->m_width * unk2] >> 24;
}

unsigned __int8 Texture::getRed(int unk1, int unk2) { return this->m_pixels[unk1 + this->m_width * unk2]; }

int Texture::offsetGXtoGL(int offset)
{
    return this->offsetGXtoGL(this->m_tileSizeX, this->m_tileSizeY, this->m_width, offset);
}

int Texture::offsetGXtoGL(int unk1, int unk2, int unk3, int offset)
{
    return ((unk1 - 1) & offset) + unk3 * (((unk2 * unk1 - 1) & offset) / unk1) +
           unk2 * unk3 * (offset / (unk2 * unk3)) + unk1 * (offset / (unk2 * unk1) % (unk3 / unk1));
}

void Texture::decodeS3TC(int, int, unsigned __int8*, unsigned __int8*) {

}

void Texture::decodeData(TexImg* tex)
{
    this->createBuffer(tex->m_width, tex->m_height, tex->m_format, tex->m_buffer);
    if (tex->m_buffer == nullptr)
    {
        TEXTUREPRINT("decoding data %d x %d : %08x\n", tex->m_width, tex->m_height, tex->m_texData);
        switch (tex->m_format)
        {
            case TexImgFormat::TEX_FMT_RGB565:
			{
                unsigned short* u16texData = (unsigned short*)tex->m_texData;
                for (int i = 0; i < this->m_width * this->m_height; ++i)
                {
                    unsigned short byteSwap = ((u16texData[i] & 0xFF00) >> 8) | ((u16texData[i] & 0xFF) << 8);
                    //u16texData[i];
                    unsigned short v29 = 8 * (((u16texData[i] & 0xFF00) >> 8) & 0x1F);
                    int v27 = this->offsetGXtoGL(i);
                    if (v27 >= this->m_width * this->m_height)
                    {
                        TEXTUREHALT("too big an offset!\n");
                        v27 = 0;
                    }
                    this->m_pixels[v27] = (8 * ((byteSwap >> 11) & 0x1F)) | ((4 * ((byteSwap >> 5) & 0x3F)) << 8) | (v29 << 16) | 0xFF000000;
                }
            } break;
            case TexImgFormat::TEX_FMT_S3TC:
                this->decodeS3TC(this->m_width, this->m_height, (unsigned __int8*)tex->m_texData, (unsigned __int8*)this->m_pixels);
            break;
            case TexImgFormat::TEX_FMT_RGB5A3:
            {
                unsigned short* u16texData = (unsigned short*)tex->m_texData;
                for (int j = 0; j < this->m_width * this->m_height; ++j)
                {
                    unsigned short byteSwap = ((u16texData[j] & 0xFF00) >> 8) | ((u16texData[j] & 0xFF) << 8);
                    unsigned __int8 v37, v36, v35, v34;
                    if ( byteSwap & 0x8000 )
                    {
                        v37 = 8 * ((byteSwap >> 10) & 0x1F);
                        v36 = 8 * ((byteSwap >> 5) & 0x1F);
                        u16texData[j];
                        v35 = 8 * (((u16texData[j] & 0xFF00) >> 8) & 0x1F);
                        v34 = -1;
                    }
                    else
                    {
                        v37 = 16 * (byteSwap >> 8 & 0xF);
                        v36 = 16 * ((byteSwap >> 4) & 0xF);
                        v35 = 16 * (byteSwap & 0xF);
                        v34 = 32 * ((byteSwap >> 12) & 7);
                    }
                    int v32 = offsetGXtoGL(j);
                    if ( v32 >= this->m_width * this->m_height )
                    {
                        TEXTUREHALT("too big an offset!\n");
                        v32 = 0;
                    }
                    this->m_pixels[v32] = v37 | (v36 << 8) | (v35 << 16) | (v34 << 24);
                }
            } break;
            case TexImgFormat::TEX_FMT_I4: {
                unsigned __int8* u8texData = (unsigned __int8*)tex->m_texData;
                for (int k = 0; k < (this->m_width/2) * this->m_height / 2; ++k )
                {
                    unsigned __int8 v4 = u8texData[k];
                    this->m_pixels[Texture::offsetGXtoGL(2 * k)] = (16 * ((v4 & 0xF0) >> 4)) | ((16 * ((v4 & 0xF0) >> 4)) << 8) | ((16 * ((v4 & 0xF0) >> 4)) << 16) | 0xFF000000;
                    this->m_pixels[Texture::offsetGXtoGL(2 * k + 1)] = (16 * (v4 & 0xF)) | ((16 * (v4 & 0xF)) << 8) | ((16 * (v4 & 0xF)) << 16) | 0xFF000000;
                }
            } break;
            /*case TexImgFormat::TEX_FMT_I8:
            v20 = *(tex->11);
            for ( l = 0; l < tex->5) * tex->4); ++l )
            {
                v7 = *(l + v20) | (*(l + v20) << 8) | (*(l + v20) << 16) | 0xFF000000;
                *(tex->5) + 4 * Texture::offsetGXtoGL(v40, l)) = v7;
            }
            break;
            case TexImgFormat::TEX_FMT_IA4:
            v24 = *(tex->11);
            for ( m = 0; m < tex->5) * tex->4); ++m )
            {
                v5 = *(m + v24);
                *(tex->5) + 4 * Texture::offsetGXtoGL(v40, m)) = (16 * (v5 & 0xF)) | ((16 * (v5 & 0xF)) << 8) | ((16 * (v5 & 0xF)) << 16) | ((16 * ((v5 & 0xF0) >> 4)) << 24);
            }
            break;
            case TexImgFormat::TEX_FMT_IA8:
            v22 = *(tex->11);
            for ( n = 0; n < tex->5) * tex->4); ++n )
            {
                v6 = ((*(v22 + 2 * n) & 0xFF00) >> 8) | ((*(v22 + 2 * n) & 0xFF) << 8);
                *(v22 + 2 * n);
                *(tex->5) + 4 * Texture::offsetGXtoGL(v40, n)) = v6 | (v6 << 8) | (v6 << 16) | (HIBYTE(v6) << 24);
            }
            break;
            case TexImgFormat::TEX_FMT_RGBA8:
            v18 = *(tex->11);
            for ( ii = 0; ii < tex->5) * tex->4); ++ii )
            {
                v8 = ((*(v18 + 2 * ((ii & 0xF) + 32 * (ii / 16))) & 0xFF00) >> 8) | ((*(v18 + 2
                                                                                            * ((ii & 0xF) + 32 * (ii / 16))) & 0xFF) << 8);
                *(tex->5) + 4 * Texture::offsetGXtoGL(v40, ii)) = v8 | (HIBYTE(v8) << 24);
            }
            for ( jj = 0; jj < tex->5) * tex->4); ++jj )
            {
                v9 = (((*(v18 + 2 * ((jj & 0xF) + 32 * (jj / 16)) + 32) & 0xFF00) >> 8) | ((*(v18
                                                                                            + 2
                                                                                            * ((jj & 0xF) + 32 * (jj / 16))
                                                                                            + 32) & 0xFF) << 8)) >> 8;
                *(v18 + 2 * ((jj & 0xF) + 32 * (jj / 16)) + 32);
                v10 = (*(v18 + 2 * ((jj & 0xF) + 32 * (jj / 16)) + 32) & 0xFF00) >> 8;
                v11 = Texture::offsetGXtoGL(v40, jj);
                *(tex->5) + 4 * v11) |= (v9 << 8) | (v10 << 16);
            }
            break;
            case TexImgFormat::TEX_FMT_RGB565:
            v15 = *(tex->11);
            for ( kk = 0; kk < tex->5) * tex->4); ++kk )
            {
                v12 = *(kk + v15) | (*(kk + v15) << 8) | (*(kk + v15) << 16) | 0xFF000000;
                *(tex->5) + 4 * Texture::offsetGXtoGL(v40, kk)) = v12;
            }
            break;*/
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
    }
    else if (!strcmp(stream.filePath + strlen(stream.filePath) - 3, "bti"))
    {
        TexImg* img = new TexImg;
    }
    else
    {
        TEXTUREHALT("Unknown texture extension (%s)!!\n", stream.filePath + strlen(stream.filePath) - 3);
    }
}
