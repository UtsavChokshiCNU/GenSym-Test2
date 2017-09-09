package com.gensym.shell;

import java.awt.Checkbox;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Image;
import java.awt.Insets;
import java.awt.Panel;
import java.awt.event.ActionEvent;
import com.gensym.jgi.G2Gateway;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwGateway;
import com.gensym.ui.AbstractCommand;
import com.gensym.util.Symbol;

public class ModulesCommand extends AbstractCommand implements TwConnectionListener {
 

  private static final String NEW_MODULE = "NewModule";
  private static final String MERGE_MODULE = "MergeModule";
  private static final String DELETE_MODULE = "DeleteModule";
  private ConnectionManager cm;
  private TwAccess[] cxns;
  private transient String currentCmdKey;
  private Telewindows app;

  public ModulesCommand(ConnectionManager cm, Telewindows app){

    super(3, new String[] {NEW_MODULE, MERGE_MODULE, DELETE_MODULE},
	  "CommandShortResource", "CommandLongResource", null, null, 
	  "COM.gensym.shell.ModulesCommand");


    this.app = app;
    this.cm = cm;
    cm.addTwConnectionListener(this);
    if (cm.getCurrentConnection() == null){
      setAvailable(NEW_MODULE, false);
      setAvailable(MERGE_MODULE, false);
      setAvailable(DELETE_MODULE, false);
      noConnection();
    }
    else {
      if (cm.getCurrentConnectionState().equals(TwGateway.RUNNING_)) 
	connectionRunning();
      else if (cm.getCurrentConnectionState().equals(TwGateway.PAUSED_)) 
	connectionPaused();
      else connectionReset();
    }
    this.currentCmdKey = "";
  }
  
  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    System.out.println("handling module event:"+cmdKey);
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey)) 
      throw new IllegalStateException("Command is unavailable.");
  
    if (cmdKey.equals(NEW_MODULE)){
      handleNewModuleCommand();
      }
    else if (cmdKey.equals(MERGE_MODULE)){ 
      handleMergeModuleCommand();
      }
    else if (cmdKey.equals(DELETE_MODULE)){
      handleDeleteModuleCommand();
      }
  }

  public void connectionOpened(TwConnectionEvent e){}
  public void connectionClosed(TwConnectionEvent e){}
  public void currentConnectionChanged(TwConnectionEvent e){
    System.out.println("currentConnectionChanged in ModuleCommand");
    TwAccess context = e.getConnection();
    boolean available = true;
    if (context == null){
      available = false;
      noConnection();
    }

    System.out.println("available: " + available);

    setAvailable(NEW_MODULE, available);
    setAvailable(MERGE_MODULE, available);
    setAvailable(DELETE_MODULE, available);
  }

  public void currentConnectionStarted(TwConnectionEvent e){
    connectionRunning();
  }
  public void currentConnectionResumed(TwConnectionEvent e){
    connectionRunning();
  }
  public void currentConnectionPaused(TwConnectionEvent e){
    connectionPaused();
  }
  public void currentConnectionReset(TwConnectionEvent e){
    connectionReset();
  }

 private void connectionRunning(){
    setModuleStateAvailability(false, false, false);
  }

  private void connectionPaused(){
    setModuleStateAvailability(false, false, false);
  }

  private void connectionReset(){
    setModuleStateAvailability(false, false, false);
  }

  private void noConnection(){
    setModuleStateAvailability(false, false, false);
  }

  private void setModuleStateAvailability(boolean newState, boolean mergeState, boolean deleteState){
    setAvailable(NEW_MODULE, newState);
    setAvailable(MERGE_MODULE, mergeState);
    setAvailable(DELETE_MODULE, deleteState);
  }   

  // BEGIN: handleNewModuleCommand

  private void handleNewModuleCommand(){
    System.out.println("handleNewModuleCommand NYI");
  }

  // END: handleNewModuleCommand

  // BEGIN: handleMergeModuleCommand
  private G2FileIODialog mergeDialog = null;
  private static Checkbox mergeAutoResolveConflictsBtn;
  private static Checkbox mergeBringFormatsUpToDateBtn;
  private static Checkbox mergeInstallSystemTablesBtn;

  public static boolean getMergeAutoResolveConflictsState(){
    return mergeAutoResolveConflictsBtn.getState();
  }

  public static void setMergeAutoResolveConflictsState(boolean state){
    mergeAutoResolveConflictsBtn.setState(state);
  }

  public static boolean getMergeBringFormatsUpToDateState(){
    return mergeBringFormatsUpToDateBtn.getState();
  }

  public static void setMergeBringFormatsUpToDateState(boolean state){
    mergeBringFormatsUpToDateBtn.setState(state);
  }

  public static boolean getMergeInstallSystemTablesState(){
    return mergeInstallSystemTablesBtn.getState();
  }

  public static void setMergeInstallSystemTablesState(boolean state){
    mergeInstallSystemTablesBtn.setState(state);
  }

  protected Checkbox addCheckboxToPanel (String label, Panel panel, GridBagLayout gridBag, GridBagConstraints gridC){
    Checkbox button = new Checkbox (label);
    gridBag.setConstraints (button, gridC);
    panel.add(button);
    return button;
  }

  private void initMergeModuleDialog (){
    String fileSpec;
    Panel subPanel = new Panel ();

    GridBagLayout gridBag = new GridBagLayout ();
    GridBagConstraints gridC = new GridBagConstraints ();
   
    subPanel.setLayout (gridBag);

    // Set up the grid constraints so that the controls are more closely packed
    gridC.insets = new Insets (0, 5, 0, 5);
    gridC.fill = GridBagConstraints.BOTH;
    gridC.weightx = 1.0;
    gridC.gridwidth = GridBagConstraints.REMAINDER; // end row

    // Create the panel that is specific to "Merge Module"
    mergeAutoResolveConflictsBtn = addCheckboxToPanel ("Resolve conficts automatically", subPanel, gridBag, gridC);
    mergeBringFormatsUpToDateBtn = addCheckboxToPanel ("Bring formats up to date", subPanel, gridBag, gridC);
    mergeInstallSystemTablesBtn = addCheckboxToPanel ("Install system tables of merged KB", subPanel, gridBag, gridC);

    // Create a generic FILE IO dialog, passing the specific panel to insert
    mergeDialog = new G2FileIODialog(app.getFrame(), "Merge Module", true, "Merge", true, subPanel);
    mergeDialog.setPromptLabel("Enter the module you would like to merge:"); 
  }

  private void handleMergeModuleCommand () {
    Boolean resolveConflicts = Boolean.FALSE;
    Boolean bringFormatsUpToDate = Boolean.FALSE;
    Boolean installSystemTables = Boolean.FALSE;
    String fileSpec;
    if (mergeDialog == null){  
      initMergeModuleDialog();
    }
    else {
      // clean the KBTextField, make sure all checkboxs are false
      mergeDialog.setKBTextField("");
      setMergeAutoResolveConflictsState(false);
      setMergeBringFormatsUpToDateState(false);
      setMergeInstallSystemTablesState(false);
    }
 
    mergeDialog.show();
    if (mergeDialog.getDialogCloseAction() == G2FileIODialog.OK_ACTION){
      fileSpec = mergeDialog.getKBTextField();
      
      // Verify fileSpec before continuing

      resolveConflicts = getMergeAutoResolveConflictsState() ? Boolean.TRUE : Boolean.FALSE;
      bringFormatsUpToDate = getMergeBringFormatsUpToDateState() ? Boolean.TRUE : Boolean.FALSE;
      installSystemTables = getMergeInstallSystemTablesState() ? Boolean.TRUE : Boolean.FALSE;

      System.out.println ("OK Merge Module: " + fileSpec + "  resolveConflicts?  " + resolveConflicts + "  bringFormatsUpToDate?  " + bringFormatsUpToDate + "  installSystemTables?  " + installSystemTables);

      Symbol mergeKBSysProc = Symbol.intern ("g2-merge-kb");
      Object[] args = new Object[4];
      args[0] = fileSpec;
      args[1] = (Object)resolveConflicts;
      args[2] = (Object)bringFormatsUpToDate;
      args[3] = (Object)installSystemTables;
      try {
	((G2Gateway)cm.getCurrentConnection()).callRPC(mergeKBSysProc, args);
      }
      catch (G2AccessException ex){
	System.out.println("bad G2AccessException");
      }
    }
    /*
    fileSpec = mergeDialog.getKBTextField();

    resolveConflicts = getMergeAutoResolveConflictsState() ? Boolean.TRUE : Boolean.FALSE;
    bringFormatsUpToDate = getMergeBringFormatsUpToDateState() ? Boolean.TRUE : Boolean.FALSE;
    installSystemTables = getMergeInstallSystemTablesState() ? Boolean.TRUE : Boolean.FALSE;

    System.out.println ("Merge Module: " + fileSpec + "  resolveConflicts?  " + resolveConflicts + "  bringFormatsUpToDate?  " + bringFormatsUpToDate + "  installSystemTables?  " + installSystemTables);

    Symbol mergeKBSysProc = Symbol.intern ("g2-merge-kb");
    Object[] args = new Object[4];
    args[0] = fileSpec;
    args[1] = (Object)resolveConflicts;
    args[2] = (Object)bringFormatsUpToDate;
    args[3] = (Object)installSystemTables;
    try {
    ((G2Gateway)cm.getCurrentConnection()).callRPC(mergeKBSysProc, args);
    }
    catch (G2AccessException ex){
      System.out.println("bad G2AccessException");
    }
    */
  }
  // END: handleMergeModuleCommand

  // BEGIN: handleDeleteModuleCommand
  private void handleDeleteModuleCommand(){
    System.out.println("deleteModuleCommand NYI");
  }
  // END: handleDeleteModuleCommand
}






