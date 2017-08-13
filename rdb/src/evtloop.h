


#ifndef __EVTLOOP_H__
#define	__EVTLOOP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "glbtypes.h"

/**
  * Event Loop Flags
  */
#define ELF_NONE		0x00
#define ELF_READ		0x01
#define ELF_WRITE		0x02
#define ELF_RW			0x03

struct elEventLoop;

typedef OD_VOID (*elFileProc) (struct elEventLoop * el, OD_I32 fd, OD_U16 mask, OD_VOID *data);

typedef struct elFileEvent{
	OD_U16 mask;	/*OD_(READ|WRITE)*/

	elFileProc	rFunc;
	elFileProc	wFunc;
	void *privatedata;
} elFileEvent;

typedef struct elFiredEvent {
	OD_I32	fd;
	OD_U16	mask;
} elFiredEvent;

typedef struct elEventLoop{
	OD_I32		size;
	OD_I32		maxfd;

	elFileEvent		*events;
	elFiredEvent	*fireds;

	OD_BOOLEAN	stop;

	OD_VOID	*api_data;
} elEventLoop;


elEventLoop	*elCreateEventLoop(OD_I32 size);
OD_VOID elDestroy(elEventLoop *el);

OD_RET elAddFileEvent(elEventLoop *el, OD_I32 fd, OD_U16 mask, elFileProc proc, OD_VOID *priv);
OD_VOID elDelFileEvent(elEventLoop *el, OD_I32 fd, OD_U16 mask);

OD_VOID elStop(elEventLoop *el);
OD_VOID elMainLoop(elEventLoop *el);

#ifdef __cplusplus
}
#endif

#endif
