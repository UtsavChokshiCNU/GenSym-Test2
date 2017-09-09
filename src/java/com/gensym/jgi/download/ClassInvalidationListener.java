
/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ClassInvalidationListener.java
 *
 *   Description: 
 *     

 *
 */
package com.gensym.jgi.download;

/** 
 * Interface for receiving events regarding changes to Items.
 * @author vkp
 * @version 1.0 6/25/98
 */

public interface ClassInvalidationListener extends java.util.EventListener {

  public void classesInvalidated (ClassInvalidationEvent cie);

}

