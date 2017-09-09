package com.gensym.cbu.experimental.mibbrowser;

import java.util.*;

public class MibFileObjectHashtable extends Hashtable
{
  public MibFileObjectHashtable()
    {
      super();

      MibFileObject mfo = addMibFileObject("iso", "1", null);
      mfo.setFullSymbolicName(mfo.getSymbolicName());
      mfo.setFullNumericName(mfo.getNumericName());
      
      addMibFileObject("org", "3", "iso");
      addMibFileObject("dod", "6", "org");
      addMibFileObject("internet", "1", "dod");
      addMibFileObject("directory", "1", "internet");
      addMibFileObject("experimental", "3", "internet");
      addMibFileObject("private", "4", "internet");
      addMibFileObject("enterprises", "1", "private");
      addMibFileObject("mgmt", "2", "internet");
      addMibFileObject("mib-2", "1", "mgmt");
      addMibFileObject("mib", "1", "mgmt");
      addMibFileObject("system", "1", "mib");
      addMibFileObject("interfaces", "2", "mib");
      addMibFileObject("at", "3", "mib");
      addMibFileObject("ip", "4", "mib");
      addMibFileObject("icmp", "5", "mib");
      addMibFileObject("tcp", "6", "mib");
      addMibFileObject("udp", "7", "mib");
      addMibFileObject("egp", "8", "mib");

    }

  MibFileObject addMibFileObject(String symbolicName,
				 String numericName,
				 String parentSymbolicName)
    {
      MibFileObject mfo = new MibFileObjectAdapter();
      mfo.setSymbolicName(symbolicName);
      mfo.setNumericName(numericName);
      mfo.setParentSymbolicName(parentSymbolicName);
      put(mfo.getSymbolicName(), mfo);
      return mfo;
    }

  @Override
  public Object put(Object key, Object value)
    {
      Object rv = null;
      
      if (containsKey(key))
	{
	  System.out.println("hashtable already has a MibFileObject stored under the key : " + key);
	}
      else
	{
	  rv = super.put(key, value);
	  if (rv != null) System.out.println("How did this happen in my hashtable?");
	}

      return rv;
    }
}
