
/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	Native Dialog Manager - DialogManager.java
 *
 *
 */

package com.gensym.dlgruntime;

import java.awt.Component;
import java.awt.Frame; // temporary
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Hashtable;
import java.util.Locale;

import com.gensym.classes.ImplAccess;
import com.gensym.classes.Item;
import com.gensym.classes.MediaBin;
import com.gensym.controls.DialogCommand;
import com.gensym.controls.ItemProxy;
import com.gensym.core.GensymApplication;
import com.gensym.gcg.DefaultGeneratedDialogFactory;
import com.gensym.gcg.GeneratedDialogFactory;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ConnectionInfo;
import com.gensym.jgi.G2Gateway;
import com.gensym.message.MessageKey;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

/**
 *  This Class is used to request dialogs from the server or client.
 *  It uses a registry to determine if the dialogs are available locally.
 */

public class DialogManager {

  /*
   * Standard Tracing Requirements
   */
  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.dlgruntime.manager",
			   DialogManager.class);
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.dlgruntime.TraceMessages", Locale.getDefault());

  private static final int DEF_TRACE_LEVEL = 5;
  private static final int DEF_WARN_LEVEL  = 2;
  private static java.awt.Dimension screenDisplaySize = java.awt.Toolkit.getDefaultToolkit().getScreenSize ();
  private static final int dialogMargin = 25;

  private Hashtable registry   = new Hashtable ();

  private TwAccess context;
  private static volatile GeneratedDialogFactory dialogFactory = new DefaultGeneratedDialogFactory();

  /**
   *  The contructor for this class
   */
  public DialogManager (TwAccess context)
  {
    this.context = context;
  }

  public static GeneratedDialogFactory getGeneratedDialogFactory(){
    return dialogFactory;
  }

  public static void setGeneratedDialogFactory(GeneratedDialogFactory factory){
    dialogFactory = factory;
  }

  /**
   *  This method will find a DialogResource for the given arguments
   *  or generate one if none exists.
   */
  public synchronized DialogResource findResource (final Item item, final Symbol userMode, final Locale locale)
    throws G2AccessException, MalformedURLException {
	Item itemBean = item;
    int    time    = 0;
    Symbol g2Class = null;


    // 1)  Check the Registry to see if an entry for this
    //     Class/Instance already exists

    DialogResourceEntry entry = new DialogResourceEntry (itemBean, g2Class, userMode, locale);
    DialogResource resource   = findRegisteredResource (entry);

    if (resource == null) {
      g2Class = itemBean.getG2ClassName();
      itemBean = null;
      entry = new DialogResourceEntry (itemBean, g2Class, userMode, locale);
      resource   = findRegisteredResource (entry);
    }

    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "foundResourceInTable",
		resource, entry);

    if (resource == null)
      // resource = findOrGenerateResource (item, userMode, locale);
      resource = generateDialog (itemBean, userMode, locale);


    return resource;
  }

  /**
   * Used if we are completely unable to  find a reasonable frame
   * to be the Dialog's owner.
   * NOTE: As I review the code, it doesn't appear to be necessary
   * to have these two separate variables, but I couldn't be
   * bothered cleaning up at this point.
   */
  private static volatile Frame lastResortFrame;
  private static volatile Frame registeredFrame;

  /**
   * Use this only when not using
   * com.gensym.core.UiApplication.setCurrentFrame.
   * This frame will be used only if the requestingComponent
   * is not provided to editItem, and (following that) if
   * UiApplication.getCurrentFrame() returns null.
   * @deprecated As of Telewindows2 toolkit 1.1 rev. 0. Use
   * com.gensym.core.UiApplication.setCurrentFrame(Frame) instead
   * @see com.gensym.core.UiApplication#setCurrentFrame(Frame)
   */
  public static void registerFrame (Frame f) {
    registeredFrame = f;
  }

  private DialogResource findRegisteredResource (DialogResourceEntry entry) {
    return (DialogResource) registry.get (entry);
  }

  /**
   * @deprecated As of Telewindows2 Toolkit 1.1 rev 0, replaced by
   * editItem(Component, Item, Symbol, Locale);
   */
  public void editItem (Item item, Symbol userMode, Locale locale)
    throws G2AccessException, MalformedURLException, ResourceInstantiationException {
    editItem(null, item, userMode, locale);
  }

  /**
   * final for performance only
   */
  private static final Frame getFrameFromComponent(final Component component) {
	Component compBean = component;
    while (compBean != null &&
	   !(compBean instanceof Frame))
      compBean = compBean.getParent();
    return (Frame)compBean;
  }

  /** The editItem method is the main runtime entry point for this class.  It allows
   *  other components to launch a dialog for a com.gensym.classes.Item in a given
   *  user-mode and locale.  If no specialized dialog is found for this combination
   *  is found, a dialog will be generated based on the type information of the item.
   * @param <code>requestingComponent</code> the component that made
   * the request. editItem will attempt to find a Dialog or Frame to act
   * as the owner for the resulting Dialog, starting with the
   * <code>requestingComponent</code>. If unable to do so editItem will
   * first use the frame registered in registerFrame(Frame). If that
   * is null, it will use UIApplication.getCurrentFrame(), and if that
   * is null, it will make its own Frame and use that.
   * @since Telewindows2 Toolkit 1.1 rev 0
   */
  public void editItem(Component requestingComponent, Item item, Symbol userMode, Locale locale)
  throws G2AccessException, MalformedURLException, ResourceInstantiationException {
    //one example where the additions to GensymApplication are used to determine
    //at runtime if an item can be edited or not.
    boolean isItemPrivate = false;
    if(com.gensym.core.GensymApplication.getApplication()!= null)
      isItemPrivate = com.gensym.core.GensymApplication.getApplication().checkIfPrivate(item, true);
    if (isItemPrivate == true)
      return;

    Frame owner = getFrameFromComponent(requestingComponent);
    if (owner == null)
      owner = getFrameForDialog();
    DialogResource resource = findResource (item, userMode, locale);
    if (resource instanceof GeneratedDialogResource)
      {
	TwAccess connection = (TwAccess) ((ImplAccess)item).getContext();
	ItemProxy proxy = new ItemProxy();
	proxy.setProxy(item);
	DialogCommand dlgCmd = new DialogCommand();
	dlgCmd.setProxies(new ItemProxy[]{proxy});
	Component dialog = dialogFactory.generateDialog(owner, connection, proxy, dlgCmd, locale);
	DefaultGeneratedDialogLauncher launcher =
	  (DefaultGeneratedDialogLauncher)resource.getDialogLauncher();
	launcher.launch(owner, dialog);
	//dialog.doHackForAWTTextComponentBug();
      }
    else
      {
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "foundResource", resource, item);
	DialogReader   reader   = resource.getDialogReader();
	Object dialogResource   = resource.makeResource ();
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "createdResource", dialogResource);
	Component dialog        = reader.getComponent (dialogResource);
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "gotComponentForLaunch", dialog);
	ItemProxy[] proxies     = reader.getItemProxies (dialogResource);
	Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "gotProxiesForLaunch", proxies);
	int index = 0;
	  for (int i=0; i<proxies.length; i++){
	    if ((proxies[i].getSubObjectAttribute() == null)||
		(proxies[i].getSubObjectAttribute().equals(""))){
	      index = i;
	      break;
	    }
	  }
	DialogCommand closer     = reader.getDialogCommand (dialogResource);
	DialogLauncher launcher = resource.getDialogLauncher();
	launcher.launch (dialog, proxies[index], item, closer);
      }
  }

  private static final Symbol APPLICABLE_FOR_CLASS_ = Symbol.intern ("APPLICABLE-FOR-CLASS"),
                              URL_                  = Symbol.intern ("URL"),
                              JAVA_CLASS_           = Symbol.intern ("JAVA-CLASS"),
                              CLASS_NAME_           = Symbol.intern ("CLASS-NAME"),
                              SOURCE_               = Symbol.intern ("SOURCE");

  private final Hashtable localeMapping = new Hashtable (5);
  private static final Symbol LANGUAGE_ = Symbol.intern ("LANGUAGE"),
                              COUNTRY_  = Symbol.intern ("COUNTRY"),
                              VARIANT_  = Symbol.intern ("VARIANT");

  private Structure getLocaleStructure (Locale locale) {
    Structure g2Locale = (Structure) localeMapping.get (locale);
    if (g2Locale == null) {
      g2Locale = new Structure ();
      g2Locale.setAttributeValue (LANGUAGE_, locale.getLanguage ()); // All strings
      g2Locale.setAttributeValue (COUNTRY_ , locale.getCountry ());
      g2Locale.setAttributeValue (VARIANT_ , locale.getVariant ());
      localeMapping.put (locale, g2Locale);
    }
    return g2Locale;
  }

  private DialogResource generateDialog (Item item, Symbol userMode, Locale locale)
  {
    return new GeneratedDialogResource (null);
  }

  /** setDialogResourceEntry can associate a DialogResource with the combination
   *  of an item or className, userMode, and locale.  Supplying both a className
   *  and an item is not allowed.  The entries created or overridden by this
   *  method are used by editItem to find DialogResources to build Dialogs at
   *  runtime.
   */

  public void setDialogResourceEntry(Item item, Symbol className,
				     Symbol userMode, Locale locale,
				     DialogResource resource)
  {
    if (item != null && className != null)
      throw new IllegalArgumentException("cannot supply both item and className");

    DialogResourceEntry dre = new DialogResourceEntry (item, className, userMode, locale);
    registry.put (dre, resource);
  }
  public void setDialogResourceEntry(Item item, Symbol className,
				     Symbol userMode, Locale locale,
				     URL resourceURL)
  {
    DialogResource resource = new DialogResource (resourceURL);
    setDialogResourceEntry(item,className,userMode,locale,resource);
  }

  /** This variation of setDialogResource entry exists mainly so it
   *  can be called remotely from G2.  The localeStructure arguement
   *  should contain three attributes for the language, country and
   *  variant.  The variant argument is optional.  see the
   *  documentation for java.util.Locale for the precise meaning of
   *  these attributes.  The urlStructure argument should contain
   *  attributes SOURCE and LOCATION.  The SOURCE attribute should
   *  contain a com.gensym.classes.MediaBin or one of the symbols, URL
   *  or FILE.  If MediaBin is specified then the location should hold
   *  a String that defines a pathname in the MediaBin, separated by
   *  slashes. If the SOURCE attribute contains the symbol URL, there
   *  should be an attribute that holds a string containing the
   *  protocol, such as "http", and the location will be used as the
   *  tail of the URL.  If the SOURCE attribute contains the symbol
   *  FILE, then the location attribute should contain a file name. */

  public void setDialogResourceEntry(Symbol className,
				     Symbol userMode,
				     Structure localeStructure,
				     Structure urlStructure)
       throws G2AccessException, MalformedURLException
  {
    Locale locale = makeLocaleFromLocaleStructure(localeStructure);
    try {
      Object srcType = urlStructure.getAttributeValue(SOURCE_);
      if (JAVA_CLASS_.equals(srcType)) {
	String dialogClassName = (String)urlStructure.getAttributeValue(CLASS_NAME_);
	setDialogResourceEntry(null,className,userMode, locale,
			       new DialogResource(dialogClassName));
      } else {
	URL url = makeURLFromUrlStructure(urlStructure);
	setDialogResourceEntry(null,className,userMode, locale,
			       new DialogResource(url));
      }
    } catch (NoSuchAttributeException nsae) {
      throw new MalformedURLException("Illegal Resource Description3!");
    }
  }

  /** This variant of setDialogResource is similar to the above one,
   *  except that it allows a dialog to be overridden for a specific item
   *  rather than a class.
   */

  public void setDialogResourceEntry(Item item,
				     Symbol userMode,
				     Structure localeStructure,
				     Structure urlStructure)
       throws G2AccessException, MalformedURLException
  {
    setDialogResourceEntry(item,null,userMode,
			   makeLocaleFromLocaleStructure(localeStructure),
			   makeURLFromUrlStructure(urlStructure));
  }

  /** clearDialogResourceEntry will disassociate any associations
   *  made by a corresponding call to setDialogResourceEntry.  See it's
   *  documentation for details on the arguments.
   */

  public void clearDialogResourceEntry(Item item, Symbol className,
				       Symbol userMode, Locale locale)
  {
    if (item != null && className != null)
      throw new IllegalArgumentException("cannot supply both item and className");

    DialogResourceEntry dre = new DialogResourceEntry (item, className, userMode, locale);
    registry.remove(dre);
  }

  /** This variant of clearDialogResourceEntry exists as convenience to be called
   * remotely from G2.  It provides a means of removing knowledge of a class-wide
   * dialog.
   */
  public void clearDialogResourceEntry(Symbol className,
				       Symbol userMode,
				       Structure localeStructure)
  {
    clearDialogResourceEntry(null,className,userMode,
			     makeLocaleFromLocaleStructure(localeStructure));
  }

   /** This variant of clearDialogResourceEntry exists as convenience to be called
   * remotely from G2.  It provides a means of removing knowledge of a instance-specific
   * dialog.
   */
  public void clearDialogResourceEntry(Item item,
				       Symbol userMode,
				       Structure localeStructure)
  {
    clearDialogResourceEntry(item,null,userMode,
			     makeLocaleFromLocaleStructure(localeStructure));
  }

  private Locale makeLocaleFromLocaleStructure(Structure localeStructure)
  {
    Object language = localeStructure.getAttributeValue(LANGUAGE_,null);
    Object country = localeStructure.getAttributeValue(COUNTRY_,null);
    Object variant = localeStructure.getAttributeValue(VARIANT_,null);
    if (language instanceof String &&
	country instanceof String)
      {
	if (variant instanceof String)
	  return new Locale((String)language, (String)country, (String)variant);
	else
	  return new Locale((String)language, (String)country);
      }
    else
      throw new IllegalArgumentException("must supply language, country, and variant strings");
  }

  private static final Symbol
    FILE_     = Symbol.intern ("FILE"),
    PROTOCOL_ = Symbol.intern ("PROTOCOL"),
    LOCATION_ = Symbol.intern ("LOCATION"),
    HOST_     = Symbol.intern ("HOST"),
    PORT_     = Symbol.intern ("PORT");

  private static final String fileSeparator = System.getProperty ("file.separator");

  private URL makeURLFromUrlStructure (Structure result)
       throws G2AccessException, MalformedURLException
  {
    try {
      java.lang.Object src = result.getAttributeValue (SOURCE_);
      String location      = (String) result.getAttributeValue (LOCATION_);
      if (src instanceof MediaBin) {
	MediaBin mediaBin = (MediaBin)src;
	Symbol binName = (Symbol) mediaBin.getNames ();
	G2ConnectionInfo cxnInfo = ((G2Gateway)context).getG2ConnectionInfo ();
	String host = cxnInfo.getHost ();
	String port = cxnInfo.getPort ();
	String urlString = "g2://" + host + ":" + port + "/" + com.gensym.net.g2.NamedMediaBinHandler.MAGIC_MARKER + "/" +
	  binName + location;
	return new URL (urlString);
      } else if (src instanceof Symbol && src.equals (URL_)) {
	Symbol protocol_ = (Symbol)result.getAttributeValue (PROTOCOL_);
	if (protocol_ == null)
	  throw new MalformedURLException ("Missing PROTOCOL component for resource URL");
	String protocol = protocol_.getPrintValue ().toLowerCase ();
	String host     = (String) result.getAttributeValue (HOST_, null);
	String port     = (String) result.getAttributeValue (PORT_, null);
	String urlString = protocol + "://" + (host == null ? "" : host)
	  + (port == null ? "" : ":" + port)
          + location;
	return new URL (urlString);
      } else if (src instanceof Symbol && src.equals (FILE_)) {
	if ("\\".equals(fileSeparator))
	  location = location.replace ('\\', '/');
	String urlString = "file:///" + location;
	return new URL (urlString);
      } else
	throw new MalformedURLException ("Illegal Resource Description!");
    } catch (NoSuchAttributeException nsae) {
      throw new MalformedURLException ("Illegal ResourceDescription2!");
    }
  }

  private static Frame getFrameForDialog () {
    Frame frame = com.gensym.core.UiApplication.getCurrentFrame ();
    if (frame == null) {
      frame = registeredFrame;
      if (frame == null) {
	if (lastResortFrame == null) {
	  synchronized (DialogManager.class) {
	    if (lastResortFrame == null) {
	      lastResortFrame = new Frame ();
	      lastResortFrame.setBounds (screenDisplaySize.width/2 - 5, screenDisplaySize.height/2 - 5, 10, 10);
	      lastResortFrame.addNotify ();
	    }
    }
	}
	frame = lastResortFrame;
	if (GensymApplication.getDevOption()) {
	  System.out.println("DialogManager using own frame " + frame);
	}
      }
    }

    return frame;
  }

  static {
    DialogResource.registerReader (new DefaultDialogReader ());
    DialogResource.registerLauncher (new DefaultDialogLauncher ());
  }
}

