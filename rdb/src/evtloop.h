


#ifndef __EVTLOOP_H__
#define	__EVTLOOP_H__

#ifdef __cplusplus
extern "C" {
#endif

#define EL_OK	0
#define EL_FAIL	-1

#define EL_NONE		0x00
#define EL_READ		0x01
#define EL_WRITE	0x02
#define EL_RW		0x03

struct elEventLoop;

typedef void (*elFileProc) (struct elEventLoop * el, int fd, void * data);

struct elFileEvent{
	unsigned int mask;

	elFileProc	rFunc;
	elFileProc	wFunc;
	void *privatedata;
} ;


struct elEventLoop{
	int size;
	struct elFileEvent	*	evts;

	int maxfd;

	int stop;
} ;


struct elEventLoop	*elCreate(int size);
void elDestroy(struct elEventLoop *el);

int elAddFileEvent(struct elEventLoop *el, int fd, unsigned int mask, elFileProc proc);
void elDelFileEvent(struct elEventLoop *el, int fd);

void elStop(struct elEventLoop *el);
void elMainLoop(struct elEventLoop *el);

#ifdef __cplusplus
}
#endif

#endif
