/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 AboutDialog.java
 *
 */
package com.gensym.dlg;

import java.awt.Frame;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

public class AboutDialog extends StandardDialog {

  private JTextArea aboutText;

  /**
   * @param parentFrame The Frame that is the parent for this instance of
   * AboutDialog
   * @param title A String containing the title for this instance of
   * AboutDialog
   * @param isModal A boolean value indicating whether or not this instance of
   * AboutDialog should be modal
   * @param aboutString A String containing the text to use for the label
   * that contains the about text.
   * @param numRows The number of rows.
   * @param numColumns The number of columns.
   * @param scrollbarVisibility A constant that determines what scrollbars
   * are created to view the text area.
   * @param client The StandardDialogClient for this dialog
   */
  public AboutDialog (Frame parentFrame, String title,
		      boolean isModal, String aboutString,
		      int numRows, int numColumns,
		      int scrollbarVisibility,
		      StandardDialogClient client) { 

    super (parentFrame, title, isModal,
	   new String[] {OK_LABEL},
	   new int[] {OK},
	   new JScrollPane(),
	   client);

    aboutText = new JTextArea (null, aboutString, numRows, numColumns);
    aboutText.setEditable(false);
    aboutText.setBackground(getParent().getBackground());
    JScrollPane scrollPane = (JScrollPane)getDialogComponent();
    scrollPane.setViewportView(aboutText);
    pack ();
  }

  /**
   * @return The JTextArea that contains the "about" text
   */
  public JTextArea getAboutJTextArea(){
    return aboutText;
  }

  /**
   * @deprecated As of version 1.1, replaced by <code>getAboutJTextArea()</code>.
   */
  public java.awt.TextArea getAboutTextArea(){
    throw new Error("Do not use com.gensym.dlg.AboutDialog.getAboutTextArea()"+
		    " use com.gensym.dlg.AboutDialog.getAboutJTextArea() instead.");
  }

  /**
   * Called from StandardDialog to lay out buttons
   */
  @Override
  public int getButtonAlignment () {
    return CENTER;
  }
}


