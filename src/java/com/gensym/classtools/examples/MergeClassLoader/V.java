package com.gensym.classtools.examples.MergeClassLoader;

import com.gensym.classtools.*;

/**
*  V is a class that is used purely during testing of the ClassTools package.
*/
public class V {
	protected int supercount = 4;
	
	public V() {
	}

	int dootherStuff() throws ClassMergeException{
		return supercount;
	}

}
