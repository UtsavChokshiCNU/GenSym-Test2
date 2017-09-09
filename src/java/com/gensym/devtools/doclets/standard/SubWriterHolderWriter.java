/*
 * @(#)SubWriterHolderWriter.java	1.8 98/02/24
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
 * This abstract class exists to provide functionality needed in the
 * the formatting of member information.  Since AbstractSubWriter and its
 * subclasses control this, they would be the logical place to put this.
 * However, because each member type has its own subclass, subclassing
 * can not be used effectively to change formatting.  The concrete
 * class subclass of this class can be subclassed to change formatting.
 *
 * @see AbstractSubWriter
 * @see ClassWriter
 *
 * @author Robert Field
 * @author Atul M Dambalkar
 */
public abstract class SubWriterHolderWriter extends HtmlStandardWriter {
    
    public SubWriterHolderWriter(String filename) throws IOException {
        super(filename);
    }


    public SubWriterHolderWriter(String path, String filename, String relpath) 
                                 throws IOException, DocletAbortException {
        super(path, filename, relpath);
    }

    public void printTypeSummaryHeader() {
        tdIndex();
        font("-1");
        code();
    }

    public void printTypeSummaryFooter() {
        codeEnd();
        fontEnd();
        tdEnd();
    }

    public void printSummaryHeader(AbstractSubWriter mw, ClassDoc cd) {
        mw.printSummaryAnchor(cd);
        tableIndexSummary();
        tableHeaderStart("#CCCCFF");
        mw.printSummaryLabel(cd);
        tableHeaderEnd();
    }

    public void printTableHeadingBackground(String str) {
        tableIndexDetail();
        tableHeaderStart("#CCCCFF", 1);
        bold(str);
        tableHeaderEnd();
        tableEnd();
    }
 
    public void printInheritedSummaryHeader(AbstractSubWriter mw, ClassDoc cd) {
        mw.printInheritedSummaryAnchor(cd);
        tableIndexSummary();
        tableInheritedHeaderStart("#EEEEFF");
        mw.printInheritedSummaryLabel(cd);
        tableInheritedHeaderEnd();
        trBgcolorStyle("white", "TableRowColor");
        summaryRow(0);
        code();
    }

    public void printSummaryFooter(AbstractSubWriter mw, ClassDoc cd) {
        tableEnd();
        space();
    }

    public void printInheritedSummaryFooter(AbstractSubWriter mw, ClassDoc cd) {
        codeEnd();
        summaryRowEnd();
        trEnd(); 
        tableEnd();
        space();
    }

    protected void printCommentDef(Doc member) {
        printNbsps();
        printIndexComment(member); 
    }

    protected void printIndexComment(Doc member) {
        Tag[] deprs = member.tags("deprecated");
        boolean deprecated = false;
        if (deprs.length > 0) {
            boldText("doclet.Deprecated"); space();
            printInlineDeprecatedComment(deprs[0]);
            return;
        } else {
            ClassDoc cd = ((ProgramElementDoc)member).containingClass();
            if (cd != null && cd.tags("deprecated").length > 0) {
                boldText("doclet.Deprecated"); space();
            } 
        }
        printSummaryComment(member);
    }

    public void printSummaryMember(AbstractSubWriter mw, ClassDoc cd, 
                                   ProgramElementDoc member) {
        trBgcolorStyle("white", "TableRowColor");
        mw.printSummaryType(member);
        summaryRow(0);
        code();
        mw.printSummaryLink(cd, member);
        codeEnd();
        println(); br();
        printCommentDef(member);
        summaryRowEnd();
        trEnd(); 
    }

    public void printInheritedSummaryMember(AbstractSubWriter mw, ClassDoc cd, 
                                            ProgramElementDoc member) {
        mw.printInheritedSummaryLink(cd, member);
    }

    public void printMemberHeader() {
        hr();
    }

    public void printMemberFooter() {
    }
}




