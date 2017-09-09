/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 PageSetupDialog.java
 *
 */
package com.gensym.uiutil.dialogs;


import java.awt.*;
import java.awt.event.*;
import java.awt.print.*;
import javax.swing.JPanel;
import javax.swing.JButton;

import com.gensym.dlg.MessageDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.message.Resource;
import java.awt.print.PageFormat;
import com.gensym.ui.AbstractCommand;


/**
 * PageSetupDialog provides a dialog for setup of printing.
 */

public class PageSetupDialog extends StandardDialog {
  private PageSetupPanel panel;
  private PageFormat pageFormat;
  private Frame frame;
  private static Resource i18nMsgs = Resource.getBundle("com.gensym.uiutil.dialogs.Messages");
  private static Resource i18nErrors = Resource.getBundle("com.gensym.uiutil.dialogs.Errors");
  
  public PageSetupDialog(Frame frame, PageFormat pageFormat, StandardDialogClient client) {
    super(frame, "", true,
	  new String[] {OK_LABEL, CANCEL_LABEL}, 
	  new int[] {OK, CANCEL},
	  new PageSetupPanel(pageFormat), 
	  client
	  );
    
    this.frame = frame;
    this.pageFormat = pageFormat;
    this.panel = (PageSetupPanel)getDialogComponent();
    setTitle(i18nMsgs.getString("PageSetupDialogTitle"));
    
    setDefaultButton(OK);
    setCancelButton(CANCEL);
  }
  
  public PageFormat getPageFormat() {
    return panel.getPageFormat();
  }
  
  public double getZoomValue() {
    return panel.getZoomValue();
  }
  
  public static void main(String[] args) {
    Frame frame = new Frame("test");
    PrinterJob printJob = PrinterJob.getPrinterJob();
    PageFormat pageFormat = new PageFormat();
    PageSetupDialog dlg = new PageSetupDialog(frame, pageFormat, null);
    dlg.show();
    
    PageFormat atarashi = dlg.getPageFormat();
    Paper p = atarashi.getPaper();
    // next four lines cut from PageSetupPanel
    double leftMargin = p.getImageableX() / 72 ;
    double rightMargin = (p.getWidth() - p.getImageableWidth() -  p.getImageableX()) / 72;
    double topMargin = p.getImageableY() / 72;
    double bottomMargin = (p.getHeight() - p.getImageableHeight() - p.getImageableY()) / 72;
    
    System.out.println("left = " + leftMargin); 
    System.out.println("right = " + rightMargin); 
    System.out.println("top = " + topMargin);
    System.out.println("bottom = " + bottomMargin);
    
    frame.addWindowListener(new WindowAdapter() {
      @Override
      public void windowClosing(WindowEvent e) {
	System.exit(0);
      }
    });
    
    frame.pack();
    frame.setVisible(true);
  } 
}

