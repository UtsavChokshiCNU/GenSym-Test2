/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ZoomDialog.java
 *
 */
package com.gensym.uiutil.dialogs;

import java.awt.Frame;
import com.gensym.dlg.MessageDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.message.Resource;

/**
 * ZoomDialog provides a dialog for users to choose a zoom scale.
 */
public class ZoomDialog extends StandardDialog{

  public static final double ZOOM_TO_FIT = 0.0;

  private ZoomPanel panel;
  private Frame frame;
  private Resource i18nMsgs = Resource.getBundle("com.gensym.uiutil.dialogs.Messages");
  private Resource i18nErrors = Resource.getBundle("com.gensym.uiutil.dialogs.Errors");

  public ZoomDialog(Frame frame, double currentZoomX, double currentZoomY, StandardDialogClient client){
    this(frame, currentZoomX, currentZoomY, null, null, true, true, client);
  }

  public ZoomDialog(Frame frame, double currentZoomX, double currentZoomY, 
		    double[] zoomValues, String[] zoomValueLabels, boolean zoomToFit,
		    boolean zoomPercent, StandardDialogClient client){
    super(frame, "", true,
	  new String[] {OK_LABEL, APPLY_LABEL, CANCEL_LABEL}, new int[] {OK, APPLY, CANCEL},
	  new ZoomPanel(zoomValues, zoomValueLabels, zoomToFit, zoomPercent, 
			currentZoomX, currentZoomY, ZOOM_TO_FIT), 
	  client);

    this.frame = frame;
    this.panel = (ZoomPanel)getDialogComponent();

    setTitle(i18nMsgs.getString("ZoomDialogTitle"));

    setDefaultButton(OK);
    setCancelButton(CANCEL);
    panel.setKeyInterpreter(getStandardKeyInterpreter());
  }
  
  /**
   * Returns the current selected value.  If zoomed to fit was selected, the return value is ZOOM_TO_FIT.
   */
  public double getValue(){
    return panel.getValue();
  }

  @Override
  protected void dispatchCallback(int code){
    String validationFailure = null;
    if (code == OK || code == APPLY)
      validationFailure = panel.validateInput();
    if (validationFailure == null)
      super.dispatchCallback(code);
    else
      new MessageDialog(frame, i18nErrors.getString("Error"), true, 
			validationFailure, null).setVisible(true);
  }
}

















