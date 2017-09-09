


#include "rdb.h"
#include "net.h"
#include "key.h"
#include "client.h"
#include "sysincs.h"


static server	_only_server;

static dictOperation devKeyOp = {
	hash_dev_key,
	cmp_dev_key,
	dup_dev_key,
	dup_obj,
	destruct_dev_key,
	destruct_obj
};

OD_VOID serverAccept(struct elEventLoop * el, OD_I32 fd, OD_U16 mask, OD_VOID *data) {
	OD_I32 clifd;
	client	*c;

	clifd = accept(fd, NULL, NULL);
	c = clientCreate(clifd);

	if (!c) {
		closesocket(clifd);
	} else {
		listAddHead(SERVER->clients, (node*)c);
	}
}

OD_VOID initServer(config *cfg) {
	OD_I32	i;

	SERVER->loop = elCreateEventLoop(1024);
	
	listenToPort(cfg->c_port, SERVER->ip_fd, &(SERVER->ipfd_count));
	for (i = 0; i < SERVER->ipfd_count; ++i) {
		elAddFileEvent(SERVER->loop, SERVER->ip_fd[i], ELF_READ, serverAccept, NULL);
	}

	SERVER->db = dbCreate(4096, &devKeyOp, NULL);
	SERVER->clients = listCreate();
}

server	*getServer() {
	return &_only_server;
}
