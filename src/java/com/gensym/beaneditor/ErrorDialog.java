/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *   Error Dialog - ErrorDialog.java
 *
 *
 *   Modifications:
 *
 */

package com.gensym.beaneditor;

import java.awt.Button;
import java.awt.Dialog;
import java.awt.Frame;
import java.awt.Label;
import java.awt.Panel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

/** This class can be used to display an error message to the user.  The dialog
 * can be made modal, and will return control to the application after it is 
 * dismissed
 */
class ErrorDialog extends Dialog implements ActionListener, WindowListener
{
  /** Constructor for this class
   */
  public ErrorDialog(Frame frame, String message, int x, int y, boolean isModal)
  {
    super(frame, "Error", isModal);

    Label  messageLabel = new Label(message);
    messageLabel.setAlignment(Label.CENTER);
    Button okButton = new Button("OK");
    Panel okPanel = new Panel();
    okPanel.add(okButton);
       
    add("Center", messageLabel);
    add("South", okPanel);
    okButton.addActionListener(this);      
         
    pack();
    setLocation(x - getSize().width/2, y - getSize().height/2);

    setResizable(false);
    addWindowListener(this);

    setVisible(true);        
  }

  public ErrorDialog(Frame frame, String message, int x, int y)
  {
    this(frame, message, x, y, true);
  }


  // Action event
  @Override
  public void actionPerformed (ActionEvent e)
  {
    dispose();
  }
   
  // Window events
  @Override
  public void windowOpened(WindowEvent e)
  {
  }

  @Override
  public void windowClosing(WindowEvent e)
  {
    e.getWindow().dispose();
  }

  @Override
  public void windowClosed(WindowEvent e)
  {
  }

  @Override
  public void windowIconified(WindowEvent e)
  {
  }

  @Override
  public void windowDeiconified(WindowEvent e)
  {
  }

  @Override
  public void windowActivated(WindowEvent e)
  {
  }

  @Override
  public void windowDeactivated(WindowEvent e)
  {
  }


}

