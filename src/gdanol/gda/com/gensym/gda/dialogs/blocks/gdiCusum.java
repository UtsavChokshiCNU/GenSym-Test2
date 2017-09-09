package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiCusum extends gdiSpcRun {
	
	public gdiCusum() {}

	public gdiCusum(java.awt.Frame frame) {
		super(frame);

		slack = new SpinEditor(0, Double.MAX_VALUE, 1);
		dpanel.placeAttributeEditor(slack, SLACK_, 12);

	}
	
	protected SpinEditor slack;

	protected final static Symbol SLACK_=Symbol.intern("SLACK");

}