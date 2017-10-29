



#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "client.h"


/**
  * 解析收到的客户端命令，并返回到client的命令列表中
  */
OD_RET op_dec(client *cli, OD_U8 *pdu, OD_I32 pdu_len);

#ifdef __cplusplus
}
#endif

#endif
