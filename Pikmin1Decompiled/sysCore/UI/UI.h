#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef UI_H
#define UI_H

#include "../Nodes.h"

class SYSCORE_API RectArea {
public:
	int x1; //0h
	int y1; //4h
	int x2; //8h
	int y2; //Ch

	RectArea() {
		this->x1 = 0;
		this->y1 = 0;
		this->x2 = 0;
		this->y2 = 0;
	}

	RectArea(int x_1, int y_1, int x_2, int y_2) {
		this->x1 = x_1;
		this->y1 = y_1;
		this->x2 = x_2;
		this->y2 = y_2;	
	}

	int height() { return this->y2 - this->y1; }
	int width()  { return this->x2 - this->x1; }
	bool pointInside (int x, int y) {
		return x > this->x1 && x < this->x2
		    && y > this->y1 && y < this->y2;
	}

	void set(int x_1, int y_1, int x_2, int y_2) {
		this->x1 = x_1;
		this->y1 = y_1;
		this->x2 = x_2;
		this->y2 = y_2;	
	}
};

class SYSCORE_API UIFrame : public Node {
	//vtable 0h
	//(CoreNode: 4h-10h)
	//(Node: 14h-1Ch)
	RectArea m_frame; //20h
	RectArea m_unk2; //30h
	RectArea m_client; //40h

	UIFrame() : Node("UIFrame") { }

	void calcClientFromFrame(RectArea& client) {
		client.x1 = 0;
		client.y1 = 0;
		client.x2 = this->m_frame.width() - (-this->m_unk2.x1 + this->m_unk2.x2);
		client.y2 = this->m_frame.height() - (-this->m_unk2.y1 + this->m_unk2.y2);
	}

	void calcFrameFromClient(RectArea& frame) {
		frame.x1 += this->m_unk2.x1;
		frame.y1 += this->m_unk2.y1;
		frame.x2 = (frame.x1 + this->m_client.x2) + (-this->m_unk2.x1 + this->m_unk2.x2);
		frame.y2 = (frame.y1 + this->m_client.y2) + (-this->m_unk2.y1 + this->m_unk2.y2);
	}

	void setClient(RectArea& client) {
		this->m_client = client;
		calcFrameFromClient(this->m_frame);
	}

	void setFrame(RectArea& frame) {
		this->m_frame = frame;
		calcClientFromFrame(this->m_client);
	}
};

#endif