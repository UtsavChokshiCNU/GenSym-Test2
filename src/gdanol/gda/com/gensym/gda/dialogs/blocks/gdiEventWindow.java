package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.beansruntime.StringVector;

import com.gensym.gda.controls.RadioBoxEditor;

public class gdiEventWindow extends gdiLogicGate {
	
	public gdiEventWindow() {}

	public gdiEventWindow(java.awt.Frame frame) {
		super(frame);

		triggeringPort=new RadioBoxEditor();
		triggeringPort.setLabels(new StringVector(new String[] {
			"input 1", "input 2", "either"}));
		triggeringPort.setMembers(new StringVector(new String[] {
			"input-1", "input-2", "either"}));
		triggeringPort.setRowsAndColumns(1, 3);
		dpanel.placeAttributeEditor(triggeringPort, TRIGGERING_PORT_,
			dpanel.symbolFieldType, 5);
		
		intervalPanel = UncertaintyBoundPanel.createIntervalUncertaintyPanel(this);
		dpanel.addPanel(intervalPanel, null, 2);

	}
	
	
	protected RadioBoxEditor triggeringPort;
	protected UncertaintyBoundPanel intervalPanel;

	protected final static Symbol TRIGGERING_PORT_ = Symbol.intern("TRIGGERING-PORT");

}