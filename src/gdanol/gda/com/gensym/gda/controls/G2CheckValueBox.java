
package com.gensym.gda.controls;

import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.jcontrols.G2Checkbox;
import java.awt.event.ItemEvent;

import java.lang.Object;

/**
This control allows to set any java.lang.Object as on and off value.
By default on value is Boolean.TRUE, and off value is Boolean.FALSE as in 
com.gensym.jcontrols.G2Checkbox.
*/
public class G2CheckValueBox extends G2Checkbox
{

    public G2CheckValueBox()
    {
		onvalue=Boolean.TRUE;
		offvalue=Boolean.FALSE;
		setText("");
    }

	public void setOnvalue(Object value) {onvalue = value;}

	public void setOffvalue(Object value) {offvalue = value;}
	
	public Object getOnvalue() {return onvalue;}
	
	public Object getOffvalue() {return offvalue;}

    public void itemStateChanged(ItemEvent itemevent)
    {
        Object obj = itemevent.getSource();
        if(obj == this && sendNextChangeToG2)
        {
            fireObjectChange(isSelected() ? onvalue : offvalue);
        }
    }

    public void objectUpdated(ObjectUpdateEvent objectupdateevent)
    {
        try
        {
            sendNextChangeToG2 = false;
            Object obj = objectupdateevent.getUpdatedValue(getAttribute(), getDefaultContents());
            setState(obj.equals(onvalue));
        }
        finally
        {
            sendNextChangeToG2 = true;
        }
    }

	protected Object onvalue;
	protected Object offvalue;
	protected boolean sendNextChangeToG2;
}