/**
 *  This Class is used to represent an entry in a registry for a dialog which
 *  has been launched for a particular class/instance
 */

class DialogResourceEntry {

  /*
   * Standard Tracing Requirements
   */
  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.dlgruntime.manager",
			   DialogManager.class);
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.dlgruntime.TraceMessages", Locale.getDefault());

  private static final int DEF_TRACE_LEVEL = 5;
  private static final int DEF_WARN_LEVEL  = 2;

  Item itm;
  Symbol className;
  Symbol userMode;
  Locale locale;

  DialogResourceEntry (Item itm, Symbol className, Symbol userMode, Locale locale) {
    this.itm       = itm;
    this.className = className;
    this.userMode  = userMode;
    this.locale    = locale;
  }
  
  @Override
  public boolean equals (Object other) {
    if (other == null || !getClass().equals(other.getClass())){
      return false;
    }
    
    DialogResourceEntry otherDRE = (DialogResourceEntry)other;

    boolean isItemEquals = (itm != null && itm.equals (otherDRE.itm)) ;
    boolean isClassNameEquals = className != null && className.equals (otherDRE.className);
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "dlgResEntryEq",
		new Object [] {this, otherDRE,
				userMode.equals (otherDRE.userMode) &&
					       locale.equals (otherDRE.locale) &&
					       (isItemEquals || isClassNameEquals),
				 userMode.equals (otherDRE.userMode),
				 locale.equals (otherDRE.locale),
				 isItemEquals,
				 isClassNameEquals});

    return (userMode.equals (otherDRE.userMode) && locale.equals (otherDRE.locale) &&
    			(isItemEquals || isClassNameEquals));
  }

  private int hashCode = -1;
  @Override
  public synchronized int hashCode () {
    if (hashCode == -1) {
      hashCode =
	((itm == null? 0 : itm.hashCode ()) << 24) ^
	((className == null? 0 : className.hashCode ()) << 16) ^
	userMode.hashCode () ^
	locale.hashCode ();
    }
    return hashCode;
  }

  @Override
  public String toString () {
    return super.toString () + "[Itm=" + itm +
      ",class=" + className +
      ",mode=" + userMode +
      ",locale=" + locale + "]";
  }
}
