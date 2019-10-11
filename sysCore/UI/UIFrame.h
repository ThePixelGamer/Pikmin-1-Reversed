#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef UIFRAME_H
#define UIFRAME_H

#include "../Nodes.h"
#include "RectArea.h"

class SYSCORE_API UIFrame : public Node {
public:
	//vtable 0h
	//(CoreNode: 4h-10h)
	//(Node: 14h-1Ch)
	RectArea m_frame; //20h
	RectArea m_zero; //30h
	RectArea m_client; //40h

	UIFrame();

	void calcClientFromFrame(RectArea&);
	void calcFrameFromClient(RectArea&);
	void setClient(RectArea&);
	void setFrame(RectArea&);
};

#endif