#include <stdio.h>

#include "bs.h"
#include "kv.h"
#include "request.h"

static inline char *urldecode(char *segment)
{
	char *cc = segment;
	char *bs = bsConstructor("");
	char escCode[3] = "\0\0\0";
	char escChar[2] = "\0\0";

	while(*cc != '\0') {
		switch (*cc) {
			case '+':
				*cc++ = ' ';
				break;
			case '%':
				*cc++ = '\0';
				bsLCat(&bs, segment);
				escCode[0] = *cc++;
				escCode[1] = *cc++;
				escChar[0] = (char) strtol(escCode, NULL, 16);//base16

				segment = cc;

				bsLCat(&bs, escChar);
				break;
			default :
				cc++;
		}
	}

	bsLCat(&bs, segment);

	return bs;
}

