


#include "client.h"
#include "rdb.h"
#include "sysincs.h"
#include "protocol.h"
#include "dbops.h"
#include "list.h"


static OD_VOID proc_op(client *cli, dbop *pOp) {
	switch (pOp->op) {
	case OP_ADD:
		dbAdd(cli->db, createObject(R_KEY, &pOp->key), pOp->obj);
	}
}

static OD_VOID proc_ops(client *cli) {
	dbop		*pOp;
	list_iter	*iter;
	
	iter = list_begin(cli->ops_pending);
	while (iter && (pOp = (dbop*)iter_next(iter))) {
		proc_op(cli, pOp);
	}

	list_end(iter);
}

static void clientSendFunc(struct elEventLoop * el, OD_I32 fd, OD_U16 mask, OD_VOID *data) {
	OD_CHAR *reply = "Hello World, too\n";
	send(fd, reply, strlen(reply), 0);

	elDelFileEvent(el, fd, ELF_WRITE);
}

static OD_VOID clientRecvFunc(struct elEventLoop * el, OD_I32 fd, OD_U16 mask, OD_VOID *data) {
	client *pClient = (client*)data;
	OD_I32 nRecvd;

	nRecvd = recv(fd, pClient->recv_buff, sizeof(pClient->recv_buff), 0);

	if (nRecvd < 0){
		clientDestoy(pClient);
		return;
	}

	op_dec(pClient, pClient->recv_buff, nRecvd);
	proc_ops(pClient);
}

client *clientCreate(OD_I32 fd) {
	client *pClient = (client*)malloc(sizeof(client));

	if (pClient) {
		pClient->fd = fd;
		pClient->ops_pending = listCreate();
		pClient->db = SERVER->db;

		elAddFileEvent(SERVER->loop, fd, ELF_READ, clientRecvFunc, pClient);
	}

	return pClient;
}

OD_VOID clientDestoy(client * cli) {
	if (cli) {
		listDel(SERVER->clients, (node*)(cli));
		
		elDelFileEvent(SERVER->loop, cli->fd, ELF_RW);
		free(cli);
	}
}
