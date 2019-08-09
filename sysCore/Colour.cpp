// olour.cpp: implementation of the Colour class.
//
//////////////////////////////////////////////////////////////////////

#include "Colour.h"

Colour::Colour(char r, char g, char b, char a) {
	this->set(r, g, b, a);
}


void Colour::add(Colour& toAdd) {
	unsigned short R = this->R + toAdd.R; 
}


void Colour::genAge(AgeServer& server, char* unk) {
	//server.New
}


void Colour::lerp(Colour&, float) {}


void Colour::lerpTo(Colour&, float, Colour&) {}


void Colour::read(Stream&) {}


void Colour::set(unsigned __int8 r, unsigned __int8 g, unsigned __int8 b, unsigned __int8 a) {}
