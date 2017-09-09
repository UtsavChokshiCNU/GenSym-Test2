package com.gensym.gda.dialogs.preferences;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;
import com.gensym.ntw.TwAccess;

public class gdaLoggingManagerDlg extends gdabasicLoggingManagerDlg {
	
	public gdaLoggingManagerDlg() {}

	public gdaLoggingManagerDlg(java.awt.Frame frame) {
		super(frame);


		gdaLogEventsIncrementally = new CheckBoxEditor();
		dpanel.placeAttributeEditor(gdaLogEventsIncrementally, 
			GDA_LOG_EVENTS_INCREMENTALLY_, 5);

		gdaLogAdvice = new CheckBoxEditor();
		dpanel.placeAttributeEditor(gdaLogAdvice, GDA_LOG_ADVICE_, 7);

		gdaLogExplanations = new CheckBoxEditor();
		dpanel.placeAttributeEditor(gdaLogExplanations, GDA_LOG_EXPLANATIONS_, 8);

	}

	protected CheckBoxEditor gdaLogEventsIncrementally;
	protected CheckBoxEditor gdaLogAdvice;
	protected CheckBoxEditor gdaLogExplanations;
	
	protected final static Symbol GDA_LOG_EVENTS_INCREMENTALLY_=
		Symbol.intern("GDA-LOG-EVENTS-INCREMENTALLY");
	protected final static Symbol GDA_LOG_ADVICE_=Symbol.intern("GDA-LOG-ADVICE");
	protected final static Symbol GDA_LOG_EXPLANATIONS_=Symbol.intern("GDA-LOG-EXPLANATIONS");

}