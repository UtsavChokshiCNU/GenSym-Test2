/*
 * @(#)AbstractPackageIndexWriter.java	1.15 98/08/18
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

package com.gensym.devtools.doclets.standard;

import com.gensym.devtools.doclets.*;
import com.sun.javadoc.*;
import java.io.*;
import java.lang.*;
import java.util.*;

/**
 * Abstract class to generate the package index. The package index needs to be
 * generated in Frame and Non-Frame format. This will be sub-classed by to 
 * generate frame-index as well as overview-index.
 *
 * @author Atul M Dambalkar 
 */
public abstract class AbstractPackageIndexWriter extends HtmlStandardWriter {

    /**
     * Array of Packages to be documented.
     */
    protected PackageDoc[] packages;

    /**
     * Constructor. Also initialises the packages variable.
     *
     * @param filename Name of the package index file to be generated.
     */
    public AbstractPackageIndexWriter(String filename) throws IOException {
        super(filename);
        packages = Standard.configuration().packages;
    }

    protected abstract void printNavigationBarHeader();
 
    protected abstract void printNavigationBarFooter();

    protected abstract void printOverviewHeader();
 
    protected abstract void printIndexHeader(String text);
 
    protected abstract void printIndexRow(PackageDoc pkg);
 
    protected abstract void printIndexFooter();
 
    /**
     * Generate the contants in the package index file. Call appropriate
     * methods from the sub-class in order to generate Frame or Non
     * Frame format.
     */ 
    protected void generatePackageIndexFile() throws IOException {
        printHeader(getText("doclet.Window_Overview", 
                             Standard.configuration().windowtitle)); 
        printNavigationBarHeader();
        printOverviewHeader();

        generateIndex();

        printOverview();

        printNavigationBarFooter();
        printBodyHtmlEnd();
    }
    
    /**
     * Default to no overview, overwrite to add overview.
     */
    protected void printOverview() throws IOException {
    }

    /**
     * Generate the frame or non-frame package index.
     */
    protected void generateIndex() {
        printIndexContents(packages, "doclet.Package_Summary");
    }
 
    /**
     * Generate code for package index contents. Call appropriate methods from
     * the sub-classes.
     * 
     * @param pacakges Array of packages to be documented.
     * @param text     String which will be used as the heading.
     */
    protected void printIndexContents(PackageDoc[] packages, String text) {
        if (packages.length > 0) {
            Arrays.sort(packages);
            printIndexHeader(text);
            printAllClassesPackagesLink();
            for(int i = 0; i < packages.length; i++) {
                PackageDoc packagedoc = packages[i];
                printIndexRow(packagedoc);
            }
            printIndexFooter();
        }
    }

    /**
     * Print the doctitle, if it is specified on the command line. 
     */
    protected void printConfigurationTitle() {
        if (Standard.configuration().doctitle.length() > 0) {
            center();
            h2();
            print(Standard.configuration().doctitle);
            h2End();
            centerEnd();
        }
    }

    /**
     * Highlight "Overview" in the bold format, in the navigation bar as this 
     * is the overview page.
     */
    @Override
    protected void navLinkContents() {
        navCellRevStart();
        fontStyle("NavBarFont1Rev");
        boldText("doclet.Overview");
        fontEnd();
        navCellEnd();
    }

    /**
     * Do nothing. This will be overridden in PackageIndexFrameWriter.
     */
    protected void printAllClassesPackagesLink() {
    }
}



