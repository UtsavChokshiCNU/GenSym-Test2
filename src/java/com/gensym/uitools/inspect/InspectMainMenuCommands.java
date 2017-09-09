package com.gensym.uitools.inspect;

import java.awt.event.ActionEvent;
import com.gensym.message.Resource;
import com.gensym.dlg.MessageDialog;
import com.gensym.dlg.InputDialog;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.Command;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.message.Trace;
import java.awt.Window;
import javax.swing.JTable;
import javax.swing.KeyStroke;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.table.TableModel;
import java.awt.Event;
import java.util.Vector;
import java.util.Enumeration;
import com.gensym.jgi.G2Access;
import java.awt.Dialog;
import java.awt.Frame;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;

public class InspectMainMenuCommands extends AbstractCommand
{
  private static final String shortResource = "InspectMainMenuShortResource";
  private static final String longResource = "InspectMainMenuLongResource";
  private static final String mnemonicResource = "InspectMainMenuMnemonicResource";
  private static Resource i18n =
  Resource.getBundle("com.gensym.uitools.inspect.InspectMainMenuShortResource");

  public static final String SAVE_RESULTS = "saveResults";
  public static final String EXIT = "exit";
  public static final String ABOUT = "about";
  public static final String VIEW_STATUS_BAR = "viewStatusBar";
  public static final String VIEW_CONTROL_PANEL = "viewControlPanel";
  public static final String SELECT_ALL = "selectAll";
  public static final String INVERT_SELECTION = "invertSelection";
  public static final String VIEW_AS_TEXT = "viewAsText";
  public static final String SHOW_ITEMS_WHEN_FOUND = "showItemsWhenFound";
  public static final String FORCE_RECOMPILE = "forceRecompile";
  public static final String AUTOMATIC_ATTRIBUTE_UPDATES = "automaticAttributeUpdates";

  private Window window;
  private InspectWindow inspectWindow;
  private TableModel model;
  private TableModelAdapter tmListener = new TableModelAdapter();
  
  public InspectMainMenuCommands(Window window,
				 InspectWindow inspectWindow)
  {
    super(new CommandInformation[]{
      new CommandInformation(EXIT, true, shortResource, longResource,
			      "exit.gif", null, null, true, mnemonicResource, null),
	new CommandInformation(SELECT_ALL, false, shortResource, longResource,
			       "select_all.gif", null, null,
			       true, mnemonicResource,
			       KeyStroke.getKeyStroke('A', Event.CTRL_MASK)),
	new CommandInformation(INVERT_SELECTION, false, shortResource, longResource,
			       null, null, null,
			       true, mnemonicResource, null),	
	new CommandInformation(VIEW_STATUS_BAR, true, shortResource, longResource,
			       null, null,
			       inspectWindow.getInspectSessionViewer().isStatusBarVisible()
			       ?Boolean.TRUE:Boolean.FALSE,
			       true, mnemonicResource, null),
	new CommandInformation(VIEW_CONTROL_PANEL, true, shortResource, longResource,
			       null, null,
			       inspectWindow.getControlPanel().isVisible()?Boolean.TRUE:Boolean.FALSE,
			       true, mnemonicResource, null),
	new CommandInformation(VIEW_AS_TEXT, true, shortResource, longResource,
			       null, null,
			       inspectWindow.getInspectSessionViewer().isViewAsText()
			       ?Boolean.TRUE:Boolean.FALSE,
			       true, mnemonicResource, null),	
	new CommandInformation(SHOW_ITEMS_WHEN_FOUND, true, shortResource, longResource,
			       null, null,
			       inspectWindow.getInspectSessionViewer().isShowItemsWhenFound()
			       ?Boolean.TRUE:Boolean.FALSE,
			       true, mnemonicResource, null),
	new CommandInformation(SAVE_RESULTS, true, shortResource, longResource,
			       "save.gif", null,
			       Boolean.FALSE,
			       false, mnemonicResource, null),	
	new CommandInformation(FORCE_RECOMPILE, true, shortResource, longResource,
			       null, null,
			       Boolean.FALSE,
			       true, mnemonicResource, null),		
	new CommandInformation(AUTOMATIC_ATTRIBUTE_UPDATES,
			       true, shortResource, longResource,
			       null, null,
			       inspectWindow.getInspectSessionViewer().isAutomaticAttributeUpdates()
			       ?Boolean.TRUE:Boolean.FALSE,
			       true, mnemonicResource, null),	
	new CommandInformation(ABOUT, true, shortResource, longResource,
			       "about.gif", null, null, false, mnemonicResource, null)
	});
    this.window = window;
    this.inspectWindow = inspectWindow;
    updateAvailability();
  }

  private void updateAvailability()
  {
    if (model == null || model.getRowCount() == 0) {
      setAvailable(SELECT_ALL, false);
      setAvailable(INVERT_SELECTION, false);
    } else {
      setAvailable(SELECT_ALL, true);
      setAvailable(INVERT_SELECTION, true);
    }
  }

  void setModel(TableModel model) {
    if (this.model != null)
      this.model.removeTableModelListener(tmListener);
    this.model = model;
    if (model != null)
      model.addTableModelListener(tmListener);
  }
  
