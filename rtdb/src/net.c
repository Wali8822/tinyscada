


#include "net.h"

#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>


OD_RET acceptConnection(OD_I32 servfd) {
	return OD_SUCCESS;
}

OD_RET listenToPort(OD_U16 port, OD_I32 *fds, OD_I32 *count) {
	OD_CHAR portName[8];
	struct addrinfo hints, *res, *ptr;
	OD_I32 ret;

	*count = 0;

	memset(&hints, 0, sizeof(hints));
	sprintf(portName, "%d", port);
	hints.ai_family = AF_INET;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;

	if ((ret = getaddrinfo(NULL, portName, &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo error: %s.\n", gai_strerror(ret));
		return OD_FAILURE;
	}

	for (ptr = res; ptr; ptr = ptr->ai_next){
		fds[*count] = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (fds[*count] <= 0) {
			fprintf(stderr, "socket error");
			continue;
		}

		if (bind(fds[*count], ptr->ai_addr, ptr->ai_addrlen) != 0) {
			fprintf(stderr, "bind error");
			closesocket(fds[*count]);
			continue;
		}

		if (listen(fds[*count], 32) != 0) {
			fprintf(stderr, "listen error");
			closesocket(fds[*count]);
			continue;
		}

		++(*count);
	}

	freeaddrinfo(res);

	return OD_SUCCESS;
}
