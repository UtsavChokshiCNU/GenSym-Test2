package com.gensym.gda.dialogs.blocks;

import com.gensym.gda.controls.G2SpinField;

public class gdiNetworkControlEntry extends gdiNetworkNumericEntry {
	
	public gdiNetworkControlEntry() {}

	public gdiNetworkControlEntry(java.awt.Frame frame) {
		super(frame);
		G2SpinField spin = (G2SpinField)valueOnInitialization.getAttributeEditor();
		spin.setFieldType(dpanel.integerFieldType);
		spin.setMinValue(0);
		spin.setMaxValue(Integer.MAX_VALUE);
		
	}

}