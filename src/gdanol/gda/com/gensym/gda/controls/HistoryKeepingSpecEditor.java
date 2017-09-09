
package com.gensym.gda.controls;

import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import javax.swing.border.LineBorder;

import javax.swing.JLabel;

import com.gensym.controls.AttributeEditor;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectChangeEvent;

import com.gensym.util.Structure;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Symbol;
import com.gensym.controls.FieldType;


/**Is used for editng the history-keeping-spec attribute of variable-or-parameter.
Contains Points (G2SpinField) and Time(IntervalField) fields. if Points is greater than 0 
the clause "with number of data points=<Points>" is concluded.
if Time is greater 0 seconds then the clause "maximum age of data points=<Time>" is concluded.
If both Points and Time are greater 0 then both clauses are concluded.
*/
public class HistoryKeepingSpecEditor extends AbstractAttributeEditor {

    public HistoryKeepingSpecEditor() {
		currentValue = new Structure();
    	GridBagLayout layout = new GridBagLayout();
    	setLayout(layout);
    	setBorder(LineBorder.createBlackLineBorder());
    	GridBagConstraints c = new GridBagConstraints();
		c.insets=new Insets(5, 5, 5, 5);    	
    	pointsLabel = new JLabel(localize("HistoryKeepingPoints"));
    	timeLabel = new JLabel(localize("HistoryKeepingTime"));
    	c.anchor = GridBagConstraints.EAST;
    	layout.setConstraints(pointsLabel, c);
		add(pointsLabel);

		c.gridy=1;
    	layout.setConstraints(timeLabel, c);
		add(timeLabel);

		pointsField = new G2SpinField(0, Integer.MAX_VALUE, 1);
		pointsField.setAttribute(MAX_NUMBER_);
		pointsField.addObjectChangeListener(changeListener);
		timeField = new IntervalField();
		timeField.setAttribute(MAX_AGE_);
		timeField.addObjectChangeListener(changeListener);

		c.gridx = 1;
	    c.weightx = 1.0;
    	c.fill = GridBagConstraints.HORIZONTAL;
	    c.anchor = GridBagConstraints.WEST;
    	
    	layout.setConstraints(timeField, c);
		add(timeField);
		
		c.gridy = 0;
    	layout.setConstraints(pointsField, c);
		add(pointsField);

	}

	public void objectUpdated(ObjectUpdateEvent event) {		
		Structure values = (Structure) event.getUpdatedObject();
		try {
			Object value = values.getAttributeValue(getAttribute());
			if(getDisableIfNotUpdated()) setEnabled(true);
			updateFields(value);
		} catch (NoSuchAttributeException e) {
			if(getDisableIfNotUpdated()) setEnabled(false);
		}
	}

	protected void updateFields(Object valueObject) {
		ObjectUpdateEvent event;
		if (valueObject instanceof Structure) {
			Structure value=(Structure) valueObject;
			currentValue=value;
			
			try {
				pointsValue = value.getAttributeValue(MAX_NUMBER_);
			} catch (NoSuchAttributeException e) {
				pointsValue = nullInteger;
				value.setAttributeValue(MAX_NUMBER_, nullInteger);
			}

			try {
				timeValue = value.getAttributeValue(MAX_AGE_);
			} catch (NoSuchAttributeException e) {
				timeValue = nullInteger;
				value.setAttributeValue(MAX_AGE_, nullInteger);
			}
				
			event = new ObjectUpdateEvent(this, value);
		} else {
			Structure structure = new Structure();
			structure.setAttributeValue(MAX_NUMBER_, nullInteger);
			structure.setAttributeValue(MAX_AGE_, nullInteger);
			currentValue=new Structure();
			pointsValue=nullInteger;
			timeValue=nullInteger;
			event = new ObjectUpdateEvent(this, structure);
		}
		pointsField.objectUpdated(event);
		timeField.objectUpdated(event);
	}


    public void setFieldType(FieldType type) {}
	public FieldType getFieldType() { return null;}

	public void setEnabled(boolean enabled) {
		super.setEnabled(enabled);
		pointsLabel.setEnabled(enabled);
		timeLabel.setEnabled(enabled);
		pointsField.setEnabled(enabled);
		timeField.setEnabled(enabled);
	}

	protected ObjectChangeListener changeListener = new ObjectChangeListener() {
		public void objectChanged(ObjectChangeEvent e) {
			AttributeEditor editor= (AttributeEditor)e.getSource();
			Object value = e.getChangedObject();
			if (value.equals(nullInteger)) {
				currentValue.deleteAttribute(editor.getAttribute());
			} else {
				currentValue.setAttributeValue(editor.getAttribute(), value);
			}
	
			fireObjectChange(currentValue);
		}
	};

	protected JLabel pointsLabel;
	protected JLabel timeLabel;
	protected G2SpinField pointsField;
	protected IntervalField timeField;	
	
	protected Object pointsValue;
	protected Object timeValue;

	protected static Integer nullInteger = new Integer(0);
	protected Structure currentValue;	
	
	protected final static Symbol MAX_NUMBER_ = 
		Symbol.intern("MAXIMUM-NUMBER-OF-DATA-POINTS");
	protected final static Symbol MAX_AGE_ = 
		Symbol.intern("MAXIMUM-AGE-OF-DATA-POINTS");
			
}