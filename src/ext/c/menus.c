/*-*- Mode: C++ -*-*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      menus.c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):
 +              2002,2004             fmw
 +
 + Description:  Win32 native menus for G2
 +
 + Dependencies:
 +
 + Notes:
 +
 + Modifications:
 +   21-Mar-04    Created from twpro.c
 +
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#ifndef CODEJOCK		// Temporary, eases debugging link problems.

#include <stdio.h>
#include <windows.h>

#include "msincls.h"
#include "cprim.h"
#include "networks.h"
#include "netevent.h"
#include "graphics.h"

/* Various externs which ought to be in an include file. */

extern void g2pvt_enqueue_display_event();
extern void g2pvt_update_statusbar_visibility(void);
extern void g2pvt_destroy_native_icon_imagelists(BOOL destroy);

extern HMENU hMenuInit;
extern HMENU hMenuInitWindow;
extern HMENU hMenuInitView;
extern HMENU hMenuInitHelp;
extern HMENU hMenuBar;
extern HMENU hViewMenu;
extern HMENU hWindowMenu;
extern HMENU hHelpMenu;
extern HMENU dummyMenuBar; /* Only Win32 menus need this, but msmain references it. */
extern long nms_menu_bar_handle;
extern BOOL bViewStatusbar;

#ifdef GENFLEX
extern void (*g2ext_nms_append_menu_callback)(long, long, long, long,
		      long, LPWSTR, long, long);

extern void (*g2ext_nms_create_menu_callback)(long, long, long);

extern void (*g2ext_nms_destroy_menu_callback)(long, long, long);

extern void (*genflex_menus_g2ext_nms_delete_menu_items_callback)(long, long);

extern void (*g2ext_nms_set_menu_callback)(long, long, long); 

extern BOOL (*genflex_TrackPopupMenu_callback)(HMENU, UINT,	int, int, int, HWND, CONST RECT*);

extern long (*genflex_g2ext_create_logbook_callback)(int, LPWSTR,
			    long, long, long, long,
			    long, long);

extern long (*genflex_g2ext_manage_logbook_callback)(long, long, long, long, LPWSTR);

extern long (*genflex_g2ext_manage_extended_logbook_callback)(long, long, long, long, LPWSTR,
                                                              long, LPWSTR, LPWSTR,
                                                              LPWSTR, LPWSTR, LPWSTR,
                                                              long);


extern long (*genflex_g2ext_create_property_grid)(int, LPWSTR, long, long, long, long, long, long);

extern long (*genflex_g2ext_manage_property_grid)(long, long, long, long, long, LPWSTR, LPWSTR, long, double);

extern long (*genflex_g2ext_nms_enable_menu_item)(long, long, long);
#endif

#define PTRACE G2TRACE




/*
 * Support Routines
 */

static int tracking_popup_menu_p = 0;
static HMENU tracked_popup_menu = (HMENU)0;

static void reclaim_g2_menu_item(G2_MENU_ITEM* item)
{
  if(item == NULL) return;
  item->magic = 0;
  free(item);
}

/* Reclaim a menu item. A no-op except for our special owner-drawn items. */
static int reclaim_associated_structures_for_menu_item(HMENU menu, int tag, int by_position_p)
{
  MENUITEMINFO mii; 

  /* FIXME: reclaim bitmap if MF_BITMAP. */

  ZeroMemory(&mii,sizeof(MENUITEMINFO));
  mii.cbSize = sizeof(MENUITEMINFO);
  mii.fMask = MIIM_TYPE | MIIM_DATA;
  if(GetMenuItemInfo(menu, tag, by_position_p, &mii) && (mii.fType & MFT_OWNERDRAW))
    reclaim_g2_menu_item((G2_MENU_ITEM*) mii.dwItemData);
  return mii.fType;
}

/*
 * Pre-NMS menus
 */

/* g2ext_begin_item_menu makes a new, empty pop-up menu, and returns
   it as pointer.  It should be added to with
   g2ext_add_to_item_menu, et al. */
long
g2ext_begin_item_menu(void)
{
  HMENU menu = CreatePopupMenu();
  if(menu == NULL) {
    fprintf(stderr, "Failed to create popup menu: %s\n", g2pvt_get_last_error_string());
    return -1;
  }
  return g2ext_cache_cpointer((long)menu);
}

void g2pvt_menu_size(int menu_size) {}

/* g2ext_add_string_to_item_menu adds string as a menu choice.
   Supplied item ID must be >=1 . */

//Changes for gensym-872 2010/01/29
long
g2ext_add_string_to_item_menu(long popup_menu_index, LPCWSTR string, long id, long options)
{
  HMENU popup_menu = (HMENU)g2ext_map_g2pointer_to_cpointer(popup_menu_index);
  int item_id = WM_USER + 100 + id;
  G2_MENU_ITEM *item;
  UINT flags = 0;
  
  if (!(options & 2)) flags |= MF_OWNERDRAW;

  /* FIXME: allocate these items from a resource, or,
   * pass one in from LISP. */

  if (flags & MF_OWNERDRAW) {
	  item = MakeInstance(G2_MENU_ITEM);
	  item->magic = G2_MENU_ITEM_MAGIC;
	  item->flags = G2M_TEXT;
	  item->string = string;	/* Owned by LISP. */
	  item->fg = (COLORREF)-1;
	  item->bg = (COLORREF)-1;
	  AppendMenuW(popup_menu, flags, item_id, (LPCWSTR)item);
  } else
	  AppendMenuW(popup_menu, flags, item_id, string);
  return id;
}

