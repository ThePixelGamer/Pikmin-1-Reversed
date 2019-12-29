#include <Graphics/Graphics.h>

Matrix4f Graphics::ident;

void PRINTGRAPHICS(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char dest[1024];

    if (sysCon)
    {
        if ("Graphics")
            sysCon->print("%s: ", "Graphics");
        vsprintf(dest, fmt, args);
        if (strlen(dest))
        {
            sysCon->write(dest, strlen(dest));
        }
    }
}

void GRAPHICSHALT(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char dest[1024];
    vsprintf(dest, fmt, args);
    System::halt("c:\\development\\dolphinpiki\\syscommon\\graphics.cpp", 17, dest);
    // file, line, error
}

Graphics::Graphics()
{
    PRINTGRAPHICS("dgxgraphics constructor\n");
    this->m_unk1 = 0;
    for (int i = 0; i < 4096; ++i)
    {
		// precalculated sine & cosine table at a precision of 4096 units per full circle.
        sinTable[i] = sin(i / 4096.0 * TAU);
        cosTable[i] = cos(i / 4096.0 * TAU);
    }
    ident.makeIdentity();
    this->m_unkColour2.set(0, 0, 0x30, 0xFF);
    this->m_unk2 = 1;
}

void Graphics::perspPrintf(Font*, Vector3f&, int, int, char*, ...) {}

void Graphics::addLight(Light* light)
{
    // light->initCore("");
    gsys->m_lightCount++;
    // this->m_lights.add(light);
}

void Graphics::cacheShape(BaseShape*, ShapeDynMaterials*) {}

int Graphics::calcBoxLighting(BoundBox&) { return 0; }

int Graphics::calcLighting(float) { return 0; }

int Graphics::calcSphereLighting(Vector3f&, float) { return 0; }

void Graphics::drawCircle(Vector3f&, float, Matrix4f&) {}

void Graphics::drawCylinder(Vector3f&, Vector3f&, float, Matrix4f&) {}

void Graphics::drawSphere(Vector3f&, float, Matrix4f&) {}

void Graphics::flushCachedShapes() {}

void Graphics::genAge(AgeServer&) {}

Matrix4f* Graphics::getMatrices(int) { return nullptr; }

void Graphics::resetCacheBuffer() {}

void Graphics::resetLights() {}

void Graphics::resetMatrixBuffer() { this->m_matrixBuffer = nullptr; }

void Graphics::initRender(int, int)
{
    // this->m_light.initCore("");
    this->resetMatrixBuffer();
    this->resetCacheBuffer();
}