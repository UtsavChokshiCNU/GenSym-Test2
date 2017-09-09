/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ClassEditorPanel.java
 *
 */
package com.gensym.g2studio.dialogs;

import java.awt.FlowLayout;
import java.awt.GridBagConstraints;
import java.awt.Image;
import java.awt.Insets;
import java.awt.Point;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.util.Vector;

import com.gensym.classes.ClassDefinition;
import com.gensym.classes.G2Definition;
import com.gensym.classes.Kb;
import com.gensym.classes.Module;
import com.gensym.dlg.TabGroupPanel;
import com.gensym.icons.IconDescription;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.WindowUtil;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.uiutil.StandardGridBagPanel;
import com.gensym.util.ClassManager;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.DefinitionSymbols;
import com.gensym.util.symbol.G2ClassSymbols;

import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

public class ClassEditorPanel extends JPanel {

  private static Resource shortBundle = Resource.getBundle("com/gensym/g2studio/dialogs/ClassEditorResource");

  private static final Symbol CLASS_DEFINITION_ = Symbol.intern("CLASS-DEFINITION");
  private static final Point  PIVOT_POINT = new Point(0, 0);

  private ConnectionManager connectionManager;
  private TwAccess currentConnection;
  private ClassManager classManager;
  private ClassDefinition classDefinition;

  private TabGroupPanel editorPanels;
  private GeneralPanel generalPanel;
  private AttributesPanel attributesPanel = null;
  private MethodsPanel methodsPanel = null;
  private RelationsPanel relationsPanel = null;
  private RulesPanel rulesPanel = null;

  public ClassEditorPanel(ConnectionManager connectionManager){
    this.connectionManager = connectionManager;
    setConnection(connectionManager.getCurrentConnection());
    createClassEditorPanel();
  }

  private void setConnection(TwAccess connection) {
    currentConnection = connection;
    if (currentConnection != null)
      classManager = currentConnection.getClassManager();
  }

  public void setClassDefinition(ClassDefinition classDef) {
    classDefinition = classDef;
    try {
      executeSetClassDefinition();
    } catch (G2AccessException gae) {
      //System.out.println(gae);
      Trace.exception(gae);
    }
  }

  private void executeSetClassDefinition() throws G2AccessException {
    if (classDefinition != null) {
      // set the class name
      Symbol className = classDefinition.getClassName();
      generalPanel.classNameTF.setText(className.toString());

      // set the superior class(es)
      Sequence directSuperiorClasses = classDefinition.getDirectSuperiorClasses();
      String dsText = "";
      Symbol tmpClassName;
      int len = directSuperiorClasses.size();
      for (int i=0; i<len; i++) {
	tmpClassName = (Symbol)directSuperiorClasses.elementAt(i);
	dsText = tmpClassName.toString();
	if (i<len-1)
	  dsText = dsText+", ";
      }
      generalPanel.superiorClassTF.setText(dsText);

      // set the instantiate button group
      boolean isInstantiatable = classDefinition.getInstantiate();
      if (isInstantiatable)
	generalPanel.canButton.setSelected(true);
      else
	generalPanel.cannotButton.setSelected(true);

      // set the icon image:
      //Structure iconDescription = classDefinition.getIconDescription();
      generalPanel.updateEditIconButton();
    }
  }

  private void createClassEditorPanel() {
    //Kb kb = currentConnection.getKb();
    //try {
    //Module module = kb.getTopLevelModule();
      //System.out.println("TopLevelModule: "+module.getName());
    //} catch (G2AccessException gae) {
    //System.out.println(gae);
    //}

    editorPanels = new TabGroupPanel();
    editorPanels.addTab(shortBundle.getString("GeneralTab"), 
			generalPanel = new GeneralPanel());
    editorPanels.addTab(shortBundle.getString("AttributesTab"),
			attributesPanel = new AttributesPanel());
    editorPanels.addTab(shortBundle.getString("MethodsTab"),
			methodsPanel = new MethodsPanel());
    editorPanels.addTab(shortBundle.getString("RelationsTab"),
			methodsPanel = new MethodsPanel());
    editorPanels.addTab(shortBundle.getString("RulesTab"),
			methodsPanel = new MethodsPanel());
    editorPanels.addAccessibleSelection(0);  
    add(editorPanels);
  }

