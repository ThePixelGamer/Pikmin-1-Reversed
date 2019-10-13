#include <Stream/CmdStream.h>

char* CmdStream::statbuff;

CmdStream::CmdStream(Stream* strm) { this->init(strm); }

void CmdStream::init(Stream* stream)
{
    this->buffer = 0;
    if (!CmdStream::statbuff)
    {
        CmdStream::statbuff = new char[0x8000]; // or = new char[0x8000]
    }
    memset(CmdStream::statbuff, 0, 0x8000);
    this->strm = stream;
    this->pending = this->strm->getPending();
    this->currentChar = 0;
    this->unkVar2 = 0;
    this->unkVar3 = 0;
    this->buffer = CmdStream::statbuff;
    this->fillBuffer(true);
}

void CmdStream::fillBuffer(bool canFill)
{
    if (canFill || this->currentChar - this->unkVar3 >= 0x4000)
    {
        if (this->unkVar2)
        {
            memcpy(this->buffer + this->unkVar3, this->buffer + this->unkVar3 + 0x4000, 0x4000);
            this->buffer -= 0x4000;
            this->unkVar3 += 0x4000;
        }

        int result = this->unkVar2 != 0 ? 0x4000 : 0x8000;

        if (this->pending - this->unkVar2 < result)
            result = this->pending - this->unkVar2;

        this->strm->read(this->buffer + this->unkVar2, result);
        this->unkVar2 += result;
    }
}

bool CmdStream::LineIsComment()
{
    return this->buffer[this->currentChar] == '#'
           // checks for //
           || this->buffer[this->currentChar] == '/' && this->buffer[this->currentChar + 1] == '/';
}

void CmdStream::copyToToken(int length)
{
    for (int i = 0; i < length; i++)
    {
        char currCharOfToken = this->buffer[this->currentChar + i];
        if (currCharOfToken == '\t')
            currCharOfToken = ' ';

        this->currentToken[i] = currCharOfToken;
    }
    // null terminate token
    this->currentToken[i] = 0;
}

bool CmdStream::endOfCmds()
{
    this->fillBuffer(false);
    while (this->currentChar < this->pending && this->whiteSpace(this->buffer[this->currentChar]))
    {
        this->currentChar++;
    }

    if (this->currentChar < this->pending)
        return this->buffer[this->currentChar] == -1;
    else
        return 1;
}

bool CmdStream::whiteSpace(char toCheck)
{
    return !toCheck || toCheck == '\n' || toCheck == '\r' || toCheck == '\t' || toCheck == ' ' || toCheck == ',';
}

bool CmdStream::endOfSection()
{
    this->fillBuffer(false);
    return this->buffer[this->currentChar] == '}';
}

char* CmdStream::getToken(bool hasComments)
{
    this->fillBuffer(false);

    if (hasComments)
    {
        while (this->LineIsComment())
            this->skipLine();
    }

    int currChar = this->currentChar;
    bool tokenInParenthesis = 0;

    if (this->buffer[currChar] == '"' || this->buffer[currChar] == '\'')
    {
        tokenInParenthesis = true;
        ++currChar;
        ++this->currentChar;
    }

    while (true)
    {
        // why is it not a bool wtf
        const signed int shouldBreak = tokenInParenthesis
                                           // if true
                                           ? this->buffer[currChar] == '"' || this->buffer[currChar] == '\'' ? 0 : 1
                                           // if false
                                           : this->whiteSpace(this->buffer[currChar]) == 0;

        if (!shouldBreak)
            break;

        ++currChar;
    }

    this->copyToToken(currChar - this->currentChar);

    // Null terminate token
    if (tokenInParenthesis)
        this->currentToken[currChar++ - this->currentChar] = 0;

    while (currChar < this->pending && this->whiteSpace(this->buffer[currChar]))
        ++currChar;

    this->currentChar = currChar;
    return this->currentToken;
}

char* CmdStream::skipLine()
{
    this->fillBuffer(false);
    int i = this->currentChar;
    while (i < this->pending && this->buffer[i] != '\n' && this->buffer[i] != '\r')
    {
        i++;
    }

    this->copyToToken(i - this->currentChar);

    while (this->buffer[i] == '\n' || this->buffer[i] == '\r')
        ++i;

    this->currentChar = i;

    return this->currentToken;
}

char CmdStream::nextChar() { return this->buffer[this->currentChar]; }

bool CmdStream::isToken(char* Str)
{
    if (!strlen(this->currentToken))
        return false;

    if (strlen(this->currentToken) != strlen(Str))
        return false;

    for (int i = 0; i < strlen(this->currentToken); ++i)
    {
        if (Str[i] != this->currentToken[i])
            return false;
    }

    return true;
}