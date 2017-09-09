package com.gensym.demos.dialogapplet;

import com.gensym.files.*;
import java.io.*;
import com.gensym.net.g2.*;
import com.gensym.core.GensymApplication;
import com.gensym.jartools.*;

public class JarConverter
{
  public static void main(String[] args)
  {
    String jarFileName = "c:\\bt\\jed-nt2\\java\\eatme.jar";
    String[] filePaths = new String[] { "asdf", "qwer"};
    boolean[] areBeans = new boolean[] { false, false };
    try {
      JarFile jarfile = new JarFile();
      int filesLength = filePaths.length;
      int areBeansLength = areBeans.length;

      for (int i =0; i < filesLength; i ++) {
	System.out.println("jar path "+filePaths[i]);
          if (i < areBeansLength)
	    jarfile.putFile(filePaths[i],areBeans[i]);
          else jarfile.putFile(filePaths[i],false);
      }
      jarfile.saveAs(jarFileName);
      
    }
    catch (Exception e) {
      System.out.println("Failure to create jar file : " + e);
      e.printStackTrace();
    }    
  }

}
