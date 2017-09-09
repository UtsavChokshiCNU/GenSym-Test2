/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MDITilingManager.java
 *
 */

package com.gensym.mdi;

import java.awt.*;
import java.util.Vector;
import java.lang.Math;

/**
 * This class is to be used only in the MDI package
 * It is a layout manager for the MDIManager Window
 */

class MDITilingManager implements LayoutManager, MDITilingConstants {
  private final int DEFAULT_INITIAL_CAPACITY = 20;
  private final int LOCATION_OFFSET = 21;
  private double PERCENT_OF_WIDTH = 0.8;
  private double PERCENT_OF_HEIGHT = 0.6;
  private int componentCount;
  private int currentTilingCode;
  private Vector layoutList = new Vector(DEFAULT_INITIAL_CAPACITY);
  private int[] columnOccupancy = new int[DEFAULT_INITIAL_CAPACITY];
  private int numRows, numCols;
  private MDITilingColumn column = new MDITilingColumn ();

  MDITilingManager () {}

  // Standard Interface Methods
  @Override
  public void addLayoutComponent(String name, Component comp) {}

  @Override
  public void removeLayoutComponent(Component comp) {}

  @Override
  public Dimension preferredLayoutSize(Container parent) {
    return parent.getSize ();
  }

  @Override
  public Dimension minimumLayoutSize(Container parent) {
    return parent.getSize ();
  }

  @Override
  public void layoutContainer(Container parent) {
    if (componentCount == 0) return;
    if (componentCount > columnOccupancy.length)
      columnOccupancy = new int[componentCount];
    if (currentTilingCode == TILE_HORIZONTALLY ||
	currentTilingCode == TILE_VERTICALLY)
      layoutContainerInGrid (parent);
    else
      stackChildren (parent);
  }

  // Specific methods
  void setTilingParameters (int tilingCode) {
    currentTilingCode = tilingCode;
  }

  void addLayoutComponent(Component comp) {
    layoutList.addElement (comp);
    componentCount++;
  }

  void clearLayoutComponents () {
    layoutList.removeAllElements();
    componentCount = 0;
  }

  private void stackChildren (Container parent) {
    Dimension size = parent.getSize ();
    Insets insets = parent.getInsets ();
    int width = size.width - insets.left - insets.right;
    int height = size.height - insets.bottom - insets.top;
    
    int childWidth = (int) (PERCENT_OF_WIDTH*width);
    int childHeight = (int) (PERCENT_OF_HEIGHT*height);
    int offset = insets.left;

    for (int i=0; i<componentCount; i++) {
      Component child = (Component) layoutList.elementAt (i);
      child.setBounds (offset, offset, childWidth, childHeight);
      offset += LOCATION_OFFSET;
      if (offset + childWidth > width ||
	  offset + childHeight > height)
	offset = 0;
    }
  }

  private void layoutContainerInGrid (Container parent) {
    Dimension size = parent.getSize ();
    Insets insets = parent.getInsets ();
    int width = size.width - insets.left - insets.right;
    int height = size.height - insets.bottom - insets.top;

    determineGridShape ();
    int columnWidth = width/numCols;
    int rightEdgeOfColumn = width + insets.left;
    int columnStartIndex = 0;
    for (int i=numCols - 1; i>=0; i--) {
      int numComponentsInColumn = columnOccupancy[i];
      column.resetColumnParameters (rightEdgeOfColumn - columnWidth,
				    insets.top,
				    rightEdgeOfColumn,
				    height + insets.top,
				    numComponentsInColumn);
      for (int j=0; j<numComponentsInColumn; j++)
	column.layoutComponentInColumn ((Component)layoutList.elementAt (columnStartIndex + j));
      columnStartIndex += numComponentsInColumn;
      rightEdgeOfColumn -= columnWidth;
    }    
  }

  private void determineGridShape () {
    int numFewer = (int) Math.floor (Math.sqrt (componentCount));
    int numOther = (int) Math.floor ((double) (componentCount/numFewer));
    if (currentTilingCode == TILE_HORIZONTALLY) {
      numCols = numFewer; numRows = numOther;
    } else {
      numRows = numFewer; numCols = numOther;
    }
    int overflow = componentCount - numRows*numCols;
    for (int i=numCols - 1; i>=0; i--) {
      if (overflow > 0) {
	columnOccupancy[i] = numRows + 1;
	overflow--;
      } else {
	columnOccupancy[i] = numRows;
      }
    }
  }

}


class MDITilingColumn {
  private int childStdWidth, childStdHeight;
  private int remainingTop, numRemaining;
  private int left, top;
  
  void resetColumnParameters (int left, int top, int right, int bottom, int numComponentsInColumn) {
    this.top = top;
    this.left = left;
    childStdWidth = right - left;
    childStdHeight = (bottom - top) / numComponentsInColumn;
    remainingTop = bottom;
    numRemaining = numComponentsInColumn;
  }

  void layoutComponentInColumn (Component comp) {
    int compHeight = (remainingTop - top != numRemaining*childStdHeight ?
		      childStdHeight + 1 : childStdHeight);
    comp.setBounds (left, remainingTop -= compHeight, childStdWidth, compHeight);
    numRemaining--;
  }
}



















