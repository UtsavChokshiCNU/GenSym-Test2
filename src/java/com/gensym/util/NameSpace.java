package com.gensym.util;

import java.util.StringTokenizer;
import java.util.Hashtable;
import java.lang.Integer;
import java.lang.Character;

public class NameSpace extends Object
{
  private Hashtable table = new Hashtable();
   
  public void store (String key, Object value)
  {
    table.put(key,value);
  }
 
  public void store (int key, Object value)
  {
    table.put(key,value);
  }
  
  private void store (Object key, Object value)
  {
    table.put(key,value);
  }

  public Object lookup (Object key)
    {
      return table.get(key);
    }

  public Object lookup (int key)
    {
      return table.get(key);
    }

  private Object[] tokenizeURL(String url)
    {
      StringTokenizer tokenizer = new StringTokenizer(url,"/",false);
      int count = tokenizer.countTokens();
      Object[] parts = new Object[count];

      for (int i = 0 ; i<count ; i++)
	{
	  String piece = tokenizer.nextToken();
          int len = piece.length();
          char[] chars = new char[len];
	  boolean isInteger = ((len < 7) ? true : false);
          piece.getChars(0,len,chars,0);

          for (int j = 0 ; j<len ; j++)
	    if (!Character.isDigit(chars[j]))
	      {
		isInteger = false;
		break;
	      }
          
	  Object value = piece;
	  if (isInteger)
            { 
              int integer_value = -1;
	      try { 
	    	  integer_value = Integer.parseInt(piece);
	      }
	      catch (NumberFormatException e) {}
              value = integer_value;
	    }
          parts[i] = value;
        }
      return parts;
    }

  public Object lookupURL(String url)
    {
      Object[] parts = tokenizeURL(url);
      int len = parts.length;
      NameSpace ns = this;
      Object value = null;

      for (int i = 0 ; i<len ; i++)
	{
          value = ns.table.get(parts[i]);
          if (value instanceof NameSpace)
            ns = (NameSpace) value;
          else
	    break;
	}
      return value;
    }

  public void storeURL(String url, Object value)
    {
      Object[] parts = tokenizeURL(url);
      int len = parts.length;
      NameSpace ns = this;
      Object thing;

      for (int i = 0 ; i<(len - 1) ; i++)
	{
          thing = ns.table.get(parts[i]);
          if (thing instanceof NameSpace)
            ns = (NameSpace) thing;
          else
	    {
              NameSpace subspace = new NameSpace();
              ns.store(parts[i],subspace);
              System.out.println("adding subspace under "+parts[i]+" at "+i);
              ns = subspace;
	    }
	}
      ns.store(parts[len-1],value);
    }

  public static void main(String[] args)
  {
    NameSpace ns = new NameSpace();
    NameSpace subspace = new NameSpace();
    Object res = null;
    Object[] parts;

    ns.store("HAT_SIZE",8);
    res = ns.lookup("HAT_SIZE");
    ns.store("FRIENDS",subspace);
    subspace.store(1,"Burt");
    subspace.store(2,"Bingo");
    ns.storeURL("/FRIENDS/3","Lucky");
    ns.storeURL("/PETS/1","Spot");
    ns.storeURL("/PETS/2","Rover");
    ns.storeURL("/PETS/3","Fluffy");
    
    System.out.println("res= "+res);
    
    parts = ns.tokenizeURL("/FRIENDS/1");
    for (int i = 0 ; i< parts.length ; i++)
      {
        System.out.println("key["+i+"]="+parts[i]);
      }

    res = ns.lookupURL("/FRIENDS/1");
    System.out.println("/FRIENDS/1 -> "+res);
    res = ns.lookupURL("/FRIENDS/3");
    System.out.println("/FRIENDS/3 -> "+res);
    res = ns.lookupURL("/PETS/1");
    System.out.println("/PETS/1 -> "+res);
    res = ns.lookupURL("/PETS/3");
    System.out.println("/PETS/3 -> "+res);

    ns.storeURL("/FRIENDS/2","Chip");
    res = ns.lookupURL("/FRIENDS/2");
    System.out.println("/FRIENDS/2 -> "+res);
    
  }
}
