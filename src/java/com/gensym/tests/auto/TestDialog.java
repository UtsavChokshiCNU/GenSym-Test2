/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TestDialog.java
 *
 */
package com.gensym.tests.auto;

import java.awt.Button;
import java.awt.Component;
import java.awt.Dialog;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.awt.Panel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.beans.PropertyVetoException;
import java.util.Vector;
import com.gensym.mdi.MDIDocument;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIManager;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.tests.auto.DialogUtils;
import com.gensym.util.Symbol;
import com.gensym.wksp.WorkspaceView;

public abstract class TestDialog extends Dialog {
  private static final boolean debugCreate = false;
 
  private WorkspaceView wkspView = null;
  private ConnectionManager cm = null;
  private MDIFrame appFrame = null;

  private static int dialogCloseAction = 0;
  private static final int CANCEL_ACTION = 0;
  private static final int OK_ACTION = 1;

  private Vector possibleItemTypes = null;
  private Vector createdItems = null;
 
  Symbol KBWORKSPACE_ = Symbol.intern("KB-WORKSPACE");

  public ConnectionManager getConnectionManager(){
    return cm;
  }

  public MDIFrame getAppFrame() {
    return appFrame;
  }

  public Vector getPossibleItemsTypes(){
    return possibleItemTypes;
  }

  public Vector getCreatedItems(){
    return createdItems;
  }

  public void setWorkspaceView(WorkspaceView workspaceView){
    wkspView = workspaceView;
  }

  public WorkspaceView getWorkspaceView(){
    return wkspView;
  }

  public Panel getPanelComponent(){
    Panel panel = null;
    int numControls = getComponentCount();
    if (numControls > 0){
      Component[] controls = getComponents();
      for (int i=0; i<numControls; i++){
	if (controls[i] instanceof Panel)
	  panel = (Panel)controls[i];
      }
    }
    return panel;
  }

  public void addPanelToDialog(Panel panel){
    GridBagLayout gridBag = new GridBagLayout ();
    GridBagConstraints gridC = new GridBagConstraints (); 
    setLayout (gridBag);
    gridC.gridwidth = GridBagConstraints.REMAINDER;
    DialogUtils.addPanel(this, panel, gridBag, gridC);

     //gridC.gridwidth = GridBagConstraints.REMAINDER;
    gridC.insets = new Insets (5, 5, 5, 5);
    gridC.gridwidth = GridBagConstraints.RELATIVE;
    gridC.fill = GridBagConstraints.VERTICAL;
    gridC.anchor = GridBagConstraints.EAST;
    gridC.ipadx = 60;
    
    Button okButton = DialogUtils.addButton (this, "OK", gridBag, gridC);
    okButton.setName("okButton");
    okButton.addActionListener (new  ActionListener (){
      @Override
      public void actionPerformed (ActionEvent event){
	try {
	  MDIManager manager = appFrame.getManager();
	  MDIDocument doc = manager.getActiveDocument();
	  doc.setClosed(true);
	}
	catch (PropertyVetoException ex){
	  System.out.println(ex.getMessage());
	}
	dialogCloseAction = OK_ACTION;
	dispose();
      }
    }
    );

    gridC.fill = GridBagConstraints.BOTH;
    gridC.anchor = GridBagConstraints.CENTER;
    gridC.ipadx = 0;

    Button cancelButton = DialogUtils.addButton (this, "Cancel", gridBag, gridC);
    cancelButton.setName("cancelButton");
    cancelButton.addActionListener (new  ActionListener (){
      @Override
      public void actionPerformed (ActionEvent event){	
	try {
	  MDIManager manager = appFrame.getManager();
	  MDIDocument document = manager.getActiveDocument();
	  document.setClosed(true);
	}
	catch (PropertyVetoException ex){
	  System.out.println(ex.getMessage());
	}
	dialogCloseAction = CANCEL_ACTION;
	dispose();
      }
    }
    );
   
    pack();
    DialogUtils.setBoundsForCenter(appFrame, this);
  }
  
  public TestDialog (MDIFrame parentFrame, String title, boolean isModal, ConnectionManager connectionManager){   
    super (parentFrame, title, isModal);

    cm = connectionManager;
    appFrame = parentFrame;

    addWindowListener(new WindowListener(){
      @Override
      public void windowActivated (WindowEvent event){}
      @Override
      public void windowClosed (WindowEvent event){}
      @Override
      public void windowClosing (WindowEvent event){dispose();}
      @Override
      public void windowDeactivated (WindowEvent event){}
      @Override
      public void windowDeiconified (WindowEvent event){}
      @Override
      public void windowIconified (WindowEvent event){}
      @Override
      public void windowOpened (WindowEvent event){}     
    }
    );
  }
} 
