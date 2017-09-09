/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DefaultObjectInstanceDataFactory.java
 *
 */

package com.gensym.ntw.util;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.MalformedURLException;

import com.gensym.dlgruntime.DialogManager;
import com.gensym.dlgruntime.ResourceInstantiationException;
import com.gensym.classes.G2Definition;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Module;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import javax.swing.JTree;
import javax.swing.tree.TreePath;
import java.awt.Cursor;
import java.awt.Container;
import java.awt.Component;
import com.gensym.shell.dialogs.NewModuleDialog;
import com.gensym.classes.ModuleInformation;
import java.awt.Window;
import java.awt.Frame;
import com.gensym.message.Resource;
import javax.swing.JCheckBox;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import javax.swing.JMenu;
import javax.swing.tree.DefaultMutableTreeNode;
import java.util.Enumeration;

public class DefaultObjectInstancePopupMenuFactory
implements InstancePopupMenuFactory, BrowserSymbols
{

  static final Resource i18n = Resource.getBundle("com/gensym/shell/dialogs/Messages");
  
  private static final String GO_TO = "Go To...";
  private static final String EDIT_TEXT = "Edit Text...";
  private static final String NEW_WORKSPACE  = "Workspace";  
  private static final String NEW_MODULE = "Module...";
  private static final String DELETE_MODULE = "Delete...";
  private static final String CREATE_INSTANCE = "Create Instance";
  private static final String PROPERTIES = "Properties...";
  private static final String EXPAND_ALL = "Expand all";


  private static final Symbol TEXT_ = Symbol.intern("TEXT");
  private static final Symbol GO_TO_ITEM_ = Symbol.intern("GO-TO-ITEM");

  private TwAccess cxn;
  private PopupMenuActionListener popupMenuAdapter = new PopupMenuActionListener();
  
  @Override
  public JPopupMenu createInstancePopupMenu(TwAccess connection,
					    Symbol dataType,
					    JTree tree) {
    cxn = connection;
    JPopupMenu menu = null;
    if (dataType.equals(MODULE_))
       menu = createModulePopupMenu(tree);
    else if (dataType.equals(KB_WORKSPACE_))
      menu = createKbWorkspacePopupMenu(tree);
    else if (dataType.equals(ITEM_) ||
	     dataType.equals(ENTITY_) ||
	     dataType.equals(G2_DEFINITION_) ||
	     dataType.equals(PROCEDURE_))
      menu = createItemPopupMenu(tree, dataType);
    /*if (menu != null) {
      menu.addSeperator();
      JMenuItem menuItem = new JMenuItem(EXPAND_ALL);
      menuItem.addActionListener(popupMenuAdapter);
      menu.add(menuItem);
    }	*/
    return menu;
  }

  private JPopupMenu createModulePopupMenu(JTree tree) {
    JPopupMenu menu = new JPopupMenu();
    JMenuItem menuItem;
    
    JMenu newMenu = new JMenu("New");
    newMenu.add(menuItem = new JMenuItem(NEW_WORKSPACE));
    menuItem.addActionListener(popupMenuAdapter);        
    newMenu.add(menuItem = new JMenuItem(NEW_MODULE));
    menuItem.addActionListener(popupMenuAdapter);    
    menu.add(newMenu);

    menu.add(menuItem = new JMenuItem(DELETE_MODULE));
    menuItem.addActionListener(popupMenuAdapter);
    menu.add(menuItem = new JMenuItem(PROPERTIES));
    menuItem.addActionListener(popupMenuAdapter);    
    menu.setInvoker(tree);
    return menu;
  }

  private JPopupMenu createKbWorkspacePopupMenu(JTree tree) {
    JPopupMenu  menu = new JPopupMenu();
    JMenuItem menuItem;
    menu.add(menuItem = new JMenuItem(GO_TO));
    menuItem.addActionListener(popupMenuAdapter);
    menu.addSeparator();
    menu.add(menuItem = new JMenuItem(PROPERTIES));
    menuItem.addActionListener(popupMenuAdapter);
    menu.setInvoker(tree);
    return menu;
  }

  private JPopupMenu createItemPopupMenu(JTree tree, Symbol dataType) {   
    JPopupMenu menu = new JPopupMenu();
    JMenuItem menuItem;
    /*if (dataType.equals(CLASS_DEFINITION_) ||
	dataType.equals(G2_DEFINITION_)) {//check instantiability too!
      menu.add(menuItem = new JMenuItem(CREATE_INSTANCE));
      menuItem.addActionListener(popupMenuAdapter);      
    }*/
    if (dataType.equals(PROCEDURE_)) {
      menu.add(menuItem = new JMenuItem(EDIT_TEXT));
      menuItem.addActionListener(popupMenuAdapter);      
    }
    menu.add(menuItem = new JMenuItem(GO_TO));
    menuItem.addActionListener(popupMenuAdapter);
    menu.addSeparator();
    menu.add(menuItem = new JMenuItem(PROPERTIES));
    menuItem.addActionListener(popupMenuAdapter);
    
    menu.setInvoker(tree);
    return menu;
  }

   // BEGIN:: handlers for popup menu items
  private void handleGoToAction(InstanceData data) {
    Symbol dataType = data.getDataType();
    KbWorkspace wksp;
    Structure particulars = new Structure();
    try {
      if (dataType.equals(KB_WORKSPACE_)) {
	wksp = (KbWorkspace)data.getItem();
	wksp.show(particulars);
      } else {
	Item item = data.getItem();
	Sequence parents = item.getContainmentHierarchy();
	if (!parents.isEmpty()) {
	  wksp = (KbWorkspace)parents.elementAt(0);
	  particulars.setAttributeValue(ITEM_, item);
	  particulars.setAttributeValue(GO_TO_ITEM_, new Boolean(true));
	  wksp.show(particulars);
	}
      }
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
  }

  private void handlePropertiesAction(Component component, InstanceData data) {
    Symbol dataType = data.getDataType();
    try {
      DialogManager dlgManager = cxn.getDialogManager();
      Symbol userMode = cxn.getUserMode();
      Item item = data.getItem();
      if (item != null) {
	dlgManager.editItem(component, item, userMode, java.util.Locale.getDefault());
      } else if (dataType.equals(MODULE_)) {
	Module module = data.getModule();
	dlgManager.editItem (component, module.getModuleInformation(), userMode, 
			     java.util.Locale.getDefault()); 
      } 
    } 
    catch (G2AccessException gae) {
      Trace.exception(gae);
    }
    catch (ResourceInstantiationException rie) {
      Trace.exception(rie);
    }
    catch (MalformedURLException mue) {
      Trace.exception(mue);
    }
  }
  private void handleNewModuleAction(Window window, InstanceData data) {
    ModuleInformation currentModule = (ModuleInformation)data.getItem();
    if (currentModule != null) {
      NewModuleDialog dlg = new NewModuleDialog((window instanceof Frame)?(Frame)window:null,
						cxn, currentModule);
      dlg.setVisible(true);
      if (dlg.wasCancelled()) return;
      dlg.saveResults();
    } 
  }

  private void handleCreateInstanceAction(Window window, InstanceData data) {
    //Item item = data.getItem();
    new com.gensym.dlg.ErrorDialog (null, "NYI", true, 
				    "Functionality not implemented", null).setVisible(true);    
    
  }
  
  private void handleNewWorkspaceAction(Window window, InstanceData data) {
    try {
      KbWorkspace wksp = com.gensym.shell.commands.WorkspaceCommands.createNewWorkspace(cxn);
      if (wksp == null) return;      
      wksp.show(new Structure());      
      Item item = data.getItem();
      if (item instanceof ModuleInformation) {
	ModuleInformation currentModule = (ModuleInformation)item;
	Symbol moduleName = currentModule.getTopLevelModule();
	wksp.setModuleAssignment(moduleName);
      }
    } catch (G2AccessException gae) {
      Trace.exception(gae);
      if (gae.getMessage() != null)
	new com.gensym.dlg.ErrorDialog (null, i18n.getString("Error"), true, 
					gae.getMessage(), null).setVisible(true);
    }
  }
  
  private void handleDeleteModuleAction(Window window, InstanceData data) {
    ModuleInformation currentModule = (ModuleInformation)data.getItem();
    try {    
      Symbol moduleName = currentModule.getTopLevelModule();
      if (moduleName == null) return;//choice shouldn't be available
      DeleteModuleDialog dmd
	= new DeleteModuleDialog((Frame)window,
				 "Delete Module " + moduleName.toString().toLowerCase(),
				 true);
      dmd.setVisible(true);
      if (dmd.wasCancelled()) return;
      LoadSaveKBTools.setDeleteAssociatedWorkspaces(dmd.deleteAssociatedWorkspaces?
						    Boolean.TRUE:Boolean.FALSE);
      LoadSaveKBTools.deleteModule(cxn, moduleName);
    } catch (G2AccessException gae) {
      Trace.exception(gae);
      if (gae.getMessage() != null)
	new com.gensym.dlg.ErrorDialog (null, i18n.getString("Error"), true, 
			 gae.getMessage(), null).setVisible(true);
    }
  }      
  
  private void handleEditTextAction(InstanceData data) {
    /*
     * com.gensym.editor.text is a private package. This code may not be supported
     * in future releases of Telewindows2 Toolkit.
     */
    new com.gensym.editor.text.Session(data.getItem(), TEXT_, null);
  }

  class PopupMenuActionListener implements ActionListener {
    @Override
    public void actionPerformed(ActionEvent e) {
      String actionCommand = e.getActionCommand();
      JMenuItem menuItem = (JMenuItem)e.getSource();
      
      JTree invoker = null;
      Component comp = menuItem;
      while (invoker == null) {
	comp = comp.getParent();
	if (comp instanceof JPopupMenu) {
	  comp = ((JPopupMenu)comp).getInvoker();
	  if (comp instanceof JTree)
	    invoker =(JTree)comp;
	}
      }

      TreePath path = invoker.getLeadSelectionPath();
      BasicTreeNode node = (BasicTreeNode)path.getLastPathComponent();
      InstanceData data = (InstanceData)node.getUserObject();

      Container window = invoker;
      Container prevWindow = window;
      while(window != null && !(prevWindow instanceof Window)) {
	prevWindow = window;
	window = window.getParent();
      }
      window = prevWindow;
      if (window != null)
	window.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));     
      if (actionCommand.equals(GO_TO))
	handleGoToAction(data);
      else if (actionCommand.equals(PROPERTIES))
	handlePropertiesAction(window, data);
      else if (actionCommand.equals(EDIT_TEXT))
	handleEditTextAction(data);
      else if (actionCommand.equals(NEW_MODULE))
	handleNewModuleAction((Window)window, data);
      else if (actionCommand.equals(DELETE_MODULE))
	handleDeleteModuleAction((Window)window, data);
      else if (actionCommand.equals(NEW_WORKSPACE))
	handleNewWorkspaceAction((Window)window, data);
      else if (actionCommand.equals(CREATE_INSTANCE))
	handleCreateInstanceAction((Window)window, data);
      else if (actionCommand.equals(EXPAND_ALL))
	expandAll(invoker, node);
      if (window != null)      
	window.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));           
    }
  }

  private static void expandAll(JTree tree, DefaultMutableTreeNode node) {
    //tree.expandRow();
    Enumeration children = node.children();
    while (children.hasMoreElements()) 
      expandAll(tree, (DefaultMutableTreeNode)children.nextElement());
  }
}  

