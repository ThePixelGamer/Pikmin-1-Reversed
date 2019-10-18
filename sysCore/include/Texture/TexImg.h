#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef TEXIMG_H
#define TEXIMG_H

#include <Nodes/CoreNode.h>
#include <Stream/RandomAccessStream.h>

enum TexImgFormat
{
    TEX_FMT_RGB565,
    TEX_FMT_S3TC,
    TEX_FMT_RGB5A3,
    TEX_FMT_I4,
    TEX_FMT_I8,
    TEX_FMT_IA4,
    TEX_FMT_IA8,
    TEX_FMT_RGBA8
};

class BTI
{
public:
    unsigned char format; // GXTexFmt
    unsigned char transparent;
    unsigned short width;
    unsigned short height;
    unsigned char wrapS; // GXTexWrapMode
    unsigned char wrapT; // GXTexWrapMode
    unsigned char fPalette;
    unsigned char paletteFormat; // GXTlutFormat
    unsigned short nPalette;
    int toPalette;
    unsigned char mipmap;
    unsigned char edgeLOD;
    unsigned char biasClamp;
    unsigned char maxAniso;  // GXAnisotropy
    unsigned char minFilter; // GXTexFilter
    unsigned char magFilter; // GXTexFilter
    char minLOD;
    char maxLOD;
    unsigned char nImage;
    short lodBias;
    int toImage;
    void read(RandomAccessStream& stream)
    {
        this->format = stream.readByte();
        this->transparent = stream.readByte();
        this->width = stream.readShort();
        this->height = stream.readShort();
        this->wrapS = stream.readByte();
        this->wrapT = stream.readByte();
        this->fPalette = stream.readByte();
        this->paletteFormat = stream.readByte();
        this->nPalette = stream.readByte();
        this->toPalette = stream.readInt();
        this->mipmap = stream.readByte();
        this->edgeLOD = stream.readByte();
        this->biasClamp = stream.readByte();
        this->maxAniso = stream.readByte();
        this->minFilter = stream.readByte();
        this->magFilter = stream.readByte();
        this->minLOD = stream.readByte();
        this->maxLOD = stream.readByte();
        this->nImage = stream.readShort();
        this->nImage = stream.readShort();
        this->lodBias = stream.readShort();
        this->toImage = stream.readInt();
    }
};

class SYSCORE_API TexImg : public CoreNode
{
public:
    // 0h vtable
    // 10h CoreNode
    int dword14;     // _14
    int m_format;    // _18
    int m_width;     // _1C
    int m_height;    // _20
    int dword24;     // _24
    int m_dataSize;  // _28
    void* m_texData; // _2C
    void* m_buffer;  // _30

    TexImg();

    int calcDataSize(int format, int width, int height);
    int convFormat(unsigned __int32 fmt);
    char* formatName(unsigned __int32 fmt);
    static void getTileSize(int, unsigned __int32&, unsigned __int32&);
    void importBti(class Texture*, RandomAccessStream&, unsigned __int8*);
    void importTxe(class Texture*, RandomAccessStream&);

    void readTexData(class Texture*, RandomAccessStream&, unsigned __int8*);
};

#endif
