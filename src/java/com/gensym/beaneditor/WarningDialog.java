/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	Warning Dialog - WarningDialog.java
 *
 *
 *   Modifications:
 *
 */

package com.gensym.beaneditor;

import java.awt.*;
import java.awt.event.*;

/** This class can be used to display an Warning message to the user.  The dialog
* is modal, and will return control to the application after it is dismissed
*/
class WarningDialog extends Dialog implements ActionListener, WindowListener
{
    public static final int YES_    =  1;
    public static final int NO_     =  0;
    public static final int CANCEL_ = -1;
    
    private int     value     = -1;
    private Button  yesButton = new Button("Yes");
    private Button  noButton  = new Button("No");
 
    /** Contructor for this class
    */
    public WarningDialog(Frame frame, String message, int x, int y)
    {	        
         super(frame, "Warning", true);

         Label  messageLabel = new Label(message);
         messageLabel.setAlignment(Label.CENTER);
         
         Button cancelButton = new Button("Cancel");
         Panel  noPanel      = new Panel();

         noPanel.add(yesButton);
         noPanel.add(noButton);
         noPanel.add(cancelButton);
       
	      add("Center", messageLabel);
         add("South", noPanel);

         yesButton.addActionListener(this);
         noButton.addActionListener(this);
         cancelButton.addActionListener(this);
         
         pack();
         setLocation(x - getSize().width/2, y - getSize().height/2);

         setResizable(false);

         addWindowListener(this);
	      setVisible(true);        
    }

    /** Gets the return value for the dialog
    */
    public int getValue()
    {
       return value;
    }

    // Action event

    @Override
    public void actionPerformed (ActionEvent e)
    {
       Object source = e.getSource();

       if (source.equals(yesButton))
           value = 1;
       else if (source.equals(noButton))
           value = 0;
       else
           value = -1;

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