  //public Symbol getClassName() {
  //  return Symbol.intern(generalPanel.classNameTF.getText().trim().toUpperCase());
  //}

  class GeneralPanel extends StandardGridBagPanel {

    Resource shortBundle = Resource.getBundle("com/gensym/shell/dialogs/ClassEditorResources");

    JTextField classNameTF;
    JTextField descriptionTF;
    JTextField superiorClassTF;
    //JList userClassesList;
    //JScrollPane userClassesPane;
    JButton browseButton;
    ButtonGroup instantiateGroup;
    JRadioButton canButton;
    JRadioButton cannotButton;
    JButton editIconButton;
    Image dummyImage = WindowUtil.createImage(50, 50);
    ImageIcon classIcon = new ImageIcon(dummyImage);
    ImageIcon classDisabledIcon = new ImageIcon(dummyImage);
    
    GeneralPanel () {
      GridBagConstraints labelGridC = new GridBagConstraints();
      GridBagConstraints textGridC = new GridBagConstraints();
      GridBagConstraints panelGridC = new GridBagConstraints();
      GridBagConstraints rbGridC = new GridBagConstraints();
      GridBagConstraints btnGridC = new GridBagConstraints();
      setLayout (gridBagLayout);
      
      Insets firstLabelInsets = new Insets (10, 5, 5, 0);
      Insets labelInsets = new Insets (5, 5, 5, 0);
      Insets firstTextInsets = new Insets (10, 10, 5, 5);
      Insets textInsets = new Insets (5, 10, 5, 5);
      Insets panelInsets = new Insets (0, 5, 5, 5);
      Insets rbInsets = new Insets (0, 5, 0, 5);
      
      // set JLabel constraints
      labelGridC.weightx = 0.0;
      labelGridC.fill = GridBagConstraints.NONE;
      labelGridC.anchor = GridBagConstraints.EAST;
      labelGridC.gridwidth = GridBagConstraints.RELATIVE;
      
      // set JTextField constraints
      textGridC.weightx = 1.0;
      textGridC.fill = GridBagConstraints.HORIZONTAL;
      textGridC.anchor = GridBagConstraints.WEST;
      textGridC.gridwidth = GridBagConstraints.REMAINDER;
      
      // set JPanel constraints
      panelGridC.weightx = 1.0;
      panelGridC.fill = GridBagConstraints.HORIZONTAL;
      panelGridC.anchor = GridBagConstraints.WEST;
      panelGridC.gridwidth = GridBagConstraints.REMAINDER;
      
      // set JRadioButton constraints
      rbGridC.weightx = 1.0;
      rbGridC.fill = GridBagConstraints.HORIZONTAL;
      rbGridC.anchor = GridBagConstraints.WEST;
      rbGridC.gridwidth = GridBagConstraints.REMAINDER;

      // set JButton constraints
      btnGridC.weightx = 1.0;
      btnGridC.anchor = GridBagConstraints.WEST;
      btnGridC.gridwidth = GridBagConstraints.REMAINDER;
      
      labelGridC.insets = firstLabelInsets;
      textGridC.insets = firstTextInsets;
      panelGridC.insets = panelInsets;
      rbGridC.insets = rbInsets;
      btnGridC.insets = textInsets;
      
      addComponent(new JLabel("Class Name:"), labelGridC);   
      addComponent(classNameTF = new JTextField("", 20), textGridC);
      
      labelGridC.insets = labelInsets;
      addComponent(new JLabel("Description:"), labelGridC);
      
      textGridC.insets = textInsets;
      addComponent(descriptionTF = new JTextField("", 20), textGridC);
      
      addComponent(new JLabel("Superior Class:"), labelGridC);
      
      JPanel superiorPanel = new JPanel();
      superiorPanel.setLayout(new FlowLayout(FlowLayout.LEFT));
      superiorPanel.add(superiorClassTF = new JTextField("", 20));
      superiorClassTF.addFocusListener (new FocusListener() {
	 @Override
	 public void focusGained (FocusEvent e) {
	   //System.out.println("focusGained");
	   //String classString = ((JTextField)e.getSource()).getText().trim().toUpperCase();
	   //updateEditIconButton(Symbol.intern(classString));
	   updateEditIconButton();
	 }
	 @Override
	 public void focusLost (FocusEvent e) {
	   //System.out.println("focusLost");
	   //String classString = ((JTextField)e.getSource()).getText().trim().toUpperCase();
	   //updateEditIconButton(Symbol.intern(classString));
	   updateEditIconButton();
	 }
      });
      superiorPanel.add(browseButton = new JButton("..."));
      addComponent(superiorPanel, panelGridC);

      //userClassesList = new JList(getUserDefinedClasses());
      //userClassesList.addListSelectionListener(new ListSelectionListener() {
      //public void valueChanged (ListSelectionEvent e) {
      //  if (!e.getValueIsAdjusting()) {
      //    Object selectedObj = ((JList)e.getSource()).getSelectedValue();
      //    if (selectedObj != null) {
      //      superiorClassTF.setText(selectedObj.toString().toUpperCase());
      //      superiorClassTF.requestFocus();
      //    }
      //  }
      //}
      //});
      // addComponent(userClassesPane = new JScrollPane(userClassesList), textGridC);
      
      instantiateGroup = new ButtonGroup();
      instantiateGroup.add(canButton = new JRadioButton("Concrete class - can be instantiated"));
      instantiateGroup.add(cannotButton = new JRadioButton("Abstract class - cannot be instantiated"));
      
      addComponent(canButton, rbGridC);
      addComponent(cannotButton, rbGridC);
      
      addComponent(new JLabel("Icon:"), labelGridC);
      addComponent(editIconButton = new JButton("Edit...", classIcon), btnGridC);
      editIconButton.setDisabledIcon(classDisabledIcon);
      editIconButton.setEnabled(false);
    }

