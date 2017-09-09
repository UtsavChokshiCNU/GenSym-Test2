package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;

import com.gensym.gda.controls.SpinEditor;

public class gdiBeliefWeight extends BlocksDialog {
	protected SpinEditor wieght;
	
    protected final static Symbol WEIGHT = Symbol.intern("WEIGHT");
    
    private static final int MAXIMUM_G2_INT = 0x1FFFFFFF;

    public gdiBeliefWeight () {}

    public gdiBeliefWeight (java.awt.Frame frame) {
        super(frame);

        wieght = new SpinEditor(-MAXIMUM_G2_INT, MAXIMUM_G2_INT, 1);
            
        dpanel.placeAttributeEditor(wieght, WEIGHT, dpanel.quantityFieldType, 10);
        
    }

}