#include "AtxFileStream.h"
#include "../System/System.h"

void ATXFILESTREAMPRINT(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char dest[1024];

	if(sysCon) {
		if ("Atx")
			sysCon->print("%s: ", "Atx");
		vsprintf(dest, fmt, args);
		if(strlen(dest)) {
			sysCon->write(dest, strlen(dest));
		}
	}
}

bool AtxFileStream::open(char* name, unsigned __int32 port) {
	if (this->stream.open("fil", 3))
	{
		this->stream.writeString(name);
		this->stream.writeInt(port);

		this->length = this->stream.readInt();
		this->position = 0;

		if (this->length < 0)
		{
			this->stream.close();
			return false;
		}
		else
		{
			this->filePath = name;
			return true;
		}
	}
	else {
		ATXFILESTREAMPRINT("Could not open file service!!\n");
		return false;
	}
}

void AtxFileStream::close() {
	this->stream.writeInt(103); // probably a define
	this->stream.flush();	// flush file
	this->stream.readInt();	// unsure of meaning behind reading an int
	this->stream.close();	// finally close the stream
}

int AtxFileStream::getLength() {
	return this->length;
}

int AtxFileStream::getPosition() {
	return this->position;
}

int AtxFileStream::getPending() {
	return this->length - this->position;
}

void AtxFileStream::setLength(int _len) {
	this->length = _len;
}

void AtxFileStream::setPosition(int _pos) {
	this->position = _pos;

	this->stream.writeInt(102);
	this->stream.writeInt(this->position);
}


void AtxFileStream::read(void* buf, int len) {
	this->stream.writeInt(100);
	this->stream.writeInt(len);	// write length of buffer
	this->stream.read(buf, len);// read (len) length into buffer
	this->position += len;		// move file pointer forward
}

void AtxFileStream::write(void* buf, int len) {
	this->stream.writeInt(101);
	this->stream.writeInt(len);
	this->stream.write(buf, len);
	this->position += len;
	if (this->position > this->length)
		this->length = this->position;
}