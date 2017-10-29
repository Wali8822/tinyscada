

#include "rdb.h"
#include "sysincs.h"


#define INIT_DEV_POINT_COUNT		(512)

typedef struct pointKey {
	OD_U16 grp;
	OD_U16 itm;
} pointKey;

static OD_I32 pointKeyHash(OD_VOID *key) {
	pointKey *pKey = key;

	if (!pKey) { return 0; }

	return (OD_I32)(pKey->grp << 16 | pKey->itm);
}

static OD_I32 pointKeyComp(OD_VOID *priv_data, OD_VOID *key1, OD_VOID *key2) {
	pointKey *pKey1 = (pointKey*)key1;
	pointKey *pKey2 = (pointKey*)key2;

	UNUSED(priv_data);

	if (pKey1->grp > pKey2->grp) {
		return 1;
	} else if (pKey1->grp < pKey2->grp) {
		return -1;
	}

	if (pKey1->itm > pKey2->itm)  {
		return 1;
	} else if (pKey1->itm < pKey2->itm) {
		return -1;
	}

	return 0;
}

static OD_VOID* pointKeyDup(OD_VOID *priv_data, OD_VOID *key) {
	UNUSED(priv_data);

	if (key) {
		pointKey *pKey = (pointKey*)key;
		pointKey *pKeyCloned = malloc(sizeof(pointKey));

		if (pKeyCloned) {
			pKeyCloned->grp = pKey->grp;
			pKeyCloned->itm = pKey->itm;
			return pKeyCloned;
		}
	}

	return NULL;
}

//static OD_VOID* (*valDup)(OD_VOID *priv_data, OD_VOID *val);
static OD_VOID pointKeyDestructor(OD_VOID *priv_data, OD_VOID *key) {
	UNUSED(priv_data);

	if (key)
		free(key);
}

//static OD_VOID(*valDestructor)(OD_VOID *priv_data, OD_VOID *val);

static dictOperation pointDictOp = {
	pointKeyHash,
	pointKeyComp,
	pointKeyDup,
	NULL,
	pointKeyDestructor,
	NULL
};

device *devCreate(OD_I32 devAddr) {
	device *pDevice = NULL;

	pDevice = malloc(sizeof(device));
	if (!pDevice) { return OD_FAILURE; }

	pDevice->dev_addr = devAddr;
	pDevice->dict_data = dictCreate(INIT_DEV_POINT_COUNT, &pointDictOp, NULL);

	if (!pDevice->dict_data) { goto ERR_DEV_CREATE; }

	return pDevice;

ERR_DEV_CREATE:
	if (pDevice) free(pDevice);

	return NULL;
}

OD_RET devAddPoint(device *pDev, OD_U16 grp, OD_U16 itm, robj *val) {
	pointKey key = {grp, itm};

	dictAdd(pDev->dict_data, &key, val);
}

robj *devGetPoint(device *pDev, OD_U16 grp, OD_U16 itm) {
	pointKey key = {grp, itm};

	return dictGet(pDev->dict_data, &key);
}

OD_VOID devSetPoint(device *pDev, OD_U16 grp, OD_U16 itm, robj *val) {
	pointKey key = { grp, itm };

	return dictSet(pDev->dict_data, &key, val);
}

OD_VOID *devDestroy(device *dev) {
	dictDestroy(dev->dict_data);

	free(dev);
}

