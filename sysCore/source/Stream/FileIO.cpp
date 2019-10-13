#include <Stream/FileIO.h>

fileIO::fileIO(FILE* fpointer, char* cwd)
{
    this->m_fStream = fpointer;
    this->filePath = cwd;
    this->m_fPtrPosition = 0;

    int offset = this->getPosition();
    fseek(this->m_fStream, 0, SEEK_END);
    this->m_fileSize = ftell(this->m_fStream);
    fseek(this->m_fStream, offset, SEEK_SET);
}

int fileIO::getPosition() { return ftell(this->m_fStream); }

void fileIO::read(void* buf, int count)
{
    fread(buf, 1, count, this->m_fStream);
    this->m_fPtrPosition += count;
}

void fileIO::write(void* buf, int count) { fwrite(buf, 1, count, this->m_fStream); }

int fileIO::getPending() { return this->m_fileSize - this->m_fPtrPosition; }

int fileIO::getAvailable() { return this->m_fileSize; }

void fileIO::close()
{
    fflush(this->m_fStream);
    fclose(this->m_fStream);
}

void fileIO::setPosition(int offset) { fseek(this->m_fStream, offset, SEEK_SET); }