//long
//g2ext_add_string_to_item_menu(long popup_menu_index, LPCWSTR string, long id, long options)
//{
//  HMENU popup_menu = (HMENU)g2ext_map_g2pointer_to_cpointer(popup_menu_index);
//  int item_id = WM_USER + 100 + id; /* Wrong. WM_USER is in the WM numberspace, 
//				       not the ID numberspace. */
//  UINT flags = MF_STRING;
//
//  if(options & 2) flags = MF_SEPARATOR;
//  if(options & 1) flags |= MF_MENUBREAK;
//
//  AppendMenuW(popup_menu, flags, item_id, string);
//
//  return id;
//}
//End of changes

//Changes for gensym-872 2010/01/29 
/* Add a string with fg and bg colors. */
long
g2ext_add_color_string_to_item_menu(long popup_menu_index, LPCWSTR string, long id,
				    long options, long fg, long bg)
{
  HMENU popup_menu = (HMENU)g2ext_map_g2pointer_to_cpointer(popup_menu_index);
  int item_id = WM_USER + 100 + id;
  G2_MENU_ITEM *item;
  UINT flags = MF_OWNERDRAW;

#ifndef GENFLEX
  if(options & 1) flags |= MF_MENUBREAK;
#endif

  /* FIXME: allocate these items from a resource, or,
   * pass one in from LISP. */
  item = MakeInstance(G2_MENU_ITEM);
  item->magic = G2_MENU_ITEM_MAGIC;
  item->flags = G2M_FOREGROUND | G2M_BACKGROUND | G2M_TEXT;
  item->string = string;	/* Owned by LISP. */
  item->fg = (COLORREF)fg;
  item->bg = (COLORREF)bg;
  AppendMenuW(popup_menu, flags, item_id, (LPCWSTR)item);
  return id;
}
//long
//g2ext_add_color_string_to_item_menu(long popup_menu_index, LPCWSTR string, long id,
//				    long options, long fg, long bg)
//{
//  HMENU popup_menu = (HMENU)g2ext_map_g2pointer_to_cpointer(popup_menu_index);
//  int item_id = WM_USER + 100 + id;
//  G2_MENU_ITEM *item;
//  UINT flags = MF_OWNERDRAW;
//
//  if(options & 1) flags |= MF_MENUBREAK;
//
//  /* FIXME: allocate these items from a resource, or,
//   * pass one in from LISP. */
//  item = MakeInstance(G2_MENU_ITEM);
//  item->magic = G2_MENU_ITEM_MAGIC;
//  item->flags = G2M_BLACK_LINE | G2M_FOREGROUND | G2M_BACKGROUND | G2M_TEXT;
//  item->string = string;	/* Owned by LISP. */
//  item->fg = (COLORREF)fg;
//  item->bg = (COLORREF)bg;
//
//  AppendMenuW(popup_menu, flags, item_id, (LPCWSTR)item);
//
//  return id;
//}
//End of changes

//Changes for gensym-872 2010/01/29
/* Add a submenu as an item.  The submenu must first have been created with
   a call to g2ext_begin_item_menu */
long
g2ext_add_submenu_to_item_menu(long popup_menu_index, LPCWSTR string, long submenu_index,
							   long options)
{
	HMENU popup_menu = (HMENU)g2ext_map_g2pointer_to_cpointer(popup_menu_index);
	HMENU submenu = (HMENU)g2ext_map_g2pointer_to_cpointer(submenu_index);
	G2_MENU_ITEM *item;
	UINT flags = MF_OWNERDRAW | MF_POPUP;
	//if(options & 1) flags |= MF_MENUBREAK;
	item = MakeInstance(G2_MENU_ITEM);
	item->magic = G2_MENU_ITEM_MAGIC;
	item->flags = G2M_TEXT;
	item->string = string;	/* Owned by LISP. */
	item->fg = (COLORREF)-1;
	item->bg = (COLORREF)-1;
	AppendMenuW(popup_menu, flags, (UINT_PTR)submenu, (LPCWSTR)item);
	return submenu_index;
}
//long
//g2ext_add_submenu_to_item_menu(long popup_menu_index, LPCWSTR string, long submenu_index,
//							   long options)
//{
//	HMENU popup_menu = (HMENU)g2ext_map_g2pointer_to_cpointer(popup_menu_index);
//	HMENU submenu = (HMENU)g2ext_map_g2pointer_to_cpointer(submenu_index);
//	UINT flags =  MF_STRING|MF_POPUP;
//
//	if(options & 1) flags |= MF_MENUBREAK;
//
//	AppendMenuW(popup_menu, flags, (UINT_PTR)submenu, string);
//	return submenu_index;
//}
//End of changes


