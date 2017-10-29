



#include "list.h"

#include <stdlib.h>


list *listCreate(){
	list *l = malloc(sizeof(list));

	if (l) {
		l->head = l->tail = NULL;
		l->_count = 0;
	}

	return l;
}

OD_VOID	listDestroy(list *l) {
	if (l) {
		list_iter *iter = list_begin(l);
		node *	tmp;
		while (iter && (tmp = iter_next(iter))) {
			l->free_func(tmp);
		}

		free(l);
	}
}

void listAddHead(list *l, node *n) {
	if (l->_count == 0) {
		l->head = l->tail = n;
		n->next = n->prev = NULL;
	} else {
		n->next = l->head;
		n->prev = NULL;
		l->head->prev = n;
		l->head = n;
	}

	l->_count += 1;
}

void listAddTail(list *l, node *n) {
	if (l->_count == 0) {
		l->tail = l->head = n;
		n->next = n->prev = NULL;
	} else {
		l->tail->next = n;
		n->prev = l->tail;
		n->next = NULL;
		l->tail = n;
	}

	l->_count += 1;
}

void listDel(list *l, node *n) {
	if (n->prev) {
		n->prev->next = n->next;
	} else {
		l->head = n->next;
	}

	if (n->next) {
		n->next->prev = n->prev;
	} else {
		l->tail = n->prev;
	}

	--l->_count;
}

list_iter *list_begin(list *l) {
	list_iter *iter = (list_iter*)malloc(sizeof(list_iter));

	if (iter) {
		iter->iter = l->head;
	}

	return iter;
}

node *iter_next(list_iter *iter) {
	node *tmp = iter->iter;

	if (iter->iter) {
		iter->iter = iter->iter->next;
	}

	return tmp;
}

OD_VOID list_end(list_iter *iter) {
	if (iter) {
		free(iter);
	}
}
