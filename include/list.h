#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdlib.h>

typedef enum IteratonResult {
	DONE, BREAK
} IterationResult;

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
void listDel(ListNode *);
IterationResult listForEach(ListNode *, ListIterator);

#endif
