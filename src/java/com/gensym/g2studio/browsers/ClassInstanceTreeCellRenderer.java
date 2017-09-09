/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ClassInstanceTreeCellRenderer.java
 *
 */
package com.gensym.uitools.browsers;

import java.awt.Component;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;

import com.gensym.classes.Block;
import com.gensym.classes.G2Definition;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Module;
import com.gensym.classes.SystemClassDefinitionImpl;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.util.Symbol;

import com.sun.java.swing.Icon;
import com.sun.java.swing.ImageIcon;
import com.sun.java.swing.JLabel;
import com.sun.java.swing.JTree;
import com.sun.java.swing.tree.TreeCellRenderer;
import com.sun.java.swing.tree.DefaultMutableTreeNode;


public class ClassInstanceTreeCellRenderer extends JLabel implements TreeCellRenderer, BrowserSymbols {
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

  private void executeDetermineToolTipText(ClassInstanceData data) {
    //setToolTipText(data.getToolTipText());

    String tooltip = "";
    Symbol name_;
    Symbol containingModule;
    int dataType = data.getDataType();
    Symbol baseClass = data.getBaseClass();
    Symbol moduleScope = data.getModuleScope();
    switch (dataType) {
    case MODULE_HIERARCHY:
      if (moduleScope.equals(ALL_))
	tooltip = "Root node for showing the entire module hierarchy";
      else
	tooltip = moduleScope.toString(); // would be nice to show requiring modules
      break;
    case WORKSPACE_HIERARCHY:
      if (moduleScope.equals(ALL_))
	tooltip = "Root node for showing entire workspace hierarchy";
      else {
	try {
	  KbWorkspace wksp = data.getKbWorkspace();
	  name_ = (Symbol)wksp.getNames();
	  if (name_ == null) name_ = DEFAULT_WORKSPACE_NAME_;
	  containingModule = wksp.getContainingModule();
	  tooltip = containingModule+":: "+name_;
	} catch (G2AccessException gae) {
	  Trace.exception(gae); 
	}
      }
      break;
    case CLASS_HIERARCHY:
      if (moduleScope.equals(ALL_)) 
	tooltip = "Root node for showing the entire class hierarchy";
      else {
	tooltip = baseClass+": a system defined class";
      }
      break;
    case KNOWLEDGE_BASE:
      tooltip = "the root for the entire knowledge-base workspace hierarchy";
      break;
    case G2_MODULE:
      Module mod = data.getModule();
      tooltip = mod.getName().toString(); // what about adding requiring modules?
      if (mod.isTopLevel())  
	tooltip = tooltip+", the top-level module";
      break;
    case G2_KB_WORKSPACE:
      try {
	KbWorkspace wksp = data.getKbWorkspace();
	name_ = (Symbol)wksp.getNames();
	if (name_ == null) name_ = DEFAULT_WORKSPACE_NAME_;
	containingModule = wksp.getContainingModule();
	tooltip = containingModule+":: "+name_;
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
      break;
    case G2_DEFINITION:
      try {
	G2Definition g2Def = data.getG2Definition();
	if (g2Def instanceof SystemClassDefinitionImpl)
	  tooltip = g2Def.getClassName()+", a system-defined class";
	else {
	  containingModule = ((Block)g2Def).getContainingModule();
	  tooltip = g2Def.getClassName()+", defined in "+containingModule;
	}
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
      break;
    }

    setToolTipText(tooltip);
  }
  
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
   
    /* Set the image. */
    if(expanded)
      setIcon(expandedIcon);
    else if(!leaf)
      setIcon(collapsedIcon);
    else
      setIcon(null);
    
    /* Set the color and the font based on the ClassInstanceData userObject. */
    ClassInstanceData userObject = (ClassInstanceData)((DefaultMutableTreeNode)value).getUserObject();

    /* set the tooltip for the node based on type etc. */
    executeDetermineToolTipText(userObject);

    int dataType = userObject.getDataType();
    if ((dataType == ClassInstanceData.G2_MODULE) || 
	(dataType == ClassInstanceData.KNOWLEDGE_BASE) ||
	((dataType == ClassInstanceData.G2_DEFINITION) && (userObject.getG2Definition() instanceof com.gensym.classes.SystemClassDefinitionImpl))) {
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
