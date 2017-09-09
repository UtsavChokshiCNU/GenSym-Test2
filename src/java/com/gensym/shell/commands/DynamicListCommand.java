package com.gensym.shell.commands;

import java.util.Vector;
import java.util.Hashtable;
import java.util.Enumeration;
import java.awt.Frame;
import java.awt.Toolkit;
import java.awt.Image;
import java.awt.event.ActionEvent;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2ConnectionListener;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.jgi.G2AccessInitiationException;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwGateway;
import com.gensym.message.Resource;
import com.gensym.shell.util.*;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.SubCommandInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.message.Trace;
import com.gensym.classes.KbWorkspace;
import com.gensym.util.Structure;
import com.gensym.message.Resource;
import java.util.MissingResourceException;

public abstract class DynamicListCommand extends AbstractStructuredCommand
{

  private boolean radioBehavior = false;
  private Vector names;
  private Vector images;
  private Resource shortResource, longResource;
  private Hashtable states;
  

  public DynamicListCommand()
  {
    super (new CommandInformation[]{});
    names = new Vector();
    images = new Vector();
    states = new Hashtable(5);
  }

  public void setShortResource(Resource shortResource)
  {
    this.shortResource = shortResource;    
  }

  public void setLongResource(Resource longResource)
  {
    this.longResource = longResource;
  }

  @Override
  public void setState(String name, Boolean hasState){
    states.put(name, hasState);
    try {
      setStructuredKeys(createCommandInfos());
    } catch (IllegalArgumentException iae) {
      int index = names.indexOf(name);
      names.removeElement(name);
      images.removeElementAt(index);
      states.remove(name);
    }
  }
  
  private CommandInformation[] createCommandInfos()
  {
    int count = names.size();
    boolean available = count > 0;
    Boolean hasState;
    CommandInformation[] infos = new CommandInformation[count];
    for (int i=0; i<count; i++){
      String name = (String)names.elementAt(i);
      String image = (String)images.elementAt(i);
      if(states != null){
	hasState = (Boolean)states.get(name);
      } else //no state
      hasState = null;
      
      String shortDesc, longDesc;
      try {
	if (shortResource != null)
	  shortDesc = shortResource.getString(name);
	else
	  shortDesc = name;
	if (longResource != null)
	  longDesc = longResource.getString(name);
	else
	  longDesc = name;
      } catch (MissingResourceException mre) {
	shortDesc = name;
	longDesc = name;
      }
      infos[i] = 
	new CommandInformation(name, true, null, null, image, null, 
			       hasState,
			       true,
			       shortDesc, longDesc,
			       null, null);
    }  
    return infos;
  }

    
  public void removeName(String name)
  {
    int i = names.indexOf(name);
    if (i>0) {
      names.removeElementAt(i);
      images.removeElementAt(i);
      if(states != null) states.remove(name);
      setStructuredKeys(createCommandInfos());
    }
  }
  
  public void addName(String name)
  {
    addNameAndImage(name, null);
  }

  public void addNameAndImage(String name, String image) {
    names.addElement(name);
    images.addElement(image);
    try {
      setStructuredKeys(createCommandInfos());
    } catch (IllegalArgumentException iae) {
      names.removeElement(name);
      images.removeElement(image);
    }
  }
  
  public void setImages(Vector images) {
    this.images = images;
  }
  public void setNames(Vector names)
  {
    this.names = names;
    setStructuredKeys(createCommandInfos());
  }
  
  public boolean getRadioBehavior()
  {
    return radioBehavior;
  }

  public void setRadioBehavior(boolean radioBehavior)
  {
    this.radioBehavior = radioBehavior;
  }

  @Override
  public abstract void actionPerformed(ActionEvent e);
  
}
