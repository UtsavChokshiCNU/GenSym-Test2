/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.Excepinfo.java
 *
 *   Author: Allan Scott
 */
 package com.gensym.com;

 /** An Excepinfo is a structure used to provide detailed information
 * about a dispatch failure, when the return code of the dispatch is
 * DISP_E_EXCEPTION.
 * @see ActiveXDispatchException
 */
 public class Excepinfo 
 {	
   public Excepinfo(long code, 
     String source,
     String description,
     String helpFile,
     long helpContext)
   {
     this.code = code;
     this.source = source;
     this.description = description;
     this.helpFile = helpFile;
     this.helpContext = helpContext;
   }
   
   public long code;
                     
   public String source;
 
   public String description;
   
   public String helpFile;
   
   public long helpContext;

   @Override
   public String toString()
   {
     return
     "Exception Information:\n" +
     "code = 0x" + Long.toHexString(code) +"\n" +
     "source = " + source + "\n" +
     "description = " + description + "\n" +
     "helpFile = " + helpFile + "\n" +
     "helpContext = 0x" + Long.toHexString(helpContext);
   }
 }
 
