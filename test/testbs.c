#include <stdio.h>
#include <stdlib.h>

#include "bs.h"


int main()
{
	char *bs = bsConstructor("helloliubang");
	
	printf("%s\n", bs);

	return 0;
}