  @Override
  public void actionPerformed(ActionEvent e){
    InspectSessionViewer viewer = inspectWindow.getInspectSessionViewer();
    InspectControlPanel controlPanel = inspectWindow.getControlPanel();
    String cmdKey = e.getActionCommand();
    if (cmdKey.equals(EXIT)) {
      window.setVisible(false);
      window.dispose();
    } else if (SAVE_RESULTS.equals(cmdKey)) {
      boolean currentState = getState(SAVE_RESULTS).booleanValue();
      boolean recompileState = getState(FORCE_RECOMPILE).booleanValue();
      if (!currentState) {
	String location = null;
	location = getSaveLocation();
	if (location == null || location.equals("")) {
	  currentState=true;
	} else {
	  controlPanel.setRunButtonText(controlPanel.WRITE);
	  inspectWindow.setPrefix(InspectSession.SAVE+location);
	}
      } else {
	controlPanel.setRunButtonText(controlPanel.FIND);
	inspectWindow.setPrefix(InspectSession.SHOW);
      }
      setState(SAVE_RESULTS, !currentState?Boolean.FALSE:Boolean.TRUE);
      setState(SAVE_RESULTS, currentState?Boolean.FALSE:Boolean.TRUE);
      setState(FORCE_RECOMPILE, recompileState?Boolean.FALSE:Boolean.TRUE);
      setState(FORCE_RECOMPILE, !recompileState?Boolean.FALSE:Boolean.TRUE);
    } else if (cmdKey.equals(SELECT_ALL)) {
      JTable table = viewer.getTable();
      table.setRowSelectionInterval(0,table.getRowCount()-1);//selectAll is buggy
    } else if (cmdKey.equals(INVERT_SELECTION)) {
      JTable table = viewer.getTable();
      int[] selectedRows = table.getSelectedRows();
      int count = selectedRows.length;
      table.setRowSelectionInterval(0,table.getRowCount()-1);//selectAll is buggy
      if (count > 0) {
	for (int i=0;i<count;i++) {
	  int nextRow = selectedRows[i];
	  table.removeRowSelectionInterval(nextRow, nextRow);
	}
      }
    } else if (cmdKey.equals(VIEW_AS_TEXT)) {
      boolean newVal = !viewer.isViewAsText();
      setState(VIEW_AS_TEXT, newVal?Boolean.TRUE:Boolean.FALSE);
      viewer.setViewAsText(newVal);
    } else if (cmdKey.equals(VIEW_STATUS_BAR)) {
      boolean newVal = !viewer.isStatusBarVisible();
      setState(VIEW_STATUS_BAR, newVal?Boolean.TRUE:Boolean.FALSE);
      viewer.setStatusBarVisible(newVal);
    } else if (cmdKey.equals(VIEW_CONTROL_PANEL)) {
      boolean newVal = !controlPanel.isVisible();
      setState(VIEW_CONTROL_PANEL, newVal?Boolean.TRUE:Boolean.FALSE);
      controlPanel.setVisible(newVal);
      controlPanel.revalidate();
    } else if (FORCE_RECOMPILE.equals(cmdKey)) {
      boolean currentState = getState(FORCE_RECOMPILE).booleanValue();
      if (!currentState) {
	setState(SAVE_RESULTS, Boolean.FALSE);
	controlPanel.setRunButtonText(controlPanel.RECOMPILE);
	inspectWindow.setPrefix(InspectSession.RECOMPILE);
      } else {
	inspectWindow.setPrefix(InspectSession.SHOW);
	controlPanel.setRunButtonText(controlPanel.FIND);
      }
      setState(FORCE_RECOMPILE, currentState?Boolean.FALSE:Boolean.TRUE);
    } else if (cmdKey.equals(SHOW_ITEMS_WHEN_FOUND)) {
      boolean newVal = !viewer.isShowItemsWhenFound();
      setState(SHOW_ITEMS_WHEN_FOUND, newVal?Boolean.TRUE:Boolean.FALSE);
      viewer.setShowItemsWhenFound(newVal);
      inspectWindow.adjustTitle();
    } else if (cmdKey.equals(AUTOMATIC_ATTRIBUTE_UPDATES)) {
      boolean newVal = !viewer.isAutomaticAttributeUpdates();
      setState(AUTOMATIC_ATTRIBUTE_UPDATES, newVal?Boolean.TRUE:Boolean.FALSE);
      viewer.setAutomaticAttributeUpdates(newVal);
    } else if (cmdKey.equals(ABOUT)) {
      new MessageDialog((window instanceof java.awt.Frame)?(java.awt.Frame)window:null,
			i18n.getString("about"),
			false,
			i18n.getString("aboutText"),
			null).setVisible(true);
    }
  }



  private void saveParameters() {
    //controlPanel.getClassName();
    //controlPanel.getItemName();
    //controlPanel.getExtraFilters();
    //controlPanel.getDisplayAttributes();
  }

  
  public String getSaveLocation() {
    InputDialog dlg = new InputDialog(null,
				  "Write to file",//i18n
				  true,
				  new String[] {"File name"},
				  new String[] {""},
				  null);
    dlg.setVisible(true);
    if (dlg.wasCancelled())
      return null;
    String[] results = dlg.getResults();
    return results[0].trim();
  }
  
  class TableModelAdapter implements TableModelListener {
    @Override
    public void tableChanged(TableModelEvent e) {
      updateAvailability();
    }
  }
}
