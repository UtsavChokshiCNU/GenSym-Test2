
/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	Native Dialog Manager Factory Interface - DialogManagerFactory.java
 *
 *
 */

package com.gensym.dlgruntime;

import com.gensym.ntw.TwAccess;

public interface DialogManagerFactory {
  public DialogManager makeDialogManager(TwAccess connection);
}
