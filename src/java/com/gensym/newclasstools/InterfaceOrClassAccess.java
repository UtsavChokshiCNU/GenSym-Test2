package com.gensym.newclasstools;

public class InterfaceOrClassAccess extends Access {
  InterfaceOrClassAccess(int flags) {
    super(flags);
  }
  
  public void addSuper() {
    accessFlags |= ACC_SUPER;
  }
}
