#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "bs.h"
#include "kv.h"
#include "server.h"
#include "template.h"



Server *server = NULL;


static void sig(int signum)
{
	if (server)
		serverDel(server);

	fprintf(stdout, "\n[%d] Bye\n", signum);
	exit(0);
}

static Response *notFound(Request *req);


int main(int argc, char *argv[])
{
	if (signal(SIGINT, sig) == SIG_ERR || signal(SIGTERM, sig) == SIG_ERR) {
		fprintf(stderr, "error: failed to bind signal handler\n");
		return 1;
	}

	srand(time(NULL));

	uint16_t server_port = 8080;
	if (argc > 1) {
		if (sscanf(argv[1], "%I16u", &server_port) == 0 || server_port > 65535) {
			fprintf(stderr, "error: invalid command line argument, using default port 8080.\n");
			server_port = 8080;
		}
	}

	Server *server = serverConstructor(server_port);
	serverAddHandler(server, notFound);
	serverAddStaticHandler(server);

	serverRun(server);

	printf("ok\n");


	return 0;
}


static Response *notFound(Request *req)
{
	Response *response = responseConstructor();	
	responseSetStatus(response, NOT_FOUND);
	Template *template = templateConstructor("public/tpls/index.html");
	responseSetBody(response, templateRender(template));
	return response;
}
