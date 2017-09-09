package com.gensym.gda.dialogs.blocks;

import javax.swing.border.TitledBorder;
import javax.swing.border.LineBorder;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiSampleAndHold extends BlocksDialog {
	
	public gdiSampleAndHold() {}

	public gdiSampleAndHold(java.awt.Frame frame) {
		super(frame);
				
		sample = new SpinEditor(1, Integer.MAX_VALUE, 1);
		dpanel.placeAttributeEditor(sample, 
			localize("SampleSeriesSize"), SAMPLE_, dpanel.integerFieldType, 0);
		
		hold = new SpinEditor(0, Integer.MAX_VALUE, 1);
		dpanel.placeAttributeEditor(hold, 
			localize("HoldSeriesSize"),HOLD_, dpanel.integerFieldType, 1);
		
		dpanel.setBorder(new TitledBorder(LineBorder.createBlackLineBorder(),
			localize("SeriesSize")));

	}
	
	protected SpinEditor sample;
	protected SpinEditor hold;
	
	protected final static Symbol SAMPLE_= Symbol.intern("SAMPLE-SERIES-SIZE");
	protected final static Symbol HOLD_= Symbol.intern("HOLD-SERIES-SIZE");

}