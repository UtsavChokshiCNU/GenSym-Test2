/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 FieldEditListener.java
 *
 *   Description: 
 *     
 *
 *	 Author:
 *		Paul B. Konigsberg             May 98
 *
 *     
 *   Modifications:
 *
 */
package com.gensym.ntw;

import com.gensym.classes.KbWorkspace;

/**
 * Interface for FieldEditEvents
 * FieldEditEvents are generated when G2 wish perform a field edit
 * for a message on this window.
 */

public interface FieldEditListener extends java.util.EventListener {

  public void cancelFieldEdit(FieldEditEvent event);
  public void createFieldEdit(FieldEditEvent event);
  public void refreshFieldEdit(FieldEditEvent event);
  public void updateFieldEdit(FieldEditEvent event);
  public void endFieldEdit(FieldEditEvent event);
  public KbWorkspace getWorkspace();

}
