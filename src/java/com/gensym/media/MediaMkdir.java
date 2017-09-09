package com.gensym.media;

import com.gensym.files.*;
import com.gensym.ntw.files.*;
import java.io.*;
import com.gensym.net.g2.*;
import com.gensym.core.GensymApplication;

public class MediaMkdir
{
  public static void main(String[] args)
  {
    try {
      GensymApplication.initialize();
      G2ProtocolRegistry.loadInterpreters();
      T2URLDirectoryModel directoryModel 
	= new T2URLDirectoryModel(true,false,true,null,null);
      URLFile directory = directoryModel.makeFileFromPath(args[0]);
      if (directory instanceof G2MediaFile)
	{
	  if (!((G2MediaFile)directory).makeSubDirectory(args[1]))
	    System.out.println("could not make sub directory");
	}
      else
	{
	  System.out.println("Non media bins not yet supported.");
	}
      System.exit(0);
    }
    catch (Exception e)
      {
	e.printStackTrace();
      }
  }

}
