package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiVelocityLimiting  extends BlocksDialog {
	
	public gdiVelocityLimiting () {}

	public gdiVelocityLimiting (java.awt.Frame frame) {
		super(frame);

		maxRiseVelocity = new SpinOrNoneEditor();
		dpanel.placeAttributeEditor(maxRiseVelocity, MAX_RISE_VELOCITY_, 0);

		maxFallVelocity = new SpinOrNoneEditor();
		dpanel.placeAttributeEditor(maxFallVelocity, MAX_FALL_VELOCITY_, 1);

	
		updateInterval= new IntervalOrNoneEditor();
		dpanel.placeAttributeEditor(updateInterval, UPDATE_INTERVAL_, 2);
	}

	protected IntervalOrNoneEditor updateInterval;
	protected SpinOrNoneEditor maxRiseVelocity;
	protected SpinOrNoneEditor maxFallVelocity;

	protected final static Symbol UPDATE_INTERVAL_= Symbol.intern("UPDATE-INTERVAL");
	protected final static Symbol MAX_RISE_VELOCITY_ = Symbol.intern("MAX-RISE-VELOCITY");
  protected final static Symbol MAX_FALL_VELOCITY_ = Symbol.intern("MAX-FALL-VELOCITY");
}