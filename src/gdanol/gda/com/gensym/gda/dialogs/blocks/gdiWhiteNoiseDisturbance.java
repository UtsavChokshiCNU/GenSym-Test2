package com.gensym.gda.dialogs.blocks;

import javax.swing.border.TitledBorder;
import javax.swing.border.LineBorder;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiWhiteNoiseDisturbance extends gdiRealTimeClock {
	
	public gdiWhiteNoiseDisturbance(){}

	public gdiWhiteNoiseDisturbance(java.awt.Frame frame) {
		super(frame);

		disturbancePanel = new BlocksPanel(this);
		disturbanceMean = new SpinEditor();
		disturbancePanel.placeAttributeEditor(disturbanceMean, 
			localize("Mean"),DISTURBANCE_MEAN_, 0);

		disturbanceVariance = new SpinEditor(0, Double.MAX_VALUE, 1);
		disturbancePanel.placeAttributeEditor(disturbanceVariance, 
			localize("Variance"),DISTURBANCE_VARIANCE_, 1);
		
		disturbancePanel.setBorder(new TitledBorder(
			LineBorder.createBlackLineBorder(),localize("Disturbance")));
		dpanel.addPanel(disturbancePanel, null, 2);

	}

	protected BlocksPanel disturbancePanel;
	protected SpinEditor disturbanceVariance;
	protected SpinEditor disturbanceMean;

	protected final static Symbol DISTURBANCE_MEAN_ = 
		Symbol.intern("DISTURBANCE-MEAN");
	protected final static Symbol DISTURBANCE_VARIANCE_ = 
		Symbol.intern("DISTURBANCE-VARIANCE");

}