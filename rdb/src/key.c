




#include "key.h"

#include "sysincs.h"


/**
  * 暂定装置地址，组号条目号，都为最大255来进行hash
  */
OD_I32 hash_dev_key(OD_VOID *key){
	dev_key *dk = (dev_key*)key;

	return dk->dev_addr << 16 | dk->grp << 8 | dk->item;
}

OD_VOID *dup_dev_key(OD_VOID *pd, OD_VOID *key) {
	dev_key *old_key = (dev_key*)key;
	dev_key *new_key = (dev_key*)malloc(sizeof(dev_key));

	if (new_key){
		new_key->dev_addr = old_key->dev_addr;
		new_key->grp = old_key->grp;
		new_key->item = old_key->item;
	}

	return new_key;
}

/**
  * 先比较dev_addr, 如果相等，再比较grp, 如果相等，再比较item
  */
OD_I32 cmp_dev_key(OD_VOID *pd, OD_VOID *key1, OD_VOID *key2) {
	dev_key *dk1 = (dev_key*)key1;
	dev_key *dk2 = (dev_key*)key2;

	if (dk1->dev_addr > dk2->dev_addr) {
		return 1;											/*great*/
	} else if(dk1->dev_addr < dk2->dev_addr) {
		return -1;											/*less*/
	}

	/*dev_addr equal*/
	if (dk1->grp > dk2->grp) {
		return 1;
	} else if (dk1->grp < dk2->grp) {
		return -1;
	}

	if (dk1->item > dk2->item) {
		return 1;
	} else if (dk1->item < dk2->item) {
		return -1;
	}

	return 0;
}

OD_VOID destruct_dev_key(OD_VOID *pd, OD_VOID *key) {
	if (key) {
		free(key);
	}
}
