


#include "rdb-cli.h"
#include "sysincs.h"


struct rdb_client {
	OD_I32	sock_fd;
};


struct rdb_client *cliInitialize() {
	struct rdb_client *pCli = NULL;

	pCli = malloc(sizeof(struct rdb_client));

	return pCli;
}

OD_VOID	cliDestroy(struct rdb_client *ndp) {
	if (ndp) free(ndp);
}