    //Vector getUserDefinedClasses() {
    //Vector userDefinedClasses = new Vector();
    //Symbol startingClass = G2ClassSymbols.ITEM_;
    //getSubClasses(startingClass, userDefinedClasses);
    //return userDefinedClasses;
    //}

    //void getSubClasses(Symbol className, Vector userClasses) {
      //System.out.println("getSubClasses: "+className);
    //Class tmpClass = null;
    //G2Definition g2Def;
    //Symbol userClass;
    //try {
    //Sequence subClasses = currentConnection.getDirectSubclasses(className);
    //for (int i =0; i<subClasses.size(); i++) {
    //  try {
    //    userClass = (Symbol)subClasses.elementAt(i);
    //    g2Def = currentConnection.getDefinition(userClass);
    //    if (g2Def instanceof ClassDefinition) {
          //System.out.println("USER DEFINED CLASS: "+userClass);
    //      userClasses.addElement(userClass);
    //    }
    //  } catch (G2AccessException gae) {
    //    System.out.println(gae);
    //  }
    //  getSubClasses((Symbol)subClasses.elementAt(i), userClasses);
    //}
    // } catch (G2AccessException gae) {
    //System.out.println(gae);
    //}
    //}

    void updateEditIconButton() {
      Symbol className_ = null;
      String classNameString = classNameTF.getText().trim().toUpperCase();
      
      boolean status = false;
      className_ = Symbol.intern(classNameString);
      status = executeUpdateEditIconButton(className_);
      if (!status) {
	classNameString = superiorClassTF.getText().trim().toUpperCase();
	className_ = Symbol.intern(classNameString);
	status = executeUpdateEditIconButton(className_);
      } 
    }

