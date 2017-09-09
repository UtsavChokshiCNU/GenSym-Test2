package com.gensym.cbu.odie;
 
import java.beans.*;
import com.gensym.denali.common.DenaliRemoteObject;
import java.io.*;
import java.rmi.*;
import java.applet.AudioClip;
import java.applet.Applet;
import java.net.URL;
import java.net.MalformedURLException;

public class AudioResponse extends DenaliRemoteObject implements Serializable, Response 
{
  PropertyChangeSupport support;
  String name = "AudioResponse";
  String audioURLasText = "http://localhost/odie/sounds/Catapult.WAV";
  URL audioURL;
  AudioClip audioClip;

  public AudioResponse() throws RemoteException, MalformedURLException
  {    
    support = new PropertyChangeSupport(this);
    if (audioURLasText != null)
      {
	setAudioURL(new URL(audioURLasText));
      }
  }// end AudioResponse Constructor

  void loadAudioURL()
  {
    audioClip = Applet.newAudioClip(audioURL);
  }
	
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
      System.out.println(name + ": AudioClip = " + audioClip + " = " + audioURLasText);
      if (audioClip != null)
	{
	  audioClip.play();
	}
    }
  }


  // Response Interface

  @Override
  public void respond(OdieEvent odieEvent) throws RemoteException
  {
    new ResponseThread(odieEvent);
  }//end respond

  //end Response Interface

  public void setAudioURL (URL audioURL) 
  {
    this.audioURL = audioURL;
    loadAudioURL();
  }

  public URL getAudioURL () 
  {
    return this.audioURL;
  }

  public String getName () 
  {
    return name;
  };

  public void setName (String name) 
  {
    String old = name;
    this.name = name;
    if (support != null) support.firePropertyChange("name", old, name);
  }

  public String getAudioURLasText () 
  {
    return audioURLasText;
  };

  public void setAudioURLasText (String audioURLasText) throws MalformedURLException
  {
    String old = name;
    this.audioURLasText = audioURLasText;
    URL newAudioURL = new URL(audioURLasText);
    if (newAudioURL != null)
      {
	setAudioURL(newAudioURL);
      }
    if (support != null) support.firePropertyChange("audioURLasText", old, audioURLasText);
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









