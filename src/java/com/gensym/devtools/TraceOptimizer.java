package com.gensym.devtools;

import com.gensym.core.CmdLineArgHandler;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.InputStream;
import java.io.IOException;
import java.io.Reader;
import java.util.StringTokenizer;

/**
 * This file has methods for removing Trace.send statements from java files.
 * TraceCleanup and DirTraceCleanup are used for manipulating a single file
 * or a directory and removing Trace.send statements from the file(s).
 * This could be extended for removing any statement, not just Trace.send. It also
 * could be modified to work with all types of files not just java
 */

public class TraceOptimizer {
  static boolean FOUNDSEMI = true;
  static boolean MODIFIED = false;
  static FileReader fileInputStream = null;
  static FileWriter fileOutputStream = null;
  static BufferedWriter fileWriter;

  public static void main(String[] args) {
    String fileName;
    String dirName;
    CmdLineArgHandler cmdLineArgHandler = new CmdLineArgHandler (args);
    fileName = cmdLineArgHandler.getOptionValue ("-file");
    dirName = cmdLineArgHandler.getOptionValue ("-dir");
    if (fileName != null) {
      TraceCleanup(fileName);
    }
    else if (dirName != null){
      DirTraceCleanup(dirName);
    }
    else {
      System.out.println("No '-file' or '-dir' flags specified");
    }
  }
  
  static void DirTraceCleanup(String targetDirName) {
    File targetDir = new File (targetDirName);
    String dirList[] = targetDir.list();
    if (dirList == null) return;
    for (int i=0; i<dirList.length; i++) {
      String filename = dirList[i];
      String targetFilename = targetDir.getAbsolutePath()+File.separator+filename;
      File sourceFile = new File(targetFilename);
      if (sourceFile.isDirectory() && (!filename.equals("CVS"))) {
        DirTraceCleanup(targetFilename);
      }
      if (targetFilename.lastIndexOf(".java") > 1) {
        //System.out.println("Editing file: " + targetFilename);
        TraceCleanup(targetFilename);
        if (MODIFIED) {
          System.out.println("file modified: " + targetFilename);
        }
        MODIFIED = false;
	    }
    }
  }

  static void TraceCleanup(String filename){
    String line;
    File source = new File (filename);
    String targetname = filename + ".copy";
    File sourceCopy = new File (targetname);
    String outputFilename = filename+".noTrace";
    File noTraceCopy = new File (outputFilename);
    javaCopyFile(source, sourceCopy);
    try {
      fileInputStream = new FileReader (source);
      fileOutputStream = new FileWriter (noTraceCopy);
      fileWriter = new BufferedWriter (fileOutputStream);
      BufferedReader fileReader = new BufferedReader (fileInputStream);
      while ((line = fileReader.readLine ()) != null) {
        String line1 = line;
        line = line.trim();
        try {
          editLine(line,line1);
        }
        catch (Exception e){
          System.out.println(e);
        }
      }
      fileWriter.flush();
    }
    catch (FileNotFoundException e) {
      System.out.println(e);
    }
    catch (IOException e) {
      System.out.println(e);
    }
    finally {
      try {
        if (fileInputStream != null)
          fileInputStream.close();
	      if (fileOutputStream != null)
          fileOutputStream.close();
        if (MODIFIED) {
          if (source.exists())
            source.delete();
          source = new File(filename);
	        noTraceCopy.renameTo(source);
        }
        else{
          if (sourceCopy.exists())
            sourceCopy.delete();
          if (noTraceCopy.exists())
	          noTraceCopy.delete ();
        }
      }
      catch (IOException e) {
        System.out.println(e);
      }
    }
  }

  static void editLine (String line, String line1) throws Exception{
    if (FOUNDSEMI) {
      if (line.startsWith("Trace.send")){
        MODIFIED = true;
        //System.out.println("******** found Trace ************");
        //System.out.println(line);
        if (line.endsWith(";")){
          ; //dont write it
        }
        else
          FOUNDSEMI = false;
      }
      else{
        try {
        fileWriter.write(line1,0,line1.length());
        fileWriter.newLine();
        }
        catch (IOException e) {
          System.out.println(e);
        }
      }
    }
    else {
      if (line.endsWith(";"))
        FOUNDSEMI = true;
    }
  }
  
  static void javaCopyFile(File sourceFile, File targetFile) {
    try {
      FileInputStream inf = new FileInputStream(sourceFile);
      FileOutputStream outf = new FileOutputStream(targetFile);

      byte[] ba = new byte[4096];
      int bytes_read;
      while ((bytes_read = inf.read(ba)) != -1) {
	      outf.write(ba, 0, bytes_read);
      }
      inf.close();
      outf.close();
    } catch (Exception e) {
      System.out.println(e.toString());
    }
  }
}
