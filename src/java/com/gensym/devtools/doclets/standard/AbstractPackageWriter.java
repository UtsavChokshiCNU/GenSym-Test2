/*
 * @(#)AbstractPackageWriter.java	1.11 98/08/18
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
 * Abstract class to generate file for each package contents. Sub-classed to
 * generate specific formats Frame and Non-Frame Output by 
 * {@link PackageIndexFrameWriter} and {@link PackageIndexFrameWriter} 
 * respectively.
 *
 * @author Atul M Dambalkar
 */
public abstract class AbstractPackageWriter extends HtmlStandardWriter {

    /**
     * The package under consideration.
     */
    PackageDoc packagedoc;

    /**
     * Create appropriate directory for the package and also initilise the 
     * relative path from this generated file to the current or
     * the destination directory.
     *
     * @param path Directories in this path will be created if they are not 
     * already there.
     * @param filename Name of the package summary file to be generated.
     * @param packagedoc PackageDoc under consideration.
     */
    public AbstractPackageWriter(String path, String filename, 
                                 PackageDoc packagedoc) 
                                 throws IOException, DocletAbortException {
        super(path, filename,
              DirectoryManager.getRelativePath(packagedoc.name()));
        this.packagedoc = packagedoc;
    }

    protected abstract void generateClassListing();

    protected abstract void printPackageDescription() throws IOException;

    protected abstract void printPackageHeader(String head);

    protected abstract void printPackageFooter();

    /**
     * Generate Individual Package File with Class/Interface/Exceptions and
     * Error Listing with the appropriate links. Calls the methods from the
     * sub-classes to generate the file contents.
     */
    protected void generatePackageFile() throws IOException {
        String pkgName = packagedoc.toString();
        String heading = getText("doclet.Window_Package", 
                                  Standard.configuration().windowtitle,
            		          pkgName);
        printHeader(heading);
        printPackageHeader(pkgName);

        generateClassListing();
        printPackageDescription();

        printPackageFooter();
        printBodyHtmlEnd();
    }
   
    /**
     * Highlight "Package" in the navigation bar, as this is the package page.
     */
    @Override
    protected void navLinkPackage() {
        navCellRevStart();
        fontStyle("NavBarFont1Rev");
        boldText("doclet.Package");
        fontEnd();
        navCellEnd();
    }
}



