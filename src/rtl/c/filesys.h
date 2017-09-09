/*
 * filesys.h - file manipulation system include file
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#ifdef oldsequent
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#endif

#define FA_ORDINARY	0x0
#define FA_READ_ONLY	0x1

#ifndef FA_HIDDEN
#define FA_HIDDEN	0x2
#endif

#ifndef FA_SYSTEM
#define FA_SYSTEM	0x4
#endif

#define ITEM_SIZE	43
#define FNAME		30
#define FILE_FOUND	0

#define COPY_IF_NULL(dst, src)    {if (!(*(dst))) strcpy((dst), (src));}

