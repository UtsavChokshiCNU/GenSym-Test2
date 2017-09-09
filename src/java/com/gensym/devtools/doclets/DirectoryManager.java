/*
 * @(#)DirectoryManager.java	1.11 98/09/22
 *
 * Copyright 1998 by Sun Microsystems, Inc.,
 * 901 San Antonio Road, Palo Alto, California, 94303, U.S.A.
 * All rights reserved.
 *
 * This software is the confidential and proprietary information
 * of Sun Microsystems, Inc. ("Confidential Information").  You
 * shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Sun.
 */

package com.gensym.devtools.doclets;

import com.sun.javadoc.*;
import java.io.*;
import java.lang.*;


/** 
 * Handle the directory creations and the path string generations.
 *
 * @since JDK1.2
 * @author Atul M Dambalkar
 */
public class DirectoryManager {
  
    /**
     * The file separator string, "/", used in the formation of the URL path.
     */
    public static final String urlfileseparator = "/";

    /**
     * The actual platform dependent file separator.
     * 
     * @see java.io.File.separator
     */
    public static final String fileseparator = File.separator;

    /**
     * Given a PackageDoc, return its URL path string.
     * 
     * @param pd PackageDoc
     * @see #getPath(String)
     */
    public static String createPathString(PackageDoc pd) {
        if (pd == null) {
            return "";
        }
        return getPath(pd.name());
    }

    /**
     * Given a ClassDoc, return its URL path string.
     * 
     * @param cd ClassDoc
     * @see #getPath(String)
     */
    public static String createPathString(ClassDoc cd) {
        if (cd == null) {
            return "";
        }
        PackageDoc pd = cd.containingPackage();
        return (pd == null)? "": getPath(pd.name());
    }

    /**
     * Given a PackageDoc, return the directory name. If name of the package
     * is "java.lang" then path will be "java/lang". If name of the package is
     * "no_interior_dot" then path will be just "no_interior_dot". The file 
     * separator used is a platform dependent file separator.
     *
     * @param pd PackageDoc 
     * @return String The directory path for the package.
     */
    public static String getDirectoryPath(PackageDoc pd) {
        if (pd == null) {
            return "";
        }
        String name = pd.name();
        StringBuffer pathstr = new StringBuffer();
        for (int i = 0; i < name.length(); i++) {
            char ch = name.charAt(i);
            if (ch == '.') {
                pathstr.append(fileseparator);
            } else {
                pathstr.append(ch);
            }
        }
        return pathstr.toString();
    }

    /**
     * Given any string, return the URL path string. For example, if the string
     * is "com.sun.javadoc" then the URL path string will be "com/sun/javadoc"
     * The URL path separator "/"(which is not platform specific) is used to 
     * separate the directory names.
     *
     * @param name String.
     * @return String URL path string.
     */
    public static String getPath(String name) {
        if (name == null || name.length() == 0) {
            return "";
        }
        StringBuffer pathstr = new StringBuffer();
        for (int i = 0; i < name.length(); i++) {
            char ch = name.charAt(i);
            if (ch == '.') {
                pathstr.append(urlfileseparator);
            } else {
                pathstr.append(ch);
            }
        }
        return pathstr.toString();
    }

    /**
     * Given two strings/(package names) return the relative path from one 
     * string to another. For example, if the parameter string "from" is 
     * "java.lang" and parameter string "to" is "java.applet" the method will 
     * return string "../../java/applet". The relative path returned is URL 
     * specific, and hence it uses "/" as file separator.
     * 
     * @param from "from" this directory(package) location.
     * @param to "to" this directory(package) location.
     * @return String relative path from "from" to "to".
     * @see #getRelativePath(String)
     * @see #getPath(String)
     */
    public static String getRelativePath(String from, String to) {
        StringBuffer pathstr = new StringBuffer();
        pathstr.append(getRelativePath(from));
        pathstr.append(getPath(to));
        pathstr.append(urlfileseparator);
        return pathstr.toString();
    }

    /**
     * Given string(package name), return relative path string. For example, 
     * if the string "from" is "java.lang" the method will return "../../" 
     * relative path, till the directory, in which is output is getting 
     * generated. The returned string is URL specific. String from is nothing 
     * but the directory location 
     *
     * @param from "from" this directory(package) location.
     * @return String relative path from "from".
     * @see #getRelativePath(String, String)
     */
    public static String getRelativePath(String from) {
        if (from == null || from.length() == 0) {
            return "";
        }
        StringBuffer pathstr = new StringBuffer();
        for (int i = 0; i < from.length(); i++) {
            char ch = from.charAt(i);
            if (ch == '.') {
                pathstr.append(".." + urlfileseparator);
            }     
        }
        pathstr.append(".." + urlfileseparator);
        return pathstr.toString();
    }

    /**
     * Given a URL path string, this will return the reverse path. For 
     * example, if the URL path string is "java/lang" the method will return 
     * URL specific string "../".
     */
    public static String getBackPath(String path) {
        if (path == null || path.length() == 0) {
            return "";
        }
        StringBuffer backpath = new StringBuffer();
        for (int i = 0; i < path.length(); i++) {
            char ch = path.charAt(i);
            if (ch == '/') {
                backpath.append("..");
                backpath.append(urlfileseparator);
            }       // there is always a trailing fileseparator
        }
        return backpath.toString();
    }

    /**
     * Given a path string create all the directories in the path. For example,
     * if the path string is "java/applet", the method will create directory 
     * "java" and then "java/applet" if they don't exist. The file separator 
     * string "/" is platform dependent system property.
     * 
     * @param path Directory path string.
     */
    public static void createDirectory(String path) {
        if (path == null || path.length() == 0) {
            return;
        }
        File dir = new File(path);
        try {
            if (dir.exists()) {
                return;
            } else {
                if (dir.mkdirs()) {
                    return;
                } else {
                    HtmlDocWriter.configuration.message.error(
                                  "doclet.Unable_to_create_directory_0", path);
                    throw new DocletAbortException();
                }
            }
        } catch (SecurityException exc) {
            exc.printStackTrace();
            System.exit(1);
        } catch (DocletAbortException exc) {
            exc.printStackTrace();
            System.exit(1);
        } 
    }

    /**
     * Given a package name and a file name, return the full path to that file.
     * For example, if PackageDoc passed is for "java.lang" and the filename 
     * passed is "package-summary.html", then the string returned is
     * "java/lang/package-summary.html".
     * 
     * @param pd         PackageDoc.
     * @param filename   File name to be appended to the path of the package.
     */
    public static String getPathToPackage(PackageDoc pd, String filename) {
        StringBuffer buf = new StringBuffer();  
        String pathstr = createPathString(pd);
        if (pathstr.length() > 0) {
            buf.append(pathstr);
            buf.append("/");
        }
        buf.append(filename);
        return buf.toString();
    }

    /**
     * Given a class name return the full path to the class file.
     * For example, if ClassDoc passed is for "java.lang.Object" then the 
     * string returned is "java/lang/Object.html".
     * 
     * @param cd   ClassDoc.
     */
    public static String getPathToClass(ClassDoc cd) {
        return getPathToPackage(cd.containingPackage(), cd.name() + ".html");
    }

}
