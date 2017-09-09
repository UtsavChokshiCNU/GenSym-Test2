package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;

import com.gensym.gda.controls.ComboBoxEditor;
import com.gensym.gda.controls.SpinEditor;
import com.gensym.gda.controls.TextAreaEditor;
import com.gensym.gda.controls.CheckBoxEditor;
import com.gensym.gda.controls.TextOrUnspecEditor;

public abstract class AlarmSource extends BlocksDialog {
	protected ComboBoxEditor displayQueue;
	protected SpinEditor severity;
	protected TextAreaEditor advice;
	protected CheckBoxEditor requireAck;
	protected TextOrUnspecEditor filterTag;
	    
    protected final static Symbol DISPLAY_QUEUE_ = Symbol.intern("GDL-DISPLAY-QUEUE");
    protected final static Symbol SEVERITY_ = Symbol.intern("SEVERITY");
    protected final static Symbol ADVICE_= Symbol.intern("ADVICE");
    protected final static Symbol REQUIRE_ACKNOWLEDGEMENT_= Symbol.intern("REQUIRE-ACKNOWLEDGEMENT");
    protected final static Symbol FILTER_TAG_ = Symbol.intern("GDL-FILTER-TAG");
    
    public AlarmSource() {}

    public AlarmSource(java.awt.Frame frame){
        super(frame);
           
        displayQueue = new ComboBoxEditor();
        dpanel.placeAttributeEditor(displayQueue, 
            DISPLAY_QUEUE_, BlocksPanel.symbolFieldType, 10);
        
        severity = new SpinEditor(1, 15, 1);
        dpanel.placeAttributeEditor(severity, 
            SEVERITY_, BlocksPanel.integerFieldType, 20);
                    
        filterTag = new TextOrUnspecEditor();
        dpanel.placeAttributeEditor(filterTag, 
            FILTER_TAG_, BlocksPanel.symbolFieldType, 30); 
        
        requireAck= new CheckBoxEditor();
        dpanel.placeAttributeEditor(requireAck, REQUIRE_ACKNOWLEDGEMENT_, 40);
                
        advice = new TextAreaEditor();
        dpanel.placeAttributeEditor(advice, ADVICE_, BlocksPanel.textFieldType, 50);
    }
    
}