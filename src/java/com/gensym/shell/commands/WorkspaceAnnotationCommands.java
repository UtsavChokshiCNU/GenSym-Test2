/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 WorkspaceAnnotationCommands
 *
 */
package com.gensym.shell.commands;

import java.awt.event.ActionEvent;
import com.gensym.message.Trace;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.dlg.StandardDialog;
import javax.swing.JPanel;
import com.gensym.message.Resource;
import java.awt.Frame;
import com.gensym.wksp.WorkspaceView;
import java.awt.GridLayout;
import javax.swing.JCheckBox;

public class WorkspaceAnnotationCommands extends AbstractCommand {

  public static final String EDIT_ANNOTATIONS = "editAnnotations";
  public static final String TOGGLE_ANNOTATION_VISIBILITY = "toggleAnnotationVisibility";
  private static final String shortResource = "CommandShortResource";
  private static final String longResource  = "CommandLongResource";
  private static final String mnemonicResource = "MnemonicResource";
  private static Resource i18n = Resource.getBundle("com/gensym/shell/commands/CommandShortResource");
  private Frame frame;
  private static final String[] availableAnnotations = WorkspaceView.getAvailableAnnotations();
  static final String HAS_NOTES="hasNotes";
  static final String IS_PERMANENT="isPermanent";

  public WorkspaceAnnotationCommands(Frame frame) {
    super(new CommandInformation[]{
	new CommandInformation(EDIT_ANNOTATIONS, true,
			       shortResource, longResource,
			       "editAnnotations.gif", null, null, true,
			       mnemonicResource, null),
	  new CommandInformation(TOGGLE_ANNOTATION_VISIBILITY, true,
				 shortResource, longResource,
				 "annotations.gif", null, Boolean.FALSE, true,
				 mnemonicResource, null)});
    this.frame = frame;
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey.equals(EDIT_ANNOTATIONS)) {
      boolean[] currentAnnotationStates = WorkspaceView.getCurrentAnnotationStates();
      AnnotationsEditor ae =
	new AnnotationsEditor(frame, availableAnnotations,currentAnnotationStates);
      ae.setVisible(true);
      if (!ae.wasCancelled()) 
	WorkspaceView.setCurrentAnnotationStates(ae.getAnnotationStates());
    } else if (cmdKey.equals(TOGGLE_ANNOTATION_VISIBILITY)) {
      WorkspaceView.setAnnotationsVisible(!WorkspaceView.getAnnotationsVisible());
    }
    frame.repaint();
  }

  class AnnotationsEditor extends StandardDialog {
    private AnnotationsEditorPanel annotationsEditorPanel; 
    public AnnotationsEditor(Frame frame, String[] annotations, boolean[] annotationStates) {
      super(frame, i18n.getString(EDIT_ANNOTATIONS), true,
	    new String[] {OK_LABEL, CANCEL_LABEL},
	    new int[] {OK, CANCEL},
	    new AnnotationsEditorPanel(annotations, annotationStates),
	    null);
      annotationsEditorPanel = (AnnotationsEditorPanel)getDialogComponent();      
    }
    public boolean[] getAnnotationStates() {
      return annotationsEditorPanel.getStates();
    }
  }
}

  class AnnotationsEditorPanel extends JPanel {
    static Resource i18n = Resource.getBundle("com.gensym.shell.commands.CommandShortResource");
    JCheckBox[] statesUI;
    AnnotationsEditorPanel(String[] annotations, boolean[] annotationStates) {
      int count = annotations.length;
      if (count != annotationStates.length) return;//throw an exception
      setLayout(new GridLayout(count+2, 1));      
      statesUI = new JCheckBox[count];
      for (int i=0;i<count;i++) {
	String annotation = i18n.getString(annotations[i]);
	boolean state = annotationStates[i];
	JCheckBox ui = new JCheckBox(annotation, state);
	statesUI[i]=ui;
	add(ui);
      }
      JCheckBox ui = new JCheckBox(i18n.getString(WorkspaceAnnotationCommands.HAS_NOTES), false);
      ui.setEnabled(false);
      add(ui);
      ui = new JCheckBox(i18n.getString(WorkspaceAnnotationCommands.IS_PERMANENT), false);
      ui.setEnabled(false);
      add(ui);      
    }
    boolean[] getStates() {
      int count = statesUI.length;
      boolean[] states= new boolean[count];
      for (int i=0;i<count;i++)
	states[i]=statesUI[i].isSelected();
      return states;
    }
  }  











