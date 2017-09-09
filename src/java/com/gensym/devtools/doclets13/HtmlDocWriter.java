/*
 * @(#)HtmlDocWriter.java	1.39 00/02/02
 *
 * Copyright 1997-2000 Sun Microsystems, Inc. All Rights Reserved.
 * 
 * This software is the proprietary information of Sun Microsystems, Inc.  
 * Use is subject to license terms.
 * 
 */

package com.gensym.devtools.doclets13;

import com.sun.javadoc.*;
import java.io.*;
import java.util.*;
import java.lang.*;
import java.text.MessageFormat;


/** 
 * Class for the Html Format Code Generation specific to JavaDoc.
 * This Class contains methods related to the Html Code Generation which 
 * are used by the Sub-Classes in the package com.gensym.devtools.doclets13.standard 
 * and com.gensym.devtools.doclets13.oneone.
 *
 * @since JDK1.2
 * @author Atul M Dambalkar
 * @author Robert Field
 */
public abstract class HtmlDocWriter extends HtmlWriter {
   
  /**
   * All the user given options on the command line.
   */ 
  public static Configuration configuration;

  /**
   * Constructor. Initializes the destination file name through the super
   * class HtmlWriter.
   *
   * @param filename String file name.
   */
  public HtmlDocWriter(String filename) throws IOException {
    super(configuration.destdirname + filename, configuration.docencoding);
    configuration.message.notice("doclet.Generating_0", 
				 configuration.destdirname + filename);
  }

  public HtmlDocWriter(String path, String filename) throws IOException {
    super(configuration.destdirname + path, filename,  
	  configuration.docencoding);
    configuration.message.notice("doclet.Generating_0", 
				 configuration.destdirname + 
				 ((path.length() > 0)? 
				  path + File.separator: "") + filename);
  }

  /**
   * Print Html Hyper Link.
   *
   * @param link String name of the file.
   * @param where Position of the link in the file. Character '#' is not
   * needed.
   * @param label Tag for the link.
   * @param bold  Boolean that sets label to bold.
   */
  public void printHyperLink(String link, String where,
			     String label, boolean bold) {
    print(getHyperLink(link, where, label, bold, ""));
  }

  /**
   * Print Html Hyper Link.
   *
   * @param link String name of the file.
   * @param where Position of the link in the file. Character '#' is not
   * needed.
   * @param label Tag for the link.
   */
  public void printHyperLink(String link, String where, String label) {
    printHyperLink(link, where, label, false);
  }
 
  /**
   * Print Html Hyper Link.
   *
   * @param link       String name of the file.
   * @param where      Position of the link in the file. Character '#' is not
   * needed.
   * @param label      Tag for the link.
   * @param bold       Boolean that sets label to bold.
   * @param stylename  String style of text defined in style sheet.
   */
  public void printHyperLink(String link, String where,
			     String label, boolean bold, 
			     String stylename) {
    print(getHyperLink(link, where, label, bold, stylename));
  }

  /**
   * Return Html Hyper Link string.
   *
   * @param link       String name of the file.
   * @param where      Position of the link in the file. Character '#' is not
   * needed.
   * @param label      Tag for the link.
   * @param bold       Boolean that sets label to bold.
   * @return String    Hyper Link.
   */
  public String getHyperLink(String link, String where, 
			     String label, boolean bold) {
    return getHyperLink(link, where, label, bold, "");
  }

  /**
   * Get Html Hyper Link string.
   *
   * @param link       String name of the file.
   * @param where      Position of the link in the file. Character '#' is not
   * needed.
   * @param label      Tag for the link.
   * @param bold       Boolean that sets label to bold.
   * @param stylename  String style of text defined in style sheet.
   * @return String    Hyper Link.
   */   
  public String getHyperLink(String link, String where, 
			     String label, boolean bold, 
			     String stylename) {
    StringBuffer retlink = new StringBuffer();
    retlink.append("<A HREF=\"");
    retlink.append(link);
    if (where.length() != 0) {
      retlink.append("#");
      retlink.append(where);
    }
    retlink.append("\">");
    if (stylename.length() != 0) {
      retlink.append("<FONT CLASS=\"");
      retlink.append(stylename);
      retlink.append("\">");
    }
    if (bold) {
      retlink.append("<B>");
    }
    retlink.append(label);
    if (bold) {
      retlink.append("</B>");
    }
    if (stylename.length() != 0) {
      retlink.append("</FONT>");
    }
    retlink.append("</A>");
    return retlink.toString();
  }
    
  /**
   * Print link without positioning in the file.
   * 
   * @param link       String name of the file.
   * @param label      Tag for the link.
   */
  public void printHyperLink(String link, String label) {
    print(getHyperLink(link, "", label, false));
  }

  /**
   * Get link string without positioning in the file.
   * 
   * @param link       String name of the file.
   * @param label      Tag for the link.
   * @return Strign    Hyper link.
   */
  public String getHyperLink(String link, String label) {
    return getHyperLink(link, "", label, false);
  }

  /**
   * Print the name of the package, this class is in.
   * 
   * @param cd    ClassDoc.
   */
  public void printPkgName(ClassDoc cd) {
    print(getPkgName(cd));
  }

  /**
   * Get the name of the package, this class is in.
   * 
   * @param cd    ClassDoc.
   */
  public String getPkgName(ClassDoc cd) {
    String pkgName = cd.containingPackage().name();
    if (pkgName.length() > 0) {
      pkgName += ".";
      return pkgName;
    }
    return "";
  }

  /**
   * Print some part of the Html file header.
   *
   * @param title    Title of this HTML document.
   */
  public void printPartialHeader(String title) {
    println("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 " + 
	    "Transitional//EN\"" + 
	    "\"http://www.w3.org/TR/REC-html40/loose.dtd>");
    println("<!--NewPage-->");
    html();
    head();
    print("<!-- Generated by javadoc on ");
    print(today());
    println("-->");
    title();
    println(title);
    titleEnd();
    headEnd();
  }

  /**
   * Print the appropriate spaces to format the class tree in the class page.
   *
   * @param len   Number of spaces.
   */
  public String spaces(int len) {
    String space = "";

    for (int i = 0; i < len; i++) {
      space += " ";
    }
    return space;
  }

  /**
   * Print the closing &lt;/body&gt; and &lt;/html&gt; tags.
   */
  public void printBodyHtmlEnd() {
    println();
    bodyEnd();
    htmlEnd();
  }

  /**
   * Calls {@link #printBodyHtmlEnd()} method.
   */
  public void printFooter() {
    printBodyHtmlEnd();
  }

  /**
   * Print closing &lt;/html&gt; tag.
   */
  public void printFrameFooter() {
    htmlEnd();
  }

  /**
   * Print ten non-breaking spaces("&#38;nbsp;").
   */
  public void printNbsps() {
    print("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");
  }
    
  /**
   * Get the day and date information for today, depending upon user option.
   * 
   * @return String Today.
   * @see java.util.Calender
   * @see java.util.GregorianCalendar 
   * @see java.util.TimeZone
   */
  public String today() {
    if (configuration.nodate) {
      return "TODAY";
    }
    Calendar calendar = new GregorianCalendar(TimeZone.getDefault());
    return calendar.getTime().toString();
  }
}
