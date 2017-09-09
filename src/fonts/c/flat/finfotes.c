/*****************************************************************************
*                                                                            *
*  Copyright 1992, as an unpublished work by Bitstream Inc., Cambridge, MA   *
*                                                                            *
*         These programs are the sole property of Bitstream Inc. and         *
*           contain its proprietary and confidential information.            *
*                                                                            *
* $Header: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/fonts/c/flat/finfotes.c,v 1.1 1995-10-03 00:57:16 jra Exp $
*
* $Log: not supported by cvs2svn $
* Revision 1.2  1995/03/14 00:29:54  mhd
* Have this be up to date with my sandbox.  This is for me just an offline
* version of the font files in /bt/.../ext/c, for offline testing and
* development.
*
 * Revision 1.1  1993/05/04  20:12:36  mhd
 * The flat-directory version of the Bitstream 4-in-1 software.
 *
 * Revision 1.1.1.1  1993/04/15  20:14:24  mhd
 * Initial checkin of Version 2.1 of 4-in-1 from Bitstream.  -jra & mpc
 *
 * Revision 1.14  93/03/16  12:59:41  roberte
 * Added error (usage) report if not enough arguments passed.
 * 
 * Revision 1.13  93/03/15  12:40:38  roberte
 * Release
 * 
 * Revision 1.4  93/02/12  16:27:35  roberte
 * Added #define of O_BINARY and use of it in the "open" call
 * to support PC applications using Microsoft or Borland C.
 * 
 * Revision 1.3  92/10/01  19:59:45  laurar
 * add include files for INTEL
 * 
 * Revision 1.2  92/09/26  14:14:04  roberte
 * Added copyright header and RCS markers. Added
 * comments, so that character dropout cascade code
 * will be clearer.
 * 
*****************************************************************************/
/***********************************************************************************************
    FILE:        FINFOTEST.C
    PROJECT:    4-in-1
    PURPOSE:    Tests binary files (Font Information Tables) for various
                font configurations for the 4-in-1 project.
    METHOD:     Accepts binary file names on the command line.  First file
				name should be a core FIT table binary file.  Adds subsequent
				tables on top.  After loading, test the missing character
				cascade, printing out either font name (if FONT_NAME is defined)
				or Bitstream font ID's to stdout.
    AUTHOR:        RJE @ Bitstream Inc.
    CREATED:    08-14-92
***********************************************************************************************/

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "stdef.h"
#ifdef INTEL
#include <stdio.h>
#else
#define O_BINARY 0
#endif
#include "finfotbl.h"
#include "pclhdrs.h"

/*
	Globals:
*/
FontInfoType gFontInfoTable[N_LOGICAL_FONTS];
char name_buf[17];

/****************************************************************************
*	main()
*	
****************************************************************************/
main(argc, argv)
int argc;
char *argv[];
{
int i, fd, nFonts, curIdx;
size_t sizeRead;
pclHdrType *font_head;
unsigned long nextCode;
int argIdx = 1;
	nFonts = 0;
	if (argc == 1)
		{/* must have some files on the command line! */
		fprintf(stderr, "Usage: %s file1 <file2> ... <fileN>\n	file1..fileN are names of FIT binary files made with the fitutil program.\n", argv[0]);
		exit(1);
		}
	while (argIdx < argc)
		{/* open each FIT binary file on the command line: */
		fd = open(argv[argIdx], O_RDWR|O_BINARY, S_IREAD);
		if (fd >= 0)
			{
			sizeRead = read(fd, &gFontInfoTable[nFonts], (size_t)sizeof(gFontInfoTable));
			close(fd);
			nFonts += sizeRead / sizeof(FontInfoType);
			printf("%s +", argv[argIdx]);
			}
		else
			fprintf(stderr, "Unable to open %s for read.", argv[argIdx]);
		++argIdx;
		}
	printf("\n\n");

	for (i = nFonts - 1 ; i >= 0; i--)
		{/* for each font in the table, bottom to top: */
		curIdx = i;
#ifdef FONT_NAME
		printf("%s->", gFontInfoTable[curIdx].stringName);
#else
		printf("%4d->", gFontInfoTable[curIdx].pclHdrInfo.font_number);
#endif
		/* pretend failed getting a char from font [curIdx] */
		nextCode = gFontInfoTable[curIdx].nextSearchEncode;
		while (!(nextCode & NEXT_NONE))
			{/* while not at end of encoded tree search: */
			if (nextCode & NEXT_ABSTARG)
				{/* next target is absolute -> core RFS */
				curIdx = (nextCode ^= NEXT_ABSTARG);
				}
			else if (nextCode & NEXT_RELTARG)
				{/* next target relative to current position */
				curIdx += (char)(nextCode ^= NEXT_RELTARG);
				}
#ifdef FONT_NAME
			/* print out the font alias name: */
			printf("%s->", gFontInfoTable[curIdx].stringName);
#else
			/* print out the font Bitstream ID: */
			printf("%4d->", gFontInfoTable[curIdx].pclHdrInfo.font_number);
#endif
			/* again, pretend failed getting a char from font [curIdx]: */
			nextCode = gFontInfoTable[curIdx].nextSearchEncode;
			}/* eo while */
		printf(" FINISHED\n");	 /* end of the line */
		}
	printf("\f"); /* nice if output directed to printer */
	exit(0);
}

/* eof finfotest.c */
