struct CoreNode
{
    int vtbl;         // _0
    char* name;       // 4h
    CoreNode* parent; // 8h
    CoreNode* next;   // Ch
    CoreNode* child;  // 10h
};

struct ID32
{
    unsigned __int32 id; // _0
    char sId[5];         // _4
};

struct Colour
{
    unsigned __int8 R; // _0
    unsigned __int8 G; // _1
    unsigned __int8 B; // _2
    unsigned __int8 A; // _3
};

struct Stream
{
    int vtbl;       // _0
    char* filePath; // _4
};

struct String
{
    int m_stringLen; // _0
    char* m_string;  // _4
};

struct Texture
{
    int m_gfxVar;       // _0
    short word4;        // _4
    short word6;        // _6
    short m_width;      // _8
    short m_height;     // _A
    int m_tileSizeX;    // _C
    int m_tileSizeY;    // _10
    GLvoid* m_pixels;   // _14
    GLuint* m_textures; // _18
    int dword1C;        // _1C
    int dword20;        // _20
    int dword24;        // _24
    int dword28;        // _28
    int dword2C;        // _2C
    int dword30;        // _30
};

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

struct TexImg : public CoreNode
{
    // _0 - _10 | CoreNode

    _DWORD dword14;
    TexImgFormat m_format;
    int m_width;
    int m_height;
    _DWORD dword24;
    int m_dataSize;
    void* m_texData;
    _DWORD dword30;
};


struct BTI
{
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
};
