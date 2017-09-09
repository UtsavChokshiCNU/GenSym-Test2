/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2SystemTablesPanel.java
 *
 *  Description:
 *
 *
 *	 Author:
 *		Todd O'Brien		Feb/98
 *
 *     
 *   Modifications:
 *
 */

package com.gensym.g2studio.dialogs;

import java.awt.Button;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.awt.List;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseAdapter;
import java.util.Locale;
import com.gensym.message.Resource;
import com.gensym.classes.Item;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.Module;
import com.gensym.classes.ModuleInformation;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;
import com.gensym.shell.util.TW2Application;
import com.gensym.uiutil.StandardGridBagPanel;
import com.gensym.core.GensymApplication;
import com.gensym.util.Symbol;

/**
 */
public class G2SystemTablesPanel extends StandardGridBagPanel 
implements ActionListener {
  private List list;
  private Button editButton;
  private Module module;
  
  private static Resource shortBundle = Resource.getBundle("com/gensym/g2studio/dialogs/CommandShortResource");

  private static String ColorParameters           = shortBundle.getString("ColorParameters");
  private static String DataServerParameters      = shortBundle.getString("DataServerParameters");
  private static String DebuggingParameters       = shortBundle.getString("DebuggingParameters");
  private static String DrawingParameters         = shortBundle.getString("DrawingParameters");
  private static String EditorParameters          = shortBundle.getString("EditorParameters");
  private static String Fonts                     = shortBundle.getString("Fonts");
  private static String InferenceEngineParameters = shortBundle.getString("InferenceEngineParameters");
  private static String KbConfiguration           = shortBundle.getString("KbConfiguration");
  private static String LanguageParameters        = shortBundle.getString("LanguageParameters");
  private static String LogbookParameters         = shortBundle.getString("LogbookParameters");
  private static String LogFileParameters         = shortBundle.getString("LogFileParameters");
  private static String MenuParameters            = shortBundle.getString("MenuParameters");
  private static String MessageBoardParameters    = shortBundle.getString("MessageBoardParameters");
  private static String MiscellaneousParameters   = shortBundle.getString("MiscellaneousParameters");
  private static String ModuleInformation         = shortBundle.getString("ModuleInformation");
  private static String PrinterSetup              = shortBundle.getString("PrinterSetup");
  private static String SavingParameters          = shortBundle.getString("SavingParameters");
  private static String SimulationParameters      = shortBundle.getString("SimulationParameters");
  private static String TimingParameters          = shortBundle.getString("TimingParameters");

  String systemTables[] = {ColorParameters, DataServerParameters, 
			   DebuggingParameters, DrawingParameters,
                           EditorParameters, Fonts, InferenceEngineParameters, 
			   KbConfiguration, LanguageParameters,
                           LogbookParameters, LogFileParameters,
			   MenuParameters, MessageBoardParameters,
                           MiscellaneousParameters, ModuleInformation, 
			   PrinterSetup, SavingParameters,
                           SimulationParameters, TimingParameters};  
  /**
   */
  public G2SystemTablesPanel(Module module)
  {
    super();
    this.module = module;

    setLayout(gridBagLayout);
    GridBagConstraints constraints = new GridBagConstraints();
    constraints.fill = GridBagConstraints.BOTH;
    constraints.insets  = new Insets (10, 10, 10, 10);

    constraints.weightx = 1;
    constraints.weighty = 1;
    constraints.gridwidth = GridBagConstraints.RELATIVE;
    constraints.gridheight = 4;
    addComponent(list = new List(), constraints);
    list.addMouseListener(new MouseAdapter()
                              {@Override
public void mouseClicked(MouseEvent event)
                                {int index = list.getSelectedIndex();
                                 if ((index != -1) && 
				     (event.getClickCount() > 1)) {
				   editSystemTable(systemTables[index]);
				 }}});

    constraints.weightx = 0;
    constraints.weighty = 0;
    constraints.gridwidth = GridBagConstraints.REMAINDER;
    constraints.gridheight = 1;
    constraints.insets  = new Insets (10, 0, 10, 10);
    addComponent(editButton = new Button(shortBundle.getString("G2SystemTablesPanelEditButtonLabel")), constraints);
    editButton.addActionListener(this);
    addSystemTables();
  }

  private void addSystemTables() {
    for (int i=0; i<systemTables.length; i++)
      list.add(systemTables[i]);
  }

  @Override
  public void actionPerformed(ActionEvent event) {
    editSystemTable(systemTables[list.getSelectedIndex()]);
  }

  private void editSystemTable(String table) {
    Item item = null;

    if (table.equals(ColorParameters))
      item = module.getColorParameters();
    else if (table.equals(DataServerParameters))
      item = module.getDataServerParameters();
    else if (table.equals(DebuggingParameters))
      item = module.getDebuggingParameters();
    else if (table.equals(DrawingParameters))
      item = module.getDrawingParameters();
    else if (table.equals(EditorParameters))
      item = module.getEditorParameters();
    else if (table.equals(Fonts))
      item = module.getFonts();
    else if (table.equals(InferenceEngineParameters))
      item = module.getInferenceEngineParameters();
    else if (table.equals(KbConfiguration))
      item = module.getKbConfiguration();
    else if (table.equals(LanguageParameters))
      item = module.getLanguageParameters();
    else if (table.equals(LogbookParameters))
      item = module.getLogbookParameters();
    else if (table.equals(LogFileParameters))
      item = module.getLogFileParameters();
    else if (table.equals(MenuParameters))
      item = module.getMenuParameters();
    else if (table.equals(MessageBoardParameters))
      item = module.getMessageBoardParameters();
    else if (table.equals(MiscellaneousParameters))
      item = module.getMiscellaneousParameters();
    else if (table.equals(ModuleInformation))
      item = module.getModuleInformation();
    else if (table.equals(PrinterSetup))
      item = module.getPrinterSetup();
    else if (table.equals(SimulationParameters))
      item = module.getSimulationParameters();
    else if (table.equals(TimingParameters))
      item = module.getTimingParameters();

    try {
      TW2Application tw2app = (TW2Application)GensymApplication.getApplication();
      TwAccess context = tw2app.getConnectionManager().getCurrentConnection();
      //TwAccess context = (TwAccess) ((ImplAccess)item).getContext();
      context.getDialogManager().editItem (item, 
					   Symbol.intern("ADMINISTRATOR"),
					   Locale.getDefault());
    }
    catch (Exception ex) {
    }
  }
}


