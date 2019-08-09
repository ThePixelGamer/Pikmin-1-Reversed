#include "AgeServer.h"

AgeServer::AgeServer() {

}

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
	this->m_unk1 = false;
}