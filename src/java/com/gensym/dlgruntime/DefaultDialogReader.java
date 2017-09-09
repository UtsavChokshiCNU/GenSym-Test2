
package com.gensym.dlgruntime;

import java.net.URL;
import java.net.URLConnection;
import java.io.*;
import java.awt.*;
import java.util.Vector;
import java.util.Locale;
import com.gensym.controls.ItemProxy;
import com.gensym.controls.DialogCommand;
import com.gensym.dlg.TabGroupPanel;
import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;
import com.gensym.beansruntime.HookupDefinition;
import com.gensym.beansruntime.G2ClassLoader;
import com.gensym.beansruntime.BeanInputStream;
import com.gensym.util.UnexpectedException;

public class DefaultDialogReader implements DialogReader {

  private static Resource i18n =
  Resource.getBundle("com.gensym.dlgruntime.Messages");

  /*
   * Standard Tracing Requirements
   */
  public static final int defaultDialogFormatVersion = 2;//2: added list of loaded jar names
  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.dlgruntime.read",
			   DefaultDialogReader.class);
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.dlgruntime.TraceMessages", Locale.getDefault());

  private static final int DEF_TRACE_LEVEL = 5;
  private static final int DEF_WARN_LEVEL  = 2;

  /* Constructors
  private DefaultDialogReader (String[] args) {
    super(args);
  }
  */

  public DefaultDialogReader () {
  }



  /**
   * Read the contents of the resource into a byte array
   * @param resourceDescription must be a URL
   */
  @Override
  public Object readResource (Object resourceDescription) throws java.io.IOException {
    if (!(resourceDescription instanceof URL))
      throw new IllegalArgumentException(i18n.format("resourceDescriptionNotURL",
						     resourceDescription));
    URL resourceURL      = (URL)resourceDescription;
    

    URLConnection cxn    = resourceURL.openConnection ();
    cxn.connect ();
    int numBytesExpected = cxn.getContentLength ();
    byte[] resourceData  = new byte[numBytesExpected];
    InputStream is       = cxn.getInputStream ();
    int i=0;
    int ch;
    while ((ch = is.read()) != -1)
      resourceData[i++] = (byte)ch;
    int numBytesRead = i; //is.read (resourceData);
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "readResBytes",
		numBytesRead, resourceURL, numBytesExpected);
    return resourceData;
  }

  /**
   * Create an actual resource object from the data
   */
  @Override
  public Object makeResource (Object  resourceData) throws ResourceInstantiationException {
    if (!(resourceData instanceof byte[]))
      throw new IllegalArgumentException(i18n.format("resourceDataNotbyte[]",
						     resourceData));
    byte[] data = (byte[])resourceData;
    try {
      ObjectInputStream ois = new BeanInputStream (new ByteArrayInputStream (data), 
						   G2ClassLoader.ourLoader);

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

         for (int h=0; h < size; h++)
         {
            HookupDefinition def = (HookupDefinition)hookups.elementAt(h);
            Class c = (G2ClassLoader.ourLoader).loadClass(def.name, def.bytes);
         }

         o = ois.readObject ();
      }

      Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "readResourceObject", o);
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

  /** 
   * Get a top level component for this resource (a panel
   * if the resource is a PageLayout or a tabbed panel if 
   * the resource is a PageGroup)
   */
  @Override
  public Component getComponent (Object resource) {
    Component component = null;
    
    if (resource instanceof PageGroup) {
      PageGroup group    = (PageGroup)resource;
      String[]  pages    = group.getPages();
      String[]  tabNames = group.getTabNames();
      
      component = new TabGroupPanel();

      for (int i=0; i<pages.length; i++)
      {
         Object page = null;

         try
         {
            byte[] subResource = (byte[])readResource (new URL (group.getLocation(), pages[i]));
            page = makeResource (subResource);         
         }
         catch (java.io.IOException ex)
         {
	   throw new UnexpectedException(ex);
         }
	 catch (ResourceInstantiationException ex){
	   throw new UnexpectedException(ex);
	 }
         Component tab = getComponentFromPage((PageLayout)page);
         ((TabGroupPanel)component).addTab (tabNames[i], tab);
      }
    } else if (resource instanceof PageLayout) {
      component = getComponentFromPage((PageLayout)resource);
    } else if (resource instanceof Component) {
      component = (Component)resource;
    }

    // bug: what if they wanted something else?
    //set the background color
    component.setBackground(Color.lightGray);
    
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "returnComponent", component);
    return component;
  }


  protected Component getComponentFromPage (PageLayout page) {
    final PageLayout pg = page;

    Container panel     = new Container() {
      @Override
      public Dimension getPreferredSize () {
	return new Dimension (pg.getWidth (), pg.getHeight ());
      }
    };
    Object[] contents = page.getContents();
    
    for (int i=0; i<contents.length; i++)
    {
      Object bean = contents[i];
      if (bean instanceof Component)
	panel.add((Component)bean);
	
    }

    return panel;
  }
  
  /**
   * Get an array of item proxies contained in this resource
   */
  @Override
  public ItemProxy[] getItemProxies (Object resource)
  {
     ItemProxy[] proxies = null;

     if (resource instanceof PageGroup)
     {
         PageGroup group    = (PageGroup)resource;
         String[]  pages    = group.getPages();
         String[]  tabNames = group.getTabNames();

         for (int i=0; i<pages.length; i++)
         {
            Object page = null;

            try
            {
               byte[] subResource =  (byte[])readResource (new URL (group.getLocation(), pages[i]));
               page = makeResource (subResource);         
            }
	    catch (java.io.IOException ex)
	      {
		throw new UnexpectedException(ex);
	      }
	    catch (ResourceInstantiationException ex){
	      throw new UnexpectedException(ex);
	    }

            if (proxies == null)
                proxies = _getItemProxies((PageLayout)page);
         }
     }
     else if (resource instanceof PageLayout)
       proxies = _getItemProxies((PageLayout)resource);
     else if (resource instanceof SingleItemEditor)
       proxies = new ItemProxy[] {((SingleItemEditor)resource).getProxy()};
     else if (resource instanceof MultipleItemEditor)
       proxies = ((MultipleItemEditor)resource).getProxies();
     else
       // NOTE if adding new clauses here, keep the message up-to-date
       System.err.println(i18n.format
			  ("drunknownDialogClass",
			   new Object[]
			   {resource.toString(),
			      "com.gensym.dlgruntime.SingleItemEditor",
			      "com.gensym.dlgruntime.MultipleItemEditor"}));

     Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "returnProxies", proxies.length);
     return proxies;
  }

  private ItemProxy[] _getItemProxies (PageLayout page) {
    Vector   proxyVector = new Vector();
    Object[] contents    = page.getContents();
    
    for (int i=0; i<contents.length; i++) {
      if (contents[i] instanceof ItemProxy) 
	  proxyVector.addElement(contents[i]);
    }
    
    // Take the vector of ItemProxies and turn it into 
    // an array
    
    int numProxies = proxyVector.size();
    ItemProxy[] proxies    = new ItemProxy[numProxies];
    proxyVector.copyInto (proxies);
    
    return proxies;
  }

  @Override
  public Object[] getObjectsOfClass(Object resource, Class clazz)
  {
    Vector objectVector = new Vector();

    if (resource instanceof PageGroup)
      {
	PageGroup group    = (PageGroup)resource;
	String[]  pages    = group.getPages();
	String[]  tabNames = group.getTabNames();
	
	for (int i=0; i<pages.length; i++)
	  {
	    Object page = null;
	    try
	      {
		byte[] subResource =  (byte[])readResource (new URL (group.getLocation(), pages[i]));
		page = makeResource (subResource);         
	      }
	    catch (java.io.IOException ex)
	      {
		throw new UnexpectedException(ex);
	      }
	    catch (ResourceInstantiationException ex){
	      throw new UnexpectedException(ex);
	    }
	    getObjectsOfClassOnPage((PageLayout)page,objectVector,clazz);
	  }
     }
     else if (resource instanceof PageLayout)
       getObjectsOfClassOnPage((PageLayout)resource,objectVector,clazz);
     
     Object[] objects = new Object[objectVector.size()];
     objectVector.copyInto(objects);
     //System.out.println ("getObjectsOfClass (" + clazz.getName () + ") =" +
     //		  com.gensym.core.DebugUtil.printArray (objects));
     return objects;
  }


  private void getObjectsOfClassOnPage (PageLayout page, Vector objectVector, 
					    Class clazz)
  {
    Object[] contents = page.getContents();
    
    for (int i=0; i<contents.length; i++) {
      if (clazz.isAssignableFrom(contents[i].getClass()))
	objectVector.addElement(contents[i]);
    }
  }

  /**
   * Get an array of dialog closers contained in this resource
   */
  @Override
  public DialogCommand getDialogCommand (Object resource)
  {
     DialogCommand closer = null;

     if (resource instanceof PageGroup)
     {
         PageGroup group    = (PageGroup)resource;
         String[]  pages    = group.getPages();
         String[]  tabNames = group.getTabNames();

         for (int i=0; i<pages.length; i++)
         {
            Object page = null;

            try
            {
               byte[] subResource =  (byte[])readResource (new URL (group.getLocation(), pages[i]));
               page = makeResource (subResource);         
            }
	    catch (java.io.IOException ex)
	      {
		throw new UnexpectedException(ex);
	      }
	    catch (ResourceInstantiationException ex){
	      throw new UnexpectedException(ex);
	    }

            if (closer == null)
                closer = _getDialogCommand ((PageLayout)page);
         }
     }
     else if (resource instanceof PageLayout)
       closer = _getDialogCommand ((PageLayout)resource);
     else if (resource instanceof Commandable)
       closer = ((Commandable)resource).getDialogCommand();
     
     Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "returnClosers", 1);
     return closer;
  }

  private DialogCommand _getDialogCommand (PageLayout page) {
    DialogCommand closerBean = null;
    Object[] contents     = page.getContents();
    
    for (int i=0; i<contents.length; i++) {
      if (contents[i] instanceof DialogCommand) {
	if (closerBean != null)
	  throw new ResourceFormatException ("Only one DialogCommand bean is allowed");
	closerBean = (DialogCommand)contents[i];
      }
    }
    return closerBean;
  }

  /*
    // Testing code
  public static void main (String[] args) throws Exception {
    DefaultDialogReader reader = new DefaultDialogReader(args);
    byte[] resource = reader.readResource (new URL (args[0]));
    Object x = reader.makeResource (resource);
  }
  */
}


class ResourceFormatException extends RuntimeException {

  ResourceFormatException (String details) {
    super (details);
  }
}
