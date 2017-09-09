package com.gensym.devtools;

import java.io.Serializable;

class Pair implements Serializable
{
  public final String name;
  public final String value;

  public Pair(String pname, String pvalue)
  {
    name=pname;
    value=pvalue;
  }

  public String header()
  {
    return name+": "+value;
  }

  @Override
  public boolean equals(Object obj)
  {
    if (obj == null || !(obj.getClass().equals(this.getClass())))
      return false;
    
    return name.equalsIgnoreCase(((Pair)obj).name);
  }

  @Override
  public int hashCode() {
	final int prime = 31;
	int result = 1;
	return prime * result + ((this.name == null) ? 0 : this.name.hashCode());
  }
  
  @Override
  public String toString () {
    return "Pair [" + name + "=" + value + "]";
  }
}
