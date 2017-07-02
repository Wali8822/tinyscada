


#include <stdlib.h>

#include "dict.h"



dict* dictCreate(int size, int(*hashFunc)(void*),
	void(*keyDestructor)(void*), void(*valDestructor)(void *)) {
	dict *	d = (dict*)calloc(1, sizeof(dict));
	if (!d){ return NULL; }

	d->size = size;
	d->table = calloc(size, sizeof(dictEntry*));
	d->dictOp.hashFunc = hashFunc ? hashFunc : NULL;
	d->dictOp.keyDestructor = keyDestructor;
	d->dictOp.valDestructor = valDestructor;

	return d;
}

void dictDestroy(dict * d) {
	int i;
	dictEntry *tmpEntry, *nextEntry;

	for (i = 0; i < d->size; i++) {
		if ((tmpEntry = d->table[i])){
			while (tmpEntry) {
				nextEntry = tmpEntry->next;

				if (d->dictOp.keyDestructor){
					d->dictOp.keyDestructor(tmpEntry->key);
				}

				if (d->dictOp.valDestructor){
					d->dictOp.valDestructor(tmpEntry->val);
				}

				free(tmpEntry);
				tmpEntry = nextEntry;
			}
		}
	}

	free(d->table);
	free(d);
}
