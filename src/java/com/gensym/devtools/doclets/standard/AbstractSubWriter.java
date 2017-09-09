/*
 * @(#)AbstractSubWriter.java	1.20 98/07/30
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
import java.util.*;
import java.lang.reflect.Modifier;

/**
 *
 * @author Robert Field
 * @author Atul M Dambalkar
 */
public abstract class AbstractSubWriter {

    protected final SubWriterHolderWriter writer;

    AbstractSubWriter(SubWriterHolderWriter writer) {
        this.writer = writer;
    }

    /*** abstracts ***/

    public abstract ProgramElementDoc[] members(ClassDoc cd);

    public abstract void printSummaryLabel(ClassDoc cd);

    public abstract void printInheritedSummaryLabel(ClassDoc cd);

    public abstract void printSummaryAnchor(ClassDoc cd);

    public abstract void printInheritedSummaryAnchor(ClassDoc cd);

    protected abstract void printSummaryType(ProgramElementDoc member);

    protected abstract void printSummaryLink(ClassDoc cd, 
                                             ProgramElementDoc member);

    protected abstract void printInheritedSummaryLink(ClassDoc cd, 
                                                      ProgramElementDoc member);

    protected abstract void printHeader(ClassDoc cd);

    protected abstract void printBodyHtmlEnd(ClassDoc cd);

    protected abstract void printMember(ProgramElementDoc elem);

    protected abstract void printDeprecatedLink(ProgramElementDoc member);

    protected abstract void printNavSummaryLink(ClassDoc cd, boolean link);

    protected abstract void printNavDetailLink(boolean link);

    /***  ***/

    protected void print(String str) {
        writer.print(str);
        writer.displayLength += str.length();
    }

    protected void print(char ch) {
        writer.print(ch);
        writer.displayLength++;
    }

    protected void bold(String str) {
        writer.bold(str);
        writer.displayLength += str.length();
    }

    protected void printTypeLinkNoDimension(Type type) {
        ClassDoc cd = type.asClassDoc();
	if (cd == null) {
	    print(type.typeName()); 
	} else {
	    writer.printClassLink(cd);
	}
    }

    protected void printTypeLink(Type type) {
        printTypeLinkNoDimension(type);
        print(type.dimension());
    }

    /**
     * Return a string describing the access modifier flags.
     * Don't include native or synchronized.
     *
     * The modifier names are returned in canonical order, as
     * specified by <em>The Java Language Specification</em>.
     */
    protected String modifierString(MemberDoc member) {
        int ms = member.modifierSpecifier();
        int no = Modifier.NATIVE | Modifier.SYNCHRONIZED;
	return Modifier.toString(ms & ~no);
    }

    protected String typeString(MemberDoc member) {
        String type = "";
        if (member instanceof MethodDoc) {
            type = ((MethodDoc)member).returnType().toString();
        } else if (member instanceof FieldDoc) {
            type = ((FieldDoc)member).type().toString();
        }
        return type;
    }
 
    protected void printModifiers(MemberDoc member) {
        String mod;
        mod = modifierString(member);
        if(mod.length() > 0) {
            print(mod);
            print(' ');
        }
    }

    protected void printTypedName(Type type, String name) {
        if (type != null) {
            printTypeLink(type);
        }
        if(name.length() > 0) {
            writer.space();
            writer.print(name);
        }
    }

    protected String makeSpace(int len) {
        if (len <= 0) {
            return "";
        }
        StringBuffer sb = new StringBuffer(len);
        for(int i = 0; i < len; i++) {
            sb.append(' ');
	}
        return sb.toString();
    }

    /**
     * Print 'static' if static and type link.
     */ 
    protected void printStaticAndType(boolean isStatic, Type type) {
        writer.printTypeSummaryHeader();
        if (isStatic) {
            print("static"); 
        }
        writer.space();
        if (type != null) {
            printTypeLink(type); 
        }
        writer.printTypeSummaryFooter();
    }

    protected void printModifierAndType(ProgramElementDoc member, Type type) {
        writer.printTypeSummaryHeader();
        printModifier(member);
        if (type == null) {
	    if (member.isOrdinaryClass()) {
                print("class");
            } else {
	        print("interface");
            }
        } else {
            printTypeLink(type); 
        }
        writer.printTypeSummaryFooter();
    }

