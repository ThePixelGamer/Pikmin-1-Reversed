#include <AgeServer.h>
#include <Model/Joint.h>

void SHAPEBASEPRINT(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char dest[1024];

    if (sysCon)
    {
        if ("shapeBase")
            sysCon->print("%s: ", "shapeBase");
        vsprintf(dest, fmt, args);
        if (strlen(dest))
        {
            sysCon->write(dest, strlen(dest));
        }
    }
}

Joint::Joint()
{
    this->m_flags = 1;
    this->dword10C = 0;
}

void Joint::read(RandomAccessStream& stream)
{
    this->m_index = stream.readInt();
    bool usingIdentifier = static_cast<bool>(stream.readInt());
    this->m_useVolume = (usingIdentifier & 1) != 0;
    this->m_useLightGroup = (usingIdentifier & 0x4000) != 0;

    this->m_bounds.m_minBounds.read(stream);
    this->m_bounds.m_maxBounds.read(stream);
    stream.readFloat();

    this->m_scale.read(stream);
    this->m_rotation.read(stream);
    this->m_translation.read(stream);

    this->m_matPolyCount = stream.readInt();
    for (int i = 0; i < m_matPolyCount; i++)
    {
        MatPoly* mPoly = new MatPoly();
        mPoly->m_index = static_cast<int>(stream.readShort());
        mPoly->m_dword20 = static_cast<int>(stream.readShort());
    }
}

void Joint::recShowHierarchy()
{
    for (Joint* j = this; j; j = static_cast<Joint*>(j->next))
    {
        SHAPEBASEPRINT("got joint %08x\n", j);
        if (j->child)
            j->recShowHierarchy();
    }
}

void Joint::sectionJoint(AgeServer& server)
{
    server.StartGroup("Info");
    server.StartBitGroup("flags", reinterpret_cast<uchar*>(this->m_flags), 120);
    server.NewBit("displays", 1, 0);
    server.EndBitGroup();
    server.EndGroup();
}

void Joint::genAge(AgeServer& server) 
{
	server.StartSection(this->name, true);
    IDelegate1<AgeServer&>* sectionJointRef =
        new Callback1<Joint*, void (Joint::*)(AgeServer&), AgeServer&>(this, &Joint::sectionJoint);
    server.setSectionRefresh(sectionJointRef);
    for (CoreNode* i = this->Child(); i; i = i->Next())
        i->genAge(server);
    server.EndSection();
}
