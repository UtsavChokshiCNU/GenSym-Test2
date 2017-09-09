package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.SpinEditor;

public class gdiBeliefRange extends BlocksDialog {
	protected BoundPanel boundPanel;
    
    private SpinEditor upper;
    private SpinEditor lower;
    	
    protected final static Symbol LOWER_THRESHOLD_ = Symbol.intern("LOWER-THRESHOLD");
    protected final static Symbol UPPER_THRESHOLD_ = Symbol.intern("UPPER-THRESHOLD");
    
    public gdiBeliefRange () {}

    public gdiBeliefRange (java.awt.Frame frame) {
        super(frame);
        
        BoundPanel boundPanel = new BoundPanel(this);
        boundPanel.setBorderTitle(localize("Threshold"));
        upper = new SpinEditor(0, 1, 0.1);
        lower = new SpinEditor(0, 1, 0.1);
        boundPanel.placeAttributeEditor(upper, localize("Upper"),
            UPPER_THRESHOLD_, boundPanel.quantityFieldType, 0);
        boundPanel.placeAttributeEditor(lower, localize("Lower"),
            LOWER_THRESHOLD_, boundPanel.quantityFieldType, 1);
        boundPanel.setEditors(upper, lower);
        dpanel.addPanel(boundPanel, null, 10);

    }

}