/* Modally tracks the menu and returns ID of item chosen, or 0 if cancelled.
   x,y, are the window (as opposed to screen) coordinates at which to popup */
long
g2ext_choose_from_item_menu(long window_index, long popup_menu_index, long x, long y)
{
  HWND hwnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
  HMENU hmenu = (HMENU)g2ext_map_g2pointer_to_cpointer(popup_menu_index);
  int item_id;
  POINT pt;

  if(tracking_popup_menu_p) return 0; /* Actually, cannot happen, but check anyways */

  tracking_popup_menu_p = TRUE;
  tracked_popup_menu = hmenu;

  pt.x = x; pt.y = y;
  ClientToScreen(hwndCoor, &pt);
	
#ifndef GENFLEX
  item_id = TrackPopupMenu(hmenu, TPM_RETURNCMD | TPM_RIGHTBUTTON, pt.x, pt.y, 0, hwndFrame, NULL);
#else
  //Changes for gensym-872 2010/01/29
  item_id = genflex_TrackPopupMenu_callback(hmenu, TPM_RETURNCMD | TPM_RIGHTBUTTON, pt.x, pt.y, 0, hwnd, NULL);
  //End of changes
#endif

  tracking_popup_menu_p = FALSE;

  g2pvt_enqueue_display_event(); /* Seems to be needed for NIP. */

  if(item_id == 0)
    return 0;			/* Cancelled */
  else
    return item_id - WM_USER - 100;
}


/* Reclaim any menu item structures associated with given menu.
 * DestroyMenu recursively destroys all of the submenus in menu,
 * so we can't call it unless we've got the top-level menu in
 * hand. top_level_p must be true only for the last call. */
long
g2ext_reclaim_item_menu(long menu_index, long top_level_p)
{
  HMENU menu = (HMENU)g2ext_map_g2pointer_to_cpointer(menu_index);
  int i;

  g2ext_decache_g2pointer(menu_index);

  for(i=0; i<GetMenuItemCount(menu); i++)
    reclaim_associated_structures_for_menu_item(menu, i, TRUE);

  if(top_level_p)
    DestroyMenu(menu);
  return 0;
}

/**********************************************************************
 * NMS (Native Menu System) routines 
 **********************************************************************/

/* Forward refs */
long g2ext_nms_set_menu(long window_index, long menu_index, long nms_menu_handle);
long g2ext_nms_dismiss(long window_index);

/* Return handle of submenu of menu containing an item with given ID. */
static HMENU
find_submenu(HMENU menu, UINT id)
{
  int i,j;
  HMENU submenu;

  for(i=0; i<GetMenuItemCount(menu); i++) {
    submenu = GetSubMenu(menu,i);
    if(submenu != NULL) {
      for(j=0; j<GetMenuItemCount(submenu); j++)
	if(GetMenuItemID(submenu,j) == id)
	  return submenu;
    }
  }
  return NULL;
}

long
g2ext_nms_create_menu(long popup_p, unsigned short *result)
{
#ifdef GENFLEX
	long g2pointer;
#endif

  HMENU menu = popup_p ? CreatePopupMenu() : CreateMenu();

  if(menu == NULL) {
    fprintf(stderr, "Failed to create NMS menu: %s\n", g2pvt_get_last_error_string());
    result[0] = 0;
    result[1] = 0;
    return -1;
  }

  /* Return Win32 HMENU handle to lisp. This was added solely to support dynamic
   * NMS menus: the WM_INITMENUPOPUP message we receive contains only the HMENU
   * of the menu to display. LISP has to map that back to an NMS handle, in
   * order to ask G2 to compute the items.  G2 only knows about NMS handles. See
   * LISP nms-handle-if-dynamic and C on_initmenupopup. */

  result[0] = HIWORD((long)menu);
  result[1] = LOWORD((long)menu);

#ifdef GENFLEX
  g2pointer = g2ext_cache_cpointer((long)menu);

  g2ext_nms_create_menu_callback(g2pointer, (long)menu, popup_p);

  return g2pointer;
#else
  return g2ext_cache_cpointer((long)menu);
#endif
}



