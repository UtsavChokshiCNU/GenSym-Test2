package com.gensym.cbu.experimental.mibbrowser;

import java.util.*;
import java.io.*;

import com.adventnet.snmp.mibs.*;


public class MibFileLoaderNew {
  static private MibOperations mibOperations = null;
  private Vector searchPath = null;
  private Vector listeners = new Vector();
  static private Thread currentLoader = null;

  public MibFileLoaderNew (MibOperations mibOprs) {
    mibOperations = mibOprs;
  }

  private String getJustPath(File file) {
    String path = file.getAbsolutePath();
    int pos = path.lastIndexOf(file.separator);
    if (pos > 0)
      return path.substring(0,pos);
    else
      return path;
  }

  private String getJustFileName(File file) {
    String path = file.getAbsolutePath();
    int pos = path.lastIndexOf(file.separator);
    return path.substring(pos + 1);
  }

  private String omitExtension(String name) {
    int pos = name.lastIndexOf(".");
    if (pos > 0)
      return name.substring(0,pos);
    else
      return name;
  }

  private String findFile(final String fileName) {
    if (searchPath !=null) {
      Iterator it = searchPath.iterator();
      while (it.hasNext()) {
        //kjb - passing in a vector of File(s)
        //String path = (String)it.next();
        //File file = new File(path);
        File file = (File) it.next();
        File[] files = file.listFiles(new FilenameFilter() {
          @Override
		  public boolean accept(File dir, String name) {
            if (fileName.equalsIgnoreCase(name))
              return true;
            if (fileName.equalsIgnoreCase(omitExtension(name)))
              return true;
            String dashedName = makeDashedName(name);
            if(fileName.equalsIgnoreCase(dashedName)) return true;
            return false;
          }
        });
        if (files.length > 0)
          return files[0].getAbsolutePath();
      }
    }
    return null;
  }

  String makeDashedName(String name)
  {
    return name.replace('.','-');
    }

  public void loadMibFile(File file) {
    if (getSearchPath() == null) {
      searchPath = new Vector();
      searchPath.addElement(getJustPath(file));
    }
    Vector requiredFiles = new Vector();
    requiredFiles.addElement(getJustFileName(file));
    while(requiredFiles.size() > 0) {
      String mibFileName = (String)requiredFiles.elementAt(0);
      requiredFiles.removeElementAt(0);
      String fullMibFileName = findFile(mibFileName);
      if (fullMibFileName != null) {
        try {
          fireLoadingFile(mibFileName);
          MibModule mibModule = mibOperations.loadMibModule(fullMibFileName);
          fireLoadFinished(mibModule);
          Thread.yield();
        } catch (FileNotFoundException fnfe) {
          if (fnfe.getMessage().indexOf("Imports Failed") != -1) {
            String name = fnfe.getMessage().substring(
              fnfe.getMessage().lastIndexOf(":") + 1);
            requiredFiles.insertElementAt(name,0);
            continue;
          }
          else {
            System.err.println("FILE NOT FOUND:\n" + fnfe);
            fireLoadError(mibFileName, "FILE NOT FOUND: " + fnfe);
            break;
          }
        } catch (Exception e) {
          fireLoadError(mibFileName,"MibFileLoad ERROR:\n" + e);
          System.err.println("MibFileLoad ERROR:\n" + e);
          break;
        }
      }
      else {
        fireLoadError(mibFileName, "FILE NOT FOUND FROM SEARCH PATH");
        System.err.println(
          "MIB FILE NOT FOUND FROM SEARCH PATH: " + mibFileName);
        break;
      }
      //requiredFiles.remove(mibFileName); - moved up top
    }
  }

  public Vector getSearchPath() {
    return searchPath;
  }

  public void setSearchPath(Vector path) {
    searchPath = path;
  }
  public void addMibFileLoaderListener(MibFileLoaderListener l) {
    listeners.add(l);
  }

  public void removeMibFileLoaderListener(MibFileLoaderListener l) {
    listeners.remove(l);
  }

  void fireLoadingFile(String mibFile) {
    for (Enumeration e = listeners.elements(); e.hasMoreElements(); ) {
  	  ((MibFileLoaderListener)e.nextElement()).loadingFile(mibFile);
	  }
  }

  void fireLoadFinished(MibModule mibModule) {
    for (Enumeration e = listeners.elements(); e.hasMoreElements(); ) {
  	  ((MibFileLoaderListener)e.nextElement()).loadFinished(mibModule);
	  }
  }

  void fireLoadError(String mibFile, String msg) {
    for (Enumeration e = listeners.elements(); e.hasMoreElements(); ) {
  	  ((MibFileLoaderListener)e.nextElement()).loadError(mibFile,msg);
	  }
  }

  public void loadAllMibFiles(File dir, boolean recurseSubDirectories) {
    //load all mibFiles
    synchronized ( mibOperations) {
      while (MibFileLoaderNew.currentLoader != null &&
              MibFileLoaderNew.currentLoader != Thread.currentThread())
      {
        try {
          System.out.println("I'm Waiting " + Thread.currentThread());
          mibOperations.wait();
          System.out.println("I'm awake " + Thread.currentThread());
        } catch (InterruptedException ie) {
        }
      }
     System.out.println("I'm Loading " + Thread.currentThread());
      MibFileLoaderNew.currentLoader = Thread.currentThread();


      File[] files = dir.listFiles(new java.io.FileFilter() {
  	    public boolean accept(File pathname)
  	      {
            if( pathname.isFile() && isMibFile(pathname))
          		return true;
            else return false;
  	      }
    	  });
      if (files != null) {
        for (int i = 0; i < files.length; i++) {
          loadMibFile(files[i]);
          Thread.yield();
        }

      //load directories
      if( recurseSubDirectories) {
        files = dir.listFiles(new java.io.FileFilter() {
  	    public boolean accept(File pathname)
  	      {
            if( pathname.isDirectory())
          		return true;
            else return false;
  	      }
      	  });
        for ( int i = 0; i < files.length; i++)
            loadAllMibFiles(files[i], recurseSubDirectories);
        }
      }
       MibFileLoaderNew.currentLoader = null;
       System.out.println(Thread.currentThread() + " is Notifying");
       mibOperations.notifyAll();
      }
  }

  boolean isMibFile(final File fileName) {
    String upperCaseFileName = fileName.getName().toUpperCase();
     if( upperCaseFileName.endsWith(".ZIP")) return false;
     if( upperCaseFileName.endsWith(".TXT")) return false;
     if( upperCaseFileName.endsWith(".TAR")) return false;
     if( upperCaseFileName.endsWith(".GZ")) return false;
     if( upperCaseFileName.endsWith(".OID")) return false;
     return true;
  }
}
