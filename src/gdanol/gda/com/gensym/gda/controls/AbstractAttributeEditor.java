	
package com.gensym.gda.controls;

import com.gensym.controls.AttributeEditor;
import com.gensym.controls.FieldType;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectChangeEvent;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.types.G2SyntaxException;
import com.gensym.dlg.WarningDialog;
import com.gensym.message.Resource;

import java.awt.BorderLayout;
import java.beans.Beans;

import java.util.MissingResourceException;

import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JCheckBox;
import javax.swing.BoxLayout;
import javax.swing.border.BevelBorder;

/**
The root class for all controls used by gda dialogs.	
	AbstractAttributeEditor in most cases contains an instance of AttributeEditor from
	com.gensym.jcontrols package.
	
*/
public abstract class AbstractAttributeEditor extends JPanel 
	implements AttributeEditor {

    public AbstractAttributeEditor() {
		super(new BorderLayout());

        listeners = null;
        attributeName = "";
        attributeSymbol = null;
		disableIfNotUpdated=true;
    }

	//
	//AttributeEditor implementation
	//
    public synchronized void addObjectChangeListener(ObjectChangeListener objectchangelistener) {
        if(listeners == null)
            listeners = new java.util.Vector();
        listeners.addElement(objectchangelistener);
    }


	/** 
	Returns the attribute of this control.
	*/
    public Symbol getAttribute() {
		return attributeSymbol;
	}


	/** Set the value of the control to the attribute value.
	If the value for the attribute of the control is not found then this control is disabled.
	It is assumed that the editor element is AttributeEditor. Otherwise override this method.
	*/
	public void objectUpdated(ObjectUpdateEvent event) {		
		Structure values = (Structure) event.getUpdatedObject();
		try {
			values.getAttributeValue(getAttribute());
			if (disableIfNotUpdated)
				setEnabled(true);
			editor.objectUpdated(event);			
		} catch (NoSuchAttributeException e) {
			if (disableIfNotUpdated)
				setEnabled(false);
		}
	}

    public synchronized void removeObjectChangeListener(ObjectChangeListener objectchangelistener) {
        if(listeners == null) {
            return;
        } else {
            listeners.removeElement(objectchangelistener);
            return;
        }
    }

	/**
	Set the attribute for this control.
	*/
	public void setAttribute(Symbol attribute) {
		if(editor!=null) {
			editor.setAttribute(attribute);
		}

		attributeSymbol = attribute;
		attributeName = attribute.toString();
	}

	//own methods

	/**
	Returns real control if it is AttributeEditor, else null
	@see #setAttributeEditor(AttributeEditor) setAttributeEditor
	*/
	public AttributeEditor getAttributeEditor() {return editor;}

	/** 
	if real control is AttributeEditor then use this method to
	register it in AbstractAttributeEditor.
	@see #getAttributeEditor() getAttributeEditor
	*/
	public void setAttributeEditor(AttributeEditor e) {
		editor = e;
		editor.addObjectChangeListener(new objectChangeListener());
	}

    public abstract void setFieldType(FieldType type);

	public abstract FieldType getFieldType();

	public void setLabel(JLabel l) {label=l;}

	public JLabel getLabel() {return label;}

	/**
	Calls super.setEnabled. If label for this control is set, then
	calls label.setEnabled. 
	@see #setLabel(JLabel) setLabel 
	@see #getLabel() getLabel
	*/
	public void setEnabled(boolean enabled) {
		super.setEnabled(enabled);
		if (label!=null) label.setEnabled(enabled);
	}

    /**
    *Notifies all ObjectChangeListeners about new value.
    *@param obj new value
    */
    protected void fireObjectChange(Object obj)
    {
        java.util.Vector vector;
      
        synchronized(this) 
        {
            if(listeners == null)
            {
                return;
            }
            vector = (java.util.Vector)listeners.clone();
        }
        ObjectChangeEvent objectchangeevent;
        if(attributeName.equals(""))
            objectchangeevent = new ObjectChangeEvent(this, obj);
        else
            objectchangeevent = new ObjectChangeEvent(this, obj, attributeName);
        for(int i = 0; i < vector.size(); i++)
        {
            ObjectChangeListener objectchangelistener = (ObjectChangeListener)vector.elementAt(i);
            objectchangelistener.objectChanged(objectchangeevent);
        }

    }

    protected void warningDialog(String s){
        if(!Beans.isDesignTime()){
            WarningDialog warningdialog = new WarningDialog(null, "", true, s, null);
            warningdialog.pack();
            warningdialog.setVisible(true);
        }
    }

	/**
	*Localizes given string from com.gensym.gda.controls.Messages.properties resource file.
	*If the value for this key is not found, returns the key itself.
        *@param string key
	*/
	protected static String localize(String string) {
		try {
			return i18n.getString(string);
		} catch (MissingResourceException e) {
			return string;
		}
	}
	
	/**
	For controls where validation is performed if validation fails the method
	*should return false. This method is used by 
	{@link com.gensym.gda.dialogs.gdaDialog#applyDialog()} 
	*method to check if it is possible to apply new values. if the method returns false the dialog 
	*containing this control should stay visible.
	*/
	public boolean isValid() {return true;}
	
	/**
	The dialog (or other Object containing this control) should check 
	that every control is valid (validation is successful)
	using {@link #isValid()} method. If control is not valid it should call 
	setValid(true) method on invalid control 
	(and make other necessary operations). 
	*/
    public void setValid(boolean valid) {}
	
    public void setDisableIfNotUpdated(boolean disable) {disableIfNotUpdated=disable;}
    public boolean getDisableIfNotUpdated() {return disableIfNotUpdated;}
    
	private JLabel label;
	private java.util.Vector listeners;
	private String attributeName;
	private Symbol attributeSymbol;
	protected AttributeEditor editor;	
	protected boolean disableIfNotUpdated;	
	protected final static Resource i18n=Resource.getBundle("com.gensym.gda.controls.Messages");

	class objectChangeListener implements ObjectChangeListener, java.io.Serializable {
			public objectChangeListener() {}
		
			public void objectChanged(ObjectChangeEvent e) {
				fireObjectChange(e.getChangedObject());
			}		
	}

}