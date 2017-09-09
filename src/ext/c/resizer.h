/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * Module:      resizer.h
 *
 * Copyright (C) 1986-2017 Gensym Corporation.
 * All Rights Reserved.
 *
 + Author: 2004         fmw
 +
 + Description:         Winforms-style resizable dialog facility
 *
 * Modifications:
 *   8/16/05, fmw: Created from filedlg.h
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#ifdef WIN32
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* Flags for g2pvt_resizer_add. Note that the values agree with the Winforms
   "anchorStyles" enumeration. */

#define ANCHOR_NONE 0		/* Keep in sync with LISP g2-anchor-xxx */
#define ANCHOR_TOP  1
#define ANCHOR_BOTTOM 2
#define ANCHOR_LEFT 4
#define ANCHOR_RIGHT 8

#define RectWidth(r) (r.right-r.left)
#define RectHeight(r) (r.bottom-r.top)

typedef struct {
  HWND parent;
  BOOL enabled;
  POINT minSize;		/* Min size (window coor) */
  POINT initSize;		/* Initial size (client coor) */
  POINT curSize;		/* Current size */
  int maxControls;		/* Size of arrays, below. */
  int n;			/* Number of controls */
  int *ids;			/* Control IDs */
  BYTE *flags;			/* LTRB edge bindings */
  RECT *rects;			/* Control positions at min (original) size */
} Resizer;

Resizer* g2pvt_resizer_create(HWND parent, int maxControls);
void g2pvt_resizer_free(Resizer *rs);
void g2pvt_resizer_add(Resizer *rs, int id, int flags);
void g2pvt_resizer_lock(Resizer *rs);
void g2pvt_resizer_resize(Resizer *rs, int cx, int cy);
BOOL g2pvt_resizer_dlgproc(Resizer *resizer, DWORD *retval,
			   HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LPRECT GetSizeGripRect(HWND hwnd, LPRECT r);

#ifdef __cplusplus
}
#endif

#endif
