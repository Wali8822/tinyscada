



#include "sysincs.h"
#include "protocol.h"
#include "dbops.h"
#include "t_int.h"


static OD_RET op_add_dec(client *cli, OD_U8 *pdu, OD_I32 pdu_len);
static OD_RET op_del_dec(client *cli, OD_U8 *pdu, OD_I32 pdu_len);
static OD_RET op_set_dec(client *cli, OD_U8 *pdu, OD_I32 pdu_len);
static OD_RET op_get_dec(client *cli, OD_U8 *pdu, OD_I32 pdu_len);


dbop * dbopCreate(OD_U8 op) {
	dbop *pDbOp = (dbop*)malloc(sizeof(dbop));

	if (pDbOp) {
		pDbOp->op = op;
	}

	return pDbOp;
}

OD_VOID dbopDestroy(dbop *op) {
	if (op) {
		free(op);
	}
}

OD_RET op_dec(client *cli, OD_U8 *pdu, OD_I32 pdu_len) {
	if (pdu_len <= 0) { return OD_FAILURE; }

	switch (pdu[0]) {
	case OP_ADD:
		return op_add_dec(cli, pdu + 1, pdu_len - 1);
	case OP_DEL:
		return op_del_dec(cli, pdu + 1, pdu_len - 1);
	case OP_SET:
		return op_set_dec(cli, pdu + 1, pdu_len - 1);
	case OP_GET:
		return op_get_dec(cli, pdu + 1, pdu_len - 1);
	}

	return OD_FAILURE;
}

static OD_RET op_add_dec(client *cli, OD_U8 *pdu, OD_I32 pdu_len) {
	dbop *pOp = dbopCreate(OP_ADD);

	pOp->key.dev_addr = pdu[0] | pdu[1] << 8 | pdu[2] << 16 | pdu[3] << 24;
	pOp->key.grp = pdu[4] | pdu[5] << 8 | pdu[6] << 16 | pdu[7] << 24;
	pOp->key.item = pdu[8] | pdu[9] << 8 | pdu[10] << 16 | pdu[11] << 24;

	switch (pdu[12]) {
	case R_INT:
		pOp->obj = createObject(R_INT, decIntObj(&pdu[13], pdu_len - 13));
		break;
	}

	listAddHead(cli->ops_pending, (node*)pOp);

	return OD_SUCCESS;
}

static OD_RET op_del_dec(client *cli, OD_U8 *pdu, OD_I32 pdu_len) {
	return OD_SUCCESS;
}

static OD_RET op_set_dec(client *cli, OD_U8 *pdu, OD_I32 pdu_len) {
	return OD_SUCCESS;
}

static OD_RET op_get_dec(client *cli, OD_U8 *pdu, OD_I32 pdu_len) {
	return OD_SUCCESS;
}
