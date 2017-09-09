/*
 * @(#)FieldSubWriter.java	1.15 98/07/17
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
public class FieldSubWriter extends AbstractSubWriter {

    FieldSubWriter(SubWriterHolderWriter writer) {
        super(writer);
    }

    public ProgramElementDoc[] members(ClassDoc cd) {
        return eligibleMembers(cd.fields());
    }

    public void printSummaryLabel(ClassDoc cd) {
        writer.boldText("doclet.Field_Summary"); 
    }

    public void printSummaryAnchor(ClassDoc cd) {
        writer.anchor("field_summary");
    }

    public void printInheritedSummaryAnchor(ClassDoc cd) {
        writer.anchor("fields_inherited_from_class_" + cd.qualifiedName());
    }

    public void printInheritedSummaryLabel(ClassDoc cd) {
        String classlink = writer.getPreQualifiedClassLink(cd);
        writer.bold();
        writer.printText("doclet.Fields_Inherited_From_Class", classlink);
        writer.boldEnd();
    }

    void printSignature(MemberDoc member) {
        FieldDoc field = (FieldDoc)member;
	writer.pre();
        printModifiers(field);
        printTypeLink(field.type());
        print(' ');
        bold(field.name());
	writer.preEnd();
    }

    protected void printSummaryLink(ClassDoc cd, ProgramElementDoc member) {
        String name = member.name();
        ClassDoc mcd = member.containingClass();
        writer.bold();
        if (mcd != cd) {
            writer.print(mcd.name() + ".");
        }
        writer.printClassLink(mcd, name, name, false);
        writer.boldEnd();
    }
  
    protected void printInheritedSummaryLink(ClassDoc cd, 
                                             ProgramElementDoc member) {
        String name = member.name();
        writer.printClassLink(cd, name, name, false);
    }

    protected void printSummaryType(ProgramElementDoc member) {
        FieldDoc field = (FieldDoc)member;
        printModifierAndType(field, field.type());
    }

    protected void printHeader(ClassDoc cd) {
        writer.anchor("field_detail");
        writer.printTableHeadingBackground(writer.
                                              getText("doclet.Field_Detail"));
    }

    protected void printBodyHtmlEnd(ClassDoc cd) {
    }

    protected void printMember(ProgramElementDoc member) {
        FieldDoc field = (FieldDoc)member;
        writer.anchor(field.name());
        printHead(field);
        printSignature(field);
        printFullComment(field);
    }

    protected void printDeprecatedLink(ProgramElementDoc member) {
        writer.printClassLink(member.containingClass(), member.name(), 
                              ((FieldDoc)member).qualifiedName());
    }

    protected void printNavSummaryLink(ClassDoc cd, boolean link) {
        if (link) {
            writer.printHyperLink("", (cd == null)?
                                          "field_summary":
                                          "fields_inherited_from_class_" +
                                           cd.qualifiedName(),
                                  writer.getText("doclet.navField"));
        } else {               
            writer.printText("doclet.navField");
        }
    }

    @Override
    protected void printNavDetailLink(boolean link) {
        if (link) {
            writer.printHyperLink("", "field_detail",
                                  writer.getText("doclet.navField"));
        } else {
            writer.printText("doclet.navField");
        } 
    }
}  
    
    
