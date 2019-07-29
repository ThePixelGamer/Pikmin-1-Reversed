// UI.h: interface for the UI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UI_H__D0971E89_2F25_4AAD_8CC9_0BF76D8E23A7__INCLUDED_)
#define AFX_UI_H__D0971E89_2F25_4AAD_8CC9_0BF76D8E23A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#include "Nodes.h"

class SYSCORE_API RectArea  
{
public:
	int topWallLength;
	int bottomWallLength;
	int leftWallLength;
	int rightWallLength;

	RectArea() {
		this->topWallLength    = 0;
		this->bottomWallLength = 0;
		this->leftWallLength   = 0;
		this->rightWallLength  = 0;
	}

	RectArea( int rwl, int bwl, int lwl, int twl ) {
		this->topWallLength    = twl;
		this->bottomWallLength = bwl;
		this->leftWallLength   = lwl;
		this->rightWallLength  = rwl;	
	}

	int height() { return this->topWallLength - this->bottomWallLength; }
	int width () { return this->leftWallLength - this->rightWallLength; }
	bool pointInside (int width, int height) {
		return width  > this->rightWallLength
		    && width  < this->leftWallLength
		    && height > this->bottomWallLength
		    && height < this->topWallLength;
	}

	void set( int rwl, int bwl, int lwl, int twl )
	{
		this->rightWallLength  = rwl;
		this->bottomWallLength = bwl;
		this->leftWallLength   = lwl;
		this->topWallLength    = twl;
	}

};

class SYSCORE_API UIFrame
	: public Node
{
	UIFrame() : Node("UIFrame") {};
};
#endif // !defined(AFX_UI_H__D0971E89_2F25_4AAD_8CC9_0BF76D8E23A7__INCLUDED_)