long
g2ext_nms_append_menu(long menu_index, long flags, long id, long submenu_index,
		      long wide, LPWSTR label, long fg, long bg)
{
  HMENU menu = (HMENU)g2ext_map_g2pointer_to_cpointer(menu_index);
  UINT_PTR item_id = (flags&MF_POPUP) ? g2ext_map_g2pointer_to_cpointer(submenu_index) : id;
  G2_MENU_ITEM *info;
  LPCWSTR item;
  int rc;

#ifdef GENFLEX
    g2ext_nms_append_menu_callback(menu_index, flags, id, submenu_index,
		      wide, label, fg, bg);
#endif

  PTRACE("g2ext_nms_append_menu(%d, 0x%0x, %d, %d, %d, %ls, %d, %d)\n",
	  menu_index, flags, id, submenu_index, wide, label, fg, bg);

  if(wide) flags |= MF_OWNERDRAW;

  if(flags & MF_OWNERDRAW) {
    info = MakeInstance(G2_MENU_ITEM);
    info->magic = G2_MENU_ITEM_MAGIC;
    if(wide)
      info->flags |= G2M_WIDE;
    if(flags & MF_SEPARATOR)
      info->flags |= G2M_SEPARATOR;

    info->flags |= G2M_TEXT;
    info->string = label;	/* Owned by LISP. */

    if(fg >= 0) {
      info->flags |= G2M_FOREGROUND;
      info->fg = (COLORREF)fg;
    }
    if(bg >= 0) {
      info->flags |= G2M_BACKGROUND;
      info->bg = (COLORREF)bg;
    }

    item = (LPCWSTR)info;
    PTRACE(" info->flags 0x%0x\n", info->flags);
  } else {
    item = label;
  }

  rc = AppendMenuW(menu, flags, item_id, item);
  if(rc == 0)
   fprintf(stderr, "AppendMenuW failed: %s\n", g2pvt_get_last_error_string());
  return rc;
}

long
g2ext_nms_destroy_menu(long window_index, long menu_index, long recurse_p)
{
  HWND hwnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
  HMENU menu = (HMENU)g2ext_map_g2pointer_to_cpointer(menu_index);
  int i, flags;
  LPG2INFO info;

#ifdef GENFLEX
  g2ext_nms_destroy_menu_callback(window_index, menu_index, recurse_p);
#endif

  /* Should not happen, but might as well check. */
  if(menu == hMenuInit || menu == hMenuInitWindow || menu == hMenuInitView)
    return -1;

  if(menu == hViewMenu)   hViewMenu = NULL;
  if(menu == hWindowMenu) hWindowMenu = NULL;
  if(menu == hHelpMenu) hHelpMenu = NULL;

  /* If deleting a menu currently being tracked, first dismiss the menu. */
  if(tracking_popup_menu_p && (menu == tracked_popup_menu))
    g2ext_nms_dismiss(window_index);

  /* If we're destroying the current menu bar, then remove the menu bar
   * entirely. We're assuming that this menu cannot be the menu bar of any other
   * MDI child. */

  info = GetlpG2Info(hwnd);
  if(info->mdi_menu_index == menu_index) {
    info->mdi_menu_index = -1;
    info->mdi_menu_nms_handle = -1;
  }

  if(menu == GetMenu(hwndFrame))            /* Deleting current menu bar: remove it. */
    g2ext_nms_set_menu(window_index, -2, -1);

  /* Loop over all menu items reclaiming G2_MENU_ITEM structures,
   * if any, and removing submenu items if we are NOT recursing. */

  /* TODO: I think this fails to reclaim associated structures in submenus. */
  for(i=GetMenuItemCount(menu)-1; i>=0; i--) {
    flags = reclaim_associated_structures_for_menu_item(menu, i, TRUE);
    if(recurse_p==0 && (flags & MF_POPUP))
      RemoveMenu(menu, i, MF_BYPOSITION);
  }

  DestroyMenu(menu);		/* Recurses to submenus. */
  DrawMenuBar(hwndFrame);
  g2ext_decache_g2pointer(menu_index); // FIXME: Do this for all submenus, too.
  return 1;
}


/* Returns TRUE if the POS-th item in MENU is one of the special items added by
 * MDI when a child window is maximized. */

static BOOL special_mdi_menu_item_p(HMENU menu, int pos)
{
  int id, maximized;

  if(!Frame_is_MDI)
    return FALSE;

  if(menu != GetMenu(hwndFrame))
    return FALSE;

  maximized = 0;
  if(!SendMessage(hwndClient, WM_MDIGETACTIVE, 0, (LPARAM)&maximized))
    return FALSE;

  if(maximized == 0)
    return FALSE;

  /* TODO: Could check that the submenu contains SC_RESTORE, etc. */
  if(pos == 0 && GetSubMenu(menu,pos))
    return TRUE;

  /* TODO: Could check that pos here is one of the last three items. */
  id = GetMenuItemID(menu,pos);
  if(id == SC_MINIMIZE || id == SC_RESTORE || id == SC_CLOSE)
    return TRUE;
  return FALSE;
}


/* Delete all of the items in given menu, recursively deleting
 * submenus and their items. The menu itself remains valid, though empty. */
static void delete_menu_items(HMENU menu)
{
  int i;
  HMENU submenu;

  for(i=GetMenuItemCount(menu)-1; i>=0; i--) {
    if(special_mdi_menu_item_p(menu, i))     /* Leave special MDI items alone. */
      continue;
    reclaim_associated_structures_for_menu_item(menu, i, TRUE);
    submenu = GetSubMenu(menu,i);
    RemoveMenu(menu, i, MF_BYPOSITION);
    if(submenu != NULL) {
      delete_menu_items(submenu);
      DestroyMenu(submenu);
    }
  }
}

