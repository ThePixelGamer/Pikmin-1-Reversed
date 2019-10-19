struct CoreNode
{
    int vtbl;         // _0
    char* name;       // 4h
    CoreNode* parent; // 8h
    CoreNode* next;   // Ch
    CoreNode* child;  // 10h
};

struct Vector3f
{
    float mX; // 0h
    float mY; // 4h
    float mZ; // 8h
};

struct Vector2f
{
    float x;
    float y;
};

struct BoundBox
{
    Vector3f m_maxBounds;
    Vector3f m_minBounds;
};

struct Matrix4f
{
    float mMatrix4f[4][4];
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
    float dword1C;      // _1C
    float dword20;      // _20
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

    int dword14;
    TexImgFormat m_format;
    int m_width;
    int m_height;
    int dword24;
    int m_dataSize;
    void* m_texData;
    int dword30;
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

struct StreamVTBL
{
    int (*readInt)();
    unsigned __int8 (*readByte)();
    short (*readShort)();
    float (*readFloat)();
    void (*readString)(char*, int);
    void (*readString_2)(String&);
    char* (*readString_3)();

    void (*writeInt)(int);
    void (*writeByte)(unsigned __int8);
    void (*writeShort)(short);
    void (*writeFloat)(float);
    void (*writeString)(char*);
    void (*writeString_2)(String&);

    void (*read)(void*, int);
    void (*write)(void*, int);

    int (*getPending)();
    int (*getAvailable)();

    void (*close)();
    bool (*getClosing)();
    void (*flush)();
};

struct Stream
{
    StreamVTBL* vtbl; // _0
    char* filePath;   // 4h
};

struct RandomAccessStreamVTBL
{
    int (*readInt)();
    unsigned __int8 (*readByte)();
    short (*readShort)();
    float (*readFloat)();
    void (*readString)(char*, int);
    void (*readString_2)(String&);
    char* (*readString_3)();

    void (*writeInt)(int);
    void (*writeByte)(unsigned __int8);
    void (*writeShort)(short);
    void (*writeFloat)(float);
    void (*writeString)(char*);
    void (*writeString_2)(String&);

    void (*read)(void*, int);
    void (*write)(void*, int);

    int (*getPending)();
    int (*getAvailable)();

    void (*close)();
    bool (*getClosing)();
    void (*flush)();
    int (*getPosition)();
    void (*setPosition)();
    int (*getLength)();
};

struct RandomAccessStream
{
    RandomAccessStreamVTBL* vtbl;
    char* filePath;
};

struct FaceNode
{
    int m_facenode_0;  // 14h
    int m_facenode_1;  // 18h
    int m_facenode_2;  // 1Ch
    int m_facenode_3;  // 20h
    int m_facenode_4;  // 24h
    int m_facenode_5;  // 28h
    int m_facenode_6;  // 2Ch
    int m_facenode_7;  // 30h
    int m_facenode_8;  // 34h
    int m_facenode_9;  // 38h
    int m_facenode_10; // 3Ch
    int m_facenode_11; // 40h
    int m_facenode_12; // 44h
};

struct DispList : public CoreNode
{
    int m_unk1;                  // 14h
    int m_dispDataCount;         // 18h
    unsigned __int8* m_dispData; // 1Ch
    int m_unk3;                  // 20h
    int m_unk4;                  // 24h
    int m_unk5;                  // 28h
    FaceNode m_face;             // 2Ch
};

struct MtxGroup
{
    int m_dependancyCount; // 0h
    int* m_dependancies;   // 4h
    int m_dispListCount;   // 8h
    DispList* m_dispLists; // Ch
};

struct VtxMatrix
{
    bool m_partiallyWeighted; // 1 byte
    char PADDING[3];          // 3 bytes (4 bytes)
    short m_index;            // 2 bytes (6 bytes)
    short PADDING_2;          // 2 bytes (8 bytes), aligned
};

struct Mesh : public CoreNode
{
    int m_unk1;            // 14h
    int m_usingEmbossBump; // 18h
    int m_dependancyIdx;   // 1Ch
    int m_mtxGroupCount;   // 20h
    MtxGroup* m_groups;    // 24h
    int m_unk2;            // 28h
    int m_vcd;             // 2Ch
};

struct Envelope
{
    int m_indicesCount;
    int* m_indices;
    float* m_weights;
};

struct Joint : public CoreNode
{
    void* m_pad1;           // 14h
    int m_index;            // 18h
    void* m_unk1;           // 1Ch
    int m_flags;            // 20h
    Vector3f m_scale;       // 24h
    Vector3f m_rotation;    // 30h
    Vector3f m_translation; // 3Ch
    Matrix4f m_unk3;        // 48h
    Matrix4f m_unk4;        // 88h

    int m_matPolyCount; // 110h
    struct MatPoly : public CoreNode
    {
        // 0h - VTBL
        // 10h - CoreNode
        class Material* m_mat; // 14h
        Mesh* m_mesh;          // 18h
        int m_index;           // 1Ch
        int mint20;            // 20h
        int mint24;            // 24h
    };

    BoundBox m_bounds;    // CCh
    bool m_useVolume;     // C9h
    bool m_useLightGroup; // CAh
};

struct TexAttr : public CoreNode
{
    int dword14;
    int m_texNum;
    short word1C;
    short word1E;
    short word20;
    short word22;
    float dword24;
    int dword28;
    Texture* m_texture;
    TexImg* m_image;
};

struct BaseShape
{
    int vtblPtr;
    char coreNode[16];
    int m_systemUsed;
    int m_currentAnims; // AnimContext* m_currentAnims;
    int* dword1C;
    int* m_animContext;
    int dword24;
    int dword28;
    int dword2C;
    int m_envelopeCount;
    Envelope* m_envelopes;
    int m_vtxMatrixCount;
    VtxMatrix* m_vtxMatrix;
    int m_materialCount;
    int m_materials;
    int m_tevInfoCount;
    int m_tevInfo;
    int m_meshCount;
    Mesh* m_meshes;
    int m_jointCount;
    struct Joint* m_joints;
    int m_jointUnkCount;
    struct JointUnk* m_jointUnk;
    int m_textureAttributesCount;
    TexAttr* m_textureAtttributes;
    int dword70;
    int m_textureCount;
    TexImg* m_textures;
    char gap7C[264];
    BoundBox m_collisionBounds;
    float m_gridSizeRadius;
    int m_gridSizeX;
    int m_gridSizeY;
    class CollGroup* m_collTris;
    int m_collTriInfoCount;
    struct CollTriInfo* m_collTriInfo;
    int m_baseRoomInfoCount;
    class RoomInfo* m_roomInfo;
    char gap1BC[192];
    int m_vertexCount;
    Vector3f* m_vertices;
    int m_colourCount;
    Colour* m_colours;
    int m_texCoordCount;
    int m_texCoordVecCount;
    Vector2f* m_texCoordVec2f[8];
    int m_vertexNormalCount;
    Vector3f* m_vertexNormals;
    int m_nbtCount;
    Vector3f* m_NBT;
};

struct CollGroup
{
    int collgroup0;
    _WORD word4;
    _DWORD dword8;
    _DWORD dwordC;
    _DWORD dword10;
    _DWORD dword14;
    _DWORD dword18;
};
