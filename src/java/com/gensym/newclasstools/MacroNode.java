package com.gensym.newclasstools;

public interface MacroNode {

	public boolean expansionRequired();

	public void expandInto(JavaNode j) throws ClassException;

}
