

#include <stdlib.h>
#include <stdio.h>
#include <WS2tcpip.h>

#include "evtloop.h"



struct elEventLoop	* elCreate(int size) {
	struct elEventLoop * el = (struct elEventLoop*)calloc(1, sizeof(struct elEventLoop));

	if (!el){
		return NULL;
	}

	el->size = size;
	el->maxfd = -1;
	el->evts = calloc(size, sizeof(struct elFileEvent));

	if (!el->evts){
		free(el);
		return NULL;
	}

	return el;
}

void elDestroy(struct elEventLoop *el) {
	free(el->evts);
	free(el);
}

int elAddFileEvent(struct elEventLoop *el, int fd, unsigned int mask, elFileProc proc) {
	if (fd >= el->size){
		return EL_FAIL;
	}

	el->evts[fd].mask |= mask;

	if (mask & EL_READ){
		el->evts[fd].rFunc = proc;
	} else if(mask & EL_WRITE) {
		el->evts[fd].wFunc = proc;
	} else {
		return EL_FAIL;
	}

	if (el->maxfd < fd){
		el->maxfd = fd;
	}

	return EL_OK;
}

void elDelFileEvent(struct elEventLoop *el, int fd) {
	int i;

	if (fd >= el->size){
		return;
	}

	el->evts[fd].mask = EL_NONE;

	for (i = el->maxfd; i >= 0; --i ) {
		if (el->evts[i].mask & EL_RW){
			if (i < el->maxfd){
				el->maxfd = i;
			}
			break;
		}
	}
}

void elStop(struct elEventLoop *el) {
	el->stop = 1;
}

void elMainLoop(struct elEventLoop *el) {
	FD_SET	rSet;
	FD_SET	wSet;
	int i, ret;

	while (!el->stop) {
		FD_ZERO(&rSet);
		FD_ZERO(&wSet);

		for (i = 0; i <= el->maxfd; ++i) {
			if (el->evts[i].mask & EL_READ){
				FD_SET(i, &rSet);
			} 

			if (el->evts[i].mask & EL_WRITE){
				FD_SET(i, &wSet);
			}
		}

		ret = select(el->maxfd, &rSet, &wSet, NULL, NULL);

		if (ret > 0){
			for (i = 0; i <= el->maxfd; ++i) {
				if (FD_ISSET(i, &rSet) && el->evts[i].rFunc) {
					el->evts[i].rFunc(el, i, el->evts[i].privatedata);
				}

				if (FD_ISSET(i, &wSet) && el->evts[i].wFunc){
					el->evts[i].wFunc(el, i, el->evts[i].privatedata);
				}
			}
		}
	}
}
