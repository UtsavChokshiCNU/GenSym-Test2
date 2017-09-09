/*
 * @(#)PackageIndexFrameWriter.java	1.12 98/08/18
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
 * Generate the package index for the left-hand frame in the generated output.
 * A click on the package name in this frame will update the page in the bottom
 * left hand frame with the listing of contents of the clicked package.
 *
 * @author Atul M Dambalkar 
 */
public class PackageIndexFrameWriter extends AbstractPackageIndexWriter {

    /**
     * Construct the PackageIndexFrameWriter object. 
     *
     * @param filename Name of the package index file to be generated.
     */ 
    public PackageIndexFrameWriter(String filename) throws IOException {
        super(filename);
    }

    /**
     * Generate the package index file named "overview-frame.html".
     */
    public static void generate() throws DocletAbortException {
        PackageIndexFrameWriter packgen;
        String filename = "overview-frame.html";
        try {
            packgen = new PackageIndexFrameWriter(filename);
            packgen.generatePackageIndexFile();
            packgen.close();
        } catch (IOException exc) {
 Standard.configuration().standardmessage.error("doclet.exception_encountered", 
                                                 exc.toString(), filename);
            throw new DocletAbortException();
        }
    }

    /**
     * Print each package name on separate rows.
     *
     * @param pd PackageDoc 
     */
    @Override
    protected void printIndexRow(PackageDoc pd) {
        fontStyle("FrameItemFont");
        printTargetHyperLink(pathString(pd, "package-frame.html"), 
                             "packageFrame", pd.name());
        fontEnd();
        br();
    }

    /**
     * Print the "-header" in bold format, at top of the page. There is 
     * actually no navigation bar for this page.
     */
    @Override
    protected void printNavigationBarHeader() {
        if (Standard.configuration().header != null) {
            printTableHeader();
            fontSizeStyle("+1", "FrameTitleFont");
            bold(Standard.configuration().header);
            fontEnd();
            printTableFooter();
        }
    }

    /**
     * Do nothing as there is no overview information in this page.
     */
    @Override
    protected void printOverviewHeader() {
    }

    /**
     * Print Html "table" tag for the package index format.
     * 
     * @param text Text string will not be used in this method.
     */
    @Override
    protected void printIndexHeader(String text) {
        printTableHeader();
    }

    /**
     * Print Html closing "table" tag at the end of the package index.
     */   
    @Override
    protected void printIndexFooter() {
        printTableFooter();
    }

    /**
     * Print "All Classes" link at the top of the left-hand frame page.
     */
    @Override
    protected void printAllClassesPackagesLink() {
        fontStyle("FrameItemFont");
        printTargetHyperLink("allclasses-frame.html", "packageFrame", 
                              getText("doclet.All_Classes"));
        fontEnd();
        p();
        fontSizeStyle("+1", "FrameHeadingFont");
        printText("doclet.Packages");
        fontEnd();
        br();
    }

    /**
     * Just print some space, since there is no navigation bar for this page.
     */
    @Override
    protected void printNavigationBarFooter() {
        p();
        space();
    }

    /**
     * Print Html closing tags for the table for package index.
     */
    protected void printTableFooter() {
        tdEnd();
        trEnd();
        tableEnd();
    }

    /**
     * Print Html tags for the table for package index.
     */
    protected void printTableHeader() {
        table();
        tr();
        tdNowrap();
    }
}



