/*
 * @(#)LocalClassNameMapper.java	1.0 99/02/16
 * 
 * Copyright (c) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 
 */

package com.gensym.jgi.download.local;

import com.gensym.util.Symbol;

public interface LocalClassNameMapper extends com.gensym.jgi.download.ClassNameMapper{
  
  String substituteJavaClassNameFromG2ClassName (Symbol g2ClassName_);

}
