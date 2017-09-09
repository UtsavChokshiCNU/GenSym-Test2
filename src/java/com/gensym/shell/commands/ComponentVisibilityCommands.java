package com.gensym.shell.commands;

import java.awt.event.ActionEvent;
import java.awt.Component;
import java.util.Hashtable;
import com.gensym.uitools.utils.ComponentVisibilityEventSource;
import com.gensym.uitools.utils.ComponentVisibilityListener;
import com.gensym.uitools.utils.ComponentVisibilityEvent;
import com.gensym.shell.commands.DynamicListCommand;
public class ComponentVisibilityCommands extends DynamicListCommand implements ComponentVisibilityListener {

  protected static Hashtable compNames;

  public ComponentVisibilityCommands(){
    super();
    compNames = new Hashtable(5);
  }
  //addComponent assumes that it has state!
  public void addComponent(Component comp, String name, String image){
    compNames.put(name, comp);
    if (image != null)
      addNameAndImage(name, image);
    else
      addName(name);
    setState(name, comp.isVisible()?Boolean.TRUE:Boolean.FALSE);
    if (comp instanceof ComponentVisibilityEventSource)
      ((ComponentVisibilityEventSource)comp).addComponentVisibilityListener(this);      
  }

  public void addComponent(Component comp, String name){
    addComponent(comp, name, null);
  }
  
  public void removeComponent(String name){
    compNames.remove(name);
    removeName(name);
  }

  private void toggleState(String cmdKey) {
    Component comp = (Component)compNames.get(cmdKey);
    //if true - i.e. command selected, make invisible
    if (getState(cmdKey).booleanValue()){
      comp.setVisible(false);
      setState(cmdKey, Boolean.FALSE);
    }else { //if false, then show the component
      comp.setVisible(true);
      setState(cmdKey, Boolean.TRUE);
    }
  }

  private void updateState(String cmdKey) {
    Component comp = (Component)compNames.get(cmdKey);
    if (getState(cmdKey).booleanValue())
      setState(cmdKey, Boolean.FALSE);
    else
      setState(cmdKey, Boolean.TRUE);
  }
  
  @Override
  public void visibilityChanged(ComponentVisibilityEvent cve) {
    updateState(((Component)cve.getSource()).getName());
  }
  
  @Override
  public void  actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    toggleState(cmdKey);
  }
}
