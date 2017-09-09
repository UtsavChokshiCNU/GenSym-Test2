
package com.gensym.gda.controls;

import java.awt.BorderLayout;
import java.util.Iterator;
import java.io.IOException;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import javax.swing.JPanel;

import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.jcontrols.G2ComboBox;
import com.gensym.controls.FieldType;
import com.gensym.beansruntime.StringVector;
import com.gensym.message.Trace;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.util.NoSuchAttributeException;

/**
ComboBoxEditor uses com.gensym.jcontrols.G2ComboBox as AttributeEditor.
@see com.gensym.jcontrols.G2ComboBox
*/
public class ComboBoxEditor extends AbstractAttributeEditor {

    public ComboBoxEditor() {
		combobox = new G2ComboBox();
/*		JPanel panel = new JPanel(new BorderLayout());
		setLayout(layout = new GridBagLayout());
		c=new GridBagConstraints();
		c.fill=GridBagConstraints.HORIZONTAL;
		c.weightx=1.0;
		layout.setConstraints(panel, c);
		add(panel);		
		panel.add(combobox, BorderLayout.CENTER);
*/		
		add(combobox, BorderLayout.CENTER);		
		setAttributeEditor(combobox);
	}

	public G2ComboBox getComboBox() {return combobox;}

    public void setFieldType(FieldType type) {combobox.setFieldType(type);}

	public FieldType getFieldType() { return combobox.getFieldType();}

	public void setEnabled(boolean enabled) {
		super.setEnabled(enabled);
		combobox.setEnabled(enabled);
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
				combobox.setChoices(strings);
				values.setAttributeValue(getAttribute(), ((Object[])attrValue)[0]);
			}
			if(getDisableIfNotUpdated()) setEnabled(true);
			editor.objectUpdated(event);			
		} catch (NoSuchAttributeException e) {
			if(getDisableIfNotUpdated()) setEnabled(false);
		}
	}
	
	/**
	attributeStructure should contain ELEMENTS attribute of type sequence.
	Method sets the elements of this sequence as choices of conbobox.
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
			combobox.setChoices(strings);
		}
	}

	// combobox methods;
	public void setChoices(StringVector stringvector) {combobox.setChoices(stringvector);}
	public StringVector getChoices() {return combobox.getChoices();}
	
	protected G2ComboBox combobox;
	
    private final static Symbol ELEMENTS_ = Symbol.intern("ELEMENTS");
	protected GridBagLayout layout;
	protected GridBagConstraints c;

}