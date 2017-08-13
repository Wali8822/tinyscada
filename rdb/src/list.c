



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

