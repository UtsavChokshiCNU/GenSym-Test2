package com.gensym.classtools;

public interface MacroNode {

	public boolean expansionRequired();

	public void expandInto(JavaNode j) throws ClassException;

}
