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

void Texture::decodeData(TexImg* tex)
{
    this->createBuffer(tex->m_width, tex->m_height, tex->m_format, tex->m_buffer);
    if (tex->m_buffer != nullptr)
    {
        TEXTUREPRINT("decoding data %d x %d : %08x\n", tex->m_width, tex->m_height, tex->m_texData);
        //< TODO!
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
