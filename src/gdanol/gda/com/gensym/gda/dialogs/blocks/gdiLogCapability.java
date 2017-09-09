
package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;
import com.gensym.ntw.TwAccess;

public class gdiLogCapability extends BlocksDialog{


	public gdiLogCapability () {}

	public gdiLogCapability (java.awt.Frame frame) {
		super(frame);

		portName= new ComboBoxEditor();
		dpanel.placeAttributeEditor(portName,
			 PORT_NAME_, dpanel.symbolFieldType, 0);

		logEntriesTo = new FileEditor();
		dpanel.placeAttributeEditor(logEntriesTo,LOG_ENTRIES_TO_,1);
		logEntriesTo.setFileDialogTitle(localize("logFilesToDialogTitle"));

		logOn = new StatusComboBoxEditor(StatusComboBoxEditor.ALL_CHANGES);
		dpanel.placeAttributeEditor(logOn,LOG_ON_, 2);
		
	}


	public void setConnection(TwAccess connection) {
		super.setConnection(connection);
		logEntriesTo.setConnection(connection);
	}
	
	protected ComboBoxEditor portName;
	protected FileEditor logEntriesTo;
	protected ComboBoxEditor logOn;

	protected final static Symbol PORT_NAME_ = Symbol.intern("PORTNAME");
	protected final static Symbol LOG_ENTRIES_TO_ = Symbol.intern("LOG-ENTRIES-TO");
	protected final static Symbol LOG_ON_ = Symbol.intern("LOG-ON");
	
}