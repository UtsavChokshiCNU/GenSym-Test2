package com.gensym.gda.controls;

import com.gensym.widgets.Spin;
import java.awt.Component;
import java.awt.event.ActionEvent;

/**
When pressing mouse on spin button the textWidget of Spin is not get the focus.
To avoid this at the {@link #actionPerformed(ActionEvent)} method the focus for textWidget is requested.
*/
public class FocusedSpin extends Spin {

	public FocusedSpin() {}
	
	public FocusedSpin(Component c) {super(c);}	
	
	public void actionPerformed(ActionEvent e) {
		if (!getSpinController().getTextWidget().hasFocus())
			getSpinController().getTextWidget().requestFocus();
		super.actionPerformed(e);
	}
}