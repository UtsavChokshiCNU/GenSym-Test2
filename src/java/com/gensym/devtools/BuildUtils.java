package com.gensym.devtools;

import java.io.File;
import java.io.FileFilter;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.StringTokenizer;
import java.util.Vector;

public class BuildUtils {

  public static final char EXTENSION_SEPARATOR = '.';

  public static final Hashtable EXTENSIONS_TO_INCLUDE = new Hashtable();
  static {
    EXTENSIONS_TO_INCLUDE.put("java", Boolean.TRUE);
    EXTENSIONS_TO_INCLUDE.put("ser", Boolean.TRUE);
    EXTENSIONS_TO_INCLUDE.put("ovr", Boolean.TRUE);
    EXTENSIONS_TO_INCLUDE.put("gif", Boolean.TRUE);
    EXTENSIONS_TO_INCLUDE.put("jpg", Boolean.TRUE);
    EXTENSIONS_TO_INCLUDE.put("htm", Boolean.TRUE);
    EXTENSIONS_TO_INCLUDE.put("html", Boolean.TRUE);
    EXTENSIONS_TO_INCLUDE.put("class", Boolean.TRUE);
    EXTENSIONS_TO_INCLUDE.put("properties", Boolean.TRUE);
    EXTENSIONS_TO_INCLUDE.put("kbs", Boolean.TRUE);
    EXTENSIONS_TO_INCLUDE.put("txt", Boolean.TRUE);
    EXTENSIONS_TO_INCLUDE.put("bat", Boolean.TRUE);
    EXTENSIONS_TO_INCLUDE.put("sh", Boolean.TRUE);
    EXTENSIONS_TO_INCLUDE.put("lisp", Boolean.TRUE);
    EXTENSIONS_TO_INCLUDE.put("dat", Boolean.TRUE);
    EXTENSIONS_TO_INCLUDE.put("jar", Boolean.TRUE);
    EXTENSIONS_TO_INCLUDE.put("xml", Boolean.TRUE);
  }

  public static String getExtension(String fileName) {
    int index = fileName.indexOf(EXTENSION_SEPARATOR);
    if (index != -1)
      return fileName.substring(index + 1);
    else
      return null;
  }
    
  public static final FileFilter FILE_TYPES_TO_INCLUDE =
  new FileFilter() {
    @Override
    public boolean accept(File file) {
      if (file.isDirectory())
	return false;
      String extension = getExtension(file.getName());
      return (extension != null && EXTENSIONS_TO_INCLUDE.get(extension) != null);
    }
  };

  public static final FileFilter FILE_TYPES_TO_INCLUDE_WITHOUT_JAVA =
  new FileFilter() {
    @Override
    public boolean accept(File file) {
      if (file.isDirectory())
	return false;
      String extension = getExtension(file.getName());
      return (extension != null && !"java".equals(extension) && EXTENSIONS_TO_INCLUDE.get(extension) != null);
    }
  };

  public static final FileFilter FILE_TYPES_TO_INCLUDE_WITH_DIRECTORIES =
  new FileFilter() {
    @Override
    public boolean accept(File file) {
      if (file.isDirectory()) {
	if (alwaysExclude(file))
	  return false;
	File[] files = file.listFiles(this);
	return files != null && files.length != 0;
      } else
	return true;
    }
  };

  public static final String JAVA_SUFFIX = ".java";

  public static final FileFilter JAVA_FILES =
  new FileFilter() {
    @Override
    public boolean accept(File file) {
      if (file.isDirectory())
	return false;
      String name = file.getName();
      return name.endsWith(JAVA_SUFFIX);
    }
  };

  private static final Vector dirNamesToAlwaysExclude = new Vector();
  static {
    dirNamesToAlwaysExclude.addElement("Cvs");
    dirNamesToAlwaysExclude.addElement("CVS");
  }

  public static boolean alwaysExclude(File file) {
    String name = file.getName();
    if (dirNamesToAlwaysExclude.contains(name))
      return true;
    else
      return false;
  }

  /**
   * @returns a Vector of Strings by breaking up line with the
   * default tokenizer.
   */
  public static Vector getList(String line) {
    return getList(line, null);
  }

  public static Vector getList(String line, String delimiters) {
    Vector list = new Vector();
    StringTokenizer st = delimiters == null ?
      new StringTokenizer(line):
      new StringTokenizer(line, delimiters);
    while (st.hasMoreElements()) {
      String item = st.nextToken();
      //System.out.println("Token " + item);
      list.addElement(item);
    }   
    return list;
  }

  public static void main(String[] args) {
    for(int i = 0; i < args.length; i++) {
      File dir = new File(args[i]);
      File[] files = dir.listFiles(FILE_TYPES_TO_INCLUDE);
      for (int j = 0; j < files.length; j++) {
	System.out.println("file=" + files[j].getName());
      }
    }
  }

