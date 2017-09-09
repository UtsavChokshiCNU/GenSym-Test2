package com.gensym.cbu.mpe;

import java.util.Vector;

public class DFAResult
{
  String tokenName; // for no match
  String matchedText;
  Vector bindings = new Vector();

  DFAResult()
  {

  }

  void startBinding(String[] names, int index)
  {
    int i = 0,len = names.length;
    for (i=0; i<len; i++)
      startBinding1(names[i],index);
  }
  
  void startBinding1(String name, int index)
  {
    int i,len = bindings.size();
    for (i=0; i<len; i++)
      if (((Binding)bindings.elementAt(i)).name.equals(name))
	return;
    bindings.addElement(new Binding(name,index));
  }

  void endBinding(String[] names, int index)
  {
    int i = 0,len = names.length;
    for (i=0; i<len; i++)
      endBinding1(names[i],index);
  }
  
  void endBinding1(String name, int index)
  {
    int i,len = bindings.size();
    for (i=0; i<len; i++)
      if (((Binding)bindings.elementAt(i)).name.equals(name))
	{
	  ((Binding)bindings.elementAt(i)).end = index;
	  return;
	}
    throw new RuntimeException("binding end "+name+" w/o start");
  }
  
  MatchEvent makeMatchEvent(Object source)
  {
    String[] names = null;
    String[] values = null;
    if (bindings != null)
      {
	int i,len = bindings.size();
	names = new String[len];
	values = new String[len];
	for (i=0; i<len; i++)
	  {
	    Binding binding = (Binding)bindings.elementAt(i);
	    names[i] = binding.name;
	    if (binding.end == -1)
	      values[i] = matchedText.substring(binding.start);
	    else
	      values[i] = matchedText.substring(binding.start,binding.end);
	  }
      }
    return new MatchEvent(source,tokenName,matchedText,names,values);
  }
    
}

class Binding
{
  String name;
  int start;
  int end = -1;

  Binding(String name, int start)
  {
    this.name = name;
    this.start = start;
  }
}
