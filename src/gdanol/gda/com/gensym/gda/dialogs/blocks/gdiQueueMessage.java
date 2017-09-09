package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;

import com.gensym.gda.controls.SpinEditor;
import com.gensym.gda.controls.TextFieldEditor;
import com.gensym.gda.controls.TextOrNoneEditor;
import com.gensym.gda.controls.StatusComboBoxEditor;

public class gdiQueueMessage extends AlarmSource {
	protected SpinEditor entryPriority;
	protected TextFieldEditor entryText;
	protected SpinEditor beliefValue;
	protected StatusComboBoxEditor beliefStatus;
    
    protected static final Symbol ENTRY_PRIORITY_ = Symbol.intern("GDL-ENTRY-PRIORITY");
    protected static final Symbol ENTRY_TEXT_ = Symbol.intern("GDL-ENTRY-TEXT");
    protected static final Symbol BELIEF_VALUE_ = Symbol.intern("GDL-BELIEF-VALUE");
    protected static final Symbol BELIEF_STATUS_ = Symbol.intern("GDL-BELIEF-STATUS");

    public gdiQueueMessage(){}

    public gdiQueueMessage(java.awt.Frame frame){
        super(frame);

        entryPriority = new SpinEditor(0, Integer.MAX_VALUE, 1);
        dpanel.placeAttributeEditor(entryPriority, ENTRY_PRIORITY_, dpanel.integerFieldType, 15);
        
        beliefValue = new SpinEditor(0,1,0.1);
        dpanel.placeAttributeEditor(beliefValue, BELIEF_VALUE_, dpanel.quantityFieldType, 42);
        
        beliefStatus = new StatusComboBoxEditor(StatusComboBoxEditor.SMALL_UNKNOWN);
        dpanel.placeAttributeEditor(beliefStatus, BELIEF_STATUS_, dpanel.statusFieldType, 43);
        
        entryText = new TextFieldEditor();
        dpanel.placeAttributeEditor(entryText, ENTRY_TEXT_, dpanel.textFieldType, 45);
        
    }
    
    
}