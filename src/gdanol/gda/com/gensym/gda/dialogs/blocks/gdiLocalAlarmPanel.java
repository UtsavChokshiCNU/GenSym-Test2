package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiLocalAlarmPanel extends BlocksDialog {
	
	public gdiLocalAlarmPanel() {}

	public gdiLocalAlarmPanel(java.awt.Frame frame) {
		super(frame);

		nameOfViewedAlarm = new ComboBoxEditor();
		dpanel.placeAttributeEditor(nameOfViewedAlarm,
			NAME_OF_VIEWED_ALARM_,dpanel.symbolFieldType, 0);

	}

	protected ComboBoxEditor nameOfViewedAlarm;

	protected final static Symbol NAME_OF_VIEWED_ALARM_= 
		Symbol.intern("NAME-OF-VIEWED-ALARM");
	

}