package com.gensym.demos.dialogapplet;

import com.gensym.files.*;
import java.io.*;
import com.gensym.net.g2.*;
import com.gensym.core.GensymApplication;

public class MediaMove
{
  public static void main(String[] args)
  {
    try {
      GensymApplication.initialize();
      G2ProtocolRegistry.loadInterpreters();
      URLFile source = URLFile.makeFileFromPath(args[0]);
      URLFile dest = URLFile.makeFileFromPath(args[1]);
      InputStream in = source.getInputStream();
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
