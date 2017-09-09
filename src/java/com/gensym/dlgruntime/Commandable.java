/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	ItemEditor.java: Interface for custom dialogs
 *
 *     
 *   Modifications:
 *
 */


package com.gensym.dlgruntime;

import com.gensym.controls.DialogCommand;

/**
 * This interface enables easy integration with the Telewindows 2 Toolkit
 */

public interface Commandable {
  public DialogCommand getDialogCommand();
}
