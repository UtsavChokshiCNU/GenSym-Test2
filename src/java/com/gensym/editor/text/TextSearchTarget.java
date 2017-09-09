/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TextSearchTarget.java
 *
 */
package com.gensym.editor.text;


public interface TextSearchTarget extends TextSource {

  public void showRegion(int startPosition, int endPosition);

  public void replaceRegion(String replacementText, int startPosition, int endPosition);

}
