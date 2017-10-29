

#ifndef __RDB_CLI_H__
#define __RDB_CLI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "global.h"
#include "glbtypes.h"



struct rdb_client;



RDB_CLIENT_API struct rdb_client *cliInitialize();
	
RDB_CLIENT_API OD_VOID	cliDestroy(struct rdb_client *ndp);



#ifdef __cplusplus
}
#endif

#endif
