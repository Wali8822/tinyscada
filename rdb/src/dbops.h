

#ifndef __DB_OPS_H__
#define __DB_OPS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "glbtypes.h"
#include "list.h"
#include "key.h"
#include "obj.h"


#define	OP_ADD		((OD_U8)0x01)
#define	OP_DEL		((OD_U8)0x02)
#define	OP_SET		((OD_U8)0x03)
#define	OP_GET		((OD_U8)0x04)


typedef struct dbop {
	DECL_LIST_NODE();

	OD_U8		op;		/*增删改查*/
	dev_key		key;	/*操作的key*/
	robj		*obj;	/*操作的value*/
} dbop;


dbop * dbopCreate(OD_U8 op);
OD_VOID dbopDestroy(dbop *op);

#ifdef __cplusplus
}
#endif

#endif
