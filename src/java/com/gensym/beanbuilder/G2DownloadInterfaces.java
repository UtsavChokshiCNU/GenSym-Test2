/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2DownloadInterfaces.java
 *
 *
 *   Modifications:
 *
 */

/* To Do


*/

/**
 * NOTE
 *  G2BeanBuilder has been designed as a bimorphic
 *  application. This class is a wrapper class around
 *  G2BeanBuilder and as such, causes the latter to
 *  the GUI designed to provide an interface to the
 *  com.gensym.util.DownloadInterfaces class.
 *
 */

package com.gensym.beanbuilder;

import com.gensym.core.CmdLineArgHandler;
import com.gensym.util.*;
import com.gensym.jgi.download.DownloadInterfaces;

public class G2DownloadInterfaces extends Object
{
    public G2DownloadInterfaces()
    {
    }


   /*
    *
    *
    *
    */
    public static void main(String args[])
    {
         CmdLineArgHandler cmdLine = new CmdLineArgHandler (args);

      // see what command lines args were passed in to the program
      String host             = cmdLine.getOptionValue ("-host");
      String port             = cmdLine.getOptionValue ("-port");
      String clazz            = cmdLine.getOptionValue ("-class");
      boolean force           = cmdLine.getSwitchValue ("-force");
      boolean stubs           = cmdLine.getSwitchValue ("-stubs");
      boolean gui             = cmdLine.getSwitchValue ("+g");


       int nbArgs = 0;

       int nbNewArgs = 0;


       try{
           nbArgs = args.length;
        }catch (ArrayIndexOutOfBoundsException e){nbArgs = 0;}



        // if command line args have been specified, but not the +g,
        // then make a call to com.gensym.util.DownloadInterfaces
        // if +g has been specified, or no args, then launch the
        // beanbuilder in downloader mode
       if(nbArgs > 1 && !gui)
       {
	DownloadInterfaces.main(args);
       }
       else
       {
           nbNewArgs = nbArgs + 1;

           String[] newArgs = new String[ nbNewArgs ];

           newArgs[nbArgs]=new String ("-download");

           for (int i = 0; i < nbArgs ;i++){
                newArgs[i]= new String(args[i]);
           }

           G2BeanBuilder beanBuilder = new G2BeanBuilder ();
           beanBuilder.main(newArgs);
       }
    }
}
