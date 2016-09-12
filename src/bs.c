#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "bs.h"

char *bsConstructor(const char *str)
{
	size_t len = strlen(str);
	char *bs = malloc(sizeof(char) * (BS_HEADER_LEN + len + 1));
	assert(bs);
	bs += BS_HEADER_LEN;
	strcpy(bs, str);
	bsSetLen(bs, len);

	return bs;
}

char *bsNewLen(char *buf, size_t len)
{
	char *bs = malloc(sizeof(char) * (BS_HEADER_LEN + len + 1));
	assert(bs);
	bs += BS_HEADER_LEN;
	memcpy(bs, buf, len);
	bsSetLen(bs, len);

	return bs;
}

char *bsCat(char *bs1, char *bs2)
{
	size_t len1 = bsGetLen(bs1);
	size_t len2 = bsGetLen(bs2);
	size_t len = len1 + len2;

	char *bs = malloc(sizeof(char) * (BS_HEADER_LEN + len + 1));
	assert(bs);
	bs += BS_HEADER_LEN;

	strcpy(bs, bs1);
	strcpy(bs + len1, bs2);
	bsSetLen(bs, len);

	return bs;
}
