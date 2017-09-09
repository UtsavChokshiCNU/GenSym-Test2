package com.gensym.gda.dialogs.blocks;

import com.gensym.gda.controls.Boundary;
import com.gensym.gda.controls.SpinEditor;
import com.gensym.gda.controls.SpinOrNoneEditor;

public class gdiFuzzyConsequent extends BlocksDialog {
	protected UncertaintyBoundPanel uboundPanel;

    public gdiFuzzyConsequent () {}
	    
    public gdiFuzzyConsequent (java.awt.Frame frame) {
        super(frame);

        UncertaintyBoundPanel uboundPanel = 
            UncertaintyBoundPanel.createThresholdUncertaintyPanel(this);
        dpanel.addPanel(uboundPanel, null, 10);
        
        ((Boundary)uboundPanel.getMinEditor()).setMinValue(0.0);
        ((Boundary)uboundPanel.getMinEditor()).setMaxValue(1.0);
        ((SpinEditor)uboundPanel.getMinEditor()).setIncrement(0.1);
        ((Boundary)uboundPanel.getMaxEditor()).setMinValue(0.0);
        ((Boundary)uboundPanel.getMaxEditor()).setMaxValue(1.0);
        ((SpinEditor)uboundPanel.getMaxEditor()).setIncrement(0.1);
        
        ((SpinOrNoneEditor)uboundPanel.getMinUncertaintyEditor()).setIncrement(0.1);
        ((SpinOrNoneEditor)uboundPanel.getMaxUncertaintyEditor()).setIncrement(0.1);                
        
    }

    
}