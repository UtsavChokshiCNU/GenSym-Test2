package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiWave extends gdiRealTimeClock {
			
	public gdiWave() {}

	public gdiWave(java.awt.Frame frame) {
		super(frame);

		period = new SpinEditor(1, Double.MAX_VALUE, 1);
		dpanel.placeAttributeEditor(period,PERIOD_, 2);
			
		bias = new SpinOrNoneEditor();
		dpanel.placeAttributeEditor(bias,BIAS_, 4);
		
		phaseAngle = new SpinEditor();
		dpanel.placeAttributeEditor(phaseAngle, PHASE_ANGLE_, 6);

		amplitude = new SpinEditor(0, Double.MAX_VALUE, 1);
		dpanel.placeAttributeEditor(amplitude, AMPLITUDE_, 8);
			
		resetPhase = CheckBoxEditor.createYesNoCheckBox();
		dpanel.placeAttributeEditor(resetPhase, RESET_PHASE_, 12);
		
	}

	protected SpinEditor period;
	protected SpinOrNoneEditor bias;
	protected SpinEditor phaseAngle;
	protected SpinEditor amplitude;
	protected CheckBoxEditor resetPhase;
	
	protected final static Symbol PERIOD_ = Symbol.intern("PERIOD");
	protected final static Symbol BIAS_ = Symbol.intern("BIAS");
	protected final static Symbol PHASE_ANGLE_ = Symbol.intern("PHASE-ANGLE");
	protected final static Symbol AMPLITUDE_ = Symbol.intern("AMPLITUDE");
	protected final static Symbol RESET_PHASE_ = Symbol.intern("RESET-PHASE");
}