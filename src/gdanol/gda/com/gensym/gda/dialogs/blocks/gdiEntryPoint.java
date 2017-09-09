
package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.beansruntime.StringVector;

import com.gensym.gda.controls.*;

public class gdiEntryPoint extends BlocksDialog {
	
	public gdiEntryPoint() {}

	public gdiEntryPoint(java.awt.Frame frame) {
		super(frame);

		nameOfSensor = new ComboBoxEditor();
		dpanel.placeAttributeEditor(nameOfSensor, 
			 NAME_OF_SENSOR_, dpanel.symbolFieldType, 0);

		dataSource = new RadioBoxEditor();
		StringVector members = new StringVector(new String[] {"embedded", "external"});
		dataSource.setLabels(members);
		dataSource.setMembers(members);
		dataSource.setRowsAndColumns(1, 2);
		dpanel.placeAttributeEditor(dataSource, 
			DATA_SOURCE_, dpanel.symbolFieldType, 1);

	}

	protected ComboBoxEditor nameOfSensor;
	protected RadioBoxEditor dataSource;

    protected final static Symbol NAME_OF_SENSOR_ = Symbol.intern("NAME-OF-SENSOR");
	protected final static Symbol DATA_SOURCE_ = Symbol.intern("DATA-SOURCE");
	
	
	//used by childs
	protected final static Symbol VALUE_ON_INITIALIZATION_ = 
		Symbol.intern("VALUE-ON-INITIALIZATION");

}