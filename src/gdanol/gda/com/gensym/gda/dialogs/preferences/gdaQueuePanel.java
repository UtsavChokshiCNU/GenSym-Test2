package com.gensym.gda.dialogs.preferences;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdaQueuePanel extends gdiQueuePanel {
	
	public gdaQueuePanel(PreferencesDialog dialog) {
		super(dialog);
		gqmDefaultPriority.setVisible(false);
		gqmDefaultPriority.getLabel().setVisible(false);
		gdaRecurringEntryClass =new ComboBoxEditor();
		placeAttributeEditor(gdaRecurringEntryClass,
			GDA_RECURRING_ENTRY_CLASS_, symbolFieldType, 1);
		
		gdaAutogenerateExplanations=new CheckBoxEditor();
		placeAttributeEditor(gdaAutogenerateExplanations,
			GDA_AUTOGENERATE_EXPLANATION_, 11);
	}

	protected ComboBoxEditor gdaRecurringEntryClass;
	protected CheckBoxEditor gdaAutogenerateExplanations;
	
	protected final static Symbol GDA_RECURRING_ENTRY_CLASS_
		= Symbol.intern("GDA-RECURRING-ENTRY-CLASS");	
	protected final static Symbol GDA_AUTOGENERATE_EXPLANATION_
		= Symbol.intern("GDA-AUTOGENERATE-EXPLANATION");	
}