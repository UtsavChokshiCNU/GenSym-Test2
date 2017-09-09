package com.gensym.media;

import com.gensym.files.*;
import com.gensym.ntw.files.*;
import java.io.*;
import java.net.*;
import com.gensym.net.g2.*;
import com.gensym.core.GensymApplication;

public class MediaMove
{
  public static void main(String[] args)
  {
    try {
      T2URLDirectoryModel directoryModel 
	= new T2URLDirectoryModel(true,false,true,null,null);
      GensymApplication.initialize();
      G2ProtocolRegistry.loadInterpreters();
      String sourceName = args[0];
      InputStream in;
      if (sourceName.startsWith("http:") ||
	  sourceName.startsWith("ftp:"))
	{
	  URL url = new URL(sourceName);
	  in = url.openStream();
	}
      else
	{
	 
	  URLFile source = directoryModel.makeFileFromPath(args[0]);
	  in = source.getInputStream();
	}
      URLFile dest = directoryModel.makeFileFromPath(args[1]);
      OutputStream out = dest.getOutputStream();
      int b;
      int count = 0;
      while ((b = in.read()) != -1)
	{
	  out.write(b);
	  count++;
	  if ((count % 10000) == 0)
	    System.out.println("moved "+count+" bytes");
	}
      in.close();
      out.close();
      System.exit(0);
    }
    catch (Exception e)
      {
	e.printStackTrace();
      }
  }

}
