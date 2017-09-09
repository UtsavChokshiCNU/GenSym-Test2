/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      resizer.c
 +
 * Copyright (C) 1986-2017 Gensym Corporation.
 * All Rights Reserved.
 +
 + Author: 2004         fmw
 +
 + Description:         Winforms-style resizable dialog facility
 +
 + External Interface:  g2pvt_resizer_create, etc.
 +
 + Dependencies:        None
 +
 + Modifications:
 +   8/16/05, fmw: Created from filedlg.cpp
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <windows.h>
#include <windowsx.h>
#include "resizer.h"

/*
 * Resizable Dialogs Facility
 */

#define AdjustEdges(code,r,edgeA,edgeB,d) \
    switch((code)&3) { \
      case 0: r.edgeA += (d)/2; r.edgeB += (d)/2; break; \
      case 2: r.edgeA += (d);   r.edgeB += (d);   break; \
      case 3:                   r.edgeB += (d);   break;}

int g2pvt_trace(const char *fmt, ...);
#define PRINTF g2pvt_trace

/*
 * Utilities
 */

/* Get window rectangle in parent client coordinates. */
LPRECT GetPCCWindowRect(HWND parent, HWND hwnd, RECT *r)
{
  GetWindowRect(hwnd,r);
  ScreenToClient(parent, (LPPOINT)&r->left);
  ScreenToClient(parent, (LPPOINT)&r->right);
  return r;
}

static LPRECT GetSizeGripRect2(int cx, int cy)
{
  static RECT r;
  r.left = cx - GetSystemMetrics(SM_CXHSCROLL);
  r.top  = cy - GetSystemMetrics(SM_CYVSCROLL);
  r.right = cx;
  r.bottom = cy;
  return &r;
}

LPRECT GetSizeGripRect(HWND hwnd, LPRECT r)
{
  GetClientRect(hwnd,r);
  *r = *GetSizeGripRect2(r->right, r->bottom);
  return r;
}

BOOL HasThickFrame(HWND hwnd)
{
  return hwnd && (GetWindowLong(hwnd,GWL_STYLE) & WS_THICKFRAME) != 0;
}

static BOOL EnableSizeGrip(HWND hwnd)
{
  HWND parent = GetParent(hwnd);

  return (!IsZoomed(hwnd) && (!parent || !IsZoomed(parent))) && (HasThickFrame(hwnd) || HasThickFrame(parent));
}

/*
 * API
 */

Resizer* g2pvt_resizer_create(HWND parent, int maxControls)
{
  Resizer *rs = (Resizer *) calloc(1,sizeof(Resizer));
  rs->parent = parent;
  rs->maxControls = maxControls;
  rs->ids   = (int*)  calloc(maxControls,sizeof(int));
  rs->flags = (BYTE*) calloc(maxControls,sizeof(BYTE));
  rs->rects = (RECT*) calloc(maxControls,sizeof(RECT));
  return rs;
}

void g2pvt_resizer_free(Resizer *rs)
{
  free(rs->ids);
  free(rs->flags);
  free(rs->rects);
  free(rs);
}

void g2pvt_resizer_add(Resizer *rs, int id, int flags)
{
  rs->ids[rs->n] = id;
  rs->flags[rs->n] = flags;
  rs->n++;
}

void g2pvt_resizer_lock(Resizer *rs)
{
  RECT r;
  int i;
  HWND hwnd;

  GetClientRect(rs->parent,&r);
  rs->minSize.x = rs->initSize.x = rs->curSize.x = RectWidth(r);
  rs->minSize.y = rs->initSize.y = rs->curSize.y = RectHeight(r);

  for(i=0; i<rs->n; i++) {
    hwnd = GetDlgItem(rs->parent,rs->ids[i]);
    if(hwnd)
      GetPCCWindowRect(rs->parent, hwnd, &rs->rects[i]);
  }
  rs->enabled = TRUE;
}

/* Apply linear resizing to controls, given new parent size. */
void g2pvt_resizer_resize(Resizer *rs, int cx, int cy)
{
  HDWP hdwp;
  HWND hwnd;
  RECT r;
  int i,flags,dx,dy;

  if(!rs->enabled) return;

  dx = cx - rs->initSize.x;
  dy = cy - rs->initSize.y;

  hdwp = BeginDeferWindowPos(rs->n);
  for(i=0; i<rs->n; i++) {
    hwnd = GetDlgItem(rs->parent,rs->ids[i]);
    if(!hwnd) continue;
    flags = rs->flags[i];
    r = rs->rects[i];
    AdjustEdges(flags,r,top,bottom,dy)
    AdjustEdges(flags>>2,r,left,right,dx)
    hdwp = DeferWindowPos(hdwp, hwnd, NULL, r.left, r.top, RectWidth(r), RectHeight(r),
			  SWP_NOZORDER);
  }
  EndDeferWindowPos(hdwp);

  rs->curSize.x = cx;
  rs->curSize.y = cy;
}

BOOL g2pvt_resizer_dlgproc(Resizer *resizer, DWORD *retval,
			   HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  HDC hdc;
  RECT r, rw, rc;
  POINT p;
  BOOL sizegrip = EnableSizeGrip(hwnd);

  if(!resizer) return FALSE;

  switch(message) {
   case WM_NCHITTEST:
     if(sizegrip) {
       GetSizeGripRect(hwnd, &r);
       MapWindowPoints(hwnd, NULL, (LPPOINT)&r, 2);
       p.x = GET_X_LPARAM(lParam);
       p.y = GET_Y_LPARAM(lParam);
       if (PtInRect(&r,p)) {
	 SetWindowLongPtr(hwnd, DWLP_MSGRESULT, HTBOTTOMRIGHT);
	 *retval = HTBOTTOMRIGHT;
	 return TRUE;
       }
     }
     break;

   case WM_PAINT: 		/* Draw the resize grip. */
     hdc = BeginPaint(hwnd, &ps);
     if(sizegrip)
       DrawFrameControl(hdc, GetSizeGripRect(hwnd,&r), DFC_SCROLL, DFCS_SCROLLSIZEGRIP);
     EndPaint(hwnd, &ps);
     *retval = 0;
     return TRUE;

   case WM_GETMINMAXINFO:
     GetWindowRect(hwnd, &rw);
     GetClientRect(hwnd, &rc);
     ((LPMINMAXINFO)lParam)->ptMinTrackSize.x = resizer->minSize.x + RectWidth(rw) - RectWidth(rc);
     ((LPMINMAXINFO)lParam)->ptMinTrackSize.y = resizer->minSize.y + RectHeight(rw) - RectHeight(rc);
     *retval = 0;
     return TRUE;
     
   case WM_SIZE:
     if(wParam != SIZE_MINIMIZED) {
       int cx = LOWORD(lParam);
       int cy = HIWORD(lParam);
       if(sizegrip) {
	 InvalidateRect(hwnd, GetSizeGripRect2(resizer->curSize.x,resizer->curSize.y), TRUE);
	 InvalidateRect(hwnd, GetSizeGripRect2(cx,cy), TRUE);
       }
       g2pvt_resizer_resize(resizer,cx,cy);
     }
     *retval = 0;
     return TRUE;
  }
  return FALSE;
}
