package com.gensym.demos.dialogapplet;

import com.gensym.dlgruntime.*;
import com.gensym.controls.ItemProxy;
import com.gensym.controls.DialogCommand;
import com.gensym.classes.Item;

import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Symbol;
import com.gensym.message.Trace;

import com.gensym.dlg.ErrorDialog;

import java.applet.*;
import java.awt.*;
import java.lang.reflect.Method;
import java.lang.reflect.InvocationTargetException;
import java.net.URL;
import java.util.Vector;
import java.io.ObjectInputStream;
import java.io.ByteArrayInputStream;

public class DialogAppletReader extends DefaultDialogReader
{

  @Override
  public Object makeResource (Object data) throws ResourceInstantiationException {
    try {
      ObjectInputStream ois = new ObjectInputStream (new ByteArrayInputStream ((byte[])data));



      Object o = ois.readObject ();
      if (o instanceof Integer){
	Integer version = (Integer)o;
	if (version.intValue() == 2)
	  ois.readObject(); //skip list of jar names
	o = ois.readObject();
      }

      if (o instanceof Vector)
      {
         // Read out the hookups
         Vector hookups = (Vector)o;
         int size = hookups.size();

	 /*
         for (int h=0; h < size; h++)
         {
            HookupDefinition def = (HookupDefinition)hookups.elementAt(h);
            Class c = (G2ClassLoader.ourLoader).loadClass(def.name, def.bytes);
         }

	 */

         o = ois.readObject ();
      }

      return o;
    } catch (Exception e) {
      if (e instanceof java.io.StreamCorruptedException ||
	  e instanceof java.io.IOException ||
	  e instanceof java.lang.ClassNotFoundException ||
	  e instanceof java.io.OptionalDataException) {
	Trace.exception (e);
	throw new ResourceInstantiationException ("Exception while trying to create resource", e);
      } else
	throw (RuntimeException)e;
    }
  }
}
