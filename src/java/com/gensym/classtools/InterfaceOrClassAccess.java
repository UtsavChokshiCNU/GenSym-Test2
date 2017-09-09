package com.gensym.classtools;

public class InterfaceOrClassAccess extends Access {
  InterfaceOrClassAccess(int flags) {
    super(flags);
  }
  
  public void addSuper() {
    accessFlags |= ACC_SUPER;
  }
}
