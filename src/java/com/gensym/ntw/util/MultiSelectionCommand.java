/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MultiSelectionCommand.java
 *
 */

package com.gensym.ntw.util;

import com.gensym.ui.CommandInformation;

abstract class MultiSelectionCommand extends SingleSelectionCommand{

  MultiSelectionCommand(CommandInformation[] info, KbMessageTableView msgTableView){
    super(info, msgTableView);
  }

  @Override
  protected void updateAvailability(){
    for (int i=0; i<keys.length; i++)
      setAvailable(keys[i], (table.getSelectedRow() != -1));
  }

}
