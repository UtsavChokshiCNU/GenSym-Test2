/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MenuNotificationListener.java
 *
 */

package com.gensym.clscupgr.gms;

import com.gensym.jgi.G2AccessException;

public interface MenuNotificationListener {

  public void handleShowMenu(MenuNotificationEvent e)
       throws G2AccessException;
  public void handleHideMenu(MenuNotificationEvent e);
  public void handleShowSubMenu(MenuNotificationEvent e)
       throws G2AccessException;
  public void handleHideSubMenu(MenuNotificationEvent e);
  public void handleMenuRecompiled(MenuNotificationEvent e);
  public void handleCheckMenuEntry(MenuNotificationEvent e);
  public void handleUnCheckMenuEntry(MenuNotificationEvent e);

}

