package com.gensym.gda.dialogs.preferences;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JButton;
import javax.swing.JPanel;


import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.gda.util.SwingWorker;
import com.gensym.dlgevent.ObjectUpdateEvent;

public class gdiQueueSettingPanel extends PreferencesPanel implements ActionListener {
	
  public gdiQueueSettingPanel(PreferencesDialog dialog) {
    super(dialog);
    
    queuePanel = new NoBoundsPreferencesPanel(dialog);
    standardQueue = new QueueComboBoxEditor();
    queuePanel.placeAttributeEditor(standardQueue, "",
				    GQM_STANDARD_QUEUE_, symbolFieldType, 0);
    configureQueue=new JButton(localize("ConfigureQueueButtonLabel"));
    configureQueue.setToolTipText(localize("ConfigureQueueButtonToolTipText"));
    configureQueue.addActionListener(this);
    queuePanel.addButton(configureQueue,3);
    addPanel(queuePanel, localize(GQM_STANDARD_QUEUE_.toString().toLowerCase()),0);
		
    //		JPanel panel = new JPanel();
    configureQueueView=new JButton(localize("ConfigureDefaultQueueViewButtonLabel"));
    configureQueueView.setToolTipText(localize("ConfigureDefaultQueueViewButtonToolTipText"));
    configureQueueView.addActionListener(this);
    queuePanel.addButton(configureQueueView,4);
    //		addPanel(panel, null, 4);
  }

  public void actionPerformed(ActionEvent e) {
    if (e.getSource()==configureQueueView) {
      try {
	dialog.getConnection().callRPC(GDL_LAUNCH_TABULAR_VIEW_TEMPLATE_DIALOG_,
				       new Object[]{settingClass, dialog.getConnection().retrieveSession()});
      } catch (G2AccessException error) {Trace.exception(error);}
    } else if (e.getSource()==configureQueue) {
      try {
	dialog.getConnection().callRPC(GDA_CONFIGURE_QUEUE_FROM_T2_PREFERENCE_,
				       new Object[]{selectedQueue,
						      dialog.getConnection().retrieveSession()});
      } catch (G2AccessException error) {Trace.exception(error);}
    }
  }
  
  
  class QueueComboBoxEditor extends ComboBoxEditor {
    public void objectUpdated(ObjectUpdateEvent event) {
      super.objectUpdated(event);
      Structure values = (Structure) event.getUpdatedObject();
      selectedQueue = (Symbol)values.getAttributeValue(getAttribute(), null);			
    }
    
    public void fireObjectChange(Object object) {
      selectedQueue=(Symbol) object;
      super.fireObjectChange(object);
    }
  }
  
  protected Symbol selectedQueue;
  protected NoBoundsPreferencesPanel queuePanel;
  protected ComboBoxEditor standardQueue;
  protected JButton configureQueue;
  protected JButton configureQueueView;
  
  protected final static Symbol GQM_STANDARD_QUEUE_ = Symbol.intern("GQM-STANDARD-QUEUE");	
  protected final static Symbol GDL_LAUNCH_TABULAR_VIEW_TEMPLATE_DIALOG_ = 
  Symbol.intern("GDL-LAUNCH-TABULAR-VIEW-TEMPLATE-DIALOG");	
  protected final static Symbol GDA_CONFIGURE_QUEUE_FROM_T2_PREFERENCE_ = 
  Symbol.intern("GDA-CONFIGURE-QUEUE-FROM-T2-PREFERENCE");
  
	
}
