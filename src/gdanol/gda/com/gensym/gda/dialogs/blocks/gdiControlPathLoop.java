package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiControlPathLoop extends BlocksDialog {
	
	public gdiControlPathLoop() {}

	public gdiControlPathLoop(java.awt.Frame frame) {
		super(frame);

		iterationLimit = new SpinEditor(1, Integer.MAX_VALUE, 1);
		dpanel.placeAttributeEditor(iterationLimit,
			ITERATION_LIMIT_, dpanel.integerFieldType, 0);

		exitIf = new TextOrNoneEditor();
		dpanel.placeAttributeEditor(exitIf,EXIT_IF_, 1);

	}

	protected SpinEditor iterationLimit;
	protected TextOrNoneEditor exitIf;

	protected final static Symbol ITERATION_LIMIT_= Symbol.intern("ITERATION-LIMIT");
	protected final static Symbol EXIT_IF_= Symbol.intern("EXIT-IF");

}