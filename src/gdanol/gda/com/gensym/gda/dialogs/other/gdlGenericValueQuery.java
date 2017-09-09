package com.gensym.gda.dialogs.other;

import java.awt.Frame;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectChangeEvent;
import com.gensym.gda.controls.*;
import com.gensym.ntw.TwAccess;

public class gdlGenericValueQuery extends com.gensym.gda.dialogs.gdaDialog {
	
    public gdlGenericValueQuery(java.awt.Frame frame, 
    	String prompt, String initialValue, Symbol formatspec, TwAccess connection) {
    		
    	super(frame);
    	apply.setVisible(false);
	   	setModal(true);
	   	setConnection(connection);
	   	setTitle(prompt);
    	button=CANCEL;
    	
       	dpanel=new com.gensym.gda.dialogs.gdaPanel(this);
       	scrollPane.setViewportView(dpanel);
	   	
    	formatSpec=formatspec;
    	field = new TextFieldEditor();
    	dpanel.placeAttributeEditor(field, null, GENERIC_VALUE_, 
    		nonReservedFieldType, 0);
    	setFieldType(formatSpec);
    	
    	Structure structure = new Structure();
    	try {
			value=field.getFieldType().stringToObject(initialValue);		
    	} catch (Exception error) {
    		value = Symbol.intern("G2");
    	}
   		structure.setAttributeValue(GENERIC_VALUE_, value);
    	field.objectUpdated(new ObjectUpdateEvent(this, structure));

		pack();
		setLocationRelativeTo(frame);
		
	}

	protected void setFieldType(Symbol formatSpec) {
		if (formatSpec.equals(GDI_NAME_FORMAT_SPEC_))
			field.setFieldType(new ValidG2NameFieldType(connection));
			
	}
		
	public void objectChanged(ObjectChangeEvent e) {
		value=e.getChangedObject();
	}
	
	public Sequence selectValue() {
		show();
		return getResult();
	}
	
	public boolean applyDialog() {
		if (!editorsAreValid())
			return false;
			
		button=OK;
		return true;
	}
		
	public Sequence getResult() {
		Sequence sequence = new Sequence(2);
		sequence.add(value);
		sequence.add(button);
		return sequence;
	}

	protected Object value;
	protected String button;
	
	protected TextFieldEditor field;
	protected Symbol formatSpec;

	protected static String OK = "OK";
	protected static String CANCEL = "Cancel";
	protected static final Symbol GENERIC_VALUE_=Symbol.intern("GENERIC-VALUE");
	protected static final Symbol GDI_NON_RESERVED_SYMBOL_OR_NONE_FORMAT_SPEC_ = 
		Symbol.intern("GDI-NON-RESERVED-SYMBOL-OR-NONE-FORMAT-SPEC");
	protected static final Symbol GDI_NAME_FORMAT_SPEC_ = Symbol.intern("GDI-NAME-FORMAT-SPEC");
	protected static final NonReservedSymbolOrNoneFieldType nonReservedFieldType = 
		new NonReservedSymbolOrNoneFieldType();
	protected com.gensym.gda.dialogs.gdaPanel dpanel;
}