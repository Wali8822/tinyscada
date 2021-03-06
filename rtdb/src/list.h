


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

	OD_VOID(*free_func)(OD_VOID *ptr);
} list;

typedef struct list_iter {
	node	*iter;
} list_iter;


list *listCreate();
OD_VOID	listDestroy(list *l);

OD_VOID listAddHead(list *l, node *n);
OD_VOID listAddTail(list *l, node *n);
OD_VOID listDel(list *l, node *n);


list_iter *list_begin(list *l);
node *iter_next(list_iter *iter);
OD_VOID list_end(list_iter *iter);

#ifdef __cplusplus
}
#endif

#endif
