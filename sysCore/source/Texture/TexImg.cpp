#include <Graphics/Graphics.h>
#include <Texture/TexImg.h>
#include <Texture/Texture.h>

TexImg::TexImg() : CoreNode("texImg")
{
    this->dword24 = 1;
    this->m_buffer = nullptr;
}

int TexImg::calcDataSize(int format, int width, int height)
{
    int dataSize = 0;
    switch (format)
    {
    case TEX_FMT_RGB565:
        dataSize = 2 * height * width;
        break;
    case TEX_FMT_S3TC:
        dataSize = 4 * (height * width / 8);
        break;
    case TEX_FMT_RGB5A3:
        dataSize = 2 * height * width;
        break;
    case TEX_FMT_I4:
        dataSize = height * width / 2;
        break;
    case TEX_FMT_I8:
        dataSize = height * width;
        break;
    case TEX_FMT_IA4:
        dataSize = height * width;
        break;
    case TEX_FMT_IA8:
        dataSize = 2 * height * width;
        break;
    case TEX_FMT_RGBA8:
        dataSize = 4 * height * width;
        break;
    case 8:
        dataSize = height * width;
        break;
    case 9:
        dataSize = height * width;
        break;
    default:
        return dataSize;
    }
    return dataSize;
}

static int btiFormats[] = {3, 4, 5, 6, 0, 2, 7, 0, 0, 0, 0, 0, 0, 0, 1};
static char* btiFormatNames[15] = {"TEX_FMT_RGB565", "TEX_FMT_S3TC", "TEX_FMT_RGB5A3", "TEX_FMT_I4",
                                   "TEX_FMT_I8",     "TEX_FMT_IA4",  "TEX_FMT_IA8",    "TEX_FMT_RGBA8"};

int TexImg::convFormat(unsigned __int32 fmt) { return btiFormats[fmt]; }
char* TexImg::formatName(unsigned __int32 fmt) { return btiFormatNames[fmt]; }

void TexImg::getTileSize(int tileFmt, unsigned __int32& tX, unsigned __int32& tY)
{
    switch (tileFmt)
    {
    case 3:
        tX = 8;
        tY = 8;
        break;
    case 4:
    case 5:
    case 9:
        tX = 8;
        tY = 4;
        break;
    default:
        tX = 4;
        tY = 4;
        break;
    }
}

void TexImg::importBti(Texture* tex, RandomAccessStream& stream, unsigned __int8* bytes)
{
    BTI bti;
    bti.read(stream);
    this->m_format = static_cast<TexImgFormat>(this->convFormat(bti.format));
    this->m_width = bti.width;
    this->m_height = bti.height;

    unsigned __int32 x;
    unsigned __int32 y;
    TexImg::getTileSize(this->m_format, x, y);
    if (this->m_width % x || this->m_height % y)
        GRAPHICSHALT("Texture %s is not correct size %d x %d\n", stream.filePath, this->m_width, this->m_height);
    if (bti.toImage != 32)
        GRAPHICSHALT("Bti file has imageData at offset %d!!!\n", bti.toImage);

    tex->word6 = (-(bti.wrapT != 0) + 256) | (bti.wrapS == 0);
    this->readTexData(tex, stream, bytes);
}

void TexImg::importTxe(Texture* tex, RandomAccessStream& stream)
{
    this->m_width = stream.readShort();
    this->m_height = stream.readShort();
    this->m_format = stream.readShort();
    tex->word6 = this->m_format >> 8;
    this->m_format &= 0xFF;

    __int16 unused = stream.readShort();
    int dataSize = stream.readInt();
    for (int i = 0; i < 10; i++)
        __int16 byte = stream.readShort();

    this->readTexData(tex, stream, nullptr);
}

void TexImg::readTexData(Texture* tex, RandomAccessStream& stream, unsigned __int8* bytes)
{
    this->m_dataSize = this->calcDataSize(this->m_format, this->m_width, this->m_height);
    this->m_texData = bytes ? bytes : static_cast<void*>(new (0x20) char[m_dataSize]);

    stream.read(this->m_texData, this->m_dataSize);
    TexImg::getTileSize(this->m_format, tex->m_tileSizeX, tex->m_tileSizeY);
    tex->dword1C = 1.0 / this->m_width;
    tex->dword20 = 1.0 / this->m_height;
    tex->decodeData(this);
}
