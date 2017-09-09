package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.beansruntime.StringVector;

import com.gensym.gda.controls.RadioBoxEditor;
import com.gensym.gda.controls.CheckBoxEditor;
import com.gensym.gda.controls.StatusComboBoxEditor;


public class gdiTimer extends gdiPersistenceGate {
    protected StatusComboBoxEditor stopWhen;
	protected CheckBoxEditor accumulateValues;
	
	protected final static Symbol STOP_WHEN_ = Symbol.intern("STOP-WHEN");
    protected final static Symbol ACCUMULATE_VALUES_ = Symbol.intern("ACCUMULATE-VALUES");

    public gdiTimer() {}

    public gdiTimer(java.awt.Frame frame) {
        super(frame);

        stopWhen = new StatusComboBoxEditor(StatusComboBoxEditor.SMALL_UNKNOWN);
        dpanel.placeAttributeEditor(stopWhen, 
            STOP_WHEN_, dpanel.statusFieldType, 6);
            
        accumulateValues = CheckBoxEditor.createYesNoCheckBox();
        dpanel.placeAttributeEditor(accumulateValues,
            ACCUMULATE_VALUES_, 7);
        
        triggerOn.setType(StatusComboBoxEditor.SMALL_UNKNOWN);
        
        delay.getLabel().setVisible(false);;
        delay.setVisible(false);
        
    }

}