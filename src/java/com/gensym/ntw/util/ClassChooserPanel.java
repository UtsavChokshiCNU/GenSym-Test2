/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ClassChooserPanel.java
 *
 *
 */
/**
  * @undocumented
  */
package com.gensym.ntw.util;

import java.awt.Component;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Image;
import java.awt.Insets;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import javax.swing.DefaultListCellRenderer;
import javax.swing.DefaultListModel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTree;
import javax.swing.JTextField;
import javax.swing.ScrollPaneConstants;
import javax.swing.border.TitledBorder;
import javax.swing.border.EtchedBorder;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreePath;
import com.gensym.classes.G2Definition;
import com.gensym.dlg.MessageDialog;
import com.gensym.icons.IconDescription;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;

public class ClassChooserPanel extends JPanel{

  private static final Resource i18n = Resource.getBundle("com.gensym.ntw.util.Messages");
  private static final Resource i18nErrors = Resource.getBundle("com.gensym.ntw.util.Errors");
  private TwAccess context;
  private JList currentList;
  private JTree classTree;
  private JTextField classTextField;
  private ActionListener inserter;

  public ClassChooserPanel (TwAccess cxn, Symbol[] selectedClasses){
    this.context = cxn;
    GridBagLayout gridBagLayout = new GridBagLayout();
    setLayout(gridBagLayout);

    GridBagConstraints constraints = new GridBagConstraints();

    inserter = new Inserter();

    JPanel hierarchyPanel = createTreePanel(cxn);
    constraints.gridx = 0;
    constraints.gridy = 0;
    constraints.gridwidth = 1;
    constraints.gridheight = 3;
    constraints.weightx = 0.6;
    constraints.weighty = 1.0;
    constraints.anchor = constraints.CENTER;
    constraints.fill = constraints.BOTH;
    gridBagLayout.setConstraints(hierarchyPanel, constraints);
    add(hierarchyPanel);

    JButton addButton = new JButton();
    addButton.setIcon(new ImageIcon(Toolkit.getDefaultToolkit().getImage(getClass().getResource("right-arrow.gif"))));
    addButton.setToolTipText(i18n.getString("AddToolTip"));
    constraints.gridx = 1;
    constraints.gridy = 1;
    constraints.gridwidth = 1;
    constraints.gridheight = 1;
    constraints.weightx = 0;
    constraints.weighty = .5;
    constraints.insets = new Insets(0, 4, 0, 4);
    constraints.anchor = constraints.CENTER;
    constraints.fill = constraints.NONE;
    gridBagLayout.setConstraints(addButton, constraints);
    add(addButton);

    JPanel listPanel = createListPanel(cxn, selectedClasses);
    constraints.gridx = 2;
    constraints.gridy = 0;
    constraints.gridwidth = 1;
    constraints.gridheight = 3;
    constraints.weightx = 0.4;
    constraints.weighty = 1.0;
    constraints.anchor = constraints.CENTER;
    constraints.fill = constraints.BOTH;
    gridBagLayout.setConstraints(listPanel, constraints);
    add(listPanel);

    addButton.addActionListener(inserter); 
  }

