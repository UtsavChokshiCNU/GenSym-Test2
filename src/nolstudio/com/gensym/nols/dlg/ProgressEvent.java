package com.gensym.nols.dlg;

import java.lang.*;

public class ProgressEvent {
	private int increment=0;

	public ProgressEvent() {
		increment++;
	}

	public int getIncrementValue() {
		return increment;
	}
}