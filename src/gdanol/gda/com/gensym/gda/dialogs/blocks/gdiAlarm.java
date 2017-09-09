
package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiAlarm extends gdiAlarmRoot{


	public gdiAlarm () {}

	public gdiAlarm (java.awt.Frame frame) {
		super(frame);
		
		memoryEnabled = new CheckBoxEditor();
		dpanel.placeAttributeEditor(memoryEnabled, MEMORY_ENABLED_, 45);

		updateAlarmReadouts= new CheckBoxEditor();
		dpanel.placeAttributeEditor(updateAlarmReadouts, UPDATE_ALARM_READOUTS_, 47);

	}


	protected CheckBoxEditor memoryEnabled;
	protected CheckBoxEditor updateAlarmReadouts;
	
	protected final static Symbol MEMORY_ENABLED_ = Symbol.intern("MEMORY-ENABLED");
	protected final static Symbol UPDATE_ALARM_READOUTS_= Symbol.intern("UPDATE-ALARM-READOUTS");

	
}