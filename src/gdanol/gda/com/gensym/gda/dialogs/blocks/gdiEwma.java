package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.beansruntime.StringVector;

import com.gensym.gda.controls.*;

public class gdiEwma extends gdiSpcRun {
	
	public gdiEwma() {}

	public gdiEwma(java.awt.Frame frame) {
		super(frame);

		filterMode = new RadioBoxEditor();
		filterMode.setLabels(new StringVector());
		filterMode.setMembers(new StringVector(
			new String[] {"points", "time"}));
		filterMode.setRowsAndColumns(1, 2);
		dpanel.placeAttributeEditor(filterMode, FILTER_MODE_, 12);
		
		filterConstant = new SpinEditor(0, Double.MAX_VALUE, 1);
		dpanel.placeAttributeEditor(filterConstant, FILTER_CONSTANT_, 13);
	}
	
	protected RadioBoxEditor filterMode;
	protected SpinEditor filterConstant;

	protected final static Symbol FILTER_MODE_=Symbol.intern("FILTER-MODE");
	protected final static Symbol FILTER_CONSTANT_=Symbol.intern("FILTER-CONSTANT");

}