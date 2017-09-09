package com.gensym.uitools.palettes;

import com.gensym.clscupgr.gfr.*;
import com.gensym.ntw.util.*;
import com.gensym.util.*;
import com.gensym.ui.*;
import com.gensym.jgi.*;
import com.gensym.ntw.*;
import com.gensym.message.Trace;
import com.gensym.clscupgr.gfr.*;
import com.gensym.util.symbol.G2ClassSymbols;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Entity;
import com.gensym.message.Resource;

import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class GFRColumnPalette extends GFRPalette {

  private boolean layoutSet = false;
  private int numberOfCols = 1;
  private int counter = 0;
  private java.awt.GridBagLayout gridBag;
  private java.awt.GridBagConstraints constraints;

  public GFRColumnPalette (String name,
			   TwAccess context,
			   KbWorkspace paletteWksp) throws G2AccessException {
    super (name, context, paletteWksp);
  }

  private void setLayout(int numberOfCols) {
    gridBag = new java.awt.GridBagLayout();
    setLayout(gridBag);
    if (numberOfCols > 0) this.numberOfCols = numberOfCols;
    constraints = new java.awt.GridBagConstraints();
    constraints.gridwidth = this.numberOfCols;
    constraints.weightx = 1.0;
    constraints.insets = new java.awt.Insets(1, 1, 1, 1);
    constraints.ipadx = 1;
    constraints.anchor = java.awt.GridBagConstraints.CENTER;
    invalidate();
  }

  @Override
  public java.awt.Component add(java.awt.Component c){
    if (!layoutSet) {
      layoutSet = true;
      setLayout(3);
    } 
    if (c instanceof JToggleButton){
      counter++;
      JToggleButton button = (JToggleButton)c;
      if (counter % numberOfCols == 0) 
	constraints.gridwidth = constraints.REMAINDER;
      else constraints.gridwidth = numberOfCols;
      gridBag.setConstraints(button, constraints);
      super.add(button);
      //System.out.println("Add button to Palette");
      invalidate();
      return button;
    }
    else return super.add(c);
  }
}


