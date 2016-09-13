#include <stdio.h>
#include <string.h>

#include "bs.h"
#include "kv.h"

/* key-val constructor */
KV *kvConstructor(char *key, char *value)
{
	KV *kv = malloc(sizeof(KV));
	kv->key = bsConstructor(key);
	kv->value = bsConstructor(value);

	return kv;
}

/* delete key-val */
void kvDel(KV *kv)
{
	bsDel(kv->key);
	bsDel(kv->value);

	free(kv);
}

/* implements iterator */
static bool kvDelEach(void *kv)
{
	if (kv) {
		bsDel(((KV *)kv)->key);
		bsDel(((KV *)kv)->value);
	}

	return true;
}

/* delete list key-val */
void kvDelList(ListNode *list)
{
	listForEach(list, kvDelEach);
	listDel(list);
}

static bool kvPrintEach(void *kv)
{
	fprintf(stdout, "%s: %s\n", ((KV *)kv)->key, ((KV *)kv)->value);
	return true;
}

void kvPrintList(ListNode *list)
{
	listForEach(list, kvPrintEach);
}

char *kvFindList(ListNode *node, char *key)
{
	while(node) {
		if (!strcmp(((KV *)node->data)->key, key))
			return ((KV *)node->data)->value;
		node = node->next;
	}

	return NULL;
}

