



#include "t_int.h"
#include "sysincs.h"

intObj	*intObjCreate(OD_I32 value) {
	intObj *iObj = malloc(sizeof(intObj));

	if (iObj) {
		iObj->value = value;
	}

	return iObj;
}

OD_VOID intObjDestroy(intObj *iObj) {
	if (iObj) {
		free(iObj);
	}
}
