

#ifndef __DICT_H__
#define __DICT_H__

#include "glbtypes.h"


#define	INIT_HASH_SIZE		(1024)
#define	INVALID_INDEX		(-1)

#define	ERR_KEY_EXIST		(0x7001)
#define	ERR_MEMORY			(0x7002)


typedef struct dictEntry{
	OD_VOID *key;
	OD_VOID *val;

	struct dictEntry *next;
} dictEntry;

typedef struct dictOperation {
	OD_I32(*hashFunc)(OD_VOID *key);
	OD_I32(*keyComp)(OD_VOID *priv_data, OD_VOID *key1, OD_VOID *key2);
	OD_VOID* (*keyDup)(OD_VOID *priv_data, OD_VOID *key);
	OD_VOID* (*valDup)(OD_VOID *priv_data, OD_VOID *val);
	OD_VOID(*keyDestructor)(OD_VOID *priv_data, OD_VOID *key);
	OD_VOID(*valDestructor)(OD_VOID *priv_data, OD_VOID *val);
} dictOperation;

typedef struct dict {
	dictEntry		**table;
	OD_SIZE			size;
	OD_SIZE			sizemask;

	dictOperation	*dictOp;

	OD_I32			*priv_data;
} dict;

OD_U32 dictIntHashFunction(OD_U32 key);
OD_U32 dictStringHashFunction(OD_CONST OD_CHAR * str, OD_CONST OD_SIZE len);

/**
  * size must be power of 2
  */
dict* dictCreate(OD_SIZE size, dictOperation *op, OD_VOID *priv_data);

dictEntry *dictFind(dict *d, OD_VOID *key);

OD_RET dictAdd(dict *d, OD_VOID *key, OD_VOID *val);
OD_VOID *dictGet(dict *d, OD_VOID *key);
OD_RET dictSet(dict *d, OD_VOID *key, OD_VOID *val);

OD_VOID dictDestroy(dict * d);

#endif
