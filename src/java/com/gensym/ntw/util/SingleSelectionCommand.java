/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 SingleSelectionCommand.java
 *
 */

package com.gensym.ntw.util;

import javax.swing.JTable;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.TableModelListener;
import javax.swing.event.TableModelEvent;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.message.Resource;

abstract class SingleSelectionCommand extends AbstractCommand{

  protected static final String shortResource = "CommandShortResource";
  protected static final String longResource = "CommandLongResource";
  protected static Resource i18n = Resource.getBundle("com/gensym/ntw/util/CommandShortResource");

  protected KbMessageTableView msgTableView;
  protected TableView tableView;
  protected JTable table;
  protected String[] keys;

  SingleSelectionCommand(CommandInformation[] info, KbMessageTableView msgTableView){
    super(info);
    int len = info.length;
    keys = new String[len];
    for (int i=0; i<len; i++)
      keys[i] = info[i].getKey();
    this.msgTableView = msgTableView;
    tableView = msgTableView.getTableView();
    table = tableView.getTable();
    ListSelectionListener selectionListener = new SelectionAdapter();
    table.getSelectionModel().addListSelectionListener(selectionListener);
    TableModelListener modelListener = new ModelAdapter();
    table.getModel().addTableModelListener(modelListener);
    updateAvailability();
  }

  protected void updateAvailability(){
    int numSelectedRows = table.getSelectedRows().length;
    for (int i=0; i<keys.length; i++)
      setAvailable(keys[i], (numSelectedRows == 1));
  }

  class SelectionAdapter implements ListSelectionListener{
    @Override
    public void valueChanged(ListSelectionEvent event){
      updateAvailability();
    }
  }

  class ModelAdapter implements TableModelListener{
    @Override
    public void tableChanged(TableModelEvent event){
      updateAvailability();
    }
  }

}
