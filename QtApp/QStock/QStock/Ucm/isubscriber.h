#ifndef ISUBSCRIBER_H
#define ISUBSCRIBER_H

#include <string>

#include "message.h"
#include "types.h"

#include <QObject>


enum {
    ISUBSCRIBER_ID_ANONYMOUS = 0,

    ISUBSCRIBER_ID_QSTOCK_MAIN_WINDOWS,
    ISUBSCRIBER_ID_QSTOCK_WAVE_WIDGET,

    ISUBSCRIBER_ID_START
};


#define DEF_HANDLER_FUNC_NAME(mid)      on_##mid(Message& )
#define DEF_HANDLER_FUNC_NAME2(mid)     on_##mid(msg)
#define DEF_HANDLER_FUNC_NAME3(mid)     on_##mid

#define DEF_HANDLER_FUNC(mid)      virtual inline \
                                   STATUS \
                                   DEF_HANDLER_FUNC_NAME(mid){\
                                        return STATUS_OK;\
                                   }

class ISubscriber
{
public:
    ~ISubscriber();
protected:
    unsigned int id;
    QString name;
public:
    ISubscriber();
    bool operator ==(unsigned int id);
    unsigned int getId() const;
    void setId(unsigned int value);
    QString getName() const;
    void setName(const QString &value);

    virtual QObject* getQobject() = 0;
protected:
    //handlers
    DEF_HANDLER_FUNC(STOCK_DATA_CHGED)
    DEF_HANDLER_FUNC(STOCK_DATA_SAVE)

protected slots:
    virtual int handleMsg(Message& msg) = 0;
    virtual void loadUserConfig();
};

#endif // ISUBSCRIBER_H