  JPanel createTreePanel(TwAccess cxn){
    JPanel panel = new JPanel();
    GridBagLayout gridBagLayout = new GridBagLayout();
    panel.setLayout(gridBagLayout);
    GridBagConstraints constraints = new GridBagConstraints();

    ClassBrowserScrollPane hierarchyScrollPane = new ClassBrowserScrollPane(cxn, 
									    ClassBrowserScrollPane.ALL_, 
									    ClassBrowserScrollPane.ROOT_);
    hierarchyScrollPane.getClassFilter().removeAllElements();
    classTree = hierarchyScrollPane.getTree();
    classTree.setVisibleRowCount(8);
    classTree.expandRow(0);
    classTree.setCellRenderer(new G2ClassTreeCellRenderer());
    hierarchyScrollPane.setBorder(new TitledBorder(new EtchedBorder(), i18n.getString("ClassTreeLabel")));
    constraints.gridx = 0;
    constraints.gridy = 0;
    constraints.gridwidth = 2;
    constraints.gridheight = 2;
    constraints.weightx = 1.0;
    constraints.weighty = 1.0;
    constraints.insets = new Insets(4, 4, 4, 4);
    constraints.anchor = constraints.CENTER;
    constraints.fill = constraints.BOTH;
    gridBagLayout.setConstraints(hierarchyScrollPane, constraints);
    panel.add(hierarchyScrollPane);

    JLabel label = new JLabel(i18n.getString("ClassNameLabel"));
    constraints.gridy = 2;
    constraints.gridwidth = 1;
    constraints.gridheight = 1;
    constraints.weightx = 0.0;
    constraints.weighty = 0.0;
    constraints.insets = new Insets(0, 4, 0, 4);
    constraints.anchor = constraints.CENTER;
    constraints.fill = constraints.NONE;
    gridBagLayout.setConstraints(label, constraints);
    panel.add(label);

    classTextField = new JTextField();
    constraints.gridx = 1;
    constraints.gridy = 2;
    constraints.gridwidth = 1;
    constraints.gridheight = 1;
    constraints.weightx = 1.0;
    constraints.weighty = 0.0;
    constraints.insets = new Insets(0, 0, 4, 4);
    constraints.anchor = constraints.CENTER;
    constraints.fill = constraints.BOTH;
    gridBagLayout.setConstraints(classTextField, constraints);
    panel.add(classTextField);

    classTextField.addActionListener(inserter);
    classTextField.addFocusListener(new FocusAdapter(){
      @Override
      public void focusGained(FocusEvent event){
	classTree.clearSelection();
      }
    });

    return panel;
  }

  JPanel createListPanel(TwAccess connection, Symbol[] selectedClasses){
    JPanel panel = new JPanel();
    GridBagLayout gridBagLayout = new GridBagLayout();
    panel.setLayout(gridBagLayout);
    GridBagConstraints constraints = new GridBagConstraints();

    DefaultListModel model = new DefaultListModel();
    for (int i=0; i<selectedClasses.length; i++)
      model.addElement(selectedClasses[i]);
    currentList = new JList(model);
    currentList.setCellRenderer(new G2ClassListRenderer(connection));
    JScrollPane currentListScrollPane = new JScrollPane(currentList, 
							ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED,
							ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
    constraints.gridx = constraints.REMAINDER;
    constraints.gridwidth = 1;
    constraints.gridheight = 2;
    constraints.weightx = 1.0;
    constraints.weighty = 1.0;
    constraints.anchor = constraints.CENTER;
    constraints.fill = constraints.BOTH;
    gridBagLayout.setConstraints(currentListScrollPane, constraints);
    panel.add(currentListScrollPane);

    JButton removeButton = new JButton(i18n.getString("RemoveFromListLabel"));
    constraints.gridwidth = 1;
    constraints.gridheight = 1;
    constraints.weightx = 1.0;
    constraints.weighty = 0.0;
    constraints.insets = new Insets(4, 0, 0, 0);
    constraints.anchor = constraints.CENTER;
    constraints.fill = constraints.NONE;
    gridBagLayout.setConstraints(removeButton, constraints);
    panel.add(removeButton);

    panel.setBorder(new TitledBorder(new EtchedBorder(), i18n.getString("SelectedClassesLabel")));

    removeButton.addActionListener(new Remover());

    return panel;
  }

  Symbol[] getSelection(){
    DefaultListModel model = (DefaultListModel)currentList.getModel();
    Object[] list = model.toArray();
    Symbol[] selection = new Symbol[list.length];
    for (int i=0; i<list.length; i++)
      selection[i] = (Symbol)list[i];
    return selection;
  }

  class Inserter implements ActionListener{

    @Override
    public void actionPerformed(ActionEvent event){
      TreePath[] selection = classTree.getSelectionPaths();
      if (selection == null || selection.length == 0){
	String className = classTextField.getText();
	if (!className.equals("")){
	  Symbol className_ = Symbol.intern(className.trim().toUpperCase());
	  try{
	    G2Definition def = G2ClassHelper.getDefinitionForClassName(context, className_);
	    if (def != null){
	      if (ClassChooserPanel.allowDefinitionOnPalette(def)){
		addOrSelectInList(className_);
		classTextField.setText("");
	      }
	      else{
		String msg;
		if (def.getIncludeInMenus())
		  msg = "illegalClass";
		else
		  msg = "notIncludedInMenus";
		  new MessageDialog(null, "Error", true, i18nErrors.format(msg, className.toUpperCase()), null).setVisible(true);
		}
	    }
	    else
	      new MessageDialog(null, "Error", true, i18nErrors.format("noClassForName", className.toUpperCase()), null).setVisible(true);
	  }
	  catch(G2AccessException ex){
	    Trace.exception(ex);
	  }
	}
      }
      else{
	DefaultListModel model = (DefaultListModel)currentList.getModel();
	for (int i=0; i<selection.length; i++){
	  DefaultMutableTreeNode node = (DefaultMutableTreeNode)selection[i].getLastPathComponent();
	  InstanceData userObject = (InstanceData)node.getUserObject();
	  try{
	    G2Definition def = userObject.getG2Definition();
	    if (ClassChooserPanel.allowDefinitionOnPalette(def)){
	      Symbol className_ = Symbol.intern(userObject.toString().toUpperCase());//or def.getClassName()
	      addOrSelectInList(className_);
	    }
	  }
	  catch(G2AccessException ex){
	    Trace.exception(ex);
	  }
	}
      }
    }

    private void addOrSelectInList(Symbol className_){
      DefaultListModel model = (DefaultListModel)currentList.getModel();
      if (!model.contains(className_)){
	int index = currentList.getMaxSelectionIndex() + 1;
	if (index == 0)
	  index = currentList.getModel().getSize();
	model.add(index, className_);
	currentList.setSelectedIndex(index);
	currentList.ensureIndexIsVisible(index);
      }
      else{
	int index = model.indexOf(className_);
	currentList.setSelectedIndex(index);
	currentList.ensureIndexIsVisible(index);
      }
    }
  }

  class Remover implements ActionListener{

    @Override
    public void actionPerformed(ActionEvent event){
      int[] selection = currentList.getSelectedIndices();
      DefaultListModel model = (DefaultListModel)currentList.getModel();
      for (int i=selection.length-1; i>=0; i--)
	model.remove(selection[i]);
    }
  }

  static boolean allowDefinitionOnPalette(G2Definition def) throws G2AccessException{
    return G2ClassHelper.isInstanceAllowedOnWorkspace(def) && def.getInstantiate() && def.getIncludeInMenus();
  }

}

class G2ClassListRenderer extends DefaultListCellRenderer{

