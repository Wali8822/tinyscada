

#include "rdbclient.h"


int main(int argc, char **argv) {
	struct rdbClient *ndp = NULL;

	WSADATA	data;
	WSAStartup(MAKEWORD(2, 2), &data);

	ndp = rcInit(inet_addr("127.0.0.1"), 1234);

	if (!ndp) {
		printf("Connect error");
	}

	rcRelease(ndp);

	WSACleanup();

	return 0;
}
