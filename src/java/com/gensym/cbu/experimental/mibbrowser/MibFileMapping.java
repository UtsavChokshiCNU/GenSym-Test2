package com.gensym.cbu.experimental.mibbrowser;

import java.io.*;
import java.util.*;

public class MibFileMapping
{
  Hashtable mappings = new Hashtable();
  
  public static void main(String args[])
    {
      try {
	MibFileMapping mfm = new MibFileMapping();

	File startingDirectory = new File("D:/gensym/Pinpoint/Event Handling/mibs");
	mfm.collectMappings(startingDirectory);
	
	File outputFile
	  = new File("D:/bt/kbolton/java/com/gensym/cbu/experimental/mibbrowser/MibFileMap.txt");
	mfm.writeMappings(outputFile);
      } catch (IOException ioe) {
	System.out.println(ioe);
      } catch (KeywordNotFoundException knfe){
	System.out.println(knfe);
      }
    }

  public void collectMappings(File startingDirectory)throws IOException, KeywordNotFoundException
    {
      //System.out.println("Writing Files in " + startingDirectory);
      File[] files = startingDirectory.listFiles();
      File nextFile;
      MibFile mibFile;
      for (int i = 0; i < files.length; i++)
	{
	  nextFile = files[i];
	  if (nextFile.isDirectory()) collectMappings(nextFile);
	  else {
	    mibFile = new MibFile (nextFile);
	    System.out.println("reading " + nextFile);
	    mibFile.parseFile();
	    //System.out.println("read " + nextFile + " name = " + mibFile.getName());
	    if (mibFile.getName() != null) {
	      if (mappings.contains(mibFile.getName()))
		  System.out.println("Mappings Already contains " + mibFile.getName() +
				     " associated with " + mappings.get(mibFile.getName()));
	      else mappings.put(mibFile.getName(), nextFile.getAbsolutePath());
	    }
	  }
	}
    }

  public void writeMappings(File outputFile)throws IOException
    {
      FileWriter fw = new FileWriter(outputFile);
      BufferedWriter bw = new BufferedWriter(fw);
      String key;
      for (Enumeration e = mappings.keys(); e.hasMoreElements();)
	{
	  key = (String)e.nextElement();
	  bw.write(key + "," + mappings.get(key) + "\n");
	}
      bw.flush();
      fw.close();
    }
}
