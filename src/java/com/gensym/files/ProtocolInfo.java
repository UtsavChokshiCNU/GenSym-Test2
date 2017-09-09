package com.gensym.files;

import java.lang.reflect.*;

public class ProtocolInfo
{
  String name;
  String urlBase;
  Method parseMethod;

  public ProtocolInfo(String name, String urlBase, Method parseMethod)
  {
    this.name = name;
    this.urlBase = urlBase;
    this.parseMethod = parseMethod;
  }

}
