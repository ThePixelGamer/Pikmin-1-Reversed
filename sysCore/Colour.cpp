// olour.cpp: implementation of the Colour class.
//
//////////////////////////////////////////////////////////////////////

#include "Colour.h"

Colour::Colour(unsigned __int8 r, unsigned __int8 g, unsigned __int8 b, unsigned __int8 a) {
	this->set(r, g, b, a);
}


void Colour::add(Colour& toAdd) {
	unsigned char r = this->R + toAdd.R;
	if (r > 255) {
		r = -1;
	}
	else {
		if (r < 0)
			r = 0;
	}

	unsigned char g = this->G + toAdd.G;
	if (g > 255) {
		g = -1;
	}
	else {
		if (g < 0)
			g = 0;
	}

	unsigned char b = this->B + toAdd.B;
	if (b > 255) {
		b = -1;
	}
	else {
		if (b < 0)
			b = 0;
	}

	unsigned char a = this->A + toAdd.A;
	if (a > 255) {
		this->set(r, g, b, 0xFF);
	}
	else {
		if (a < 0)
			a = 0;
		this->set(r, g, b, a);
	}
}


void Colour::genAge(AgeServer& server, char* unk) {
	server.NewEditor(unk, *this);
}


void Colour::lerp(Colour& l, float t) {
	this->R = ((l.R - this->R) * t + this->R);
	this->G = ((l.G - this->G) * t + this->G);
	this->B = ((l.B - this->B) * t + this->B);
	this->A = ((l.A - this->A) * t + this->A);
}


void Colour::lerpTo(Colour& col1, float t, Colour& col2) {
	col2.R = ((col1.R - this->R) * t + this->R);
	col2.G = ((col1.G - this->G) * t + this->G);
	col2.B = ((col1.B - this->B) * t + this->B);
	col2.A = ((col1.A - this->A) * t + this->A);
}


void Colour::read(Stream & strm) {
	this->R = strm.readByte();
	this->G = strm.readByte();
	this->B = strm.readByte();
	this->A = strm.readByte();
}


void Colour::set(unsigned __int8 r, unsigned __int8 g, unsigned __int8 b, unsigned __int8 a) {
	this->R = r;
	this->G = g;
	this->B = b;
	this->A = a;
}

void Colour::write(Stream & strm) {
	strm.writeByte(this->R);
	strm.writeByte(this->G);
	strm.writeByte(this->B);
	strm.writeByte(this->A);
}
