
package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;

import com.gensym.gda.controls.*;

public class gdiDataPathEntry extends gdiEntryPoint{


	public gdiDataPathEntry() {}

	public gdiDataPathEntry(java.awt.Frame frame) {
		super(frame);

		validityInterval = new IntervalOrRadioEditor (
			new Symbol[]{INDEFINITE_, SUPPLIED_});
		dpanel.placeAttributeEditor(validityInterval, 
			VALIDITY_INTERVAL_,  2);

	}

	protected IntervalOrRadioEditor validityInterval;
	
	protected final static Symbol VALIDITY_INTERVAL_ = Symbol.intern("VALIDITY-INTERVAL");
	protected final static Symbol INDEFINITE_ = Symbol.intern("INDEFINITE");
	protected final static Symbol SUPPLIED_ = Symbol.intern("SUPPLIED");

	
}