long
g2ext_nms_delete_menu_items(long window_index, long menu_index)
{
  HWND hwnd = (HWND)g2ext_map_g2pointer_to_cpointer(window_index);
  HMENU menu = (HMENU)g2ext_map_g2pointer_to_cpointer(menu_index);

#ifdef GENFLEX
  genflex_menus_g2ext_nms_delete_menu_items_callback(window_index, menu_index);
#endif

  /* Should not happen, but might as well check. */
  if(menu == hMenuInit || menu == hMenuInitWindow || menu == hMenuInitView)
    return -1;

  delete_menu_items(menu);
  return 1;
}


long g2ext_nms_remove_menu_item(long menu_index, long item)
{
  HMENU menu = (HMENU)g2ext_map_g2pointer_to_cpointer(menu_index);

  reclaim_associated_structures_for_menu_item(menu, item, FALSE);
  RemoveMenu(menu, item, MF_BYCOMMAND);
  DrawMenuBar(hwndFrame);	/* Needed? */
  return 1;
}

long
g2ext_nms_check_menu_item(long menu_index, long item, long flags)
{
  HMENU menu = (HMENU)g2ext_map_g2pointer_to_cpointer(menu_index);
  return CheckMenuItem(menu, item, flags);
}

long g2ext_nms_check_radio_item(long menu_index, long first, long last, long check, long flags)
{
  HMENU menu = (HMENU)g2ext_map_g2pointer_to_cpointer(menu_index);

  PTRACE("g2ext_nms_check_radio_item(%d, %d, %d, %d, 0x%x)\n",
	 menu_index, first, last, check, flags);

  return CheckMenuRadioItem(menu, first, last, check, flags);
}

long g2ext_nms_enable_menu_item(long menu_index, long item, long flags)
{
  HMENU menu = (HMENU)g2ext_map_g2pointer_to_cpointer(menu_index);

  int rc = EnableMenuItem(menu, item, flags);

#ifdef GENFLEX
   //MessageBox(0, "enablOrdis", "eee", 0);
  MENUITEMINFO info;
  memset(&info, 0, sizeof(MENUITEMINFO));
  info.cbSize = sizeof(MENUITEMINFO);
  info.fMask = MIIM_ID;
  GetMenuItemInfo(menu, item, TRUE, &info);
	genflex_g2ext_nms_enable_menu_item(menu_index, info.wID, flags);
#endif

  if(rc == -1)
    fprintf(stderr, "Warning: menu 0x%0x item %d flags 0x%0x not found.\n",
	    menu, item, flags);

  /* If the menu bar was affected, redraw it. */
  if(menu == GetMenu(hwndFrame))
    DrawMenuBar(hwndFrame);
  return rc;
}

/* Returns TRUE if menus require "width maintenance", ie, whether the WIDE
 * argument to g2ext_nms_modify_menu_item does anything. */
long g2ext_nms_width_maintainance_p(void)
{
  return 1;
}

/* Only used by XTP */
long g2ext_nms_set_help(long menu_index, long nID, LPWSTR new_help)
{
  return 0;
}

/* Set the label and colors of an item. The item is OWNERDRAW iff it has
 * non-default colors or an icon. A default color is indicated by -1 for either
 * fg or bg. */
