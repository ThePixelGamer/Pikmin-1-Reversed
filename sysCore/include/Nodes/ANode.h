#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef ANODE_H
#define ANODE_H

//
//	Add any headers here!
//

class SYSCORE_API ANode
{
public:
    virtual void genAge(class AgeServer&);
    virtual void genAgeNode(class AgeServer&);
    virtual int getAgeNodeType();
};

#endif
