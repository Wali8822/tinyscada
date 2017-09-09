


#include "rdb.h"

#include <stdlib.h>


rdb *dbCreate(size_t dictSize, dictOperation *op, void *pd) {
	rdb *db = malloc(sizeof(rdb));

	if (db) {
		db->dict = dictCreate(dictSize, op, pd);
	}

	return db;
}

void dbDestroy(rdb *db) {
	if (db) {
		if (db->dict) {
			dictDestroy(db->dict);
		}

		free(db);
	}
}

void dbAdd(rdb *db, robj *key, robj *value) {
	dictAdd(db->dict, key->ptr, value->ptr);
}

void dbSet(rdb *db, robj *key, robj *value) {
	dictSet(db->dict, key->ptr, value->ptr);
}

int dbExist(rdb *db, robj *key) {
	return dictFind(db->dict, key->ptr) != NULL;
}
