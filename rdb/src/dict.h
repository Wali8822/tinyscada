

#ifndef __DICT_H__
#define __DICT_H__

typedef struct dictEntry{
	void *key;
	void *val;

	struct dictEntry *next;
} dictEntry;

typedef struct dictOperation {
	int (*hashFunc)(void*);
	int(*keyComp)(void *privatedata, void *key1, void *key2);
	void* (*keyDup)(void *privatedata, void *key);
	void* (*valDup)(void *privatedata, void *key);
	void(*keyDestructor)(void *privatedata, void *key);
	void(*valDestructor)(void *privatedata, void *val);
} dictOperation;

typedef struct dict {
	dictEntry **	table;
	int	size;

	dictOperation *dictOp;

	void *privatedata;
} dict;

unsigned int dictIntHashFunction(unsigned int);
unsigned int dictStringHashFunction(const char * str, const size_t len);

dict* dictCreate(size_t size, dictOperation *op, void *privatedata);

int dictAdd(dict *d, void *key, void *val);
void *dictGet(dict *d, void *key);

void dictDestroy(dict * d);

#endif
