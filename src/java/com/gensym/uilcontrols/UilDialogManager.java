package com.gensym.uilcontrols;

import java.awt.Component;
import java.awt.Dialog;
import java.awt.Panel;
import java.awt.Color;
import java.net.URL;
import java.net.MalformedURLException;
import java.util.Hashtable;
import com.gensym.jgi.*;
import com.gensym.dlgruntime.*;
import com.gensym.core.UiApplication;
import com.gensym.controls.ItemProxy;
import com.gensym.controls.DialogCommand;
import com.gensym.dlg.WarningDialog;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.UnexpectedException;
import com.gensym.classes.UiClientSession;
import com.gensym.classes.Item;
import com.gensym.message.Trace;

import java.lang.reflect.Method;

public class UilDialogManager
{
  private G2Access cnxn;
  private static final Symbol launchTranslatedUilDialog_ 
    = Symbol.intern("LAUNCH-TRANSLATED-UIL-DIALOG");
  private static Hashtable dialogResourceTable = new Hashtable();
  private static Hashtable launcherTable = new Hashtable();
  private static String dialogRepository;

  UilDialogManager(G2Access cnxn)
  {
    this.cnxn = cnxn;
    launcherTable.put(cnxn, this);
  }
  
  public static void setupLaunching(G2Access cnxn)
  {
    try {
      Method method 
	= UilDialogManager.class.getMethod("uilControlDialogCallback",
				     new Class[]
				     { Object.class,
				       Symbol.class,
				       Object.class,
				       Object.class,
				       Boolean.class});
      dialogRepository = System.getProperty ("com.gensym.beaneditor.uilconversionrepository", null);
      cnxn.registerJavaMethod(new UilDialogManager(cnxn),method,launchTranslatedUilDialog_,true);
    } catch (Exception e)
      {
	Trace.exception(e);
	// should probably call System.exit(0);
      }
  }

  public static void uilControlDialogCallback(G2Access cxn, 
					      Object targetObject,
					      Symbol targetAttribute,
					      Object actionArray,
					      Object initiatingItem){
    UilDialogManager launcher = (UilDialogManager)launcherTable.get(cxn);
    if (launcher != null)
      launcher.uilControlDialogCallback(targetObject, targetAttribute, actionArray, initiatingItem, Boolean.FALSE);
    else
      throw new IllegalArgumentException("There is no launcher associated with cxn "+cxn);
  }

  public void uilControlDialogCallback(Object targetObject,
				       Symbol targetAttribute,
				       Object actionArray,
				       Object initiatingItem,
				       Boolean modal)
  {
    try{
      if (targetObject instanceof String){
	DialogResource resource =  getResourceFromId((String)targetObject);
	Object dialogResource =  resource.makeResource();
	DialogReader reader = resource.getDialogReader();
	Component component = reader.getComponent (dialogResource);
	ItemProxy[] proxies = reader.getItemProxies (dialogResource);
	DialogCommand commandBean = reader.getDialogCommand(dialogResource);
	UilDialog dialog = new UilDialog(component, modal.booleanValue());
	if (commandBean instanceof UILDialogProxy){
	  UILDialogProxy dlgProxy = (UILDialogProxy)commandBean;
	  dlgProxy.setDialog(dialog);
	  if (initiatingItem instanceof UilClientPushbutton){
	    UilClientPushbutton button = (UilClientPushbutton)initiatingItem;
	    button.getDialogProxy().addChildDialog(dlgProxy);
	    dlgProxy.setLaunchActions(button.getActions());
	    dlgProxy.setButtonThatLaunchedDialog(button);
	  }
	}
	resource.getDialogLauncher().launch(dialog, proxies[0], 
					    (initiatingItem instanceof Item ? (Item)initiatingItem : null), 
					    commandBean);
      }
      else
	throw new IllegalArgumentException("Expecting targetObject to be a String");
    }
    catch(ResourceInstantiationException ex){
      //throw new UnexpectedException(ex);
      new WarningDialog(UiApplication.getCurrentFrame(), "Error", true, "Error instantiating resource <"+dialogRepository+"/"+targetObject+".ser> \n"+ex.toString(), null).setVisible(true);
      Trace.exception(ex);
    }
    catch(MalformedURLException ex){
      //throw new UnexpectedException(ex);
      new WarningDialog(UiApplication.getCurrentFrame(), "Error", true, "Unable to find resource <"+dialogRepository+"/"+targetObject+".ser>", null).setVisible(true);
    }
  }

  private DialogResource getResourceFromId(String id) throws MalformedURLException{
    DialogResource resource = (DialogResource)dialogResourceTable.get(id);
    if (resource == null){
      URL url = new URL(dialogRepository+"/"+id+".ser");
      resource = new DialogResource(url);
      dialogResourceTable.put(id, resource);
    }
    return resource;
  }

  private class UilDialog extends Dialog{
    UilDialog(Component component, boolean modal){
      super(UiApplication.getCurrentFrame());
      setModal(modal);
      Panel p = new Panel();//need panel for java.awt.TextField bug
      add(p);
      p.add(component);
      pack();
      setBackground (Color.lightGray);
      validate();
    }
  }
}
