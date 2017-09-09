/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MDIStatusBar.java
 *
 */

package com.gensym.mdi;

import java.awt.Graphics;
import java.awt.Font;
import java.awt.Color;
import java.awt.Dimension;
import javax.swing.JPanel;

public class MDIStatusBar extends JPanel{
  private static final Font stdFont = new Font ("SansSerif", Font.PLAIN, 12);
  private static final Dimension preferredSize = new Dimension (100, 22);
  private String statusMessage = new String("no connection");

  public MDIStatusBar(){
  }

  @Override
  public Dimension getPreferredSize () {
    return preferredSize;
  }

  @Override
  public void paint(Graphics g){
    super.paint(g);
    int width = getSize().width;
    g.setColor (Color.gray);
    g.drawLine (0, 0, width, 0);
    g.setColor (Color.white);
    g.drawLine (0, 1, width, 1);
    g.setColor(Color.black);
    g.setFont (stdFont);
    if (statusMessage != null) {
      int msgWidth = g.getFontMetrics().stringWidth(statusMessage);
      g.drawString (statusMessage, width-msgWidth-5, 15);
    }
  }

  /** @undocumented
   *  This method is here temporarily to display the current connection*/
  public void setStatus(String msg){
    //System.out.println("setting status bar to "+msg);    
    statusMessage = msg;
    repaint();
  }


}
