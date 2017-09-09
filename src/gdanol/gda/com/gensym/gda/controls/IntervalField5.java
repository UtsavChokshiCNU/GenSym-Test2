package com.gensym.gda.controls;

import java.awt.event.FocusEvent;

public class IntervalField5 extends IntervalField1 {	
	
	public IntervalField5 () {
		super(0, true);
	}
	
	public void focusGained(FocusEvent e) {
		super.focusGained(e);
		Object source = e.getSource();
		if (source ==intervalField[0]) 
			spin.setMaxValue(MAXIMUM_G2_INT);
		if (source ==intervalField[1]) 
			spin.setMaxValue(6);
		else if (e.getSource()==intervalField[2]) 
			spin.setMaxValue(23);
		else if (e.getSource()==intervalField[3]) 
			spin.setMaxValue(59);
		else if (e.getSource()==intervalField[4]) 
			spin.setMaxValue(59);
	}
}