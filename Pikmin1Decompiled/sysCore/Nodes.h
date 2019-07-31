#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef NODES_H
#define NODES_H

class SYSCORE_API ANode {
public:
	ANode() { }

	virtual void genAge(struct AgeServer *);
	virtual void genAgeNode(struct AgeServer *);
	virtual int getAgeNodeType();
};

#include "Stream/RandomAccessStream.h"

class SYSCORE_API CoreNode : public ANode {
public:
	//CoreNode Size: 14h 
	//vtable 0h
	char* name; // 4h
	CoreNode* parent; // 8h
	CoreNode* next;	// Ch
	CoreNode* child; // 10h

	CoreNode(char * name = "CoreNode")
	{
		this->initCore(name);
	}

	virtual void write (RandomAccessStream *) {}
	virtual void read  (RandomAccessStream *) {}
	virtual int getAgeNodeType() { return 2; }

	CoreNode * Next   ()				{ return this->next;  }
	void	   Next   (CoreNode * set)  { this->next = set;   }
	CoreNode * Child  ()				{ return this->child; }
	void	   Child  (CoreNode * set)	{ this->child = set;  }
	char	 * Name   ()				{ return this->name;  }
	CoreNode * Parent ()				{ return this->parent;}

	int getChildCount();

	void initCore(char * name);
	void setName(char * name);

	void add(CoreNode *);
	void del();

	void load(char *, char *, unsigned __int32); // TODO

	void genWrite(struct AgeServer *);			 // TODO
	void genRead (struct AgeServer *);			 // TODO
	virtual void genAgeNode(struct AgeServer *){}// TODO
	virtual void genAge(struct AgeServer *){}	 // TODO
};

class SYSCORE_API Node : public CoreNode {
public:
	//vtable 0h
	//(CoreNode: 4h-10h)
	int type; //14h
	int flags; //18h
	int dword1c; //1Ch

	//Functions
	Node(char * name = "<Node>") : CoreNode(name) { /*this->init(name)*/ }

};

static unsigned char foundNode;
static CoreNode * unkNode;

class SYSCORE_API NodeMgr {
	//Var
	int unk;
	CoreNode firstnode;

	// Functions
	NodeMgr() { unk = 0; }
	~NodeMgr() {}

	CoreNode * findNode(char *, CoreNode *);
	CoreNode * firstNode() { return &this->firstnode; }
	void recFindNode(CoreNode *, char *);
};

#endif 