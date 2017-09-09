package com.gensym.gda.commands;

import java.awt.event.ActionEvent;
import java.util.MissingResourceException;
import java.awt.Cursor;

import com.gensym.core.UiApplication;
import com.gensym.message.Resource;
import com.gensym.ntw.TwAccess;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.TW2Application;
import com.gensym.shell.util.TW2MDIApplication;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.gda.util.SwingWorker;


/**
The root for each command. Implements listener for connection manager.
Override {@link #setCurrentConnection setCurrentConnection} method if it is needed to implement some 
actions when connection is changed.
Override {@link #commandPerformed commandPerformed} method to implement command actions.
*/
public abstract class gdaAbstractCommand extends AbstractStructuredCommand {

    public gdaAbstractCommand(UiApplication uiapplication, StructuredCommandInformation[] commands) {
    	super(commands);
        app = uiapplication;        
        if(uiapplication instanceof TW2Application) {
            connectionManager = ((TW2Application)uiapplication).getConnectionManager();
            currentConnection = ((TW2Application)uiapplication).getConnection();
        } else if(uiapplication instanceof TW2MDIApplication) {
            connectionManager = ((TW2MDIApplication)uiapplication).getConnectionManager();
            currentConnection = ((TW2MDIApplication)uiapplication).getConnection();
        }        
        if(connectionManager != null) {
            currentConnection = connectionManager.getCurrentConnection();
            connectionManager.addContextChangedListener(new ConnectionChangedListener());
        }

        updateAvailability();
 //    if (currentConnection!=null) setCurrentConnection(currentConnection); ??
    }

    public gdaAbstractCommand(UiApplication uiapplication) {
		this(uiapplication, new StructuredCommandInformation[0]);
    }

    public void setConnection(TwAccess twaccess) {
        if(connectionManager == null && (currentConnection != null && !currentConnection.equals(twaccess) || currentConnection == null && twaccess != null))
            setCurrentConnection(twaccess);
    }

    protected void setCurrentConnection(TwAccess twaccess) {
        currentConnection = twaccess;
        updateAvailability();
    }


    public void actionPerformed(ActionEvent actionevent) {
        String s = actionevent.getActionCommand();
        if(!isAvailable(s)) {
            throw new IllegalStateException(i18n.format("CommandIsUnavailable", s));
        }
        
        final ActionEvent event = actionevent;
        SwingWorker worker = new SwingWorker() {
            public Object construct() {
            	try {
   					app.getCurrentFrame().setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
	            	commandPerformed(event);
		        } finally {
					app.getCurrentFrame().setCursor(Cursor.getDefaultCursor());
				}
            	return null;
            }
        };
		worker.start();
        
    }

    /**
    The method called by actionPerformed method.
    */
    public void commandPerformed(ActionEvent event) {}

    public void updateAvailability() {
    }
    
    class ConnectionChangedListener implements ContextChangedListener {
        public void currentConnectionChanged(ContextChangedEvent contextchangedevent) {
            setCurrentConnection(contextchangedevent.getConnection());
       }
        ConnectionChangedListener() {}
    }
    
    protected static String localize(String text) {
		try {
			return i18n.getString(text);
		} catch (MissingResourceException e) {
			return text;
		}
	}

   
    protected static Resource i18n=Resource.getBundle("com/gensym/gda/commands/Messages");;
    protected UiApplication app;
    protected ConnectionManager connectionManager;
    protected TwAccess currentConnection;
    protected static String shortResource = "ShortResource";
    protected static String longResource = "LongResource";
    protected static String mnemonicResource = "MnemonicResource";
        
}