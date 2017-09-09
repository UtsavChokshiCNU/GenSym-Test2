/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 BasicTreeCellRenderer.java
 *
 */
package com.gensym.ntw.util;

import java.awt.Component;
import java.awt.Color;
import java.awt.Graphics;

import javax.swing.Icon;
import javax.swing.JLabel;
import javax.swing.JTree;
import javax.swing.UIManager;
import javax.swing.tree.TreeCellRenderer;
import javax.swing.tree.DefaultMutableTreeNode;

public class BasicTreeCellRenderer extends JLabel implements TreeCellRenderer, BrowserSymbols {
 
  /** Color to use for the background when selected. */
  static protected final Color selectedBackgroundColor = UIManager.getColor("Tree.selectionBackground");
  static protected final Color selectedForegroundColor = UIManager.getColor("Tree.selectionForeground");
  static protected final Color selectedBorderColor = UIManager.getColor("Tree.selectionBorderColor");

  /** Whether or not the item that was last configured is selected. */
  protected boolean selected;
  protected boolean hasFocus;

  /**
   * This is messaged from JTree whenever it needs to get the size
   * of the component or it wants to draw it.
   * This attempts to set the font based on value, which will be
   * a TreeNode.
   */
  @Override
  public Component getTreeCellRendererComponent(JTree tree, Object value,
						boolean selected, boolean expanded,
						boolean leaf, int row, boolean hasFocus) {
    InstanceData userObject
      = (InstanceData)((DefaultMutableTreeNode)value).getUserObject();
    BasicObjectDataRenderer renderer = userObject.getRenderer();
    setToolTipText(renderer.getToolTipRepresentation());
    setFont(renderer.getFont());
    setText(renderer.getTextRepresentation());
    setIcon(renderer.getIconRepresentation());

    if (selected)
      setForeground(selectedForegroundColor);
    else
      setForeground(Color.black);
    
    /* Update the selected flag for the next paint. */
    this.selected = selected;
    this.hasFocus = hasFocus;

    return this;
  }
  
  /**
   * paint is subclassed to draw the background correctly.  JLabel
   * currently does not allow backgrounds other than white, and it
   * will also fill behind the icon.  Something that isn't desirable.
   */
  @Override
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
    int offset = 0;
    if(currentI != null && getText() != null)
      offset = (currentI.getIconWidth() + getIconTextGap());
      
    g.fillRect(offset, 0, getWidth() - 1 - offset,
	       getHeight() - 1);
    if (hasFocus){
      g.setColor(selectedBorderColor);
      g.drawRect(offset, 0, getWidth()-1-offset, getHeight()-1);
    }
    super.paint(g);
  }
}
