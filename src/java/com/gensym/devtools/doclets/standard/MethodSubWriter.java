/*
 * @(#)MethodSubWriter.java	1.19 98/08/05
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

import java.util.*;
import com.gensym.devtools.doclets.*;
import com.sun.javadoc.*;

/**
 *
 * @author Robert Field
 * @author Atul M Dambalkar
 */
public class MethodSubWriter extends ExecutableMemberSubWriter {

    MethodSubWriter(SubWriterHolderWriter writer) {
        super(writer);
    }

    @Override
    public ProgramElementDoc[] members(ClassDoc cd) {
        return eligibleMembers(cd.methods());
    }

    @Override
    public void printSummaryLabel(ClassDoc cd) {
        writer.boldText("doclet.Method_Summary"); 
    }

    @Override
    public void printSummaryAnchor(ClassDoc cd) {
        writer.anchor("method_summary");
    }
   
    @Override
    public void printInheritedMembersSummary(ClassDoc cd) {
        List tcms = Group.asList(cd.methods()); // this class' methods
        Map imsmap = new HashMap();   // inherited methods
        List hierarchy = new ArrayList();
        if (cd.isClass()) {
            imsmap = getInheritedMethodMapForClass(cd, tcms, imsmap, hierarchy);
        } else {
            imsmap = getInheritedMethodMapForInterface(cd, tcms, imsmap,
                                                       hierarchy);
        }
        if (hierarchy.size() > 0) {
            for (int i = 0; i < hierarchy.size(); i++) {
                ClassDoc classkey = (ClassDoc)hierarchy.get(i);
		if (!Standard.excludeClass(classkey)) {
		  List methodlist = (List)imsmap.get(classkey);
		  printInheritedMembersInfo(classkey, methodlist);
		}
            }
        }
    }
 

    protected void printInheritedMembersInfo(ClassDoc icd, List members) {
      boolean printedFirstDoc = false;
        if (members.size() > 0) {
            Collections.sort(members);
            printInheritedSummaryHeader(icd);
	    ProgramElementDoc doc = (ProgramElementDoc)members.get(0);
	    if (memberIsEligible(doc)) {
	      printInheritedSummaryMember(icd, doc);
	      printedFirstDoc = true;
	    }
            for (int i = 1; i < members.size(); ++i) {
	      doc = (ProgramElementDoc)members.get(i);
	      if (memberIsEligible(doc)) {
		if (printedFirstDoc)
		  writer.println(", ");
		printInheritedSummaryMember(icd, doc);
		printedFirstDoc = true;
	      }
            }
            printInheritedSummaryFooter(icd);
        }
    }

 
    @Override
    public void printInheritedSummaryAnchor(ClassDoc cd) {
        writer.anchor("methods_inherited_from_class_" + cd.qualifiedName());
    }   
    
    @Override
    public void printInheritedSummaryLabel(ClassDoc cd) {
        String classlink = writer.getPreQualifiedClassLink(cd);
        writer.bold();
        if (cd.isClass()) {
            writer.printText("doclet.Methods_Inherited_From_Class", classlink);
        } else {
            writer.printText("doclet.Methods_Inherited_From_Interface",
                              classlink);
        } 
        writer.boldEnd();
    }

    protected void printSummaryType(ProgramElementDoc member) {
        MethodDoc meth = (MethodDoc)member;
        printModifierAndType(meth, meth.returnType());
    }

    protected void printReturnTag(Tag[] returns) {
        if (returns.length > 0) {
            writer.dt();
            writer.boldText("doclet.Returns");
            writer.dd();
            writer.printInlineComment(returns[0]);
        }
    }

    protected void printOverridden(ClassDoc overridden, MethodDoc method) {
        if (overridden != null) {
            String overriddenclasslink = writer.getClassLink(overridden);
            String methlink = "";
            String name = method.name();
            writer.dt();
            writer.boldText("doclet.Overrides");
            writer.dd();
            methlink = writer.getClassLink(overridden, 
                                           name + method.signature(), 
                                           name, false);
            writer.printText("doclet.in_class", methlink, overriddenclasslink);
        }
    }

