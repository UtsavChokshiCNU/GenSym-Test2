package com.gensym.nols.data;

/**
 *		Gensym Project Class.
 *		This class is extended from Object.class
 *		Modified 11/12/97 by Gchen
 */

import java.io.*;
import java.lang.*;
import java.util.*;
import java.lang.reflect.*;
import java.util.zip.*;

import com.gensym.DEBUG;
import com.gensym.nols.data.*;
/**
  * A class whose sole purpose in life is to control the writing and repair of files function. */

public class FullVersionManager implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	static final int productFileVersion = 1; // change this when necessary. new version 12.6.2002

	private int instanceFileVersion = productFileVersion;

	public boolean isValidLicense(long licenseCode){
		return true;
	}
}

