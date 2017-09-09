
package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.beansruntime.StringVector;

import com.gensym.gda.controls.*;

public class gdiEventSequenceGate extends gdiLogicGate {
	
	public gdiEventSequenceGate() {}

	public gdiEventSequenceGate(java.awt.Frame frame) {
		super(frame);
		
		temporalUncertainty= new IntervalOrNoneEditor();
		dpanel.placeAttributeEditor(temporalUncertainty,
			TEMPORAL_UNCERTAINTY_, 1);
			
		triggerOn = new RadioBoxEditor();
		triggerOn.setLabels(new StringVector(new String[] 
			{"true", "false"}));
		triggerOn.setMembers(new StringVector(new String[] 
			{".true", ".false"}));
		triggerOn.setRowsAndColumns(1, 2);
		dpanel.placeAttributeEditor(triggerOn,TRIGGER_ON_, 3);

		enforceStrictSequence = CheckBoxEditor.createYesNoCheckBox();
		dpanel.placeAttributeEditor(enforceStrictSequence,
			ENFORCE_STRICT_SEQUENCE_, dpanel.statusFieldType, 5);
		
	}


	protected IntervalOrNoneEditor temporalUncertainty;
	protected RadioBoxEditor triggerOn;
	protected CheckBoxEditor enforceStrictSequence;

	protected final static Symbol TEMPORAL_UNCERTAINTY_ = 
		Symbol.intern("TEMPORAL-UNCERTAINTY");
	protected final static Symbol TRIGGER_ON_ = Symbol.intern("TRIGGER-ON");
	protected final static Symbol ENFORCE_STRICT_SEQUENCE_ = 
		Symbol.intern("ENFORCE-STRICT-SEQUENCE");

}