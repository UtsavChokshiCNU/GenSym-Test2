/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ZoomCommands.java
 *
 */
package com.gensym.editor.icon.shell;

import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.geom.NoninvertibleTransformException;
import javax.swing.KeyStroke;
import java.awt.Event;
import java.awt.event.KeyEvent;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.uiutil.dialogs.ZoomDialog;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.editor.icon.core.IconEditorCanvas;
import com.gensym.mdi.MDIListener;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIEvent;
import com.gensym.mdi.MDIDocument;

/**
 * This command may be used to scale the current workspace view.  This command 
 * uses features only available in JDK 1.2 or later.  A ZoomCommands may be used
 * in both MDI and SDI applications. In SDI applications, use the setWorkspaceView method
 * to inform the command of the current workspace view.
 */
public final class ZoomCommands extends AbstractStructuredCommand
implements MDIListener, PropertyChangeListener {

  public static final String ZOOM = "Zoom";
  public static final String ZOOM_IN = "ZoomIn";
  public static final String ZOOM_OUT = "ZoomOut";

  private static final String shortResource = "IconEditorShortResource";
  private static final String longResource = "IconEditorShortResource";
  private static final String mnemonicResource = "IconEditorMnemonicResource";
  private Resource i18nErrors = Resource.getBundle("com.gensym.shell.commands.Errors");

  private double[] zoomValues;
  private String[] zoomValueLabels;
  private boolean includeZoomToFit = false;
  private boolean includeZoomPercent = true;

  private double zoomInAmount = 1.25;
  private double zoomOutAmount = 0.8;

  private IconEditorCanvas currentCanvas;
  private IconEditor frame;
  
  /**
   * Create a new ZoomCommands with a default zoomInAmount of 1.2 and a default
   * zoomOutAmount of 0.8.
   * @see ZoomCommands(Frame, double[], labels[], boolean, boolean, double, double)
   */
  public ZoomCommands(IconEditor frame){
    super(new CommandInformation[]{
      new CommandInformation(ZOOM, true, shortResource, longResource, "zoomimage.gif", 
			     null, null, false, mnemonicResource,
			     KeyStroke.getKeyStroke('M', Event.CTRL_MASK)),
      new CommandInformation(ZOOM_IN, true, shortResource, longResource, "zoominimage.gif", 
			     null, null, true, mnemonicResource,
			     KeyStroke.getKeyStroke('=',//KeyEvent.VK_PLUS, swing bug using '+'
						    Event.CTRL_MASK)),
      new CommandInformation(ZOOM_OUT, true, shortResource, longResource, "zoomoutimage.gif", 
			     null, null, true, mnemonicResource,
			     KeyStroke.getKeyStroke(KeyEvent.VK_MINUS,
						    Event.CTRL_MASK))});
    if (frame != null) {
      this.frame = frame;
      frame.getManager().addMDIListener(this);
      MDIDocument[] docs = frame.getManager().getDocuments();
      for (int i=0; i<docs.length; i++){
	if (docs[i] instanceof IconEditorSessionDocument)
	  docs[i].addPropertyChangeListener(this);
      }
    } 
  }

  /**
   * @param zoomInAmount the ratio to multiply the current scale
   * by when zooming "in" (i.e., making larger). Should be greater than 1.0
   * @param zoomOutAmount the ratio to multiply the current scale
   * by when zooming "out" (i.e., making smaller). Should be less than 1.0
   */
  public ZoomCommands(IconEditor frame, double[] values, String[] labels, boolean includeZoomToFit, 
		     boolean includeZoomPercent, double zoomInAmount, double zoomOutAmount){
    this(frame);
    this.zoomValues = values;
    this.zoomValueLabels = labels;
    this.includeZoomToFit = includeZoomToFit;
    this.includeZoomPercent = includeZoomPercent;
    this.zoomInAmount = zoomInAmount;
    this.zoomOutAmount = zoomOutAmount;
  }

  protected void updateAvailability() {
    boolean available;
    available = (currentCanvas != null);
    setAvailable(ZOOM, available);
    setAvailable(ZOOM_IN, available);
    setAvailable(ZOOM_OUT, available);
  }
  
  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (!isAvailable(cmdKey))
      throw new IllegalStateException(i18nErrors.format("CommandIsUnavailable", cmdKey));

    try{
      if (cmdKey.equals(ZOOM)){
	new ZoomDialog(frame, currentCanvas.getScaleX(),
				currentCanvas.getScaleY(),
		       zoomValues, zoomValueLabels, 
		       includeZoomToFit, includeZoomPercent,
		       new ZoomDialogClient()).setVisible(true);
      }
      else if (cmdKey.equals(ZOOM_IN)){
	currentCanvas.setScale(currentCanvas.getScaleX() * zoomInAmount,
			       currentCanvas.getScaleY() * zoomInAmount);
      }
      else{
	double sx = currentCanvas.getScaleX();
	double sy = currentCanvas.getScaleY();
	currentCanvas.setScale(sx * zoomOutAmount, sy * zoomOutAmount);
      }
  }
    catch(NoninvertibleTransformException ex){
      //This should not happen
      Trace.exception(ex);
      }
  }
  
  private void setCurrentCanvas(IconEditorCanvas canvas) {
    currentCanvas = canvas;
  }

  @Override
  public void documentAdded(MDIEvent event) {
    MDIDocument document = (MDIDocument)event.getDocument();
    if (document instanceof IconEditorSessionDocument) {
      IconEditorSessionDocument iconDoc = (IconEditorSessionDocument)document;
      iconDoc.addPropertyChangeListener(this);
      setCurrentCanvas(iconDoc.getCanvas());      
    }
  }

  @Override
  public void propertyChange(PropertyChangeEvent e) {
    MDIDocument document = (MDIDocument)e.getSource();
    if (document instanceof IconEditorSessionDocument) {
      IconEditorSessionDocument iconDoc = (IconEditorSessionDocument)document;
      if (e.getPropertyName().equals(IconEditorSessionDocument.IS_SELECTED_PROPERTY)){
	Boolean selected = (Boolean)e.getNewValue();
	//if (selected.booleanValue()) selected = new Boolean(!document.isIcon());
	if (selected.booleanValue()) {
	  setCurrentCanvas(iconDoc.getCanvas());	  
	} else {
	  //setCurrentDocument(null);	  
	}
      }
    }
  }


  class ZoomDialogClient implements StandardDialogClient{

    @Override
    public void dialogDismissed(StandardDialog dlg, int cmdCode){
      if (dlg.wasCancelled()) return;

      ZoomDialog zoomDialog = (ZoomDialog)dlg; 
      double scale = zoomDialog.getValue();
      try{
	currentCanvas.setScale(scale, scale);
      }
      catch(NoninvertibleTransformException ex){
	//this should never happen
	Trace.exception(ex);
      }
    }
  }

}
