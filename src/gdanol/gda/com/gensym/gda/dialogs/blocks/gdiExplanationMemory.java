package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;

import com.gensym.gda.controls.CheckBoxEditor;
import com.gensym.gda.controls.ComboBoxEditor;

public class gdiExplanationMemory extends gdiControlInhibit {
	protected CheckBoxEditor displayWhenUpdated;
	protected ComboBoxEditor displayExplanationsOn;
	
    protected final static Symbol DISPLAY_WHEN_UPDATED_ = Symbol.intern("DISPLAY-WHEN-UPDATED");
    protected final static Symbol DISPLAY_EXPLANATIONS_ON_ = Symbol.intern("DISPLAY-EXPLANATIONS-ON");
    
	public gdiExplanationMemory() {}

	public gdiExplanationMemory(java.awt.Frame frame) {
        super(frame);
        
        displayWhenUpdated = new CheckBoxEditor();
        dpanel.placeAttributeEditor(displayWhenUpdated, 
            DISPLAY_WHEN_UPDATED_, 20);
        
        displayExplanationsOn = new ComboBoxEditor();
        dpanel.placeAttributeEditor(displayExplanationsOn, 
            DISPLAY_EXPLANATIONS_ON_, dpanel.symbolFieldType, 30);
   
    } 
    
}