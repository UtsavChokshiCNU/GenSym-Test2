package com.gensym.g2scriptruntime;

import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Vector;

public class DefaultNamingService implements NamingService
{
  Hashtable table = new Hashtable();
  RegistrationListener listener;

  public void put(String name, Object object)
  {
    // Maintain chain of objects with name under partial ordering
    // from "is subclass of".  No zero-length buckets permitted. 
    Bucket startBucket = (Bucket) table.get(name);
    if (startBucket == null)
      {
	table.put(name,new Bucket(object));
      }
    else
      {
	Class c2, c1 = object.getClass();
	Bucket bucket = startBucket, previous = null;
	while (true)
	  {
	    if (bucket == null)
	      {
		previous.next = new Bucket(object);
		break;
	      }
	    else
	      c2 = bucket.object.getClass();

	    if (c2 == c1) 
	      {
		bucket.object = object;
		break;
	      } 
	    else if (c2.isAssignableFrom(c1)) // i.e. c1 subclass of c2
	      {
		Bucket newBucket = new Bucket(object,bucket);
		if (previous != null)
		  previous.next = newBucket;
		else
		  table.put(name,newBucket);
	      }
	    else 
	      {
		previous = bucket;
		bucket = bucket.next;
	      }
	  }
      }
    fireRegistrationEvent(object,true);
  }

  @Override
  public Object lookup(String name, Class clazz)
  {
    Bucket bucket = (Bucket) table.get(name);
    if (bucket != null)
      {
	while (bucket != null)
	  {
	    if (clazz.isInstance(bucket.object))
	      return bucket.object;
	    else
	      bucket = bucket.next;
	  }
	return null;
      }
    else 
      return null;
  }

  @Override
  public Enumeration lookup(Class clazz)
  {
    Enumeration enumeration = table.elements();
    Vector elementsForClass = new Vector();
    while (enumeration.hasMoreElements())
      {
	Bucket bucket = (Bucket) enumeration.nextElement();
	do {
	  Object object = bucket.object;
	  if (clazz.isInstance(object))
	    {
	      elementsForClass.addElement(object);
	    }
	} while ((bucket = bucket.next) != null);
      }
    return elementsForClass.elements();
  }

  @Override
  public synchronized void setRegistrationListener(RegistrationListener listener)
  {
    this.listener = listener;
  }

  @Override
  public RegistrationListener getRegistrationListener()
  {
    return listener;
  }

  private void fireRegistrationEvent(Object o, boolean isAdd)
  {
    RegistrationEvent event = new RegistrationEvent(this,o);
    if (isAdd)
      listener.registerObject(event);
    else
      listener.deregisterObject(event);
  }

  public static void main(String[] args)
  {
    DefaultNamingService ns = new DefaultNamingService();
    ns.put("Bob",1);
    ns.put("Frank",2);
    ns.put("Louie",3.0);
    ns.put("Frank",4.0);
    
    System.out.println("Bob "+ns.lookup("Bob",Integer.class));
    System.out.println("Bob "+ns.lookup("Bob",Object.class));
    System.out.println("Frank"+ns.lookup("Frank",Integer.class));
    System.out.println("Frank"+ns.lookup("Frank",Double.class));
    System.out.println("Frank"+ns.lookup("Frank",Number.class));
    
  }

}

class Bucket 
{
  Object object;
  Bucket next = null;

  Bucket (Object object)
  {
    this.object = object;
  }

  Bucket (Object object, Bucket next)
  {
    this.object = object;
    this.next = next;
  }
}
