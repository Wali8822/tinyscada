


#include "rdbclient.h"



struct rdbClient {
	OD_I32		sockfd;
} ;

static OD_RET rcConnect(struct rdbClient *ndp, OD_U32 ip, OD_U16 port) {
	struct sockaddr_in addr;

	ndp->sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (ndp->sockfd < 0) { return OD_FAILURE; }

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = ip;//htonl(ip);
	if (connect(ndp->sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		goto CONNECT_ERR;
	}

	return OD_SUCCESS;

CONNECT_ERR:
	closesocket(ndp->sockfd);

	return OD_FAILURE;
}

static OD_VOID rcClose(struct rdbClient *ndp) {
	closesocket(ndp->sockfd);
}

struct rdbClient * rcInit(OD_U32 ip, OD_U16 port) {
	struct rdbClient *ndp = (struct rdbClient*) calloc(1, sizeof(struct rdbClient));

	if (ndp) {
		if (OD_FAILED(rcConnect(ndp, ip, port))) {
			rcRelease(ndp);
			return NULL;
		}
	}

	return ndp;
}

OD_VOID rcRelease(struct rdbClient *ndp) {
	if (ndp) {
		rcClose(ndp);
		free(ndp);
	}
}

OD_RET rcAddPoint(struct rdbClient *ndp, OD_I32 devAddr, OD_I32 grp, OD_I32 item, OD_I8 type) {
	return OD_SUCCESS;
}

OD_RET rcDelPoint(struct rdbClient *ndp, OD_I32 devAddr, OD_I32 grp, OD_I32 item) {
	return OD_SUCCESS;
}

OD_RET rcSet(struct rdbClient *ndp, OD_I32 devAddr, OD_I32 grp, OD_I32 item, OD_I8 type, OD_VOID *value) {
	return OD_SUCCESS;
}

OD_RET rcGet(struct rdbClient *ndp, OD_I32 devAddr, OD_I32 grp, OD_I32 item, OD_I8 *type, OD_VOID *value) {
	return OD_SUCCESS;
}

