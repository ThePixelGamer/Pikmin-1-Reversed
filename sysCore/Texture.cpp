#include "Texture.h"

Texture::Texture() : GfxObject() {
    this->tex = -1;
}

void Texture::attach() {

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