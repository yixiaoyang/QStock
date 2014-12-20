#include "message.h"
#include <cstdio>
#include <cstring>

Message::Message()
{
    reset();
}

Message::Message(const Message &msg)
{
    this->reset();

    this->mhdr = msg.mhdr;
    this->content_len = msg.content_len;
    this->content = new char[this->content_len];
    memcpy(this->content, msg.content, this->content_len);
}

Message::Message(mid_t id, unsigned int from)
{
    reset();
    this->mhdr.mid = id;
    this->mhdr.from = from;
}

Message::Message(mid_t id, unsigned int from,  int flags, int val, mop_t op)
{
    reset();
    this->mhdr.mid = id;
    this->mhdr.from = from;
    this->mhdr.op = op;
    this->mhdr.opt.asInt = val;
    this->mhdr.flags |= flags;
}

Message::Message(mid_t id, unsigned int from, int flags, double dval, mop_t op)
{
    reset();
    this->mhdr.mid = id;
    this->mhdr.from = from;
    this->mhdr.op = op;
    this->mhdr.opt.asDouble = dval;
    this->mhdr.flags |= flags;
}

Message::Message(mid_t id, unsigned int from, int flags, QString str, mop_t op)
{
    reset();
    this->mhdr.mid = id;
    this->mhdr.from = from;
    this->mhdr.op = op;
    strncpy(this->mhdr.opt.asString, str.toStdString().c_str(),MESSAGE_STR_LEN);
    this->mhdr.flags |= flags;
}

Message::Message(const MessageHdr *hdr, const char *data, const unsigned int len)
{
    reset();
    this->mhdr = *hdr;

    this->content_len = len;
    this->content = new char[len];
    memcpy (content,data,len);
}

Message::~Message()
{
    char* mem = (char*)content;
    if(mem != NULL){
        delete mem;
        content = NULL;
    }
}

void Message::reset()
{
    std::memset(&this->mhdr, 0, sizeof(MessageHdr));
    this->mhdr.op = MSG_OP_SET;

    this->content = NULL;
    this->content_len = 0;
}

