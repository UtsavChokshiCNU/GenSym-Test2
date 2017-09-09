package com.gensym.gda.dialogs.preferences;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gqmGeneralSettingsDlgPanel extends PreferencesPanel{
	
	public gqmGeneralSettingsDlgPanel(PreferencesDialog dialog) {
		super(dialog);

		settingClass=GQM_GENERAL_SETTING_;

		gqmDateTimeFormat = new TextFieldEditor();
		placeAttributeEditor(gqmDateTimeFormat, GQM_DATE_TIME_FORMAT_, 0);
	
		gqmDateFormat = new TextFieldEditor();
		placeAttributeEditor(gqmDateFormat, GQM_DATE_FORMAT_, 1);

		gqmTimeFormat = new TextFieldEditor();
		placeAttributeEditor(gqmTimeFormat, GQM_TIME_FORMAT_, 2);

		gqmFileTimeFormat = new TextFieldEditor();
		placeAttributeEditor(gqmFileTimeFormat, GQM_FILE_TIME_FORMAT_, 3);

		gqmOrdinationProcedure = new ComboBoxEditor();
		placeAttributeEditor(gqmOrdinationProcedure, GQM_ORDINATION_PROCEDURE_, 
			symbolFieldType, 4);
	}


	protected TextFieldEditor gqmDateTimeFormat;
	protected TextFieldEditor gqmDateFormat;
	protected TextFieldEditor gqmTimeFormat;
	protected TextFieldEditor gqmFileTimeFormat;
	protected ComboBoxEditor gqmOrdinationProcedure;

	protected final static Symbol GQM_DATE_TIME_FORMAT_=Symbol.intern("GQM-DATE-TIME-FORMAT");
	protected final static Symbol GQM_DATE_FORMAT_=Symbol.intern("GQM-DATE-FORMAT");
	protected final static Symbol GQM_TIME_FORMAT_=Symbol.intern("GQM-TIME-FORMAT");
	protected final static Symbol GQM_FILE_TIME_FORMAT_=Symbol.intern("GQM-FILE-TIME-FORMAT");
	protected final static Symbol GQM_ORDINATION_PROCEDURE_=Symbol.intern("GQM-ORDINATION-PROCEDURE");

	protected final static Symbol GQM_GENERAL_SETTING_ = Symbol.intern("GQM-GENERAL-SETTING");
}