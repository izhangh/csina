#ifndef LIST_H
#define LIST_H



typedef struct node {
	struct node *next;
	void *data;
} ListNode;


ListNode *listConstructor();



#endif