    protected void printModifier(ProgramElementDoc member) {
        if (member.isProtected()) {
            print("protected ");
        } else if (member.isPrivate()) {
            print("private ");
        } else if (!member.isPublic()) { // Package private
            writer.printText("doclet.Package_private");
            print(" ");
        }
        if (member.isMethod() && ((MethodDoc)member).isAbstract()) {
            print("abstract ");
        }
        if (member.isStatic()) {
            print("static");
        }
        writer.space();
    }

    protected void printComment(ProgramElementDoc member) {
        if (member.inlineTags().length > 0) {
            writer.dd();
            writer.printInlineComment(member);
        } 
    }

    protected void printMemberCommentsFromInterfaces(ProgramElementDoc member) {
        // N. A. for all except MethodDoc
    }

    protected void printTags(ProgramElementDoc member) {
        Tag[] since = member.tags("since");
        if (member.seeTags().length + since.length > 0) {
            writer.dd();
            writer.dl();
            writer.printSeeTags(member);
            writer.printSinceTag(member);
            writer.dlEnd();
            writer.ddEnd();
        }
    }

    protected String name(ProgramElementDoc member) {
        return member.name();
    }

    protected void printDeprecated(ProgramElementDoc member) {
        Tag[] deprs = member.tags("deprecated");
        if (deprs.length > 0) {
	    writer.dd();
            writer.boldText("doclet.Deprecated");
            writer.space();
            writer.printInlineDeprecatedComment(deprs[0]);
        } else {
            printDeprecatedClassComment(member);
        }
    }

    protected void printDeprecatedClassComment(ProgramElementDoc member) {
        Tag[] deprs = member.containingClass().tags("deprecated");
        if (deprs.length > 0) {
            writer.dd();
            writer.boldText("doclet.Deprecated");
            writer.space();
        }
    }  
  
    protected void printHead(MemberDoc member) {
        writer.h3();
        writer.print(member.name());
        writer.h3End();
    }

    protected void printFullComment(ProgramElementDoc member) {
        writer.dl();
        printDeprecated(member);
        printCommentAndTags(member);
        writer.dlEnd();
    }

    protected void printCommentAndTags(ProgramElementDoc member) {
        printComment(member);
        printTags(member);
    }

    /**
     * Forward to containing writer
     */
    public void printSummaryHeader(ClassDoc cd) {
        writer.printSummaryHeader(this, cd);
    }

    /**
     * Forward to containing writer
     */
    public void printInheritedSummaryHeader(ClassDoc cd) {
        writer.printInheritedSummaryHeader(this, cd);
    }

    /**
     * Forward to containing writer
     */
    public void printInheritedSummaryFooter(ClassDoc cd) {
        writer.printInheritedSummaryFooter(this, cd);
    }

    /**
     * Forward to containing writer
     */
    public void printSummaryFooter(ClassDoc cd) {
        writer.printSummaryFooter(this, cd);
    }

    /**
     * Forward to containing writer
     */
    public void printSummaryMember(ClassDoc cd, ProgramElementDoc member) {
        writer.printSummaryMember(this, cd, member);
    }

    /**
     * Forward to containing writer
     */
    public void printInheritedSummaryMember(ClassDoc cd, 
                                            ProgramElementDoc member) {
        writer.printInheritedSummaryMember(this, cd, member);
    }

    public void printMembersSummary(ClassDoc cd) {
        ProgramElementDoc[] members = members(cd);
        if (members.length > 0) {
            Arrays.sort(members);
            printSummaryHeader(cd);
            for (int i = 0; i < members.length; ++i) {
                printSummaryMember(cd, members[i]);
            }
            printSummaryFooter(cd);
        }
    }

    public void printInheritedMembersSummary(ClassDoc cd) {
        if (cd.isClass()) {
            ClassDoc icd = cd.superclass();
            while (icd != null) {
                printInheritedMembersInfo(icd);
                icd = icd.superclass();
            }
        } else { // this is an interface 
            ClassDoc[] iin = cd.interfaces();
            for (int i = 0; i < iin.length; i++) {
                printInheritedMembersInfo(iin[i]);
            }
            for (int i = 0; i < iin.length; i++) {
                printInheritedMembersSummary(iin[i]);
            }
        }
    }

