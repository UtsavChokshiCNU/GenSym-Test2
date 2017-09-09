package com.gensym.clscupgr.gms;

import com.gensym.util.Sequence;
import com.gensym.util.Symbol;

public class MenuDescription {

  private int      index;
  private String   label;
  private Object   key;
  private Symbol   type;
  private Symbol   iconClass;
  private boolean  isChecked;
  private Symbol   targetMode;
  private Sequence subMenu;
  private Symbol   parentType = null;

  public MenuDescription () {
  }

  public MenuDescription (int index, String label, Object key, Symbol type, Symbol iconClass,
			  boolean isChecked, Symbol mode, Sequence subMenu, Symbol parentType) {
    this.index = index;
    this.label = label;
    this.key =  key;
    this.type = type;
    this.iconClass = iconClass;
    this.isChecked = isChecked;
    this.targetMode = mode;
    this.subMenu = subMenu;
    this.parentType = parentType;
  }  

  public int getIndex() {
    return index;
  }

  public void setIndex(int index) {
    this.index = index;
  }

  public String getLabel() {
    return label;
  }

  public void setLabel(String label) {
    this.label = label;
  }

  public Object getKey() {
    return key;
  }

  public void setKey(Object key) {
    this.key = key;
  }

  public Symbol getType() {
    return type;
  }

  public void setType(Symbol type) {
    this.type = type;
  }

  public Symbol getIconClass() {
    return iconClass;
  }

  public void setIconClass(Symbol iconClass) {
    this.iconClass = iconClass;
  }

  public boolean getIsChecked() {
    return isChecked;
  }

  public void setIsChecked(boolean state) {
    isChecked = state;
  } 

  public Symbol getTargetMode() {
    return targetMode;
  }

  public void setTargetMode(Symbol mode) {
    targetMode = mode;
  }

  public Sequence getSubMenu() {
    return subMenu;
  }

  public void setSubMenu(Sequence subMenu) {
    this.subMenu = subMenu;
  }

  public Symbol getParentType() {
    return parentType;
  }

  public void setParentType(Symbol parentType) {
    this.parentType = parentType;
  }

  @Override
  public String toString() {
    return "INDEX: "+index+" LABEL: "+label+"  KEY: "+key+"  TYPE: "+type+"   ICONCLASS: "+iconClass+"  ISCHECKED: "+isChecked+"   TARGETMODE: "+targetMode+"  SUBMENU: "+subMenu+"  PARENT_TYPE: "+parentType;
  }
}
