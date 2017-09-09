package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiCovariance extends gdiHistoricalBlock {
	
	public gdiCovariance() {}

	public gdiCovariance(java.awt.Frame frame) {
		super(frame);

		covarianceScaling = CheckBoxEditor.createYesNoCheckBox();
		dpanel.placeAttributeEditor(covarianceScaling, COVARIANCE_SCALING_, 3);
		
		concurrencyWindow= new IntervalEditor();
		dpanel.placeAttributeEditor(concurrencyWindow,CONCURRENCY_WINDOW_, 4);
		
	}

	protected CheckBoxEditor covarianceScaling;
	protected IntervalEditor concurrencyWindow;

	protected final static Symbol COVARIANCE_SCALING_ = 	
		Symbol.intern("COVARIANCE-SCALING");
	protected final static Symbol CONCURRENCY_WINDOW_ = 
		Symbol.intern("CONCURRENCY-WINDOW");


}