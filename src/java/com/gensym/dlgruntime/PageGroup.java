
/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	Page Group - PageGroup.java
 *
 */


package com.gensym.dlgruntime;

import java.net.URL;

/** This is a top level class used to specify the contents of a dialog.
 */
public class PageGroup implements java.io.Serializable
{ 

    /** The width of this page group
    */
    private int width;

    /** The height of this page group
    */
    private int height;

    /** The location of this PageGroup
    */
    private URL location;

    /** An array of Strings which represent the names of the tab pages for 
    * this dialog.
    */
    private String[] tabNames;

    /** An array of resources which describe the contents of each page
    */
    private String[] pages;
    
    /** Creates a PageGroup with pages defined by the given args
    */
    public PageGroup(URL location, String[] tabNames, String[] pages, int width, int height)
    {
       this.location = location;
       this.tabNames = tabNames;
       this.pages    = pages;
       this.width    = width;
       this.height   = height;
    }

    /** Gets the width of this PageGroup
    */
    public int getWidth()
    {
       return width;
    }

    /** Sets the width of this PageGroup
    */
    public void setWidth(int width)
    {
       this.width = width;
    }

    /** Gets the height of this PageGroup
    */
    public int getHeight()
    {
       return height;
    }

    /** Sets the Height of this PageGroup
    */
    public void setHeight(int height)
    {
       this.height = height;
    }

    /** Gets the location of this PageGroup
    */
    public URL getLocation()
    {
       return location;
    }

    /** Sets the location of this PageGroup
    */
    public void setLocation(URL location)
    {
       this.location = location;
    }

    /** Gets the tabNames of this PageGroup
    */
    public String[] getTabNames()
    {
       return tabNames;
    }

    /** Sets the tabNames of this PageGroup
    */
    public void setTabNames(String[] tabNames)
    {
       this.tabNames = tabNames;
    }

    /** Gets the pages of this PageGroup
    */
    public String[] getPages()
    {
       return pages;
    }

    /** Sets the pages of this PageGroup
    */
    public void setPages(String[] pages)
    {
       this.pages = pages;
    }

    /** Adds a page to this PageGroup
    */
    public void addPage(String tabName, String page)
    {
       String[] newNames  = new String[tabNames.length + 1];

       //rebuild the tabNames
       for (int i=0; i < tabNames.length; i++)
       {
          newNames[i] = tabNames[i];
       }

       newNames[tabNames.length] = tabName;
       
       tabNames = newNames;

       //rebuild the pages
       String[] newPages = new String[pages.length + 1];

       for (int i=0; i < pages.length; i++)
       {
          newPages[i] = pages[i];
       }

       newPages[pages.length] = page;
       
       pages = newPages;
    }

    /** Removes a page from this PageGroup
    */
    public void removePage(String tabName)
    {
       String[] newNames  = new String[tabNames.length - 1];
       String[] newPages = new String[pages.length - 1];
       int      j         = 0;

       for (int i=0; i < tabNames.length; i++)
       {
          if (!tabName.equals(tabName))
              j++;

          // making the assumption that pages and
          // tabNames are the same length
          newNames[i] = tabNames[j];
          newPages[i] = pages[j];

       }
       
       tabNames = newNames;
       pages    = newPages;      
    }

}