  private TwAccess connection;

  G2ClassListRenderer(TwAccess connection){
    this.connection = connection;
  }

  @Override
  public Component getListCellRendererComponent(JList list, Object value, int index, boolean isSelected,
						boolean cellHasFocus){
    JLabel label = (JLabel)super.getListCellRendererComponent(list, value, index, isSelected, cellHasFocus);
    try{
      G2Definition def = G2ClassHelper.getDefinitionForClassName(connection, (Symbol)value);
      if (def != null){
	Image icon = G2ClassHelper.getIconForClass(connection, def, (Symbol)value,
						   null,//regionOverrides	   
						   null,//variableOverrides
						   G2ClassHelper.SMALL_ICON);
	if (icon != null)
	  setIcon(new ImageIcon(icon));
	else
	  setIcon(null);
      }
      else
	setIcon(null);
    }
    catch(G2AccessException ex){
      Trace.exception(ex);
      setIcon(null);
    }
    return label;	  
  }

}

class G2ClassTreeCellRenderer extends BasicTreeCellRenderer{

  @Override
  public Component getTreeCellRendererComponent(JTree tree, Object value,
						boolean selected, boolean expanded,
						boolean leaf, int row, boolean hasFocus) {
    InstanceData userObject
      = (InstanceData)((DefaultMutableTreeNode)value).getUserObject();
    G2Definition def = userObject.getG2Definition();
    Component c = super.getTreeCellRendererComponent(tree, value, selected, expanded, leaf, row, hasFocus);
    try{
      setEnabled(ClassChooserPanel.allowDefinitionOnPalette(def));
    }
    catch(G2AccessException ex){
      Trace.exception(ex);
      setEnabled(false);
    }
    return c;
  }
}
