


#ifndef __SERVER_H__
#define __SERVER_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int acceptConnection(int servfd);

int listenToPort(unsigned short port, int *fds, int *count);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
