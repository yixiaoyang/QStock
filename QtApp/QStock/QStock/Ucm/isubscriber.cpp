#include "isubscriber.h"

bool ISubscriber::operator ==(unsigned int id)
{
    return this->id == id;
}


unsigned int ISubscriber::getId() const
{
    return id;
}

void ISubscriber::setId(unsigned int value)
{
    id = value;
}

#define HANDLE_MSG_CASE(mid)    case mid: \
                                    ret = DEF_HANDLER_FUNC_NAME2(mid); \
                                    break

int ISubscriber::handleMsg(Message &msg)
{
    int ret = STATUS_OK;

    /* irnore message not for me */
    if(ISSET(msg.mhdr.flags,MSG_FLAGS_NOTIFY_SELF) &&
            msg.mhdr.from != this->id){
        return ret;
    }
    /* ignore message from me */
    if(ISSET(msg.mhdr.flags,MSG_FLAGS_NOTIFY_NOTSELF) &&
            msg.mhdr.from == this->id){
        return ret;
    }

    switch(msg.mhdr.mid){
    HANDLE_MSG_CASE(STOCK_DATA_CHGED);
    HANDLE_MSG_CASE(STOCK_DATA_SAVE);
    default:
        break;
    }

    return ret;
}


ISubscriber::ISubscriber()
{
    id = 0;
}
ISubscriber::~ISubscriber()
{

}

QString ISubscriber::getName() const
{
    return name;
}

void ISubscriber::setName(const QString &value)
{
    name = value;
}

void ISubscriber::loadUserConfig()
{

}
