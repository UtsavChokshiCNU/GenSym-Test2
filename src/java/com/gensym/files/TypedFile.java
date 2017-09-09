/*
 * @(#)TypedFile.java	1.8 98/02/02
 * 
 * Copyright (c) 1997 Sun Microsystems, Inc. All Rights Reserved.
 * 
 * This software is the confidential and proprietary information of Sun
 * Microsystems, Inc. ("Confidential Information").  You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered into
 * with Sun.
 * 
 * SUN MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
 * SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE, OR NON-INFRINGEMENT. SUN SHALL NOT BE LIABLE FOR ANY DAMAGES
 * SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
 * THIS SOFTWARE OR ITS DERIVATIVES.
 * 
 */
package com.gensym.files;

import javax.swing.*;
import java.io.File;

/**
 * Typed File Objects, returned by FileChooserModel
 * <p>
 * Warning: serialized objects of this class will not be compatible with
 * future swing releases.  The current serialization support is appropriate
 * for short term storage or RMI between Swing1.0 applications.  It will
 * not be possible to load serialized Swing1.0 objects with future releases
 * of Swing.  The JDK1.2 release of Swing will be the compatibility
 * baseline for the serialized form of Swing objects.
 *
 * @version 1.8 02/02/98
 * @author Ray Ryan
 */
public class TypedFile extends File {
    private FileType type = null;

    /**
     * Package constructor, used only by FileChooserModel
     */
    TypedFile(String path) {
        this(path, (FileType)null);
    }
        
    /**
     * Package constructor, used only by FileChooserModel.
     */
    TypedFile(String path, String name) {
        this(path, name, null);
    }

    /**
     * Return a TypedFile of <code>type</code> for
     * <code>path</code>. If you need a TypedFile and you don't know
     * the type, use <code>FileChooserModel.getType</code>.
     */
    public TypedFile(String path, FileType type) {
        super(path);
	if (type != null)
	  this.setType(type);
    }

    /**
     * Return a TypedFile of <code>type</code> for
     * <code>path</code> and <code>name</code>. If you need a
     * TypedFile and you don't know the type, use
     * <code>FileChooserModel.getType</code>. 
     */
    public TypedFile(String path, String name, FileType type) {
        super(path, name);
        if (type != null) {
            this.setType(type);
        }
    }

    /**
     * Guaranteed not to return null. RuntimeException thrown if this
     * is called before a type has been set.
     */
    public FileType getType() {
        if (type == null) {
            throw new TypeNotSetException("Asked for type before it was set");
        }
        return type;
    }

    /**
     * Must be called once (and only once) before getType is called.
     * RuntimeException thrown if this is violated.
     */
    public void setType(FileType type) {
        if (this.type != null) {
            throw new RuntimeException("Tried to set type twice. 1) "
                                       + this.type + " 2) " + type);
        }
        this.type = type;
    }

    /**
     * May return null, in which case UI must provide a default icon
     */
    public Icon getIcon() {
        return this.getType().getIcon();
    }

    /**
     * Returns a string that displays and identifies this
     * object's properties.
     */
    @Override
    public String toString() {
        return super.toString() + " type: " + type;
    }

} // End class TypedFile

