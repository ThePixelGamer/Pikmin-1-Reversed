#include <AgeServer.h>
#include <Atx/AtxFileStream.h>
#include <IDelegate.h>
#include <Nodes/CoreNode.h>
#include <Stream/BufferedStream.h>
#include <sysCore.h>

void NODEPRINT(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char dest[1024];

    if (sysCon)
    {
        if ("Node")
            sysCon->print("%s: ", "Node");
        vsprintf(dest, fmt, args);
        if (strlen(dest))
        {
            sysCon->write(dest, strlen(dest));
        }
    }
}

struct String128 : public String
{
    char* name;

    String128() : String() { this->init(name, 128); }
};

CoreNode::CoreNode(char* name) { this->initCore(name); }

void CoreNode::genAge(AgeServer& server)
{
    server.StartSection("Node", true);
    server.StartGroup("Node");

    IDelegate1<AgeServer&>* loadButton =
        new Callback1<CoreNode*, void (CoreNode::*)(AgeServer&), AgeServer&>(this, &CoreNode::genRead);
    server.NewButton("Load", loadButton, 120);

    IDelegate1<AgeServer&>* saveButton =
        new Callback1<CoreNode*, void (CoreNode::*)(AgeServer&), AgeServer&>(this, &CoreNode::genWrite);
    server.NewButton("Save", saveButton, 120);

    server.EndGroup();
    server.EndSection();
}

void CoreNode::genAgeNode(AgeServer& server)
{
    char* name = this->getName() ? this->getName() : "NULL";
    server.NewNode(name, this);

    for (CoreNode* i = this->child; i; i = i->next)
        i->genAge(server);

    server.EndNode();
}

void CoreNode::genRead(AgeServer& server)
{
    String128 filename;
    if (server.getOpenFilename(filename, "All files (*.*)|*.*"))
    {
        AtxFileStream stream;
        NODEPRINT("Trying to open file '%s'\n", filename.m_string);
        if (stream.open(filename.m_string, true))
        {
            NODEPRINT("opened file ...\n");
            BufferedStream bFstream(static_cast<RandomAccessStream*>(&stream), 0x8000);
            NODEPRINT("reading file ...\n");
            this->read(bFstream);
            NODEPRINT("closing file ...\n");
            bFstream.close();
            server.RefreshNode();
        }
        else
        {
            NODEPRINT("cant open file '%s'\n", filename.m_string);
        }
    }
}

void CoreNode::genWrite(AgeServer& server)
{
    String128 filename;
    if (server.getOpenFilename(filename, "All files (*.*)|*.*"))
    {
        AtxFileStream stream;
        if (stream.open(filename.m_string, true))
        {
            NODEPRINT("saving as '%s'\n", filename.m_string);
            this->write(stream);
            stream.close();
            NODEPRINT("closed file\n");
        }
        else
        {
            NODEPRINT("cant save file '%s'\n", filename.m_string);
        }
    }
}

int CoreNode::getAgeNodeType() { return 2; }

CoreNode* CoreNode::Next() { return this->next; }

void CoreNode::Next(CoreNode* set) { this->next = set; }

CoreNode* CoreNode::Child() { return this->child; }

void CoreNode::Child(CoreNode* set) { this->child = set; }

char* CoreNode::Name() { return this->name; }

CoreNode* CoreNode::Parent() { return this->parent; }

void CoreNode::initCore(char* nme)
{
    this->parent = 0;
    this->next = 0;
    this->child = 0;
    this->setName(nme);
}

void CoreNode::setName(char* nme) { this->name = nme; }

void CoreNode::add(CoreNode* toAdd)
{
    CoreNode* temp = this->child;

    if (temp)
    {
        while (temp->next)
            temp = temp->next;
        temp->next = toAdd;
    }
    else
    {
        this->child = toAdd;
    }

    toAdd->parent = this;
}

void CoreNode::del()
{
    if (this->parent)
    {
        CoreNode* parChild = this->parent->child;
        CoreNode* oldChild = 0;
        while (parChild)
        {
            if (parChild == this)
            {
                if (oldChild)
                    oldChild->next = parChild->next;
                else
                    this->parent->child = parChild->next;

                this->next = nullptr;
                this->parent = nullptr;

                return;
            }
            oldChild = parChild;
            parChild = parChild->next;
        }
    }
}

int CoreNode::getChildCount()
{
    int count;
    for (CoreNode* temp = this->child; temp; temp = temp->next)
        count++;
    return count;
}

char* CoreNode::getName() { return this->name; }
