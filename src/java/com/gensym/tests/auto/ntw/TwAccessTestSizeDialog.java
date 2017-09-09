package com.gensym.tests.auto.ntw;

import java.awt.Checkbox;
import java.awt.CheckboxGroup;
import java.awt.GridLayout;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.awt.Panel;
import java.awt.Rectangle;
import java.awt.event.*;
import java.util.Vector;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.dlg.WarningDialog;
import com.gensym.jgi.G2AccessException;
import com.gensym.mdi.MDIFrame;
import com.gensym.ntw.TwAccess;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.tests.auto.DialogUtils;
import com.gensym.tests.auto.TestDialog;
import com.gensym.tests.auto.TestUtils;
import com.gensym.tests.auto.LogWindow;
import com.gensym.util.Symbol;

public class TwAccessTestSizeDialog extends TestDialog {
  private Vector createdItems = null;
  private LogWindow lw;
  private static final int REF_HORIZONTAL = 1;
  private static final int REF_VERTICAL = 2;
  private static WarningDialog informDialog;
 
  public Checkbox getMovePassedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "movePassed");
    return (Checkbox)control;
  }

  public Checkbox getMoveFailedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "moveFailed");
    return (Checkbox)control;
  }

  public Checkbox getMoveUntestedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "moveUntested");
    return (Checkbox)control;
  }

  public Checkbox getResizePassedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "resizePassed");
    return (Checkbox)control;
  }

  public Checkbox getResizeFailedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "resizeFailed");
    return (Checkbox)control;
  }

  public Checkbox getResizeUntestedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "resizeUntested");
    return (Checkbox)control;
  }

  public Checkbox getRestoreSizePassedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "restoreSizePassed");
    return (Checkbox)control;
  }

  public Checkbox getRestoreSizeFailedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "restoreSizeFailed");
    return (Checkbox)control;
  }

  public Checkbox getRestoreSizeUntestedCB (){
    Object control = null;
    Panel panel = getPanelComponent();
    control = DialogUtils.findComponentByName(panel, "restoreSizeUntested");
    return (Checkbox)control;
  }

  // BEGIN: createMoveItemPanel
  private Panel createMoveItemPanel(){
    Panel panel = new Panel();
    panel.setName("MoveItemPanel");

    GridBagLayout gridBag = new GridBagLayout ();
    GridBagConstraints gridC = new GridBagConstraints ();
   
    panel.setLayout (gridBag);

    gridC.insets = new Insets (10,10,0,10);
    gridC.fill = GridBagConstraints.BOTH;
    gridC.weightx = 1.0;

    gridC.gridwidth = GridBagConstraints.REMAINDER; 

    // add the Move Item Checkbox
    Checkbox cb1 = DialogUtils.addCheckboxToPanel(panel, "Move Item", gridBag, gridC);
    cb1.addItemListener (new ItemListener (){
      @Override
      public void itemStateChanged (ItemEvent event){
	      if ((event.getStateChange()) == ItemEvent.SELECTED){
	        boolean status = runMoveItemTest();
	        Checkbox cb = getMovePassedCB();
	        CheckboxGroup moveCBG = cb.getCheckboxGroup();
	        if (moveCBG != null){
	          if (status)
	            cb = getMovePassedCB();
	          else
	            cb = getMoveFailedCB();
	        moveCBG.setSelectedCheckbox(cb);
	        }
	      }
      }
    });

    gridC.insets = new Insets (0, 30, 0, 0);
    panel.setLayout(new GridLayout(3, 1));  
    CheckboxGroup cbg = new CheckboxGroup();
    Checkbox move1 = (Checkbox)add(new Checkbox("passed", cbg, false));
    move1.setName("movePassed");
    Checkbox move2 = (Checkbox)add(new Checkbox("failed", cbg, false));
    move2.setName("moveFailed");
    Checkbox move3 = (Checkbox)add(new Checkbox("untested", cbg, true));
    move3.setName("moveUntested");
    DialogUtils.addCheckboxToPanel(panel, move1, gridBag, gridC);
    DialogUtils.addCheckboxToPanel(panel, move2, gridBag, gridC);
    gridC.insets = new Insets (0, 30, 10, 0);
    DialogUtils.addCheckboxToPanel(panel, move3, gridBag, gridC);
    panel.setLayout (gridBag);
    gridC.insets = new Insets (0, 10, 0, 0);
  
    // add the Resize Item Checkbox
    Checkbox cb2 = DialogUtils.addCheckboxToPanel(panel, "Resize Item", gridBag, gridC);
    cb2.addItemListener (new ItemListener (){
      @Override
      public void itemStateChanged (ItemEvent event){
        if ((event.getStateChange()) == ItemEvent.SELECTED){
	        boolean status = runResizeItemTest();
	        Checkbox cb = getResizePassedCB();
	        CheckboxGroup resizeCBG = cb.getCheckboxGroup();
	        if (resizeCBG != null){
	          if (status)
	            cb = getResizePassedCB();
	          else
	            cb = getResizeFailedCB();
	        resizeCBG.setSelectedCheckbox(cb);
	        }
	      }
      }
    });  
	   
    gridC.insets = new Insets (0, 30, 0, 0);
    panel.setLayout(new GridLayout(3, 1));  
    cbg = new CheckboxGroup();
    Checkbox resize1 = (Checkbox)add(new Checkbox("passed", cbg, false));
    resize1.setName("resizePassed");
    Checkbox resize2 = (Checkbox)add(new Checkbox("failed", cbg, false));
    resize2.setName("resizeFailed");
    Checkbox resize3 = (Checkbox)add(new Checkbox("untested", cbg, true));
    resize3.setName("resizeUntested");
    DialogUtils.addCheckboxToPanel(panel, resize1, gridBag, gridC);
    DialogUtils.addCheckboxToPanel(panel, resize2, gridBag, gridC);
    gridC.insets = new Insets (0, 30, 10, 0);
    DialogUtils.addCheckboxToPanel(panel, resize3, gridBag, gridC);
    panel.setLayout (gridBag);
    gridC.insets = new Insets (0, 10, 0, 0);
  

    // add the RestoreSize Item Checkbox
    Checkbox cb4 = DialogUtils.addCheckboxToPanel(panel, "RestoreSize Item", gridBag, gridC);
    cb4.addItemListener (new ItemListener (){
      @Override
      public void itemStateChanged (ItemEvent event){
        if ((event.getStateChange()) == ItemEvent.SELECTED){
	        boolean status = runRestoreSizeItemTest();
	        Checkbox cb = getRestoreSizePassedCB();
	        CheckboxGroup restoreSizeCBG = cb.getCheckboxGroup();
	        if (restoreSizeCBG != null){
	          if (status)
	            cb = getRestoreSizePassedCB();
	          else
	            cb = getRestoreSizeFailedCB();
	        restoreSizeCBG.setSelectedCheckbox(cb);
	        }
	      }
      }
    });  
	   
    gridC.insets = new Insets (0, 30, 0, 0);
    panel.setLayout(new GridLayout(3, 1));  
    cbg = new CheckboxGroup();
    Checkbox restoreSize1 = (Checkbox)add(new Checkbox("passed", cbg, false));
    restoreSize1.setName("restoreSizePassed");
    Checkbox restoreSize2 = (Checkbox)add(new Checkbox("failed", cbg, false));
    restoreSize2.setName("restoreSizeFailed");
    Checkbox restoreSize3 = (Checkbox)add(new Checkbox("untested", cbg, true));
    restoreSize3.setName("restoreSizeUntested");
    DialogUtils.addCheckboxToPanel(panel, restoreSize1, gridBag, gridC);
    DialogUtils.addCheckboxToPanel(panel, restoreSize2, gridBag, gridC);
    gridC.insets = new Insets (0, 30, 10, 0);
    DialogUtils.addCheckboxToPanel(panel, restoreSize3, gridBag, gridC);
    panel.setLayout (gridBag);
    gridC.insets = new Insets (0, 10, 0, 0);
  
    return panel;
  }
  // END: createMoveItemPanel

  // BEGIN: constructor
  public TwAccessTestSizeDialog (MDIFrame parentFrame, String title, boolean isModal, 
    int panelType, LogWindow logWindow, ConnectionManager connectionManager, Vector items){
    super (parentFrame, title, isModal, connectionManager);
    createdItems = items;
    System.out.println("created items " + createdItems);
    lw = logWindow;
    addPanelToDialog(createMoveItemPanel());
  }
  // END: constructor

  // BEGIN: runMoveItemTest
  public boolean runMoveItemTest(){
    boolean status = true;
    TwAccess context = getConnectionManager().getCurrentConnection();

    if (createdItems == null || createdItems.isEmpty()) {
      displayMessage("No items to move");
    }
    else{
      for (int i = 0; i<createdItems.size(); i++){
        try {
          System.out.println("item to move: " + (Item)(createdItems.elementAt(i)));
          context.moveWorkspaceItemBy ( (Item)(createdItems.elementAt(i)), 
                                        20, 20, false);
          System.out.println("moved " + (Item)(createdItems.elementAt(i)));
        }
        catch (G2AccessException ex){
	        System.out.println(ex.getMessage());
        }
      }
    }
    System.out.println("***** DONE with Move Item Test *****");

    return status;
  }
  // END: runMoveItemTest

  public boolean runResizeItemTest(){
    boolean status = true;
    TwAccess context = getConnectionManager().getCurrentConnection();

    if (createdItems == null || createdItems.isEmpty()) {
      displayMessage("No items to resize");
    }

    else {
      for (int i = 0; i<createdItems.size(); i++){
        try {
          System.out.println("item to resize: " + (Item)(createdItems.elementAt(i)));
          int x = ((Item)(createdItems.elementAt(i))).getItemXPosition();
          System.out.print("xpos " + x);
          int y = ((Item)(createdItems.elementAt(i))).getItemYPosition();
          System.out.print("ypos " + y);
          int width = ((Item)(createdItems.elementAt(i))).getItemWidth();
          System.out.print("width " + width);
          int height = ((Item)(createdItems.elementAt(i))).getItemHeight();
          System.out.println("height " + height);
          int lft = x - (width/2);
          int top = y + (height/2);
          int rgt = x + (width);
          int bot = y + (height);

            Symbol ref = context.getReflectionAndRotation((Item)(createdItems.elementAt(i)));
            System.out.println("reflection  " + ref);

          context.resizeItem((Item)(createdItems.elementAt(i)), x, y, rgt+30, bot+30, Symbol.intern("FOO-MODE"));
          System.out.println("resized " + (Item)(createdItems.elementAt(i)));
        }
        catch (G2AccessException ex){
	        System.out.println(ex.getMessage());
        }
      }
    }

    System.out.println("***** DONE with Resize Item Test *****");

    return status;
  }

  public boolean runRestoreSizeItemTest(){
    boolean status = true;
    TwAccess context = getConnectionManager().getCurrentConnection();

    if (createdItems == null || createdItems.isEmpty()) {
      displayMessage("No items to restore size");
    }

    else {
      for (int i = 0; i<createdItems.size(); i++){
        try {
          System.out.println("item to restore size of: " + (Item)(createdItems.elementAt(i)));
          context.requestRestoreNormalSize((Item)(createdItems.elementAt(i)));
          System.out.println("restored " + (Item)(createdItems.elementAt(i)));
        }
        catch (G2AccessException ex){
	        System.out.println(ex.getMessage());
        }
      }
    }

    System.out.println("***** DONE with RestoreSize Item Test *****");

    return true;
  }

  public boolean runReflectItemTest(int direction){
    boolean status = true;
    TwAccess context = getConnectionManager().getCurrentConnection();

    if (createdItems == null || createdItems.isEmpty()) {
      displayMessage("No items to reflect");
    }

    for (int i = 0; i<createdItems.size(); i++){
      try {
        if (direction == REF_HORIZONTAL){  
          Symbol ref = context.getReflectionAndRotation((Item)(createdItems.elementAt(i)));
          context.reflectItemHorizontally((Item)(createdItems.elementAt(i)));
          System.out.println("reflection  " + ref);
        }
        else if (direction == REF_VERTICAL) {
          Symbol ref = context.getReflectionAndRotation((Item)(createdItems.elementAt(i)));
          context.reflectItemVertically((Item)(createdItems.elementAt(i)));
          System.out.println("reflection  " + ref);
        }
      }
      catch (G2AccessException ex){
	      System.out.println(ex.getMessage());
      }
    }

    System.out.println("***** DONE with Resize Item Test *****");

    return status;
  }

  private void displayMessage(String msg) {
    informDialog = new WarningDialog ("Warning", true, msg, null);
    informDialog.pack ();
    informDialog.setVisible (true);
  }
}
