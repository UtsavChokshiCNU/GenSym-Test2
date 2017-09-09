package com.gensym.files;

public class BadURLFile extends URLFile
{
  String name;

  BadURLFile(String s)
  {
    super(FileType.SharedGenericFile);
    name = s;
  }

  @Override
  public String getName()
  {
    return name;
  }

  @Override
  public String getPath()
  {
    return name;
  }

  @Override
  public boolean isAbsolute()
  {
    return false;
  }
}
