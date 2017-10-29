


#ifndef __CONFIG_H__
#define __CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "glbtypes.h"


typedef struct config {
	OD_U16	c_port;		/*服务端监听端口号*/

	OD_SIZE	c_dbVolume;	/*dict的初始大小*/
} config;



#ifdef __cplusplus
}
#endif

#endif
