


#ifndef __SERVER_H__
#define __SERVER_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "glbtypes.h"


OD_RET acceptConnection(OD_I32 servfd);

OD_RET listenToPort(OD_U16 port, OD_I32 *fds, OD_I32 *count);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
