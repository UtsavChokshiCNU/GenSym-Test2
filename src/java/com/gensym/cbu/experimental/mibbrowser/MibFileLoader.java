package com.gensym.cbu.experimental.mibbrowser;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.tree.*;
import java.util.*;

public class MibFileLoader
{
  static MibFileObjectHashtable ht = new MibFileObjectHashtable();
  Vector listeners = new Vector();
  final MibFile mibFile = new MibFile();
  static MibDirectories mibDirectories = new MibDirectories();
  static Vector loadedMibFiles = new Vector();
  
  static public MibFileObjectHashtable getHashtable ()
    {
      return MibFileLoader.ht;
    }

  static boolean alreadyLoaded(String mibName)
    {
      MibFile mibFile;

      if (mibName.toUpperCase().indexOf("RFC-1212") == 0) return true;
      if (mibName.toUpperCase().indexOf("RFC-1215") == 0) return true;
      for(Enumeration e = loadedMibFiles.elements(); e.hasMoreElements(); )
	{
	  mibFile = (MibFile)e.nextElement();
	  if(mibFile.getName().toUpperCase().indexOf(mibName) == 0) return true;
	}
      return false;
    }

  static File findRequiredFile(String mibName)
    {
      File directory;
      File[] fileList;
      File f;

      //System.out.println("looking for " + mibName);
      
      for (Enumeration e = mibDirectories.getDirectories(); e.hasMoreElements();)
	{
	  directory = (File)e.nextElement();
	  //System.out.println("Dir = " + directory.getPath());
	  fileList = directory.listFiles();
	  //System.out.println("Filelist contains " + fileList.length + " files");
	  for (int i = 0; i < fileList.length; i++)
	    {
	      f = fileList[i];
	      if (f.isFile())
		{
		  //System.out.println("=? " + f.getName());
		  if (f.getName().equals(mibName)) return f;
		}
	    }
	}
      return null;
    }

  public void addMibFileLoaderListener(MibFileLoaderListener l)
    {
      listeners.add(l);
    }

  public void removeMibFileLoaderListener(MibFileLoaderListener l)
    {
      listeners.remove(l);
    }

  void fireProgressEvent(String message)
    {
      for (Enumeration e = listeners.elements(); e.hasMoreElements(); )
	{
	  ((MibFileLoaderListener)e.nextElement()).progressEvent(mibFile, message);
	}
    }

    void fireLoadFinished()
    {
      for (Enumeration e = listeners.elements(); e.hasMoreElements(); )
	{
	  ((MibFileLoaderListener)e.nextElement()).loadFinished(mibFile);
	}
    }

  void fireRequiredFileLoaded(MibFile mibFile)
    {
      for (Enumeration e = listeners.elements(); e.hasMoreElements(); )
	{
	  ((MibFileLoaderListener)e.nextElement()).requiredFileLoaded(mibFile);
	}
    }
  
  void fireLoadingRequiredFile(MibFile mibFile)
    {
      for (Enumeration e = listeners.elements(); e.hasMoreElements(); )
	{
	  ((MibFileLoaderListener)e.nextElement()).loadingRequiredFile(mibFile);
	}
    }
  
  public MibFileLoader(final File file)
    {
      mibFile.setFile(file);
    }

  public MibFile getMibFile()
    {
      return mibFile;
    }

