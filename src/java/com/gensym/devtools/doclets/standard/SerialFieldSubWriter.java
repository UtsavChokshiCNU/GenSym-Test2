/*
 * @(#)SerialFieldSubWriter.java	1.13 98/08/24
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
import java.util.Arrays;

/**
 * Generate serialized form for serializable fields.
 * Documentation denoted by the tags <code>serial</code> and
 * <code>serialField<\code> is processed.
 *
 * @author Joe Fialli
 */
public class SerialFieldSubWriter extends FieldSubWriter {
    ProgramElementDoc[] members = null;

    SerialFieldSubWriter(SubWriterHolderWriter writer) {
        super(writer);
    }

    public ProgramElementDoc[] members(ClassDoc cd) {
	if (members == null) { 
	    FieldDoc[] array = cd.serializableFields();
	    Arrays.sort(array);
	    members = eligibleMembers(array);
	}
	return members;
    }

    void printSignature(MemberDoc member) {
        FieldDoc field = (FieldDoc)member;
        printHead(member);
	writer.pre();
        printTypeLink(field.type());
        print(' ');
        bold(field.name());
	writer.preEnd();
    }

    protected void printHeader(ClassDoc cd) {
        writer.anchor("serializedForm");
	printSerializableClassComment(cd);
	writer.printTableHeadingBackground(writer.getText("doclet.Serialized_Form_fields"));
    }

    /**
     * javadoc comments for "serialPersistentFields" is considered
     * as serializable class comments, not field comments.
     */
    private void printSerializableClassComment(ClassDoc cd) {
	if (cd.definesSerializableFields()) {
	    FieldDoc serialPersistentFields = (FieldDoc)(members(cd)[0]);
	    String comment = serialPersistentFields.commentText();
	    if (comment.length() > 0) {
		writer.printTableHeadingBackground(writer.getText("doclet.Serialized_Form_class"));
		printFullComment(serialPersistentFields);
	    }
	}
    }

    protected void printBodyHtmlEnd(ClassDoc cd) {
    }

    /**
     * Print a default Serializable field or
     * print all Serializable fields documented by
     * <code>serialField</code> tags.
     */
    protected void printMember(ProgramElementDoc member) {
        FieldDoc field = (FieldDoc)member;
	ClassDoc cd = field.containingClass();
	if (cd.definesSerializableFields()) {

	    // Process Serializable Fields specified as array of ObjectStreamFields.
	    //Print a member for each serialField tag.
	    //(There should be one serialField tag per ObjectStreamField element.)
	    SerialFieldTag[] tags = field.serialFieldTags();
	    Arrays.sort(tags);
	    for (int i = 0; i < tags.length; i++) {
		if (i > 0) {
		    writer.printMemberHeader();
		} 
		printSignature(tags[i]);
		printComment(tags[i]);
                writer.printMemberFooter();
	    }
	} else {

	    // Process default Serializable field.
	    if ((field.tags("serial").length == 0) && ! field.isSynthetic()) {
	       Standard.configuration().
		   standardmessage.warning("doclet.MissingSerialTag",
			      cd.qualifiedName(), field.name());
	    }
	    printSignature(field);
	    printFullComment(field);
	}
    }

    /*
     * Print comment for a default Serializable field.
     *
     * If serial tag has an optional comment, append the
     * comment to the javadoc comment for the field.
     */
    protected void printComment(ProgramElementDoc member) {
	String fieldComment = member.commentText();
        if (fieldComment.length() > 0) {
            writer.dd();
            print(fieldComment);
	}

	Tag[] tags = member.tags("serial");
	if (tags.length > 0 && tags[0].text().length() > 0) {
	    String serialComment = tags[0].text();
            writer.dd();
	    print(serialComment);
	}
    }

    /* Methods for processing serialField fieldName fieldType description.*/
    void printSignature(SerialFieldTag sftag) {
	writer.pre();
	ClassDoc fieldTypeDoc = sftag.fieldTypeDoc();
	if (fieldTypeDoc != null) {
	    writer.printClassLink(fieldTypeDoc);
        } else {
	    writer.print(sftag.fieldType());
	}
        print(' ');
        bold(sftag.fieldName());
	writer.preEnd();
    }

    private void printComment(SerialFieldTag sftag) {
	writer.dl();
        writer.dd();
        writer.print(sftag.description());
	writer.dlEnd();
    }

    /* The methods following this comment have no meaning for SerialFields.*/
    protected void printDeprecatedLink(ProgramElementDoc member) {
    }

    public void printSummaryLabel(ClassDoc cd) {
    }

    public void printInheritedSummaryLabel(ClassDoc cd) {
    }

    protected void printSummaryLink(ClassDoc cd, ProgramElementDoc member) {
    }

    protected void printInheritedSummaryLink(ClassDoc cd,
                                             ProgramElementDoc member) {
    }

    protected void printSummaryType(ProgramElementDoc member) {
    }
}

