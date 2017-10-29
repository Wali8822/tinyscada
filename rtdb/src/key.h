



#ifndef __KEY_H__
#define __KEY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "glbtypes.h"

typedef struct dev_key{
	OD_I32 dev_addr;
} dev_key;


OD_I32 hash_dev_key(OD_VOID *key);
OD_VOID *dup_dev_key(OD_VOID *pd, OD_VOID *key);
OD_I32 cmp_dev_key(OD_VOID *pd, OD_VOID *key1, OD_VOID *key2);
OD_VOID destruct_dev_key(OD_VOID *pd, OD_VOID *key);

#ifdef __cplusplus
}
#endif

#endif
