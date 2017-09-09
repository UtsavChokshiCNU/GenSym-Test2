package com.gensym.gda.dialogs.blocks;

import com.gensym.gda.controls.*;
import com.gensym.util.Symbol;

public class gdiAlarmRoot extends AlarmSource {
	protected ComboBoxEditor triggerOn;
	protected CheckBoxEditor automaticExplanation;
	protected CheckBoxEditor showMessages;
	
    protected static final Symbol TRIGGER_ON_ = Symbol.intern("TRIGGER-ON");
	protected static final Symbol AUTOMATIC_EXPLANATION_ = Symbol.intern("GENERATE-AUTOMATIC-EXPLANATION");
    protected static final Symbol SHOW_MESSAGES_ = Symbol.intern("SHOW-MESSAGES");
	
	public gdiAlarmRoot() {}

	public gdiAlarmRoot(java.awt.Frame frame) {
        super(frame);
               
        triggerOn = new StatusComboBoxEditor(StatusComboBoxEditor.SMALL_UNKNOWN);
        dpanel.placeAttributeEditor(triggerOn, TRIGGER_ON_, 5);
                            
        automaticExplanation= new CheckBoxEditor();
        dpanel.placeAttributeEditor(automaticExplanation, AUTOMATIC_EXPLANATION_, 43);

        showMessages = new CheckBoxEditor();
        dpanel.placeAttributeEditor(showMessages, SHOW_MESSAGES_, 41);

    }
	
}