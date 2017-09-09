package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.beansruntime.StringVector;

import com.gensym.gda.controls.*;

public class gdiResidual extends gdiHistoricalBlock {
	
	public gdiResidual() {}

	public gdiResidual(java.awt.Frame frame) {
		super(frame);

		errorType = new RadioBoxEditor();
		errorType.setLabels(new StringVector());
		errorType.setMembers(new StringVector(
			new String[]{"sum", "sse", "abs"}));
		errorType.setRowsAndColumns(1, 3);
		dpanel.placeAttributeEditor(errorType,
			ERROR_TYPE_, dpanel.symbolFieldType, 2);
			
		externalDatasource = new ComboBoxEditor();
		dpanel.placeAttributeEditor(externalDatasource,
			EXTERNAL_DATASOURCE_,dpanel.symbolFieldType, 3);
		
		concurrencyWindow = new IntervalEditor();
		dpanel.placeAttributeEditor(concurrencyWindow,CONCURRENCY_WINDOW_, 4);
	}


	protected RadioBoxEditor errorType;
	
	/**
	   How about quantity? (gdi-quantity-or-name-or-expression-or-none-format-spec)
	 */
	protected ComboBoxEditor externalDatasource;
	protected IntervalEditor concurrencyWindow;

	protected final static Symbol ERROR_TYPE_ = Symbol.intern("ERROR-TYPE");
	protected final static Symbol EXTERNAL_DATASOURCE_ = 
		Symbol.intern("EXTERNAL-DATASOURCE");
	protected final static Symbol CONCURRENCY_WINDOW_ = 
		Symbol.intern("CONCURRENCY-WINDOW");

}