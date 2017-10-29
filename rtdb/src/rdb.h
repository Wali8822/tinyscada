



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

/**
 * 
 */
typedef struct device {
	OD_I32	dev_addr;

	dict	*dict_data;						/*hold all datas*/
} device;

/**
 *
 */
typedef struct _rdb{
	dict	*dict_dev;						/*hold all devices*/
} rdb;

typedef struct _server{
	OD_I32	ip_fd[SERVER_FD_MAX];			/*server ÎÄ¼þÃèÊö·û*/
	OD_I32	ipfd_count;

	elEventLoop	*loop;

	rdb		*db;
	list	*clients;
} server;

/**
 *	Device operations
 */
device *devCreate(OD_I32 devAddr);
OD_RET devAddPoint(device *pDev, OD_U16 grp, OD_U16 itm, robj *val);
robj *devGetPoint(device *pDev, OD_U16 grp, OD_U16 itm);
OD_VOID devSetPoint(device *pDev, OD_U16 grp, OD_U16 itm, robj *val);
OD_VOID *devDestroy(device *dev);


/**
 * DB operations
 */
rdb *dbCreate(OD_SIZE dictSize, dictOperation *op, OD_VOID *pd);
OD_VOID dbDestroy(rdb *db);
OD_VOID dbAdd(rdb *db, robj *key, robj *value);
OD_VOID dbSet(rdb *db, robj *key, robj *value);
OD_RET dbExist(rdb *db, robj *key);


/**
 * Server operations
 */
OD_VOID initServer(config *cfg);

#define	SERVER	getServer()
server	*getServer();

#ifdef __cplusplus
}
#endif

#endif
