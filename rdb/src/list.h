


#ifndef __LIST_H__
#define __LIST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "glbtypes.h"


typedef struct _node {
	struct _node *prev;
	struct _node *next;
} node;

#define DECL_LIST_NODE()	node	_n

typedef struct _list {
	node	*head;
	node	*tail;
	OD_SIZE	_count;
} list;


list *listCreate();
OD_VOID listAddHead(list *l, node *n);
OD_VOID listAddTail(list *l, node *n);
OD_VOID listDel(list *l, node *n);

#ifdef __cplusplus
}
#endif

#endif
