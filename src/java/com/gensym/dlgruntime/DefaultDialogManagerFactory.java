
/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	Native Dialog Manager Factory - DefaultDialogManagerFactory.java
 *
 *
 */

package com.gensym.dlgruntime;

import com.gensym.ntw.TwAccess;

public class DefaultDialogManagerFactory implements DialogManagerFactory {

  @Override
  public DialogManager makeDialogManager(TwAccess connection) {
    return new DialogManager(connection);
  }
}