long g2ext_nms_modify_menu_item(long menu_index, long id, long pos, long wide,
				long new_label_p, LPWSTR new_label, long new_fg, long new_bg,
				long new_icon)
{
  HMENU menu = (HMENU)g2ext_map_g2pointer_to_cpointer(menu_index);
  MENUITEMINFO mii; 
  G2_MENU_ITEM *info;
  UINT_PTR newID;
  LPCWSTR newItem;
  int flags = MF_BYPOSITION, mask, state;
  int become_ownerdraw = wide || (new_fg>=0) || (new_bg>=0) || (new_icon>=0);
  int was_ownerdraw;

  PTRACE("g2ext_nms_modify_menu_item(%d, %d, %d, %d, \"%ls\", %x, %x, icon=0x%0x\n",
	  menu_index, id, pos, wide, new_label ? new_label : L"(none)", new_fg, new_bg, new_icon);

  state = GetMenuState(menu, pos, MF_BYPOSITION);

  ZeroMemory(&mii,sizeof(MENUITEMINFO));
  mii.cbSize = sizeof(MENUITEMINFO);
  mii.fMask = MIIM_TYPE | MIIM_DATA | MIIM_SUBMENU | MIIM_ID;
  if(state == -1 || (!GetMenuItemInfo(menu, pos, TRUE, &mii))) {
    fprintf(stderr,
	    "Warning: cannot find menu item at pos %d in menu [%d] (%d items)\n",
	    pos, menu_index, GetMenuItemCount(menu));
    return -1;
  }

  if(mii.hSubMenu != NULL) {
    flags |= MF_POPUP;
    newID = (UINT_PTR) mii.hSubMenu;
    state = LOBYTE(state);	/* Only low byte is valid if opens a submenu. */
  }
  else
    newID = mii.wID;

  was_ownerdraw = (mii.fType & MFT_OWNERDRAW);

  if(become_ownerdraw) {
    info = was_ownerdraw ? ((G2_MENU_ITEM*) mii.dwItemData) : MakeInstance(G2_MENU_ITEM);
    info->magic = G2_MENU_ITEM_MAGIC;
    info->flags = 0;
    if(wide)
      info->flags |= G2M_WIDE;
    if(new_fg>=0) {
      info->flags |= G2M_FOREGROUND;
      info->fg = (COLORREF) new_fg;
    }
    if(new_bg>=0) {
      info->flags |= G2M_BACKGROUND;
      info->bg = (COLORREF) new_bg;
    }
    if(new_icon>=0) {
      info->flags |= G2M_ICON | G2M_WIDE;
      info->icon = new_icon;
    }
    if(new_label != NULL && wcslen(new_label) > 0) {
      info->flags |= G2M_TEXT;
      info->string = new_label;
    }
    if(mii.fType & MFT_SEPARATOR)
      info->flags |= G2M_SEPARATOR;

    flags |= MF_OWNERDRAW;
    newItem = (LPCWSTR) info;

    PTRACE(" info->flags 0x%0x\n", info->flags);

  } else {
    if(was_ownerdraw)
      reclaim_g2_menu_item((G2_MENU_ITEM*) mii.dwItemData);
    newItem = new_label;
  }

  /* We want to preserve all of the state bits of the menu item, 
     except for the MF_OWNERDRAW bit, which may be changing. */
  mask = MF_OWNERDRAW;
  flags = (flags&mask) | (state&~mask) | MF_BYPOSITION;

  PTRACE(" ModifyMenuW(0x%0x, %d, 0x%0x, %d, 0x%0x)\n", menu, pos, flags, newID, newItem);

  if(ModifyMenuW(menu, pos, flags, newID, newItem) == 0)
    fprintf(stderr, "ModifyMenu failed: %s\n", g2pvt_get_last_error_string());

  DrawMenuBar(hwndFrame);
  return 1;
}

static void set_menu_internal(HWND hwnd, HMENU menu, HMENU winmenu)
{
  if(Frame_is_MDI)
    SendMessage(hwnd, WM_MDISETMENU, (WPARAM)menu, (LPARAM)winmenu);
  else
    SetMenu(hwnd,menu);
}

/* Makes main frame window's menu bar be menu. If menu_index is -1, revert to default
 * twpro menu bar. If -2, remove the menu bar.  Top-level entries in the menu bar named
 * "View" and "Window", if any, have a special status.
 * Don't call this unless hwnd is the active MDI child! */
long
g2pvt_set_menu(HWND hwnd, long menu_index, long nms_menu_handle)
{
  HMENU menu = NULL;
  HMENU viewmenu = NULL;
  HMENU winmenu = NULL;
  HMENU helpmenu = NULL;

  if(menu_index >= 0) {
    menu = (HMENU) g2ext_map_g2pointer_to_cpointer(menu_index);
    viewmenu = find_submenu(menu, TWPRO_STATUSBAR); /* Find menus via command IDs. */
    winmenu  = find_submenu(menu, TWPRO_CLOSE);
    helpmenu = find_submenu(menu, TWPRO_HELP);
  }
  else if(menu_index == -1) {
    menu = hMenuInit;
    viewmenu = hMenuInitView;
    winmenu = hMenuInitWindow;
    helpmenu = hMenuInitHelp;
  }

  if(!Frame_is_MDI)
    set_menu_internal(hwndFrame, menu, NULL); // SetMenu(hwndFrame,menu)

  else if(menu != NULL)
    set_menu_internal(hwndClient, menu, winmenu); // SetMenu(hwndFrame,menu)

  else if (GetMenu(hwndFrame) != NULL) { /* Request to hide menu bar. */
    if(dummyMenuBar == NULL)
      dummyMenuBar = CreateMenu();
    /* We need to use MDISETMENU here in order for MDI to remove any minimize,
     * etc, icons from the menu bar. Unfortunately, MDISETMENU does not provide
     * any way to completely hide the menu bar, so we MDISETMENU to a dummy
     * menu, then do a SetMenu NULL to hide the menu bar This fixes
     * HQ-4432673. -fmw, 10/29/02 */

    /* Apparently, we can't destroy the dummy menu because MDI has moved the
     * system menu for the maximized child into it, and if we destroy dummy it
     * will destroy the system menu, too.  This is what caused the system menu
     * to stop functioning after doing a hide and show menu bar when a child is
     * maximized. I thought that I could destroy it once we've MDISETMENU'd a
     * new menu, but that seemed to break things, too. It appears to work OK,
     * and not leak, if we just keep the dummy menu around until we exit.
     * -fmw, 8/21/03 */
    SendMessage(hwndClient, WM_MDISETMENU, (WPARAM)dummyMenuBar, (LPARAM)NULL);
    SetMenu(hwndFrame, NULL);
  }

  /* MDI needs to know the window menu, if any.  Other msmain code needs to
   * know the view menu, if any. */
  hMenuBar = menu;
  nms_menu_bar_handle = nms_menu_handle;
  hViewMenu = viewmenu;
  hWindowMenu = winmenu;
  hHelpMenu = helpmenu;

  /* Check or uncheck items as needed, to reflect the current state. */
  if(viewmenu != NULL) {
    g2pvt_update_statusbar_visibility();
  }
  DrawMenuBar(hwndFrame);
  return 1;
}

