/*
 * @(#)SerialMethodSubWriter.java	1.13 98/07/18
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

/**
 * Generate serialized form for Serializable/Externalizable methods.
 * Documentation denoted by the <code>serialData</code> tag is processed.
 *
 * @author Joe Fialli
 */
public class SerialMethodSubWriter extends MethodSubWriter {
    SerialMethodSubWriter(SubWriterHolderWriter writer) {
        super(writer);
    }

    public ProgramElementDoc[] members(ClassDoc cd) {
	return eligibleMembers(cd.serializationMethods());
    }

    protected void printHeader(ClassDoc cd) {
        writer.anchor("serialized_methods");
        writer.printTableHeadingBackground(writer.getText("doclet.Serialized_Form_methods"));

	// Specify if Class is Serializable or Externalizable.

        writer.p();

	if (cd.isSerializable() && !cd.isExternalizable()) {
            if (members(cd).length == 0) {
		String msg =
		    writer.getText("doclet.Serializable_no_customization");
		writer.print(msg);
		writer.p();
	    }
	}
    }

    protected void printMember(ClassDoc cd, ProgramElementDoc member) {
        ExecutableMemberDoc emd = (ExecutableMemberDoc)member;
        String name = emd.name();
        printHead(emd);
        printFullComment(emd);
    }

    protected void printSerialDataTag(Tag[] serialData) {
        if (serialData != null && serialData.length > 0) {
            writer.dt();
            writer.boldText("doclet.SerialData");
            writer.dd();
	    for (int i = 0; i < serialData.length; i++)
		writer.print(serialData[i].text());
        }
    }

    /**
     * Print comments, See tags and serialData for SerialMethods.
     */
    protected void printTags(ProgramElementDoc member) {
        MethodDoc method = (MethodDoc)member;
	Tag[] serialData = method.tags("serialData");
	Tag[] sinces = method.tags("since");
        SeeTag[] sees = method.seeTags();
        if (serialData.length + sees.length + sinces.length > 0) {
            writer.dd();
            writer.dl();
	    printSerialDataTag(serialData);
            writer.printSinceTag(method);
            writer.printSeeTags(method);
            writer.dlEnd();
            writer.ddEnd();
	} else {
	    if (method.name().compareTo("writeExternal") == 0) {
		Standard.configuration().standardmessage.
		    warning("doclet.MissingSerialDataTag",
			    method.containingClass().qualifiedName(),
			    method.name());
	    }
	}
    }

    /**
     * Print header even if there are no serializable methods.
     */
    public void printMembers(ClassDoc cd) {
        if (members(cd).length > 0) {
	    super.printMembers(cd);
        }
    }
}


