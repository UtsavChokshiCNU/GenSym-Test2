/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ExitCommand.java
 *
 */
package com.gensym.tests.auto;

import java.awt.event.WindowListener;
import java.awt.event.WindowEvent;
import java.awt.event.ActionEvent;
import com.gensym.ntw.TwAccess;
import com.gensym.message.Resource;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;

/** Command to show the log window */
public class LogWindowCommand extends AbstractCommand{
  private static final String SHOW_LOG_WINDOW = "ShowLogWindow";

  private Resource i18n = Resource.getBundle("com/gensym/shell/Errors");

  LogWindow logwindow = null;

  public LogWindowCommand(LogWindow logWin){
    super(new CommandInformation[]{
      new CommandInformation(SHOW_LOG_WINDOW, true, "CommandShortResource", 
			     "CommandLongResource", null, null, null, true)});
    logwindow = logWin;
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey)){
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", cmdKey));
    } 
    logwindow.show();
    logwindow.pack();
  }
}