/* The function g2ext_nms_set_menu() sets the menu bar to be associated with the
 * window corresponding to window_index.  The window can either be the frame,
 * client, or a child window, and, if a child, is assumed to be active.  This
 * sets frame's menu bar and saves the index away for reuse when a child window
 * become reactivated.  */
long
g2ext_nms_set_menu(long window_index, long menu_index, long nms_menu_handle)
{
  HWND hwnd = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
  LPG2INFO info;

#ifdef GENFLEX
  g2ext_nms_set_menu_callback(window_index, menu_index, nms_menu_handle);
#endif

  info = GetlpG2Info(hwnd);
  if(info == NULL) {
    fprintf(stderr, "set_menu: Null window info\n");
  } else {
    info->mdi_menu_index = menu_index;
    info->mdi_menu_nms_handle = nms_menu_handle;
  }

  g2pvt_set_menu(hwnd, menu_index, nms_menu_handle);
  return 1;
}

/* Modally tracks the menu and enqueues a WM_COMMAND for the ID of item chosen, or NMS_NO_CHOICE
 * if cancelled. x,y, are the window (as opposed to screen) coordinates at which to 
 * popup.  The menu's top-center is centered on x,y. */
long
g2ext_nms_pop_up_menu(long window_index, long menu_handle, long menu_index, long x, long y)
{
  HWND  hwnd = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
  HMENU menu = (HMENU)g2ext_map_g2pointer_to_cpointer(menu_index);
  POINT pt;
  int choice;
  int flags = TPM_RETURNCMD | TPM_RIGHTBUTTON | TPM_CENTERALIGN | TPM_TOPALIGN;

  if(tracking_popup_menu_p) return NMS_NO_CHOICE; /* Actually, cannot happen, but check anyways */
  tracking_popup_menu_p = TRUE;
  tracked_popup_menu = menu;

  pt.x = x; pt.y = y;
  ClientToScreen(hwndCoor, &pt);

  choice = TrackPopupMenu(menu, flags, pt.x, pt.y, 0, hwndFrame, NULL);

  tracking_popup_menu_p = FALSE;

  if(choice == 0) choice = NMS_NO_CHOICE;
  PostMessage(hwndFrame, WM_NMS_MENU_CHOICE, choice, menu_handle);
  return choice;
}

/* Deexposes any NMS pop-up or drop-down menus, and exits any modal menu context. */
long g2ext_nms_dismiss(long window_index)
{
  HWND hwnd = (HWND) g2ext_map_g2pointer_to_cpointer(window_index);
  /* The send to hwnd gets any popups on the G2 window. The send to hwndFrame
   * gets any pulldowns on the menu bar or the system menu.
   * What about popups on sibling G2 windows? I think we do the right thing here,
   * actually, which is to only cancel popups if on our own window. */
  SendMessage(hwnd, WM_CANCELMODE, 0, 0);
  SendMessage(hwndFrame, WM_CANCELMODE, 0, 0);
  return 1;
}



/*
 * Native Icons
 */

void g2pvt_refresh_native_icon(int handle, int where)
{
  if(handle==0 && where==0) {	/* Compatibility with old G2's */
    DrawMenuBar(hwndFrame);
    return;
  }

  if(where & 0x01)		/* MenuBar */
    DrawMenuBar(hwndFrame);

  if(where & 0x02)		/* MDI child windows */
    g2pvt_refresh_mdi_child_icon(handle);

  if(where & 0x04)		/* Dialog windows */
    g2pvt_refresh_dialog_icon(handle);
}

void g2pvt_destroy_native_icons(BOOL destroy)
{
  g2pvt_destroy_native_icon_imagelists(destroy);
}



/*
 * Native MDI Child Windows
 */

HWND g2pvt_create_workspace_view(long handle, HWND client, LPWSTR title, DWORD style, RECT* r)
{
  return CreateMDIWindowW((LPWSTR)GensymWorkspaceViewClass, title, style,
			  r->left, r->top, r->right-r->left, r->bottom-r->top,
			  client, hInst, (LPARAM)handle);
}

void g2pvt_set_workspace_view_background_color(HWND hwnd, COLORREF color) {}

/*
 * Tabbed MDI Mode (TWNG Only)
 */

long g2ext_tabbed_mdi_mode(long opcode, long arg) {
  return -1;
}



/*
 * MDI Dialogs
 */

HWND g2pvt_bless_mdi_child(HWND hwnd, int handle)
{
  return hwnd;			// The TWNG version ensures an MFC frame for hwnd.
}

