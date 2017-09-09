/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2ColorField.java
 *
 */

package com.gensym.gcg;

import java.awt.Color;

import com.gensym.controls.FieldType;
import com.gensym.jcontrols.G2TextField;

import com.gensym.editor.color.G2Colors;
import com.gensym.editor.color.G2ColorsCanvas;
import com.gensym.editor.color.G2ColorsDialog;
import com.gensym.util.Symbol;

import java.awt.Frame;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;

/** 
 * The G2ColorField is a component for displaying and editing an attribute which is a color.
 * The background color of this text field is painted the selected color.  The color is edited
 * by a sub dialog.
 */
public class G2ColorField extends G2TextField implements EditedBySubDialog{

  private Color  color;
  private Symbol colorSymbol;
  private String colorString;

  private static G2Colors g2Colors = new G2Colors();
  private static final int numColumns = 9;
  private static int optionalColorsToInclude = G2ColorsCanvas.INCLUDE_NO_OPTIONAL_COLORS;
  private static final int BLACK_FOREGROUND_THRESHOLD = 350;

  private static final Symbol FOREGROUND_  = Symbol.intern("FOREGROUND");
  private static final Symbol TRANSPARENT_ = Symbol.intern("TRANSPARENT");
 
  private DialogClient dialogClient;

  /**
   * Creates a G2ColorField with choices of the standard colors.
   */
  public G2ColorField() {
    super();
    initializeColorField();
  }

  /**
   * Creates a G2ColorFiels with the standard colors and the specified optional colors, e.g., transparent
   * and foreground.
   */
  public G2ColorField(int optionalColors) {
    super();
    optionalColorsToInclude = optionalColors;
    initializeColorField();
  }

  G2ColorField(int optionalColors, String title){
    this(optionalColors);
  }

  private void initializeColorField() {
    setFieldType(new FieldType("Symbol"));
    setEditable(false);
    dialogClient = new DialogClient();
  }

  @Override
  public void setText(String text){
    setColor(Symbol.intern(text.trim().toUpperCase()));
  }

  public void setColor(Symbol colorName) {
    colorSymbol = colorName;
    String colorAsString = colorSymbol.toString();
    if ((colorSymbol.equals(FOREGROUND_)) || (colorSymbol.equals(TRANSPARENT_))) {
      colorString = colorAsString.toLowerCase();
      color = Color.gray;
    } else {
      colorString = g2Colors.getColorStringForColorSymbol(colorSymbol);
      if (colorString == null)
	throw new IllegalArgumentException(colorName+" is not a legal G2 color");
      color = g2Colors.getColorObjectForColorString(colorString);
    }

    setBackground(color);
    int total = color.getRed() + color.getGreen() + color.getBlue();
    if (total >= BLACK_FOREGROUND_THRESHOLD)
      setForeground(Color.black);
    else
      setForeground(Color.white);

    super.setText(colorAsString);
  }

  public Symbol getColorName() {
    return colorSymbol;
  }

  public Color getColor() {
    return color;
  }

  @Override
  public void launchSubDialog() {
    G2ColorsDialog dlg = new G2ColorsDialog(null, getAttribute().toString(), true, 
					    numColumns, optionalColorsToInclude, dialogClient);
    dlg.setSelectedColor(colorString);
    dlg.setVisible(true);
  }

  class DialogClient implements StandardDialogClient , java.io.Serializable {
    @Override
    public void dialogDismissed (StandardDialog dlg, int code) {
      if (dlg.wasCancelled()) {
    	  return;
      }

      if (dlg instanceof G2ColorsDialog) {
	G2ColorsDialog cd = (G2ColorsDialog)dlg;
	setColor(cd.getSelectedColorSymbol());
	fireObjectChange();
      }
    }
  }

  private void fireObjectChange()
  {
    fireObjectChangeOnContents();
  }
}
