/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ColorPreviewCanvas.java
 *
 */
package com.gensym.uiutil;

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
 * ColorPreviewCanvas consists of a Canvas that displays two rectangular
 * regions for showing the two different colors that could be used to depict
 * before/after, current/selected scenarios. Each region is labeled to 
 * indicate what is it showing.
 */
public class ColorPreviewCanvas extends Canvas {

  private static Resource shortBundle = 
		Resource.getBundle("com.gensym.uiutil.ColorEditorResources");

  private Graphics canvasGraphics = null;
  private Image canvasImage = null;
  private Dimension canvasDimension = null;

  private final Font canvasFont = new Font("SansSerif", Font.PLAIN, 12);

  private Color backgroundColor = null;
  private Color outlineColor = null;
  private Color currentColor = null;
  private Color selectedColor = null;

  private int canvasWidth = 60;
  private int canvasHeight = 100;
  private int labelHeight = 0;
  private int fontDescent = 0;
	
  /**
   * A constructor for ColorPreviewCanvas
   */
  public ColorPreviewCanvas () {
    createColorPreviewCanvas();
  }

  /**
   * A constructor for ColorPreviewCanvas
   * @param width An integer specifying the width of the ColorPreviewCanvas
   * @param height An integer specifying the height of the
   * ColorPreviewCanvas
   */
  public ColorPreviewCanvas (int width, int height) {
    canvasWidth = width;
    canvasHeight = height;
    createColorPreviewCanvas();
  }

  private void createColorPreviewCanvas () {
    
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
   * Forces an update of the ColorPreviewCanvas
   * @param graphics The Graphics component for the image associated with the
   * ColorPreviewCanvas
   */
  @Override
  public void paint(Graphics graphics) {
    update (graphics);
  }

  /**
   * Updates the image associated with the ColorPreviewCanvas
   * @pararm graphics The Graphics component for the image associated with the
   * ColorPreviewCanvas.
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
    }

    // draw filled upper rect with selected color
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

    graphics.drawImage(canvasImage, 0, 0, null);
  }

  /**
   * Gets the preferred dimensions for the ColorPreviewCanvas. The preferred
   * size is given by its width and height, which by default are 60 and 100
   * respectively.
   * @return Dimension A Dimension component containing the preferred width and
   * height for the ColorPreviewCanvas.
   */
  @Override
  public Dimension getPreferredSize() {
    return new Dimension(canvasWidth, canvasHeight);
  }

  /**
   * Sets the background color for the image associated with the
   * ColorPreviewCanvas. By default the background color of the parent
   * component for the ColorPreviewCanvas is used. If there is no parent
   * component, the default color is light-gray.
   * @param color A Color component specifying the background color to use for
   * the image associated with the ColorPreviewCanvas.
   */
  public void setBackgroundColor (Color color) {
    backgroundColor = color;
  }

  /**
   * Sets the outline color for the image associated with the 
   * ColorPreviewCanvas. By default, the outline color is black.
   * @param color A Color component specifying the outline color to use for the
   * image associated with the ColorPreviewCanvas.
   */
  public void setOutlineColor (Color color) {
    outlineColor = color;
  }

  /**
   * Sets the color for the "current" color region of the image associated with
   * the ColorPreviewCanvas. The "current" region is the lower region.
   * @param color A Color component specifying the color to use for the
   * "current" color region.
   */
  public void setCurrentColor (Color color) {
    currentColor = color;
  }

  /**
   * Sets the color for the "selected" color region of the image associated
   * with the ColorPreviewCanvas. The "selected" region is the upper region.
   * @param color A Color component specifying the color to use for the
   * "selected" color region.
   */
  public void setSelectedColor (Color color) {
    selectedColor = color;
  }
}

