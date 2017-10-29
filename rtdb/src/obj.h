


#ifndef __OBJ_H__
#define __OBJ_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "glbtypes.h"


#define	R_KEY		((OD_U8)0x08)
#define	R_INT		((OD_U8)0x01)
#define	R_FLOAT		((OD_U8)0x02)
#define	R_STRING	((OD_U8)0x03)


typedef struct _robj{
	OD_U16	type;
	OD_VOID *ptr;
} robj;


OD_VOID * dup_obj(OD_VOID *priv_data, OD_VOID *val);
OD_VOID destruct_obj(OD_VOID *priv_data, OD_VOID *val);

robj *createIntObject(OD_I32 value);

robj *createObject(OD_U16 type, OD_VOID *ptr);
OD_VOID deleteObject(robj *obj);

#ifdef __cplusplus
}
#endif

#endif
