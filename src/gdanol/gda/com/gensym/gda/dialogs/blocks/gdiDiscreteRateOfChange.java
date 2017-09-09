package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.beansruntime.StringVector;

import com.gensym.gda.controls.*;

public class gdiDiscreteRateOfChange extends gdiDataShift {
	
	public gdiDiscreteRateOfChange() {}

	public gdiDiscreteRateOfChange(java.awt.Frame frame) {
		super(frame);

		sampleBox.setType(sampleBox.updateType);
		
		numberOfPoints = new RadioBoxEditor();
		numberOfPoints.setLabels(new StringVector());
		numberOfPoints.setMembers(new StringVector(
			new String[]{"5", "7"}));
		numberOfPoints.setRowsAndColumns(1, 2);
		dpanel.placeAttributeEditor(numberOfPoints,
			NUMBER_OF_POINTS_, dpanel.integerFieldType, 2);
			
		polynomialOrder = new RadioBoxEditor();
		polynomialOrder.setLabels(new StringVector());
		polynomialOrder.setMembers(new StringVector(
			new String[]{"2", "3"}));
		polynomialOrder.setRowsAndColumns(1, 2);
		dpanel.placeAttributeEditor(polynomialOrder,
			POLYNOMIAL_ORDER_, dpanel.integerFieldType, 3);
			
		scaleFactor = new SpinEditor();
		dpanel.placeAttributeEditor(scaleFactor,SCALE_FACTOR_, 4);
		
	}

	protected RadioBoxEditor numberOfPoints;
	protected RadioBoxEditor polynomialOrder;
	protected SpinEditor scaleFactor;

	protected final static Symbol NUMBER_OF_POINTS_ = 
		Symbol.intern("NUMBER-OF-POINTS");
	protected final static Symbol POLYNOMIAL_ORDER_ = 
		Symbol.intern("POLYNOMIAL-ORDER");
	protected final static Symbol SCALE_FACTOR_ = 
		Symbol.intern("SCALE-FACTOR");


}