
package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.beansruntime.StringVector;
import com.gensym.gda.controls.*;

public class gdiDataInputCounter extends BlocksDialog{


	public gdiDataInputCounter () {}

	public gdiDataInputCounter (java.awt.Frame frame) {
		super(frame);
	
		updateOutput = new RadioBoxEditor();
		StringVector members = new StringVector(new String[] {"continuously", "upon-reset"});
		updateOutput.setLabels(members);
		updateOutput.setMembers(members);
		updateOutput.setRowsAndColumns(1, 2);
		dpanel.placeAttributeEditor(updateOutput, 
		UPDATE_OUTPUT_, dpanel.symbolFieldType, 1);
		
	}


	protected RadioBoxEditor updateOutput;		

	protected final static Symbol UPDATE_OUTPUT_= Symbol.intern("UPDATE-OUTPUT");

/*
	protected final static Symbol CONTINUOUSLY_= Symbol.intern("CONTINUOUSLY");
	protected final static Symbol UPONRESET_= Symbol.intern("UPON-RESET");
*/
}