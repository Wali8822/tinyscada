


#include "obj.h"
#include "t_int.h"

#include <stdlib.h>

OD_VOID * dup_obj(OD_VOID *priv_data, OD_VOID *val) {
	return val;
}

OD_VOID destruct_obj(OD_VOID *priv_data, OD_VOID *val) {

}

robj *createIntObject(OD_I32 value) {
	intObj	* iObj = intObjCreate(value);

	return createObject(R_INT, iObj);
}

robj *createObject(OD_U16 type, OD_VOID *ptr) {
	robj * pObj = (robj*)malloc(sizeof(robj));

	if (pObj) {
		pObj->type = type;
		pObj->ptr = ptr;
	}

	return pObj;
}

OD_VOID deleteObject(robj *obj) {
	if (obj) {
		free(obj);
	}
}
