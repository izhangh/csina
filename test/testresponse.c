#include <stdio.h>
#include <stdlib.h>
#include "response.h"

#define TEST


int main()
{
	Response *response = responseConstructor();

	responseSetStatus(response, OK);
	responseSetBody(response, bsConstructor("<h1>hello world</h1>"));
	responseAddHeader(response, "Content-Type", "text/html");
	responseAddCookie(response, "name", "liubang", "iliubang.cn", "/", 100);

	responseSend(response, 123);
	responseDel(response);
	return 0;
}
