

#include <stdlib.h>
#include <stdio.h>
#include <WS2tcpip.h>

#include "evtloop.h"


#if defined(WIN32)
	#define	__USE_SELECT
		#include "el_select.c"
	#undef	__USE_SELECT
#elif defined(linux)
	#if defined(USE_SELECT)
		#define	__USE_SELECT
			#include "el_select.c"
		#undef	__USE_SELECT
	#endif
#endif


elEventLoop	* elCreateEventLoop(OD_I32 size) {
	elEventLoop *el = (elEventLoop*)calloc(1, sizeof(elEventLoop));

	if (el){
		el->size = size > 0 ? size : 1024;
		el->maxfd = -1;

		el->events = calloc(size, sizeof(elFileEvent));
		el->fireds = calloc(size, sizeof(elFiredEvent));
		if (!el->events || !el->fireds) { goto EL_C_ERR; }

		if (OD_FAILED(elApiCreate(el))) { goto EL_C_ERR; }
	}

	return el;

EL_C_ERR:
	if (el) {
		if (el->events) { free(el->events); }
		if (el->fireds) { free(el->fireds); }
		free(el);
	}

	return NULL;
}

void elDestroy(struct elEventLoop *el) {
	if (el) {
		elApiDestroy(el);
		if (el->events) { free(el->events); }
		if (el->fireds) { free(el->fireds); }
		free(el);
	}
}

OD_RET elAddFileEvent(elEventLoop *el, OD_I32 fd, OD_U16 mask, elFileProc proc, OD_VOID *priv) {
	if (fd >= el->size){ return OD_FAILURE; }

	if (OD_FAILED(elApiAddEvent(el, fd, mask))) { return OD_FAILURE; }

	el->events[fd].mask |= mask;
	el->events[fd].privatedata = priv;

	if (mask & ELF_READ){ el->events[fd].rFunc = proc; }
	if (mask & ELF_WRITE) { el->events[fd].wFunc = proc; }

	if (el->maxfd < fd){
		el->maxfd = fd;
	}

	return OD_SUCCESS;
}

OD_VOID elDelFileEvent(elEventLoop *el, OD_I32 fd, OD_U16 mask) {
	if (fd > el->size) { return; }

	el->events[fd].mask = el->events[fd].mask & (~mask);

	elApiDelEvent(el, fd, mask);

	if (fd == el->maxfd) {
		int ix;
		for (ix = el->maxfd - 1; ix >= 0; --ix) {
			if (el->events[ix].mask != ELF_NONE) { break; }
		}

		el->maxfd = ix;
	}
}

OD_VOID elStop(elEventLoop *el) {
	el->stop = OD_TRUE;
}

OD_VOID elProcessEvents(elEventLoop *el, OD_U16 flag) {
	OD_I32	numEvents, ix;

	numEvents = elApiPoll(el, NULL);

	for (ix = 0; ix < numEvents; ++ix) {
		elFiredEvent *fired = &(el->fireds[ix]);
		elFileEvent *fe = &(el->events[fired->fd]);

		if (fired->mask & ELF_READ) {
			if (fe->rFunc) { fe->rFunc(el, fired->fd, fired->mask, fe->privatedata); }
		}

		if (fired->mask & ELF_WRITE) {
			if (fe->wFunc) { fe->wFunc(el, fired->fd, fired->mask, fe->privatedata); }
		}
	}
}

OD_VOID elMainLoop(elEventLoop *el) {
	el->stop = OD_FALSE;

	while (!el->stop){
		elProcessEvents(el, 0);
	}
}
