/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 RepresentationConstraints.java
 *
 */

package com.gensym.ui;

import javax.swing.SwingConstants;
import com.gensym.message.Resource;

/**
 *  This class encapsulates the representation style for a 
 *  javax.swing.AbstractButton.
 *
 */

public class RepresentationConstraints implements SwingConstants{
  public static final int TEXT_ONLY = 0;
  public static final int ICON_ONLY = 1;
  public static final int TEXT_AND_ICON = 2;

  private static Resource i18n = Resource.getBundle("com/gensym/ui/Errors");

  private int representationType = TEXT_ONLY;
  private int horizontalAlignment = CENTER;
  private int verticalAlignment = CENTER;
  private int horizontalTextPosition = RIGHT;
  private int verticalTextPosition = CENTER;

  public RepresentationConstraints(int representationType){
    checkRepresentationType(representationType);
    this.representationType = representationType;
  }

  public RepresentationConstraints(int horizontalAlignment, 
				   int verticalAlignment, 
				   int horizontalTextPosition, 
				   int verticalTextPosition){
    checkAlignmentAndPosition(horizontalAlignment,  verticalAlignment, 
			      horizontalTextPosition, verticalTextPosition);
    this.horizontalAlignment = horizontalAlignment;
    this.verticalAlignment = verticalAlignment;
    this.horizontalTextPosition = horizontalTextPosition;
    this.verticalTextPosition = verticalTextPosition;
  }

  public RepresentationConstraints(int representationType,
				   int horizontalAlignment, 
				   int verticalAlignment, 
				   int horizontalTextPosition, 
				   int verticalTextPosition){
    checkRepresentationType(representationType);
    checkAlignmentAndPosition(horizontalAlignment,  verticalAlignment, 
			      horizontalTextPosition, verticalTextPosition);
    this.representationType = representationType;
    this.horizontalAlignment = horizontalAlignment;
    this.verticalAlignment = verticalAlignment;
    this.horizontalTextPosition = horizontalTextPosition;
    this.verticalTextPosition = verticalTextPosition;
  }

  private void checkRepresentationType(int representationType){
    if (!((representationType == TEXT_ONLY) || 
	(representationType == ICON_ONLY) ||
	(representationType == TEXT_AND_ICON)))			   
      throw new IllegalArgumentException(i18n.getString("IllegalRepresentationType"));
  }

  private void checkAlignmentAndPosition(int horizontalAlignment, 
				    int verticalAlignment, 
				    int horizontalTextPosition, 
				    int verticalTextPosition){
    String key = null;
    if (!((horizontalAlignment == CENTER) || (horizontalAlignment == LEFT) ||
	  (horizontalAlignment == RIGHT))) key = "IllegalHorizontalAlignment";
    if (key != null){
    	throw new IllegalArgumentException(key);
    }
        if (!((verticalAlignment == CENTER) || (verticalAlignment == TOP) ||
	  (verticalAlignment == BOTTOM))) key = "IllegalVerticalAlignment";
    if (key != null){
    	throw new IllegalArgumentException(key);
    }
    if (!((horizontalTextPosition == CENTER) || (horizontalTextPosition == LEFT) ||
	  (horizontalTextPosition == RIGHT))) key = "IllegalHorizontalTextPosition";
    if (key != null){
    	throw new IllegalArgumentException(key);
    }
    if (!((verticalTextPosition == CENTER) || (verticalTextPosition == TOP) ||
	  (verticalTextPosition == BOTTOM))) key = "IllegalVerticalTextPosition";
    if (key != null){
    	throw new IllegalArgumentException(i18n.getString(key));
    }
  }

  /** 
   *  Returns the horizontal alignment of the icon and text, possible
   *  values are CENTER, LEFT, or RIGHT.  The default value is CENTER.
   */
  public int getHorizontalAlignment(){
    return horizontalAlignment;
  }

  /**
   *  Returns the vertical alignment of the icon and text, possible values
   *  are CENTER, TOP, or BOTTOM.  The default value is CENTER.
   */
  public int getVerticalAlignment(){
    return verticalAlignment;
  }

  /**
   *  Returns the horizontal position of the text relative to the icon, possible
   *  values are CENTER, LEFT, RIGHT.  The default value is RIGHT.
   */
  public int getHorizontalTextPosition(){
    return horizontalTextPosition;
  }

  /** 
   *  Returns the vertical position of the text relative to the icon, possible
   *  values are CENTER, TOP, or BOTTOM.  The default value is CENTER.
   */
  public int getVerticalTextPosition(){
    return verticalTextPosition;
  }

  /** 
   *  Returns the representation type which is either TEXT_ONLY, ICON_ONLY, or
   *  TEXT_AND_ICON.  The default value is TEXT_ONLY.
   */
  public int getRepresentationType(){
    return representationType;
  }
}

