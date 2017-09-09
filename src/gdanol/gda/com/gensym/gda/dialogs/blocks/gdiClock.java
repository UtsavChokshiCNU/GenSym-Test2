package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiClock extends BlocksDialog {
	
	public gdiClock() {}

	public gdiClock(java.awt.Frame frame) {
		super(frame);

		evaluationPeriod = new IntervalEditor();
		dpanel.placeAttributeEditor(evaluationPeriod,EVALUATION_PERIOD_, 0);

		allowIntermediateEvaluation = CheckBoxEditor.createYesNoCheckBox();
		dpanel.placeAttributeEditor(allowIntermediateEvaluation,
			ALLOW_INTERMEDIATE_EVALUATION_, 1);

	}

	protected IntervalEditor evaluationPeriod;
	protected CheckBoxEditor allowIntermediateEvaluation;

	protected final static Symbol EVALUATION_PERIOD_= 
		Symbol.intern("EVALUATION-PERIOD");
	protected final static Symbol ALLOW_INTERMEDIATE_EVALUATION_= 
		Symbol.intern("ALLOW-INTERMEDIATE-EVALUATION");
	

}