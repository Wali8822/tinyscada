


#include <stdlib.h>

#include "dict.h"



/* Thomas Wang's 32 bit Mix Function */
unsigned int dictIntHashFunction(unsigned int key)
{
	key += ~(key << 15);
	key ^= (key >> 10);
	key += (key << 3);
	key ^= (key >> 6);
	key += ~(key << 11);
	key ^= (key >> 16);
	return key;
}

dict* dictCreate(size_t size, dictOperation *op, void *privatedata) {
	dict *	d = (dict*)calloc(1, sizeof(dict));
	if (!d){ return NULL; }

	d->dictOp = op;
	d->privatedata = privatedata;

	if (size == 0) {
		size = 1024;
	}

	d->size = size;
	d->table = calloc(size, sizeof(dictEntry*));

	return d;
}

static int _dictKeyIndex(dict *d, void *key) {
	int hash = d->dictOp->hashFunc(key);
	int idx = hash & (d->size - 1);
	dictEntry *he;

	he = d->table[idx];
	while (he) {
		if (d->dictOp->keyComp(d->privatedata, he->key, key) == 0) {
			return -1;
		}

		he = he->next;
	}

	return idx;
}

int dictAdd(dict *d, void *key, void *val) {
	dictEntry	*entry = calloc(1, sizeof(dictEntry));
	int index;

	if ((index = _dictKeyIndex(d, key)) == -1) {
		return 1;
	}

	entry->next = d->table[index];
	d->table[index] = entry;

	entry->key = d->dictOp->keyDup(d->privatedata, key);
	entry->val = d->dictOp->valDup(d->privatedata, val);

	return 1;
}

void *dictGet(dict *d, void *key) {
	int index = (d->dictOp->hashFunc(key) & (d->size - 1));
	dictEntry * he;

	he = d->table[index];
	while (he) {
		if (d->dictOp->keyComp(d->privatedata, he->key, key) == 0) {
			return he->val;
		}
		he = he->next;
	}

	return NULL;
}

void dictDestroy(dict * d) {
	int i;
	dictEntry *tmpEntry, *nextEntry;

	for (i = 0; i < d->size; i++) {
		if ((tmpEntry = d->table[i])){
			while (tmpEntry) {
				nextEntry = tmpEntry->next;

				if (d->dictOp->keyDestructor){
					d->dictOp->keyDestructor(d->privatedata, tmpEntry->key);
				}

				if (d->dictOp->valDestructor){
					d->dictOp->valDestructor(d->privatedata, tmpEntry->val);
				}

				free(tmpEntry);
				tmpEntry = nextEntry;
			}
		}
	}

	free(d->table);
	free(d);
}
