package com.gensym.shell.commands;

import java.awt.Frame;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;
import com.gensym.classes.KbWorkspace;
import com.gensym.mdi.MDIDocument;
import com.gensym.mdi.MDIEvent;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIManager;
import com.gensym.mdi.MDIListener;
import com.gensym.shell.util.WorkspaceDocument;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.wksp.WorkspaceView;

abstract class WorkspaceViewSelectedCommand extends BasicCommand{

  private WorkspaceView currentView;
  private DocumentAdapter documentAdapter = new DocumentAdapter();

  protected WorkspaceViewSelectedCommand(StructuredCommandInformation[] structure, Frame frame){
    this(structure, frame, null);
  }

  protected WorkspaceViewSelectedCommand(StructuredCommandInformation[] structure, Frame frame, 
					 WorkspaceView view){
    super(structure, frame);

    if (isMDIApplication()){
      MDIManager manager = ((MDIFrame)frame).getManager();
      manager.addMDIListener(documentAdapter);
      MDIDocument[] docs = manager.getDocuments();
      for (int i=0; i<docs.length; i++){
	if (docs[i] instanceof WorkspaceDocument)
	  docs[i].addPropertyChangeListener(documentAdapter);
      }
      MDIDocument doc = manager.getActiveDocument();
      if (doc instanceof WorkspaceDocument)
	setWorkspaceView(((WorkspaceDocument)doc).getWorkspaceView());
      else
	setAvailability(false);
    }
    else
      setWorkspaceView(view);
  }

  public void setWorkspaceView(WorkspaceView view){
    currentView = view;
    updateAvailability();
  }

  protected WorkspaceView getWorkspaceView(){
    return currentView;
  }

  protected void updateAvailability(){
    if (currentView != null){
      KbWorkspace wksp = currentView.getWorkspace();
      setAvailability(wksp != null && wksp.isValid());
    }
    else
      setAvailability(false);
  }

  class DocumentAdapter implements PropertyChangeListener, MDIListener{

    @Override
    public void documentAdded(MDIEvent event) {
      MDIDocument document = event.getDocument();
      if (document instanceof WorkspaceDocument) {
	WorkspaceDocument wkspDoc = (WorkspaceDocument)document;
	wkspDoc.addPropertyChangeListener(this);
	setWorkspaceView(wkspDoc.getWorkspaceView());
      }
    }

    @Override
    public void propertyChange(PropertyChangeEvent e) {
      WorkspaceDocument document = (WorkspaceDocument)e.getSource();
      if (e.getPropertyName().equals(WorkspaceDocument.IS_SELECTED_PROPERTY)){
	Boolean selected = (Boolean)e.getNewValue();
	if (selected.booleanValue())
	  setWorkspaceView(document.getWorkspaceView());
	else
	  setWorkspaceView(null);
      }
      else if (e.getPropertyName().equals(WorkspaceDocument.IS_CLOSED_PROPERTY)){
	document.removePropertyChangeListener(this);
	MDIDocument activeDocument = ((MDIFrame)getFrame()).getManager().getActiveDocument();
	WorkspaceView view = null;
	if (activeDocument instanceof WorkspaceDocument) 
	  view = ((WorkspaceDocument)activeDocument).getWorkspaceView();
	setWorkspaceView(view);
      }
    }
  }

}
