package com.gensym.g2script;

import com.gensym.classtools.Access;

public class UncompiledField
{
  String name;
  Type   type;
  Access access;

  UncompiledField (String name, Type type, Access access)
  {
    this.name = name;
    this.type = type;
    this.access = access;
  }
}
