package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.gda.controls.*;
import com.gensym.dlg.WarningDialog;

public class gdiNonlinearFilter extends gdiExponentialFilter {
	
	public gdiNonlinearFilter() {}

	public gdiNonlinearFilter(java.awt.Frame frame) {
		super(frame);

		noiseStdDeviation = new SpinEditor(0, Double.MAX_VALUE, 1);
		dpanel.placeAttributeEditor(noiseStdDeviation,
			NOISE_STD_DEVIATION_, dpanel.quantityFieldType, 20);

	}


	public boolean applyDialog() {
		Number deviation = (Number)getChangedValue(NOISE_STD_DEVIATION_);
		Number constant = (Number)getChangedValue(FILTER_CONSTANT_);
		if (deviation == null)
			deviation = (Number)getInitialValue(NOISE_STD_DEVIATION_);
		if (constant == null)
			constant = (Number)getInitialValue(FILTER_CONSTANT_);
			
		if (deviation.doubleValue()==constant.doubleValue()) {
			WarningDialog warningdialog = new WarningDialog(null, "", true, 
				localize("NoiseEqualsFilterConstant"), null);
      warningdialog.pack();
      warningdialog.setVisible(true);
			return false;
		}
			
		return super.applyDialog();
	}
	
	protected SpinEditor noiseStdDeviation;

	protected final static Symbol  NOISE_STD_DEVIATION_= 
		Symbol.intern("NOISE-STD-DEVIATION");
		

}