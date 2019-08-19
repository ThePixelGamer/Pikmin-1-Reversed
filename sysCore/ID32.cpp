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

ID32::ID32(unsigned __int32 _id) {
    this->setID(_id);
}

void ID32::ageChangeID() {
    this->updateID();
}

void ID32::genAge(AgeServer& server, char* name) {
    server.setOnChange(new Callback<ID32*, void (ID32::*)()>(this, &ID32::ageChangeID));
    server.NewEditor(name, this->sId, 5);
    server.setOnChange(static_cast<IDelegate*>(0));
}

bool ID32::match(unsigned __int32 _id, char exception) {
    char* p_id = reinterpret_cast<char*>(&_id);
    char* m_id = reinterpret_cast<char*>(&this->id);

    for(int i = 0; i < 4; i++) {
        if(p_id[i] != exception && p_id[i] != m_id[i])
            return 0;
    }
    return 1;
}

void ID32::print() {
    char str[5];
    str[0] = (this->id & 0xFF000000) >> 24;
    str[1] = (this->id & 0xFF0000) >> 16;
    str[2] = (this->id & 0xFF00) >> 8;
    str[3] = this->id & 0xFF;
    str[4] = 0;
    ::print("id (%x) is %s\n", this->id, str);
}

void ID32::read(RandomAccessStream& stream) {
    char* m_id = reinterpret_cast<char*>(&this->id);
    m_id[0] = stream.readByte();
    m_id[1] = stream.readByte();
    m_id[2] = stream.readByte();
    m_id[3] = stream.readByte();

    char* m_id2 = reinterpret_cast<char*>(&this->id);
    for(int i = 0; i < 4; i++) {
        this->sId[i] = m_id2[3-i];
    }
    this->sId[4] = 0;
}

void ID32::setID(unsigned __int32 _id) {
    this->id = _id;
    this->updateString();
}

void ID32::sprint(char* str) {
    str[0] = (this->id & 0xFF000000) >> 24;
    str[1] = (this->id & 0xFF0000) >> 16;
    str[2] = (this->id & 0xFF00) >> 8;
    str[3] = this->id & 0xFF;
    str[4] = 0;
}

void ID32::updateID() {
    char* m_id = reinterpret_cast<char*>(&this->id);

    for(int i = 0; i < 4; i++)
        m_id[i] = this->sId[3 - i];
}

void ID32::updateString() {
    char* m_id = reinterpret_cast<char*>(&this->id);

    for(int i = 0; i < 4; i++)
        this->sId[i] = m_id[3 - i];
    sId[4] = 0;
}

void ID32::write(RandomAccessStream& stream) {
    char* m_id = reinterpret_cast<char*>(&this->id);
    
    stream.writeByte(m_id[0]);
    stream.writeByte(m_id[1]);
    stream.writeByte(m_id[2]);
    stream.writeByte(m_id[3]);
}

void ID32::operator=(unsigned __int32 _id) {
    this->setID(_id);
}

bool ID32::operator!=(unsigned __int32 _id) {
    return (this->id != _id);
}

bool ID32::operator==(unsigned __int32 _id) {
    return (this->id == _id);
}