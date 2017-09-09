package com.gensym.cbu.odie;

import java.beans.PropertyChangeSupport;
import java.beans.PropertyChangeListener;
import com.gensym.denali.common.DenaliRemoteObject;
import java.io.Serializable;
import java.rmi.RemoteException;
import java.applet.AudioClip;
import java.applet.Applet;
import java.net.URL;
import java.net.MalformedURLException;
import javax.swing.JOptionPane;

public class DialogResponse extends DenaliRemoteObject implements Serializable, Response 
{
  PropertyChangeSupport support;
  String name = "DialogResponse";

  public DialogResponse() throws RemoteException
  {    
    support = new PropertyChangeSupport(this);
  }// end AudioResponse Constructor

	
  class ResponseThread implements Runnable
  {
    OdieEvent odieEvent;
    
    public ResponseThread(OdieEvent odieEvent)
    {
      this.odieEvent = odieEvent;
      Thread t = new Thread (this);
      t.start();
    }

    @Override
    public void run()
    {
      try {
	JOptionPane.showMessageDialog(null, //how can I get a frame here?
				      odieEvent.getMessageText() + "\n" +
				      odieEvent.getAdditionalText(),
				      "OdieEvent",
				      JOptionPane.INFORMATION_MESSAGE);
      }
      catch (RemoteException e)
	{
	  throw new Error("Dialog Response Thread (" + this +
				 ") encountered a remote exception error");
	}
    }
  }

  // Response Interface

  @Override
  public void respond(OdieEvent odieEvent) throws RemoteException
  {
    System.out.println(name + ": responding to event");
    new ResponseThread (odieEvent);
  }//end respond


  //end Response Interface

  public String getName()
  {
    return name;
  }

  public void setName (String name) 
  {
    String old = name;
    this.name = name;
    if (support != null) support.firePropertyChange("name", old, name);
  }

  public PropertyChangeSupport getSupport()
  {
    return support;
  }

  public void setSupport(PropertyChangeSupport support)
  {
    this.support = support;
  }

  public void addPropertyChangeListener(PropertyChangeListener listener)
  {
    support.addPropertyChangeListener(listener);
  }

  public void removePropertyChangeListener(PropertyChangeListener listener)
  {
    support.removePropertyChangeListener(listener);
  }
}









