#include <stdio.h>
#include <stdlib.h>

#include "bs.h"


int main()
{
	char *bs = bsConstructor("helloliubang");
	
	printf("%s\n", bs);

	bsLCat(&bs, " hhh");
	printf("%s\n", bs);

	char *bs1 = bsConcat(bsConstructor("hello"), bsConstructor("world"));
	printf("%s\n", bs1);

	return 0;
}
