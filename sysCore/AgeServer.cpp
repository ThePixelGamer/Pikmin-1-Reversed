#include "AgeServer.h" 
#include "sysCore.h"

void AGEPRINT(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char dest[1024];

	if(sysCon) {
		if ("Age")
			sysCon->print("%s: ", "Age");
		vsprintf(dest, fmt, args);
		if(strlen(dest)) {
			sysCon->write(dest, strlen(dest));
		}
	}
}

AgeServer::AgeServer() {

}

//END

void AgeServer::Done() {
	this->writeInt(200);
}

void AgeServer::EndBitGroup() {
	this->writeInt(0);
}

void AgeServer::EndGroup() {
	this->writeInt(303);
}

void AgeServer::EndNode() {
	this->writeInt(200);
}

void AgeServer::EndOptionBox() {
	this->writeInt(0);
}

void AgeServer::EndSection() {
	this->writeInt(301);
	this->m_unkOpen = false;
}

//NEW

void AgeServer::NewBit(char* str, unsigned __int32 a2, unsigned __int32 a3) {
	this->writeInt(1);
	this->writeString(str);
	this->writeInt(a2);
	this->writeInt(a3);
}

void AgeServer::NewEditor(char* unk, Colour& col) {
	this->writeInt(102);
	this->writeString(unk);
	this->writeProp(COLOUR, (void*)& col);
}

void AgeServer::NewEditor(char* unk, char* unk2, int unk3) {
	this->writeInt(102);
	this->writeString(unk);
	this->writeProp(UNK8, unk2);
	this->writeInt(unk3 - 1);
}

void AgeServer::NewEditor(char* unk, char* unk2, int unk3, int unk4, int unk5) {
	this->writeInt(102);
	this->writeString(unk);
	this->writeProp(UNK8, unk2);
	this->writeInt(unk3);
	this->writeInt(unk4);
	this->writeInt(unk5);
}

void AgeServer::setOnChange(IDelegate* a2) {
	
}

void AgeServer::setOnChange(IDelegate1<AgeServer&>*) {
	
}

//WRITE

int AgeServer::writeProp(PROP_TYPE type, void* buffer) {
	this->writeInt((int)type);
	this->writeInt((int)buffer);
	return this->writePropValue(type, buffer);
}

int AgeServer::writePropValue(PROP_TYPE type, void* buffer) {
	return 0;
}

bool AgeServer::Open() {
	AGEPRINT("!!!!! Opening Age server\n");
	if (this->open("age", 3)) {
		this->m_unkOpen = false;
		return true;
	}
	else {
		AGEPRINT("cant open AgeServer\n");
		return false;
	}
}