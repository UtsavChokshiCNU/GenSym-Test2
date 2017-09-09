package com.gensym.g2export.denali;

import java.util.Enumeration;

public interface DenaliService
{
  public void registerItem(com.gensym.g2export.G2__Base itm);

  public Enumeration getItems(com.gensym.g2export.KbWorkspace ws);

}
