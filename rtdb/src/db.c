


#include "rdb.h"

#include <stdlib.h>


rdb *dbCreate(size_t dictSize, dictOperation *op, void *pd) {
	rdb *db = malloc(sizeof(rdb));

	if (db) {
		db->dict_dev = dictCreate(dictSize, op, pd);

		if (!db->dict_dev) {
			free(db);
			return NULL;
		}
	}

	return db;
}

void dbDestroy(rdb *db) {
	if (db) {
		if (db->dict_dev) {
			dictDestroy(db->dict_dev);
		}

		free(db);
	}
}

void dbAdd(rdb *db, robj *key, robj *value) {
	dictAdd(db->dict_dev, key->ptr, value->ptr);
}

void dbSet(rdb *db, robj *key, robj *value) {
	dictSet(db->dict_dev, key->ptr, value->ptr);
}

int dbExist(rdb *db, robj *key) {
	return dictFind(db->dict_dev, key->ptr) != NULL;
}
