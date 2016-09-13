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

static inline ListNode *parseCookies(char *header)
{
	ListNode *cookies = NULL;
	char *copy = bsConstructor(header);
	char *segment, *key;

	bool s = true;

	for (;;) {
		if (s) {
			segment = strtok(copy, "=");
			s = false;
		} else {
			segment = strtok(NULL, "=");
		}

		if (!segment)
			break;

		if (*segment == ' ')
			segment += 1;

		key = segment;
		segment = strtok(NULL, ";\0");

		if (!segment)
			break;

		/* parse cookie to a list */
		cookies = listConstructor(kvConstructor(key, segment), sizeof(KV), cookies);
	}

	bsDel(copy);

	return cookies;
}

static inline ListNode *parseQueryString(char *path)
{
	ListNode *qs = NULL;
	char *copy = bsConstructor(path);

	char *segment, *key, *value;

	bool s = true;

	for (;;) {
		if (s) {
			segment = strtok(copy, "=");
			s = false;
		} else {
			segment = strtok(NULL, "=");
		}
		if (!segment)
			break;
		if (*(segment + strlen(segment) + 1) == '&')
			continue;

		key = segment;
		segment = strtok(NULL, "&\0");
		
		if (!segment)
			break;

		key = urldecode(key);
		value = urldecode(segment);
		qs = listConstructor(kvConstructor(key, value), sizeof(KV), qs);

		bsDel(key);
		bsDel(value);
	}

	bsDel(copy);

	return qs;
}

static inline ListNode *parseHeaders(char *segment)
{
	ListNode *headers = NULL;
	size_t len;
	char *header;

	while(segment) {
		segment = strtok(NULL, ":\n");
		if (!segment || *segment == '\r')
			break;

		header = segment;
		segment = strtok(NULL, "\n");
		if (!segment)
			break;
		if (*segment == ' ')
			segment += 1;

		len = strlen(segment);
		if (*(segment + len - 1) == '\r')
			*(segment + len - 1) = '\0';

		headers = listConstructor(kvConstructor(header, segment), sizeof(KV), headers);

	}

	return headers;
}

#define TOK(s, d)		\
	segment = strtok(s, d);	\
	if (!segment)		\
		goto fail;

Request *requestConstructor(char *buf)
{
	Request *request = malloc(sizeof(Request));

	char *segment, *bs;

	request->method = UNKNOWN_METHOD;
	request->path = NULL;
	request->uri = NULL;
	request->queryString = NULL;
	request->postBody = NULL;
	request->headers = NULL;
	request->cookies = NULL;

	//method
	TOK(buf, " \t");

	if (!strcmp(segment, "OPTIONS")) request->method = OPTIONS;
	else if (!strcmp(segment, "GET")) request->method = GET;
	else if (!strcmp(segment, "HEAD")) request->method = HEAD;
	else if (!strcmp(segment, "POST")) request->method = POST;
	else if (!strcmp(segment, "PUT")) request->method = PUT;
	else if (!strcmp(segment, "DELETE")) request->method = DELETE;
	else if (!strcmp(segment, "TRACE")) request->method = TRACE;
	else if (!strcmp(segment, "CONNECT")) request->method = CONNECT;
	else goto fail;

	//path
	TOK(NULL, " \t");

	request->path = bsConstructor(segment);
	request->uri = bsConstructor(segment);
	//do not support hash
	if (strchr(request->path, '#')) goto fail;

	//version
	TOK(NULL, "\n");

	if (strncmp(segment, "HTTP/1.0", 8) != 0 && strncmp(segment, "HTTP/1.1", 8) != 0)
		goto fail;

	//headers
	request->headers = parseHeaders(segment);
	//body
	bs = kvFindList(request->headers, "Content-Type");
	if (bs && !strncmp(bs, "application/x-www-form-urlencoded", 33)) {
		segment = strtok(NULL, "\0");
		if (!segment)
			goto fail;

		request->postBody = parseQueryString(segment);
	}

	//query string
	segment = strchr(request->path, '?');
	if (segment) {
		request->uri = bsNewLen(request->path, segment - request->path);
		request->queryString = parseQueryString(segment + 1);
		if (!request->queryString)
			goto fail;
	}
	
	//cookies
	segment = kvFindList(request->headers, "Cookie");
	if (segment) {
		request->cookies = parseCookies(segment);
		if (!request->cookies)
			goto fail;
	}

	return request;

fail:
	requestDel(request);
	return NULL;
}

/* destructor request */
void requestDel(Request *request)
{
	if (request->path) bsDel(request->path);
	if (request->uri) bsDel(request->uri);
	if (request->queryString) kvDelList(request->queryString);
	if (request->postBody) kvDelList(request->postBody);
	if (request->headers) kvDelList(request->headers);
	if (request->cookies) kvDelList(request->cookies);

	free(request);
}
