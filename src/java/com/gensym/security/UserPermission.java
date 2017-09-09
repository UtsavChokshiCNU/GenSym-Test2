package com.gensym.security;

import java.security.BasicPermission;

public class UserPermission extends BasicPermission
{

  static final long serialVersionUID = 1L;

  public UserPermission(String name)
  {
    super(name);
  }

  @Override
  public String toString() {
    return getName();
  }

}
