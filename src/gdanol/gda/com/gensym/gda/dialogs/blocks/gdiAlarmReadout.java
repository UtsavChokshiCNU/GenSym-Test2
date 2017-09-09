package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiAlarmReadout extends BlocksDialog {
	
	public gdiAlarmReadout() {}

	public gdiAlarmReadout(java.awt.Frame frame) {
		super(frame);

		nameOfViewedBlock = new ComboBoxEditor();
		dpanel.placeAttributeEditor(nameOfViewedBlock,
			NAME_OF_VIEWED_BLOCK_,dpanel.symbolFieldType, 0);

		portname = new ComboBoxEditor();
		dpanel.placeAttributeEditor(portname,
			PORTNAME_, dpanel.symbolFieldType, 1);
		
		displayAttribute = new ComboBoxEditor();
		dpanel.placeAttributeEditor(displayAttribute,
			DISPLAY_ATTRIBUTE_, dpanel.symbolFieldType, 2);

		quantization = new SpinOrNoneEditor();
		dpanel.placeAttributeEditor(quantization,QUANTIZATION_, 3);
		
	}

	protected ComboBoxEditor nameOfViewedBlock;
	protected ComboBoxEditor portname;
	protected ComboBoxEditor displayAttribute;
	protected SpinOrNoneEditor quantization;

	protected final static Symbol NAME_OF_VIEWED_BLOCK_= 
		Symbol.intern("NAME-OF-VIEWED-BLOCK");
	protected final static Symbol PORTNAME_= Symbol.intern("PORTNAME");
	protected final static Symbol DISPLAY_ATTRIBUTE_= Symbol.intern("DISPLAY-ATTRIBUTE");
	protected final static Symbol QUANTIZATION_= Symbol.intern("QUANTIZATION");
	

}