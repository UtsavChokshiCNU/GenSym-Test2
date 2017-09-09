package com.gensym.g2export;

public interface G2ObjectConverter
{
  public java.lang.Object toLocalAttribute(java.lang.Object obj);

  public java.lang.Object toG2Attribute(java.lang.Object obj);

  public java.lang.Object toLocalParameter(java.lang.Object obj);

  public java.lang.Object toG2Parameter(java.lang.Object obj);
}
