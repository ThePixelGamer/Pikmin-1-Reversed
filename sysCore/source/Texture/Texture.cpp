#include <Texture/Texture.h>
#include <sysCore.h>

Texture::Texture() : GfxObject() { this->tex = -1; }

void Texture::attach()
{
    if (this->tex == -1)
    {
        glGenTextures(1, &this->tex);
        glBindTexture(GL_TEXTURE_2D, this->tex);
    }
}

void Texture::detach()
{
    if (this->tex >= 0)
    {
        glDeleteTextures(1, &this->tex);
        this->tex = -1;
    }
}

void Texture::makeResident() {}

void Texture::grabBuffer(GLsizei width, GLsizei height, bool unused1, bool unused2)
{
    glReadPixels(0, glnHeight - width, width, height, GL_RGBA, GL_UNSIGNED_BYTE, this->pixels);
    // TODO: figure out what makes the variable below 'zf' not 'ST70_4'
    bool unused = this->tex == 0;
    glBindTexture(GL_TEXTURE_2D, this->tex);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, this->pixels);
}

unsigned __int8 Texture::getAlpha(int unk1, int unk2)
{
    // gets rightmost byte
    return this->pixels[unk1 + this->width * unk2] >> 24;
}

unsigned __int8 Texture::getRed(int unk1, int unk2) { return this->pixels[unk1 + this->width * unk2]; }

void Texture::read(RandomAccessStream& stream)
{
    if (!strcmp(stream.filePath + strlen(stream.filePath) - 3, "txe"))
    {
        // new teximg, import txe
    }
    else if (!strcmp(stream.filePath + strlen(stream.filePath) - 3, "bti"))
    {
        // if statement and texturehalt
        // new teximg, import bti
    }
}
