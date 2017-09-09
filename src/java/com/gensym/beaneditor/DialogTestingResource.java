package com.gensym.beaneditor;

import com.gensym.dlgruntime.*;
import com.gensym.controls.ItemProxy;
import com.gensym.controls.DialogCommand;
import com.gensym.controls.ItemRetriever;
import com.gensym.classes.Item;

import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Symbol;
import com.gensym.message.Trace;

import com.gensym.beansruntime.G2ClassLoader;
import com.gensym.dlg.ErrorDialog;

import java.awt.Component;
import java.lang.reflect.Method;
import java.lang.reflect.InvocationTargetException;
import java.net.URL;
import java.util.Vector;

public class DialogTestingResource extends DialogResource
{
  public DialogTestingResource(byte[] serializedDialog,
			       DialogReader reader,
			       DialogLauncher launcher)
  {
    super(null,reader,launcher);
    setResourceData(serializedDialog);
  }

  public void launchForTesting(EditorFrame frame)
       throws ResourceInstantiationException
  {
    ComponentEditor application = frame.application;
    DialogReader reader = getDialogReader();

    Object dialogResource   = makeResource ();
    Component dialog        = reader.getComponent (dialogResource);
    ItemProxy[] proxies     = reader.getItemProxies (dialogResource);
    Object[] retrievers =  reader.getObjectsOfClass(dialogResource, ItemRetriever.class);
    Class commandClass = com.gensym.controls.DialogCommand.class;
    DialogCommand commandBean = reader.getDialogCommand(dialogResource);
    
    if (retrievers != null &&
	!ComponentEditor.noAutoActivationOfRetrievers)
      overrideAndActivateRetrievers(ItemRetriever.class,retrievers,
				    application.hostName,
				    application.portName);

    getDialogLauncher().launch (dialog, proxies , new String[0], new Item[0], commandBean);
  }

  private void hookupProxies (Class commandClass,
			      Object commandBean,
			      Class itemProxyClass,
			      Object[] proxies) {
    try {
      int numProxies = proxies.length;
      Object itemProxyArray =
	java.lang.reflect.Array.newInstance (itemProxyClass, numProxies);
      System.arraycopy (proxies, 0, itemProxyArray, 0, numProxies);
      Class itemProxyArrayClass = 
	itemProxyArray.getClass ();
      Method setProxiesMethod =
	commandClass.getMethod ("setProxies", new Class[]{itemProxyArrayClass});
      setProxiesMethod.invoke (commandBean, new Object[]{itemProxyArray});
    } catch (InvocationTargetException ite) {
      ite.getTargetException().printStackTrace();
      Trace.exception(ite.getTargetException ());
    } catch (Exception e) {
	Trace.exception(e);
    } 
  }

  private void hookupCloser (Class commandClass,
			     Object command,
			     DialogLauncher launcher,
			     Component c) {
    try {
      Method addDlgStateListenerMethod =
	commandClass.getMethod ("addDialogStateListener", new Class[] {com.gensym.dlgruntime.DialogStateListener.class});

      addDlgStateListenerMethod.invoke (command, new Object[] {launcher});
      ((DialogTestingLauncher)launcher).hookupJarCommandBean (command, c);
    } catch (InvocationTargetException ite) {
      ite.getTargetException().printStackTrace();
      Trace.exception(ite.getTargetException ());
    } catch (Exception e) {
	Trace.exception(e);
    }
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
  }
}