  public static File ensureDirectory(File rootDir, String relativePath)
  throws IOException {
    String rootPath = rootDir.getAbsolutePath();
    String fullPath = rootPath + File.separator + relativePath;
    File newDirectory = new File(fullPath);
    newDirectory.mkdirs();
    return newDirectory;
  }

  public static File newFile(File directory, String name) {
    String dirPath = directory.getAbsolutePath();
    String newPath = dirPath + File.separator + name;
    return new File(newPath);
  }

  public static String getRelativePath(File rootDirectory, File subFile) {
    String fullRootPath = rootDirectory.getAbsolutePath();
    String fullSubPath = subFile.getAbsolutePath();
    return fullSubPath.substring(fullRootPath.length());
  }

  public static void copyFile(File sourceFile, File targetFile)
  throws IOException {
    FileInputStream inf = new FileInputStream(sourceFile);
    FileOutputStream outf = new FileOutputStream(targetFile);
    try {
      byte[] ba = new byte[4096];
      int bytes_read;
      while ((bytes_read = inf.read(ba)) != -1) {
	outf.write(ba, 0, bytes_read);
      }
    } finally {
      inf.close();
      outf.close();
    }
  }

  /**
   * recursively copies sourceDirectory into targetDirectory.
   */
  public static void copyDirectory(File targetDirectory,
				   File sourceDirectory,
				   FileFilter filter)
  throws IOException {
    File[] filesToCopy = sourceDirectory.listFiles(filter);
    if (filesToCopy == null)
      return;
    int length = filesToCopy.length;
    for (int i = 0; i < length; i++) {
      File currentFile = filesToCopy[i];
      if (currentFile.isDirectory()) {
	String name = currentFile.getName();
	File newTarget = ensureDirectory(targetDirectory, name);
	copyDirectory(newTarget, currentFile, filter);
      } else {
	File outFile = newFile(targetDirectory, currentFile.getName());
	copyFile(currentFile, outFile);
      }
    }
  }

  public static String convertPackageToRelativePath(String packageName) {
    return packageName.replace('.', File.separatorChar);
  }

  public static File getFileForPackage(String root, String packageName) {
   return new File(root + File.separator +
		   convertPackageToRelativePath(packageName));
  }

  private static Hashtable packageInfoMap = new Hashtable();

  public static final String PACKAGE_INFO = "package.info";

  private static final Object NO_MODULE_INFO = new Object();

  public static ModuleInfo getModuleInfoForPackage(String root, String packageName) {
    Object moduleInfo = packageInfoMap.get(packageName);
    if (moduleInfo == null) {
      File dir = getFileForPackage(root, packageName);
      File infoFile = new File(dir.getAbsolutePath() + File.separator +
			       PACKAGE_INFO);
      if (infoFile.exists()) {
	try {
	  moduleInfo = new ModuleInfo(infoFile, root, false);
	} catch (IOException ioe) {
	  ioe.printStackTrace();
	  packageInfoMap.put(packageName, NO_MODULE_INFO);
	  return null;
	}
	packageInfoMap.put(packageName, moduleInfo);
	return (ModuleInfo)moduleInfo;
      } else {
	packageInfoMap.put(packageName, NO_MODULE_INFO);
	return null;
      }
    } else if (NO_MODULE_INFO.equals(moduleInfo)) {
      return null;
    } else {
      return (ModuleInfo)moduleInfo;
    }
  }

  public static boolean wildcardCompare(Vector names, String name) {
    if (names == null) {
    	return false;
    }
    for (Enumeration e = names.elements(); e.hasMoreElements();) {
      String compareStr = (String)e.nextElement();
      if (wildcardCompare(compareStr, name))
	      return true;
    }
    return false;
  }

  public static boolean wildcardCompare(final String source, final String toCompareString) {
    //System.out.println(source + "  " +  toCompareString);
	String compareString = toCompareString;
    if (source.equals(compareString))
      return true;

    StringTokenizer st = new StringTokenizer(source, "*");
    int numTokens = st.countTokens();
    String tokens[] = new String[numTokens];
    int i = 0;
    while (st.hasMoreTokens()) {
      tokens[i] = st.nextToken();
      //System.out.println("Wtoken " + i + tokens[i]);
      i++;
    }

    for (i = 0; i<numTokens; i++) {
      if (i==0) {
	      if (compareString.indexOf(tokens[i]) == -1)
	        return false;
	      else
	    	  compareString = compareString.substring(compareString.indexOf(tokens[i]) + 
						           tokens[i].length()); 
      } else {
	      if (!compareString.startsWith(tokens[i])) 
	        return false;
	      else
	    	  compareString = compareString.substring(tokens[i].length());
      }

      if (i<numTokens-1) {
	      int nextTokenPos = compareString.indexOf(tokens[i+1]);
	      if (nextTokenPos > 0)
	    	  compareString = compareString.substring(nextTokenPos);
	      else if (nextTokenPos == -1)
	        return false;
      }
    }

    return true;
  }
}

