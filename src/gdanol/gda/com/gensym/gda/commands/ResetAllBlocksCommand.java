package com.gensym.gda.commands;

import java.awt.event.ActionEvent;

import com.gensym.core.UiApplication;
import com.gensym.ui.CommandInformation;
import com.gensym.util.Symbol;
// import com.gensym.jdlg.JQuestionDialog;   
// import com.gensym.jdlg.JStandardDialogClient;
// import com.gensym.jdlg.JStandardDialog;
import com.gensym.dlg.CommandConstants;
import com.gensym.message.Trace;
import com.gensym.jgi.G2AccessException;
import com.gensym.gda.util.SwingWorker;


/**
Implements reset All Blocks command. Shows the confirmation dialog and
if not cancel is selected calls GDL-RESET-ALL-GDL-OBJECTS procedure.
*/
public class ResetAllBlocksCommand extends gdaAbstractCommand {

    public ResetAllBlocksCommand(UiApplication uiapplication) {
		super(uiapplication,
			new CommandInformation[] {
	            new CommandInformation(RESET_ALL_BLOCKS, true, shortResource, longResource, null, null, null, true, mnemonicResource, null), 
			}
		);
    }

    public void commandPerformed(ActionEvent actionevent) {    	  
   	
   		try {
	   		String reply = (String)currentConnection.callRPC(GDL_RESET_BLOCKS_DIALOG_RPC,
	   			new Object[]{currentConnection.retrieveSession()},
	   			0);
	   		if (reply.equals("CANCEL") || reply.equals("TIMEOUT"))
	   			return;
	   			
			currentConnection.callRPC(GDL_RESET_ALL_GDL_OBJECTS_RPC,
				new Object[] {currentConnection.retrieveSession(), 
					new Boolean(reply.equals("NO")), Boolean.TRUE}
			);
   		} catch (G2AccessException e) {Trace.exception(e);}   
    }

    public void updateAvailability () {
		if (currentConnection==null)
			setAvailable(RESET_ALL_BLOCKS, false);
		else {
			try {
				currentConnection.getUniqueNamedItem(com.gensym.util.symbol.G2ClassSymbols.ITEM_,
					GDL_RESET_ALL_GDL_OBJECTS_RPC);
				setAvailable(RESET_ALL_BLOCKS, true);
			}catch (G2AccessException e) {
				setAvailable(RESET_ALL_BLOCKS, false);
			}
		}
    }
    
    public static final String RESET_ALL_BLOCKS = "ResetAllBlocks";
	public static final Symbol GDL_RESET_ALL_GDL_OBJECTS_RPC = 
		Symbol.intern("GDL-RESET-ALL-GDL-OBJECTS");
	public static final Symbol GDL_RESET_BLOCKS_DIALOG_RPC = 
		Symbol.intern("GDL-RESET-BLOCKS-DIALOG");		
}