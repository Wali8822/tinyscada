


#include <stdlib.h>

#include "dict.h"


OD_STATIC OD_I32 _dictKeyIndex(dict *d, OD_VOID *key);

/* Thomas Wang's 32 bit Mix Function */
OD_U32 dictIntHashFunction(OD_U32 key) {
	key += ~(key << 15);
	key ^= (key >> 10);
	key += (key << 3);
	key ^= (key >> 6);
	key += ~(key << 11);
	key ^= (key >> 16);

	return key;
}

OD_U32 dictStringHashFunction(OD_CONST OD_CHAR * str, OD_CONST OD_SIZE len) {
	//TODO
	return 0;
}

dict* dictCreate(OD_SIZE size, dictOperation *op, OD_VOID *priv_data) {
	dict *	d = (dict*)calloc(1, sizeof(dict));
	if (!d){ return NULL; }

	d->dictOp	 = op;
	d->priv_data = priv_data;

	if (size == 0) {
		size = INIT_HASH_SIZE;
	}

	d->size = size;
	d->sizemask = size - 1;
	d->table = calloc(size, sizeof(dictEntry*));
	if (!d->table) {
		goto DICT_CREAT_ERR;
	}

	return d;

DICT_CREAT_ERR:
	if (d) {
		if (d->table) {
			free(d->table);
		}
		free(d);
	}

	return NULL;
}

dictEntry *dictFind(dict *d, OD_VOID *key) {
	OD_I32 hash = d->dictOp->hashFunc(key);
	OD_I32 idx = hash & (d->size - 1);
	dictEntry *he;

	he = d->table[idx];
	while (he) {
		if (d->dictOp->keyComp(d->priv_data, he->key, key) == 0) {
			return he;
		}

		he = he->next;
	}

	return NULL;
}

static OD_I32 _dictKeyIndex(dict *d, OD_VOID *key) {
	OD_I32 hash = d->dictOp->hashFunc(key);
	OD_I32 idx = hash & d->sizemask;
	dictEntry *he;

	he = d->table[idx];
	while (he) {
		if (d->dictOp->keyComp(d->priv_data, he->key, key) == 0) {
			return INVALID_INDEX;
		}

		he = he->next;
	}

	return idx;
}

OD_RET dictAdd(dict *d, OD_VOID *key, OD_VOID *val) {
	dictEntry	*entry;
	OD_I32		index;

	if ((index = _dictKeyIndex(d, key)) == -1) {		/*key 已经存在*/
		return OD_FAILURE;
	}

	entry = calloc(1, sizeof(dictEntry));
	if (!entry){
		return -1;
	}

	entry->next = d->table[index];
	d->table[index] = entry;

	if (d->dictOp->keyDup) {
		entry->key = d->dictOp->keyDup(d->priv_data, key);
	} else {
		entry->key = key;
	}

	if (d->dictOp->valDup) {
		entry->val = d->dictOp->valDup(d->priv_data, val);
	} else {
		entry->val = val;
	}

	return OD_SUCCESS;		/*添加成功*/
}

OD_VOID *dictGet(dict *d, OD_VOID *key) {
	OD_I32 index = (d->dictOp->hashFunc(key) & (d->sizemask));
	dictEntry * he;

	he = d->table[index];
	while (he) {
		if (d->dictOp->keyComp(d->priv_data, he->key, key) == 0) {
			return he->val;
		}
		he = he->next;
	}

	return NULL;
}

OD_RET dictSet(dict *d, OD_VOID *key, OD_VOID *val) {
	dictEntry *entry, auxentry;

	if (OD_SUCCED(dictAdd(d, key, val))) {
		return OD_SUCCESS;
	}

	entry = dictFind(d, key);		/*Add failed, this must be not null*/

	auxentry = *entry;

	if (d->dictOp->valDup) {
		entry->val = d->dictOp->valDup(d->priv_data, val);
	} else {
		entry->val = val;
	}

	if (d->dictOp->valDestructor) {
		d->dictOp->valDestructor(d->priv_data, auxentry.val);
	}

	return OD_SUCCESS;
}

OD_VOID dictDestroy(dict * d) {
	OD_SIZE		i;
	dictEntry *tmpEntry, *nextEntry;

	for (i = 0; i < d->size; i++) {
		if ((tmpEntry = d->table[i])){
			while (tmpEntry) {
				nextEntry = tmpEntry->next;

				if (d->dictOp->keyDestructor){
					d->dictOp->keyDestructor(d->priv_data, tmpEntry->key);
				}

				if (d->dictOp->valDestructor){
					d->dictOp->valDestructor(d->priv_data, tmpEntry->val);
				}

				free(tmpEntry);
				tmpEntry = nextEntry;
			}
		}
	}

	free(d->table);
	free(d);
}
