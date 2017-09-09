/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2ColorsCanvas.java
 *
 */
package com.gensym.editor.color;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.util.Enumeration;
import java.util.Vector;
import com.gensym.message.Resource;

/**
 * G2ColorsPreviewCanvas consists of a Canvas that displays two rectangular
 * regions for showing the two different colors that could be used to depict
 * before/after, current/selected scenarios. Each region is labeled to 
 * indicate what is it showing.
 */
public class G2ColorsPreviewCanvas extends Canvas implements G2ColorSelectedListener {

  private static Resource shortBundle = 
		Resource.getBundle("com.gensym.editor.color.ColorEditorResources");

  private Graphics canvasGraphics = null;
  private Image canvasImage = null;
  private Dimension canvasDimension = null;

  private final Font canvasFont = new Font("SansSerif", Font.PLAIN, 12);
  private final Font optionalFont = new Font("SansSerif", Font.PLAIN, 10);

  private Color backgroundColor = null;
  private Color outlineColor = null;
  private Color currentColor = null;
  private String currentColorString = null;
  private boolean currentIsOptional = false;
  private Color selectedColor = null;
  private String selectedColorString = null;
  private boolean selectedIsOptional = false;

  private int canvasWidth = 60;
  private int canvasHeight = 100;
  private int labelHeight = 0;
  private int fontDescent = 0;
	
  /**
   * A constructor for G2ColorsPreviewCanvas
   */
  public G2ColorsPreviewCanvas () {
    createG2ColorsPreviewCanvas();
  }

  /**
   * A constructor for G2ColorsPreviewCanvas
   * @param width An integer specifying the width of the G2ColorsPrevieCanvas
   * @param height An integer specifying the height of the
   * G2ColorsPreviewCanvas
   */
  public G2ColorsPreviewCanvas (int width, int height) {
    canvasWidth = width;
    canvasHeight = height;
    createG2ColorsPreviewCanvas();
  }

  private void createG2ColorsPreviewCanvas () {
    
    canvasDimension = getPreferredSize();

    // set the background and outline colors for canvas
    outlineColor = Color.black;
    if (getParent() != null)
      backgroundColor = getParent().getBackground();
    else
      backgroundColor = Color.lightGray;

    currentColor = backgroundColor;
    selectedColor = backgroundColor;

    setBackground(backgroundColor); 
  }

  /**
   * Forces an update of the G2ColorsPreviewCanvas
   * @param graphics The Graphics component for the image associated with the
   * G2ColorsPreviewCanvas
   */
  @Override
  public void paint(Graphics graphics) {
    update (graphics);
  }

  /**
   * Updates the image associated with the G2ColorsPreviewCanvas
   * @pararm graphics The Graphics component for the image associated with the
   * G2ColorsPreviewCanvas.
   */
  @Override
  public void update (Graphics graphics) {
    if (canvasImage == null) {
      canvasImage = createImage(canvasDimension.width, canvasDimension.height);
      canvasGraphics = canvasImage.getGraphics();
      canvasGraphics.setFont(canvasFont);
      FontMetrics fontMetrics = canvasGraphics.getFontMetrics();

      fontDescent = fontMetrics.getDescent();
      labelHeight = fontMetrics.getHeight();
    } else {
      // set back in case of optionalFont
      canvasGraphics.setFont(canvasFont);
    }

    // draw filled upper rect with selected color

    // BEGIN: check for the case when color is null, when  color is TRANSPARENT or FOREGROUND
    if (selectedColor == null) {
      selectedColor = Color.gray;
      selectedIsOptional = true;
    } else
      selectedIsOptional = false;

    if (currentColor == null) {
      currentColor = Color.gray;
      currentIsOptional = true;
    } 
    // END: check for the case when color is null

    //System.out.println("in update, selectedColor: "+selectedColor+"  currentColor: "+currentColor);
   
    canvasGraphics.setColor(selectedColor);
    canvasGraphics.fillRect(0, labelHeight + fontDescent, 
			    canvasDimension.width,
			    canvasDimension.height/2);

    // draw filled lower rect with current color
    canvasGraphics.setColor(currentColor);
    canvasGraphics.fillRect(0, canvasDimension.height/2, 
			    canvasDimension.width,
			    canvasDimension.height/2 -
			    (labelHeight) - (fontDescent)); 

    canvasGraphics.setColor(Color.black);
    canvasGraphics.drawLine(0, canvasDimension.height/2,
			    canvasDimension.width, canvasDimension.height/2);
    canvasGraphics.drawRect(0, labelHeight + fontDescent,
			    canvasDimension.width-1,
			    canvasDimension.height-
			    (2*labelHeight)-(2*fontDescent));

    canvasGraphics.drawString (shortBundle.getString("New"),
			       0, labelHeight);
    canvasGraphics.drawString (shortBundle.getString("Current"),
			       0,
			       canvasDimension.height-fontDescent);

    // BEGIN: display first char of selected color string for TRANSPARENT & FOREGROUND
    if (selectedIsOptional) {
      canvasGraphics.setFont(optionalFont);
      FontMetrics fontMetrics = canvasGraphics.getFontMetrics();
      int stringWidth = fontMetrics.stringWidth(selectedColorString);  
      int stringHeight = fontMetrics.getHeight();
      canvasGraphics.drawString(selectedColorString, 
				5, canvasDimension.height/2 - stringHeight);
    }

    if (currentIsOptional) {
      //System.out.println("currentColorString: "+currentColorString);
      canvasGraphics.setFont(optionalFont);
      FontMetrics fontMetrics = canvasGraphics.getFontMetrics();
      int stringWidth = fontMetrics.stringWidth(currentColorString);  
      int stringHeight = fontMetrics.getHeight();
      canvasGraphics.drawString(currentColorString, 
				5, canvasDimension.height - stringHeight*2);
    }
    // END:

    graphics.drawImage(canvasImage, 0, 0, null);
  }

