#ifndef KV_H
#define KV_H

#include <stdbool.h>
#include "list.h"

typedef struct KV {
	char *key;
	char *value;
}KV;


KV *kvConstructor(char *, char *);
void kvDel(KV *);
void kvDelList(ListNode *);
void kvPrintList(ListNode *);
char *kvFindList(ListNode *, char *);

#endif
