/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 PageGroupCommands.java
 *
 */
package com.gensym.beaneditor;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.util.Vector;
import java.io.IOException;
import java.net.URL;
import com.gensym.files.URLFile;
import com.gensym.ntw.files.*;
import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.util.ResourceCache;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.dlgruntime.PageGroup;

class PageGroupCommands extends AbstractCommand{

  //Command Keys
  static final String EDIT_PROPERTIES = "PageGroupEditProperties";

  private static final Resource errorResource = Resource.getBundle("com.gensym.beaneditor.Errors");

  private EditorFrame frame;
  private PageCommands pageCommands;

  PageGroupCommands(EditorFrame frame, PageCommands pageCommands){
    super(new CommandInformation[]{
      new CommandInformation(EDIT_PROPERTIES, true,
    	  "CommandShortResource", "CommandLongResource", null, null, null, false)});
    this.frame = frame;
    this.pageCommands = pageCommands;
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey)) {
      throw new IllegalStateException(errorResource.format("CommandIsUnavailable", cmdKey));
    }

    //System.out.println("PageGroupCommands handling command key:"+cmdKey);
    if (cmdKey.equals(EDIT_PROPERTIES)){} 
  }

  PageGroup makePageGroup(String parentURLString,
			  String parentFilename,
			  boolean forTesting)
       throws IOException
  {
    PageNode page = pageCommands.getFirstPage();
    int maxHeight = 0, maxWidth = 0, count = pageCommands.pageCount(), i=0;
    String[] tabNames = new String[count];
    String[] pageNames = new String[count];
    while (page != null)
      {
	String pageFilename = page.location + "_" + parentFilename;
	pageNames[i] = pageFilename;
	tabNames[i] = page.name;
	Dimension size = page.canvas.getContainerSize();
	maxWidth = Math.max(maxWidth,size.width);
	maxHeight = Math.max(maxHeight,size.height);
	if (forTesting)
	  ResourceCache.registerResource(pageFilename,
					 page.canvas.serializeToBytes());
	else
	  {
	    T2URLDirectoryModel directoryModel 
	      = new T2URLDirectoryModel(true,true,true,null,null);
	    URLFile urlFile 
	      = directoryModel.makeFileFromPath(parentURLString+"/"+pageFilename);
	    try {
	      page.canvas.save(urlFile.getOutputStream());
	    } catch (java.io.IOException e)
	      {
		Trace.exception(e);
	      }
	  }
	page = page.next;
	i++;
      }
    return new PageGroup(new URL(parentURLString),
			 tabNames,
			 pageNames,
			 maxWidth,
			 maxHeight);
  }

}

  
