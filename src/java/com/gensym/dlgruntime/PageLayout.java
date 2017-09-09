
/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	Page Layout - PageLayout.java
 *
 */

package com.gensym.dlgruntime;

/** This class is used to define the contents of a single page
 *  which may be part of a tab page group
 */
public class PageLayout implements java.io.Serializable
{ 
  static final long serialVersionUID = -6974225735356632872L;
    /** The width of this page
    */
    private int width;

    /** The height of this page
    */
    private int height;

    /** An array of objects which describe the contents of this page
    */
    private Object[]  contents;

    /** Constuctor for this class
    */
    public PageLayout (int width, int height, Object[] contents)
    {
       this.width = width;
       this.height = height;
       this.contents = contents;
    }

    /** Gets the width of this PageLayout
    */
    public int getWidth()
    {
       return width;
    }

    /** Sets the width of this PageLayout
    */
    public void setWidth(int width)
    {
       this.width = width;
    }

    /** Gets the height of this PageLayout
    */
    public int getHeight()
    {
       return height;
    }

    /** Sets the height of this PageLayout
    */
    public void setHeight(int height)
    {
       this.height = height;
    }

    /** Gets the contents of this PageLayout
    */
    public Object[] getContents()
    {
       return contents;
    }

    /** Sets the contents of this PageLayout
    */
    public void setContents(Object[] contents)
    {
       this.contents = contents;
    }



}
