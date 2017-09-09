/*
 * @(#)ClassSubWriter.java	1.13 98/07/17
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

/**
 *
 * @author Robert Field
 * @author Atul M Dambalkar
 */
public class ClassSubWriter extends AbstractSubWriter {

    ClassSubWriter(SubWriterHolderWriter writer) {
        super(writer);
    }

    @Override
    public ProgramElementDoc[] members(ClassDoc cd) {
        return eligibleMembers(cd.innerClasses());
    }

    @Override
    public void printSummaryLabel(ClassDoc cd) {
        writer.boldText("doclet.Inner_Class_Summary"); 
    }

    @Override
    public void printSummaryAnchor(ClassDoc cd) {
        writer.anchor("inner_class_summary"); 
    }
    
    @Override
    public void printInheritedSummaryAnchor(ClassDoc cd) {
        writer.anchor("inner_classes_inherited_from_class_" + 
                       cd.qualifiedName());
    }   
    
    @Override
    public void printInheritedSummaryLabel(ClassDoc cd) {
        String clslink = writer.getPreQualifiedClassLink(cd);
        writer.bold();
        writer.printText("doclet.Inner_Classes_Inherited_From_Class", clslink);
        writer.boldEnd();
    }

    protected void printSummaryLink(ClassDoc cd, ProgramElementDoc member) {
        writer.bold();
        writer.printClassLink((ClassDoc)member);
        writer.boldEnd();
    }

    protected void printInheritedSummaryLink(ClassDoc cd, 
                                             ProgramElementDoc member) {
        printSummaryLink(cd, member);
    }
  
    protected void printSummaryType(ProgramElementDoc member) {
        ClassDoc cd = (ClassDoc)member;
        //printStaticAndType(cd.isStatic(), null);
        printModifierAndType(cd, null);
    }

    @Override
    protected void printHeader(ClassDoc cd) {
        // N.A.
    }

    @Override
    protected void printBodyHtmlEnd(ClassDoc cd) {
        // N.A.
    }

    protected void printMember(ProgramElementDoc member) {
        // N.A.
    }

    protected void printDeprecatedLink(ProgramElementDoc member) {
        writer.printQualifiedClassLink((ClassDoc)member);
    }

    @Override
    protected void printNavSummaryLink(ClassDoc cd, boolean link) {
        if (link) {
            writer.printHyperLink("", (cd == null)? 
                                         "inner_class_summary":
                                         "inner_classes_inherited_from_class_" +
                                          cd.qualifiedName(),
                                  writer.getText("doclet.navInner"));
        } else {               
            writer.printText("doclet.navInner");
        } 
    }

    @Override
    protected void printNavDetailLink(boolean link) {
    }

    protected void printMemberLink(ProgramElementDoc member) {
    }

    protected void printMembersSummaryLink(ClassDoc cd, ClassDoc icd, 
                                           boolean link) {
        if (link) {
            writer.printHyperLink(cd.name() + ".html",
                                  (cd == icd)? 
                                       "inner_class_summary":
                                       "inner_classes_inherited_from_class_" +
                                        icd.qualifiedName(),
                                 writer.getText("doclet.Inner_Class_Summary"));
        } else {               
            writer.printText("doclet.Inner_Class_Summary");
        } 
    }
}  
    
    
