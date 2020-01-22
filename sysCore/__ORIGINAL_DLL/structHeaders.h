enum PROP_TYPE
{
    CHAR_PROP = 0,
    SHORT_PROP,    // 1
    INT_PROP,      // 2
    FLOAT_PROP,    // 3
    COLOUR_PROP,   // 4
    IMAGE_PROP,    // 5
    STRING_PROP,   // 6
    UNK7,          // 7
    CHAR_PTR_PROP, // 8
    UNK9           // 9
};

struct CoreNode
{
    int vtbl;         // _0
    char* name;       // 4h
    CoreNode* parent; // 8h
    CoreNode* next;   // Ch
    CoreNode* child;  // 10h
};

struct Node
{
    // vtable 0h
    //(CoreNode: 4h-10h)
    int type;    // 14h
    int flags;   // 18h
    int dword1c; // 1Ch
};

struct BaseRoomInfo
{
    int m_unk1; // _0
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

struct ShortColour
{
    unsigned short R; // _0
    unsigned short G; // _1
    unsigned short B; // _2
    unsigned short A; // _3
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

typedef void* GLvoid;
typedef unsigned int GLuint;

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

    int m_index;
    TexImgFormat m_format;
    int m_width;
    int m_height;
    int dword24;
    int m_dataSize;
    void* m_texData;
    void* m_pixels;
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
    int m_nodeCount;             // 24h
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
    int m_index;           // 14h
    int m_usingEmbossBump; // 18h
    int m_dependancyIdx;   // 1Ch
    int m_mtxGroupCount;   // 20h
    MtxGroup* m_groups;    // 24h
    int m_unk2;            // 28h
    int m_vcd;             // 2Ch, (|= 0x1000 if emboss NBT is used)
};

struct Envelope
{
    int m_indicesCount;
    int* m_indices;
    float* m_weights;
};

enum JointType // originally called kind
{
    NULL,
    MESH,
    JOINT
};

struct Joint : public CoreNode
{
    struct MatPoly : public CoreNode
    {
        // 0h - VTBL
        // 10h - CoreNode
        class Material* m_mat; // 14h
        Mesh* m_mesh;          // 18h
        int m_index;           // 1Ch
        int m_int20;           // 20h
        int m_int24;           // 24h
    };

    int m_index;            // 14h
    int m_parent;           // 18h
    JointType m_type;       // 1Ch
    int m_flags;            // 20h
    Vector3f m_scale;       // 24h
    Vector3f m_rotation;    // 30h
    Vector3f m_translation; // 3Ch
    Matrix4f m_unk3;        // 48h
    // CANT BE MATRIX4F
    Matrix4f m_unk4;        // 88h
    _BYTE m_isBillboard;    // 89h
    _BYTE m_useVolume;      // 8Ah
    _BYTE m_useLightGroup;  // 8Bh

    BoundBox m_bounds;     // CCh
    MatPoly m_matPolygons; // E4h

    _DWORD m_dword10C; // 10Ch
    _DWORD m_dword110; // 110h
    _DWORD m_dword114; // 114h
    _DWORD m_dword118; // 118h
};

struct TexAttr : public CoreNode
{
    int m_index;
    int m_texNum;
    short m_tiling; // | 1 == clamp
    short m_flags;  // EDG = 2, XLU = 4
    short word20;
    short word22;
    float dword24;
    char* m_name;
    Texture* m_texture;
    TexImg* m_image;
};

struct DataChunk
{
    int m_dataIndex; // _0
    int m_dataSize;  // _4
    float* m_data;   // _8
};

struct param
{
    int param1;
    int param2;
    int param3;
};

struct SRT
{
    Vector3f m_scale;
    Vector3f m_rotation;
    Vector3f m_position;
};

struct AnimJoint
{
    param sx_param;
    param sy_param;
    param sz_param;

    param rx_param;
    param ry_param;
    param rz_param;

    param tx_param;
    param ty_param;
    param tz_param;