    boolean executeUpdateEditIconButton(Symbol className) {
      //System.out.println("executeUpdateEditIcon, className: "+className);

      boolean status = false;

      if (className.toString().equals(""))
	return status;

      // check for class existence first
      try {
	ClassDefinition classDef = (ClassDefinition)currentConnection.getUniqueNamedItem(CLASS_DEFINITION_, className);
	if (classDef != null) {
	  //System.out.println("calling classManager.getClassAttributeValue for: "+className);
	  Structure iconDescStruct = (Structure)classManager.getClassAttributeValue(className, 
					  	          DefinitionSymbols.ICON_DESCRIPTION_);
	  Image iconImage = null;
	  if (iconDescStruct != null) {
	    IconDescription iconDesc = new IconDescription(iconDescStruct);
	    iconImage = iconDesc.createImage(iconDesc.getWidth(), iconDesc.getHeight(),
					     0, PIVOT_POINT, false, null, null);
	  } else 
	    iconImage = dummyImage;
	  
	  classIcon.setImage(iconImage);
	  classDisabledIcon.setImage(iconImage);
	  editIconButton.repaint();
	  status = true;
	}
      } catch (G2AccessException gae) {
	//System.out.println(gae);
	Trace.exception(gae);
      }

      /*
      try {
	Structure iconDescStruct = (Structure)classManager.getClassAttributeValue(className, 
							DefinitionSymbols.ICON_DESCRIPTION_);
	Image iconImage = null;
	if (iconDescStruct != null) {
	  IconDescription iconDesc = new IconDescription(iconDescStruct);
	  iconImage = iconDesc.createImage(iconDesc.getWidth(), iconDesc.getHeight(),
					   0, PIVOT_POINT, false, null, null);
	} else 
	  iconImage = dummyImage;
	  
	classIcon.setImage(iconImage);
	classDisabledIcon.setImage(iconImage);
	editIconButton.repaint();
	status = true;
      } catch (G2AccessException gae) {
	System.out.println("begin SDM: "+gae+" :end SDM");
	Trace.exception(gae);
      }
      */
     
      return status;
    }
  }


  class AttributesPanel extends StandardGridBagPanel {

    Resource shortBundle = Resource.getBundle("com/gensym/shell/dialogs/ClassEditorResources");

    JTextField hostTextField;

    AttributesPanel () {
      GridBagConstraints labelGridC = new GridBagConstraints();
      GridBagConstraints textGridC = new GridBagConstraints();
      setLayout (gridBagLayout);
      
      Insets firstLabelInsets = new Insets (10, 5, 5, 0);
      Insets labelInsets = new Insets (5, 5, 5, 0);
      Insets firstTextInsets = new Insets (10, 10, 5, 5);
      Insets textInsets = new Insets (5, 10, 5, 5);
      
      // set Label constraints
      labelGridC.gridwidth = 50;
      labelGridC.weightx = 0.0;
      labelGridC.fill = GridBagConstraints.NONE;
      labelGridC.anchor = GridBagConstraints.EAST;
      labelGridC.gridwidth = GridBagConstraints.RELATIVE;
      
      // set TextField constraints
      textGridC.weightx = 1.0;
      textGridC.gridwidth = 200;
      textGridC.fill = GridBagConstraints.HORIZONTAL;
      textGridC.anchor = GridBagConstraints.WEST;
      textGridC.gridwidth = GridBagConstraints.REMAINDER;
      
      labelGridC.insets = firstLabelInsets;
      addComponent(new JLabel("bar"), labelGridC);
      
      textGridC.insets = firstTextInsets;
      addComponent(hostTextField = new JTextField("", 20), textGridC);
    }
  }
  
  class MethodsPanel extends StandardGridBagPanel {

    Resource shortBundle = Resource.getBundle("com/gensym/shell/dialogs/ClassEditorResources");

    JTextField hostTextField;

