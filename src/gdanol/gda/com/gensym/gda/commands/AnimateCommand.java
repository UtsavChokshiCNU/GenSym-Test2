package com.gensym.gda.commands;

import java.awt.event.ActionEvent;

import com.gensym.core.UiApplication;
import com.gensym.ui.CommandInformation;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.message.Trace;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.ItemListener;
import com.gensym.util.ItemEvent;
import com.gensym.ntw.TwAccess;
import com.gensym.classes.Item;


/**
Implements Animate command. Finds the GDL-ENGINE object and
listens for the ANIMATE attribute of it. If object is not found the
command is disabled. When command is choosen calls GDL-TURN-ANIMATION-ON or
GDL-TURN-ANIMATION-OFF procedures depend on current state.
*/
public class AnimateCommand extends gdaAbstractCommand {

    public AnimateCommand(UiApplication uiapplication) {
		super(uiapplication,
			new CommandInformation[] {
	            new CommandInformation(ANIMATE, true, shortResource, longResource, null, null, Boolean.FALSE, true, mnemonicResource, null), 
			}
		);

		engineListener=new GdlEngineListener();
		gdlEngine=null;
		checkEngineListener();
        updateAvailability();
    }

    protected void setCurrentConnection(TwAccess twaccess) {
        currentConnection = twaccess;
       	checkEngineListener();
        updateAvailability();
   }

    public void commandPerformed(ActionEvent actionevent) {
        String s = actionevent.getActionCommand();
        if (s!=ANIMATE)
        	return;
        Boolean state = getState(ANIMATE);
		try {
			currentConnection.callRPC(state.booleanValue() ? TURN_ANIMATION_OFF_RPC : GDL_TURN_ANIMATION_ON_RPC,
				new Object[] {currentConnection.retrieveSession()}
			);
		} catch (G2AccessException e) {Trace.exception(e);}
    }

    public void updateAvailability () {
		setAvailable(ANIMATE, gdlEngine!=null);
    }

    public void setState(String cmdKey, Boolean state) {super.setState(cmdKey, state);}
    
    protected void checkEngineListener() {
    	if (gdlEngine!=null) {
    		try {
    			gdlEngine.removeItemListener(engineListener);
    		} catch (G2AccessException gae) {Trace.exception(gae);}
    		gdlEngine=null;
    	}
    	
    	if (currentConnection==null)
    		return;
    		
    	try {
    		gdlEngine = currentConnection.getUniqueNamedItem(
    			GDL_APPLICATION_ENGINE_, GDL_ENGINE_NAME_);
    		gdlEngine.addItemListener(engineListener);
    	} catch (G2AccessException e) {
    		gdlEngine=null;
    	}
    }
    
    
    class GdlEngineListener implements ItemListener {
 		public GdlEngineListener() {}
 		
    	public void receivedInitialValues(ItemEvent e) {
    		Structure values = (Structure) e.getNewValue();
    		Boolean checked = (Boolean) values.getAttributeValue(ANIMATE_, null);
    		if (checked!=null)
    			setState(ANIMATE, checked);
    	}
    	
    	public void itemModified(ItemEvent e) {
            Structure structure = (Structure)e.getDenotation().get(0);
            Symbol symbol = (Symbol)structure.getAttributeValue(NAME_, null);
            if (!ANIMATE_.equals(symbol))
            	return;
            setState(ANIMATE, (Boolean)e.getNewValue());    		
    	}
    	
    	public void itemDeleted(ItemEvent e) {}
    }
    
    public static final String ANIMATE = "Animate";
	protected static final Symbol GDL_TURN_ANIMATION_ON_RPC = 
		Symbol.intern("GDL-TURN-ANIMATION-ON");
	protected static final Symbol TURN_ANIMATION_OFF_RPC = 
		Symbol.intern("GDL-TURN-ANIMATION-OFF");

    protected static final Symbol ANIMATE_ = Symbol.intern("ANIMATE");
	protected static final Symbol NAME_ = Symbol.intern("NAME");
		
	protected static final Symbol GDL_ENGINE_NAME_ = Symbol.intern("GDL-ENGINE");
    protected static final Symbol GDL_APPLICATION_ENGINE_ = Symbol.intern("GDL-APPLICATION-ENGINE");

    protected GdlEngineListener engineListener;
    protected Item gdlEngine;
}