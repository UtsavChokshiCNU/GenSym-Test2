package com.gensym.rules;

import java.io.*;
import java.awt.*;
import java.awt.event.*;
import java.beans.*;

import com.gensym.g2scriptruntime.NamingService;
import com.gensym.g2scriptruntime.DefaultNamingService;

public class RuleHarness
{

  public static void main(String args[])
  {
    try {
      FileInputStream fis = new FileInputStream(args[0]);
      ObjectInputStream ois = new ObjectInputStream(fis);
      Rule rule = (Rule)ois.readObject();
      ois.close();
      rule.install();
      DefaultNamingService ns = new DefaultNamingService();
      RegistrationAdapter ra = new RegistrationAdapter();
      ns.setRegistrationListener(ra);
      
      Frame frame = new Frame();
      ns.put("Bob",frame);
      frame.setSize(600,600);
      frame.addWindowListener
	(
	 new WindowAdapter ()
	 {
	   @Override
	   public void windowClosing(WindowEvent e)
	     {
	       System.exit(0);
	     }
	 } ) ;
      
      Tank tank = new Tank();
      ns.put("Tim",tank);
      System.out.println("starting setLevel Test!");
      frame.show();
      tank.setLevel(10.0);
      tank.setLevel(99.0);
      tank.setCapacity(200.0);
      
    } catch (Exception e)
      {
	e.printStackTrace();
      }
  }
}

class Tank 
{
  private double level = 0.0;
  private double capacity = 100.0;
  private PropertyChangeSupport support;

  public Tank()
  {
    support = new PropertyChangeSupport(this);
  }

  public double getLevel()
  {
    return level;
  }

  public void setLevel(double level)
  {
    double old = this.level;
    this.level = level;
    support.firePropertyChange("level", new Double(old), new Double(level));
  }

  public double getCapacity()
  {
    return capacity;
  }

  public void setCapacity(double capacity)
  {
    double old = this.capacity;
    this.capacity = capacity;
    support.firePropertyChange("capacity", new Double(old), new Double(capacity));
  }

  public void addPropertyChangeListener(PropertyChangeListener listener)
  {
    Thread.dumpStack();
    support.addPropertyChangeListener(listener);
  }

  public void removePropertyChangeListener(PropertyChangeListener listener)
  {
    support.removePropertyChangeListener(listener);
  }


}
