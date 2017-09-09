/*
 * @(#)FileType.java	1.5 98/02/02
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

import java.util.*;
import java.io.File;
import java.net.*;
import javax.swing.*;
/**
 * @version 1.5 02/02/98
 * @author Ray Ryan
 */
public interface FileType {
    /**
     * @return a human readable name for this type, e.g. "HyperText Markup Language Document (HTML)"
     */
    String getPresentationName();

    /**
     * Return true if it would be appropriate to set this as the
     * type of the given file. Does not necessarily imply
     * that the file exists.
     */
    boolean testFile(File file);

    /**
     * May return null. In this case the UI must provide an icon
     */
    Icon getIcon();

    /**
     * @return true if file choosers should descend into this type.
     *
     * Note that returning false from this is a perfectly acceptable
     * way to tell a FileChooser that a given type of directory is
     * actually a document, and not to be descended.
     */
    boolean isContainer();

    static public final GenericFile SharedGenericFile = new GenericFile();
    public class GenericFile implements FileType {
	protected GenericFile() { }

	@Override
	public String getPresentationName() { return "File"; }
	@Override
	public Icon getIcon() { return null; }

	/**
	 * Kind of an expensive test (hits the disk, I think).
	 * If you know already, don't ask
	 */
	@Override
	public boolean testFile(File file) {
	    return true;
	}

	@Override
	public boolean isContainer() { return false; }
    }

    static public final Folder SharedFolder = new Folder();
    public class Folder implements FileType {
	protected Folder() { }

	@Override
	public String getPresentationName() { return "Folder"; }
	@Override
	public Icon getIcon() { return null; }

	/**
	 * Kind of an expensive test (hits the disk, I think).
	 * If you know already, don't ask. 
	 */
	@Override
	public boolean testFile(File file) {
	    return file.isDirectory();
	}

	@Override
	public boolean isContainer() { return true; }
    }

    /**
     * Used more as a rule than as a file type. Its test returns true
     * for any file whose first character is '.'.  Not inteneded to be
     * used as the type of a specific file, rather for use as the
     * special <code>hiddenRule</code> of a
     * <code>FileChooserModel</code>.
     */
    static public final Hidden SharedHidden = new Hidden();
    public class Hidden implements FileType {
	protected Hidden() { }

	@Override
	public String getPresentationName() { return "Hidden"; }
	@Override
	public Icon getIcon() { return null; }
	@Override
	public boolean testFile(File file) {
	    String n = file.getName();
	    return n.length() > 0 && n.charAt(0) == '.';
	}
	@Override
	public boolean isContainer() { return false; }
    }
	

    static public final Computer SharedComputer = new Computer();
    public class Computer implements FileType {
	protected Computer() { }

	@Override
	public String getPresentationName() { return "Computer"; }
	@Override
	public Icon getIcon() { return null; }
	@Override
	public boolean testFile(File file) { return false; }
	@Override
	public boolean isContainer() { return true; }
    }

    static public final FloppyDrive SharedFloppyDrive = new FloppyDrive();
    public class FloppyDrive implements FileType {
	protected FloppyDrive() { }

	@Override
	public String getPresentationName() {
	    return "3" + '\u00BD' + " Inch Floppy Disk";
	    // '\u00BD' is unicode for "vulgar one half mark"
	    // http://www.unicode.org/Unicode.charts/glyphless/U+0080.html
	}
	@Override
	public Icon getIcon() { return null; }
	@Override
	public boolean testFile(File file) {
	    String path = file.getPath();
	    if (path.length() == 3 && path.charAt(1) == ':'
		&& path.charAt(2) == '\\') 
	    {
		char c = path.charAt(0); 
		return c == 'A' || c == 'a' || c == 'B' || c == 'b';
	    } else {
		return false;
	    }
	}
	@Override
	public boolean isContainer() { return true; }
    }

    static public final HardDrive SharedHardDrive = new HardDrive();
    public class HardDrive implements FileType {
	protected HardDrive() { }

	@Override
	public String getPresentationName() { return "Disk Drive"; }
	@Override
	public Icon getIcon() { return null; }
	@Override
	public boolean testFile(File file) {
	    String path = file.getPath();
	    if (path.length() == 3 && path.charAt(1) == ':'
		&& path.charAt(2) == '\\') 
	    {
		char c = path.charAt(0);
		return (c >= 'C' && c <= 'Z') || (c >= 'c' && c <= 'z');
	    } else {
		return false;
	    }
	}
	@Override
	public boolean isContainer() { return true; }
    }

    public class ExtensionBased implements FileType {
	private String[] extensions;
	private String presentationName;
	private Icon icon;

	public ExtensionBased(String presentationName, String extension,
			      Icon icon) {
	    super();

	    this.presentationName = presentationName;
	    this.extensions = new String[1];
	    this.extensions[0] = extension;
	    this.icon = icon;
	}
	    
	public ExtensionBased(String presentationName, String[] extensions,
			      Icon icon) {
	    super();
	    if (extensions.length < 1) {
		throw new IllegalArgumentException("Empty extensions array");
	    }
	    this.presentationName = presentationName;
	    this.extensions = (String[])extensions.clone();
	    this.icon = icon;
	}
	    
	/**
	 * Return true if the file ends in one of this type's extensions.
	 * Note that this will succeed whether or not file is a directory.
	 * That's a feature.
	 */
	@Override
	public boolean testFile(File file) {
	    int count = extensions.length;
	    String path = file.getPath();
	    for (int i =0; i < count; i++) {
		String ext = extensions[i];
		if (path.endsWith(ext) 
		    && path.charAt(path.length()-ext.length()) == '.') {
		    return true;
		}
	    }
	    return false;
	}		

	@Override
	public String getPresentationName() {
	    // PENDING(rjrjr) Better default name
	    return presentationName == null ? extensions[0] : presentationName;
	}

	@Override
	public Icon getIcon() {
	    return this.icon;
	}

	public void setIcon(Icon icon) {
	    this.icon = icon;
	}

	/**
	 * @return false
	 */
    	@Override
    	public boolean isContainer() {
	    return false;
	}
    }

//     public class MIMEBased implements FileType {
// 	private String mimeType;
// 	private String presentationName;

// 	public MIMEBased(String presentationName,
// 			 String mimeType) {
// 	    super();
// 	    if (mimeType == null || presentationName == null) {
// 		throw new
// 		    IllegalArgumentException("Empty MIME type or description");
// 	    }
// 	}

// 	public String getPresentationName() {
// 	    return presentationName;
// 	}

// 	public String getMimeType() {
// 	    return mimeType;
// 	}

// 	public boolean testFile(File f) {
// 	    try {
// 		return new URL("file://localhost/" + f.getPath()).
// 		    openConnection().getContentType().
// 		    equals(this.getMimeType());
// 		//    Too slow. Why? Should be local operation. 
// 	    } catch (Exception e) {
// 		return false;
// 	    }
// 	}
//     }
}
