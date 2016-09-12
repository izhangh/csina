#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdlib.h>

typedef enum IteratonResult {
	DONE, BREAK
} IteratonResult;

/* list node */
typedef struct node {
	struct node *next;
	void *data;
	size_t size;
} ListNode;

/* ListIterator interface */
typedef bool (*ListIterator)(void *);

ListNode *listConstructor(void *, size_t, ListNode *);
ListNode *listRevers(ListNode *);
void listDel(listNode *);
IteratonResult listForEach(listNode *, ListIterator);

#endif
