#include "ID32.h"

#include "sysCore.h"
#include "IDelegate.h"
#include "Stream/RandomAccessStream.h"
#include "AgeServer.h"

void print(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char dest[1024];

	if(sysCon) {
		if ("id32")
			sysCon->print("%s: ", "id32");
		vsprintf(dest, fmt, args);
		if(strlen(dest)) {
			sysCon->write(dest, strlen(dest));
		}
	}
}

ID32::ID32() {
    this->setID(0x6E6F6E65);
}

ID32::ID32(unsigned __int32 a2) {
    this->setID(a2);
}

void ID32::ageChangeID() {
    this->updateID();
}

void ID32::genAge(AgeServer& a2, char* a3) {
    IDelegate* test = new Callback<ID32*, void (ID32::*)()>(this, ageChangeID);
    a2.setOnChange(test);
}

void ID32::match(unsigned __int32, char) {
    
}

void ID32::print() {
    char a2[5];
    a2[0] = (this->id & 0xFF000000) >> 24;
    a2[1] = (this->id & 0xFF0000) >> 16;
    a2[2] = (this->id & 0xFF00) >> 8;
    a2[3] = this->id & 0xFF;
    a2[4] = 0;
    ::print("id (%x) is %s\n", this->id, a2);
}

void ID32::read(RandomAccessStream&) {
    
}

void ID32::setID(unsigned __int32 a2) {
    this->id = a2;
    this->updateString();
}

void ID32::sprint(char* a2) {
    a2[0] = (this->id & 0xFF000000) >> 24;
    a2[1] = (this->id & 0xFF0000) >> 16;
    a2[2] = (this->id & 0xFF00) >> 8;
    a2[3] = this->id & 0xFF;
    a2[4] = 0;
}

void ID32::updateID() {
    ID32* probAutoGen = this;

    for(int i = 0; i < 4; i++)
        probAutoGen->cId[i] = this->sId[3 - i];
}

void ID32::updateString() {
    ID32* probAutoGen = this;

    for(int i = 0; i < 4; i++)
        this->sId[i] = probAutoGen->cId[3 - i];
    sId[4] = 0;
}

void ID32::write(RandomAccessStream& a2) {
    ID32* probAutoGen = this;
    
    a2.writeByte(probAutoGen->cId[0]);
    a2.writeByte(probAutoGen->cId[1]);
    a2.writeByte(probAutoGen->cId[2]);
    a2.writeByte(probAutoGen->cId[3]);
}