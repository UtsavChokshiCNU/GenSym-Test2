package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiRecurringCondition extends gdiConclusion {
	

	public gdiRecurringCondition() {}

	public gdiRecurringCondition(java.awt.Frame frame) {
		super(frame);
	

		triggerOn = new StatusComboBoxEditor(StatusComboBoxEditor.ALWAYS_UNKNOWN);
		dpanel.placeAttributeEditor(triggerOn, TRIGGER_ON_, 2);
	
		recurringAlarmThreshold=new SpinEditor(0, Integer.MAX_VALUE, 1);
		dpanel.placeAttributeEditor(recurringAlarmThreshold, 
			RECURRING_ALARM_THRESHOLD_, dpanel.integerFieldType, 4);
		
		recurringAlarmInterval=new IntervalEditor();
		dpanel.placeAttributeEditor(recurringAlarmInterval, 
			RECURRING_ALARM_INTERVAL_, 6);
		
	}

	protected StatusComboBoxEditor triggerOn;
	protected SpinEditor recurringAlarmThreshold;
	protected IntervalEditor recurringAlarmInterval;

	protected final static Symbol  TRIGGER_ON_= Symbol.intern("TRIGGER-ON");
	protected final static Symbol  RECURRING_ALARM_THRESHOLD_= 
		Symbol.intern("RECURRING-ALARM-THRESHOLD");
	protected final static Symbol  RECURRING_ALARM_INTERVAL_= 
		Symbol.intern("RECURRING-ALARM-INTERVAL");

}