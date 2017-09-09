
package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiInputSelection extends BlocksDialog{


	public gdiInputSelection () {}

	public gdiInputSelection (java.awt.Frame frame) {
		super(frame);

		useExpiredInputs = CheckBoxEditor.createYesNoCheckBox();
		dpanel.placeAttributeEditor(useExpiredInputs, USE_EXPIRED_INPUTS_, 1);

	}

	protected CheckBoxEditor useExpiredInputs;

	protected final static Symbol USE_EXPIRED_INPUTS_= Symbol.intern("USE-EXPIRED-INPUTS");
}