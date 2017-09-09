
package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiEqualityObservation extends gdiConclusion {
	
	
	public gdiEqualityObservation() {}

	public gdiEqualityObservation(java.awt.Frame frame) {
		super(frame);

		referenceValue = new TextFieldEditor();
		referenceValue.getTextField().setShowQuotesForTextType(true);
		dpanel.placeAttributeEditor(referenceValue,
			REFERENCE_VALUE_, dpanel.valueFieldType,  3);
			
		equivalenceBand = new SpinOrNoneEditor(0, Double.MAX_VALUE, 1);
		dpanel.placeAttributeEditor(equivalenceBand,
			EQUIVALENCE_BAND_,dpanel.quantityFieldType, 7);

	}

	protected TextFieldEditor referenceValue;
	protected SpinOrNoneEditor equivalenceBand;

	protected final static Symbol  REFERENCE_VALUE_= 
		Symbol.intern("REFERENCE-VALUE");
	protected final static Symbol  EQUIVALENCE_BAND_= 
		Symbol.intern("EQUIVALENCE-BAND");

}