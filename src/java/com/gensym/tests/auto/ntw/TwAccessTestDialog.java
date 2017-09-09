/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TwAccessTestDialog.java
 *
 */
package com.gensym.tests.auto.ntw;

import java.awt.Button;
import java.awt.Checkbox;
import java.awt.CheckboxGroup;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.GridLayout;
import java.awt.Insets;
import java.awt.Panel;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.Vector;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.jgi.G2AccessException;
import com.gensym.mdi.MDIFrame;
import com.gensym.ntw.TwAccess;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.tests.auto.DialogUtils;
import com.gensym.tests.auto.TestDialog;
import com.gensym.tests.auto.TestUtils;
import com.gensym.tests.auto.LogWindow;

public class TwAccessTestDialog extends TestDialog {
  public static final int CREATE_ITEM_PANEL = 1;
  private Vector createdItems = null;
  private LogWindow lw;

  //Symbol KBWORKSPACE_ = Symbol.intern("KB-WORKSPACE");

  public Checkbox getCreatePassedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "createPassed");
    return (Checkbox)control;
  }

  public Checkbox getCreateFailedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "createFailed");
    return (Checkbox)control;
  }

  public Checkbox getCreateUntestedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "createUntested");
    return (Checkbox)control;
  }

  public Checkbox getClonePassedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "clonePassed");
    return (Checkbox)control;
  }

  public Checkbox getCloneFailedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "cloneFailed");
    return (Checkbox)control;
  }

  public Checkbox getCloneUntestedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "cloneUntested");
    return (Checkbox)control;
  }

  public Checkbox getDisablePassedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "disablePassed");
    return (Checkbox)control;
  }

  public Checkbox getDisableFailedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "disableFailed");
    return (Checkbox)control;
  }

  public Checkbox getDisableUntestedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "disableUntested");
    return (Checkbox)control;
  }

  public Checkbox getEnablePassedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "enablePassed");
    return (Checkbox)control;
  }

  public Checkbox getEnableFailedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "enableFailed");
    return (Checkbox)control;
  }

  public Checkbox getEnableUntestedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "enableUntested");
    return (Checkbox)control;
  }

  public Checkbox getDeletePassedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "deletePassed");
    return (Checkbox)control;
  }

  public Checkbox getDeleteFailedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "deleteFailed");
    return (Checkbox)control;
  }

  public Checkbox getDeleteUntestedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "deleteUntested");
    return (Checkbox)control;
  }

  // BEGIN: createCreateItemPanel
  private Panel createCreateItemPanel(){
    Panel panel = new Panel();
    panel.setName("createItemPanel");

    GridBagLayout gridBag = new GridBagLayout ();
    GridBagConstraints gridC = new GridBagConstraints ();
   
    panel.setLayout (gridBag);

    gridC.insets = new Insets (10,10,0,10);
    gridC.fill = GridBagConstraints.BOTH;
    gridC.weightx = 1.0;

    gridC.gridwidth = GridBagConstraints.REMAINDER; 

    // add the create Item Checkbox
    Checkbox cb1 = DialogUtils.addCheckboxToPanel(panel, "Create Item", gridBag, gridC);
    cb1.addItemListener (new ItemListener (){
      @Override
      public void itemStateChanged (ItemEvent event){
	if ((event.getStateChange()) == ItemEvent.SELECTED){
	  boolean status = runCreateItemTest();
	  Checkbox cb = getCreatePassedCB();
	  CheckboxGroup createCBG = cb.getCheckboxGroup();
	  if (createCBG != null){
	    if (status)
	      cb = getCreatePassedCB();
	    else
	      cb = getCreateFailedCB();
	  createCBG.setSelectedCheckbox(cb);
	  }
	}
      }
    }
    );

    gridC.insets = new Insets (0, 30, 0, 0);
    panel.setLayout(new GridLayout(3, 1));  
    CheckboxGroup cbg = new CheckboxGroup();
    Checkbox create1 = (Checkbox)add(new Checkbox("passed", cbg, false));
    create1.setName("createPassed");
    Checkbox create2 = (Checkbox)add(new Checkbox("failed", cbg, false));
    create2.setName("createFailed");
    Checkbox create3 = (Checkbox)add(new Checkbox("untested", cbg, true));
    create3.setName("createUntested");
    DialogUtils.addCheckboxToPanel(panel, create1, gridBag, gridC);
    DialogUtils.addCheckboxToPanel(panel, create2, gridBag, gridC);
    gridC.insets = new Insets (0, 30, 10, 0);
    DialogUtils.addCheckboxToPanel(panel, create3, gridBag, gridC);
    panel.setLayout (gridBag);
    gridC.insets = new Insets (0, 10, 0, 0);

    // add the Clone Item Checkbox
    Checkbox cb2 = DialogUtils.addCheckboxToPanel(panel, "Clone Item", gridBag, gridC);
    cb2.addItemListener (new ItemListener (){
      @Override
      public void itemStateChanged (ItemEvent event){
        if ((event.getStateChange()) == ItemEvent.SELECTED){
	        boolean status = runCloneItemTest();
	        Checkbox cb = getClonePassedCB();
	        CheckboxGroup cloneCBG = cb.getCheckboxGroup();
	        if (cloneCBG != null){
	          if (status)
	            cb = getClonePassedCB();
	          else
	            cb = getCloneFailedCB();
	        cloneCBG.setSelectedCheckbox(cb);
	        }
	      }
      }
    });  
	   
    gridC.insets = new Insets (0, 30, 0, 0);
    panel.setLayout(new GridLayout(3, 1));  
    cbg = new CheckboxGroup();
    Checkbox clone1 = (Checkbox)add(new Checkbox("passed", cbg, false));
    clone1.setName("clonePassed");
    Checkbox clone2 = (Checkbox)add(new Checkbox("failed", cbg, false));
    clone2.setName("cloneFailed");
    Checkbox clone3 = (Checkbox)add(new Checkbox("untested", cbg, true));
    clone3.setName("cloneUntested");
    DialogUtils.addCheckboxToPanel(panel, clone1, gridBag, gridC);
    DialogUtils.addCheckboxToPanel(panel, clone2, gridBag, gridC);
    gridC.insets = new Insets (0, 30, 10, 0);
    DialogUtils.addCheckboxToPanel(panel, clone3, gridBag, gridC);
    panel.setLayout (gridBag);
    gridC.insets = new Insets (0, 10, 0, 0);
  
    // add the Enable Item Checkbox
    Checkbox cb3 = DialogUtils.addCheckboxToPanel(panel, "Enable Item", gridBag, gridC);
    cb3.addItemListener (new ItemListener (){
      @Override
      public void itemStateChanged (ItemEvent event){
        if ((event.getStateChange()) == ItemEvent.SELECTED){
	        boolean status = runEnableItemTest();
	        Checkbox cb = getEnablePassedCB();
	        CheckboxGroup enableCBG = cb.getCheckboxGroup();
	        if (enableCBG != null){
	          if (status)
	            cb = getEnablePassedCB();
	          else
	            cb = getEnableFailedCB();
	        enableCBG.setSelectedCheckbox(cb);
	        }
	      }
      }
    });  
	   
    gridC.insets = new Insets (0, 30, 0, 0);
    panel.setLayout(new GridLayout(3, 1));  
    cbg = new CheckboxGroup();
    Checkbox enable1 = (Checkbox)add(new Checkbox("passed", cbg, false));
    enable1.setName("enablePassed");
    Checkbox enable2 = (Checkbox)add(new Checkbox("failed", cbg, false));
    enable2.setName("enableFailed");
    Checkbox enable3 = (Checkbox)add(new Checkbox("untested", cbg, true));
    enable3.setName("enableUntested");
    DialogUtils.addCheckboxToPanel(panel, enable1, gridBag, gridC);
    DialogUtils.addCheckboxToPanel(panel, enable2, gridBag, gridC);
    gridC.insets = new Insets (0, 30, 10, 0);
    DialogUtils.addCheckboxToPanel(panel, enable3, gridBag, gridC);
    panel.setLayout (gridBag);
    gridC.insets = new Insets (0, 10, 0, 0);

    // add the Disable Item Checkbox
    Checkbox cb4 = DialogUtils.addCheckboxToPanel(panel, "Disable Item", gridBag, gridC);
    cb4.addItemListener (new ItemListener (){
      @Override
      public void itemStateChanged (ItemEvent event){
        if ((event.getStateChange()) == ItemEvent.SELECTED){
	        boolean status = runDisableItemTest();
	        Checkbox cb = getDisablePassedCB();
	        CheckboxGroup disableCBG = cb.getCheckboxGroup();
	        if (disableCBG != null){
	          if (status)
	            cb = getDisablePassedCB();
	          else
	            cb = getDisableFailedCB();
	        disableCBG.setSelectedCheckbox(cb);
	        }
	      }
      }
    });  
	   
    gridC.insets = new Insets (0, 30, 0, 0);
    panel.setLayout(new GridLayout(3, 1));  
    cbg = new CheckboxGroup();
    Checkbox disable1 = (Checkbox)add(new Checkbox("passed", cbg, false));
    disable1.setName("disablePassed");
    Checkbox disable2 = (Checkbox)add(new Checkbox("failed", cbg, false));
    disable2.setName("disableFailed");
    Checkbox disable3 = (Checkbox)add(new Checkbox("untested", cbg, true));
    disable3.setName("disableUntested");
    DialogUtils.addCheckboxToPanel(panel, disable1, gridBag, gridC);
    DialogUtils.addCheckboxToPanel(panel, disable2, gridBag, gridC);
    gridC.insets = new Insets (0, 30, 10, 0);
    DialogUtils.addCheckboxToPanel(panel, disable3, gridBag, gridC);
    panel.setLayout (gridBag);
    gridC.insets = new Insets (0, 10, 0, 0);
  
    // add the delete Item Checkbox
    Checkbox cb5 = DialogUtils.addCheckboxToPanel(panel, "Delete Item", gridBag, gridC);
    cb5.addItemListener (new ItemListener (){
      @Override
      public void itemStateChanged (ItemEvent event){
	      if ((event.getStateChange()) == ItemEvent.SELECTED){
	        boolean status = runDeleteItemTest();
	        Checkbox cb = getDeletePassedCB();
	        CheckboxGroup deleteCBG = cb.getCheckboxGroup();
	        if (deleteCBG != null){
	          if (status)
	            cb = getDeletePassedCB();
	          else
	            cb = getDeleteFailedCB();
	        deleteCBG.setSelectedCheckbox(cb);
	        }
	      }
      }
    });

    gridC.insets = new Insets (0, 30, 0, 0);
    panel.setLayout(new GridLayout(3, 1));  
    cbg = new CheckboxGroup();
    Checkbox delete1 = (Checkbox)add(new Checkbox("passed", cbg, false));
    delete1.setName("deletePassed");
    Checkbox delete2 = (Checkbox)add(new Checkbox("failed", cbg, false));
    delete2.setName("deleteFailed");
    Checkbox delete3 = (Checkbox)add(new Checkbox("untested", cbg, true));
    delete3.setName("deleteUntested");
    DialogUtils.addCheckboxToPanel(panel, delete1, gridBag, gridC);
    DialogUtils.addCheckboxToPanel(panel, delete2, gridBag, gridC);
    gridC.insets = new Insets (0, 30, 10, 0);
    DialogUtils.addCheckboxToPanel(panel, delete3, gridBag, gridC);
    panel.setLayout (gridBag);
    gridC.insets = new Insets (0, 10, 0, 0);

    gridC.insets = new Insets (0, 30, 0, 0);
    Button more = new Button("More Item Methods...");
    more.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
        TwAccessTestSizeDialog twd =
          new TwAccessTestSizeDialog(getAppFrame(), "Testing Resize Methods", false, 
                               2,lw, getConnectionManager(), createdItems);
        twd.show();
      }
    });
    panel.add (more);

    return panel;
  }
  // END: createCreateItemPanel

  // BEGIN: runCreateItemTest
  public boolean runCreateItemTest(){
    boolean status = true;

    // create Vector of possible items types and create instances of each
    createdItems = TestUtils.setupAndCreateItems(getConnectionManager());
  
    // for every item that was successfully created, transfer it to the view
    TwAccess context = getConnectionManager().getCurrentConnection();
    Rectangle bounds = null;
    KbWorkspace kbWksp = getWorkspaceView().getWorkspace();
    try {
      bounds = ((com.gensym.classes.ImplAccess)kbWksp).getBounds();
    }
    catch (G2AccessException ex){
      System.out.println(ex.getMessage());
    }
    int midX = (int)(bounds.x + (bounds.width/2));
    int midY = (int)(bounds.y - (bounds.height/2));
    //Vector createdItems = getCreatedItems();
    for (int i = 0; i<createdItems.size(); i++){
      try {
	context.transferItem((Item)createdItems.elementAt(i), kbWksp,
			     midX, midY,
			     Boolean.FALSE, Boolean.FALSE);
      }
      catch (G2AccessException ex){
	System.out.println(ex.getMessage());
      }
    }
  
    System.out.println("***** DONE with Create Item Test *****");

    return status;
  }
  // END: runCreateItemTest
  public boolean runCloneItemTest(){
    boolean status = true;
    TwAccess context = getConnectionManager().getCurrentConnection();

    Rectangle bounds = null;
    KbWorkspace kbWksp = getWorkspaceView().getWorkspace();
    try {
      bounds = ((com.gensym.classes.ImplAccess)kbWksp).getBounds();
    }
    catch (G2AccessException ex){
      System.out.println(ex.getMessage());
    }
    int cloneX = (int)(bounds.x + (bounds.width/4));
    int cloneY = (int)(bounds.y - (bounds.height/4));

    lw.setText("In runCloneItemTest\n");
    for (int i=0; i<createdItems.size(); i++){
      try {
        lw.setText("Attempting to clone: " + ((Item)(createdItems.elementAt(i))).toString()+"\n");
        System.out.println("cloning [" + (Item)(createdItems.elementAt(i)) + "]");
	      Item itemCloned = context.cloneItem((Item)(createdItems.elementAt(i)));
	      context.transferItem((Item)itemCloned, kbWksp, cloneX, cloneY,
			           Boolean.FALSE, Boolean.FALSE);
        lw.setText(((Item)(createdItems.elementAt(i))).toString()+" cloned\n");
      }
      catch (G2AccessException ex){
	      System.out.println(ex.getMessage());
        lw.setText(ex.getMessage());
      }
    }

    System.out.println("***** DONE with Clone Item Test *****");

    return status;
  }

  public boolean runDisableItemTest(){
    boolean status = true;
    TwAccess context = getConnectionManager().getCurrentConnection();
    lw.setText("In runDisableItemTest\n");

    for (int i = 0; i<createdItems.size(); i++){
      try {
	      boolean t = context.disableItem((Item)(createdItems.elementAt(i)));
        if (t)
          lw.setText(((Item)(createdItems.elementAt(i))).toString()+" disabled\n");
        else
          lw.setText(((Item)(createdItems.elementAt(i))).toString()+" failed\n");
      }
      catch (G2AccessException ex){
	      System.out.println(ex.getMessage());
      }
    }

    System.out.println("***** DONE with Disable Item Test *****");

    return status;
  }  

  public boolean runEnableItemTest(){
    boolean status = true;
    TwAccess context = getConnectionManager().getCurrentConnection();

    lw.setText("In runEnableItemTest\n");
    for (int i = 0; i<createdItems.size(); i++){
      try {
	      boolean t = context.enableItem((Item)(createdItems.elementAt(i)));
        if (t)
          lw.setText(((Item)(createdItems.elementAt(i))).toString()+" enabled\n");
        else
          lw.setText(((Item)(createdItems.elementAt(i))).toString()+" failed\n");
      }
      catch (G2AccessException ex){
	      System.out.println(ex.getMessage());
      }
    }

    System.out.println("***** DONE with Enable Item Test *****");

    return status;
  }  

  public boolean runDeleteItemTest(){
    boolean status = true;
    TwAccess context = getConnectionManager().getCurrentConnection();

    for (int i = 0; i<createdItems.size(); i++){
      try {
	      //((Item)(createdItems.elementAt(i))).delete(true, false);
        //TwAccess.deleteItem is broken as of Feb 10, 98.
        boolean t = context.deleteItem((Item)(createdItems.elementAt(i)));
        System.out.println("deleted " + (Item)(createdItems.elementAt(i)));
      }
      catch (G2AccessException ex){
	      System.out.println(ex.getMessage());
      }
    }

    System.out.println("***** DONE with Delete Item Test *****");

    return status;
  }  

  public TwAccessTestDialog (MDIFrame parentFrame, String title, boolean isModal, int panelType, LogWindow logWindow, ConnectionManager connectionManager){   
    super (parentFrame, title, isModal, connectionManager);
    lw = logWindow;
    addPanelToDialog(createCreateItemPanel());
  }
}
