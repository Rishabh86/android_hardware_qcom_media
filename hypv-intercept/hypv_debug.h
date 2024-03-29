/*--------------------------------------------------------------------------
Copyright (c) 2017, 2019 The Linux Foundation. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
--------------------------------------------------------------------------*/
#ifndef __HYPV_DEBUG_H__
#define __HYPV_DEBUG_H__


enum {
    HYP_PRIO_ERROR = 0x1,
    HYP_PRIO_HIGH  = 0x2,
    HYP_PRIO_LOW   = 0x4,
    HYP_PRIO_INFO  = 0x8
};

#ifndef __FILENAME__
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#ifdef _LINUX_    // LV
#include <syslog.h>
#include <sys/syscall.h>

#define gettid() syscall(SYS_gettid)
#define getpid() syscall(SYS_getpid)
#define DEBUG_PRINT_CTL(level, fmt, args...)   \
         do {                             \
              if (level <= debug_level)           \
                syslog(level, "[%ld:%ld]:[%s:%s] " fmt " \n", getpid(), \
                gettid(), __FILENAME__, __FUNCTION__, ##args); \
         } while(0)

#define HYP_VIDEO_MSG_INFO( msg_fmt,args...)   DEBUG_PRINT_CTL(LOG_DEBUG, msg_fmt, ##args )
#define HYP_VIDEO_MSG_LOW( msg_fmt,args...)    DEBUG_PRINT_CTL(LOG_INFO, msg_fmt, ##args )
#define HYP_VIDEO_MSG_HIGH( msg_fmt,args...)   DEBUG_PRINT_CTL(LOG_NOTICE, msg_fmt, ##args )
#define HYP_VIDEO_MSG_ERROR( msg_fmt,args...)  DEBUG_PRINT_CTL(LOG_ERR, msg_fmt, ##args )

#elif defined(_ANDROID_)

#ifdef LOG_NDEBUG
#undef LOG_NDEBUG
#endif

#define LOG_NDEBUG 0

#define LOG_HYP_TAG "HYPV_INTERCEPT"
#include "android/log.h"

#define HYP_VIDEO_MSG_INFO(fmt, args...)  ({if(debug_level & HYP_PRIO_INFO) \
                                               __android_log_print(ANDROID_LOG_DEBUG, LOG_HYP_TAG, "[%d:%d]:[%s:%s]" fmt "",  \
                                               getpid(), gettid(), __FILENAME__, __FUNCTION__, ##args);})
#define HYP_VIDEO_MSG_LOW(fmt, args...)   ({if(debug_level & HYP_PRIO_LOW) \
                                               __android_log_print(ANDROID_LOG_VERBOSE, LOG_HYP_TAG, "[%d:%d]:[%s:%s]" fmt "", \
                                               getpid(), gettid(), __FILENAME__, __FUNCTION__, ##args);})
#define HYP_VIDEO_MSG_HIGH(fmt, args...)  ({if(debug_level & HYP_PRIO_HIGH) \
                                               __android_log_print(ANDROID_LOG_INFO, LOG_HYP_TAG, "[%d:%d]:[%s:%s]" fmt "",   \
                                               getpid(), gettid(), __FILENAME__, __FUNCTION__, ##args);})
#define HYP_VIDEO_MSG_ERROR(fmt, args...) ({if(debug_level & HYP_PRIO_ERROR) \
                                               __android_log_print(ANDROID_LOG_ERROR, LOG_HYP_TAG, "[%d:%d]:[%s:%s]" fmt "", \
                                               getpid(), gettid(), __FILENAME__, __FUNCTION__, ##args);})
#endif


#endif
