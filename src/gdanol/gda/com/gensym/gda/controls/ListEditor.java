
package com.gensym.gda.controls;

import java.awt.BorderLayout;
import java.util.Iterator;
import java.io.IOException;

import javax.swing.JScrollPane;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.controls.FieldType;
import com.gensym.beansruntime.StringVector;
import com.gensym.message.Trace;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.util.NoSuchAttributeException;


/**
ListEditor uses {@link G2ListAsComboBox} as AttributeEditor.
@see G2ListAsComboBox
*/
public class ListEditor extends AbstractAttributeEditor {

    public ListEditor() {
		list = new G2ListAsComboBox();
		add(new JScrollPane(list), BorderLayout.CENTER);		
		setAttributeEditor(list);
		setVisibleRowCount(4);
	}

	public G2ListAsComboBox getList() {return list;}

  public void setFieldType(FieldType type) {list.setFieldType(type);}

	public FieldType getFieldType() { return list.getFieldType();}
	
	public void setVisibleRowCount(int visibleRowCount) {
		list.setVisibleRowCount(visibleRowCount);
	}

	public int getVisibleRowCount() {
		return list.getVisibleRowCount();
	}
	
	public void setEnabled(boolean enabled) {
		super.setEnabled(enabled);
		list.setEnabled(enabled);
	}

	
	public void objectUpdated(ObjectUpdateEvent event) {		
		Structure values = (Structure) event.getUpdatedObject();
		try {
			Object attrValue = values.getAttributeValue(getAttribute());
			if (attrValue instanceof Object[]) {
				Sequence elements=  (Sequence) ((Object[])attrValue)[1];
				StringVector strings= new StringVector();
				for (Iterator i=elements.iterator();i.hasNext();) { 
					try {					
						strings.add(getFieldType().objectToString(i.next()));
					} catch (IOException e ) {
						Trace.exception(e);
					}				
				}
				list.setChoices(strings);
				values.setAttributeValue(getAttribute(), ((Object[])attrValue)[0]);
			}
			if(getDisableIfNotUpdated()) setEnabled(true);
			editor.objectUpdated(event);			
		} catch (NoSuchAttributeException e) {
			if(getDisableIfNotUpdated()) setEnabled(false);
		}
	}
	/**
	attributeStructure should contain ELEMENTS attribute of type 
	{@link com.gensym.util.Sequence}.
	Method sets as choices of combobox the elements of this Sequence.
	*/
	public void initialize(Structure attributeStructure) {
		if (attributeStructure == null)
			return;
		Sequence elements= (Sequence) 
			attributeStructure.getAttributeValue(ELEMENTS_, null);
		if (elements!=null) {
			StringVector strings= new StringVector();
			for (Iterator i=elements.iterator();i.hasNext();) { 
				try {					
					strings.add(getFieldType().objectToString(i.next()));
				} catch (IOException e ) {
					Trace.exception(e);
				}				
			}
			list.setChoices(strings);
		}
	}

	protected G2ListAsComboBox list;
	
    private final static Symbol ELEMENTS_ = Symbol.intern("ELEMENTS");

}