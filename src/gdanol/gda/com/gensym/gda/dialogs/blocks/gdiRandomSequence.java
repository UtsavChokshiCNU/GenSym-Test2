package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiRandomSequence extends gdiRealTimeClock {
	
	public gdiRandomSequence() {}

	public gdiRandomSequence(java.awt.Frame frame) {
		super(frame);
		
		boundPanel = new BoundPanel(this);
		maxValue= new SpinEditor();
		minValue = new SpinEditor();
		boundPanel.placeAttributeEditor(minValue, MIN_VALUE_, 0);
		boundPanel.placeAttributeEditor(maxValue, MAX_VALUE_, 1);
		boundPanel.setEditors(maxValue, minValue);
		dpanel.addPanel(boundPanel, null, 2);
		
	}

	protected BoundPanel boundPanel;

	protected SpinEditor minValue;
	protected SpinEditor maxValue;

	protected final static Symbol MIN_VALUE_ = Symbol.intern("MIN-VALUE");
	protected final static Symbol MAX_VALUE_ = Symbol.intern("MAX-VALUE");

}