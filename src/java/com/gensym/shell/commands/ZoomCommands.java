/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ZoomCommands.java
 *
 */
package com.gensym.shell.commands;

import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.geom.NoninvertibleTransformException;
import javax.swing.KeyStroke;
import java.awt.Event;
import java.awt.event.KeyEvent;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.uiutil.dialogs.ZoomDialog;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.wksp.ScalableWorkspaceView;

/**
 * This command may be used to scale the current workspace view.  This command 
 * uses features only available in JDK 1.2 or later.  A ZoomCommands may be used
 * in both MDI and SDI applications. In SDI applications, use the setWorkspaceView method
 * to inform the command of the current workspace view.
 */
public final class ZoomCommands extends WorkspaceViewSelectedCommand {

  public static final String ZOOM = "Zoom";
  public static final String ZOOM_IN = "ZoomIn";
  public static final String ZOOM_OUT = "ZoomOut";

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private static final String mnemonicResource = "MnemonicResource";
  private Resource i18nErrors = Resource.getBundle("com.gensym.shell.commands.Errors");

  private double[] zoomValues;
  private String[] zoomValueLabels;
  private boolean includeZoomToFit = true;
  private boolean includeZoomPercent = true;

  private double zoomInAmount = 1.25;
  private double zoomOutAmount = 0.8;

  /**
   * Create a new ZoomCommands with a default zoomInAmount of 1.2 and a default
   * zoomOutAmount of 0.8.
   * @see ZoomCommands(Frame, double[], labels[], boolean, boolean, double, double)
   */
  public ZoomCommands(Frame frame){
    super(new CommandInformation[]{
      new CommandInformation(ZOOM, true, shortResource, longResource, "zoom.gif", 
			     null, null, false, mnemonicResource,
			     KeyStroke.getKeyStroke('M', Event.CTRL_MASK)),
      new CommandInformation(ZOOM_IN, true, shortResource, longResource, "zoomin.gif", 
			     null, null, true, mnemonicResource,
			     KeyStroke.getKeyStroke('=',//KeyEvent.VK_PLUS, swing bug using '+'
						    Event.CTRL_MASK)),
      new CommandInformation(ZOOM_OUT, true, shortResource, longResource, "zoomout.gif", 
			     null, null, true, mnemonicResource,
			     KeyStroke.getKeyStroke(KeyEvent.VK_MINUS,
						    Event.CTRL_MASK))}, frame);
  }

  /**
   * @param zoomInAmount the ratio to multiply the current scale
   * by when zooming "in" (i.e., making larger). Should be greater than 1.0
   * @param zoomOutAmount the ratio to multiply the current scale
   * by when zooming "out" (i.e., making smaller). Should be less than 1.0
   */
  public ZoomCommands(Frame frame, double[] values, String[] labels, boolean includeZoomToFit, 
		     boolean includeZoomPercent, double zoomInAmount, double zoomOutAmount){
    this(frame);
    this.zoomValues = values;
    this.zoomValueLabels = labels;
    this.includeZoomToFit = includeZoomToFit;
    this.includeZoomPercent = includeZoomPercent;
    this.zoomInAmount = zoomInAmount;
    this.zoomOutAmount = zoomOutAmount;
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (!isAvailable(cmdKey))
      throw new IllegalStateException(i18nErrors.format("CommandIsUnavailable", cmdKey));

    try{
      if (cmdKey.equals(ZOOM)){
	ScalableWorkspaceView view = (ScalableWorkspaceView)getWorkspaceView();
	new ZoomDialog(getFrame(), view.getScaleX(), view.getScaleY(), zoomValues, zoomValueLabels, 
		       includeZoomToFit, includeZoomPercent, new ZoomDialogClient()).setVisible(true);
      }
      else if (cmdKey.equals(ZOOM_IN)){
	ScalableWorkspaceView view = (ScalableWorkspaceView)getWorkspaceView();
	view.setScale(view.getScaleX() * zoomInAmount, view.getScaleY() * zoomInAmount);
      }
      else{
	ScalableWorkspaceView view = (ScalableWorkspaceView)getWorkspaceView();
	double sx = view.getScaleX();
	double sy = view.getScaleY();
	view.setScale(sx * zoomOutAmount, sy * zoomOutAmount);
      }
    }
    catch(NoninvertibleTransformException ex){
      //This should not happen
      Trace.exception(ex);
    }
  }

  /**
   * For SDI applications, sets the current workspace view for the command.  This will
   * trigger the command to update its availability.
   */
  public void setWorkspaceView(ScalableWorkspaceView view){
    super.setWorkspaceView(view);
  }

  class ZoomDialogClient implements StandardDialogClient{

    @Override
    public void dialogDismissed(StandardDialog dlg, int cmdCode){
      if (dlg.wasCancelled()) return;

      ScalableWorkspaceView view = (ScalableWorkspaceView)getWorkspaceView();
      ZoomDialog zoomDialog = (ZoomDialog)dlg; 
      double scale = zoomDialog.getValue();
      try{
	if (scale == zoomDialog.ZOOM_TO_FIT)
	  view.setScaledToFit(true);
	else
	  view.setScale(scale, scale);
      }
      catch(NoninvertibleTransformException ex){
	//this should never happen
	Trace.exception(ex);
      }
    }
  }

}
