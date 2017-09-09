package com.gensym.beaneditor;

import java.awt.Panel;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Color;
import java.awt.Graphics;

class BeanStatusBar extends Panel
{
  
  private Dimension preferredSize = new Dimension (100, 20);
  private Font stdFont = new Font ("Dialog", Font.PLAIN, 12);

  private String initialStatus = "Ready";
  private String currentStatus = initialStatus;
  private String pageName = "";
  
  public BeanStatusBar ()
  {
    setBackground (Color.lightGray);
  }
  
  @Override
  public Dimension getPreferredSize ()
  {
    return preferredSize;
  }
  
  @Override
  public void paint (Graphics g)
  {
    g.setFont (stdFont);
    int width = getSize().width;
    g.drawString(currentStatus, 10, 15);
    if (!pageName.equals("")){
      String formattedPageName = "["+pageName+"]";
      int msgWidth = g.getFontMetrics().stringWidth(formattedPageName); 
      g.drawString (formattedPageName, width-msgWidth-5, 15);
    }
  }

  public void setPageName(String name){
    if (name == null)
      pageName = "";
    else
      pageName = name;
    repaint();
  }

  public void setStatus(String newStatus){
    currentStatus = newStatus;
    repaint();
  }
  
  public void resetStatus ()
  {
    currentStatus = initialStatus;
    repaint ();
  }


}
