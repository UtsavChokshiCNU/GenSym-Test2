package com.gensym.gda.dialogs.other;

import java.awt.Frame;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectChangeEvent;
import com.gensym.gda.controls.ListEditor;

public class gdlGenericListSelection extends com.gensym.gda.dialogs.gdaDialog {
	
    public gdlGenericListSelection(java.awt.Frame frame, String title, 
    	String prompt, int defaultIndex, Sequence initialvalues) {
    	super(frame);
    	setTitle(title);
    	setModal(true);
       	apply.setVisible(false);
 	
       	dpanel=new com.gensym.gda.dialogs.gdaPanel(this);
       	scrollPane.setViewportView(dpanel);
    	list = new ListEditor();
    	dpanel.placeAttributeEditor(list, prompt, LIST_SELECTION_, 
    		dpanel.symbolFieldType, 0);
    	
    	Structure structure = new Structure();
    	structure.setAttributeValue(LIST_SELECTION_, new Object[]{
    		defaultIndex==-1 ? null : initialvalues.get(defaultIndex), initialvalues});
    	list.objectUpdated(new ObjectUpdateEvent(this, structure));

    	button=CANCEL;
    	try {
			value=defaultIndex == -1 ? "" : list.getFieldType().
				objectToString(initialvalues.get(defaultIndex));
    	} catch(java.io.IOException error) {}
		
		pack();
		setLocationRelativeTo(frame);
		
	}

	public void objectChanged(ObjectChangeEvent e) {
		try {
			value=list.getFieldType().objectToString(e.getChangedObject());
		} catch (java.io.IOException error) {}
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
	
	protected ListEditor list;
	
	protected static String OK = "OK";
	protected static String CANCEL = "Cancel";
	protected static final Symbol LIST_SELECTION_=Symbol.intern("LIST-SELECTION");
	protected com.gensym.gda.dialogs.gdaPanel dpanel;
}