#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef JOINT_H
#define JOINT_H

//
#include <Nodes/CoreNode.h>
//

class SYSCORE_API Joint : public CoreNode
{
public:
    Joint();
};

#endif