  /**
   * Gets the preferred dimensions for the G2ColorsPreviewCanvas. The preferred
   * size is given by its width and height, which by default are 60 and 100
   * respectively.
   * @return Dimension A Dimension component containing the preferred width and
   * height for the G2ColorsPreviewCanvas.
   */
  @Override
  public Dimension getPreferredSize() {
    return new Dimension(canvasWidth, canvasHeight);
  }

  /**
   * Sets the background color for the image associated with the
   * G2ColorsPreviewCanvas. By default the background color of the parent
   * component for the G2ColorsPreviewCanvas is used. If there is no parent
   * component, the default color is light-gray.
   * @param color A Color component specifying the background color to use for
   * the image associated with the G2ColorsPreviewCanvas.
   */
  public void setBackgroundColor (Color color) {
    backgroundColor = color;
  }

  /**
   * Sets the outline color for the image associated with the 
   * G2ColorsPreviewCanvas. By default, the outline color is black.
   * @param color A Color component specifying the outline color to use for the
   * image associated with the G2ColorsPreviewCanvas.
   */
  public void setOutlineColor (Color color) {
    outlineColor = color;
  }

  /**
   * Sets the color for the "current" color region of the image associated with
   * the G2ColorsPreviewCanvas. The "current" region is the lower region.
   * @param color A Color component specifying the color to use for the
   * "current" color region.
   */
  public void setCurrentColor (Color color) {
    currentColor = color;
    currentIsOptional = false;
  }

  public void setCurrentColor (Color color, String colorString) {
    setCurrentColor(color);
    currentColorString = colorString;
    currentIsOptional = true;
  }

  /**
   * Sets the color for the "selected" color region of the image associated
   * with the G2ColorsPreviewCanvas. The "selected" region is the upper region.
   * @param color A Color component specifying the color to use for the
   * "selected" color region.
   */
  public void setSelectedColor (Color color) {
    //System.out.println("G2ColorsPreviewCanvas.setSelectedColor with 1 arg");
    selectedColor = color;
  }

  private void setSelectedColor (Color color, String colorString) {
    //System.out.println("G2ColorsPreviewCanvas.setSelectedColor with 2 args");
    setSelectedColor(color);
    selectedColorString = colorString;
  }

  /**
   * g2ColorSelected is the mandatory method the G2ColorsPreviewCanvas must 
   * have as a G2ColorsSelectedListener. Whenever a color is selected in the
   * G2ColorCanvas, the G2ColorsPreviewCanvas is notified via the 
   * g2ColorSelected method. This sets the selected color in the 
   * G2ColorsPreviewCanvas and forces it to repaint itself.
   */
  @Override
  public void g2ColorSelected(G2ColorSelectedEvent event) {
    //System.out.println("G2ColorsPreviewCanvas.g2ColorSelected: "+event.getColorString());
    setSelectedColor(event.getColor(), event.getColorString());
    repaint();
  }
}

