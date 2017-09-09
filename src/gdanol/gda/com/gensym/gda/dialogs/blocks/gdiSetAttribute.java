
package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiSetAttribute extends BlocksDialog{


	public gdiSetAttribute() {}

	public gdiSetAttribute(java.awt.Frame frame) {
		super(frame);

		targetAttribute = new ListEditor();
		dpanel.placeAttributeEditor(targetAttribute,
			 TARGET_ATTRIBUTE_, dpanel.symbolFieldType, 0);

	}

	protected ListEditor targetAttribute;

	protected final static Symbol TARGET_ATTRIBUTE_ = Symbol.intern("TARGET-ATTRIBUTE");
	
}