    _BYTE gap0[8];
    Matrix4f matrix4f74;
    SRT srtB4;
    _WORD wordD8;
};

struct AnimData : public CoreNode
{
    DataChunk* m_scaling;
    DataChunk* m_rotation;
    DataChunk* m_translation;
    short* m_jointIndex;
    int dword24;
    int m_numJoints;
    int dword2C;
    int m_numFrames;
    int dword34;
    int dword38;
    AnimJoint* dword3C;
    int dword40;
};

struct LightFlare : public CoreNode
{
    int dword14;
    int dword18;
    int dword1C;
    int dword20;
};

struct LightGroup : public CoreNode
{
    int dword14;
    int dword18;
    int dword1C;
    int dword20;
    int dword24;
    int dword28;
    int dword2C;
    int dword30;
    int dword34;
    int dword38;
    int dword3C;
    LightFlare lightflare40;
    int dword64;
    int dword68;
};

struct ObjCollInfo : public CoreNode
{
    int dword14;
    int dword18;
    int dword1C;
    int dword20;
    int dword24;
    int dword28;
    int dword2C;
    int dword30;
    int dword34;
    int dword38;
    int dword3C;
    int dword40;
    int dword44;
    int dword48;
    int dword4C;
    int dword50;
};
struct RouteLink : public CoreNode
{
    int dword14;
};

struct RoutePoint
{
    int dword14;
    int dword18;
    int dword1C;
    int dword20;
    int dword24;
    int dword28;
    int dword2C;
    int dword30;
    int dword34;
    int dword38;
    RouteLink routelink3C;
};

struct RouteGroup : public CoreNode
{
    _DWORD dword14;
    _BYTE gap18[64];
    _DWORD dword58;
    _BYTE gap5C[8];
    _DWORD dword64;
    _BYTE gap68[84];
    _DWORD dwordBC;
};

struct CollGroup
{
    int collgroup0;
    short* word4;
    int dword8;
    int dwordC;
    int dword10;
    int dword14;
    int dword18;
};

struct BaseShape : public CoreNode
{
    // _0 vtbl
    // _10 corenode
    int m_systemUsed;                         // _14
    class AnimContext* m_currentAnims;        // _18 AnimContext* m_currentAnims;
    int* m_animOverrides;                     // _1C
    int* m_animContext;                       // _20
    class AnimFrameCacher* m_animFrameCacher; // _24
    Matrix4f* m_animMatrix;                   // _28
    int dword2C;                              // _2C
    int m_envelopeCount;                      // _30
    Envelope* m_envelopes;                    // _34
    int m_vtxMatrixCount;                     // _38
    VtxMatrix* m_vtxMatrix;                   // _3C
    int m_materialCount;                      // _40
    class Material* m_materials;              // _44
    int m_tevInfoCount;                       // _48
    class TevInfo* m_tevInfo;                 // _4C
    int m_meshCount;                          // _50
    Mesh* m_meshes;                           // _54
    int m_jointCount;                         // _58
    struct Joint* m_joints;                   // _5C
    int m_routeGroupCount;                    // _60
    RouteGroup* m_routeGroup;                 // _64
    int m_textureAttributesCount;             // _68
    TexAttr* m_textureAtttributes;            // _6C
    int dword70;                              // _70
    int m_textureCount;                       // _74
    TexImg* m_textures;                       // _78
    AnimData m_animData;                      // _7C
    LightGroup m_groups;                      // _C0
    ObjCollInfo m_collisionInfo;              // _12C
    int dword180;                             // _180
    BoundBox m_courseExtents;                 // _184
    float m_gridSize;                         // _19C
    int m_gridSizeX;                          // _1A0
    int m_gridSizeY;                          // _1A4
    int* m_collisionTriangles;                // _1A8
    int m_collTriCount;                       // _1AC
    _DWORD* m_collTriInfo;                    // _1B0
    int m_baseRoomCount;                      // _1B4
    BaseRoomInfo* proominfo1B8;               // _1B8
    _BYTE gap1BC[0xC0];                       // _1BC
    int m_vertexCount;                        // _27C
    Vector3f* m_vertices;                     // _280
    int m_vertColourCount;                    // _284
    Colour* m_vertColours;                    // _288
    int m_texCoordSetCount;                   // _28C
    int m_texCoordCount[8];                   // _290
    Vector2f* m_texCoords[8];                 // _2B0
    int m_normalCount;                        // _2D0
    Vector3f* m_normals;                      // _2D4
    int m_nbtCount;                           // _2D8
    Vector3f* m_nbt;                          // _2DC
    _DWORD dword2E0;                          // _2E0
    _DWORD dword2E4;                          // _2E4
    _DWORD dword2E8;                          // _2E8
    _DWORD dword2EC;                          // _2EC
    _BYTE byte2F0;                            // _2FO
};

struct AyuStack
{
    int m_allocType;       // 0h
    int m_size;            // 4h
    int m_used;            // 8h
    unsigned __int32* top; // Ch
    int m_topSize;         // 10h
    unsigned __int32* sp;  // 14h ( this + 20 ) | <- top probably???
    int m_topFree;         // 18h
    bool overflowProtect;  // 1Ch
    bool active;           // 1Dh ( this + 29 )
    char* name;            // 20h ( this + 32 )
};

struct AyuHeap : public AyuStack
{
    int dword24;
};

struct GfxobjInfo
{
    int vtbl;         // 0h
    GfxobjInfo* prev; // 4h
    GfxobjInfo* next; // 8h
    char* str;        // Ch
    ID32 id32;        // 10h
    int attached;     // 1Ch
};

struct StdSystem
{
    int vtbl;              // 0h
    bool pending;          // 4h
    int dword8;            // 8h
    float initialFade;     // Ch
    float endFade;         // 10h
    void* m_consFont;      // 14h, class Font
    int m_frameClamp;      // 18h
    int dword1C;           // 1Ch
    int m_debugPrint;      // 20h
    int dword24;           // 24h
    int dword28;           // 28h
    int dword2C;           // 2Ch
    void* dword30;         // 30h
    void* dword34;         // 34h
    void* m_shapeTimer;    // 38h, class Timers
    void* m_textureCacher; // 3Ch, class TextureCacher
    int matrixUnk;         // 40h
    Matrix4f* matrix;      // 44h
    char* bloRoot;         // 48h
    char* texRoot;         // 4Ch
    char* baseDir;         // 50h
    char* fileName;        // 54h
    AyuHeap heaps[8];      // 58h
    int heapNum;           // 198h
    void* dword19C;        // 19Ch
    void* dword1A0;        // 1A0h
    void* dword1A4;        // 1A4h
    void* dword1A8;        // 1A8h
    void* dword1AC;        // 1ACh
    int m_lightCount;      // 1B0h
    void* dword1B4;        // 1B4h
    void* dword1B8;        // 1B8h
    void* dword1BC;        // 1BCh
    void* dword1C0;        // 1C0h
    void* dword1C4;        // 1C4h
    int unkShutdownCode;   // 1C8h
    void* dword1CC;        // 1CCh
    GfxobjInfo gfx;        // 1D0h
    bool m_toAttachObjs;   // 1F0h
    char* m_textureBase1;  // 1F4h
    char* m_textureBase2;  // 1F8h
    class Shape* shape;    // 1FCh
    CoreNode core1;        // 200h
    CoreNode core2;        // 214h
    void* dword228;        // 228h
    void* m_lFlares;       // 22Ch
    void* dword230;        // 230h
    void* dword234;        // 234h
    void* dword238;        // 238h
    void* dword23C;        // 23Ch
    void* dword240;        // 240h
};

struct TexobjInfo : public GfxobjInfo
{
    Texture* texData;
};

struct Graphics
{
    int vtbl;
    _DWORD dword4;
    _DWORD dword8;
    _DWORD dwordC;
    _DWORD dword10;
    _BYTE m_light[724]; // _14
    _DWORD dword2E8;
    _BYTE gap2EC[32];
    _DWORD dword30C;
    _DWORD dword310;
    _DWORD dword314;
    _DWORD dword318;
    _DWORD dword31C;
    _DWORD dword320;
    _BYTE byte324;
    _BYTE byte325;
    _BYTE gap326[2];
    _DWORD dword328;
    _DWORD dword32C;
    _DWORD dword330;
    _DWORD dword334;
    _DWORD dword338;
    struct LightCamera* m_lightCam;
    _DWORD dword340;
    _DWORD dword344;
    _DWORD dword348;
    _DWORD dword34C;
    _DWORD dword350;
    struct MaterialHandler* m_matHandler;
    _DWORD dword358;
    _DWORD dword35C;
    _DWORD dword360;
    _DWORD dword364;
    _DWORD dword368;
    _DWORD dword36C;
    _DWORD dword370;
    _DWORD dword374;
    _DWORD dword378;
    _DWORD dword37C;
    _DWORD dword380;
    _DWORD dword384;
    _DWORD dword388;
    _DWORD dword38C;
    _DWORD dword390;
    char char394;
};

struct CacheInfo
{
    int dword0;        // _0
    CacheInfo* dword4; // _4
    CacheInfo* dword8; // _8
    int dwordC;        // _C
    int dword10;       // _10
    int dword14;       // _14
};

struct AnimCacheInfo
{
    int dword0;
    int dword4;
    int dword8;
    int dwordC;
    CacheInfo* dword10;
    int dword14;
    int dword18;
    int dword1C;
};

struct AnimData : public CoreNode
{
    // vtable 0h
    // CoreNode: 4h-10h)
    DataChunk* m_scaling;     // _14
    DataChunk* m_rotation;    // _18
    DataChunk* m_translation; // _1C
    int* dword20;             // _20
    int dword24;              // _24
    int m_jointCount;         // _28
    int dword2C;              // _2C
    int m_frameCount;         // 30h
    int dword34;              // _34
    int dword38;              // _38
    int dword3C;              // _3C
    AnimCacheInfo* animCache; // 40h
};

struct Controller
{
    _BYTE node[32];
    _DWORD dword20;
    _DWORD dword24;
    _DWORD dword28;
    _DWORD dword2C;
    _DWORD dword30;
    _DWORD dword34;
    _DWORD dword38;
    _DWORD dword3C;
    _DWORD dword40;
    _BYTE byte44;
    _BYTE byte45;
    _BYTE byte46;
    _BYTE byte47;
    _BYTE byte48;
    _BYTE byte49;
    _BYTE byte4A;
    _BYTE byte4B;
    _BYTE byte4C;
};

struct AtxStream : public Stream
{
    // 0h - vtbl
    // 4h - stream var
    class TcpStream* m_stream; // 8h
    int m_dwordC;
};

struct AtxFileStream : public RandomAccessStream
{
    int position;     // 8h
    int length;       // Ch
    AtxStream stream; // 10h
};

struct BufferedInputStream : public RandomAccessStream
{
    // 4h - Stream variable + vtbl ptr
    unsigned char* m_buffer; // 8h
    int m_bufferSize;        // Ch
    int m_amountToRead;      // 10h
    int m_readLimit;         // 14h
    int m_position;          // 18h
    Stream* m_bufferStream;  // 1Ch
};

struct BufferedStream : public RandomAccessStream
{
    // 4h - Stream variable + vtbl ptr
    RandomAccessStream* m_stream;     // 8h
    BufferedInputStream m_buffStream; // 1Ch
};

struct ControllerMgr
{
    int vtblPtr;
    BYTE lpKeyState[0x100];
};

struct System : public StdSystem
{
    _DWORD dword244;
    _DWORD dword248;
    bool m_textureByteUnk;  // 24Ch
    bool m_isFullScreen;    // 24Dh
    bool m_unkGameAppBool2; // 24Eh
    _DWORD dword250;
    int m_defaultBPP; // 254h
    _DWORD dword258;  // 258h
    void* m_heapMemory;
    int m_heapSize; // 260h
    AtxFileStream atxfilestream264;
    BufferedStream bufferedStream;
    int streamType;
    ControllerMgr controllermgr;
    char m_hostName[0x80];       // 3B8h
    class AtxRouter* mainRouter; // 438h
    _DWORD dword43C;
    LARGE_INTEGER dword440;
    _DWORD dword444;
    LARGE_INTEGER dword448;
    _DWORD dword44C;
    _DWORD dword450;
    _DWORD dword454;
    float frameTime; // 458h
    float frameRate; // 45Ch
    void* dword460;
    void* dword464; // 464h
    int frameCount; // 468h
};

struct PVWKeyInfoU8
{
    // 12 bytes big
    char m_unk1; // supposed to be char, but for decomp to work properly has to be char
    float m_unk2;
    float m_unk3;
};

struct PVWKeyInfoF32
{
    float m_keyframeA;
    float m_keyframeB;
    float m_keyframeC;
};

// POLYGON1 VARIABLES

struct PVWPolygonData // ???
{
    // 0x28/40 bytes big
    int m_unk1;
    PVWKeyInfoU8 m_keyinfoa;
    PVWKeyInfoU8 m_keyinfob;
    PVWKeyInfoU8 m_keyinfoc;
};

struct PVWPolygon // ???
{
    int m_count;
    PVWPolygonData* m_data;
};

// POLYGON2 VARIABLES

struct PVWPolygon2Data // ???
{
    // 0x10/16 bytes big
    int m_unk1;
    PVWKeyInfoU8 m_keyinfo;
};

struct PVWPolygon2 // ???
{
    int m_count;
    PVWPolygon2Data* m_data;
};

struct PVWPolygonColourInfo
{
    Colour m_diffuseColor;
    unsigned int unsigned4;
    float float8;
    PVWPolygon m_polygon1;
    PVWPolygon2 m_polygon2; // UNSURE OF NAME
    float float1C;
};

struct PVWLightingInfo
{
    int m_unk1;
    float m_unk2;
    _DWORD dword8;
};

struct PVWPeInfo
{
    int m_unk1;
    int m_unk2;
    int m_unk3;
    int m_unk4;
};

struct PVWTexGenData
{
    char m_unk1;
    char m_unk2;
    char m_unk3;
    char m_unk4;
};

struct PVWTextureKeyframeData // ???
{
    int m_unk1;
    PVWKeyInfoF32 m_scale;       // 16 bytes
    PVWKeyInfoF32 m_rotation;    // 28 bytes
    PVWKeyInfoF32 m_translation; // 40 bytes
};

struct PVWTexDataHolder // ???
{
    int m_count;
    PVWTextureKeyframeData* data;
};

struct PVWTextureData
{
    _DWORD dword0;
    _DWORD dword4;
    _DWORD dword8;
    _WORD wordC;
    _WORD wordE;
    _BYTE byte10;
    _BYTE byte11;
    _BYTE byte12;
    _BYTE byte13;
    bool dword14;
    _DWORD dword18;
    float float1C;
    float float20;
    float float24;
    float float28;
    float float2C;
    float float30;
    float float34;
    _DWORD dword38;
    float float3C;
    PVWTexDataHolder m_TexDataHolderA; // 48h
    PVWTexDataHolder m_TexDataHolderB; // 50h
    PVWTexDataHolder m_TexDataHolderC; // 58h
};

struct PVWTextureInfo
{
    Vector3f vector3f0;
    int m_textureDataCount;
    int m_genDataCount;
    _DWORD dword14;
    _DWORD dword18;
    PVWTextureData* m_textureData;
    PVWTexGenData* m_texGenData;
};

struct Material : public CoreNode
{
    int m_index;
    int m_flag; // PVWTexInfo = (& 1), TEX = 2, XLU = 4
    int m_textureIndex;
    _DWORD dword20;
    _DWORD dword24;
    _DWORD dword28;
    PVWPolygonColourInfo m_colourInfo; // 2Ch
    PVWLightingInfo m_lightingInfo;    // 50h
    PVWPeInfo m_envInfo;
    PVWTextureInfo m_textureInfo; // 68h
    _DWORD dword8C;
    ShortColour* m_color;
    _DWORD dword94;
    _DWORD dword98;
};

struct MatobjInfo : public GfxobjInfo
{
    _DWORD unk;
};