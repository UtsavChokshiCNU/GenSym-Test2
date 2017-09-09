/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CustomizePalettePanelDialog.java
 *
 * THIS IS A WORK IN PROGRESS
 *
 */
package com.gensym.shell.dialogs;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.util.Vector;

import com.gensym.core.UiApplication;
import com.gensym.classes.Module;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.G2ObjectCreator;
import com.gensym.shell.util.TW2MDIApplication;
import com.gensym.ntw.util.BrowserSymbols;
import com.gensym.ntw.util.ClassBrowserScrollPane;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ListSelectionModel;
import javax.swing.ScrollPaneConstants;

public class CustomizePalettePanelDialog extends JDialog {

  public CustomizePalettePanelDialog(G2ObjectCreator objectCreator) {
    getContentPane().setLayout(new BorderLayout());
    getContentPane().add(new CustomizePalettePanel(objectCreator), "Center");
    pack();
  }
}

class CustomizePalettePanel extends JPanel {
  private JPanel currentClassesPanel;
  private JPanel buttonPanel;
  private JPanel classHierarchyPanel;
 
  public CustomizePalettePanel (G2ObjectCreator objectCreator) {
    setLayout(new FlowLayout(FlowLayout.LEFT));
    add(currentClassesPanel = new CurrentClassesPanel(objectCreator));
    add(buttonPanel = new ButtonPanel());
    add(classHierarchyPanel = new ClassHierarchyPanel());

    //GridBagConstraints gridC = new GridBagConstraints();
    //GridBagLayout gridBagLayout = new GridBagLayout();
    //setLayout(gridBagLayout);

    // gridC.insets = new Insets(5, 5, 0, 5);
    //gridC.weightx = 0.3;
    //gridC.fill = GridBagConstraints.BOTH;
    //gridC.gridwidth = GridBagConstraints.RELATIVE; 
    //gridC.anchor = GridBagConstraints.NORTHWEST;
    
    //currentClassesPanel = new CurrentClassesPanel(objectCreator);
    //gridBagLayout.setConstraints(currentClassesPanel, gridC);
    //add(currentClassesPanel);

    //gridC.anchor = GridBagConstraints.CENTER;
    //buttonPanel = new ButtonPanel();
    //gridBagLayout.setConstraints(buttonPanel, gridC);
    //add(buttonPanel);

    //gridC.anchor = GridBagConstraints.NORTHEAST;
    //classHierarchyPanel = new ClassHierarchyPanel();
    //gridBagLayout.setConstraints(classHierarchyPanel, gridC);
    //add(classHierarchyPanel);
  }
}

class CurrentClassesPanel extends JPanel {

  private static Resource i18n = Resource.getBundle("com/gensym/shell/dialogs/Messages");

  private JLabel currentLabel;
  private JScrollPane currentListScrollPane;
  private JList  currentList;

  public CurrentClassesPanel (G2ObjectCreator objectCreator) {
    GridBagConstraints gridC = new GridBagConstraints();
    GridBagLayout gridBagLayout = new GridBagLayout();
    setLayout(gridBagLayout);

    gridC.insets = new Insets(5, 5, 0, 5);
    gridC.fill = GridBagConstraints.BOTH;
    gridC.weightx = 0.4;
    gridC.gridwidth = GridBagConstraints.REMAINDER; 

    currentLabel = new JLabel(i18n.getString("ToolbarClassesLabel"));
    gridBagLayout.setConstraints(currentLabel, gridC);
    add(currentLabel);

    //gridC.gridwidth = GridBagConstraints.RELATIVE; 
    currentList = new JList(objectCreator.getKeys());
    currentList.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
    currentListScrollPane = new JScrollPane(currentList, 
					    ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED,
					    ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
    gridBagLayout.setConstraints(currentListScrollPane, gridC);
    add(currentListScrollPane);
  }
}

class ButtonPanel extends JPanel {

  private static Resource i18n = Resource.getBundle("com/gensym/shell/dialogs/Messages");

  private JButton addButton;
  private JButton removeButton;

  public ButtonPanel () {
    GridBagConstraints gridC = new GridBagConstraints();
    GridBagLayout gridBagLayout = new GridBagLayout();
    setLayout(gridBagLayout);

    gridC.insets = new Insets(5, 5, 0, 5);
    gridC.fill = GridBagConstraints.BOTH;
    gridC.weightx = 0.2;
    gridC.gridwidth = GridBagConstraints.REMAINDER;

    addButton = new JButton(i18n.getString("AddButtonLabel"));
    gridBagLayout.setConstraints(addButton, gridC);
    add(addButton);

    removeButton = new JButton(i18n.getString("RemoveButtonLabel"));
    gridBagLayout.setConstraints(removeButton, gridC);
    add(removeButton);
  }
}

class ClassHierarchyPanel extends JPanel implements BrowserSymbols {
  private static Resource i18n = Resource.getBundle("com/gensym/shell/dialogs/Messages");

