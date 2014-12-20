#ifndef IPUBLISHER_H
#define IPUBLISHER_H

#include <string>
#include <list>
#include <vector>
#include <QReadWriteLock>
#include <QObject>

#include "isubscriber.h"
#include "types.h"

class IPublisher : public QObject
{
Q_OBJECT
public:
    virtual int registerFor(ISubscriber *pObserver, int id, QString name);
    virtual int unRegisterFor(ISubscriber *pObserver);
    virtual int post(Message& msg, void* param=NULL);
private:
    virtual int handleMsg(Message& msg, void* param=NULL) = 0;
    virtual void notify(Message &msg);
    virtual void notifyBySignal(Message &msg);
private:
    QReadWriteLock lock;

public:
    IPublisher();
    ~IPublisher();
signals:
    void sendMsg(Message& msg);
};

#endif // IPUBLISHER_H
