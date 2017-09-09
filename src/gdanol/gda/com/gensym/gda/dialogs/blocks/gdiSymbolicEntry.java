package com.gensym.gda.dialogs.blocks;


public class gdiSymbolicEntry extends gdiTextEntry {
	
	public gdiSymbolicEntry() {}

	public gdiSymbolicEntry(java.awt.Frame frame) {
		super(frame);
		valueOnInitialization.setFieldType(dpanel.symbolFieldType);
		
	}
}