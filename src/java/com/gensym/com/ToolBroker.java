package com.gensym.com;

import java.io.PrintStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.io.IOException;

import java.util.StringTokenizer;

import java.lang.reflect.Method;

import sun.tools.javac.Main;

import com.gensym.jartools.JarFile;

/** An uninstantiable class that contains the interface to common Java
* tools that are used by the com module.  Currently (SEQUIOA, Beta 0)
* this class requires that the sun.tools package be in the classpath
*/
public final class ToolBroker 
{
  private static sun.tools.javac.Main compiler = null;
  
  public static boolean useJavac() {
      String property =  System.getProperty("com.gensym.com.usejavac");
      if (property == null || property.equals("")) 
          property = "true";  // For now make javac the default
      property = property.toLowerCase();
      if (property.equals("true")) {
      if (compiler != null)
            return true;
          else {
            try {
              compiler = new sun.tools.javac.Main(System.out,"");
            }
            catch (Throwable t) {                
              return false;
            }
            return true;
          }
      }
      else return false;
  }


  public static boolean useVersions() {
      String property = System.getProperty("com.gensym.com.useversions");
      if (property == null || property.equals("")) 
          property = "false";  // For now make no versions the default
      property = property.toLowerCase();
      if (property.equals("true")) {
          return true;
      }
      else return false;
  }

  /** Compile a java source file to the specified output directory.
  * Return value will indicate whether this is successful or not.
  * Stdout of the compiler is directed to System.out, Stderr is directed
  * to System.err.  Note that for classes that have packages this
  * will create the appropriate subdirectories for the package specified
  * in the output directory
  */
  public static boolean compileJavaSourceFile(String fileName,
	  String outputDirectory) {

        boolean useJavac = useJavac();
        File source = new File(fileName);
        String files = null;
       
        if (source.isDirectory()) {
          files = fileName + File.separator + "*.java";
        }
        else
        {
          int end = fileName.indexOf(".java");
          String stripped = fileName.substring(0, end);
      
          File dotclass = new File(stripped + ".class");
          
          if (! source.exists()) {
            System.out.println("Source does not exist - " + source);
            return false;

          }
          if (dotclass.exists()) {
            long sourceModified = source.lastModified();     
            long classModified = dotclass.lastModified();
            if (classModified >= sourceModified)
              return true;
          }
        }
        
        if (useJavac) { 
          System.gc();
          Boolean result;
          String classpath;
          classpath = System.getProperty("java.class.path");
          if (classpath == null)
            return false;
          try {
            if (outputDirectory != null && (! outputDirectory.equals(""))) {    
              return
                ((sun.tools.javac.Main) compiler).compile(new String[] {"-classpath", classpath, "-d",outputDirectory,fileName});
            }
            else { 
              return 
                ((sun.tools.javac.Main) compiler).compile(new String[] {"-classpath", 
                System.getProperty("java.class.classpath"), fileName});   
            }
          }
        catch (Exception e) {
            e.printStackTrace();
            return false;
        }
       }
       else {
         return false;
       }
  }

  /** Create a jar file from multiple filePaths and 
   *  multiple specifications of whether they are beans
   *  or not.
   */ 
  public static boolean createJarFile(String[] filePaths,
                                      boolean[] areBeans,  
                                      String jarFileName)
  {
    int filesLength;
    int areBeansLength;

    try {
      JarFile jarfile = new JarFile();
      filesLength = filePaths.length;
      areBeansLength = areBeans.length;

      for (int i =0; i < filesLength; i ++) {
          if (i < areBeansLength) {
            jarfile.putFile(filePaths[i],areBeans[i]);
          }
          else jarfile.putFile(filePaths[i],false);
      }
      jarfile.saveAs(jarFileName);
      return true;
    }
    catch (Exception e) {
      System.out.println("Failure to create jar file : " + e);
      e.printStackTrace();
      return false;
    }    
  }


  private static String getLocalDirectoryForFile(String path) {
    StringTokenizer stok = new StringTokenizer(path,File.separator);
    StringBuffer buf = new StringBuffer();
    String token;

    token = stok.nextToken();
    buf.append(token);
    while (stok.hasMoreTokens()) {
      token = stok.nextToken();
      if (stok.hasMoreTokens()) {
	buf.append(File.separator);
	buf.append(token);
      }
    }
    return buf.toString();		
  }

  private static String localizeFilePath(String path) {
    StringTokenizer stok = new StringTokenizer(path,"/");
    StringBuffer buf = new StringBuffer();
    String token;

    token = stok.nextToken();
    buf.append(token);
    while (stok.hasMoreTokens()) {
      token = stok.nextToken();
      buf.append(File.separator);
      buf.append(token);
    }
    return buf.toString();		
  }

  private static String fileNameOnly(String path) {
    StringTokenizer stok = new StringTokenizer(path,File.separator);
    String token = "";
    while (stok.hasMoreTokens()) 
      token = stok.nextToken();
    return File.separator + token;
  }

  private static void message(String line) {
    // Change to use tracing facility
    NativeMethodBroker.traceln(ActiveXTraceLevels.AX_PROGRESS, line);
  }

} 
