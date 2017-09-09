/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	URL Dialog - URLDialog.java
 *
 *
 *   Modifications:
 *
 */

package com.gensym.beaneditor;

import java.awt.*;
import java.awt.event.*;
import java.net.URL;
import java.net.MalformedURLException;
import java.util.*;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;
import com.gensym.message.Message;
import com.gensym.message.MessageEvent;

/** This class can be used to 
*/
class URLDialog extends Dialog implements ActionListener, WindowListener
{
    private URL       url = null;
    private TextField urlField = new TextField("file://temp.grp");
    private Button    okButton = new Button("OK"); 
    private Button    cancelButton = new Button("Cancel");
  
   /*
    * Standard Messaging Requirements
    */

    static private Resource i18n =
                   Resource.getBundle("com.gensym.resources.Messages",
                   Locale.getDefault());

    static private int GUI_LEVEL = 2;


    /** Contructor for this class
    */
    public URLDialog(Frame frame, int x, int y)
    {	        
         super(frame, "Location", true);
      
         Panel okPanel = new Panel();

         okPanel.add(okButton);
         okPanel.add(cancelButton);
  
         add("North",  new Label("Please enter a URL for this Page Group:"));
	      add("Center", urlField);
         add("South",  okPanel);

         okButton.addActionListener(this); 
         cancelButton.addActionListener(this);
         
         pack();
         setLocation(x - getSize().width/2, y - getSize().height/2);

         addWindowListener(this);
	      setVisible(true);      
    }

    /** Gets the URL
    */
    public URL getURL()
    {
       return url;
    }

    @Override
    public Insets getInsets()
    {
       Insets insets = super.getInsets();
       insets.left  = insets.left + 5;
       insets.right = insets.right + 5;
       return insets;
    }

    // Action event

    @Override
    public void actionPerformed (ActionEvent e)
    {
       if ((e.getSource()).equals(okButton))
       {
          try
          {
             url = new URL(urlField.getText());
             dispose();
          }
          catch (MalformedURLException ex)
          {
             Message.send (new MessageEvent(GUI_LEVEL, "com.gensym.beaneditor",
                           URLDialog.class, i18n, "notAValidURL", new Object[] {}));
          }
          
       }
       else
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

