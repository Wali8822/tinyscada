


#ifndef __OBJ_H__
#define __OBJ_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "glbtypes.h"


#define	R_INT		1
#define	R_FLOAT		2
#define	R_STRING	3


typedef struct _robj{
	OD_U16	type;
	OD_VOID *ptr;
} robj;


robj *createObject(OD_U16 type, OD_VOID *ptr);
OD_VOID deleteObject(robj *obj);

#ifdef __cplusplus
}
#endif

#endif
