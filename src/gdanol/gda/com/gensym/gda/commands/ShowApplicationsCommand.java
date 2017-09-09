package com.gensym.gda.commands;

import java.awt.event.ActionEvent;

import com.gensym.core.UiApplication;
import com.gensym.ui.CommandInformation;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.dlg.SelectionDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.CommandConstants;
import com.gensym.message.Trace;
import com.gensym.jgi.G2AccessException;

/**
Implements Show Applications command. Shows the dialog with the list of
available applications. When the application is selected and Ok is pressed 
shows the application workspace.
*/
public class ShowApplicationsCommand extends gdaAbstractCommand {

    public ShowApplicationsCommand(UiApplication uiapplication) {
		super(uiapplication,
			new CommandInformation[] {
	            new CommandInformation(SHOW_APPLICATIONS, true, shortResource, longResource, null, null, null, true, mnemonicResource, null), 
			}
		);
		dialogClient=new DialogClient();
    }

    public void commandPerformed(ActionEvent actionevent) {
        try {	
            Sequence sequence = (Sequence) currentConnection.callRPC(GET_APPLICATION_DESCRIPTIONS_RPC_,
            	new Object[0]
            );
            applicationDescriptions=sequence;
            int i = sequence.size();
            String as[] = new String[i];
            for(int j = 0; j < i; j++)
                as[j] = (String)((Structure)sequence.get(j)).getAttributeValue(APPLICATION_TITLE_, "");

            (new SelectionDialog(app.getCurrentFrame(), localize("ShowApplicationsTitle"), true, 
            	localize("ChooseApplicationPrompt"), as, false, -1, true, dialogClient)).setVisible(true);
        }
        catch(G2AccessException g2accessexception) {
        	Trace.exception(g2accessexception);
            return;
        }
        catch(Exception exception) {
            Trace.exception(exception);
        }
    }

    public void updateAvailability () {
		if (currentConnection==null)
			setAvailable(SHOW_APPLICATIONS, false);
		else {
			try {
				currentConnection.getUniqueNamedItem(com.gensym.util.symbol.G2ClassSymbols.ITEM_,
					GET_APPLICATION_DESCRIPTIONS_RPC_);
				setAvailable(SHOW_APPLICATIONS, true);
			}catch (G2AccessException e) {
				setAvailable(SHOW_APPLICATIONS, false);
			}
		}
    }

    class DialogClient implements StandardDialogClient{

        public void dialogDismissed(StandardDialog standarddialog, int i) {
            SelectionDialog selectiondialog = (SelectionDialog)standarddialog;
            if(selectiondialog.wasCancelled())
                return;
            int ai[] = selectiondialog.getResults();
            for(int j = 0; j < ai.length; j++) {
                int k = ai[j];
                try {
	                currentConnection.callRPC(SHOW_APPLICATION_RPC_,
	                	new Object[]{((Structure)applicationDescriptions.get(k)).
	                	getAttributeValue(APPLICATION_NAVIIGATION_KEY_, null),
	                	currentConnection.retrieveSession()}
	                );
                } catch (G2AccessException e) {Trace.exception(e);}
            }
        }
    }
        
    protected Sequence applicationDescriptions;
 	protected DialogClient dialogClient;
    public static final String SHOW_APPLICATIONS = "ShowApplications";
	public static final Symbol GET_APPLICATION_DESCRIPTIONS_RPC_ = 
		Symbol.intern("GDL-GET-APPLICATION-DESCRIPTIONS");
	public static final Symbol SHOW_APPLICATION_RPC_ = 
		Symbol.intern("GDL-SHOW-APPLICATION");
	public static final Symbol APPLICATION_TITLE_ = 
		Symbol.intern("APPLICATION-TITLE");
	public static final Symbol APPLICATION_NAVIIGATION_KEY_ = 
		Symbol.intern("APPLICATION-NAVIGATION-KEY");
}