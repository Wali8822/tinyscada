


#ifndef __CLIENT_H__
#define __CLIENT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "list.h"
#include "glbtypes.h"



typedef struct _client{
	DECL_LIST_NODE();

	OD_I32	fd;
	OD_U8	recv_buff[4096];
} client;


client *clientCreate(OD_I32 fd);
OD_VOID clientDestoy(client * cli);


#ifdef __cplusplus
}
#endif

#endif
