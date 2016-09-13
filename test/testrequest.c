#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "request.h"
#include "kv.h"


int main()
{
	char buf[] = "POST /index.php?name=liubang&age=23 HTTP/1.1\r\n"		\
		     "Host: linger.iliubang.cn\r\n"				\
		     "Content-Type: application/x-www-form-urlencoded\r\n"	\
		     "Content-Length: 100\r\n"					\
		     "Cookie: _octo=GH1.1.1580016471.1473400796; logged_in=yes; dotcom_user=iliubang; user_session=etqtpRcimbr6UJmzQ2zrk2m2s-Fo2BTIpPiRYtCMocnogxobV9eka5GELpK1AaN238KWIZVNzgXpqrT7; _gh_sess=eyJzZXNzaW9uX2lkIjoiMTg3NzMwOWYxMGI1NzQzYzg4ZmYzYWI2NDJkNjI4MTEiLCJzcHlfcmVwbyI6ImlsaXViYW5nL2NzaW5hIiwic3B5X3JlcG9fYXQiOjE0NzM3NTAxMjMsImNvbnRleHQiOiIvIn0%3D--0b71ed8c139dde57989cea21b28f4b3eda6fbf01; _ga=GA1.2.1887061096.1473400796; tz=Asia%2FShanghai\r\n\r\n我是中国人，zheshi 测试用的数据";

	printf("%s\n", buf);


	Request *req = requestConstructor(buf);

	printf("path: %s\n", req->path);
	printf("uri: %s\n", req->uri);

	printf("=========query string=========\n");
	kvPrintList(req->queryString);
	printf("=========post body==========\n");
	kvPrintList(req->postBody);
	printf("=========cookies=========\n");
	kvPrintList(req->cookies);
	printf("=========headers=========\n");
	kvPrintList(req->headers);

	requestDel(req);
	return 0;
}
