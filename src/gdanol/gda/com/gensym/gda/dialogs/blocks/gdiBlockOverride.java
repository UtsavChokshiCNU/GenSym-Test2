package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.beansruntime.StringVector;

import com.gensym.gda.controls.*;

public class gdiBlockOverride extends BlocksDialog {
	
	public gdiBlockOverride() {}

	public gdiBlockOverride(java.awt.Frame frame) {
		super(frame);
				
		overrideMode = new RadioBoxEditor();
		overrideMode.setLabels(new StringVector());
		overrideMode.setMembers(new StringVector(new String[]{"automatic", "manual"}));
		overrideMode.setRowsAndColumns(1, 2);
		dpanel.placeAttributeEditor(overrideMode, 
			OVERRIDE_MODE_, dpanel.symbolFieldType, 0);
		
		overrideStatus = new StatusComboBoxEditor(StatusComboBoxEditor.SMALL_UNKNOWN);
		dpanel.placeAttributeEditor(overrideStatus, OVERRIDE_STATUS_, 1);
		
		overrideBelief = new SpinOrNoneEditor(0, 1, 0.1);
		dpanel.placeAttributeEditor(overrideBelief, OVERRIDE_BELIEF_, 2);
		
		overrideNumeric = new SpinOrNoneEditor();
		dpanel.placeAttributeEditor(overrideNumeric, OVERRIDE_NUMERIC_, 3);

		overrideSymbol = new TextOrNoneEditor();
		dpanel.placeAttributeEditor(overrideSymbol, 
			OVERRIDE_SYMBOL_, dpanel.symbolFieldType, 4);

		overrideText = new TextFieldEditor();
		dpanel.placeAttributeEditor(overrideText, OVERRIDE_TEXT_, 5);
			
		multipleInvocations = new MIRadioEditor(true, false);
		dpanel.placeAttributeEditor(multipleInvocations, MULTIPLE_INVOCATIONS_, 6);
		
		displayRouting = new ComboBoxEditor();
		dpanel.placeAttributeEditor(displayRouting, 
			DISPLAY_ROUTING_, dpanel.symbolFieldType, 7);
		
	}
	

	
	protected RadioBoxEditor overrideMode;
	protected StatusComboBoxEditor overrideStatus;
	protected SpinOrNoneEditor overrideBelief;
	protected SpinOrNoneEditor overrideNumeric;
	protected TextOrNoneEditor overrideSymbol;
	protected TextFieldEditor overrideText;
	protected MIRadioEditor multipleInvocations;
	protected ComboBoxEditor displayRouting;
	
	protected final static Symbol OVERRIDE_MODE_= Symbol.intern("OVERRIDE-MODE");
	protected final static Symbol OVERRIDE_STATUS_= Symbol.intern("OVERRIDE-STATUS");
	protected final static Symbol OVERRIDE_BELIEF_= Symbol.intern("OVERRIDE-BELIEF");
	protected final static Symbol OVERRIDE_NUMERIC_= Symbol.intern("OVERRIDE-NUMERIC");
	protected final static Symbol OVERRIDE_SYMBOL_= Symbol.intern("OVERRIDE-SYMBOL");
	protected final static Symbol OVERRIDE_TEXT_= Symbol.intern("OVERRIDE-TEXT");
	protected final static Symbol MULTIPLE_INVOCATIONS_= Symbol.intern("MULTIPLE-INVOCATIONS");
	protected final static Symbol DISPLAY_ROUTING_= Symbol.intern("DISPLAY-ROUTING");

}