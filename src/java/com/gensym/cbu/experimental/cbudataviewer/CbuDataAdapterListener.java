package com.gensym.cbu.experimental.cbudataviewer;


public interface CbuDataAdapterListener
{
  public void addCbuData(CbuData data);

  public void removeCbuData(CbuData data);
  
  public void cbuDataChanged(CbuData data, String propertyName, Object newPropertyValue);
}
