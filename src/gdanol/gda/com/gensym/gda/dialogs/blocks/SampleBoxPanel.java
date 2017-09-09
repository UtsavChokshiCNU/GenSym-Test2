
package com.gensym.gda.dialogs.blocks;


import javax.swing.border.TitledBorder;
import javax.swing.border.LineBorder;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class SampleBoxPanel extends gdaPanel {


	public SampleBoxPanel(gdaDialog listener) {
    	this(listener, SampleComboBoxEditor.FIXED, 1);
	}
	
	public SampleBoxPanel(gdaDialog listener, int type, int minvalue) {
    	super(listener);
		sampleType = new SampleComboBoxEditor(type);
		placeAttributeEditor(sampleType,SAMPLE_TYPE_, 1);
	
		sampleSize = new SpinEditor(minvalue, Integer.MAX_VALUE, 1);
		placeAttributeEditor(sampleSize,SAMPLE_SIZE_, integerFieldType, 2);
		setBorder(new TitledBorder(LineBorder.createBlackLineBorder(),
			dialog.localize("Sample")));
	
  	}

	public void setSampleTypeType(int type) {sampleType.setType(type);}
	
	public void setSampleSizeMinValue(int minvalue) {
		sampleSize.getSpinField().setMinValue(minvalue);
	}
	
	protected SampleComboBoxEditor sampleType;
	protected SpinEditor sampleSize;

	protected final static Symbol SAMPLE_TYPE_= Symbol.intern("SAMPLE-TYPE");		
    protected final static Symbol SAMPLE_SIZE_ = Symbol.intern("SAMPLE-SIZE");		

}