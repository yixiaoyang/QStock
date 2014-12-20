#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QMetaType>
#include "types.h"

enum MessageID{
    MID_VOID = -1,
    STOCK_DATA_CHGED,
    STOCK_DATA_SAVE,
    MID_MAX
};
typedef int mid_t;


#define MSG_FLAGS_NOTIFY_ALL            (1<<0)
#define MSG_FLAGS_NOTIFY_NONE           (1<<1)
#define MSG_FLAGS_NOTIFY_SELF           (1<<2)
#define MSG_FLAGS_NOTIFY_NOTSELF        (1<<3)

enum  MSG_OP_ID{
    MSG_OP_SET = 0,
    MSG_OP_GET,
    MSG_OP_ADD,
    MSG_OP_DEL,
    MSG_OP_LOAD,
    MSG_OP_CLEAR,
    MSG_OP_ORDER,
    MSG_OP_MAX
};
typedef unsigned int mop_t;

enum  MSG_TYPE_ID{
    MSG_TYPE_LOCAL_MSG = 0,
    MSG_TYPE_REMOTE_NORMAL_MSG,
    MSG_TYPE_REMOTE_PANEL_MSG,
    MSG_TYPE_MAX
};
typedef int mtype_t;
#if 0
enum{
    MSG_ARRAY_OPT_INDEX0,
    MSG_ARRAY_OPT_INDEX1,
    MSG_ARRAY_OPT_INDEX2,
    MSG_ARRAY_OPT_INDEX3,

    MSG_ARRAY_OPT_INDEX4,
    MSG_ARRAY_OPT_INDEX5,
    MSG_ARRAY_OPT_INDEX6,
    MSG_ARRAY_OPT_INDEX7,

    MSG_ARRAY_OPT_INDEX8,
    MSG_ARRAY_OPT_INDEX9,
    MSG_ARRAY_OPT_INDEXA,
    MSG_ARRAY_OPT_INDEXB,
    MSG_ARRAY_OPT_INDEXC,
    MSG_ARRAY_OPT_INDEXD,
    MSG_ARRAY_OPT_INDEXE,
    MSG_ARRAY_OPT_INDEXF,

    MSG_ARRAY_OPT_SIZE_MAX_CHARS,
    MSG_ARRAY_OPT_SIZE_MAX_INT = MSG_ARRAY_OPT_INDEX4,
    MSG_ARRAY_OPT_SIZE_MAX_SHORT = MSG_ARRAY_OPT_INDEX8
};
#endif

#pragma pack(1)
#define MESSAGE_STR_LEN     (32)
typedef struct MessageHdrStruct{
    mid_t mid;
    mop_t op;
    unsigned int flags;
    unsigned int type;
    unsigned int from;
    /* TODO: use template */
    union _opt{
        int asInt;
        double asDouble;
        bool asBool;
        char asString[MESSAGE_STR_LEN];
    }opt;
#if 0
    union{
        /* 4*int=16 bytes */
        int asInts[MSG_ARRAY_OPT_SIZE_MAX_INT];
        short asShorts[MSG_ARRAY_OPT_SIZE_MAX_SHORT];
        char asChars[MSG_ARRAY_OPT_SIZE_MAX_CHARS];
        double asDoubles[MSG_ARRAY_OPT_SIZE_MAX_INT];
        bool asBools[MSG_ARRAY_OPT_SIZE_MAX_INT];
    }arrayOpt;
#endif
    int retCode;

    char param[0];
}MessageHdr;
#pragma pack()

class Message
{
public:
    MessageHdr mhdr;
    void *content;
    int content_len;
public:
    Message();
    Message(const Message& msg);
    Message(mid_t id, unsigned int from);
    Message(mid_t id, unsigned int from, int flags,int val, mop_t op=MSG_OP_SET);
    Message(mid_t id, unsigned int from, int flags,double val, mop_t op=MSG_OP_SET);
    Message(mid_t id, unsigned int from, int flags,QString str, mop_t op=MSG_OP_SET);
    Message(const MessageHdr* hdr,const char *data, const unsigned int len);
    ~Message();
private:
    void reset();
};


Q_DECLARE_METATYPE(Message)


#endif // MESSAGE_H
