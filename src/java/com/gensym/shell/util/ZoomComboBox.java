 /*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ZoomComboBox.java
 *
 */
package com.gensym.shell.util;

import java.awt.Font;
import java.awt.Dimension;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.text.NumberFormat;
import javax.swing.JComboBox;
import javax.swing.ComboBoxEditor;
import com.gensym.mdi.MDIListener;
import com.gensym.wksp.ScalableWorkspaceView;
import com.gensym.ui.toolbar.ToolBar;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIEvent;
import com.gensym.mdi.MDIManager;
import com.gensym.mdi.MDIDocument;
import com.gensym.mdi.MDIToolBarPanel;
import com.gensym.ntw.WorkspaceShowingListener;
import com.gensym.ntw.WorkspaceShowingEvent;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;
import com.gensym.classes.KbWorkspace;
import com.gensym.wksp.WorkspaceView;
import com.gensym.wksp.TransformationListener;
import com.gensym.wksp.TransformationEvent;

public class ZoomComboBox extends JComboBox implements TransformationListener
{
  private ScalableWorkspaceView currentView;
  private MDIFrame frame;    
  private DocumentAdapter documentAdapter = new DocumentAdapter();
  private static final String SCALE_TO_FIT = "Fit";
  private static NumberFormat nf = NumberFormat.getPercentInstance();  
  private static String[] defaultScales =
  {pprintScale(4.0), pprintScale(2.0), pprintScale(1.5),
   pprintScale(1.0), pprintScale(.75), pprintScale(.5), pprintScale(.25),
   pprintScale(.1), SCALE_TO_FIT};

  public ZoomComboBox (ScalableWorkspaceView view) {
    this((MDIFrame)null);
    setWorkspaceView(view);
  }

  /**
   * @param frame an MDIFrame to which this combo box should listener to
   * mdi events in order to determine the currently selected workspace view.
   */
  public ZoomComboBox (MDIFrame frame) {
    super(defaultScales);
    setToolTipText("Zoom");
    this.frame = frame;
    setFont(new Font("Arial", Font.PLAIN, 12));
    setPreferredSize(new Dimension(70, 20));
    setEditable(true);
    setEnabled(false);
    addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
        ZoomComboBox zcb = (ZoomComboBox)e.getSource();
	if (currentView != null)
	  zcb.zoomCurrentView();
      } 
    }); 
    addMDIListeners(frame);
  }
  
  /**
   * Sets the workspace view component. Adds itself as a transformation
   * listener to the view.
   * @param view the new ScalableWorkspaceView for which this combo box should
   * be scaling.
   */
  public void setWorkspaceView(ScalableWorkspaceView view){
    if (currentView == view) return;
    if (currentView !=  null)
      currentView.removeTransformationListener(this);
    currentView = view;
    boolean haveScalableView =(currentView != null);
    setEnabled(haveScalableView);
    if (haveScalableView) {
      updateScale(currentView);      
      currentView.addTransformationListener(this);          
    }
  }

  private static String pprintScale(double scale) {
    return nf.format(scale);
  }

  /**
   * If the source of the event is a ScalableWorkspaceView,
   * updates the currently displayed scale using the 
   * scale contained in the transformation.
   */
  @Override
  public void transformationChanged(TransformationEvent event) {
    Object source = event.getSource();
    if (source instanceof ScalableWorkspaceView)
      updateScale((ScalableWorkspaceView)source);
  }

  /**
   * @return the current workspace view component
   */
  protected WorkspaceView getWorkspaceView(){
    return currentView;
  }

  private void addMDIListeners(MDIFrame frame) {
    if (frame != null) {
      MDIManager manager = frame.getManager();
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
	setWorkspaceView(null);
    }
  }

  private final void setWorkspaceView(WorkspaceView view) {
    if (view instanceof ScalableWorkspaceView)
      setWorkspaceView((ScalableWorkspaceView)view);
    else
      setWorkspaceView((ScalableWorkspaceView)null);
  }
  
  @Override
  public void setEnabled(boolean enabled) {
    super.setEnabled(enabled);
    if (!enabled) {
      ComboBoxEditor cbe = (ComboBoxEditor)getEditor();      
      cbe.setItem("  ");
    } 
  }
  
  private void updateScale(ScalableWorkspaceView view) {
    double xScale = view.getScaleX ();
    ComboBoxEditor cbe = (ComboBoxEditor)getEditor();      
    cbe.setItem(pprintScale(xScale));
  }
  
  private void zoomCurrentView() {
    String arg = (String)getSelectedItem();      
    ComboBoxEditor cbe = (ComboBoxEditor)getEditor();
    if (SCALE_TO_FIT.equals(arg)) 
      currentView.setScaledToFit(true);
    else {
      if (arg.indexOf('%') == -1) arg+="%";
      try {
        currentView.setScaledToFit(false);	
        float i = nf.parse(arg).floatValue();
        currentView.setScaleX(i);
        currentView.setScaleY(i);
      } catch (NumberFormatException nfe) {
	updateScale(currentView);
      } catch (java.text.ParseException pe) {
	updateScale(currentView);
      } catch (java.awt.geom.NoninvertibleTransformException nite) {
	updateScale(currentView);
      }
    }
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
      } else if (e.getPropertyName().equals(WorkspaceDocument.IS_CLOSED_PROPERTY)){
	document.removePropertyChangeListener(this);
	MDIDocument activeDocument = frame.getManager().getActiveDocument();
	WorkspaceView view = null;
	if (activeDocument instanceof WorkspaceDocument)
	  view = ((WorkspaceDocument)activeDocument).getWorkspaceView();
	setWorkspaceView(view);
      }
    }
  }  
}


