/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 PromptView.java
 *
 */
package com.gensym.editor.text;

import javax.swing.JPanel;
import javax.swing.BoxLayout;
import javax.swing.border.EmptyBorder;
import javax.swing.JScrollPane;
import javax.swing.JList;
import javax.swing.ListModel;
import javax.swing.ListSelectionModel;
import javax.swing.DefaultListModel;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.ListSelectionEvent;
import java.awt.Dimension;


/**  
 * @author David McDonald
 * @version 2.0 
 * March 1999
 */

public class PromptView extends JList {

  DefaultListModel prompts;
  protected DefaultListModel getPrompts() { return prompts; }

  void setModel(DefaultListModel m) {
    super.setModel(m);
    prompts = m;
  }

  /** 
   */
  public PromptView() {
    setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
    setModel( new DefaultListModel() );
  }



  //----- operations that may be requested by the editor -----

  String getFirstItem() {
    return (String)prompts.firstElement();
  }

  String getLastItem() {
    return (String)prompts.lastElement();
  }


  //---- operations used by the PromptManager

  boolean empty() {
    return ( prompts.isEmpty() );
  }

  void clear() {
    prompts.clear();
  }

  void add(String prompt) {
    prompts.addElement(prompt);
  }

}
