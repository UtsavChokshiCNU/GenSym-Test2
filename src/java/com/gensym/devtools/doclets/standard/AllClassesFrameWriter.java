/*
 * @(#)AllClassesFrameWriter.java	1.9 98/08/18
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

import com.sun.javadoc.*;
import com.gensym.devtools.doclets.*;
import java.io.*;
import java.lang.*;
import java.util.*;

/**
 * Generate the file with list of all the classes in this run. This page will be
 * used in the left-hand bottom frame, when "All Classes" link is clicked in 
 * the left-hand top frame. The name of the generated file is 
 * "allclasses-frame.html".
 *
 * @author Atul M Dambalkar
 * @author Doug Kramer
 */
public class AllClassesFrameWriter extends HtmlStandardWriter {

    /**
     * Index of all the classes.
     */
    protected IndexBuilder indexbuilder;

    /**
     * Construct AllClassesFrameWriter object. Also initilises the indexbuilder
     * variable in this class.
     */
    public AllClassesFrameWriter(String filename, IndexBuilder indexbuilder)
                              throws IOException, DocletAbortException {
        super(filename);
        this.indexbuilder = indexbuilder;
    }

    /**
     * Create AllClassesFrameWriter object. Then use it to generate the 
     * "allclasses-frame.html" file. Generate the file in the current or the
     * destination directory.
     *
     * @param indexbuilder IndexBuilder object for all classes index.
     */ 
    public static void generate(IndexBuilder indexbuilder)
                         throws DocletAbortException {
        AllClassesFrameWriter allclassgen;
        String filename = "allclasses-frame.html";
        try {
            allclassgen = new AllClassesFrameWriter(filename, indexbuilder);
            allclassgen.generateAllClassesFile();
            allclassgen.close();
        } catch (IOException exc) {
            Standard.configuration().standardmessage.
                     error("doclet.exception_encountered",
                           exc.toString(), filename);
            throw new DocletAbortException();
        }
    }

    /**
     * Print all the classes in table format in the file.
     */
    protected void generateAllClassesFile() throws IOException {
        String label = getText("doclet.All_Classes");

        printHeader(label);

        printAllClassesTableHeader();
        printAllClasses();
        printAllClassesTableFooter();

        printBodyHtmlEnd();
    }

    /**
     * Use the sorted index of all the classes and print all the classes.
     */
    protected void printAllClasses() {
        for (int i = 0; i < indexbuilder.elements().length; i++) {
            Character unicode = (Character)((indexbuilder.elements())[i]);
            generateContents(indexbuilder.getMemberList(unicode));
        }
    }

    /**
     * Given a list of classes, generate links for each class or interface.
     * If the class lind is interface, print it in the italics font. Also all 
     * links should target the right-hand frame. If clicked on any class name
     * in this page, appropriate class page should get opened in the right-hand
     * frame.
     *
     * @param classlist Sorted list of classes.
     */
    protected void generateContents(List classlist) {
        for (int i = 0; i < classlist.size(); i++) {
            ClassDoc cd = (ClassDoc)(classlist.get(i));
            if (!isCoreClass(cd)) {
                continue;
            }
            String label = italicsClassName(cd, false);
            printTargetHyperLink(pathToClass(cd), "classFrame", label);
            br();
        }
    }

    /**
     * Print the heading "All Classes" and also print Html table tag.
     */
    protected void printAllClassesTableHeader() {
        fontSizeStyle("+1", "FrameHeadingFont");
        boldText("doclet.All_Classes"); 
        fontEnd();
        br();
        table();
        tr();
        tdNowrap();
        fontStyle("FrameItemFont");
    }

    /**
     * Print Html closing table tag.
     */
    protected void printAllClassesTableFooter() {
        fontEnd();
        tdEnd();
        trEnd();
        tableEnd();
    }
}



