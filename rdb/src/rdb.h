



#ifndef __RDB_H__
#define __RDB_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "glbtypes.h"
#include "dict.h"
#include "obj.h"
#include "config.h"
#include "evtloop.h"
#include "list.h"


#define	SERVER_FD_MAX		(16)


typedef struct _rdb{
	dict	*dict;			/*存储实际的数据*/
} rdb;

typedef struct _server{
	OD_I32	ip_fd[SERVER_FD_MAX];			/*server 文件描述符*/
	OD_I32	ipfd_count;

	elEventLoop	*loop;

	rdb		*db;
	list	*clients;
} server;


rdb *dbCreate(OD_SIZE dictSize, dictOperation *op, OD_VOID *pd);
OD_VOID dbDestroy(rdb *db);
OD_VOID dbAdd(rdb *db, robj *key, robj *value);
OD_VOID dbSet(rdb *db, robj *key, robj *value);
OD_RET dbExist(rdb *db, robj *key);


OD_VOID initServer(config *cfg);

#define	SERVER	getServer()
server	*getServer();

#ifdef __cplusplus
}
#endif

#endif