    MethodsPanel () {
      GridBagConstraints labelGridC = new GridBagConstraints();
      GridBagConstraints textGridC = new GridBagConstraints();
      setLayout (gridBagLayout);
      
      Insets firstLabelInsets = new Insets (10, 5, 5, 0);
      Insets labelInsets = new Insets (5, 5, 5, 0);
      Insets firstTextInsets = new Insets (10, 10, 5, 5);
      Insets textInsets = new Insets (5, 10, 5, 5);
      
      // set Label constraints
      labelGridC.gridwidth = 50;
      labelGridC.weightx = 0.0;
      labelGridC.fill = GridBagConstraints.NONE;
      labelGridC.anchor = GridBagConstraints.EAST;
      labelGridC.gridwidth = GridBagConstraints.RELATIVE;
      
      // set TextField constraints
      textGridC.weightx = 1.0;
      textGridC.gridwidth = 200;
      textGridC.fill = GridBagConstraints.HORIZONTAL;
      textGridC.anchor = GridBagConstraints.WEST;
      textGridC.gridwidth = GridBagConstraints.REMAINDER;
      
      labelGridC.insets = firstLabelInsets;
      addComponent(new JLabel("bah"), labelGridC);
      
      textGridC.insets = firstTextInsets;
      addComponent(hostTextField = new JTextField("", 20), textGridC);
    }
  }
  
  class RelationsPanel extends StandardGridBagPanel {

    Resource shortBundle = Resource.getBundle("com/gensym/shell/dialogs/ClassEditorResources");

    JTextField hostTextField;

    RelationsPanel () {
      GridBagConstraints labelGridC = new GridBagConstraints();
      GridBagConstraints textGridC = new GridBagConstraints();
      setLayout (gridBagLayout);
      
      Insets firstLabelInsets = new Insets (10, 5, 5, 0);
      Insets labelInsets = new Insets (5, 5, 5, 0);
      Insets firstTextInsets = new Insets (10, 10, 5, 5);
      Insets textInsets = new Insets (5, 10, 5, 5);
      
      // set Label constraints
      labelGridC.gridwidth = 50;
      labelGridC.weightx = 0.0;
      labelGridC.fill = GridBagConstraints.NONE;
      labelGridC.anchor = GridBagConstraints.EAST;
      labelGridC.gridwidth = GridBagConstraints.RELATIVE;
      
      // set TextField constraints
      textGridC.weightx = 1.0;
      textGridC.gridwidth = 200;
      textGridC.fill = GridBagConstraints.HORIZONTAL;
      textGridC.anchor = GridBagConstraints.WEST;
      textGridC.gridwidth = GridBagConstraints.REMAINDER;
      
      labelGridC.insets = firstLabelInsets;
      addComponent(new JLabel("baa"), labelGridC);
      
      textGridC.insets = firstTextInsets;
      addComponent(hostTextField = new JTextField("", 20), textGridC);
    }
  }
  
  class RulesPanel extends StandardGridBagPanel {

    Resource shortBundle = Resource.getBundle("com/gensym/shell/dialogs/ClassEditorResources");

    JTextField hostTextField;

    RulesPanel () {
      GridBagConstraints labelGridC = new GridBagConstraints();
      GridBagConstraints textGridC = new GridBagConstraints();
      setLayout (gridBagLayout);
      
      Insets firstLabelInsets = new Insets (10, 5, 5, 0);
      Insets labelInsets = new Insets (5, 5, 5, 0);
      Insets firstTextInsets = new Insets (10, 10, 5, 5);
      Insets textInsets = new Insets (5, 10, 5, 5);
      
      // set Label constraints
      labelGridC.gridwidth = 50;
      labelGridC.weightx = 0.0;
      labelGridC.fill = GridBagConstraints.NONE;
      labelGridC.anchor = GridBagConstraints.EAST;
      labelGridC.gridwidth = GridBagConstraints.RELATIVE;
      
      // set TextField constraints
      textGridC.weightx = 1.0;
      textGridC.gridwidth = 200;
      textGridC.fill = GridBagConstraints.HORIZONTAL;
      textGridC.anchor = GridBagConstraints.WEST;
      textGridC.gridwidth = GridBagConstraints.REMAINDER;
      
      labelGridC.insets = firstLabelInsets;
      addComponent(new JLabel("moo"), labelGridC);
      
      textGridC.insets = firstTextInsets;
      addComponent(hostTextField = new JTextField("", 20), textGridC);
    }
  }
}


