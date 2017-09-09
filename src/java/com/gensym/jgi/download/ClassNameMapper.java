/*
 * @(#)ClassNameMapper.java	1.0 97/12/15
 * 
 * Copyright (c) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 
 */

package com.gensym.jgi.download;

import com.gensym.util.Symbol;

public interface ClassNameMapper {
  
  String javaClassNameFromG2ClassName (Symbol g2ClassName_);

  String getVersionForClass (Symbol g2ClassName_);

}
