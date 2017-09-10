


#ifndef __RDB_CLIENT_H__
#define __RDB_CLIENT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "glbtypes.h"
#include "sysincs.h"

struct rdbClient;


struct rdbClient *rcInit(OD_U32 ip, OD_U16 port);
OD_VOID rcRelease(struct rdbClient *ndp);

OD_RET	rcAddPoint(struct rdbClient *ndp, OD_I32 devAddr, OD_I32 grp, OD_I32 item, OD_I8 type);
OD_RET	rcDelPoint(struct rdbClient *ndp, OD_I32 devAddr, OD_I32 grp, OD_I32 item);
OD_RET	rcSet(struct rdbClient *ndp, OD_I32 devAddr, OD_I32 grp, OD_I32 item, OD_I8 type, OD_VOID *value);
OD_RET	rcGet(struct rdbClient *ndp, OD_I32 devAddr, OD_I32 grp, OD_I32 item, OD_I8 *type, OD_VOID *value);

#ifdef __cplusplus
}
#endif

#endif
