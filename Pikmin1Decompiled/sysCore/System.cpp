#include "System.h"

System::System() : StdSystem() {

}

System::System(const System& sys) : StdSystem(sys) {

}

System::~System() {

}

RandomAccssStream* System::openFile(char*, bool, bool) {

}

void System::sndPlaySe(unsigned int) {

}

void System::beginRender() {

}

void System::buildModeList() {

}

UIWindow* System::createDebugStream(UIWindow*) {

}

void System::createFile(char*, bool) {

}

RandomAccessStream* System::doneRender() {

}

BaseApp* System::firstApp() {

}

void System::genAge(AgeServer*) {

}

AtxRouter* System::getAtxRouter() {

}

int	System::getFrameCount() {

}

float System::getFrameRate() {

}

float System::getFrameTime() {

}

float System::getTime() {

}

void System::halt(char*, int, char*) {

}

void System::hardReset() {

}

int System::run(BaseApp*) {

}

void System::searchFiles(char*, char*, IDelegate2<char*, unsigned int>*, bool) {

}

void System::setAtxRouter(int) {

}

int System::setStreamType(int) {

}

bool System::setVideoMode(bool, int, int, int) {

}

void System::sleep(float) {

}

void System::updateSysClock() {

}

void System::waitRetrace() {

}

System System::operator=(const System&) {

}