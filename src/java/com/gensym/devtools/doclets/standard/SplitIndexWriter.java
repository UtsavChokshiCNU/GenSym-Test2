/*
 * @(#)SplitIndexWriter.java	1.11 98/08/18
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
 * Generate Separate Index Files for all the member names with Indexing in
 * Unicode Order. This will create "index-files" directory in the current or
 * destination directory and will generate separate file for each unicode index.
 *
 * @see java.lang.Character
 * @author Atul M Dambalkar
 */
public class SplitIndexWriter extends AbstractIndexWriter {

    /**
     * Previous unicode character index in the built index.
     */
    protected int prev;

    /**
     * Next unicode character in the built index.
     */
    protected int next;

    /**
     * Construct the SplitIndexWriter. Uses path to this file and relative path
     * from this file.
     * 
     * @param path       Path to the file which is getting generated.
     * @param filename   Name of the file which is getting genrated.
     * @param relpath    Relative path from this file to the current directory.
     * @param indexbuilder Unicode based Index from {@link IndexBuilder}
     */
    public SplitIndexWriter(String path, String filename, 
                            String relpath, IndexBuilder indexbuilder,
                            int prev, int next) throws IOException {
        super(path, filename, relpath, indexbuilder);
        this.prev = prev;
        this.next = next;
    }

    /**
     * Generate separate index files, for each Unicode character, listing all
     * the members starting with the particular unicode character.
     * 
     * @param indexbuilder IndexBuilder built by {@link IndexBuilder}
     */
    public static void generate(IndexBuilder indexbuilder) 
                                throws DocletAbortException {
        SplitIndexWriter indexgen;
        String filename = "";
        String path = DirectoryManager.getPath("index-files");
        String relpath = DirectoryManager.getRelativePath("index-files");
        try {
            for (int i = 0; i < indexbuilder.elements().length; i++) {
                int j = i + 1;
                int prev = (j == 1)? -1: i;
                int next = (j == indexbuilder.elements().length)? -1: j + 1;
                filename = "index-" + j +".html";
                indexgen = new SplitIndexWriter(path, filename, relpath,
                                                indexbuilder, prev, next);
                indexgen.generateIndexFile((Character)indexbuilder.
                                                                 elements()[i]);
                indexgen.close();
            }
        } catch (IOException exc) {
 Standard.configuration().standardmessage.error("doclet.exception_encountered",
                                                 exc.toString(), filename);
            throw new DocletAbortException();
        }
    }

    /**
     * Generate the contents of each index file, with Header, Footer, 
     * Member Field, Method and Constructor Description.
     *
     * @param unicode Unicode character referring to the character for the
     * index.
     */
    protected void generateIndexFile(Character unicode) throws IOException {
        printHeader(getText("doclet.Window_Split_Index",
                            Standard.configuration().windowtitle, 
                            unicode.toString()));
       
        navLinks(true);
        printLinksForIndexes();
        
        hr();
        
        generateContents(unicode, indexbuilder.getMemberList(unicode));

        navLinks(false);
        printLinksForIndexes();
        
        printBottom(); 
        printBodyHtmlEnd();
    }

    /**
     * Print Links for all the Index Files per unicode character.
     */
    protected void printLinksForIndexes() {
        for (int i = 0; i < indexbuilder.elements().length; i++) {
            int j = i + 1;
            printHyperLink("index-" + j + ".html",
                           indexbuilder.elements()[i].toString());
            print(' ');
        }
    }
  
    /**
     * Print the previous unicode character index link.
     */
    @Override
    protected void navLinkPrevious() {
        if (prev == -1) {
            printText("doclet.Prev_Letter");
        } else {
            printHyperLink("index-" + prev + ".html", "",
                            getText("doclet.Prev_Letter"), true);
        }
    } 

    /**
     * Print the next unicode character index link.
     */
    @Override
    protected void navLinkNext() {
        if (next == -1) {
            printText("doclet.Next_Letter");
        } else {
            printHyperLink("index-" + next + ".html","",
                            getText("doclet.Next_Letter"), true);
        }
    } 
}
