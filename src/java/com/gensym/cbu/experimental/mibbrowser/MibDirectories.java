package com.gensym.cbu.experimental.mibbrowser;

import java.io.*;
import java.util.*;
import javax.swing.*;

class MibDirectories {
  Vector directories = new Vector();

  public void addDirectory(String dir)
    {
      addDirectory(new File(dir));
    }

  public void addDirectory(File dir)
    {
      directories.add(dir);
    }

  public void removeDirectory(File dir)
    {
      directories.remove(dir);
    }

  public Enumeration getDirectories()
    {
      return directories.elements();
    }

  public MibDirectories()
    {
      File file = new File("D:/gensym/Pinpoint/Event Handling/mibs");
      directories.add(file);
      addAllSubDirectories(file);
    }

    void addAllSubDirectories(File dir)
    {
      File[] files = dir.listFiles(new FilenameFilter() {
          @Override
		public boolean accept(File dir, String name) {
            File candidate = new File(dir, name);
            if (candidate.isDirectory()) return true;
            return false;
          }
        });
        if(files != null) {
      for ( int i = 0; i < files.length; i++) {
        //System.out.println("i = " + i + " : " + files[i]);
        directories.add(files[i]);
        addAllSubDirectories(files[i]);
        }
      }
      }
}
