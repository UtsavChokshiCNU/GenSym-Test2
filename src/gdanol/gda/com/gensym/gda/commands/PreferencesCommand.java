package com.gensym.gda.commands;

import java.awt.event.ActionEvent;

import com.gensym.core.UiApplication;
import com.gensym.ui.CommandInformation;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;

import com.gensym.gda.dialogs.preferences.Preferences;


/**
Shows the {@link com.gensym.gda.dialogs.preferences.Preferences} dialog.
*/
public class PreferencesCommand extends gdaAbstractCommand {

    public PreferencesCommand(UiApplication uiapplication) {
		super(uiapplication,
			new CommandInformation[] {
	            new CommandInformation(PREFERENCES, true, shortResource, longResource, null, null, null, false, mnemonicResource, null), 
			}
		);
    }

    public void updateAvailability () {
		if (currentConnection==null)
			setAvailable(PREFERENCES, false);
		else {
			try {
				currentConnection.getUniqueNamedItem(com.gensym.util.symbol.G2ClassSymbols.ITEM_,
					GET_PREFERENCES_CONFIGURATION_);
				setAvailable(PREFERENCES, true);
			}catch (G2AccessException e) {
				setAvailable(PREFERENCES, false);
			}
		}
    }

    
    public void commandPerformed(ActionEvent actionevent) {

		java.awt.Frame frame = app.getCurrentFrame();
    	if (dialog==null){
			dialog = new Preferences(frame);
			dialog.setConnection(currentConnection);
    	}
		try {
			Structure s = (Structure) currentConnection.callRPC(GET_PREFERENCES_CONFIGURATION_,
				new Object[] {currentConnection.retrieveSession()});
			dialog.setAdditionalData(s);
	    	dialog.show();
		} catch (G2AccessException e) {Trace.exception(e);}
    }

   protected final static Symbol GET_PREFERENCES_CONFIGURATION_ = 
    	Symbol.intern("GDL-GET-PREFERENCES-CONFIGURATION");
 	protected Preferences dialog;
    public static final String PREFERENCES = "Preferences";
}