  public void loadMibFile()
    {
      try {
	fireProgressEvent("loading " + mibFile.getFileName());
	mibFile.loadFile();
	fireProgressEvent("parsing " + mibFile.getFileName());
	mibFile.parseFile();
	
	Vector requiredFiles = mibFile.getRequiredFiles();
	String requiredMibName;
	MibFileLoader mibFileLoader;
	File requiredFile;
	for (Enumeration e = requiredFiles.elements(); e.hasMoreElements(); )
	  {
	    requiredMibName = (String)e.nextElement();
	    if (!MibFileLoader.alreadyLoaded(requiredMibName))
	      {
		requiredFile = findRequiredFile(requiredMibName);
		if (requiredFile != null)
		  {
		    mibFileLoader = new MibFileLoader(requiredFile);
		    fireLoadingRequiredFile(mibFileLoader.getMibFile());
		    mibFileLoader.loadMibFile();
		    fireRequiredFileLoaded(mibFileLoader.getMibFile());
		  }
		else
		  System.out.println("couldn't find mib file:" +  requiredMibName);
	      }
	  }
		  
      } catch (IOException ioe) {
	System.out.println(ioe);
      } catch (KeywordNotFoundException knfe) {
	System.out.println(knfe);
	System.out.println(mibFile.fileContents);
      } catch (TokenNotFoundException tnfe) {
	System.out.println(tnfe);
	System.out.println(mibFile.fileContents);
      }
      fireProgressEvent("done loading " + mibFile.getFileName());
      
      updateHashtable();
      
      determineFullNames();
      
      MibFileLoader.loadedMibFiles.add(mibFile);
      fireLoadFinished();
    }

  void updateHashtable()
    {
      fireProgressEvent("updating hashtable with Object Types");
      MibFileObject mfo;
      for (Enumeration e = mibFile.objectTypes.elements();
	   e.hasMoreElements();)
	{
	  mfo = (MibFileObject)e.nextElement();
	  MibFileLoader.ht.put(mfo.getSymbolicName(), mfo);
	}

      fireProgressEvent("updating hashtable with Trap Types");
      for (Enumeration e = mibFile.trapTypes.elements();
	   e.hasMoreElements();)
	{
	  mfo = (MibFileObject)e.nextElement();
	  MibFileLoader.ht.put(mfo.getSymbolicName(), mfo);
	}

      fireProgressEvent("updating hashtable with Notification Types");
      for (Enumeration e = mibFile.notificationTypes.elements();
	   e.hasMoreElements();)
	{
	  mfo = (MibFileObject)e.nextElement();
	  MibFileLoader.ht.put(mfo.getSymbolicName(), mfo);
	}

      for (Enumeration e = mibFile.objectIdentifiers.elements();
	   e.hasMoreElements();)
	{
	  mfo = (MibFileObject)e.nextElement();
	  MibFileLoader.ht.put(mfo.getSymbolicName(), mfo);
	}
    }

  void determineFullNames()
    {
      String symbolicName;
      MibFileObject mfo;
      
      fireProgressEvent("determining full names");
      for (Enumeration e = MibFileLoader.ht.keys(); e.hasMoreElements(); )
	{
	  mfo = (MibFileObject)MibFileLoader.ht.get(e.nextElement());
	  if(mfo.getFullSymbolicName() == null) {
	    determineFullNames(mfo);
	  } 
	}
      //dumpHashtable();
    }

  void determineFullNames(MibFileObject mfo)
    {
      String parentSymbolicName = mfo.getParentSymbolicName();
      MibFileObject parent;
      fireProgressEvent("determining full names for " + mfo.getSymbolicName());
      //System.out.println("MFO =" + mfo.getSymbolicName());
      //System.out.println("Parent Symbolic Name: " + parentSymbolicName);
      if (parentSymbolicName != null)
	{
	  parent = (MibFileObject)MibFileLoader.ht.get(parentSymbolicName);
	  if(parent != null)
	    {
	      if(parent.getFullSymbolicName() == null)
		{
		  determineFullNames(parent);
		}
	      //System.out.println(parent);
	      mfo.setFullSymbolicName(parent.getFullSymbolicName() + "." +
				      mfo.getSymbolicName());
	      mfo.setFullNumericName(parent.getFullNumericName() + "." +
				      mfo.getNumericName());
	    }
	  else
	    {
	      System.out.println("Hashtable did not contain parent of\n" + mfo);
	    }
	}
      else
	{
	  System.out.println("parentSymbolicName of " + mfo + " is null");
      }
    }

  static void dumpHashtable ()
    {
      String key;
      System.out.println("Hashtable");
      for (Enumeration e = MibFileLoader.ht.keys(); e.hasMoreElements(); )
	{
	  key = (String)e.nextElement();
	  System.out.println(key + " = " + (MibFileObject)MibFileLoader.ht.get(key));
	}
    }
}
