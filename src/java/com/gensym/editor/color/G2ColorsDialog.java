/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2ColorsDialog.java
 *
 */
package com.gensym.editor.color;

import java.awt.Color;
import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.util.Symbol;

public class G2ColorsDialog extends StandardDialog {

  private G2ColorsPanel colorsPanel = null;

  /**
   * @param parentFrame The Frame that is the parent for this instance of
   * G2ColorsDialog
   * @param title A String containing the title for this instance of
   * G2ColorsDialog
   * @param isModal A boolean value indicating whether or not this instance of
   * G2ColorsDialog should be modal
   * @param numColumns The number of columns used in displaying colors in the
   * G2ColorCanvas
   * @param optionalColorsToInclude An integer value indicating whether or not
   * to include colors blocks for TRANSPARENT and/or FOREGROUND.
   * @param client The StandardDialogClient for this G2ColorsDialog
   */
  public G2ColorsDialog (Frame parentFrame, String title,
			 boolean isModal,
			 int numColumns,
			 int optionalColorsToInclude,
			 StandardDialogClient client) { 

    super (parentFrame, title, isModal,
	   new String[] {OK_LABEL, APPLY_LABEL, CANCEL_LABEL},
	   new int[] {OK, APPLY, CANCEL},
	   new G2ColorsPanel(numColumns, optionalColorsToInclude),
	   client);

    initialize();
  }

  /**
   * @param parentFrame The Frame that is the parent for this instance of
   * G2ColorsDialog
   * @param title A String containing the title for this instance of
   * G2ColorsDialog
   * @param isModal A boolean value indicating whether or not this instance of
   * G2ColorsDialog should be modal
   * @param numColumns The number of columns used in displaying colors in the
   * G2ColorCanvas
   * @param client The StandardDialogClient for this G2ColorsDialog
   */
  public G2ColorsDialog (Frame parentFrame, String title,
			 boolean isModal,
			 int numColumns,
			 StandardDialogClient client) { 

    super (parentFrame, title, isModal,
	   new String[] {OK_LABEL, APPLY_LABEL, CANCEL_LABEL},
	   new int[] {OK, APPLY, CANCEL},
	   new G2ColorsPanel(numColumns),
	   client);

    initialize();

    //colorsPanel = (G2ColorsPanel) getDialogComponent();
    //Button applyButton = getButton(APPLY);
    //applyButton.addActionListener (new ActionListener () {
    //public void actionPerformed (ActionEvent event) {
    //setSelectedColor(getSelectedColorString());
    //}
    //}
    //);	
    //pack ();
  }

  /**
   * @param parentFrame The Frame that is the parent for this instance of
   * G2ColorsDialog
   * @param title A String containing the title for this instance of
   * G2ColorsDialog
   * @param isModal A boolean value indicating whether or not this instance of
   * G2ColorsDialog should be modal
   * @param client The StandardDialogClient for this G2ColorsDialog
   */
  public G2ColorsDialog (Frame parentFrame, String title,
			 boolean isModal,
			 StandardDialogClient client) { 

    super (parentFrame, title, isModal,
	   new String[] {OK_LABEL, APPLY_LABEL, CANCEL_LABEL},
	   new int[] {OK, APPLY, CANCEL},
	   new G2ColorsPanel(),
	   client);

    initialize();

    //colorsPanel = (G2ColorsPanel) getDialogComponent();
    //Button applyButton = getButton(APPLY);
    //applyButton.addActionListener (new ActionListener () {
    //public void actionPerformed (ActionEvent event) {
    //setSelectedColor(getSelectedColorString());
    //}
    //}
    // );	
    //pack ();
  }

  private void initialize() {
    colorsPanel = (G2ColorsPanel) getDialogComponent();
    JButton applyButton = getJButton(APPLY);
    applyButton.addActionListener (new ActionListener () {
      @Override
      public void actionPerformed (ActionEvent event) {
	setSelectedColor(getSelectedColorString());
      }
    });	
    pack ();
  }

  /**
   * Sets the selected color in the G2ColorsCanvas of the G2ColorsDialog
   * @param colorString A String containing the name of a G2 standard color.
   */
  public void setSelectedColor(String colorString) {
    colorsPanel.setSelectedColor(colorString);
  }

  /**
   * Gets the name of the selected G2 standard color
   * @return String A String containing the name of the selected G2 standard
   * color.
   */
  public String getSelectedColorName () {
    return colorsPanel.getSelectedColorString();
  }

  /**
   * Gets the String representation of the selected G2 standard color
   * @return String A String containing the visual name of the selected G2 standard
   * color.
   */
  public String getSelectedColorString () {
    return colorsPanel.getSelectedColorString();
  }

  /**
   * Gets the Symbol name of the selected G2 standard color
   * @return Symbol A Symbol containing the G2 symbol name of the selected
   * color.
   */
  public Symbol getSelectedColorSymbol () {
    return colorsPanel.getSelectedColorSymbol();
  }

  /**
   * Gets the selected G2 standard color.
   * @return Color A Color component for the selected G2 standard color.
   */
  public Color getSelectedColor () {
    return colorsPanel.getSelectedColor();
  }

}
