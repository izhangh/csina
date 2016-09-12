#include <string.h>

#include "list.h"

/* construct a list node */
ListNode *listConstructor(void *value, size_t size, ListNode *next)
{
	ListNode *node = malloc(sizeof(ListNode));
	node->next = next;
	node->value = malloc(size);
	node->size = size;

	memcpy(node->value, value, size);

	return node;
}

/* reverse a list */
ListNode *listReverse(ListNode *node)
{
	ListNode *prev = NULL;
	while(node) {
		ListNode *next = node->next;
		node->next = prev;
		prev = node;
		node = next;
	}

	return prev;
}

void listDel(ListNode *node)
{
	if (!node)
		return;
	do {
		ListNode *next = node->next;
		free(node->value);
		free(node);
		node = next;
	} while(node);
}

/* list iteration */
IterationResult listForEach(ListNode *node, ListIterator iteratior)
{
	if (!node)
		return DONE;

	bool res;
	do {
		res = iterator(node->value);
		node = node->next;
	} while(node && res);

	return res ? DONE : BREAK;
}

