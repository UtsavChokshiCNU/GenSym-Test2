package com.gensym.devtools;

import java.io.File;
import java.io.IOException;
import java.util.zip.ZipException;
import com.gensym.jartools.JarFile;
import com.gensym.core.CmdLineArgHandler;

public class AddFilesToJar {
  public static JarFile jarFile;
  private static String jarName;
  private boolean debug = true;

  public static void main(String args[]) {
    CmdLineArgHandler cmdLine = new CmdLineArgHandler (args);

    if (args.length == 0) {
      System.out.println("Usage: AddFilesToJar -jar <jar> [-files|-file] <file1> <file2>.. -save <newJar>");
    }

    else {
      String jar  = cmdLine.getOptionValue ("-jar");
      if (jar != null) {
        String[] files = cmdLine.getOptionValues ("-files");
        if (files == null)
          files = cmdLine.getOptionValues ("-file");
        if (files != null) {
          AddFilesToJar af = new AddFilesToJar(jar);
          af.addFiles(files);
          String newJar  = cmdLine.getOptionValue ("-save");
          af.saveJar(newJar);
        }
        else {
          System.out.println("Please specify files to be added to the jar");
        }
      }
      else
        System.out.println("Specify a jar with -jar <jarName>");
    }
  }

  public AddFilesToJar(String jar) {
    File file = new File(jar);
    jarName = jar;
    if (file.exists()) {
      System.out.println("Jar " + jar + " exists");
      try {
        System.out.println("Using existing jar: " + jar);
        jarFile = new JarFile(jar);
      }
      catch (Exception e) {
        System.out.println("Failed" + e);
      }
    }
    else {
      try {
        jarFile = new JarFile();
        System.out.println("Creating a new jar: " + jar);
      }
      catch (Exception e) {
        System.out.println("Failed" + e);
      }
    }
  }

  public void addFiles(String[] files) {
    for (int i=0; i<files.length; i++) {
      try {
        System.out.println("adding: " + files[i]);
        jarFile.putFile(files[i]);
      }
      catch (Exception e) {
      }
    }
  }

  public void saveJar(String name) {
    if (name != null) {
      try {
        System.out.println("Saving: " + name);
        jarFile.saveAs(name);
      }
      catch  (Exception e) {
      }
    }
    else {
      try {
        System.out.println("Saving: " + jarName);
        jarFile.saveAs(jarName);
      }
      catch  (Exception e) {
      }
    }
  }
}