class DeleteModuleDialog extends com.gensym.dlg.StandardDialog {
  boolean deleteAssociatedWorkspaces = true;
  DeleteModuleDialog(Frame frame, String title, boolean isModal) {
    super (frame, title, isModal,
	   new String[] {OK_LABEL, CANCEL_LABEL},
	   new int[] {OK, CANCEL},
	   new DeleteModuleOptionsPanel(), null);
  }
}
  
class DeleteModuleOptionsPanel extends javax.swing.JPanel {
  JCheckBox deleteAssociatedButton;
  public DeleteModuleOptionsPanel() {
    GridBagConstraints gridC = new GridBagConstraints();
    GridBagLayout gridBagLayout = new GridBagLayout();
    setLayout (gridBagLayout);
 
    gridC.insets = new Insets (5, 5, 0, 5);
    gridC.fill = GridBagConstraints.BOTH;
    gridC.weightx = 1.0;
    gridC.gridwidth = GridBagConstraints.REMAINDER; // end row

    deleteAssociatedButton = new JCheckBox(DefaultObjectInstancePopupMenuFactory.i18n.getString("DeleteAssociatedWorkspaces"), true);
    deleteAssociatedButton.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
	Component parent = getParent();
	while ((parent != null) && (!(parent instanceof DeleteModuleDialog))) {
	  parent = parent.getParent();
	}
	((DeleteModuleDialog)parent).deleteAssociatedWorkspaces = deleteAssociatedButton.isSelected();
      }
});
    gridBagLayout.setConstraints(deleteAssociatedButton, gridC);
    add(deleteAssociatedButton);
  }
}
  


