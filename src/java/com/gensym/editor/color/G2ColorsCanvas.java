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
import com.gensym.util.Symbol;

/**
 * G2ColorsCanvas extends java.awt.Canvas. It provides a "canvas" interface for
 * users to browse the standard colors offered by G2. The number of columns
 * used for displaying the colors is definable in the constructor. Whether or
 * to display "tooltips" with the G2 color name is optional, and settable via
 * the displayColorString() method. <p>
 * Selecting a color generates a G2ColorSelected event. Components that are
 * G2ColorSelectedListeners are notified whenever a color is selected.<p>
 * Methods exist for converting color names into java.awt.Color classes as
 * well as converting color names into an array of RGB values.
 */
public class G2ColorsCanvas extends Canvas 
implements MouseListener, MouseMotionListener {
  private static Resource i18n = Resource.getBundle("com.gensym.editor.color.ColorEditorResources");

  private static final String FOREGROUND_COLOR  = i18n.getString("ForegroundColor");
  private static final String TRANSPARENT_COLOR = i18n.getString("TransparentColor");

  private static final Symbol FOREGROUND_COLOR_  = Symbol.intern(FOREGROUND_COLOR.toUpperCase());
  private static final Symbol TRANSPARENT_COLOR_ = Symbol.intern(TRANSPARENT_COLOR.toUpperCase());

  public static final int INCLUDE_NO_OPTIONAL_COLORS = 0;
  public static final int INCLUDE_FOREGROUND = 1;
  public static final int INCLUDE_TRANSPARENT = 10;

  private int optionalColorsToInclude = 
  //INCLUDE_TRANSPARENT;
  //INCLUDE_FOREGROUND;
  //INCLUDE_FOREGROUND + INCLUDE_TRANSPARENT; 
  INCLUDE_NO_OPTIONAL_COLORS;
  private int numberOfAdditionalColors = INCLUDE_NO_OPTIONAL_COLORS;

  private Vector g2ColorSelectedListeners = null;
  private Vector g2ColorPendingListeners = null;

  protected G2Colors g2Colors = new G2Colors();

  private Graphics canvasGraphics = null;
  private Image canvasImage = null;
  private Dimension canvasDimension = null;

  private int numRows = 7;
  private int numColumns = 9;

  private int blockWidth = 20;
  private int blockHeight = 20;
  private int blockSpacing = 8;

  private double selectedX = 0;
  private double selectedY = 0;

  private double movedX = 0;
  private double movedY = 0;

  private boolean mouseMoved = false;
  private boolean mouseClicked = false;

  private final boolean RAISED = true;
  private final boolean SUNKEN = false;

  private long DisplayColorNameDuration = 1000;  // not used yet
  private boolean DISPLAY_COLOR_NAME = true;

  private final Font colorStringFont = new Font("SansSerif", Font.PLAIN, 12);

  private Color backgroundColor = null;
  private Color outlineColor = null;
 
  private String selectedColorString = null;
  private Symbol selectedColorSymbol = null;
  private Color  selectedColor = null;

  private String pendingColorString = null;
  private Symbol pendingColorSymbol = null;
  private Color  pendingColor = null;
	
  /**
   * G2ColorsCanvas creates a browsable canvas of G2 Standard colors that
   * consists of 7 rows and 9 columns.
   */
  public G2ColorsCanvas () {
    createG2ColorsCanvas(numColumns);
  }

  /**
   * G2ColorsCanvas creates a browsable canvas of G2 Standard colors.
   * @param columns The number of columns to use for displaying the G2
   * standard colors palette.
   */
  public G2ColorsCanvas (int columns) {
    createG2ColorsCanvas(columns);
  }

  /**
   * G2ColorsCanvas creates a browsable canvas of G2 Standard colors.
   * @param columns The number of columns to use for displaying the G2
   * standard colors palette.
   * @param optionalColors An integer value which specifies whether or not
   * to display blocks for the optional "colors" in G2 (foreground and transparent).
   * Possible values are: INCLUDE_NO_OPTIONAL_COLORS, INCLUDE_FOREGROUND, 
   * INCLUDE_TRANSPARENT, INCLUDE_FOREGROUND + INCLUDE_TRANSPARENT.
   */
  public G2ColorsCanvas (int columns, int optionalColors) {
    optionalColorsToInclude = optionalColors;
    createG2ColorsCanvas (columns);
  }

  private void createG2ColorsCanvas (int columns) {
    g2ColorSelectedListeners = new Vector();
    g2ColorPendingListeners = new Vector();

    // do we need to create additional blocks for foreground/transparent?
    if (optionalColorsToInclude > INCLUDE_NO_OPTIONAL_COLORS)
      numberOfAdditionalColors += 1;
    if (optionalColorsToInclude > INCLUDE_TRANSPARENT)
      numberOfAdditionalColors += 1;

    //System.out.println("**** numberOfAdditionalColors: "+numberOfAdditionalColors);

    // define the number of rows based on the number of columns
    numColumns = columns;
    double dRows = ((double)(g2Colors.numColors + numberOfAdditionalColors)/numColumns);
    numRows = (int)dRows;
    if (numRows < dRows)
      numRows  = numRows + 1;
    
    // preferred size based on the number of rows & columns & block size
    canvasDimension = getPreferredSize();

    // set the background and outline colors for canvas
    outlineColor = Color.black;
    if (getParent() != null)
      backgroundColor = getParent().getBackground();
    else
      backgroundColor = Color.lightGray;
    setBackground(backgroundColor);
    addMouseListener(this);
    addMouseMotionListener(this);
  }

  /**
   * Forces an update of the G2ColorsCanvas image.
   * @param graphics The Graphics component associated with the G2ColorsCanvas
   * image.
   */
  @Override
  public void paint(Graphics graphics) {
    update (graphics);
  }

  /**
   * Updates the G2ColorsCanvas image.
   * @param graphics The Graphics component associated with the G2ColorsCanvas
   * image.
   */
  @Override
  public void update (Graphics graphics) {
    int iColor = (int)(movedX + (movedY * numColumns));
    if (iColor >= g2Colors.numColors + numberOfAdditionalColors) {
    	return;
    }

    if (canvasImage == null) {
      canvasImage = createImage(canvasDimension.width, canvasDimension.height);
      canvasGraphics = canvasImage.getGraphics();
    }

    canvasGraphics.setColor(backgroundColor);
    canvasGraphics.fillRect(0, 0, 
			    canvasDimension.width, canvasDimension.height);

    // leave an edge half the width of a block
    int xPos = blockWidth/2;
    int yPos = blockHeight/2;
	
    for (int i=0; i<numRows; i++) {
      for(int j=0; j<numColumns; j++) {
	if ((i*numColumns)+j < (g2Colors.numColors + numberOfAdditionalColors)) {
	  if (((i*numColumns)+j) < g2Colors.numColors) {
	    canvasGraphics.setColor(outlineColor);
	    canvasGraphics.drawRect(xPos, yPos, blockWidth, blockHeight);
	    canvasGraphics.setColor(g2Colors.colorObjects[(i*numColumns)+j]);
	    canvasGraphics.fillRect(xPos+1, yPos+1, blockWidth-1, blockHeight-1);
	  } else {
	    // blocks for optional colors
	    canvasGraphics.setColor(outlineColor);
	    canvasGraphics.drawRect(xPos, yPos, blockWidth, blockHeight);

	    // draw the first char for this color
	    String colorChar = null;
	    if (isTransparent((i*numColumns+j)-g2Colors.numColors))
	      colorChar = TRANSPARENT_COLOR.substring(0, 1).toUpperCase();
	    else
	      colorChar = FOREGROUND_COLOR.substring(0, 1).toUpperCase();

	    canvasGraphics.setFont(colorStringFont);
	    FontMetrics fontMetrics = canvasGraphics.getFontMetrics();
	    int stringWidth = fontMetrics.stringWidth(colorChar);  
	    int stringHeight = fontMetrics.getHeight();
	    canvasGraphics.drawString(colorChar, 
				      xPos + blockWidth/2 - stringWidth/2, 
				      yPos + blockHeight/2 + stringHeight/2);

	  }
	  xPos += blockWidth + blockSpacing;
	}
      }
      xPos = blockWidth/2;
      yPos += blockHeight + blockSpacing;
    }

    if (mouseMoved) {
      updateSelectionRect(movedX, movedY, RAISED);
      if (DISPLAY_COLOR_NAME)
	displayColorName();
      mouseMoved = false;
    }

    // Should we "select" a color?
    if (mouseClicked) {
      updateSelectionRect(selectedX, selectedY, SUNKEN);
    }

    graphics.drawImage(canvasImage, 0, 0, null);
  }

  // displays the name of the "current" color under the mouse in a "tooltip"
  private void displayColorName() {
    int xPad = 2;
    int x = (int)movedX;
    int y = (int)movedY;
    int i = x+(y*numColumns);
    String colorString = null;
    if (i < g2Colors.numColors)
      colorString = g2Colors.colorStrings[i];
    else {
      if (isTransparent(i - g2Colors.numColors))
	colorString = TRANSPARENT_COLOR;
      else
	colorString = FOREGROUND_COLOR;

      /*
      i -= g2Colors.numColors;
      if (i == 1) {
	colorString =  TRANSPARENT_COLOR;
      } else {
	if (optionalColorsToInclude == INCLUDE_TRANSPARENT) {
	  colorString = TRANSPARENT_COLOR;
	} else {
	  colorString = FOREGROUND_COLOR;
	}
      }
      */
    }
    
    int nameX = (int)((movedX * (blockWidth+blockSpacing)) + blockWidth);
    int nameY = (int)((movedY * (blockHeight+blockSpacing)) + (3*blockHeight));

    canvasGraphics.setFont(colorStringFont);
    FontMetrics fontMetrics = canvasGraphics.getFontMetrics();

    int stringWidth = fontMetrics.stringWidth(colorString);  
    int stringHeight = fontMetrics.getHeight();
    int fontDescent = fontMetrics.getDescent();
    
    // make sure colorString displays within canvas dimensions
    if (nameX + stringWidth + (2*xPad) > canvasDimension.width)
      nameX = canvasDimension.width - stringWidth - (2*xPad);

    if (nameY + stringHeight + fontDescent > canvasDimension.height)
      nameY = canvasDimension.height - stringHeight - fontDescent;
  
    canvasGraphics.setColor(Color.white);
    canvasGraphics.fillRect(nameX - xPad,
			    nameY-stringHeight+(fontDescent),
			    stringWidth + (2*xPad),
			    stringHeight);
    canvasGraphics.setColor(Color.black);
    canvasGraphics.drawRect(nameX - xPad,
			    nameY-stringHeight+(fontDescent),
			    stringWidth + (2*xPad),
			    stringHeight);
			  

    canvasGraphics.setColor(Color.black);
    canvasGraphics.drawString(colorString, nameX, nameY);
  }

  // updates the rectangle indicating the currently selected color
  private void updateSelectionRect(double x, double y, boolean raised) {
    int intX = (int)((x * (blockWidth+blockSpacing)) + 6);
    int intY = (int)((y * (blockHeight+blockSpacing)) + 6);
    int width = blockWidth+blockSpacing;
    int height = blockHeight+blockSpacing;

    canvasGraphics.setColor(backgroundColor);
    canvasGraphics.draw3DRect(intX, intY, width, height, raised);
  }

  /**
   * Returns the preferred size for the instance of G2ColorsCanvas. The
   * preferred size is calculated based on the number of columns specified
   * by the user. If none is specified, the default number of columns is 9.
   */
  @Override
  public Dimension getPreferredSize() {
    return new Dimension(
	  ((numColumns*blockWidth) + ((numColumns-1)*blockSpacing)+blockWidth),
	  ((numRows*blockHeight) + (blockSpacing*(numRows-1))+blockHeight));
  }

  /**
   * Sets the selected color for the G2ColorsCanvas to the specified G2 color.
   * @param colorString The String representation of a G2 standard color.
   */
  public void setSelectedColor (String colorString) {

    /*
    for (int i=0; i<g2Colors.numColors + numberOfAdditionalColors; i++) {
      if (i<g2Colors.numColors) {
	if (g2Colors.colorStrings[i].equals(colorString)) {
	  selectedY = i/numColumns;
	  selectedX = i - (selectedY*numColumns);

	  mouseClicked = true;
	  setSelectedColorVariables(i);

	  G2ColorSelectedEvent event = new G2ColorSelectedEvent (this,
								 selectedColorString,
								 selectedColorSymbol,
								 selectedColor);
	  notifyG2ColorSelectedListeners(event);
	}
      } else {
	
      }
    }
    */
    
    for (int i=0; i<g2Colors.numColors; i++) {
      if (g2Colors.colorStrings[i].equals(colorString)) {
	selectedY = ((double)i)/numColumns;
	selectedX = i - (selectedY*numColumns);

	mouseClicked = true;
	setSelectedColorVariables(i);

	G2ColorSelectedEvent event = new G2ColorSelectedEvent (this,
							   selectedColorString,
							   selectedColorSymbol,
							   selectedColor);
	notifyG2ColorSelectedListeners(event);
      }
    }
    
  }

  /**
   * Gets the selected color for the G2ColorsCanvas.
   * @return Color A Color component for the selected G2 standard color.
   */
  public Color getSelectedColor () {
    return selectedColor;
  }

  /**
   * Gets the selected color for the G2ColorsCanvas.
   * @return String A String representation of the selected
   * G2 standard color.
   */
  public String getSelectedColorString () {
    return selectedColorString;
  }

  /**
   * Gets the symbol name for the selected color.
   * @return String A String component containing the symbol name 
   * of the selected G2 standard color.
   */
  public Symbol getSelectedColorSymbol () {
    return selectedColorSymbol;
  }

  /**
   * Sets the background color for the G2ColorsCanvas. By default the canvas
   * sets the background to be the same as its parent. If there is no parent,
   * the default color is light-gray.
   * @param color A Color component indicating the color to use as the
   * background color.
   */
  public void setBackgroundColor (Color color) {
    backgroundColor = color;
  }

  /**
   * Sets the outline color for the color blocks on the G2ColorsCanvas. By
   * default the outline color is black.
   * @param color A Color component indicating the color to use as the outline
   * color for the color blocks of the G2ColorsCanvas.
   */
  public void setOutlineColor (Color color) {
    outlineColor = color;
  }

  /**
   * Specifies whether or not to display the name of the color currently under
   * the mouse in a "tooltip".
   * @param displayName A boolean value that when "true" specifies that the
   * name of the color currently under the mouse should be displayed in a
   * "tooltip". If "false", no color name is displayed.
   */
  public void displayColorName (boolean displayName) {
    DISPLAY_COLOR_NAME = displayName;
  }

  /**
   * Adds the specified listener to the G2ColorsCanvas as a 
   * G2ColorSelectedListener. All listeners receive a G2ColorSelected event
   * whenever a color is selected in the G2ColorsCanvas.
   * @param listener A G2ColorSelectedListener to add to the list of
   * listeners for the G2ColorsCanvas.
   */
  public void addG2ColorSelectedListener(G2ColorSelectedListener listener){
    g2ColorSelectedListeners.addElement(listener);
  }

  /**
   * Removes the specified listener from the G2ColorsCanvas as a 
   * G2ColorSelectedListener. The listener will no longer receive
   * G2ColorSelected events.
   * @param listener A G2ColorSelectedListener to remove from the list of
   * listeners for the G2ColorsCanvas.
   */
  public void removeG2ColorSelectedListener(G2ColorSelectedListener listener){
    g2ColorSelectedListeners.removeElement(listener);
  }

  private void notifyG2ColorSelectedListeners(G2ColorSelectedEvent e){
    if (g2ColorSelectedListeners.isEmpty()) 
    	return;
    Vector v;
	synchronized (this) {
		v = (Vector) g2ColorSelectedListeners.clone();
	}
    Enumeration ccv = v.elements();
    while (ccv.hasMoreElements())
      ((G2ColorSelectedListener)ccv.nextElement()).g2ColorSelected(e);
  }

  public void addG2ColorPendingListener(G2ColorPendingListener listener) {
    g2ColorPendingListeners.addElement(listener);
  }

  public void removeG2ColorPendingListener(G2ColorPendingListener listener) {
    g2ColorPendingListeners.removeElement(listener);
  }

  private void notifyG2ColorPendingListeners(G2ColorPendingEvent e){
    if (g2ColorPendingListeners.isEmpty()) 
    	return;
    Vector v;
	synchronized (this) {
		v = (Vector) g2ColorPendingListeners.clone();
	}
    Enumeration ccv = v.elements();
    while (ccv.hasMoreElements())
      ((G2ColorPendingListener)ccv.nextElement()).g2ColorPending(e);
  }

  private boolean isTransparent(int i) {
    boolean returnValue = false;
    if (i == 1) {
      returnValue = true;
    } else {
      if (optionalColorsToInclude == INCLUDE_TRANSPARENT) {
	returnValue = true;
      }
      else {
	returnValue = false;
      }
    }
    return returnValue;
  }

  /*
   * Diagram for interpreting (g2Colors.numColors - i) for
   * setSelectedColorVariables and setPendingColorVariables
   *
   *    |     0       |     1
   * ------------------------------
   * 11 | foreground  | transparent
   * ------------------------------
   * 10 | transparent | na
   * ------------------------------
   *  1 | foreground  | na
   * ------------------------------
   *  0 | na          | na
   * ------------------------------
   */

  private void setSelectedColorVariables(final int i) {
	int index = i;  
    if (index < g2Colors.numColors) {
      selectedColorString = g2Colors.colorStrings[index];
      selectedColorSymbol = g2Colors.getColorSymbolForColorString(selectedColorString);
      selectedColor = g2Colors.colorObjects[index];
    }  else {
      // i should end up being either 0 or 1
    	index = index - g2Colors.numColors;
      if (isTransparent(index)) {
	selectedColorString = TRANSPARENT_COLOR;
	selectedColorSymbol = TRANSPARENT_COLOR_;
	selectedColor = null; // what should we do?
      } else {
	selectedColorString = FOREGROUND_COLOR;
	selectedColorSymbol = FOREGROUND_COLOR_;
	selectedColor = null; // what should we do?
      }
    }
  }

  private void setPendingColorVariables(final int i) {
	int index = i;  
    if (index < g2Colors.numColors) {
      pendingColorString = g2Colors.colorStrings[index];
      pendingColorSymbol = g2Colors.getColorSymbolForColorString(pendingColorString);
      pendingColor = g2Colors.colorObjects[index];
    } else {
      // i should end up being either 0 or 1
      index = index - g2Colors.numColors;
      if (isTransparent(index)) {
	pendingColorString = TRANSPARENT_COLOR;
	pendingColorSymbol = TRANSPARENT_COLOR_;
	pendingColor = null; // what should we do?
      } else {
	 pendingColorString = FOREGROUND_COLOR;
	 pendingColorSymbol = FOREGROUND_COLOR_;
	 pendingColor = null; // what should we do?
      }
    }
  }

  // BEGIN: MouseListener Events
  @Override
  public void mouseClicked (MouseEvent e) {
    double newX = ((double)e.getX())/(blockWidth+blockSpacing);
    double newY = ((double)e.getY())/(blockHeight+blockSpacing);

    if (newX + (newY * numColumns) >= g2Colors.numColors + numberOfAdditionalColors){
    	return;
    }

    if (newX >= numColumns){
    	return;
    }
    if (newY >= numRows){
    	return;
    }

    selectedX = newX;
    selectedY = newY;

    // set the selectedColor variables
    int x = (int)selectedX;
    int y = (int)selectedY;
    int i = x + (y * numColumns);

    setSelectedColorVariables(i);
    mouseClicked = true;

    G2ColorSelectedEvent event = new G2ColorSelectedEvent (this,
							   selectedColorString,
							   selectedColorSymbol,
							   selectedColor);
    notifyG2ColorSelectedListeners(event);

    // call the update method via repaint 
    repaint();
  }

  @Override
  public void mouseEntered (MouseEvent e) {}
  @Override
  public void mouseExited (MouseEvent e) {}
  @Override
  public void mousePressed (MouseEvent e) {}
  @Override
  public void mouseReleased (MouseEvent e) {}
  // END: MouseListener Events

  // BEGIN: MouseMotionListener Events
  @Override
  public void mouseDragged (MouseEvent e) {}

  @Override
  public void mouseMoved (MouseEvent e) {
    //System.out.println("when? "+e.getWhen());

    movedX = ((double)e.getX())/(blockWidth+blockSpacing);
    movedY = ((double)e.getY())/(blockHeight+blockSpacing);

    if (movedX + (movedY * numColumns) >= g2Colors.numColors + numberOfAdditionalColors){
    	return;
    }

    // if mouse moves beyound the left or bottem edge, 
    // bind it to last row or column
    if (movedX >= numColumns)
      movedX = numColumns - 1.0d;
    if (movedY >= numRows)
      movedY = numRows - 1.0d;

    // set the selectedColor variables
    int x = (int)movedX;
    int y = (int)movedY;
    int i = x + (y * numColumns);

    setPendingColorVariables(i);
    mouseMoved = true;

    G2ColorPendingEvent event = new G2ColorPendingEvent (this,
							 pendingColorString,
							 pendingColorSymbol,
							 pendingColor);
    notifyG2ColorPendingListeners(event);

    // call the update method via repaint
    repaint();
  }
  // END: MouseMotionListener Events
}

