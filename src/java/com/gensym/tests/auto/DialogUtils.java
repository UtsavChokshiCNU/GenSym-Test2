/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DialogUtils.java
 *
 */
package com.gensym.tests.auto;

import java.awt.Button;
import java.awt.Checkbox;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Label;
import java.awt.List;
import java.awt.Panel;
import java.awt.Point;
import java.awt.TextArea;
import java.awt.TextField;

public abstract class DialogUtils {
  // BEGIN: findComponentByName
  public static Component findComponentByName (Container container, String name){
    Component control = null;
    int numControls = container.getComponentCount();
    if (numControls > 0){
      Component[] controls = container.getComponents();
      for (int i=0; i<numControls; i++){
	if (controls[i].getName().equals(name)){
	  control = controls[i];
	}
      }
    }

    if (control == null)
      System.out.println("ERROR in DialogUtils: unable to find component: " + name);

    return control;
  }
  // END: findComponentByName
  
  // BEGIN: convenience methods for dealing with GridBagConstraints
  public static Button addButton (Container container, String label, GridBagLayout gridBag, GridBagConstraints gridC){
    Button button = new Button (label);
    gridBag.setConstraints (button, gridC);
    container.add(button);
    return button;
  }

  public static Checkbox addCheckbox (Container container, String label, GridBagLayout gridBag, GridBagConstraints gridC){
    Checkbox button = new Checkbox (label);
    gridBag.setConstraints (button, gridC);
    container.add(button);
    return button;
  }

  public static TextField addTextField (Container container, String text, int len, GridBagLayout gridBag, GridBagConstraints gridC){
    TextField textF = new TextField (text, len);
    gridBag.setConstraints (textF, gridC);
    container.add(textF);
    return textF;
  }

  public static Label addLabel (Container container, String text, GridBagLayout gridBag, GridBagConstraints gridC){
    Label lab = new Label (text);
    gridBag.setConstraints (lab, gridC);
    container.add (lab);
    return lab;
  }

  public static TextArea addTextArea (Container container, String text, int numRows, int numColumns, int scrollbarVisibility, GridBagLayout gridBag, GridBagConstraints gridC){
    TextArea textArea = new TextArea (text, numRows, numColumns,
				      scrollbarVisibility);
    gridBag.setConstraints (textArea, gridC);
    container.add(textArea);
    return textArea;
  }

  public static List addList (Container container, GridBagLayout gridBag, GridBagConstraints gridC){
    List list = new List(6, false);
    gridBag.setConstraints (list, gridC);
    container.add(list);
    return list;
  }

  public static void addPanel (Container container, Panel subPanel, GridBagLayout gridBag, GridBagConstraints gridC){
    gridBag.setConstraints (subPanel, gridC);
    container.add (subPanel);
  }

  public static Checkbox addCheckboxToPanel (Panel panel, String label, GridBagLayout gridBag, GridBagConstraints gridC){
    Checkbox button = new Checkbox (label);
    gridBag.setConstraints (button, gridC);
    panel.add(button);
    return button;
  }

  public static void addCheckboxToPanel (Panel panel, Checkbox cb, GridBagLayout gridBag, GridBagConstraints gridC){
    gridBag.setConstraints (cb, gridC);
    panel.add(cb);
  }

  public static void addLabelToPanel (Panel panel, String labelString, GridBagLayout gridBag, GridBagConstraints gridC){
    Label label = new Label(labelString);
    gridBag.setConstraints(label, gridC);
    panel.add(label);
  }

  public static List addListToPanel (Panel panel, GridBagLayout gridBag, GridBagConstraints gridC){
    List list = new List(6, false);
    gridBag.setConstraints (list, gridC);
    panel.add(list);
    return list;
  }

  public static TextField addTextFieldToPanel (Panel panel, int numColumns, GridBagLayout gridBag, GridBagConstraints gridC){
    TextField tf = new TextField(numColumns);
    gridBag.setConstraints (tf, gridC);
    panel.add(tf);
    return tf;
  }
  // END: convenience methods for dealing with GridBagConstraints

  public static void setBoundsForCenter (Frame parentFrame, Component component){
    // make this dialog come up in the center of the application frame
    Dimension frameSize = parentFrame.getSize();
    Point     frameLoc  = parentFrame.getLocation();
    Dimension mySize    = component.getSize();
    int       x,y;
      
    x = frameLoc.x + (frameSize.width/2) -(mySize.width/2);
    y = frameLoc.y + (frameSize.height/2)-(mySize.height/2);
    component.setBounds (x, y, mySize.width, mySize.height);
  }
}
