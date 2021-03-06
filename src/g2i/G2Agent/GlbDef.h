#ifndef _GLOBAL_DEF_H_
#define _GLOBAL_DEF_H_


/***************************************************************************
 *
 *		Glb_Def.h
 *
 *			Contains global definitions not specific to the application.
 *
 *		Feel free to use this code as is, or modified to suit your needs.
 *		Although this software has been extensively tested, Gensym cannot
 *		guarantee error-free performance in all applications.  Accordingly,
 *		use of the software is at the customer's sole risk.
 *
 ***************************************************************************/


#ifndef uchar
#define	uchar				unsigned char
#endif



#ifndef ushort
#define	ushort				unsigned short
#endif



#ifndef ulong
#define	ulong				unsigned long
#endif


#ifndef BOOL
#define	BOOL				long
#endif


#ifndef	FALSE
#define	FALSE				0
#endif


#ifndef	TRUE
#define	TRUE				1
#endif




#define	TIME_DELAY(x)		((long)time(NULL) - (long)x)



#ifdef WIN32
#define	DIR_SEP				"\\"
#else
#define	DIR_SEP				"/"
#endif

#undef MAX_NAME_LENGTH
#ifndef MAX_NAME_LENGTH
#define MAX_NAME_LENGTH		64
#endif

#endif