int g2pvt_show_dialog_in_pane(HWND hwndDlg, int handle,
			      int x, int y, int width, int height,
			      int dock, int neighborID, int icon)
{
  return -1;
}



/* Also see "get-local-ui-toolkit-name" (native-tw.lisp) -- binghe, 2009/7/9 */
long g2ext_nms_get_toolkit(void)
{
#ifndef GENFLEX
  return 1;			/* Win32 (TW) */
#else
  return 3;			/* GenFlex */
#endif
}

/*
 * Win32 stubs
 */

long g2ext_nms_append_control(long menu_index, long control_index, long flags) {return -1;}
long g2ext_nms_manage_control(long control_index, long opcode) {return -1;}
long g2ext_nms_delete_control(long menu_index, long control_index) {return -1;}

long g2ext_nms_create_toolbar(long handle, LPWSTR name, long dock, long n, long e, long b) {return -1;}
long g2ext_nms_create_edit_box(long handle, LPWSTR name, long width, LPWSTR initial) {return -1;}
long g2ext_nms_create_combo_box(long handle, LPWSTR name, long width, LPWSTR initial,
				LPWSTR choices, long flags,
				long drop_down_width) {return -1;}
long g2ext_nms_set_theme(long code) {return -1;}

void g2ext_nms_set_iconsize(long iconsize) {return;}

long g2ext_manage_pane(long opcode, long handle, 
		       long x, long y, long width, long height, LPWSTR string)
{return -1;}

long g2ext_create_tree_view(int handle, LPWSTR title,
			    long x, long y, long width, long height,
			    long dock, long neighbor)
{return -1;}

long g2ext_manage_tree_view(long opcode, long handle, LPWSTR string, long flags,
			    long x, long y, long width, long height, long lParam,
			    long parent)
{return -1;}

long g2ext_create_html_view(long handle, LPWSTR title, LPWSTR url,
			    long x, long y, long width, long height, long dock, long neighbor)
{return -1;}

long g2ext_manage_html_view(long opcode, long handle, LPWSTR url)
{return -1;}

long g2ext_create_shortcut_bar(long handle, long style, long obstyle, LPWSTR title,
			       long x, long y, long width, long height,
			       long dock, long neighborID)
{return -1;}

long g2ext_manage_shortcut_bar(long opcode, long handle, LPWSTR string, 
			       long nFolder, long icon, long userdata)
{return -1;}

long g2ext_create_logbook(int handle, LPWSTR title,
			    long x, long y, long width, long height,
			    long dock, long neighbor, long logbookType)
{
#ifdef GENFLEX
	return genflex_g2ext_create_logbook_callback(handle, title,
			    x, y, width, height,
			    dock, neighbor);
#else
	return -1;
#endif
}

long g2ext_manage_logbook(long opcode, long handle, long msgNum, long date, LPWSTR string)
{
#ifdef GENFLEX
	return genflex_g2ext_manage_logbook_callback(opcode, handle, msgNum, date, string);
#else
	return -1;
#endif
}

long g2ext_manage_extended_logbook(long opcode, long handle, long msgNum, long date, 
                                   LPWSTR string, long message_type,
                                   LPWSTR workspace_uuid, LPWSTR workspace_name,
                                   LPWSTR object_uuid, LPWSTR object_type, LPWSTR object_name, 
                                   long line_number)
{
#ifdef GENFLEX
  return genflex_g2ext_manage_extended_logbook_callback(opcode, handle, msgNum, date, 
                                                        string, message_type, 
                                                        workspace_uuid, workspace_name,
                                                        object_uuid, object_type, object_name,
                                                        line_number);
#else
  return -1;
#endif
}


long g2ext_create_property_grid(int handle, LPWSTR title,
			    long x, long y, long width, long height,
			    long dock, long neighbor)
{
#ifdef GENFLEX
	return genflex_g2ext_create_property_grid(handle, title,
			    x, y, width, height,
			    dock, neighbor);
#else
	return -1;
#endif
}

/* NOTE: Victor Kazarinov @ 2009-07-10: when I create here ifdef for GenFlex I foinded that
   this manage function parameters is differs from TWNG function parameters. May be this
   stub here is have wrong parameters?

   NOTE: Chun Tian (binghe) @ 2009-07-10: By checking original declaration on G2 server
   side, I'm sure the original parameters of this function here is WRONG. So we correct it. */

long g2ext_manage_property_grid(long opcode, long handle, 
				long node, long type, long parent, LPWSTR caption,
				LPWSTR strValue, long intValue, double floatValue)
{
#ifdef GENFLEX
	return genflex_g2ext_manage_property_grid(opcode, handle, 
				node, type, parent, caption,
				strValue, intValue, floatValue);
#else
	return -1;
#endif
}

long g2ext_create_tabular_view(int handle, LPWSTR title,
			       long x, long y, long width, long height,
			       long dock, long neighbor,
				   int sortColumn, BOOL sortAscending)
{return -1;}

long g2ext_manage_tabular_view(long opcode, long handle, long rowID,
			       LPWSTR strValue, long argA, long argB, long argC)
{return -1;}

#endif
