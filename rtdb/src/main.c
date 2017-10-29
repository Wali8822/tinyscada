


#include "sysincs.h"
#include "dict.h"
#include "net.h"
#include "evtloop.h"
#include "rdb.h"
#include "key.h"


int main(int argc, char *argv[]) {
	config	c = { 1234 };
	WSADATA	data;

	WSAStartup(MAKEWORD(2, 2), &data);

	initServer(&c);

	elMainLoop(SERVER->loop);

	WSACleanup();

	return 0;
}
