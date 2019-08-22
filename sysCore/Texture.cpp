#include "Texture.h"

Texture::Texture() : GfxObject() {
    this->tex = -1;
}

void Texture::attach() {
	if (this->tex == -1)
	{
		glGenTextures(1, &this->tex);
		glBindTexture(GL_TEXTURE_2D, this->tex);
	}
}

void Texture::detach() {
    if(this->tex >= 0) {
        glDeleteTextures(1, &this->tex);
        this->tex = -1;
    }
}

void Texture::makeResident() {

}

void Texture::grabBuffer(GLsizei width, GLsizei height, bool unused1, bool unused2) {
    if(this->tex != -1) {

    }
}

unsigned __int8 Texture::getAlpha(int unk1, int unk2) {
	return this->pixels[unk1 + this->width * unk2] >> 24;
}

unsigned __int8 Texture::getRed(int unk1, int unk2) {
	return this->pixels[unk1 + this->width * unk2];
};