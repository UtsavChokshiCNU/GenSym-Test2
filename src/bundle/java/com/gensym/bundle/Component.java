/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Component.java
 *
 * @author David McDonald
 * @version 0.1 initiated 6/30/00
 */

//package com.gensym.bundle;

import java.util.Vector;

public class Component {

  private String name;
  public void setName(String n) { name = n; }
  public String getName() { return name; }
    
  private int index;
  public void setIndex(int i) { index = i; }
  public int getIndex() { return index; }
  

  private boolean optional;
  public void setOptional(boolean b) { optional = b; }
  public boolean isOptional() { return optional; }
  

  /* We're a little bit lame on the button group front. For coding
     convenience, the group can only be one of: 1, 2, 3, 4, 5, 6. In
     addition, the first of these (1) is assumed to be for choosing
     among "client packs", and so presented to the user.  The
     following are used in ReadFamilyFileData to check while reading.  */
  public int min_button_group = 1;
  public int max_button_group = 6;
    
  private int buttonGroup;
  public int getButtonGroup() { return buttonGroup; }
  public void setButtonGroup(int v) {
    buttonGroup = v;
    licensingComponent = true;
  }
  private boolean licensingComponent = false;
  public boolean isLicensingComponent() { return licensingComponent; }


  private Vector validPlatforms;
  public void setValidPlatforms(Vector platforms) { validPlatforms = platforms; }

  public boolean validOnSelectedPlatform(Platform targetPlatform) {
    boolean isValid = false;
    if ( validPlatforms == null)
      return true;
    for (int i=0; i < validPlatforms.size(); i++) {
      Platform p = (Platform)validPlatforms.elementAt(i);
      if (p.equals(targetPlatform)) {
	isValid = true;
	break;
      }
    }
    return isValid;
  }
    

  public Component(String name) {
    this.name = name;
  }

    
}
