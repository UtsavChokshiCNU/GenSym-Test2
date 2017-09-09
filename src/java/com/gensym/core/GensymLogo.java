/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 GensymLogo.java
 *
 */
package com.gensym.core;

import java.awt.Toolkit;
import java.awt.Image;

/**
 * This class lets T2-internals developers reference a single, shared
 * instance of the upper-left corner gif file of the Gensym logo.
 * @undocumented
 */

public class GensymLogo {

  public static Image get() {  
    return LazyGensymLogo.INSTANCE; 
  }
  
  private static class LazyGensymLogo {
    private static final Image INSTANCE = Toolkit.getDefaultToolkit().
        getImage(GensymLogo.class.getResource("gensym_logo.gif"));
  }

}
