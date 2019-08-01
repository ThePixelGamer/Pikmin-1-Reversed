#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef NODES_H
#define NODES_H

#include "Stream/RandomAccessStream.h"

class AgeServer;

class SYSCORE_API ANode {
public:
	virtual void genAge(AgeServer*);
	virtual void genAgeNode(AgeServer*);
	virtual int getAgeNodeType();
};


class SYSCORE_API CoreNode : public ANode {
public:
	//vtable 0h
	char* name; // 4h
	CoreNode* parent; // 8h
	CoreNode* next;	// Ch
	CoreNode* child; // 10h

	CoreNode(char* = "CoreNode");

	virtual void write(RandomAccessStream*) {}
	virtual void read(RandomAccessStream*) {}
	virtual int getAgeNodeType();

	CoreNode* Next();
	void Next(CoreNode*);
	CoreNode* Child();
	void Child(CoreNode*);
	char* Name();
	CoreNode* Parent();

	int getChildCount();

	void initCore(char*);
	void setName(char*);

	void add(CoreNode*);
	void del();

	void load(char*, char*, unsigned __int32); // TODO

	void genWrite(AgeServer*);			 // TODO
	void genRead(AgeServer*);			 // TODO
	virtual void genAgeNode(AgeServer*) {}// TODO
	virtual void genAge(AgeServer*) {}	 // TODO
};

class Graphics;
class Matrix4f;
class SRT;
class VQS;

class SYSCORE_API Node : public CoreNode {
public:
	//vtable 0h
	//(CoreNode: 4h-10h)
	int type; //14h
	int flags; //18h
	int dword1c; //1Ch

	Node(char* = "<Node>");

	virtual void update();
	virtual void draw(Graphics&);
	virtual void render(Graphics&);
	virtual void concat();
	virtual void concat(VQS&);
	virtual void concat(SRT&);
	virtual void concat(Matrix4f&);
	virtual void getModelMatrix();

	bool getFlag(int);
};

static unsigned char foundNode;
static CoreNode* unkNode;

class SYSCORE_API NodeMgr {
	//Var
	int unk;
	CoreNode firstnode;

	// Functions
	NodeMgr();
	~NodeMgr();

	CoreNode* findNode(char*, CoreNode*);
	CoreNode* firstNode();
	void recFindNode(CoreNode*, char*);
};

extern SYSCORE_API NodeMgr * nodeMgr;

#endif 