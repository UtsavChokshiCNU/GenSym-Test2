/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.FileBroker.java
 *
 *   Author: Allan Scott
 */
package com.gensym.com;

import java.io.File;
import java.util.StringTokenizer;

/** An uninstantiable class that contains methods for
* the File facilities used by the com package.
*/ 
public final class FileBroker {

/** Returns a File object for a file in a temporary directory
* The file name is generated from the integer arguments and the
* suffix.  The integer arguments are converted into hex. 
*/
public static File generateTemporaryFile(int key1, 
                                         int key2,
                                         int key3,
                                         String suffix) {
  return new File(generateTemporaryFileName(key1,key2,key3,suffix));
}

/** Returns a File object for a file of the name specified
* in a temporary directory 
*/
public static File generateTemporaryFile(String fileName) {
		return new File(generateTemporaryFileName(fileName));
}

/** Deletes a file 
*/
public static boolean deleteTemporaryFile(File file) {
		return file.delete();
}

/** Generates a the full path of a temporary file from
* the arguments.The integer keys are encoded into hex and
* included in the filename, and the suffix is appended.
*/
public static String generateTemporaryFileName(int key1,
											   int key2,
											   int key3,
											   String suffix) {
    String path = generateTemporaryFilePath();
    return (path + File.separator +
          Integer.toHexString(key1) +
	    Integer.toHexString(key2) +
	    Integer.toHexString(key3) + "." + suffix);
}


/** Returns a full path to locate a temporary file, including the
* filename specified by the argument.
*/
public static String generateTemporaryFileName(String fileName) {
	return generateTemporaryFilePath() + File.separator + fileName;	
}

/** Returns a location where the com module can create temporary
* files.  The path returned is taken from the following system
* properties, in order of preference:<br>
* i) com.gensym.com.emitdir <br>
* ii) com.gensym.beaneditor.jarlocation <br>
* iii) user.dir <br>
* iv) user.home <br>
* v) the current directory of this process
*/
public static String generateTemporaryFilePath() {
    String property;
    if ((property = System.getProperty("com.gensym.com.emitdir")) 
	== null
	|| dirNotWritable(property)) 
      if ((property = System.getProperty("com.gensym.beaneditor.jarlocation"))
	  == null
	  || dirNotWritable(property))
	if(dirNotWritable(property = System.getProperty("user.dir")))
	  if (dirNotWritable(property = System.getProperty("user.home")))
	    property = "";	

    if (property.equals(""))
		return property;
    else return property; 
}

/** Returns the value of the com.gensym.com.emitpackage property.
*	If this property is not set then this will return the string
*   com.gensym.test
*/
public static String getDefaultEmitPackage() {
	String property = System.getProperty("com.gensym.com.emitpackage");

	if (property == null)
		return "com.gensym.tests";
	else return property;
}

/** Returns the value of the com.gensym.com.emitpackage property
* as if it was a relative path, ie. converting .'s to file
* separator characters.<br>
* e.g. if the value of com.gensym.com.emitpackage is com.gensym.tests
* then this function will return com/gensym/tests<br>
* If localFileSeparators is true this will replace / with the local file separator
* character which is \ on NT.
*/
public static String getDefaultRelativeEmitPath(boolean localFileSeparators) {
  String property = getDefaultEmitPackage();	
  return convertPackageNameToRelativePath(property, localFileSeparators);      
}


/** Converts a dot separated package name into a relative path
*/
public static String convertPackageNameToRelativePath(String packageName, 
                                                      boolean localFileSeparators) 
{
  if (localFileSeparators) 
    return multipleReplace(packageName,"./",File.separator); // Just in case
  return multipleReplace(packageName,"." + File.separator,"/");
}

/** Rename a file, using path strings */
public static boolean renameFile(String fromPath, String toPath) {
		File file1, file2;

		file1 = new File(fromPath);
		file2 = new File(toPath);
		return file1.renameTo(file2);
}

private static boolean dirNotWritable(String dir) {	
    File fi = new File(dir);
    return (! (fi.exists() && fi.canWrite()));
}

private static String multipleReplace(String path,String tokens, String newToken) {
    StringTokenizer stok = new StringTokenizer(path,tokens);
    StringBuffer buf = new StringBuffer();
    String token;

    token = stok.nextToken();
    buf.append(token);
    while (stok.hasMoreTokens()) {
      token = stok.nextToken();
	  buf.append(newToken);
	  buf.append(token);
    }
    return buf.toString();		
 }


}
