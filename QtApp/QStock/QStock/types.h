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

typedef unsigned long       DWORD;
typedef unsigned long       LONG;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef int                 INT;
typedef unsigned int        UINT;


/* Log Level*/
typedef enum LOG_DEBUG_LEVEL_STRUCT{
    LOG_DEBUG_LEVEL_FATAL=1,
    LOG_DEBUG_LEVEL_ERROR,
    LOG_DEBUG_LEVEL_WARN,
    LOG_DEBUG_LEVEL_INFO,
    LOG_DEBUG_LEVEL_DEBUG,
    LOG_DEBUG_LEVEL_TRACE,
    LOG_DEBUG_LEVEL_ALL,
    LOG_DEBUG_LEVEL_OFF,
    LOG_DEBUG_LEVEL_MAX
}LOG_DEBUG_LEVEL;


enum {
    STATUS_ERR_REMOTE_BUSY,
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



#define SET(where, flags)       (where) |= (flags)
#define CLR(where, flags)       (where) &= ~(flags)
#define ISSET(where, flags)     ((where) & (flags))
#define ISNOTSET(where,flags)   (!(where & flags))

#define SIZEOF_ARRAY(x) sizeof(x)/sizeof(x[0])

#endif /* TYPES_H_ */
