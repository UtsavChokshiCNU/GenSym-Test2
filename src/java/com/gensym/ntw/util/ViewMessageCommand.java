/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ViewMessageCommand.java
 *
 */

package com.gensym.ntw.util;

import java.awt.Panel;
import java.awt.Frame;
import java.awt.Window;
import java.awt.Insets;
import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.util.Enumeration;
import javax.swing.JTextArea;
import javax.swing.JScrollPane;
import javax.swing.border.BevelBorder;
import com.gensym.ui.CommandInformation;
import com.gensym.jgi.G2AccessException;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.WarningDialog;
import com.gensym.message.Trace;
import com.gensym.classes.Message;

class ViewMessageCommand extends SingleSelectionCommand{


  private static final String VIEW_MESSAGE = "ViewMessage";

  ViewMessageCommand(KbMessageTableView msgTableView){
    super(new CommandInformation[]{
      new CommandInformation(VIEW_MESSAGE, true, shortResource, longResource, "view.gif", 
			     null, null, true)},
      msgTableView);
  }

  @Override
  public void actionPerformed(ActionEvent event){
    try{
      int selectedRow = table.getSelectedRow();
      if (selectedRow == -1) return;
      TableViewMessage viewMsg = tableView.getTableViewMessage(selectedRow);
      if (viewMsg instanceof KbMessage){
	Message message = ((KbMessage)viewMsg).getMessage();
	String text = message.getText();
	MessageDialog dlg = new MessageDialog(msgTableView, msgTableView.getParentWindow(), 
					      i18n.getString("MessageDetails"), new MessagePanel(text));
	dlg.setVisible(true);
      }
    }
    catch(G2AccessException ex){
      Trace.exception(ex);
      new CenteredWarningDialog(msgTableView, msgTableView.getParentWindow(),
				i18n.getString("ErrorTitle"), true, 
				i18n.format("CommunicationError", ex.toString()), 
				null).setVisible(true);
    }
  }

  class MessageDialog extends StandardDialog{
    private Window centerWindow;

    MessageDialog(KbMessageTableView msgTableView, Window centerWindow, String title, MessagePanel panel){
      super(msgTableView.getParentFrame(centerWindow), title, false, new String[]{DISMISS_LABEL}, 
            new int[]{DISMISS}, panel, null);
      this.centerWindow = centerWindow;
      setDefaultButton(DISMISS);
      setDefaultCloseOperation(DISPOSE_ON_CLOSE);
    }

    @Override
    protected int getButtonAlignment () {
      return CENTER;
    }

    @Override
    public void setVisible(boolean visible){
      if (visible)
	WindowUtil.centerFrame (centerWindow, this);
      show();
    }
  }
   
  class MessagePanel extends Panel{

    MessagePanel(String text){
      setLayout(new BorderLayout());
      JTextArea textArea = new JTextArea();
      textArea.setEditable(false);
      textArea.setSize(300, 200);
      textArea.setFont(table.getFont());
      textArea.setLineWrap(true);
      textArea.setWrapStyleWord(true);
      textArea.setText(text);
      JScrollPane scrollpane = new JScrollPane(textArea);
      scrollpane.setBorder(new BevelBorder(BevelBorder.LOWERED));
      add(scrollpane, BorderLayout.CENTER);
    }

    @Override
    public Insets getInsets () {
      return new Insets(10,10,10,10);
    }

  }

}
