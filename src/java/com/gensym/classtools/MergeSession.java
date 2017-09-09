package com.gensym.classtools;

/** The class <code>MergeSession</code> is used to control the 
* behavior of the merge() method in ClassInfo.   
*/
public class MergeSession
{
	private ClassInfo[] classes;
	private short mergePolicy;

	public static final short MERGE_EXCEPTION_ON_CONFLICT = 0;

	public static final short MERGE_IGNORE_ON_CONFLICT = 1;

	public static final short MERGE_BUFFER_CONFLICTS = 2;

        public static final short MERGE_REPLACE_ON_CONFLICT = 3;

	/** Construct a MergeSession.  The classes argument must be
	* an array of ClassInfo objects representing a class hierarchy.
	* The class hierarchy cannot contain any gaps, but it need not
	* go all the way to java.lang.Object. The restriction on the class
	* hierarchy is that it must be adequate to describe a merge for
	* the ClassInfo that this MergeSession is passed to.
	* For example:
	* <br>
	* java.lang.Object -> com.ajs.Boo->com.ajs.Baz -> com.ajs.Bar<br>
	* java.lang.Object -> com.ajs.Boo->com.ajs.Foo<br>
	* <br>
	* To merge the class Bar into the class Foo the ClassInfo object
	* that describes Baz and the ClassInfo object that describes Bar
	* will both be necessary.
	* <p>
	* The mergePolicy is a constant that controls how the merge will 
	* handle conflicts.
	*/
	public MergeSession(ClassInfo[] classes, short mergePolicy)
	{
		this.classes = classes;
		this.mergePolicy = mergePolicy;
	}

	public short getMergePolicy()
	{
		return mergePolicy;
	}

	public ClassInfo[] getClasses()
	{
		return (ClassInfo[]) classes.clone();
	}
}
