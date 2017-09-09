package com.gensym.uitools.inspect;

import com.gensym.shell.commands.DynamicListCommand;
import java.util.Hashtable;
import java.awt.event.ActionEvent;
import com.gensym.util.Symbol;

public class InspectHistoryCommand extends DynamicListCommand
{
  private Hashtable
  sessions = new Hashtable(),
    attributes = new Hashtable();
  private InspectWindow inspectWindow;

  public InspectHistoryCommand(InspectWindow inspectWindow)
  {
    this.inspectWindow = inspectWindow;
  }
  
  public void addSession(InspectSession session)
       //NOTE: WE ARE NOT PRESERVING THE PREFIX ON PURPOSE!
  {
    addSession(session, null);
  }

  private static String printAttributesArray(Symbol[] attributes)
  {
    String attrs = "(";
    for (int i=0;i<attributes.length;i++) {
      attrs+=attributes[i].toString().toLowerCase();
      if (i<attributes.length-1)
	attrs+=",";
    }
    attrs+=")";
    return attrs;
  }

  public void dispose() {
    sessions.clear();
    attributes.clear();
  }
  
  public void addSession(InspectSession session,
			 Symbol[] attributesToDisplay)
  {
    String name = session.getFilterText();
    if (attributesToDisplay != null &&
	attributesToDisplay.length > 0) {
      name+=printAttributesArray(attributesToDisplay);
      attributes.put(name, attributesToDisplay);
    }
    sessions.put(name, session);
    addName(name);
  }
  
  public void removeSession(InspectSession session)
  {
    String name = session.toString();
    sessions.remove(name);
    removeName(name);
  }

  @Override
  public void actionPerformed(ActionEvent e)
  {
    InspectControlPanel controlPanel = inspectWindow.getControlPanel();
    controlPanel.pause();
    //should launch a dialog asking whether they 
    //want to save the current search results
    controlPanel.stop();
    controlPanel.clear();
    
    String cmd = e.getActionCommand();
    InspectSession session = (InspectSession)sessions.get(cmd);
    controlPanel.setClassName(session.getClassName());
    controlPanel.setItemName(session.getItemName());
    controlPanel.setExtraFilters(session.getExtraFilters());
    Symbol[] attrs = (Symbol[])attributes.get(cmd);
    controlPanel.setDisplayAttributes(attrs);
    controlPanel.find();
  }
  
}
