package com.gensym.editor.icon.core;

import java.util.Vector;
import com.gensym.editor.icon.shell.IconEditorSimulationCommands;

public class Parameter {

  private String name;
  private Class type;
  private Object defaultValue;
  private String simulationPreferenceKey = IconEditorSimulationCommands.SCALAR;
  
  public Parameter(String name, Class type, Object defaultValue) {
    this.name = name;
    this.type = type;
    this.defaultValue = defaultValue;
  }

  public void setSimulationPreferenceKey(String key) {
    this.simulationPreferenceKey = key;
  }

  public String getSimulationPreferenceKey() {
    return simulationPreferenceKey;
  }
  
  @Override
  public boolean equals(Object object) {
    return ((object instanceof Parameter) &&
	    (((Parameter) object).getName().equals(name)));
  }

  @Override
  public String toString() {
    return name;
  }
  
  public String getName() {
    return name;
  }
  
  public Class getType() {
    return type;
  }

  private Vector listeners = new Vector();
  public void addValueListener(ValueListener listener) {
    listeners.addElement(listener);
  }

  public void removeValueListener(ValueListener listener) {
    listeners.removeElement(listener);
  }  

  private void notifyValueListeners() {
    ValueListener[] lstnrs = new ValueListener[0];
    synchronized(listeners) {
      lstnrs = new ValueListener[listeners.size()];
      listeners.copyInto(lstnrs);
    }
    ValueChangedEvent vce = null;
    synchronized (defaultValue) {
      vce = new ValueChangedEvent(this, defaultValue);
    }
    for (int i=0;i<lstnrs.length;i++) 
      lstnrs[i].valueChanged(vce);
  }
  
  public Object getDefaultValue() {
    return defaultValue;
  }

  public void setName(String name) {
    this.name = name;
  }
  
  public void setType(Class type) {
    this.type = type;
  }
  
  public void setDefaultValue(Object value) {
    this.defaultValue = value;
    notifyValueListeners();
  }
  
}
