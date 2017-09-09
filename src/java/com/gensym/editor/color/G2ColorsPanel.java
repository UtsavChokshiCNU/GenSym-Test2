/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2ColorsPanel.java
 *
 */
package com.gensym.editor.color;

import java.awt.Color;
import java.awt.GridBagConstraints;
import java.awt.Image;
import java.awt.Insets;
import java.awt.Label;
import java.awt.Panel;
import com.gensym.message.Resource;
import com.gensym.uiutil.StandardGridBagPanel;
import com.gensym.util.Symbol;

/**
 * G2ColorsPanel pulls together an instance of G2ColorsCanvas and
 * G2ColorsPreviewCanvas. As colors are selected in the G2ColorsCanvas, the
 * G2ColorsPreviewCanvas is updated to show the new selection.
 */
public class G2ColorsPanel extends StandardGridBagPanel {
  private static Resource i18n = 
		Resource.getBundle("com.gensym.editor.color.ColorEditorResources");
  
  private Label  canvasLabel = null;
  private G2ColorsCanvas colorCanvas = null;
  private G2ColorsPreviewCanvas previewCanvas = null;
 
  private int numColumns = 7;

  private int optionalColorsToInclude = G2ColorsCanvas.INCLUDE_NO_OPTIONAL_COLORS;

  public G2ColorsPanel (int columns, int optionalColors) {
    numColumns = columns;
    optionalColorsToInclude = optionalColors;
    initialize();
  }

  /**
   * @param columns The number of columns used to display the palette of G2
   * standard colors.
   */
  public G2ColorsPanel (int columns) {
    numColumns = columns;
    initialize();
    //createG2ColorsPanel (numColumns, optionalColorsToInclude);
    //setSelectedColor("white");
  }

  public G2ColorsPanel () {
    initialize();
  }

  private void initialize() {
    createG2ColorsPanel (numColumns);
    setSelectedColor("white");
  }

  private void createG2ColorsPanel (int columns) {
    GridBagConstraints gridC = new GridBagConstraints ();
    setLayout (gridBagLayout);
    setBackground(Color.lightGray);

    gridC.gridwidth = GridBagConstraints.REMAINDER;
    gridC.anchor = GridBagConstraints.WEST;
    gridC.insets = new Insets(5, 5, 0, 5);
    addComponent(canvasLabel = new Label(i18n.getString("StandardG2Colors")),
					 gridC);
    
    gridC.gridwidth = GridBagConstraints.RELATIVE;
    gridC.insets = new Insets(0, 5, 0, 5);
    addComponent(colorCanvas = new G2ColorsCanvas(columns, optionalColorsToInclude), gridC);

    gridC.gridwidth = GridBagConstraints.REMAINDER;
    gridC.anchor = GridBagConstraints.SOUTHWEST;
    gridC.insets = new Insets(0, 5, 5, 5);
    addComponent(previewCanvas = new G2ColorsPreviewCanvas(), gridC);

    colorCanvas.addG2ColorSelectedListener(previewCanvas);
  }

  /**
   * Gets the G2ColorsPreviewCanvas for the instance of G2ColorsPanel.
   * @return G2ColorsPreviewCanvas The G2ColorsPreviewCanvas for the
   * G2ColorsPanel.
   */
  public G2ColorsPreviewCanvas getG2ColorsPreviewCanvas () {
    return previewCanvas;
  }

  /**
   * Gets the G2ColorsCanvas for the instance of G2ColorsPanel.
   * @return G2ColorsCanvas The G2ColorsCanvas for the G2ColorsPanel.
   */
  public G2ColorsCanvas getG2ColorsCanvas () {
    return colorCanvas;
  }

  /**
   * Sets the selected color in the G2ColorsCanvas for the instance of
   * G2ColorsPanel based on a String representation.
   * @param colorString A String containing the name of a G2 standard color.
   */
  public void setSelectedColor(String colorString) {
    //System.out.println("*** G2ColorsPanel.setSelectedColor: "+colorString);
    // make the color, colorString, the selected color on the canvas
    if (colorString != null) {
      colorCanvas.setSelectedColor(colorString);
      Color color = colorCanvas.g2Colors.getColorObjectForColorString(colorString);
      
      // update the preview area with selected color
      previewCanvas.setSelectedColor(color);
      
      // check for TRANSPARENT or FOREGROUND, check for null
      //System.out.println("*** color: "+color);
      if (color == null) {
	previewCanvas.setCurrentColor(color, colorString);
      } else
	previewCanvas.setCurrentColor(color);
    }
    previewCanvas.repaint();
  }

  /**
   * Gets the Symbol representation of the selected G2 standard color
   * in the G2ColorsCanvas for the instance of G2ColorsPanel.
   * @return Symbol A Symbol containing the G2 symbol name of the selected color.
   */
  public Symbol getSelectedColorSymbol() {
    return colorCanvas.getSelectedColorSymbol();
  }

  /**
   * Gets the String representation of the selected G2 standard color in the 
   * G2ColorsCanvas for the instance of G2ColorsPanel.
   * @return String A String containing the name of the selected G2 standard
   * color.
   */
  public String getSelectedColorString() {
    return colorCanvas.getSelectedColorString();
  }

  /**
   * Get the Color component for the selected G2 standard color in the
   * G2ColorsCanvas for the instance of G2ColorsPanel.
   * @return Color A Color component for the selected G2 standard color.
   */
  public Color getSelectedColor() {
    return colorCanvas.getSelectedColor();
  }
}
