/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DebugWindow.java
 *
 */
package com.gensym.beaneditor;

import java.awt.Dialog;
import java.awt.Button;
import java.awt.Frame;
import java.awt.Panel;
import java.awt.TextArea;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import com.gensym.beansruntime.HookupListener;
import com.gensym.beansruntime.Hookup;
import com.gensym.beansruntime.HookupEvent;

class DebugWindow extends Dialog implements HookupListener{

  private Button continueButton;
  private TextArea textArea;
  private Hookup hookup;
  private boolean step = false;
  int msgID = 0;

  DebugWindow(Frame frame){
    super(frame, "Debug", false);
    if (step){
      Panel buttonPanel = new Panel();
      continueButton = new Button("Continue");
      continueButton.setEnabled(false);
      continueButton.addActionListener(new ActionAdapter());
      buttonPanel.add(continueButton);
      add(buttonPanel, "South");
    }
    textArea = new TextArea();
    textArea.setEditable(false);
    add(textArea, "Center");
    setSize(frame.getSize().width, 200);
    setLocation(frame.getLocation().x, frame.getSize().height - 200);
  }

  @Override
  public void hookupPaused(HookupEvent e){
    hookup = (Hookup)e.getSource();
    addMessage("\nHookup class: "+hookup+"\nEvent: "+e+"\n");
    hookup.continueHookupEvent();
  }

  void clear(){
    textArea.setText("");
  }

  private void addMessage(String msg){
    if (step) continueButton.setEnabled(true);
    textArea.append ("\n" + (msgID++) + " : " + new java.util.Date ());
    textArea.append(msg);
  }

  void done(){
    if (step) continueButton.setEnabled(false);
  }

  class ActionAdapter implements ActionListener{
    @Override
    public void actionPerformed(ActionEvent event){
      hookup.continueHookupEvent();
    }
  }

}
  
