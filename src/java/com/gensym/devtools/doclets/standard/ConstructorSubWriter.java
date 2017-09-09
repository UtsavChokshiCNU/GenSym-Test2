/**
 * @(#)ConstructorSubWriter.java	1.11 98/07/17
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
public class ConstructorSubWriter extends ExecutableMemberSubWriter {

    protected boolean foundNonPublicMember = false;

    ConstructorSubWriter(SubWriterHolderWriter writer) {
        super(writer);
    }

    public ProgramElementDoc[] members(ClassDoc cd) {
        ProgramElementDoc[] members = eligibleMembers(cd.constructors());
        checkForNonPublicMembers(members);
        return members;
    }

    public void printSummaryLabel(ClassDoc cd) {
        writer.boldText("doclet.Constructor_Summary"); 
    }

    public void printSummaryAnchor(ClassDoc cd) {
        writer.anchor("constructor_summary");
    }
    
    public void printInheritedSummaryAnchor(ClassDoc cd) {
    }   // no such
    
    public void printInheritedSummaryLabel(ClassDoc cd) {
        // no such
    }

    protected void printSummaryType(ProgramElementDoc member) {
        if (foundNonPublicMember) {
            writer.printTypeSummaryHeader();
            if (member.isProtected()) {
                print("protected ");
            } else if (member.isPrivate()) {
                print("private ");
            } else if (member.isPublic()) {
                writer.space();
            } else {
                writer.printText("doclet.Package_private");
            }
            writer.printTypeSummaryFooter();
	}
    }

    protected void printTags(ProgramElementDoc member) {
        ParamTag[] params = ((ConstructorDoc)member).paramTags();
        ThrowsTag[] thrown = ((ConstructorDoc)member).throwsTags();
        Tag[] sinces = member.tags("since");
        SeeTag[] sees = member.seeTags();
        if (params.length + thrown.length + sees.length + sinces.length > 0) {
            writer.dd();
            writer.dl();
            printParamTags(params);
            printThrowsTags(thrown);
            writer.printSinceTag(member);
            writer.printSeeTags(member);
            writer.dlEnd();
            writer.ddEnd();
        }
    }
                               
    protected void printHeader(ClassDoc cd) {
        writer.anchor("constructor_detail");
        writer.printTableHeadingBackground(writer.
                                       getText("doclet.Constructor_Detail"));
    }

    protected void navSummaryLink(ClassDoc cd) {
         printNavSummaryLink(cd, members(cd).length > 0? true: false);
    } 

    protected void printNavSummaryLink(ClassDoc cd, boolean link) {
        if (link) {
            writer.printHyperLink("", "constructor_summary",
                                  writer.getText("doclet.navConstructor"));
        } else {
            writer.printText("doclet.navConstructor");
        }
    }

    @Override
    protected void printNavDetailLink(boolean link) {
        if (link) {
            writer.printHyperLink("", "constructor_detail",
                                      writer.getText("doclet.navConstructor"));
        } else {
            writer.printText("doclet.navConstructor");
        } 
    }

    protected void checkForNonPublicMembers(ProgramElementDoc[] members) {
        for (int i = 0; i < members.length; i++) {
            if (!foundNonPublicMember) {
                if (!members[i].isPublic()) {
                    foundNonPublicMember = true;
                    break;
                }
            }
        }
    }
}  
    
    