    protected void printInheritedMembersInfo(ClassDoc icd) {
      if (Standard.excludeClass(icd))
	return;

        ProgramElementDoc[] members = members(icd);
        if (members.length > 0) {
            Arrays.sort(members);
            printInheritedSummaryHeader(icd);
	    
            printInheritedSummaryMember(icd, members[0]);
            for (int i = 1; i < members.length; ++i) {
                print(", "); writer.println(' ');
                printInheritedSummaryMember(icd, members[i]);
            }
            printInheritedSummaryFooter(icd);
        }
    }

    public void printMembers(ClassDoc cd) {
        ProgramElementDoc[] members = members(cd);
        if (members.length > 0) {
            printHeader(cd);
            for (int i = 0; i < members.length; ++i) {
                if (i > 0) {
                    writer.printMemberHeader();
                }
                writer.println("");
                printMember(members[i]);
                writer.printMemberFooter();
            }
            printBodyHtmlEnd(cd);
        }
    }

    /**
     * Generate the code for listing the deprecated APIs. Create the table
     * format for listing the API. Call methods from the sub-class to complete
     * the generation.
     */
    protected void printDeprecatedAPI(List deprmembers, String headingKey) {
        if (deprmembers.size() > 0) {
            writer.tableIndexSummary();
            writer.tableHeaderStart("#CCCCFF");
            writer.boldText(headingKey);
            writer.tableHeaderEnd();
            for (int i = 0; i < deprmembers.size(); i++) {
                ProgramElementDoc member =(ProgramElementDoc)deprmembers.get(i);
                ClassDoc cd = member.containingClass();
                writer.trBgcolorStyle("white", "TableRowColor");
                writer.summaryRow(0);
                printDeprecatedLink(member);
                writer.br();
                writer.printNbsps();
                writer.printInlineDeprecatedComment(member.tags("deprecated")[0]);
                writer.space();
                writer.summaryRowEnd();
                writer.trEnd();
            }
            writer.tableEnd();
            writer.space();
            writer.p();
        }
    }

    /**
     * Print use info.
     */
    protected void printUseInfo(Object mems, String heading) {
        if (mems == null) {
            return;
        }
        List members = (List)mems;
        if (members.size() > 0) {
            writer.tableIndexSummary();
            writer.tableUseInfoHeaderStart("#CCCCFF");
            writer.print(heading);
            writer.tableHeaderEnd();
            for (Iterator it = members.iterator(); it.hasNext(); ) {
                printSummaryMember(null, (ProgramElementDoc)it.next());
            }
            writer.tableEnd();
            writer.space();
            writer.p();
        }
    }

    protected void navSummaryLink(ClassDoc cd) {
        ProgramElementDoc[] members = members(cd);
        if (members.length > 0) {
            printNavSummaryLink(null, true);
            return;
        } else {
            ClassDoc icd = cd.superclass();
            while (icd != null) {
                ProgramElementDoc[] inhmembers = members(icd);
                if (inhmembers.length > 0) {
                    printNavSummaryLink(icd, true);
                    return;
                }
                icd = icd.superclass();
            }
        }
        printNavSummaryLink(null, false);
    }
   
    protected void navDetailLink(ClassDoc cd) {
        ProgramElementDoc[] members = members(cd);
        printNavDetailLink(members.length > 0? true: false);
    }

  protected boolean memberIsEligible(ProgramElementDoc member) {
    boolean noDeprecated = Standard.configuration().nodeprecated;

    return (!noDeprecated || member.tags("deprecated").length == 0) &&
      member.tags("undocumented").length == 0;
  }

  // gensym: ignore nodeprecated for now
    protected ProgramElementDoc[] eligibleMembers(ProgramElementDoc[] members) {
        List list = new ArrayList();
        for (int i = 0; i < members.length; i++) {
            if (memberIsEligible(members[i])) {
                list.add(members[i]);
            }
        }
        return (ProgramElementDoc[])list.
                               toArray(new ProgramElementDoc[list.size()]); 
    }
 
            
        
}  
    
    
