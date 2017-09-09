/*
 * @(#)PackageListWriter.java	1.18 98/06/23
 *
 * Copyright 1997, 1998 by Sun Microsystems, Inc.,
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
 * Write out the package index.
 *
 * @see com.sun.javadoc.PackageDoc
 * @see com.gensym.devtools.doclets.HtmlDocWriter
 * @author Atul M Dambalkar 
 */
public class PackageListWriter extends HtmlStandardWriter {

    /**
     * Constructor.
     */
    public PackageListWriter(String filename) throws IOException {
        super(filename);
    }

    /**
     * Generate the package index.
     *
     * @param root the root of the doc tree.
     */
    public static void generate(RootDoc root) throws DocletAbortException {
        PackageListWriter packgen;
        String filename = "package-list";
        try {
            packgen = new PackageListWriter(filename);
            packgen.generatePackageListFile(root);
            packgen.close();
        } catch (IOException exc) {
 Standard.configuration().standardmessage.error("doclet.exception_encountered", 
                                                 exc.toString(), filename);
            throw new DocletAbortException();
        }
    }

    protected void generatePackageListFile(RootDoc root) {
        PackageDoc[] packages = Standard.configuration().packages;
        for (int i = 0; i < packages.length; i++) {
            println(packages[i].name());
        } 
    }
}



