#include "ipublisher.h"
#include "types.h"

static int idMax = ISUBSCRIBER_ID_START;

int IPublisher::registerFor(ISubscriber *pObserver,int id, QString name)
{
    pObserver->setId (id);
    pObserver->setName(name);
    QObject::connect(this, SIGNAL(sendMsg(Message&)), pObserver->getQobject (), SLOT(handleMsg(Message&)));
    debug_print(DBG_DEBUG,"ISubscriber %02d registered",id);
    return STATUS_OK;
}

int IPublisher::unRegisterFor(ISubscriber *pObserver)
{
    QObject::disconnect(this, SIGNAL(sendMsg(Message&)), pObserver->getQobject (), SLOT(handleMsg(Message&)));
    return STATUS_OK;
}

int IPublisher::post(Message &msg, void* param)
{
    int ret = handleMsg (msg,param);
    if(ret != STATUS_OK){
        return ret;
    }

    notify(msg);

    if(!param)
        delete (char*)param;

    return ret;
}

void IPublisher::notify(Message &msg)
{
    if(msg.mhdr.mid < MID_MAX){
        if(ISNOTSET(msg.mhdr.flags,MSG_FLAGS_NOTIFY_NONE) &&
           (msg.mhdr.op != MSG_OP_GET)){
            notifyBySignal(msg);
        }
    }
}

void IPublisher::notifyBySignal(Message &msg)
{
    emit sendMsg (msg);
}

IPublisher::IPublisher() :
    QObject()
{
    idMax = 0;
}

IPublisher::~IPublisher()
{

}
