#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "bs.h"
#include "kv.h"
#include "response.h"

char *STATUSES[5][25] = {
	{"Continue", "Switching Protocols"},
	{"OK", "Created", "Accepted", "Non-Authoritative Information", 
	"No Content", "Reset Content", "Partial Content"},
	{"Multiple Choices", "Moved Permanently", "Found", "See Other", 
	"Not Modified", "Use Proxy", "Switch Proxy", "Temporary Redirect", 
	"Permanent Redirect"},
	{"Bad Request", "Unauthorized", "Payment Required", "Forbidden",
	"Not Found", "Method Not Allowed", "Not Acceptable",
	"Proxy Authentication Required", "Request Timeout", "Conflict",
	"Gone", "Length Required", "Precondition Failed",
	"Request Entity Too Large", "Request-URI Too Long",
	"Unsupported Media Type", "Requested Range Not Satisfiable",
	"Expectation Failed", "I'm A Teapot", "Authentication Timeout",
	"Enhance Your Calm"},
	{"Internal Server Error", "Not Implemneted", "Bad Gateway",
	"Service Unavailable", "Gateway Timeout",
	"HTTP Version Not Supported"},
};

Response *responseConstructor()
{
	Response *response = malloc(sizeof(Response));
	response->status = OK;
	response->headers = NULL;
	response->body = NULL;
	
	return response;
}

Response *responseNewRedirect(char *url)
{
	Response *response = responseConstructor();
	responseSetStatus(response, FOUND);
	responseAddHeader(response, "Location", url);

	return response;
}

void responseSetStatus(Response *response, Status status)
{
	response->status = status;
}


void responseSetBody(Response *response, char *body)
{
	response->body = body;
}

void responseAddCookie(Response *response, char *key, char *value, char *domain, char *path, int ttl)
{
	char cbuff[512];
	char sbuff[100];

	time_t t = time(NULL) + ttl;
	strftime(sbuff, 100, "%c GMT", gmtime(&t));
	sprintf(cbuff, "%s=%s; Expires=%s", key, value, sbuff);

	if (domain) {
		sprintf(sbuff, "; Domain=%s", domain);
		strcat(cbuff, sbuff);
	}

	if (path) {
		sprintf(sbuff, "; Path=%s", path);
		strcat(cbuff, sbuff);
	} else {
		strcat(cbuff, "; Path=/");
	}

	responseAddHeader(response, "Set-Cookie", cbuff);
}

void responseAddHeader(Response *response, char *key, char *value)
{
	response->headers = listConstructor(kvConstructor(key, value), sizeof(KV), response->headers);
}


void responseDel(Response *response)
{
	if (response->headers)
		kvDelList(response->headers);
	if (response->body)
		kvDelList(response->body);


	free(response);
}


void responseSend(Response *response, int fd)
{
	ListNode *buffer = NULL;
	ListNode *header;

	char sbuffer[2048];
	
	//headers
	header = response->header;
	while(header) {
		sprintf(sbuffer, "%s: %s\r\n", ((KV *)header->data)->key, ((KV *)header->data)->value);
		buffer = listConstructor(sbuffer, sizeof(char) * (strlen(sbuffer) + 1), buffer);
		header = header->next;
	}

	//status
	sprintf(sbuffer, "HTTP/1.0 %d %s\r\n",
			response->status,
			STATUSES[response->status / 100 - 1][response->status % 100]);

	buffer = listConstructor(sbuffer, sizeof(char) * (strlen(sbuffer) + 1), buffer);

	//output
	while(buffer) {
		send(fd, buffer->data, strlen(buffer->data), 0);
		buffer = buffer->next;
	}

	send(fd, "\r\n", 2, 0);
	if (response->body)
		send(fd, response->body, bsGetLen(response->body), 0);
}
