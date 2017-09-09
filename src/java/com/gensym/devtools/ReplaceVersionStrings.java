package com.gensym.devtools;

import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import java.io.BufferedReader;
import java.io.PrintWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.InputStream;
import java.io.IOException;
import java.io.Reader;
import java.util.Enumeration;
import java.util.StringTokenizer;
import java.util.Vector;

/******* ReplaceVersionStrings
 * read each file and check the extension
 * read each line and check if the symbols are there and replace
 * close the file
 * 
*/
public class ReplaceVersionStrings {
  static boolean MODIFIED = false;
  static FileReader fileInputStream = null;
  static FileWriter fileOutputStream = null;
  static PrintWriter fileWriter;
  private static Structure envStruct;
  private static final int MAX_TAGS  = 2;

  static Vector fileTypesToInclude = new Vector();
  {
    fileTypesToInclude.addElement(".java");
    fileTypesToInclude.addElement(".htm");
    fileTypesToInclude.addElement(".html");
    fileTypesToInclude.addElement(".txt");
    fileTypesToInclude.addElement(".bat");
    fileTypesToInclude.addElement(".sh");
    fileTypesToInclude.addElement(".reg");
  }
  
  public static void main(String[] args) {
    String fileName;
    String dirName;
    fileTypesToInclude.addElement(".java");
    fileTypesToInclude.addElement(".htm");
    fileTypesToInclude.addElement(".html");
    fileTypesToInclude.addElement(".txt");
    fileTypesToInclude.addElement(".bat");
    fileTypesToInclude.addElement(".sh");
    fileTypesToInclude.addElement(".reg");

    if (args.length == 1) {
      com.gensym.core.GensymApplication.initialize();    
      dirName = args[0];
      System.out.println("dir is: " + dirName);
      String tagFileName = System.getProperty ("com.gensym.version.tags");
      System.out.println(tagFileName);
      readTags(tagFileName + File.separator + "tags.txt");
      if (dirName != null){
        DirCleanup(dirName);
      }
    }
    else {
      System.out.println("usage: java com.gensym.devtools.ReplaceVersionStrings DirFullPath");
      System.out.println("ex: java com.gensym.devtools.ReplaceVersionStrings c:\\temp");
      System.exit(1);      
    }
  }
  
  private static void readTags(String tagsFileName) {
    int i;
    String line;    
    envStruct = new Structure ();
    Symbol[] oldTag = new Symbol[10];
    try {
      FileReader fileInputStream = new FileReader (tagsFileName);
      BufferedReader fileReader = new BufferedReader (fileInputStream);
      while ((line = fileReader.readLine ()) != null) {
        i = 0;
        StringTokenizer stoknizer = new StringTokenizer(line, "=");
        while (stoknizer.hasMoreTokens()) {
          if (i == MAX_TAGS)
	          System.out.println ("Too many tokens in " + line);          
          String tag = stoknizer.nextToken();
          System.out.println("tag " + tag);
          oldTag[i] = Symbol.intern (tag);
          tag = stoknizer.nextToken();
          envStruct.setAttributeValue (oldTag[i++], tag);
        }
      }
    }
    catch (FileNotFoundException e) {
      System.out.println(e);
    }
    catch (IOException e) {
      System.err.println(e.toString());;
    }
  }
  
  static void DirCleanup(String targetDirName) {
    File targetDir = new File (targetDirName);
    String dirList[] = targetDir.list();
    if (dirList == null) return;
    for (int i=0; i<dirList.length; i++) {
      String filename = dirList[i];
      String targetFilename = targetDir.getAbsolutePath()+File.separator+filename;
      File sourceFile = new File(targetFilename);
      if (sourceFile.isDirectory() && (!filename.equals("CVS"))) {
        DirCleanup(targetFilename);
      }
      int prefixPos = filename.lastIndexOf(".");
	    String fileType = prefixPos > -1 ? filename.substring(prefixPos) : "";
      //System.out.println("filetype " + fileType);
      //System.out.println(fileTypesToInclude);
      if ( fileTypesToInclude == null || 
           (fileTypesToInclude != null && fileTypesToInclude.contains(fileType))) {
        //System.out.println("parsing " + targetFilename);
        fileCleanup(targetFilename);
	    }
      else
        System.out.println("nothing");
    }
  }

  static void fileCleanup(String filename){
    String line;
    Object value = null, attribute = null;    
    File source = new File (filename);
    File target = new File (source.getPath() + "2");
    //System.out.println("In fileCleanup");
    try {
      fileInputStream = new FileReader (source);
      fileOutputStream = new FileWriter (target);
      fileWriter = new PrintWriter (fileOutputStream);
      BufferedReader fileReader = new BufferedReader (fileInputStream);
      while ((line = fileReader.readLine ()) != null) {
        //line = line.trim();
        Enumeration enumeration = envStruct.getAttributeNames();
        while (enumeration.hasMoreElements()) {
          attribute = enumeration.nextElement();
          try {
          value = envStruct.getAttributeValue((Symbol) attribute);
          }
          catch (NoSuchAttributeException e) {
            System.out.println(e);
          }
          int pos = line.indexOf(attribute.toString());
          if (pos > -1) {
            System.out.println(line + " before");
            line = multipleReplace(line, attribute.toString(), value.toString());
            System.out.println(line + " after\n");
          }
        }
        fileWriter.println(line);
      }
    }
    catch (FileNotFoundException e) {
      System.out.println(e);
    }
    catch (IOException e) {
      System.err.println(e.toString());;
    }
    finally {
      try {
        if (fileInputStream != null)
          fileInputStream.close();
	      if (fileOutputStream != null)
          fileOutputStream.close();
	        javaCopyFile (target, source);
	        target.delete ();        
        }
      catch (IOException e) {
        System.out.println(e);
      }
    }
  }

  static String replaceString(String original, String oldStr, String newStr){
    StringBuffer buf = new StringBuffer();
    int pos = original.indexOf(oldStr);
    int oldLen = oldStr.length();

    if (pos == -1)
      return original;
    else {
      if(pos != 0) {
        String temp = original.substring(0,pos);
        buf.append(temp);
        temp = original.substring(pos+oldLen,original.length());
        buf.append(newStr);
        buf.append(temp);
      }
      else {
        buf.append(newStr);
        String temp2 = original.substring(oldLen, original.length());
        buf.append(temp2);
      }

      return buf.toString();
    }
  }

  static String multipleReplace(String line, String oldToken, String newToken) {
    StringBuffer buf = new StringBuffer();
    int pos, curPos=0;
    int tokenLen = oldToken.length();
    int len = line.length();

    while ((pos = line.indexOf(oldToken, curPos)) >= 0) {
  	  buf.append(line.substring(curPos, pos));
  	  buf.append(newToken);
      curPos = pos + tokenLen;
    }
    buf.append(line.substring(curPos));
    return buf.toString();		
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
