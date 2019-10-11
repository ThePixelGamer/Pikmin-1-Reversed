#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef NODEMGR_H
#define NODEMGR_H

//
#include "Node.h"
//

static unsigned char foundNode;
static CoreNode* unkNode;

class SYSCORE_API NodeMgr {
public:
	//0h - vtbl
	int unk; //4h
	CoreNode firstnode; //32h

	// Functions
	NodeMgr();
	~NodeMgr();

	CoreNode* findNode(char*, CoreNode*);
	CoreNode* firstNode();
	void recFindNode(CoreNode*, char*);
	void Del(Node*);
};

extern SYSCORE_API NodeMgr* nodeMgr;


#endif