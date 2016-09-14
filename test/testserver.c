#include "list.h"
#include "bs.h"
#include "kv.h"
#include "request.h"
#include "response.h"
#include "server.h"


Response *handler(Request *req)
{
	Response *response = responseConstructor();
	responseSetStatus(response, OK);
	responseSetBody(response, bsConstructor("<h1>test content</h1>"));
	responseAddHeader(response, bsConstructor("name"), bsConstructor("liubang"));

	return response;
}


int main()
{
	Server *server = serverConstructor(8080);
	serverAddHandler(server, handler);
	serverRun(server);

}
