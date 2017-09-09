/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 WorkspaceViewTestDialog.java
 *
 */
package com.gensym.tests.auto.wksp;

import java.awt.Checkbox;
import java.awt.CheckboxGroup;
import java.awt.Color;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.GridLayout;
import java.awt.Insets;
import java.awt.Panel;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.Vector;
import com.gensym.classes.Item;
import com.gensym.jgi.G2AccessException;
import com.gensym.mdi.MDIFrame;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.tests.auto.DialogUtils;
import com.gensym.tests.auto.TestDialog;
import com.gensym.tests.auto.TestUtils;
import com.gensym.wksp.WorkspaceElement;

public class WorkspaceViewTestDialog extends TestDialog {
  private static final boolean debugFind = false;

  private Vector createdItems = null;
  private Vector createdElements = null;
  private Vector addedElements = null;
  private Vector foundElements = null;

  public static final int ELEMENT_METHODS_PANEL = 1;
  public static final int COLOR_METHODS_PANEL = 2;

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

  public Checkbox getAddPassedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "addPassed");
    return (Checkbox)control;
  }

  public Checkbox getAddFailedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "addFailed");
    return (Checkbox)control;
  }

  public Checkbox getAddUntestedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "addUntested");
    return (Checkbox)control;
  }

   public Checkbox getFindPassedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "findPassed");
    return (Checkbox)control;
  }

  public Checkbox getFindFailedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "findFailed");
    return (Checkbox)control;
  }

  public Checkbox getFindUntestedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "findUntested");
    return (Checkbox)control;
  }

  public Checkbox getRemovePassedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "removePassed");
    return (Checkbox)control;
  }

  public Checkbox getRemoveFailedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "removeFailed");
    return (Checkbox)control;
  }

  public Checkbox getRemoveUntestedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "removeUntested");
    return (Checkbox)control;
  }

  // BEGIN: createElementMethodsPanel
  private Panel createElementMethodsPanel(){
    Panel panel = new Panel();
    panel.setName("elementMethodsPanel");

    GridBagLayout gridBag = new GridBagLayout ();
    GridBagConstraints gridC = new GridBagConstraints ();
   
    panel.setLayout (gridBag);

    gridC.insets = new Insets (10,10,0,10);
    gridC.fill = GridBagConstraints.BOTH;
    gridC.weightx = 1.0;

    gridC.gridwidth = GridBagConstraints.REMAINDER; 

    // add the Create Element Checkbox
    Checkbox cb1 = DialogUtils.addCheckboxToPanel(panel, "Create Element (createElement)", gridBag, gridC);
    cb1.addItemListener (new ItemListener (){
      @Override
      public void itemStateChanged (ItemEvent event){
	if ((event.getStateChange()) == ItemEvent.SELECTED){
	  boolean status = runCreateElementTest();
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
   
    // add the Add Element Checkbox
    Checkbox cb2 = DialogUtils.addCheckboxToPanel(panel, "Add Element to WorkspaceView (addElement)", gridBag, gridC);
    cb2.addItemListener (new ItemListener (){
    @Override
    public void itemStateChanged (ItemEvent event){
      if ((event.getStateChange()) == ItemEvent.SELECTED){
	  boolean status = runAddElementTest();
	  Checkbox cb = getAddPassedCB();
	  CheckboxGroup addCBG = cb.getCheckboxGroup();
	  if (addCBG != null){
	    if (status)
	      cb = getAddPassedCB();
	    else
	      cb = getAddFailedCB();
	  addCBG.setSelectedCheckbox(cb);
	  }
	}
      }
    }
    );  
	   
    gridC.insets = new Insets (0, 30, 0, 0);
    panel.setLayout(new GridLayout(3, 1));  
    cbg = new CheckboxGroup();
    Checkbox add1 = (Checkbox)add(new Checkbox("passed", cbg, false));
    add1.setName("addPassed");
    Checkbox add2 = (Checkbox)add(new Checkbox("failed", cbg, false));
    add2.setName("addFailed");
    Checkbox add3 = (Checkbox)add(new Checkbox("untested", cbg, true));
    add3.setName("addUntested");
    DialogUtils.addCheckboxToPanel(panel, add1, gridBag, gridC);
    DialogUtils.addCheckboxToPanel(panel, add2, gridBag, gridC);
    gridC.insets = new Insets (0, 30, 10, 0);
    DialogUtils.addCheckboxToPanel(panel, add3, gridBag, gridC);
    panel.setLayout (gridBag);
    gridC.insets = new Insets (0, 10, 0, 0);

    // Add the Find Element Checkbox
    Checkbox cb3 = DialogUtils.addCheckboxToPanel(panel, "Find Element on WorkspaceView (findElement)", gridBag, gridC);
    cb3.addItemListener (new ItemListener (){
      @Override
      public void itemStateChanged (ItemEvent event){	
	      if ((event.getStateChange()) == ItemEvent.SELECTED){
	        boolean status = runFindElementTest();
	        Checkbox cb = getFindPassedCB();
	        CheckboxGroup findCBG = cb.getCheckboxGroup();
	        if (findCBG != null){
	          if (status)
	            cb = getFindPassedCB();
	          else
	            cb = getFindFailedCB();
	        findCBG.setSelectedCheckbox(cb);
	        }
	      }
      }
    }
    );

    gridC.insets = new Insets (0, 30, 0, 0);
    panel.setLayout(new GridLayout(3, 1));  
    cbg = new CheckboxGroup();
    Checkbox find1 = (Checkbox)add(new Checkbox("passed", cbg, false));
    find1.setName("findPassed");
    Checkbox find2 = (Checkbox)add(new Checkbox("failed", cbg, false));
    find2.setName("findFailed");
    Checkbox find3 = (Checkbox)add(new Checkbox("untested", cbg, true));
    find3.setName("findUntested");
    DialogUtils.addCheckboxToPanel(panel, find1, gridBag, gridC);
    DialogUtils.addCheckboxToPanel(panel, find2, gridBag, gridC);
    gridC.insets = new Insets (0, 30, 10, 0);
    DialogUtils.addCheckboxToPanel(panel, find3, gridBag, gridC);
    panel.setLayout (gridBag);
    gridC.insets = new Insets (0, 10, 0, 0);

    // Add the Remove Element Checkbox
    Checkbox cb4 = DialogUtils.addCheckboxToPanel(panel, "Remove Element on WorkspaceView (removeElement)", gridBag, gridC);
    cb4.addItemListener (new ItemListener (){
      @Override
      public void itemStateChanged (ItemEvent event){	
	if ((event.getStateChange()) == ItemEvent.SELECTED){
	  boolean status = runRemoveElementTest();
	  Checkbox cb = getRemovePassedCB();
	  CheckboxGroup removeCBG = cb.getCheckboxGroup();
	  if (removeCBG != null){
	    if (status)
	      cb = getRemovePassedCB();
	    else
	      cb = getRemoveFailedCB();
	  removeCBG.setSelectedCheckbox(cb);
	  }
	}
      }
    }
    );

    gridC.insets = new Insets (0, 30, 0, 0);
    panel.setLayout(new GridLayout(3, 1));  
    cbg = new CheckboxGroup();
    Checkbox remove1 = (Checkbox)add(new Checkbox("passed", cbg, false));
    remove1.setName("removePassed");
    Checkbox remove2 = (Checkbox)add(new Checkbox("failed", cbg, false));
    remove2.setName("removeFailed");
    Checkbox remove3 = (Checkbox)add(new Checkbox("untested", cbg, true));
    remove3.setName("removeUntested");
    DialogUtils.addCheckboxToPanel(panel, remove1, gridBag, gridC);
    DialogUtils.addCheckboxToPanel(panel, remove2, gridBag, gridC);
    gridC.insets = new Insets (0, 30, 10, 0);
    DialogUtils.addCheckboxToPanel(panel, remove3, gridBag, gridC);
    panel.setLayout (gridBag);
    gridC.insets = new Insets (0, 10, 0, 0);
    return panel;
  }
  // END: createElementMethodsPanel

  // BEGIN: createColorMethodsPanel
  private Panel createColorMethodsPanel(){
    Panel panel = new Panel();
    panel.setName("colorMethodsPanel");

    GridBagLayout gridBag = new GridBagLayout ();
    GridBagConstraints gridC = new GridBagConstraints ();
   
    panel.setLayout (gridBag);

    gridC.insets = new Insets (10, 10, 10, 10);
    gridC.fill = GridBagConstraints.BOTH;
    gridC.weightx = 1.0;

    gridC.gridwidth = GridBagConstraints.REMAINDER; 
    Checkbox cb1 = DialogUtils.addCheckboxToPanel(panel, "Set Background Color", gridBag, gridC);
    cb1.addItemListener (new ItemListener (){
      @Override
      public void itemStateChanged (ItemEvent event){
	if ((event.getStateChange()) == ItemEvent.SELECTED){
	  boolean status = runSetBackgroundColorTest();
	}
      }
    });

    //gridC.gridwidth = GridBagConstraints.REMAINDER; // end row
    gridC.insets = new Insets (10, 10, 10, 10);
   
    // add the Add Element Checkbox
    Checkbox cb2 = DialogUtils.addCheckboxToPanel(panel, "Set Foreground Color", gridBag, gridC);
    cb2.addItemListener (new ItemListener (){
      @Override
      public void itemStateChanged (ItemEvent event){
	if ((event.getStateChange()) == ItemEvent.SELECTED){
	  boolean status = runSetForegroundColorTest();
	}
      }
    }); 

    return panel;
  }
 
  // BEGIN: runCreateElementTest
  public boolean runCreateElementTest(){
    boolean status = true;

    // setup the Vector of possible item types and create instances of each
    if (createdItems == null)
      createdItems = TestUtils.setupAndCreateItems(getConnectionManager());
    
    // for every item that was successfully created, call createElement
    createdElements = new Vector();
    for (int i = 0; i<createdItems.size(); i++){
      try {
        WorkspaceElement wsElement = getWorkspaceView().createElement((Item)createdItems.elementAt(i));
        createdElements.addElement(wsElement);
      }
      catch (G2AccessException ex){
        System.out.println(ex.getMessage());
        status = false;
      }
    }

    System.out.print("***********" + createdElements.size() + " elements were created! *********");
  
    return status;
  }
  // END: runCreateElementTest

  // BEGIN: runAddElementTest
  public boolean runAddElementTest(){
    boolean status = true;
    addedElements = new Vector();
    for (int i=0; i<createdElements.size(); i++){
      WorkspaceElement wkspE = (WorkspaceElement)createdElements.elementAt(i);
      getWorkspaceView().addElement(wkspE);
      addedElements.addElement(wkspE);
    }
    return status;
  }
  // END: runAddElementTest

  // BEGIN: runFindElementTest
  public boolean runFindElementTest(){
    boolean status = true;
    foundElements = new Vector();

    if (createdItems == null)
      createdItems = TestUtils.setupAndCreateItems(getConnectionManager());

    for (int i=0; i<createdItems.size(); i++){
      if (debugFind)
	System.out.println("findElement: " + i);
      Item item = (Item)createdItems.elementAt(i);
      if (debugFind)
	System.out.println("Item is: " + item);
      WorkspaceElement wkspE = getWorkspaceView().findElement(item);
      if (wkspE != null)
	foundElements.addElement(wkspE);
      else
	status = false;
    }
    return status;
  }
  // END: runFindElementTest

  // BEGIN: runRemoveElementTest
  public boolean runRemoveElementTest(){
    boolean status = true;
    for (int i=0; i<addedElements.size(); i++){
      WorkspaceElement wkspE = (WorkspaceElement)addedElements.elementAt(i);
      getWorkspaceView().removeElement(wkspE);
    }
    return status;
  }
  // END: runRemoveElementTest

  // BEGIN: runSetBackgroundColorTest
  public boolean runSetBackgroundColorTest(){
    boolean status = true;
    getWorkspaceView().setBackgroundColor(Color.red);
    return status;
  }
  // END: runSetBackgroundColorTest

  // BEGIN: runSetForegroundColorTest
  public boolean runSetForegroundColorTest(){
    boolean status = true;
    getWorkspaceView().setForegroundColor(Color.yellow);
    return status;
  }
  // END: runSetForegroundColorTest

  public WorkspaceViewTestDialog (MDIFrame parentFrame, String title, boolean isModal, int panelType, ConnectionManager connectionManager){
    super (parentFrame, title, isModal, connectionManager);

    Panel panel = null;
    if (panelType == ELEMENT_METHODS_PANEL)
      panel = createElementMethodsPanel();
    else if (panelType == COLOR_METHODS_PANEL)
      panel = createColorMethodsPanel();
    if (panel != null)
      addPanelToDialog(panel);
  }
} 
