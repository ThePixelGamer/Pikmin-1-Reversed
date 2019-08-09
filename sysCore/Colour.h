// olour.h: interface for the Colour class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OLOUR_H__84878EA3_C165_4F21_B504_2A7E4E5CC245__INCLUDED_)
#define AFX_OLOUR_H__84878EA3_C165_4F21_B504_2A7E4E5CC245__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Colour  
{
public:
	char R;
	char G;
	char B;
	char A;

	Colour(char r, char g, char b, char a);
	Colour () {}

};

#endif // !defined(AFX_OLOUR_H__84878EA3_C165_4F21_B504_2A7E4E5CC245__INCLUDED_)
