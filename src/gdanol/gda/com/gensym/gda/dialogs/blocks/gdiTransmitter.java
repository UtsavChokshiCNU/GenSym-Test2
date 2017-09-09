package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiTransmitter extends gdiPathConnectionPost {
	
	public gdiTransmitter() {}

	public gdiTransmitter(java.awt.Frame frame) {
		super(frame);

		g2process = new ComboBoxEditor();
		dpanel.placeAttributeEditor(g2process, G2_PROCESS_, 
			dpanel.symbolFieldType, 1);
		
	}


	protected ComboBoxEditor g2process;
	protected final static Symbol G2_PROCESS_ = Symbol.intern("G2-PROCESS");


}