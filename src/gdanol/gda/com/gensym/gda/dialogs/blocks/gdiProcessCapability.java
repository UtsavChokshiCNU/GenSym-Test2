
package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiProcessCapability extends gdiHistoricalBlock{


	public gdiProcessCapability () {}

	public gdiProcessCapability (java.awt.Frame frame) {
		super(frame);

		sampleBox.setFixed(false);
		
		BoundPanel boundPanel = new BoundPanel(this);
		boundPanel.setBorderTitle(localize("SpecificationLimit"));
		upper = new SpinEditor();
		lower = new SpinEditor();
		boundPanel.placeAttributeEditor(upper, UPPER_SPECIFICATION_LIMIT_, 0);
		boundPanel.placeAttributeEditor(lower, LOWER_SPECIFICATION_LIMIT_, 1);
		boundPanel.setEditors(upper, lower);
		dpanel.addPanel(boundPanel, null, 2);

	}


	protected SpinEditor upper;
	protected SpinEditor lower;

	protected final static Symbol UPPER_SPECIFICATION_LIMIT_ = Symbol.intern("UPPER-SPECIFICATION-LIMIT");
	protected final static Symbol LOWER_SPECIFICATION_LIMIT_ = Symbol.intern("LOWER-SPECIFICATION-LIMIT");
	
}