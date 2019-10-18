#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef TEXTURE_H
#define TEXTURE_H

#include <Windows.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include <Object/GfxObject.h>
#include <Stream/RandomAccessStream.h>
#pragma comment(lib, "opengl32.lib")

class SYSCORE_API Texture : public GfxObject
{
public:
    short word4;                  // _4
    short word6;                  // _6
    ushort m_width;               // _8
    ushort m_height;              // _A
    unsigned __int32 m_tileSizeX; // _C
    unsigned __int32 m_tileSizeY; // _10
    GLuint* m_pixels;             // _14
    GLuint m_textures;            // _18
    int dword1C;                  // _1C
    int dword20;                  // _20
    int dword24;                  // _24
    int dword28;                  // _28
    int dword2C;                  // _2C
    int dword30;                  // _30

    Texture();

    virtual void attach();
    virtual void detach();
    virtual void makeResident();

    void read(RandomAccessStream&);
    void grabBuffer(GLsizei, GLsizei, bool, bool);
    void createBuffer(int, int, int, void*);
    uchar getAlpha(int, int);
    uchar getRed(int, int);
    int offsetGXtoGL(int);
    int offsetGXtoGL(int, int, int, int);
    void decodeS3TC(int, int, uchar*, uchar*);

    void decodeData(class TexImg*);
};

#endif
