package com.gensym.gda.util;


import java.awt.Frame;
import javax.swing.JOptionPane;
import java.util.Vector;

import com.gensym.core.UiApplication;
import com.gensym.classes.Item;
import com.gensym.util.Symbol;
import com.gensym.message.Resource;
import java.util.MissingResourceException;

public class GfrCommunicationManager {


    public GfrCommunicationManager() {}

	/**
	Shows dialog depend on class of <code>comm</code> which contains 
	the message <code>message</code> and button(s) with the default label(s).
	*/	
    public static void handleCommunication(Item comm, String message) {
    	handleCommunication(comm, message, null);
    }

	/**
	Shows dialog depend on class of <code>comm</code> which contains 
	the message <code>message</code> and button(s) with the labels defined 
	in the <code>buttons</code>. The size of <code>buttons</code> should be equals to
	the number of buttons.
	If the class of <code>comm</code> is gfr-alert then alert is shown,
	if the class of <code>comm</code> is gfr-ok-cancel-confirm then ok-cancel dialog is shown,
	if the class of <code>comm</code> is gfr-yes-no-cancel-confirm then yes-no-cancel dialog is shown.
	*/	
    public static void handleCommunication(Item comm, String message, Vector buttons) {
        if (comm.isInstanceOfG2Class(GFR_ALERT))
            showAlert(comm, message, buttons);
        else if (comm.isInstanceOfG2Class(GFR_OK_CANCEL_CONFIRM))
            showOkCancelDialog(comm, message, buttons);
        else if (comm.isInstanceOfG2Class(GFR_YES_NO_CANCEL_CONFIRM))
            showYesNoCancelDialog(comm, message, buttons);
    }

    /**
    Shows dialog which contains the message <code>message</code> and 
    the button with the label "OK";
    */
    public static void showAlert(String message) {
    	showAlert(null, message, defaultAlertButtons);
    }

    /**
    Shows dialog which contains the message <code>message</code> and 
    the button with the label "OK";
    */
    public static void showAlert(Item comm, String message) {
    	showAlert(comm, message, defaultAlertButtons);
    }

    /**
    Shows dialog which contains the message <code>message</code> and 
    one button with the label which is the first element in <code>buttons</code>.
    */
    public static void showAlert(Item comm, String message, Vector buttons) {
    	if (buttons==null) buttons = defaultAlertButtons;
    	Frame parent = getApplicationFrame();
		Object[] options=buttons.toArray();
		OptionPane pane = new OptionPane(comm, parent, message, 
			localize("AlertTitle"), JOptionPane.DEFAULT_OPTION,JOptionPane.WARNING_MESSAGE, 
			null,options, options[0]);
		pane.showOptionDialog();

    }

    /**
    Shows dialog which contains the message <code>message</code> and 
    two buttons with the labels "OK" and "Cancel".
    */
    public static void showOkCancelDialog(Item comm, String message) {
    	showOkCancelDialog(comm, message, defaultOkCancelButtons);
    }
    
    /**
    Shows dialog which contains the message <code>message</code> and 
    two buttons with the labels which are the first and the second elements of <code>buttons</code>.
    */
    public static void showOkCancelDialog(Item comm, String message, Vector buttons) {
    	if (buttons==null) buttons = defaultOkCancelButtons;
    	Frame parent = getApplicationFrame();
		Object[] options=buttons.toArray();
		OptionPane pane = new OptionPane(comm, parent, message,
			localize("OkCancelConfirmTitle"), JOptionPane.OK_CANCEL_OPTION, JOptionPane.QUESTION_MESSAGE,
			null,options, options[0]);
		pane.showOptionDialog();

    }

    /**
    Shows dialog which contains the message <code>message</code> and 
    three buttons with the labels "Yes", "No" and "Cancel".
    */
    public static void showYesNoCancelDialog(Item comm, String message) {
    	showYesNoCancelDialog(comm, message, defaultYesNoCancelButtons);
    }
    
    /**
    Shows dialog which contains the message <code>message</code> and 
    three buttons with the labels which are the first, the second and 
    the third elements of <code>buttons</code>.

    */
    public static void showYesNoCancelDialog(Item comm, String message, Vector buttons) {
    	if (buttons==null) buttons = defaultYesNoCancelButtons;
    	Frame parent = getApplicationFrame();
		Object[] options=buttons.toArray();
		OptionPane pane = new OptionPane(comm, parent, message,
			localize("YesNoCancelConfirmTitle"), JOptionPane.YES_NO_CANCEL_OPTION, JOptionPane.QUESTION_MESSAGE,
			null,options, options[0]);
		pane.showOptionDialog();

    }

	protected static Frame getApplicationFrame() {
        return UiApplication.getCurrentFrame();
	}

	/**Localizes text from com.gensym.gda.util.Messages
		resource file. If the value for the key is not found then it returns key itself.
	*/
	protected static String localize(String string) {
		try { return i18n.getString(string);
		} catch (MissingResourceException e) {return string;}
	}


    protected static final Symbol GFR_ALERT = Symbol.intern("GFR-ALERT");
    protected static final Symbol GFR_OK_CANCEL_CONFIRM = Symbol.intern("GFR-OK-CANCEL-CONFIRM");
    protected static final Symbol GFR_YES_NO_CANCEL_CONFIRM = Symbol.intern("GFR-YES-NO-CANCEL-CONFIRM");

	protected static Resource i18n=Resource.getBundle("com.gensym.gda.util.Messages");
	
	protected static Vector defaultAlertButtons;
	protected static Vector defaultOkCancelButtons;
	protected static Vector defaultYesNoCancelButtons;
	static {
		defaultAlertButtons=new Vector(1);
		defaultAlertButtons.add(localize("AlertDefaultButton"));
		defaultOkCancelButtons=new Vector(2);
		defaultOkCancelButtons.add(localize("OkCancelOkDefaultButton"));
		defaultOkCancelButtons.add(localize("OkCancelCancelDefaultButton"));
		defaultYesNoCancelButtons=new Vector(3);
		defaultYesNoCancelButtons.add(localize("YesNoCancelYesDefaultButton"));
		defaultYesNoCancelButtons.add(localize("YesNoCancelNoDefaultButton"));
		defaultYesNoCancelButtons.add(localize("YesNoCancelCancelDefaultButton"));
	}

}