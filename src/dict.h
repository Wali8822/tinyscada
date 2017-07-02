

#ifndef __DICT_H__
#define __DICT_H__

typedef struct dictEntry{
	void *key;
	void *val;

	struct dictEntry *next;
} dictEntry;

typedef struct dictOperation {
	int (*hashFunc)(void*);

	void(*keyDestructor)(void*);
	void(*valDestructor)(void*);
} dictOperation;

typedef struct dict {
	dictEntry **	table;
	int	size;

	dictOperation dictOp;
} dict;


dict* dictCreate(int size, int (*hashFunc)(void*),
	void (*keyDestructor)(void*), void (*valDestructor)(void *));
void dictDestroy(dict * d);

#endif
