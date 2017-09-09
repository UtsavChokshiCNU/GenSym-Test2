package com.gensym.gda.dialogs.blocks;

import javax.swing.border.TitledBorder;
import javax.swing.border.LineBorder;

import com.gensym.util.Symbol;
import com.gensym.beansruntime.StringVector;

import com.gensym.gda.controls.*;

public class gdiChangebandFilter extends gdiQuantization {
	
	public gdiChangebandFilter() {}

	public gdiChangebandFilter(java.awt.Frame frame) {
		super(frame);

		bandPanel = new BlocksPanel(this);
		
		bandCenter = new SpinOrNoneEditor();
		bandPanel.placeAttributeEditor(bandCenter, 
			localize("Center"), BAND_CENTER_, 0);
		
		bandType = new RadioBoxEditor();
		bandType.setLabels(new StringVector());
		bandType.setMembers(new StringVector(new String[]{"fixed", "floating"}));
		bandType.setRowsAndColumns(1, 2);
		bandPanel.placeAttributeEditor(bandType,localize("Type"),
			BAND_TYPE_, bandPanel.symbolFieldType, 1);
		
		bandRange = new SpinOrNoneEditor();
		bandPanel.placeAttributeEditor(bandRange, 
			localize("Range"),BAND_RANGE_, 2);
		
		bandPanel.setBorder(new TitledBorder(
			LineBorder.createBlackLineBorder(),localize("Band")));
		dpanel.addPanel(bandPanel, null, 15);

	}

	protected BlocksPanel bandPanel;
	protected SpinOrNoneEditor bandCenter;
	protected RadioBoxEditor bandType;
	protected SpinOrNoneEditor bandRange;

	protected final static Symbol  BAND_CENTER_= Symbol.intern("BAND-CENTER");
	protected final static Symbol  BAND_TYPE_= Symbol.intern("BAND-TYPE");
	protected final static Symbol  BAND_RANGE_= Symbol.intern("BAND-RANGE");


}