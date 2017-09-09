
package com.gensym.beaneditor;

import java.util.*;
import java.io.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.jgi.*;
import com.gensym.ntw.*;
import com.gensym.classes.MediaBin;

public class Write
{  
  static Symbol media_bin_ = Symbol.intern("MEDIA-BIN");

   
  public static void main (String args[])
  {
    G2Connection  context = null;    
    Symbol        bin_name_ = Symbol.intern(args[2]);
	 MediaBin      mbw     = null;

	 try
    {
        TwGateway.initialize ();
        context = (G2Connection)TwGateway.openConnection(args[0], args[1]);
	((TwAccess)context).login();
        mbw = (MediaBin) context.getUniqueNamedItem(media_bin_, bin_name_ );
	 }
    catch (Exception e)
    {
      System.err.println (e);
    }
	 
    try
    {

      File            file = new File(".", args[3]);
      FileInputStream fis  = new FileInputStream(file);
      int             ch;
      int             i = 0;

	   Sequence location = new Sequence(0);
	  
	   G2BinaryOutputStream out = mbw.makeBinaryOutputStream(location, args[3]);

      while ((ch = fis.read()) != -1)
      {
         out.write(ch);
         i++;
      }
	   
      fis.close();
	   out.close();

      System.out.println ("Wrote " + args[3] +
                          "(" + i + " bytes) to media bin " + args[2] + ".");
      System.exit(0);

	 }
	 catch (Exception e)
	 {
      e.printStackTrace();
    }

  }

}
