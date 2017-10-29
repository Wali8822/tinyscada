

#ifndef __SYSINCS_H__
#define __SYSINCS_H__


#ifdef __cplusplus
extern "C" {
#endif


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>

#include <assert.h>

/**
  * @desc Win32 system
  */
#if defined(_WIN32)

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <share.h>

#endif


/**
 * @desc linux system
 */
#if defined(linux)

/* _LINUX系统相关头文件 */
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <sys/time.h>
#include <sys/timerfd.h>
#include <pthread.h>
#include <sys/stat.h>

#endif

#ifdef __cplusplus
}
#endif

#endif
