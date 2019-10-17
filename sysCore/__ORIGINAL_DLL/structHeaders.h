struct ID32
{
    unsigned __int32 id;
    char sId[5]; // 0h
};

struct Colour
{
    unsigned __int8 R;
    unsigned __int8 G;
    unsigned __int8 B;
    unsigned __int8 A;
};

struct Stream
{
    int vtbl;
    char* filePath; // 4h
};

struct String
{
    int m_stringLen;
    char* m_string;
}