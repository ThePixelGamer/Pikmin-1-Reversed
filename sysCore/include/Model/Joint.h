#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef JOINT_H
#define JOINT_H

//
#include <Math/BoundBox.h>
#include <Math/Matrix4f.h>
#include <Math/Vector3f.h>
#include <Model/Mesh.h>
#include <Nodes/CoreNode.h>
#include <Stream/RandomAccessStream.h>
//

class Material;

//< TODO: finish class
class SYSCORE_API Joint : public CoreNode
{
public:
    // 0h - VTBL
    // 10h - CoreNode
    void* m_pad1;           // 14h
    int m_index;            // 18h
    void* m_unk1;           // 1Ch
    int m_flags;           // 20h
    Vector3f m_scale;       // 24h
    Vector3f m_rotation;    // 30h
    Vector3f m_translation; // 3Ch
    Matrix4f m_unk3;        // 48h
    Matrix4f m_unk4;        // 88h

    int m_matPolyCount; // 110h
    class SYSCORE_API MatPoly : public CoreNode
    {
    public:
        // 0h - VTBL
        // 10h - CoreNode
        Material* m_mat; // 14h
        Mesh* m_mesh;    // 18h
        int m_index;     // 1Ch
        int m_dword20;   // 20h
        int m_dword24;   // 24h

        MatPoly() : CoreNode("matpoly") {}
        MatPoly(Material* mat, Mesh* mesh) : CoreNode("matpoly")
        {
            this->m_mat = mat;
            this->m_mesh = mesh;
            this->m_dword24 = 0;
        }
    };

    BoundBox m_bounds;    // CCh
    bool m_useVolume;     // C9h
    bool m_useLightGroup; // CAh

	int dword10C; // 10Ch

    Joint();

    void read(RandomAccessStream&);
    void recShowHierarchy();
    void sectionJoint(AgeServer&);
};

#endif