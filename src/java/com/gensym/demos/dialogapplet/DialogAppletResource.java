package com.gensym.demos.dialogapplet;

import com.gensym.dlgruntime.*;
import com.gensym.controls.ItemProxy;
import com.gensym.controls.DialogCommand;
import com.gensym.classes.Item;

import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Symbol;
import com.gensym.message.Trace;

import com.gensym.beansruntime.G2ClassLoader;
import com.gensym.dlg.ErrorDialog;

import java.applet.*;
import java.awt.*;
import java.lang.reflect.Method;
import java.lang.reflect.InvocationTargetException;
import java.net.URL;
import java.util.Vector;


public class DialogAppletResource extends DialogResource
{
  public DialogAppletResource(URL url)
  {
    super(url, new DialogAppletReader(), new DialogAppletLauncher());
  }

  public void launchForTesting(DialogApplet applet)
       throws ResourceInstantiationException
  {
    DialogReader reader     = getDialogReader();
    Object dialogResource   = makeResource ();
    Component dialog        = reader.getComponent (dialogResource);
    System.out.println("main component is "+dialog);
    if (dialog instanceof Container)
      {
	Container container = (Container)dialog;
	Component[] components = container.getComponents();
	for (int i = 0; i<components.length ; i++)
	  System.out.println("comp "+i+" = "+components[i]);
      }
    applet.setLayout(new BorderLayout());
    applet.add(dialog,"Center");
    Class retrieverClass = null;
    Object[] retrievers = null;
    try {
      retrieverClass 
	= Class.forName("com.gensym.controls.ItemRetriever");
    } catch (Exception e)
      {
	e.printStackTrace();
      }
    System.out.println("retrvrClass" + retrieverClass);
    if (retrieverClass != null)
      retrievers = reader.getObjectsOfClass(dialogResource,retrieverClass);
    
    System.out.println("retrvrClass" + retrieverClass+
		       "rtvrs" + retrievers +
		       "len "+ (retrievers == null ? 0 : retrievers.length));
    // ItemProxy[] proxies = reader.getItemProxies (dialogResource);
    ItemProxy[] proxies     = new ItemProxy[0]; 

    DialogCommand closer     = reader.getDialogCommand (dialogResource);
    getDialogLauncher().launch (dialog, proxies, 
		     new String[0], new Item[0], closer);
    applet.setBackground (Color.white);
    applet.validate();
    if (retrieverClass != null &&
	retrievers != null)
      overrideAndActivateRetrievers(retrieverClass,retrievers,
				    applet.hostName,
				    applet.portName);
  }
  
  
  private void overrideAndActivateRetrievers(Class retrieverClass,
					     Object[] retrievers,
					     String hostName,
					     String portName)
  {
    try {
      Method setHostName 
	= retrieverClass.getMethod("setHost",
				   new Class[] { java.lang.String.class });
      Method setPort 
	= retrieverClass.getMethod("setPort",
				   new Class[] { java.lang.String.class });
      Method retrieveItem
	= retrieverClass.getMethod("retrieveItem",
				   new Class[0]);
      int i,length = retrievers.length;
      if (hostName != null)
	for (i=0; i<length; i++)
	  setHostName.invoke(retrievers[i],new Object[] { hostName });
      if (portName != null)
	for (i=0; i<length; i++)
	  setPort.invoke(retrievers[i],new Object[] { portName });
      for (i=0; i<length; i++)
	retrieveItem.invoke(retrievers[i],new Object[0]);
      //Method retrieve = asdf;
      //retrieve.invoke();
    }
    catch (InvocationTargetException ite)
      {
	ite.getTargetException().printStackTrace();
	Trace.exception(ite);
      }
    catch (Exception e)
      {
	Trace.exception(e);
      }
  }


  public static void main(String[] args)
  {
    System.out.println("grr = "+DialogResource.getRegisteredReader());
  }
}
