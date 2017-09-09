package com.gensym.g2script;

class LocalVariable
{
  String g2Name;
  String javaName;
  String g2Type;
  Type type;
  boolean isThis;

  
  LocalVariable(String g2Name, String javaName, Type type)
  {
    this.g2Name = g2Name;
    this.javaName = javaName;
    this.type = type;
    
  }
}
