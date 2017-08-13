


#include "obj.h"

#include <stdlib.h>


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
