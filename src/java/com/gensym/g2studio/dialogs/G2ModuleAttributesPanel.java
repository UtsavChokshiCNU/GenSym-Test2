/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2ModuleAttributesPanel.java
 *
 *  Description:
 *
 *
 *	 Author:
 *		Todd O'Brien		Feb/98
 *
 *     
 *   Modifications:
 *
 */

package com.gensym.g2studio.dialogs;

import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.awt.Label;
import java.awt.List;
import java.awt.TextField;
import com.gensym.classes.Module;
import com.gensym.classes.ModuleInformation;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Resource;
import com.gensym.uiutil.StandardGridBagPanel;
import com.gensym.util.Symbol;

/**
 */
public class G2ModuleAttributesPanel extends StandardGridBagPanel {
  TextField nameField, filenameField, changeLogField, annotationsField;
  List      requiredByList;
  Label     nameLabel, filenameLabel, changeLogLabel, annotationsLabel,
            requiredByLabel;
  int       fieldWidth = 24;
  String    name, filename, changeLog, annotations;

  private static Resource shortBundle = Resource.getBundle("com/gensym/g2studio/dialogs/CommandShortResource");

  /**
   */
  public G2ModuleAttributesPanel(Module module)
  {
    super();

    setLayout(gridBagLayout);
    GridBagConstraints constraints = new GridBagConstraints();
    constraints.fill = GridBagConstraints.BOTH;
    constraints.insets  = new Insets (10, 0, 0, 10);

    constraints.weightx = 0;
    constraints.gridwidth = GridBagConstraints.RELATIVE;
    addComponent(nameLabel = new Label(shortBundle.getString("G2ModuleAttributesPanelNameLabel")), constraints);
    nameLabel.setAlignment(Label.RIGHT);

    constraints.weightx = 1;
    constraints.gridwidth = GridBagConstraints.REMAINDER;
    addComponent(nameField = new TextField("", fieldWidth), constraints);

    constraints.weightx = 0;
    constraints.gridwidth = GridBagConstraints.RELATIVE;
    addComponent(filenameLabel = new Label(shortBundle.getString("G2ModuleAttributesPanelFilenameLabel")), constraints);
    filenameLabel.setAlignment(Label.RIGHT);

    constraints.weightx = 1;
    constraints.gridwidth = GridBagConstraints.REMAINDER;
    addComponent(filenameField = new TextField("", fieldWidth), constraints);

    constraints.weightx = 0;
    constraints.gridwidth = GridBagConstraints.RELATIVE;
    addComponent(changeLogLabel = new Label(shortBundle.getString("G2ModuleAttributesPanelChangeLogLabel")), constraints);
    changeLogLabel.setAlignment(Label.RIGHT);

    constraints.weightx = 1;
    constraints.gridwidth = GridBagConstraints.REMAINDER;
    addComponent(changeLogField = new TextField("", fieldWidth), constraints);

    constraints.weightx = 0;
    constraints.gridwidth = GridBagConstraints.RELATIVE;
    addComponent(annotationsLabel = new Label(shortBundle.getString("G2ModuleAttributesPanelAnnotationsLabel")), constraints);
    annotationsLabel.setAlignment(Label.RIGHT);

    constraints.weightx = 1;
    constraints.gridwidth = GridBagConstraints.REMAINDER;
    addComponent(annotationsField = new TextField("", fieldWidth), constraints);

    constraints.weightx = 0;
    constraints.gridwidth = GridBagConstraints.RELATIVE;
    addComponent(requiredByLabel = new Label(shortBundle.getString("G2ModuleAttributesPanelRequiredByLabel")), constraints);
    requiredByLabel.setAlignment(Label.RIGHT);

    constraints.weightx = 1;
    constraints.weighty = 1;
    constraints.gridheight = 4;
    constraints.insets  = new Insets (10, 0, 10, 10);
    addComponent(requiredByList = new List(), constraints);

    try {
      ModuleInformation info = module.getModuleInformation();
      Symbol nameSymbol = module.getName();

      name = (nameSymbol != null) ? nameSymbol.getPrintValue() : "";
      //filename    = (String)info.getModuleFileName();
      changeLog = new String("");
      annotations = new String("");

      if (info == null) 
	System.out.println ("info is null");
      if (info.getModuleFileName() == null) 
	System.out.println ("filename is null");

      nameField.setText(name);
      filenameField.setText(filename);
      changeLogField.setText(changeLog);
      annotationsField.setText(annotations);
    }
    catch(G2AccessException ex) {
    }
  }
}