  private TwAccess cxn;

  private ClassBrowserScrollPane hierarchyScrollPane;
  private JLabel classTreeLabel;
  //private JLabel moduleFilterLabel;
  //private JComboBox moduleComboBox;

  private Symbol TOP_LEVEL_MODULE_;

  public ClassHierarchyPanel () {
    TW2MDIApplication app = (TW2MDIApplication)UiApplication.getApplication();
    cxn = app.getConnectionManager().getCurrentConnection();

    GridBagConstraints gridC = new GridBagConstraints();
    GridBagLayout gridBagLayout = new GridBagLayout();
    setLayout(gridBagLayout);

    gridC.insets = new Insets(5, 5, 0, 5);
    gridC.fill = GridBagConstraints.BOTH;
    gridC.weightx = 0.4;
    gridC.gridwidth = GridBagConstraints.REMAINDER; 

    //moduleFilterLabel = new JLabel(i18n.getString("ModuleFilterLabel"));
    //gridBagLayout.setConstraints(moduleFilterLabel, gridC);
    //add(moduleFilterLabel);

    //gridC.gridwidth = GridBagConstraints.REMAINDER;
    //moduleComboBox = new JComboBox(executeGetModuleList(cxn));
    //try {
    //  TOP_LEVEL_MODULE_ = cxn.getKb().getTopLevelModule().getName();
    //moduleComboBox.setSelectedItem(TOP_LEVEL_MODULE_);
    //} catch (G2AccessException gae) {
    //Trace.exception(gae);
    //moduleComboBox.setSelectedIndex(0);
    //TOP_LEVEL_MODULE_ = BrowserSymbols.ALL_;
    //}
    //gridBagLayout.setConstraints(moduleComboBox, gridC);
    //add(moduleComboBox);

    classTreeLabel = new JLabel(i18n.getString("ClassTreeLabel"));
    gridBagLayout.setConstraints(classTreeLabel, gridC);
    add(classTreeLabel);

    gridC.gridwidth = GridBagConstraints.REMAINDER;

    //hierarchyScrollPane = new ClassBrowserScrollPane(cxn, TOP_LEVEL_MODULE_, ROOT_);
    hierarchyScrollPane = new ClassBrowserScrollPane(cxn, ALL_, ROOT_);
    gridBagLayout.setConstraints(hierarchyScrollPane, gridC);
    add(hierarchyScrollPane);
  }

  private String[] executeGetModuleList(TwAccess cxn) {
    String[] moduleNamesAsStrings = null;
    
    try {
      Vector modules = new Vector();
      modules.addElement(BrowserSymbols.ALL_);
      Module topLevelModule = cxn.getKb().getTopLevelModule();
      if (topLevelModule != null) {
	modules.addElement(topLevelModule.getName());
	getRequiredModules(topLevelModule, modules);
	if (modules.size() > 0) {
	  moduleNamesAsStrings = new String[modules.size()];
	  for (int i=0; i<modules.size(); i++)
	    moduleNamesAsStrings[i] = modules.elementAt(i).toString();
	}
      }
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }

    return moduleNamesAsStrings;
  }

  private void getRequiredModules(Module module, Vector modules) {
    Symbol moduleName;
    Module tmpModule;
    boolean hasRequiredModules = false;

    try {
      Sequence requiredModules = module.getRequiredModules();
      for (int i =0; i<requiredModules.size(); i++) {
	moduleName = (Symbol)requiredModules.elementAt(i);
	tmpModule = cxn.getKb().getModule(moduleName);
	Sequence moreModules = tmpModule.getRequiredModules();

	if (moreModules.size() == 0)
	  hasRequiredModules = false;
	else 
	  hasRequiredModules = true;

	// make sure modules is not already in the Vector of modules
	Symbol tmpName;
	boolean found = false;
	for (int j=0; j<modules.size(); j++) {
	  tmpName = (Symbol)modules.elementAt(j);
	  if (moduleName.equals(tmpName))
	      found = true;
	}
	if (!found) 
	  modules.addElement(moduleName);
	
	if (hasRequiredModules)
	  getRequiredModules(tmpModule, modules);
      }  
    } catch (G2AccessException gae) {
      System.out.println(gae);
    }
  }
}
