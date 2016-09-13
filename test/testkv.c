#include <stdio.h>
#include <stdlib.h>

#include "kv.h"


int main()
{
	KV *kv = kvConstructor("liubang", "haoren");

	printf("%s: %s\n", kv->key, kv->value);

	kvDel(kv);
	return 0;
}
