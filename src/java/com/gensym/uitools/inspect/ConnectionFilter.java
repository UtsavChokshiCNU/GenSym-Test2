package com.gensym.uitools.inspect;

import com.gensym.uitools.tables.ItemFilter;
import com.gensym.jgi.G2Access;
import com.gensym.classes.Item;
import com.gensym.classes.ImplAccess;

public class ConnectionFilter implements ItemFilter
{
  private G2Access connection;

  public void setConnection(G2Access connection) {
    this.connection = connection;
  }
  
  @Override
  public boolean isFiltered(Item item) {
    if (connection != null) 
      return !connection.equals(((ImplAccess)item).getContext());
    else
      return false;
  }
  
}
