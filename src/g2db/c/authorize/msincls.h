/* -*- Mode: C -*-
 *
 * Module:      MSINCLS.H
 *
 * DESCRIPTION: This file contains the assorted types, defined,
 *              and global references for the PC specific files.
 *
 * Copyright (C) 1986-2017 Gensym Corporation.
 * All Rights Reserved.
 *
 * Pre 8-93: Richard Haggard & Kamal Bijlani
 *
 * mpc 12-10-93: In an effort to bring back the forked PC TW code,
 *     this file was created to encapsulate the contents of numerous
 *     header files which were included by the MS specific files.
 */

#if defined(WIN32) || defined(__WATCOMC__)

/*************************************************************************/
/* TYPEDEFS                                                              */
/*************************************************************************/

typedef struct G2Event {
    struct G2Event *next;
    long window_index;
    long type;
    long x;
    long y;
    long width;
    long height;
    long key_code;
    long key_bits;
    long time;
} G2EVENT;


typedef struct tagG2INFO {
    long	    nTileBG;	    /* Colors for tiling. */
    long	    nTileFG;	    /* */
    HBRUSH          Tilehbr;        /* Tiling Pattern Brush */
    RECT	    rcPaint;	    /* Last paint message coords. */
    struct G2Event *events_head;
    struct G2Event *events_tail;
    long            G2Context;
    BOOL            InitDone;
} G2INFO, * LPG2INFO;


typedef struct tagXCOLOR {
    char       *szColor;
    COLORREF	rgbColor;
} XCOLOR, * LPXCOLOR;


/*************************************************************************/
/* DEFINES                                                               */
/*************************************************************************/

/* Server extra word defines. */

#define	WW_G2_S_INFO			 0	/* Server specific information. */
#define	WW_G2_S_EXTRA			 4


/* temporarily define globals here   */
#define	DEFAULT_COLORS     69   /* Number of default colors*/

#if defined(WIN32)
#define WIN32_IS_NT      (GetVersion() < 0x80000000)
#define WIN32_IS_WIN32S  ((GetVersion() & 0x80000000) && \
			  (LOBYTE(LOWORD(GetVersion())) <4))
#define WIN32_IS_WIN95   ((GetVersion() & 0x80000000) && \
			  (LOBYTE(LOWORD(GetVersion())) >=4))
#else
#define WIN32_IS_NT      0
#define WIN32_IS_WIN32S  1
#define WIN32_IS_WIN95   0
#endif 

/*************************************************************************/
/* GLOBAL REFS                                                           */
/*************************************************************************/
extern int      GiFreeGDI;
extern HDC	Ghdc;	    /* the Global Handle to Device Context */
extern HDC	GhdcMem;    /* the Global Handle to Memory Device Context */
extern HBITMAP  GhbmDummy;

extern  HPALETTE     GensymPalette;	   /* Handle to the color palette. */
extern  HWND	     hwndExec;		   /* Main window for the application. */
extern  XCOLOR       XColorArray[DEFAULT_COLORS];
extern  int          iNumColors;	   /* Number of colors in custom palette */
extern  int          iNumStandardColors;   /* Number of colors before the extended ones. */

#endif /* WIN32 || __WATCOMC__ */
