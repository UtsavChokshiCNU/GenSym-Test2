/*
 * @(#)PackagesFileWriter.java	1.1 98/08/06
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
import java.io.*;
import java.lang.*;
import java.util.*;

/**
 * Generate the "packages.html" file for the backward compatibility.
 *
 * @author Atul M Dambalkar
 */
public class PackagesFileWriter extends HtmlStandardWriter {

    /**
     * Constructor.
     */
    public PackagesFileWriter(String filename) throws IOException {
        super(filename);
    }

    /**
     * Generate the file.
     */
    public static void generate() throws DocletAbortException {
        PackagesFileWriter packgen;
        String filename = "";
        try {
            filename = "packages.html";
            packgen = new PackagesFileWriter(filename);
            packgen.generatePackagesFile();
            packgen.close();
        } catch (IOException exc) {
            Standard.configuration().standardmessage.error(
                "doclet.exception_encountered",
                exc.toString(), filename);
            throw new DocletAbortException();
        }
    }

    /**
     * Generate the packages file.
     */
    protected void generatePackagesFile() {
        printHeader(getText("doclet.Window_Packages_title",
                            Standard.configuration().windowtitle));

        printPackagesFileContents();

        printBodyHtmlEnd();
    }

    /**
     * Print the pacakges file contents.
     */
    protected void printPackagesFileContents() {
        br(); br(); br();
        center(); 
        printText("doclet.Packages_File_line_1"); 
        printText("doclet.Packages_File_line_2");
        br(); printNbsps();
        printHyperLink("index.html", getText("doclet.Frame_Version"));
        br(); printNbsps();
        printHyperLink(Standard.configuration().topFile,
                       getText("doclet.Non_Frame_Version"));
        centerEnd();
    }

}

