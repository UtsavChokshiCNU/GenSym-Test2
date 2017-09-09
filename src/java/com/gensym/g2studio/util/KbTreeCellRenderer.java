/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 KbTreeCellRenderer.java
 *
 */
package com.gensym.g2studio.util;

import com.sun.java.swing.Icon;
import com.sun.java.swing.ImageIcon;
import com.sun.java.swing.JLabel;
import com.sun.java.swing.JTree;
import com.sun.java.swing.tree.TreeCellRenderer;
import com.sun.java.swing.tree.DefaultMutableTreeNode;
import java.awt.Component;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;

public class KbTreeCellRenderer extends JLabel implements TreeCellRenderer {
  /** Font used if the string to be displayed isn't a module */
  static protected Font defaultFont;
  /** Font used if the string to be displayed is a module */
  static protected Font moduleFont;
  /** Icon to use when the item is collapsed. */
  static protected ImageIcon collapsedIcon;
    /** Icon to use when the item is expanded. */
  static protected ImageIcon expandedIcon;

  /** Color to use for the background when selected. */
  static protected final Color selectedBackgroundColor = Color.blue;
  static protected final Color selectedForegroundColor = Color.white;

  static
  {
    try {
      defaultFont = new Font("SansSerif", Font.PLAIN, 12);
    } catch (Exception e) {}
    try {
      moduleFont = new Font("SansSerif", Font.BOLD, 12);
    } catch (Exception e) {}
    try {
      collapsedIcon = new ImageIcon("images/collapsed.gif");
      expandedIcon = new ImageIcon("images/expanded.gif");
    } catch (Exception e) {
      System.out.println("Couldn't load images: " + e);
    }
  }
  
  /** Whether or not the item that was last configured is selected. */
  protected boolean selected;
  
  /**
   * This is messaged from JTree whenever it needs to get the size
   * of the component or it wants to draw it.
   * This attempts to set the font based on value, which will be
   * a TreeNode.
   */
  public Component getTreeCellRendererComponent(JTree tree, Object value,
						boolean selected, boolean expanded,
						boolean leaf, int row,
						boolean hasFocus) {
    Font font;
    String stringValue = tree.convertValueToText(value, selected,
						 expanded, leaf, row, hasFocus);

    /* Set the text. */
    setText(stringValue);
    /* Tooltips used by the tree. */
    setToolTipText(stringValue);

    /* Set the image. */
    if(expanded)
      setIcon(expandedIcon);
    else if(!leaf)
      setIcon(collapsedIcon);
    else
      setIcon(null);
    
    /* Set the color and the font based on the KbData userObject. */
    KbData userObject = (KbData)((DefaultMutableTreeNode)value).getUserObject();
    if (userObject.getDataType() == KbData.G2_MODULE) {
      setFont(moduleFont);
    } else {
      setFont(defaultFont);
    }

    if (selected)
      setForeground(selectedForegroundColor);
    else
      setForeground(Color.black);
    
    /* Update the selected flag for the next paint. */
    this.selected = selected;
    
    return this;
  }
  
  /**
   * paint is subclassed to draw the background correctly.  JLabel
   * currently does not allow backgrounds other than white, and it
   * will also fill behind the icon.  Something that isn't desirable.
   */
  public void paint(Graphics g) {
    Color bColor, fColor;
    Icon currentI = getIcon();
    
    if (selected) {
      bColor = selectedBackgroundColor;
      fColor = selectedForegroundColor;
    }
    else if(getParent() != null)
      /* Pick background color up from parent (which will come from
	 the JTree we're contained in). */
      bColor = getParent().getBackground();
    else
      bColor = getBackground();
    g.setColor(bColor);
    if(currentI != null && getText() != null) {
      int offset = (currentI.getIconWidth() + getIconTextGap());
      
      g.fillRect(offset, 0, getWidth() - 1 - offset,
		 getHeight() - 1);
    } else
      g.fillRect(0, 0, getWidth()-1, getHeight()-1);
    super.paint(g);
  }
}
