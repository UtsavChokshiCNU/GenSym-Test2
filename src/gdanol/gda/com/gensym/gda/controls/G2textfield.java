
package com.gensym.gda.controls;

import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectChangeEvent;
import com.gensym.jcontrols.G2TextField;
import com.gensym.widgets.TextWidget;
import com.gensym.controls.FieldType;
import com.gensym.types.IntegerType;

import java.awt.event.KeyEvent;
import java.awt.event.FocusEvent;
import javax.swing.KeyStroke;


/**The subclass of com.gensym.jcontrols.G2TextField implemented for changing
*invalid value to previous one and for implementing TextWidget interface 
*(used by G2SpinField).
*/
public class G2textfield extends G2TextField implements TextWidget{

    public G2textfield() {
    	isvalid=true;
		addObjectChangeListener(new objectChangeListener());
		KeyStroke enter = KeyStroke.getKeyStroke(KeyEvent.VK_ENTER, 0);
		getKeymap().removeKeyStrokeBinding(enter);
		setShowQuotesForTextType(false);
    }
    
    protected void fireObjectChangeOnContents() {
    	isvalid=false;
		super.fireObjectChangeOnContents();
		if(!isvalid) {
			setText(oldtext);
   		} else
			oldtext = getText();
    }
    
    public boolean isValid() {return isvalid;}
    
    public void setValid(boolean valid) {isvalid=valid;}
    
    public void focusGained (FocusEvent focusevent) {
    	super.focusGained(focusevent);
		oldtext = getText();
    }
    public void focusLost(FocusEvent focusevent) {
    	super.focusLost(focusevent);
    }
        
    public void setFieldType(FieldType fieldtype) {
    	super.setFieldType(fieldtype);
    	
    	Object obj = fieldtype.newInstance();
    	if (obj==null) return;
    	
		if(fieldtype.isNumeric()) {
			Number number = (Number) obj;
			if (number.doubleValue()<getLowerLimit())
				setDefaultContents(getDefaultFromValue(getLowerLimit()));
			else if (number.doubleValue()>getUpperLimit())
				setDefaultContents(getDefaultFromValue(getUpperLimit()));
			else try {
				setDefaultContents(fieldtype.objectToString(obj));
			} catch (java.io.IOException e) {}
		} else try {
			setDefaultContents(fieldtype.objectToString(obj));
		} catch (java.io.IOException e) {}
		
        if(fieldtype.isNumeric()) {
            if (fieldtype.getType() instanceof IntegerType)
                setDocument(new IntegerDocument());
            else
                setDocument(new FloatDocument());
        }		
	}
	
	
	private String getDefaultFromValue(double value) {
		try {
			return getFieldType().objectToString(new Integer((int)value));
		} catch (java.io.IOException e) {
			return getDefaultContents();
		}
	}
	
	public void setUpperLimit(double limit) {
		super.setUpperLimit(limit);
		try {
			Object obj = getFieldType().stringToObject(getDefaultContents());
			if(getFieldType().isNumeric()) {
				Number number = (Number) obj;
				if (((Number) obj).doubleValue()>limit)
					setDefaultContents(getDefaultFromValue(limit));
			}
		} catch (Exception e) {}
	}

	public void setLowerLimit(double limit) {
		super.setLowerLimit(limit);
		try {
			Object obj = getFieldType().stringToObject(getDefaultContents());
			if(getFieldType().isNumeric()) {
				Number number = (Number) obj;
				if (((Number) obj).doubleValue()<limit)
					setDefaultContents(getDefaultFromValue(limit));
			}
		} catch (Exception e) {}
	}


	protected boolean isvalid;
	protected String oldtext;

	class objectChangeListener implements ObjectChangeListener, java.io.Serializable {
			public objectChangeListener() {}		
			public void objectChanged(ObjectChangeEvent e) {isvalid = true;}		
	}
	
}