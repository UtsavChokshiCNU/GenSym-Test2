/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 BeanPalette.java
 *
 */

package com.gensym.beaneditor;

import javax.swing.JToggleButton;
import com.gensym.message.Resource;
import com.gensym.ui.ObjectCreator;
import com.gensym.ui.palette.Palette;

/** A BeanPalette is a palette for creating Java Beans. */
public class BeanPalette extends Palette{

  private Resource i18n = Resource.getBundle("com.gensym.ui.palette.Messages");

  private int numberOfCols = 1;
  private int counter = 0;
  private java.awt.GridBagLayout gridBag;
  private java.awt.GridBagConstraints constraints;

  public BeanPalette(){
    super(null);
  }

  public BeanPalette(String name){
    super(name);
  }

  public BeanPalette(String name, int numberOfCols){
    super(name);
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

  /** Checks to ensure only BeanObjectCreators are added. */
  @Override
  public void add(ObjectCreator objectCreator){
    if (!(objectCreator instanceof BeanCreator))
      throw new IllegalArgumentException(i18n.getString("BeanCreatorsOnly"));
    else super.add(objectCreator);
  }


  @Override
  public java.awt.Component add(java.awt.Component c){
    if (c instanceof JToggleButton){
      counter++;
      JToggleButton button = (JToggleButton)c;
      if (counter % numberOfCols == 0) 
	constraints.gridwidth = constraints.REMAINDER;
      else constraints.gridwidth = numberOfCols;
      gridBag.setConstraints(button, constraints);
      super.add(button);
      //System.out.println("Add button to Palette");
      return button;
    }
    else return super.add(c);
  }


}
