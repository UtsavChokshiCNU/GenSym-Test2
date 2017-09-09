package com.gensym.gda.dialogs;

import java.awt.Frame;
import java.lang.reflect.Constructor;
import java.util.ResourceBundle;
import java.util.Hashtable;
import java.util.Enumeration;

import javax.swing.JDialog;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.classes.Item;
import com.gensym.ntw.TwAccess;
import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;
import com.gensym.jgi.G2AccessException;

import com.gensym.gda.util.GfrCommunicationManager;
/**
The instance of this dialog manager should be created for the TwAccess which is connected to 
the GDA Application. 
@see gdaDialogManagerFactory
*/
public class gdaDialogManager extends com.gensym.dlgruntime.DialogManager {


    public gdaDialogManager(TwAccess connection) {
    	super(connection);
    	this.connection=connection;
		dialogs = new Hashtable();
		
    }

	/** startDialog is called by G2 side when configure menu choice is selected. This method
	should be registered (@see com.gensym.jgi.G2Access.registerJavaMethod())
	*/
	public void startDialog(Frame frame, Structure additionalData, TwAccess connection) {

		Trace.send(Trace.ALL_LEVELS, traceKey, i18n, "StartingDialog", additionalData);
	        
	    Constructor c = findDialogConstructor(additionalData);
	    if (c==null) 
	    	return;
		//launching dialog
		try  {
			gdaDialog dialog = (gdaDialog) c.newInstance(new Object[]{frame});
			dialog.setConnection(connection);
			dialog.setAdditionalData(additionalData);
			dialog.setVisible(true);

		} catch (Exception e) {
			Trace.exception(e);
		}		
	}

	
	public Sequence promptForValueFromList(Frame frame, String title,  
    	String prompt, int defaultIndex, Sequence initialValues) {
    	return (new com.gensym.gda.dialogs.other.gdlGenericListSelection(
    		frame, title, prompt, defaultIndex, initialValues)).selectValue();
    }

	public Sequence promptForValue(Frame frame, 
    	String prompt, String initialValue, Symbol formatSpec, TwAccess connection) {
    	return (new com.gensym.gda.dialogs.other.gdlGenericValueQuery(
    		frame, prompt, initialValue, formatSpec, connection)).selectValue();
    }
    
    public void showPathTable(Frame frame, String title, 
            com.gensym.classes.modules.gdluisup.GdlPathItemEventManager manager,
            Sequence attrNames, Sequence initVals){
        com.gensym.gda.dialogs.other.gdlPathTable table = 
            new com.gensym.gda.dialogs.other.gdlPathTable(frame, attrNames, initVals);
        table.setManager(manager);
        table.setTitle(title);
        table.setVisible(true);
    }

    public Constructor findDialogConstructor(Structure additionalData) {
		
		String javaName = (String) additionalData.getAttributeValue(DIALOG_CLASS_, null);
		if (javaName == null) {
			Item item = (Item) additionalData.getAttributeValue(ITEM_, null);
			String itemClass = null;
			try {
				itemClass=item.getG2ClassName().toString().toLowerCase();
			} catch (G2AccessException e) {
				Trace.exception(e);
				return null;
			}
	
			javaName = (String) dialogs.get(itemClass);
			if (javaName==null) {
				GfrCommunicationManager.showAlert(i18n.format("DialogIsNotFound", itemClass));
				return null;
			}
		}				
		//Searching for class = javaName;
		Class clazz = null;
		try {
	        clazz = Class.forName(javaName);
		} catch (ClassNotFoundException e) {
			GfrCommunicationManager.showAlert(i18n.format("ClassIsNotFound",javaName));
			return null;
		}

		//Seraching for dialog constructor
		Constructor c = null;
		try {
			c = clazz.getDeclaredConstructor(new Class[]{Frame.class});
			Trace.send(Trace.ALL_LEVELS, traceKey, i18n, "ConstructorIsFound", c);
		} catch (Exception e) {
			Trace.send(Trace.ALL_LEVELS, traceKey, i18n, "ConstructorIsNotFound", clazz);
			return null;
		}
		
		return c;
	}
	
	/**
	Dialog resoure is a ResourceBundle object where keys are G2 object class name,
	and values are java dialog class name, instance of which should be displayed when
	configure menu choice is selected for the item of that class.
	For GDA blocks the ResourceBundle "com.gensym.dialogs.Dialogs" should be registered in
	the gdaDialogManager. 
	*/
	public void addDialogResource(ResourceBundle bundle) {
		String key;
		for (Enumeration enum=bundle.getKeys(); enum.hasMoreElements();) {
			key = (String) enum.nextElement();
			dialogs.put(key, bundle.getObject(key));
		}
	}


    protected TwAccess connection;
    protected Sequence warningSequence;
	private final static Symbol G2 = Symbol.intern("G2");
	private final static Symbol DIALOG_CLASS_ = Symbol.intern("DIALOG-CLASS");
	private final static Symbol ITEM_ = Symbol.intern("ITEM");
	private static Resource i18n = Resource.getBundle("com/gensym/gda/dialogs/Messages");
	private static MessageKey traceKey = Trace.registerMessageKey("com.gensym.gda", gdaDialogManager.class);
    
    private Hashtable dialogs;

}