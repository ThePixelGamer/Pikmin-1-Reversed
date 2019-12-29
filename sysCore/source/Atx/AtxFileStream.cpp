#include <Atx/AtxFileStream.h>
#include <System/System.h>

bool AtxFileStream::open(char* name, unsigned __int32 port)
{
    if (this->stream.open("fil", 3))
    {
		// Write the name, and then the port of the server we want to connect to
        this->stream.writeString(name);
        this->stream.writeInt(port);

		// Get the length of the stream
        this->length = this->stream.readInt();
        this->position = 0;

		// If the stream is empty, then we have to close it.
        if (this->length < 0)
        {
            this->stream.close();
            return false;
        }
        else
        {
			// We've got the stream open with bytes! Assign the filepath.
            this->filePath = name;
            return true;
        }
    }
    else
    {
        ATXPRINT("Could not open file service!!\n");
        return false;
    }
}

void AtxFileStream::close()
{
    this->stream.writeInt(103); // probably a define
    this->stream.flush();       // flush file
    this->stream.readInt();
    this->stream.close();       // finally close the stream
}

int AtxFileStream::getLength() { return this->length; }

int AtxFileStream::getPosition() { return this->position; }

int AtxFileStream::getPending() { return this->length - this->position; }

void AtxFileStream::setLength(int _len) { this->length = _len; }

void AtxFileStream::setPosition(int _pos)
{
    this->position = _pos;

    this->stream.writeInt(102);
    this->stream.writeInt(this->position);
}

void AtxFileStream::read(void* buf, int len)
{
    this->stream.writeInt(100);
    this->stream.writeInt(len);  // write length of buffer
    this->stream.read(buf, len); // read (len) length into buffer
    this->position += len;       // move file pointer forward
}

void AtxFileStream::write(void* buf, int len)
{
    this->stream.writeInt(101);
    this->stream.writeInt(len);
    this->stream.write(buf, len);
    this->position += len;
    if (this->position > this->length)
        this->length = this->position; // Move the length of the stream forward if we've gone past what we thought was possible
}