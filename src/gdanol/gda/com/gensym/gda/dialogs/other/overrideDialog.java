package com.gensym.gda.dialogs.other;

import java.util.Enumeration;

import java.awt.Frame;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Font;
import javax.swing.JLabel;

import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.message.Trace;
import com.gensym.message.MessageKey;
import com.gensym.message.Resource;

import com.gensym.gda.controls.AbstractAttributeEditor;

/**
  The root class of all override dialogs
    */
public class overrideDialog extends com.gensym.gda.dialogs.blocks.BlocksDialog implements Runnable {
  
  public overrideDialog() {}
  
  public overrideDialog(java.awt.Frame frame) {
      super(frame);
        i18n = Resource.getBundle("com.gensym.gda.dialogs.other.Messages");
    }
  
  /**
      Overrided to set the values of timeout, update interval and override text.
        Note that timeout and update interval should be passed from G2 in seconds.
        Zero or negative values or null lead to cancel the countdown.
	*/
  public void setAdditionalData(Structure additionalData) {
      super.setAdditionalData(additionalData);
        
        Integer Timeout = (Integer)additionalData.getAttributeValue(TIMEOUT_, null);
        Integer UpdateInterval = (Integer)additionalData.getAttributeValue(UPDATE_INTERVAL_, null);
        String OverrideText = (String)additionalData.getAttributeValue(OVERRIDE_TEXT_, null);
        if (OverrideText != null)
	  addOverrideText(OverrideText);
	
        timeout = (Timeout == null)?-1:Timeout.longValue()*1000;
        updateInterval = (UpdateInterval == null)?-1:UpdateInterval.longValue()*1000;
	
        if (timeout <= 0 || updateInterval <= 0){
	  updateCountdownControl(-1);
            return;
        }
        
        timeoutThread = new Thread( this );
        timeoutThread.start();
    }
  
  /**
      Overrided to implement the ability to change the new value prompt.
        Assumes that there is the only editor in the dialog.
	*/
  public void initializeEditors() {
      Enumeration attr = attributes.elements();
        if (attr.hasMoreElements()){
	  Structure attribute = (Structure)attr.nextElement();
            Object newLabel = attribute.getAttributeValue(NEW_VALUE_PROMPT_, null);
            if ((newLabel != null)&&(editor != null)){
	      editor.getLabel().setText(newLabel.toString());
                pack();
            }
        }
        
    }
  
  /**
      Called when the OVERRIDE-TEXT is present ini the launching structure.
        This implementation inserts the label with this text in the top of the dialog
        @param text the override text
	*/
  protected void addOverrideText(String text){
      GridBagConstraints c = new GridBagConstraints();
        GridBagLayout l = (GridBagLayout)dpanel.getLayout();
	
        c.gridy = 0;
        c.gridwidth = GridBagConstraints.REMAINDER;
	
        JLabel label = new JLabel(text);
        
        Font font = label.getFont();
        label.setFont(font.deriveFont((float)(font.getSize()+3)));
        
        l.setConstraints(label, c);
        dpanel.add(label);
        pack();
    }
  
  //NB! negative value means that countdown was canceled
  /**
      Called after each update interval to update the control diplaying time 
        to the timeout. This implementation does nothing.
        @param remTime the time in milliseconds to the timeout. Negative value means that the countdown
	was canceled (i.e. user pressed Apply button)
	    */
  protected void updateCountdownControl(long remTime){
    }
  
  /**
      Runs the countdown in the separate thread.
	*/
  public synchronized void run(){
      long reminingTime = timeout;
        long delay;
        
        while (reminingTime > 0){
	  updateCountdownControl(reminingTime);
            delay = Math.min(reminingTime, updateInterval);
            reminingTime -= delay;
            try{
	      wait(delay);
            }catch(InterruptedException e){
	      break;
            }
            if (isApplyPressed)
	      break;
        }
        updateCountdownControl(-1); // cancel countdown
        if (!isApplyPressed){ //timeout 
	  cancelDialog();
            try {
	      connection.callRPC(GDL_HANDLE_OVERRIDE_TIMEOUT_PROC_,
			       new Object[]{editedItem, getResultStructures(), connection.retrieveSession()},
                30000);
            } catch (Exception e) {
	      Trace.exception(e);
            }
        }

    }
    
  /**
      Overrided to call GDL-APPLY-OVERRIDES in G2
      */
  public boolean applyDialog() {
      synchronized (this) {
	  isApplyPressed = true;
            this.notify();
        }
        
        if (!editorsAreValid())
	  return false;
	
        try {
	  connection.callRPC(GDL_APPLY_OVERRIDE_PROC_,
			       new Object[]{editedItem, getResultStructures(), connection.retrieveSession()},
                30000);
        } catch (Exception e) {
	  Trace.exception(e);
            return false;
        }
        //changedAttributes.clear(); Don't clear changed attributes for override.
        return true;

    }
  public Sequence getResultStructures() {
    //In an override dialog, all values must be applied, whether changed or not
    Sequence returnAttributes = new Sequence(attributes.size());
    returnAttributes.addAll(changedAttributes.values());//Placing the changed attributes first 
    //                                                    will cause GDA to use them over the originals
    returnAttributes.addAll(attributes.values());
    Trace.send(Trace.ALL_LEVELS, traceKey, gdaDialogMessages, "ReturnValuesToApply", returnAttributes);

    return returnAttributes;
  }



  private boolean isApplyPressed = false;
    
  private Thread timeoutThread;
    
  private long timeout;
  private long updateInterval;
  
  protected AbstractAttributeEditor editor;


  public final static Symbol OVERRIDE_VALUE_ = Symbol.intern("OVERRIDE-VALUE");
  public final static Symbol NEW_VALUE_PROMPT_ = Symbol.intern("NEW-VALUE-PROMPT");
  private static final Symbol TIMEOUT_ = Symbol.intern("TIMEOUT");
  private static final Symbol UPDATE_INTERVAL_ = Symbol.intern("UPDATE-INTERVAL");
  protected static final Symbol OVERRIDE_TEXT_ = Symbol.intern("OVERRIDE-TEXT");
        
  private static final Symbol GDL_APPLY_OVERRIDE_PROC_ = Symbol.intern("GDL-APPLY-OVERRIDES");
  private static final Symbol GDL_HANDLE_OVERRIDE_TIMEOUT_PROC_ = Symbol.intern("GDL-HANDLE-OVERRIDE-TIMEOUT");
  static MessageKey traceKey = Trace.registerMessageKey("com.gensym.gda", overrideDialog.class);
}
