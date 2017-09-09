package com.gensym.gda.dialogs.blocks;

public class gdiNetworkSymbolEntry extends gdiNetworkTextEntry {
	
	public gdiNetworkSymbolEntry() {}

	public gdiNetworkSymbolEntry(java.awt.Frame frame) {
		super(frame);
		valueOnInitialization.setFieldType(dpanel.symbolFieldType);	
	}
}