

#ifndef __GLBTYPES_H__
#define __GLBTYPES_H__

#ifdef __cplusplus
extern "C" {
#endif



/*****************************************************/
/******通用定义，所有平台都适用******/
/*****************************************************/

#define OD_TRUE			1
#define OD_FALSE		0
#define OD_SUCCESS		0
#define OD_FAILURE		1
#define OD_BIG_ENDIAN			0
#define OD_LITTLE_ENDIAN		1

#define UNUSED(arg)			(void)(arg)

#define	OD_FAILED(ret)		((ret) != OD_SUCCESS)
#define OD_SUCCED(ret)		((ret) == OD_SUCCESS)

/************************************************************************/
/* MS-DOS and WINDOWS							*/
/************************************************************************/
#if defined(_WIN32)

#define OD_BYTE_ORDER		OD_LITTLE_ENDIAN		/*for windows, default little endian*/

#define OD_RET		int

#define OD_CHAR		char
#define OD_UCHAR	unsigned char

#define OD_BOOLEAN	unsigned char

#define OD_I8		char
#define OD_I16		short
#define OD_I32		int
#define OD_I64		long long
#define OD_U8		unsigned char
#define OD_U16		unsigned short
#define OD_U32		unsigned int
#define OD_U64		unsigned long long

#define OD_VOID		void
#define OD_STATIC	static
#define OD_CONST	const

#define OD_FLOAT	float
#define OD_DOUBLE	double

#define	OD_SIZE		unsigned int

#endif

/*************************************************************/
/*LINUX SYSTEM												*/
/*************************************************************/
#if defined(linux)

#include <endian.h>

#if (__BYTE_ORDER == __LITTLE_ENDIAN)
	#define OD_BYTE_ORDER	OD_LITTLE_ENDIAN
#elif (__BYTE_ORDER == __BIG_ENDIAN)
	#define OD_BYTE_ORDER	OD_BIG_ENDIAN
#else
	#error	"unsupported byte order"
#endif

#define OD_RET		int

#define OD_CHAR		char
#define OD_UCHAR	unsigned char

#define OD_BOOLEAN	unsigned char

#define OD_I8		char
#define OD_I16		short
#define OD_I32		int
#define OD_I64		long long

#define OD_U8		unsigned char
#define OD_U16		unsigned short
#define OD_U32		unsigned int
#define OD_U64		unsigned long long

#define OD_VOID		void
#define OD_STATIC	static
#define OD_CONST	const

#define OD_FLOAT	float
#define OD_DOUBLE	double

#define	OD_SIZE		unsigned int

#if !defined(max)
	#define max(a,b) 	(((a)>(b)) ? (a) : (b))
#endif

#if !defined(min)
	#define min(a,b) 	(((a)<(b)) ? (a) : (b))
#endif

#endif


#ifdef __cplusplus
}
#endif

#endif

