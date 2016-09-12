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

char *bsConcat(char *bs1, char *bs2)
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

char *bsSubstr(char *orig, uint32_t start, int32_t end)
{
	size_t len = bsGetLen(orig);
	size_t newLen = (end <= 0) ? len - start + end : end - start;
	assert(newLen > 0);
	assert(newLen <= len);

	char *bs = malloc(sizeof(char) * (BS_HEADER_LEN + newLen + 1));
	assert(bs);
	bs += BS_HEADER_LEN;

	memcpy(bs, orig + start, newLen);
	
	bsSetLen(bs, newLen);

	return bs;
}

char *bsRandom(uint32_t len, char *suffix)
{
	char table[62] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
			  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
			  'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
			  'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
			  'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
			  'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
			  'Y', 'Z'};
	char *bs = malloc(sizeof(char) * (BS_HEADER_LEN + len + 1));
	assert(bs);
	bs += BS_HEADER_LEN;
	bsSetLen(bs, len);
	
	for (uint32_t i = 0; i < len; i++) {
		bs[i] = table[rand() % sizeof(table)];
	}

	if (suffix)
		bsConcat(bs, suffix);

	return bs;
}

char *bsEscape(char *bs)
{
	char *copy = bsConstructor(bs);
	char *res = bsConstructor("");

	char *c = copy;
	char *p = copy;

	while(*c != '\0') {
		if (*c == '<') {
			*c = '\0';
			bsLCat(&res, p);
			bsLCat(&res, "&lt;");
			p = c + 1;
		} else if (*c == '>') {
			*c = '\0';
			bsLCat(&res, p);
			bsLCat(&res, "&gt;");
			p = c + 1;
		}
		c++;
	}

	bsLCat(&res, p);
	bsDel(copy);

	return res;
}
