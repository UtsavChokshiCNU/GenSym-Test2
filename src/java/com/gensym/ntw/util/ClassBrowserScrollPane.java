/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ClassBrowserScrollPane.java
 *
 */
package com.gensym.ntw.util;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Enumeration;
import java.util.Vector;

import com.gensym.classes.Definition;
import com.gensym.classes.Item;
import com.gensym.classes.Kb;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Module;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.ntw.TwGateway;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.KbEvent;
import com.gensym.ntw.util.KbModuleListener;
import com.gensym.util.DefinitionEvent;
import com.gensym.util.DefinitionListener;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

import javax.swing.JFrame;
import javax.swing.JPopupMenu;
import javax.swing.JScrollPane;
import javax.swing.JTree;
import javax.swing.ToolTipManager;
import javax.swing.event.TreeModelEvent;
import javax.swing.event.TreeModelListener;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.TreePath;

public class ClassBrowserScrollPane extends BrowserScrollPane
implements DefinitionListener {

  private Symbol moduleScope = ALL_;  // NYI: a module filter for loading children, ALL_ or module name
  private Symbol baseClass   = ROOT_;

  public ClassBrowserScrollPane (TwAccess cxn, Symbol moduleScope, Symbol baseClass) {
    super(cxn);
    this.moduleScope = moduleScope;
    this.baseClass   = baseClass;
    initTree();
  }

  @Override
  protected InstanceDataFactory createInstanceDataFactory()
  {
    return new DefaultClassInstanceDataFactory();
  }

  @Override
  protected InstancePopupMenuFactory createInstancePopupMenuFactory()
  {
    return new DefaultObjectInstancePopupMenuFactory();
  }

  public Symbol getModuleScope() {
    return moduleScope;
  }

  public Symbol getBaseClass() {
    return baseClass;
  }

  @Override
  protected BasicDynamicTreeNode createRootNode() {
    InstanceData data =
      getInstanceDataFactory().createInstanceData(CLASS_HIERARCHY_);
    return new G2DefinitionDynamicTreeNode(getConnection(), data, this);
  }


  // BEGIN:: support for DefinitionListener
  @Override
  public void staticAttributeChanged (DefinitionEvent e) {
    Definition def = (Definition)e.getSource(); //e.getDefinitionOriginatingChange();
    Symbol attName_ = e.getAttributeName();
    Object newValue = e.getNewValue();
  }
  @Override
  public void classNameChanged (DefinitionEvent e) {
    Definition def = (Definition)e.getSource(); //e.getDefinitionOriginatingChange();
    //System.out.println("ClassBrowserScrollPane.classNameChanged: "+def);
  }
  @Override
  public void directSuperiorClassesChanged (DefinitionEvent e) {
    Definition def = (Definition)e.getSource(); //e.getDefinitionOriginatingChange();
    //System.out.println("ClassBrowserScrollPane.directSuperiorClassesChanged: "+def);
  }
  @Override
  public void deleted (DefinitionEvent e) {
    Definition def = (Definition)e.getSource(); //e.getDefinitionOriginatingChange();
    //System.out.println("ClassBrowserScrollPane.deleted: "+def);
  }
  @Override
  public void classInheritancePathChanged (DefinitionEvent e) {
    Definition def = (Definition)e.getSource(); //e.getDefinitionOriginatingChange();
    //System.out.println("ClassBrowserScrollPane.classInheritancePathChanged: "+def);
  } 
  @Override
  public void classSpecificAttributesChanged (DefinitionEvent e) {
    Definition def = (Definition)e.getSource(); //e.getDefinitionOriginatingChange();
    //System.out.println("ClassBrowserScrollPane.classSpecificAttributesChanged: "+def);
  }
  // END:: support for DefinitionListener

  public static void main(String[] args){
    try{
      TwAccess connection = TwGateway.openConnection("localhost", "1111");
      connection.loginSession();
      
      JFrame frame = new JFrame();
      ClassBrowserScrollPane pane = new ClassBrowserScrollPane(connection, ALL_, ROOT_);
      frame.getContentPane().add(pane, "Center");
      frame.pack();
      frame.setVisible(true);
    }
    catch(Exception ex){
      System.out.println(ex);
    }
  }

}