    protected void printTags(ProgramElementDoc member) {
        MethodDoc method = (MethodDoc)member;

        ParamTag[] params = method.paramTags();
        Tag[] returns = method.tags("return");
        Tag[] sinces = method.tags("since");
        ThrowsTag[] thrown = method.throwsTags();
        SeeTag[] sees = method.seeTags();
        ClassDoc[] intfacs = member.containingClass().interfaces();
        ClassDoc overridden = method.overriddenClass();
        if (params.length + returns.length + thrown.length + sinces.length
            + intfacs.length + sees.length > 0 ||
            overridden != null) {
            writer.dd();
            writer.dl();
            printImplementsInfo(method);
            printParamTags(params);
            printReturnTag(returns);
            printThrowsTags(thrown);
            printOverridden(overridden, method);
            writer.printSinceTag(method);
            writer.printSeeTags(method);
            writer.dlEnd();
            writer.ddEnd();
        }
    }
                               
    protected void printSignature(ExecutableMemberDoc member) {
        writer.displayLength = 0;
	writer.pre();
	printModifiers(member);
	printReturnType((MethodDoc)member);
	bold(member.name());
	printParameters(member);
	printExceptions(member);
	writer.preEnd();
    }
      
    protected void printReturnType(MethodDoc method) {
        Type type = method.returnType();
        if (type != null) {
            printTypeLink(type);
            print(' ');
        }
    }
    
    @Override
    protected void printHeader(ClassDoc cd) {
        writer.anchor("method_detail");
        writer.printTableHeadingBackground(writer.
                                              getText("doclet.Method_Detail"));
    }

    @Override
    protected void printNavSummaryLink(ClassDoc cd, boolean link) {
        if (link) {
            writer.printHyperLink("", (cd == null)?
                                          "method_summary":
                                          "methods_inherited_from_class_" +
                                           cd.qualifiedName(),
                                      writer.getText("doclet.navMethod"));
        } else {
            writer.printText("doclet.navMethod");
        }
    }

    @Override
    protected void printNavDetailLink(boolean link) {
        if (link) {
            writer.printHyperLink("", "method_detail",
                                  writer.getText("doclet.navMethod"));
        } else {
            writer.printText("doclet.navMethod");
        }
    }

    protected Map getInheritedMethodMapForClass(ClassDoc cd, List tcms, 
                                                Map imsmap, List hierarchy) {
        ClassDoc icd = cd.superclass();
        while (icd != null) {
            composeInheritedMethodMap(icd, tcms, imsmap, hierarchy);
            icd = icd.superclass();
        }
        return imsmap;
    }

    // IMPORTANT: This code assumes that there is no ambiguity for a method
    // in the extended interfaces. If there is an ambiguity, Java compiler will
    // give compilation error for such a case. So the Java code to be
    // documented has to be compile time error free.

    protected Map getInheritedMethodMapForInterface(ClassDoc cd, List tims, 
                                                  Map imsmap, List hierarchy) {
        ClassDoc[] iin = cd.interfaces(); // implemented interfaces
        for (int i = 0; i < iin.length; i++) {
            composeInheritedMethodMap(iin[i], tims, imsmap, hierarchy);
        }
        for (int i = 0; i < iin.length; i++) {
            getInheritedMethodMapForInterface(iin[i], tims, imsmap, hierarchy);
        }
        return imsmap;
    }

    protected void composeInheritedMethodMap(ClassDoc icd, List tcms, 
                                             Map imsmap, List hierarchy) {
        MethodDoc[] methods = icd.methods();
        List methodlist = new ArrayList();
        for (int i = 0; i < methods.length; i++) {
            if (!contains(tcms, methods[i])) {
                methodlist.add(methods[i]);
                tcms.add(methods[i]);
            }
        }
        imsmap.put(icd, methodlist);
        hierarchy.add(icd);
    }
 
    /**
     * The simple search. Order `n'.
     */
    protected boolean contains(List tcmethods, MethodDoc method) {
        for (int i = 0; i < tcmethods.size(); i++) {
            MethodDoc tcmethod = (MethodDoc)tcmethods.get(i);
            if (tcmethod.name().equals(method.name()) &&
                   tcmethod.signature().equals(method.signature())) {
                return true;
            }
        }
        return false;
    }
}  
    
    
