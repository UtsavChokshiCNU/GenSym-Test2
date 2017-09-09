package com.gensym.ntw.util;

import java.awt.Frame;
import javax.swing.JList;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.message.Resource;
import com.gensym.util.Symbol;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.ntw.util.ModuleList;
import com.gensym.ntw.util.ModuleBrowserScrollPane;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.BrowserSymbols;
import java.awt.Dimension;
import com.gensym.ntw.util.ClassInstanceData;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JPanel;
import javax.swing.JTextField;
import java.awt.BorderLayout;
import javax.swing.JRadioButton;
import javax.swing.JLabel;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;

public class ModuleSelectionPanel extends JPanel {
  private static Resource i18n = Resource.getBundle("com/gensym/ntw/util/Messages");
  private Component currentComponent;
  private Symbol selectedModule;
  private JLabel selectionDisplay;
  private static Font selectionDisplayFont = new Font("sansserif", Font.BOLD, 12);
  private ModuleList moduleList;
  private ModuleBrowserScrollPane moduleTree;
  private JScrollPane moduleScrollList;
  public static final int MODULE_TREE = 0;
  public static final int MODULE_LIST = 1;
  private JRadioButton treeButton, listButton;
  
  public ModuleSelectionPanel(TwAccess cxn) {
    setName(i18n.getString("ModuleSelection"));
    moduleList = new ModuleList(cxn);
    moduleScrollList = new JScrollPane(moduleList);
    moduleList.addListSelectionListener(new ListSelectionListener() {
      @Override
      public void valueChanged(ListSelectionEvent e) {
	if (!moduleList.getValueIsAdjusting()) {
          Object o = moduleList.getSelectedValue();
          Symbol s;
          if (o instanceof String) {
            s = Symbol.intern(((String)o).toUpperCase());
          } else if (o instanceof Symbol) {
            s = (Symbol) o;
          } else {
            s = Symbol.intern("NONE");
          }
	  setSelectedModule(s);
	}
      }
    });
    moduleTree = new ModuleBrowserScrollPane(cxn, BrowserSymbols.ALL_, BrowserSymbols.ROOT_);        
    moduleTree.setPreferredSize(new Dimension(400, 200));
    moduleTree.addTreeSelectionListener(new TreeSelectionListener() {
      @Override
      public void valueChanged(TreeSelectionEvent e) {
	ClassInstanceData data = (ClassInstanceData)moduleTree.getUserObjectForSelectedTreeNode();
	if (data != null && data.getModule() != null) 
	  setSelectedModule(data.getModule().getName());
      }
    });
    selectionDisplay = new JLabel();
    setLayout(new BorderLayout());
    JPanel selectionDisplayPanel = new JPanel();
    selectionDisplay.setPreferredSize(new Dimension(100, 20));
    selectionDisplay.setFont(selectionDisplayFont);
    selectionDisplayPanel.setLayout(new BorderLayout());
    selectionDisplayPanel.add(new JLabel(i18n.getString("ModuleName")+":   "),BorderLayout.WEST);    
    selectionDisplayPanel.add(selectionDisplay);
    JPanel buttonPanel = new JPanel();
    treeButton = new JRadioButton(i18n.getString("ModuleTree"));

    treeButton.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent ae) {
	setCurrentComponent(MODULE_TREE);
      }
    });
    listButton = new JRadioButton(i18n.getString("ModuleList"));
    listButton.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent ae) {
	setCurrentComponent(MODULE_LIST);
      }
    });
    buttonPanel.setLayout(new BorderLayout());
    JPanel modePanel = new JPanel();
    modePanel.add(listButton);        
    modePanel.add(treeButton);
    buttonPanel.add(modePanel, BorderLayout.EAST);
    buttonPanel.add(selectionDisplayPanel);
    add(buttonPanel, BorderLayout.SOUTH);
    setCurrentComponent(MODULE_LIST);
  }

  public void setCurrentComponent(int componentID) {
    if (currentComponent != null)
      remove(currentComponent);
    switch(componentID) {
    case MODULE_LIST:
      currentComponent = moduleScrollList;
      add(moduleScrollList);
      listButton.setSelected(true);
      treeButton.setSelected(false);
      break;
    case MODULE_TREE:
      currentComponent = moduleTree;
      add(moduleTree);
      listButton.setSelected(false);
      treeButton.setSelected(true);
      break;      
    }
    validate();
    repaint();
  }

  public Symbol getSelectedModule() {
    return selectedModule;
  }
  
  public void setSelectedModule(Symbol moduleName) {
    this.selectedModule = moduleName;
    selectionDisplay.setText(moduleName.toString());
  }
  
  
}
