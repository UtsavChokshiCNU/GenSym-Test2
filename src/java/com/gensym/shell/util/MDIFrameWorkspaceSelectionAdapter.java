package com.gensym.shell.util;

import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.jgi.G2AccessException;
import com.gensym.mdi.MDIDocument;
import com.gensym.mdi.MDIEvent;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIListener;
import com.gensym.message.Trace;
import com.gensym.ntw.util.SelectionEvent;
import com.gensym.ntw.util.SelectionListener;
import com.gensym.shell.util.WorkspaceDocument;
import com.gensym.wksp.WorkspaceElement;
import com.gensym.wksp.WorkspaceView;
import java.util.Vector;

public class MDIFrameWorkspaceSelectionAdapter
implements PropertyChangeListener, SelectionListener, MDIListener
{
  private Vector listeners = new Vector();
  private MDIFrame frame;
  private WorkspaceView workspaceView = null;
  
  public MDIFrameWorkspaceSelectionAdapter(MDIFrame frame) {
    this.frame = frame;
    frame.getManager().addMDIListener(this);
    MDIDocument[] docs = frame.getManager().getDocuments();
    for (int i=0; i<docs.length; i++){
      if (docs[i] instanceof WorkspaceDocument)
	docs[i].addPropertyChangeListener(this);
    }
    MDIDocument activeDocument = frame.getManager().getActiveDocument();
    if (activeDocument instanceof WorkspaceDocument)
      setWorkspaceView(((WorkspaceDocument)activeDocument).getWorkspaceView());
  }
  
  private void setWorkspaceView(WorkspaceView workspaceView) {
    if (this.workspaceView != null) 
      this.workspaceView.removeSelectionListener(this);    
    this.workspaceView = workspaceView;
    if (workspaceView != null) 
      workspaceView.addSelectionListener(this);
    notifyListeners(workspaceView);
  }
  
  public void addSelectionListener(SelectionListener sl) {
    listeners.add(sl);
  }

  public void removeSelectionListener(SelectionListener sl) {
    listeners.remove(sl);
  }

  private void notifyListeners(SelectionEvent se) {
    SelectionListener[] lst;
    synchronized(listeners) {
      lst = new SelectionListener[listeners.size()];
      listeners.copyInto(lst);
    }
    for (int i=0;i<lst.length;i++)
      lst[i].selectionChanged(se);
  }

  private void notifyListeners(WorkspaceView view) {
    Object source = view;
    if (source == null) source = this;
    notifyListeners(new SelectionEvent(source));
  }

  @Override
  public void selectionChanged(SelectionEvent event){
    notifyListeners(event);
  }

  @Override
  public void documentAdded(MDIEvent event) {
    MDIDocument document = (MDIDocument)event.getDocument();
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
    } else if (e.getPropertyName().equals(WorkspaceDocument.IS_CLOSED_PROPERTY)){
      document.removePropertyChangeListener(this);
      setWorkspaceView(null);
    } else if (document.isClosed()) {
      document.removePropertyChangeListener(this);
      setWorkspaceView(null);
    }
  }
  
}
