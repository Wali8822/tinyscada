


#include "client.h"
#include "rdb.h"

#include <stdlib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>

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

	pClient->recv_buff[nRecvd] = 0;

	printf(pClient->recv_buff);

	elAddFileEvent(el, fd, ELF_WRITE, clientSendFunc, pClient);
}

client *clientCreate(OD_I32 fd) {
	client *pClient = (client*)malloc(sizeof(client));

	if (pClient) {
		pClient->fd = fd;

		elAddFileEvent(SERVER->loop, fd, ELF_READ, clientRecvFunc, pClient);
	}

	return pClient;
}

OD_VOID clientDestoy(client * cli) {
	if (cli) {
		listDel(SERVER->clients, cli);
		elDelFileEvent(SERVER->loop, cli->fd, ELF_RW);
		free(cli);
	}
}
