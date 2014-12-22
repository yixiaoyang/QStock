/*
 * (C) Copyright 2013-2015. All rights reserved.
 * Define the base types.
 *
 * @brief   Define the base types.
 * @file    types.h
 * @version 1.0
 * @author  Leon
 * @note
 *      -Create by Leon<hityixiaoyang@gmail.com> on 13Jun14.
 */

#ifndef TYPES_H_
#define TYPES_H_

typedef unsigned char 	int8u_t;
typedef signed char 	int8s_t;

typedef unsigned short	int16u_t;
typedef signed short 	int16s_t;

typedef unsigned long	int32u_t;
typedef signed long     int32s_t;

/** Another Style */
typedef unsigned char 	u8_t;
typedef signed char 	s8_t;

typedef unsigned short	u16_t;
typedef signed short 	s16_t;

typedef unsigned long	u32_t;
typedef signed long     s32_t;

/*another typedef*/
typedef unsigned char 	u8;
typedef signed char 	s8;

typedef unsigned short	u16;
typedef signed short 	s16;

typedef unsigned long	u32;
typedef signed long     s32;

#define PUBLIC
#define LOCAL   static

/* Log Level*/
typedef enum LOG_DBG_LEVEL_STRUCT{
    LOG_DBG_LEVEL_FATAL=1,
    LOG_DBG_LEVEL_ERROR,
    LOG_DBG_LEVEL_WARN,
    LOG_DBG_LEVEL_INFO,
    LOG_DBG_LEVEL_DEBUG,
    LOG_DBG_LEVEL_TRACE,
    LOG_DBG_LEVEL_ALL,
    LOG_DBG_LEVEL_OFF,
    LOG_DBG_LEVEL_MAX
}LOG_DBG_LEVEL;


enum {
    STATUS_NULL = -10,
    STATUS_ERR_REMOTE_BUSY = -9,
    STATUS_ERR_EXISTED = -8,
    STATUS_ERR_DISCONNECTED = -7,
    STATUS_ERR_PACKET = -6,
    STATUS_ERR_NOT_DEVICE = -5,
    STATUS_ERR_INITIALIZED = -4,
    STATUS_ERR_NOT_EXISTED = -3,
    STATUS_ERR_NOMEM = -2,

    STATUS_FAILED = -1,
    STATUS_OK = 0,

    STATUS_CONNECTED = 1,
    STATUS_DISCONNECTED = STATUS_FAILED
};
typedef int STATUS;

/* Debug print */
#define SET(where, flags)       (where) |= (flags)
#define CLR(where, flags)       (where) &= ~(flags)
#define ISSET(where, flags)     ((where) & (flags))
#define ISNOTSET(where,flags)   (!(where & flags))
#define DBG_FATEL   (0)
#define DBG_ERROR   (1)
#define DBG_WARN    (2)
#define DBG_INFO    (3)
#define DBG_DEBUG   (4)
#define DBG_FLOW    (5)
#define DBG_MAX     (6)
#define debug_print(level, fmt, args...) \
    do {    \
        if (g_debugLevel() >= level ){ \
            printf("[%-10s %16s] %05d: " fmt "\n", #level, __FUNCTION__ , __LINE__, ##args);\
        }\
    }while (0)
PUBLIC int g_debugLevel();


#define SIZEOF_ARRAY(x) sizeof(x)/sizeof(x[0])

enum{
    DAYS_OF_MONTH=30,
    DAYS_OF_3MONTH=DAYS_OF_MONTH*3,
    DAYS_OF_6MONTH=DAYS_OF_MONTH*6,
    DAYS_OF_YEAR=365,
    DAYS_OF_2YEAR=DAYS_OF_YEAR*2,
    DAYS_OF_3YEAR=DAYS_OF_YEAR*3
};

enum{
    WAVE_VIEW_KLINE,
    WAVE_VIEW_TIME_INDEX,
    WAVE_VIEW_MAX
};

#endif /* TYPES_H_ */
