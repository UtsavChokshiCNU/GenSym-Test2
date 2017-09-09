/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TransformationListener.java
 *
 */
package com.gensym.wksp;

import java.util.EventListener;

public interface TransformationListener extends EventListener{

  public void transformationChanged(TransformationEvent event);

}
