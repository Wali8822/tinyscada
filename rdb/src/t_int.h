


#ifndef __T_INT_H__
#define __T_INT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "glbtypes.h"



typedef struct _intObj{
	OD_I32	value;
} intObj;


intObj	*intObjCreate(OD_I32 value);
OD_VOID intObjDestroy(intObj *iObj);


#ifdef __cplusplus
}
#endif

#endif
