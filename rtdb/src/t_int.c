



#include "t_int.h"
#include "sysincs.h"
#include "obj.h"


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

intObj *decIntObj(OD_U8 *pdu, OD_U8 pdu_len) {
	OD_I32	value;

	value = pdu[0] | pdu[1] << 8 | pdu[2] << 16 | pdu[3] << 24;

	return intObjCreate(value);
}
