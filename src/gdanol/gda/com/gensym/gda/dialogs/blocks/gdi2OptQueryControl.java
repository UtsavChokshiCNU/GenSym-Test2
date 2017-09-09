package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdi2OptQueryControl extends BlocksDialog {
	
	public gdi2OptQueryControl() {}

	public gdi2OptQueryControl(java.awt.Frame frame) {
		super(frame);


		messageText = new TextAreaEditor();
		dpanel.placeAttributeEditor(messageText,MESSAGE_TEXT_, 0);
		
		option1Description = new TextAreaEditor();
		dpanel.placeAttributeEditor(option1Description,OPTION_1_DESCRIPTION_, 1);

		option2Description = new TextAreaEditor();
		dpanel.placeAttributeEditor(option2Description,OPTION_2_DESCRIPTION_, 2);

		defaultOption = new SpinEditor(0, 2, 1);
		dpanel.placeAttributeEditor(defaultOption,
			DEFAULT_OPTION_, dpanel.integerFieldType, 4);
			
		displayRouting = new ComboBoxEditor();		
		dpanel.placeAttributeEditor(displayRouting,
			DISPLAY_ROUTING_, dpanel.symbolFieldType, 5);

		overrideTimeout=new IntervalEditor();
		dpanel.placeAttributeEditor(overrideTimeout,OVERRIDE_TIMEOUT_, 6);
		
	}
	
	protected TextAreaEditor messageText;
	protected TextAreaEditor option1Description;
	protected TextAreaEditor option2Description;
	protected SpinEditor defaultOption;
	protected ComboBoxEditor displayRouting;
	protected IntervalEditor overrideTimeout;

	protected final static Symbol MESSAGE_TEXT_= Symbol.intern("MESSAGE-TEXT");
	protected final static Symbol OPTION_1_DESCRIPTION_= Symbol.intern("OPTION-1-DESCRIPTION");
	protected final static Symbol OPTION_2_DESCRIPTION_= Symbol.intern("OPTION-2-DESCRIPTION");
	protected final static Symbol DEFAULT_OPTION_= Symbol.intern("DEFAULT-OPTION");
	protected final static Symbol DISPLAY_ROUTING_= Symbol.intern("DISPLAY-ROUTING");
	protected final static Symbol OVERRIDE_TIMEOUT_= Symbol.intern("OVERRIDE-TIMEOUT");

}