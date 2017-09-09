
package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiRecurringAlarm  extends gdiAlarmRoot{


	public gdiRecurringAlarm () {}

	public gdiRecurringAlarm (java.awt.Frame frame) {
		super(frame);

		recurringAlarmThreshold = new SpinEditor(0, Integer.MAX_VALUE, 1);
		dpanel.placeAttributeEditor(recurringAlarmThreshold,
			RECURRING_ALARM_THRESHOLD_, dpanel.integerFieldType, 0);

		recurringAlarmInterval = new IntervalEditor();
		dpanel.placeAttributeEditor(recurringAlarmInterval,
			RECURRING_ALARM_INTERVAL_, dpanel.integerFieldType, 1);
		
        filterTag.getLabel().setVisible(false);
        filterTag.setVisible(false);
        
	}

	protected SpinEditor recurringAlarmThreshold;
	protected IntervalEditor recurringAlarmInterval;

	protected final static Symbol RECURRING_ALARM_THRESHOLD_ = 
	Symbol.intern("RECURRING-ALARM-THRESHOLD");
	protected final static Symbol RECURRING_ALARM_INTERVAL_ = 
	Symbol.intern("RECURRING-ALARM-INTERVAL");
	
}