package com.gensym.classes;

import java.awt.*;
import java.beans.*;
import java.io.*;
import java.lang.reflect.*;
import java.util.*;

import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.jgi.*;
import com.gensym.dlgevent.*;
import com.gensym.dlg.MessageDialog;

/**
 * This class is the root class of all wrapped G2Beans created from the
 * G2BeanBuilder. It sub classes java.awt.component so that it can be
 * used with in a visual development tool such as BeanBox.
 */
public class G2_ItemWrapper extends Component implements ItemListener, ObjectChangeListener{

  static final long serialVersionUID = -6224243325478303746L;

  private static final Symbol ITEM_ = Symbol.intern ("ITEM");
  private static final Symbol WIDTH_ = Symbol.intern ("WIDTH");
  private static final Symbol HEIGHT_ = Symbol.intern ("HEIGHT");
  private static final Symbol NAME_ = Symbol.intern ("NAME");
  protected static final String itemNotAvailableString = "The G2 Item has not been fetched";
  protected static String iconComponentClassName = "com.gensym.ntw.util.G2BeanIconRender";

  private transient ItemInfo info = null;
  private transient boolean noIcon = true;
  protected transient Item item;
  private Vector itemWrapperListeners; 
  private transient String oldURL = "";
  private transient G2Access context = null;
  protected PropertyChangeSupport changeSupport; 
  protected Vector  objectUpdateListeners=null; 
  protected boolean itemFetched = false;
  private String sourceURL = "g2://localhost:1111/NAME";
  private transient Component iconComponent = null;
  private boolean noLoadableIconComponent = false;
  private java.lang.Class iconComponentClass = null;  
  private boolean showIconUpdates = false;
  private boolean scaleImageToFit = true;
  private boolean useG2Icon = true;


  private boolean showUIForInformationMessage = false;
  //private transient IconElement drawElement;

  /**
   * Getter for the sourceURL property. The source URL specifies a G2
   * item within a specific G2.
   * @return The current value of the sourceURL property.
   */
  public String getSourceURL () {
    return sourceURL;
  }



  /**
   * Set the sourceURL property, which specifies the G2 item to wrap within
   * this component bean.
   * e.g. g2:://localhost:1111/A-G2-ITEM
   * Where A-G2-Item is located within a G2 server at host name localhost port 1111.
   * @param url The sourceUrl string
   */
  public void setSourceURL (String url)
       throws G2AccessException,
	 G2AccessInitiationException,
	 ConnectionTimedOutException
  {
    sourceURL = url;
    if (item != null)
      setG2ItemFetched(true);
  }

  /**
   * Add a G2_ItemWrapperListener to the ItemWrapperListener list. The
   * G2_ItemWrapperListener will be informed when a G2 Item is successfully
   * received and accesible from this object.
   * @param il The G2_ItemWrapperListener to add.
   */
  public void addG2_ItemWrapperListener (G2_ItemWrapperListener il) {
    if (itemWrapperListeners == null)
      itemWrapperListeners = new Vector();

    itemWrapperListeners.addElement(il);
  }

  /**
   * Remove a G2_ItemWrapperListener from the ItemWrapperListener list.
   * @param il The G2_ItemWrapperListener to remove.
   */
  public void removeG2_ItemWrapperListener (G2_ItemWrapperListener il) {
    if (itemWrapperListeners == null)
      itemWrapperListeners = new Vector();

    itemWrapperListeners.removeElement(il);
  }

  /**
   * @undocumented
   */
  protected void fireItemReceived (Item item) throws G2AccessException {
    if (itemWrapperListeners != null) {
      G2_ItemWrapperEvent evt = new G2_ItemWrapperEvent (this);

      java.util.Vector targets;
      synchronized (this) {
	if (itemWrapperListeners == null) {
	  return;
	}
	targets = (java.util.Vector) itemWrapperListeners.clone();
      }

      for (int i = 0; i < targets.size(); i++) {
	G2_ItemWrapperListener target = (G2_ItemWrapperListener)targets.elementAt(i);
	target.itemReceived (evt);
      }
    }
  }

  /**
   * @undocumented
   */
  protected void checkItem (G2__BaseImpl item) {
    if (item == null) {
      ItemNotAvailableException inae = new ItemNotAvailableException (itemNotAvailableString);
      informUser (null, inae);
      throw inae;
    }
  }

  /**
   * @undocumented
   */
  protected void fireItemRemoved () throws G2AccessException {}

  /**
   * Gives the item that this G2_ItemWrapper is wrapping
   * @return true if this object is currently wrapping a G2 Item.
   */
  public boolean getG2ItemFetched() {
    return (item != null);
  }

  /**
   * This method enables the setting of this property.
   * If set true when previously false, then the sourceURL
   * will be used to attempt to fetch a reference to a G2 Item.
   * If set false when previouly true any refernce G2 Item will be dropped.
   * @param status The new value for the g2ItemFetched property.
   */
  public void setG2ItemFetched(boolean status)
       throws G2AccessException,
  	 ConnectionTimedOutException,
	 G2AccessInitiationException {
    if (status) {
	fetchG2Item();
	oldURL = sourceURL;
    } else {
      _changeItemFetched(false);
      // Need to remove Item Listeners here !!!!
    }
  }

  /**
   * This method wraps up a given G2 Item, do not us the sourceURL.
   * @param theItem The G2 Item to wrap.
   */
  public boolean wrapG2Item(Item theItem) throws G2AccessException {
    try {
      return _wrapUpNewItem(theItem);
    } catch (G2AccessException e) {
      _changeItemFetched(false);
      Trace.exception(e);
      informUser("While wrapping " + theItem, e);
      throw e;
    }
  }

  /**
   * Force The G2 Item to be fetch using the sourceURL field, this
   * method is equivalent to performing setG2ItemFetched(true).
   *
   * @return true if the call item was fetched
   */
  public boolean fetchG2Item ()
       throws G2AccessException,
	 ConnectionTimedOutException,
	 G2AccessInitiationException {
    Item newItem = null;
    try {
      item = _getWrappedItem();
      newItem = item;
      return _wrapUpNewItem(item);

      //item.setLocallyCached (true);
    } catch (G2AccessException e) {
      Trace.exception(e);
      if (newItem != null)
	informUser("While Wrapping " + newItem, e);
      else
	informUser("While Fetching the G2 Item " + e);
      _changeItemFetched(false);
      throw e;
    }
  }

  /**
   * Get the current connection used to get the wrapped Item.
   * @return the G2Access used to fetch the G2 wrapped item from G2,
   * null if none.
   */
  public G2Access getConnection() {
    return context;
  }


  /**
   * Get the current setting for setScaleImageToFit.
   * @param boolean flag controling if icon image is to be scaled to
   *        fit within the bounds of this item
   */
  public void setScaleImageToFit(boolean newScaleImageToFit) {
    scaleImageToFit = newScaleImageToFit;

    if(iconComponent!=null)
      { iconComponent.setSize(this.getSize());
        setIconComponentScaleImageToFit(newScaleImageToFit);
    }
    repaint();
  }


  /**
   * This method allows the setting of the scaleImageToFit attribute; which
   * indicates if the image for this bean is to be scaled so as to fit
   * within the bounds of the bean or not.
   * @return boolean flag representing this property
   */
  public boolean isScaleImageToFit() {
    return scaleImageToFit;
  }


  /**
   * This method allows the setUseG2Icon property to be set.
   * If true, indicates that the bean will use the G2 icon for the class as
   * its graphical representaton. If false the bean will display the image as
   * specified in its bean info file.
   * @param boolean flag to set this Java object to use
   *        the G2 icon of the G2 item it represents
   */
  public void setUseG2Icon(boolean newUseG2Icon) {
    useG2Icon = newUseG2Icon;
    repaint();

  }

  /**
   * This method returns a boolean value representing the property.
   * If true, indicates that the bean will use the G2 icon for the class as
   * its graphical representaton.  If false the bean will display the image as
   * specified in its bean info file.
   * @return boolean flag representing this property
   */
  public boolean isUseG2Icon() {
    return useG2Icon;
  }



  /**
   * This method enables the setting of the showIconUpdates attribute.
   *
   * @param boolean flag to set this Java object to show icon color and
   *        variable changes in the icon of the G2 item it represents
   */
  public void setShowIconUpdates(boolean newShowIconUpdates) {
    showIconUpdates = newShowIconUpdates;
    setIconComponentShowIconUpdates(newShowIconUpdates);
  }

  /**
   * This method allows the boolean value of the showIconUpdates attribute to
   * be obtained.
   * @return boolean flag if true this Java object shows icon color and
   *        variable changes in the icon of the G2 item it represents
   */
  public boolean isShowIconUpdates() {
    return showIconUpdates;
  }


  /**
   * A method using Reflection to set the setShowIconUpdates attribute of the
   * helper to the same value as it has in this object.
   *
   *@param boolean flag to set the G2BeanIconRenderer for this object to reflect
   *changes in the G2 icon of the wrapped item
   */
  private void setIconComponentShowIconUpdates(boolean status) {
    callIconComponentMethod("setShowIconUpdates",
			    new java.lang.Class[] {Boolean.TYPE},
			    new java.lang.Object[] {new Boolean(status)});
  }


  /**
   * A methid using Reflection to set the setScaleImageToFit attribute of the
   * helper to the same value as it has in this object.
   *
   *@param boolean flag to set the setScaleImageToFit for this object to scale
   * the bean image to the size of the bean
   */
   private void setIconComponentScaleImageToFit(boolean status) {
    callIconComponentMethod("setScaleImageToFit",
			    new java.lang.Class[] {Boolean.TYPE},
			    new java.lang.Object[] {new Boolean(status)});
  }



   /**
   * Return the Image that is used to represent this bean.
   * each of the classes has an overide for this method
   */
  protected Image readIconImage() {
    return null;
  }


  /**
   * Method override of the setSize method,
   *
   * If the G2 item that this bean represents has been fetched, then
   * set size also change the size of the icon
   *
   * @param d  - the Dimension describing the new size for the icon
   */
  @Override
  public void setSize( Dimension d)
  {
      if (item != null && iconComponent != null)
      {
	//setScaleImageToFit(isScaleImageToFit());
	iconComponent.setSize(d);
       }
       super.setSize(d);
  }




  /**
   * series of methods which via reflection, pass attribute values down from
   * G2ItemWraopper to the vm.
   */
  private void setupIconComponent() {
    callIconComponentMethod("setItem",
			    new java.lang.Class[] {Item.class},
			    new java.lang.Object[] {item});
  }


  private static boolean iconRendererClassDoesNotExist;
  /**
   *This method determines if Telewindows2 is available since the iconComponent
   * is only available with Telewindows2
   */
  private java.lang.Object callIconComponentMethod(String methodName,
						   java.lang.Class[] argClasses,
						   java.lang.Object[] args) {

    if (iconComponent == null && !noLoadableIconComponent) {
      try {
 	if (!iconRendererClassDoesNotExist) {
	  if (iconComponentClass == null)
	    iconComponentClass = java.lang.Class.forName(iconComponentClassName);
	}
      }
      catch (ClassNotFoundException E) {
	Trace.exception(E);
	iconRendererClassDoesNotExist = true;
      }
      if (iconComponentClass != null) {
	 try {

	   java.lang.reflect.Constructor cons =
	     iconComponentClass.getConstructor(new Class[] {Component.class});
	   // create the class
	   iconComponent = (Component)cons.newInstance(new java.lang.Object[] {this});
	   //add(iconComponent);
	   //iconComponent.setSize(this.getSize());
	 }
	 catch (Exception E) {
	   Trace.exception(E);
	   throw new RuntimeException(E.toString() +
				      " thrown while constructing G2BeanIconRender");

	 }
      }
    }
    if (iconComponent != null)
      return callMethod(iconComponentClass,
			iconComponent,
			methodName,
			argClasses,
			args);
    else {
      noLoadableIconComponent = true;
      return null;
    }
  }


  /**
   * Check if its is OK to call into G2. G2 must be RUNNING for
   * G2_ItemWrappers to communicate with G2.
   */
  protected boolean okToCallG2() throws G2AccessException{
    if (item == null){
    	return true;
    }
     Symbol currentG2State = null;
     if (context == null)
       context = ((ImplAccess)item).getContext (); // For calls thru wrapG2Item
     currentG2State = context.getG2State();
    if (!currentG2State.equals(G2Gateway.RUNNING_)) {
      String str = "Warning: Can not call G2 as G2 is currently " + currentG2State;
      throw new G2AccessException(str);
      //try { Thread.sleep(2000); } catch (Exception e) {}
      //return false;
    }
    return true;
  }


  /**
   * Set the status of UI information message displaying.
   * Some UI builders can hide Exceptions. If set
   * information and exception messages will be shown via a popup dialog.
   */
  public void setEnableUIForMessages(boolean state) {
    showUIForInformationMessage = state;
  }

  /**
   * Get the status of UI information messagee displaying.
   * Some UI builders can hide Exceptions. If set
   * information and exception messages will be shown via a popup dialog.
   */
  public boolean getEnableUIForMessages() {
    return showUIForInformationMessage;
  }

   /**
   * Inform the user via some UI dialog of some message.
   */
  protected void forcedInformUser(String message) {
    synchronized (G2_ItemWrapper.class) {
		if (informUserThread == null) {
			informUserThread = new InformThread();
			informUserThread.start();
		}
		informUserThread.newMessage(message);
	}
  }

  /**
   * Inform the user via some UI dialog of some message
   * But only if showUIForInformationMessage is true.
   */
  protected void informUser(String message) {
    if (!showUIForInformationMessage){
    	return;
    }
    forcedInformUser(message);
  }

  private static InformThread informUserThread;

  class InformThread extends Thread {
    Vector messages = new Vector();
    public void newMessage(String message) {
      messages.addElement(message);
      synchronized (messages) {
	messages.notifyAll();
      }
    }

    @Override
    public void run() {
      for (;;) {
	if (messages.isEmpty()) {
	  synchronized (messages) {
	    try { 
	    	messages.wait(); 
	    } catch (Exception e) { 
	    	Trace.exception(e); 
	    }
	  }
	}
	if (!messages.isEmpty()) {
	  String message = (String)messages.elementAt(0);
	  messages.removeElementAt(0);
	  MessageDialog md = new MessageDialog (null, "G2 Bean Message",
                true, message, null);

       	  md.setVisible (true);
	}
      }
    }
  }



  /**
   * Inform the user via some UI dialog of some an exception that has been raised.
   */
  protected void informUser(String duringStr, Throwable e) {
    StringWriter sw = new StringWriter();
    PrintWriter pw = new PrintWriter(sw);
    e.printStackTrace(pw);
    if (duringStr != null)
      informUser(duringStr + "\n " + sw.toString());
    else
      informUser(sw.toString());
  }

  String displayInfo = new String("Not yet fetched");


 /**
  *@undocumented
  */
  private boolean _wrapUpNewItem (Item theitem) throws G2AccessException {
    if (theitem == null) {
      _changeItemFetched(false);
      return false;
    }

    if (_isAcceptableItem(theitem)) {
      item = theitem;
      setupIconComponent();
      displayInfo = "fetched " + theitem;
      item.addItemListener (this);
      _changeItemFetched(true);
      fireItemReceived (theitem);
      repaint();
      return true;

    } else {
      _changeItemFetched(false);
      // the incomming class is not within the hierarcy of the wrapper
      throw new G2AccessException("The referenced G2 Item was not of the correct Class for this G2 Bean");
    }

  }


  /**
   *@undocumented
   */
  private void _changeItemFetched(boolean newValue) {
    if (newValue == false) {
      try {
	fireItemRemoved();
      } catch (Exception e) {
	Trace.exception(e);
	informUser("", e);
      }
      item = null;
      noIcon = true;
      repaint();
    }
    boolean old_itemFetched = itemFetched;
    itemFetched = newValue;
    firePropertyChange ("G2ItemFetched",
			new Boolean(old_itemFetched),
			new Boolean(newValue));
  }


  /**
   * Get the context for the connection. Use TwAccess if available.
   */
  private Item _getWrappedItem()
    throws ConnectionTimedOutException,
      G2AccessInitiationException,
      G2AccessException
  {

    // Remove any existing wrapped item
    if (item != null)
      _changeItemFetched(false);

    context = null;
     info = parseURL ();
    Class twClass = null;

    // We may not have Telewindows 2 classes...if we have then we can show
    // icons and other sexy things !
    try {
      twClass = Class.forName("com.gensym.ntw.TwGateway");
    }
    catch (ClassNotFoundException E) {Trace.exception(E); }

    //context = (G2Access)TwGateway.openConnection(info.host, info.port);
    //((TwAccess)context).loginSession();

    if (twClass != null) {  // they have bought sequoia (ye ha)

      Class twInfoClass = null;
      try {
	twInfoClass = Class.forName("com.gensym.ntw.TwConnectionInfo");
      }
      catch (ClassNotFoundException E) {
	Trace.exception(E);
	throw new RuntimeException(E.toString() +
                "Could not find com.gensym.ntw.TwConnectionInfo");
      }

      // We want a sharable ConnectionInfo
      java.lang.Object twInfoObj = null;
      try {

 	java.lang.reflect.Constructor cons =
 	  twInfoClass.getConstructor(new Class[] {String.class, String.class,
                                     String.class,
	                             Boolean.TYPE, Boolean.TYPE} );
 	// create the class
	twInfoObj =
            cons.newInstance(new java.lang.Object[] {   null,
                                                        info.host,
                                                        info.port,
                                                        new Boolean(false),  // Dont force
                                                        new Boolean(true)}); // Sharable


      }
      catch (Exception E) {
	Trace.exception(E);
	throw new RuntimeException(E.toString() +
				   " thrown while constructing TwConnectionInfo");
      }

      context = (G2Access)callMethod(twClass,
				     null,
				     "openConnection",
				     new java.lang.Class[] {twInfoClass},
				     new java.lang.Object[] {twInfoObj});

      Boolean loggedIn = (Boolean)callMethod(twClass,
				    context,
				    "isLoggedIn",
				    new java.lang.Class[] {},
				    new java.lang.Object[] {});

      if (!loggedIn.booleanValue())
	callMethod(twClass,
		   context,
		   "loginSession",
		   new java.lang.Class[] {},
		   new java.lang.Object[] {});

    }

    // No Sequoia available, use G2Gateway
    if (context == null)
      context = G2Gateway.getOrMakeConnection (info.host, info.port);

    if (context != null)
      item = context.getUniqueNamedItem (ITEM_, info.name);


    // So the connection has got the current state;
    context.getG2State();

    return item;
  }

 /**
  *This method uses Reflection to inoke specific methods.
  */
  private java.lang.Object callMethod(java.lang.Class targetClass,
			    java.lang.Object target,
			    String methodName,
			    java.lang.Class[] paramtypes,
			    java.lang.Object[] params) {
    java.lang.Object result = null;

    try {
 	java.lang.reflect.Method method =
 	  targetClass.getMethod(methodName, paramtypes );
 	// call the method
	result = method.invoke(target, params );

      }
      catch (NoSuchMethodException E) {
	Trace.exception(E);
	String errstr = "..Can't find " +
		     (target == null ? targetClass.toString() : target.toString()) +
	             "." + methodName;
        informUser(errstr, E);
	throw new RuntimeException(E.toString() + errstr);
      }
      catch (InvocationTargetException E) {
	  Trace.exception(E);
	  StringWriter sw = new StringWriter();
	  PrintWriter pw = new PrintWriter(sw);
	  E.getTargetException().printStackTrace(pw);
	  informUser("While Connecting...", E.getTargetException());
	  throw new RuntimeException(sw.toString());
      }
      catch (IllegalAccessException E) {
	Trace.exception(E);
	informUser("While Connecting...", E);
	throw new RuntimeException(E.toString() +
				    " ..during " +
		      (target == null ? targetClass.toString() : target.toString()) +
				    "." + methodName);
      }

      return result;
  }



  /** This method checks that the Class of the inbound item is within the
   *  hierarchy of the item-wrapper
   * @returns true if the incomming item may be stored within this wrapper.
   * else false.
   */
   private boolean _isAcceptableItem(Item inboundItem ){
     Class intendedClass = getIntendedClass();

     //System.out.println("Checking inbound item now"+ inboundItem.toString()+ "\n  ");
     //System.out.println("Checking static item  "+ intendedClass.toString()+"\n");

     // Checking Strings here, due the BeanBox using multiple Class Loaders

        if( intendedClass.getName().equals(inboundItem.getClass().getName())) {
	  //System.out.println("        Class ok\n");
	  return true;
        } else {
	  //System.out.println("        Class BAD\n");
	  return false;
        }
   }

  /**
   *This method returns thet class that this wrapper may contain.
   *@return the indended class
   */
  protected Class getIntendedClass() {
    return ItemImpl.class;
  }

  // g2://bombay:1111/TANK-1
  // Need to incorporate three teir url here
  private ItemInfo parseURL () {
    String host = null;
    String port = null;
    int urlStartIndex = sourceURL.indexOf ("//");
    //System.out.println ("URLSTart = " + urlStartIndex);
    int locnEndIndex = sourceURL.indexOf ('/', urlStartIndex + 2);
    //System.out.println ("URLEnd = " + locnEndIndex);
    if (locnEndIndex == urlStartIndex + 2) {
      host = "localhost";
      port = "1111";
    } else {
      String locn = sourceURL.substring (urlStartIndex + 2, locnEndIndex);
      //System.out.println ("Location = " + locn);
      int colonIndex = sourceURL.indexOf (':', urlStartIndex);
      //System.out.println ("ColonIndex = " + colonIndex);
      if (colonIndex < 0 || colonIndex > locnEndIndex) {
	host = locn;
	port = "1111";
      } else {
	host = sourceURL.substring (urlStartIndex + 2, colonIndex);
	port = sourceURL.substring (colonIndex + 1, locnEndIndex);
      }
    }
    String name = sourceURL.substring (locnEndIndex + 1);
    //System.out.println ("Name = " + name);
    return new ItemInfo (host, port, Symbol.intern (name.toUpperCase ()));
  }


  /**
   * @undocumented
   */
  protected String getPrettyClassName () {
    return "Item";
  }


  /**
   * This method returns a preferred size for the item
   * @return a Dimension representing the preferred size
   */
  @Override
  public Dimension getPreferredSize () {
    return new Dimension (50, 50);
  }



 /**
  *This method paints the visual representaion of the bean.
  *
  *@param g the graphic on which to paint
  *
  */
  @Override
  public void paint (Graphics g) {

    if (item != null && iconComponent != null && useG2Icon) {
      iconComponent.paint(g);
    } else {
      if( info == null)
         paintStaticImage (g);
     else
       paintIcon(g);
    }
  }



  /**
   * This method displays a graphical representation of this bean
   *
   *@param g - the graphics to paint this image on
   */
  private void paintIcon (Graphics g) {
    Dimension size = this.getSize ();
    Image iconImage = readIconImage();
    if (iconImage != null )
    {
        int iconWidth = iconImage.getWidth(null);
        int iconHeight = iconImage.getHeight(null);
        if (this.isScaleImageToFit())
        {
                g.drawImage(iconImage.getScaledInstance(
							size.width,
							size.height,
							Image.SCALE_SMOOTH),
			    0,0,
			    null);
        }
	else
        {

                g.setColor (this.getBackground());
                g.fillRect (0, 0, size.width, size.height);

                g.drawImage(iconImage,
			size.width/2 - iconWidth/2,
			size.height /2 - iconHeight/2,
			null);
	  }

	paintItemName(g);

    }

  }


  /**
   * This method displays the name of the G2 item this bean represents
   * if the name is not available, then it displays the class name.
   *
   *@param g - the graphics to paint this image on
   */
   private void paintItemName (Graphics g) {

    String txt;

    if(item != null){
        txt = info.name.toString();
    }
    else {
        txt = getPrettyClassName ();
    }

    FontMetrics fm = g.getFontMetrics ();

//    int height = fm.getHeight ();
    int width = fm.stringWidth (txt);

    g.setColor (this.getForeground());

    Dimension size = getSize ();

    g.drawString (txt, size.width/2 - width/2, size.height - 2);

  }





  /**
   * This method creates a basic display for an item prior to connecting to G2
   * @param g - the graphics to paint this image on
   */
   private void paintStaticImage (Graphics g) {
    String displayString = getPrettyClassName ();
    Dimension size = getSize ();
    FontMetrics fm = g.getFontMetrics ();
    int width = fm.stringWidth (displayString);
    int height = fm.getHeight ();

    if(!scaleImageToFit){
        g.setColor (this.getBackground());

        g.fillRect (0, 0, size.width, size.height);
    }

    g.setColor (this.getForeground());

    Image iconImage = readIconImage();
    if (iconImage != null) {
      int iconWidth = iconImage.getWidth(this);
      int iconHeight = iconImage.getHeight(this);
      int iconYPos =size.height/3;
      g.drawImage(iconImage, size.width/2 - iconWidth/2, iconYPos, this);

    }

     paintItemName(g);
  }




  // Listener Methods
  /**
   * This method is from the itemListener interface.
   *@param An ItemEvent detailing the modification
   */
  @Override
  public void receivedInitialValues (ItemEvent e) {}

  /**
   * This method is from the itemListener interface. It will be called
   * when the wrapped item is modified. Mormally the method will
   * signal a G2 attribute change, and will therefore fire a Property change
   * event.
   *@param e An ItemEvent detailing the modification
   */
  @Override
  public void itemModified (ItemEvent e) {
    //System.out.println ("Item Modified: " + e);
    Sequence dentn = (Sequence) e.getDenotation ();
    java.lang.Object newValue = e.getNewValue ();
    if (dentn.size () != 1)
      return;
    Structure dentn1 = (Structure) dentn.elementAt (0);
    Symbol attrName = (Symbol) dentn1.getAttributeValue (NAME_, null);
    if (attrName == null)
      return;
    String javaPropertyName =
      G2ClassTranslator.slotNameFromG2Slot (attrName.getPrintValue ());
    //System.out.println ("Firing property change: " + javaPropertyName + "  " +
    //		null + " -> " + newValue);
    firePropertyChange (javaPropertyName, null, newValue);

    Structure structure = new Structure ();
     structure.setAttributeValue(attrName, newValue);
    ObjectUpdateEvent evt;
    evt = new ObjectUpdateEvent(this,structure );
		fireObjectUpdated(evt);
  }

  /**
   * This method is called from the itemListener interface. It will be called
   * when the wrapped item is deleted. This bean will remove all
   * references to the deleted G2 Item.
   *@param e An ItemEvent detailing the deletion
   */
  @Override
  public void itemDeleted (ItemEvent e) {
    itemFetched = false;
    firePropertyChange("G2ItemFetched", null , new Boolean(false));
    item = null;
    noIcon = true;
    repaint();
  }



  /**
   * This method will add a PropertyChangeListener to the PropertyChangeListener
   * list.
   * The PropertyChangeListener will be notifed when an Attribute Changes in
   * the wrapped G2 item.
   *@param pl The PropertyChangeListener to add to the PropertyChangeListener list
   */
  @Override
  public void addPropertyChangeListener (PropertyChangeListener pl) {
    if (changeSupport == null)
      changeSupport = new PropertyChangeSupport (this);
    changeSupport.addPropertyChangeListener (pl);
  }


  /**
   * This method removes a PropertyChangeListener from the
   * PropertyChangeListener List.
   *@param pl The PropertyChangeListener to remove from the
   * PropertyChangeListener list
   */
  @Override
  public void removePropertyChangeListener (PropertyChangeListener pl) {
    if (changeSupport == null)
      return;
    changeSupport.removePropertyChangeListener (pl);
  }

 /**
  *This method fires a property change event to all of the object registered
  * to the property change event of this item.
  *
  *@param propertyName a string representing the property that has changed.
  *@param oldValue the old value of the changed property.
  *@param newValue the new value of the changed property.
  */
  @Override
  protected void firePropertyChange(String propertyName,
                                    java.lang.Object oldValue,
                                    java.lang.Object newValue) {
    if (changeSupport == null)
      return;
    changeSupport.firePropertyChange(propertyName, oldValue, newValue);
  }

  /**
   * This method implements the objectChange from the ObjectChangeListener Interface.
   * Object Attribute Changes are passed back to the Wrapped Item.
   * @param e An ObjectChange Event detailing the ObjectChange
   */
  @Override
  public void objectChanged(ObjectChangeEvent e) {
    if (item == null)
      throw new IllegalStateException ("No item set in proxy");
    String attrName =  e.getAttributeName();
    //System.out.println("recv object changed event in IP attr="+attrName+
    //	       " and value "+e.getChangedObject());
    if (attrName != null) {
      Symbol nameSymbol = Symbol.intern(attrName.toUpperCase());
      try {
	item.setPropertyValue (nameSymbol,e.getChangedObject());
      } catch (G2AccessException gae) {
	Trace.exception (gae);
      }
    }
  }



  /**
   * Remove a ObjectUpdateListener from the ObjectUpdateListener List.
   *@param pl The ObjectUpdateListener to remove from the ObjectUpdateListener list
   */
  public synchronized void removeObjectUpdateListener(ObjectUpdateListener l) {
    if (objectUpdateListeners == null)
	objectUpdateListeners = new Vector();

    objectUpdateListeners.removeElement(l);
    //System.out.println("in removeObjectUpdateListener");
  }


  /**
   * This method will add a ObjectUpdateListener to the ObjectUpdateListener list.
   * The ObjectUpdateListener will be notifed when an Attribute Changes in the wrapped
   * G2 item.
   *@param l The ObjectUpdateListener to add to the ObjectUpdateListener list
   */
  public synchronized void addObjectUpdateListener(ObjectUpdateListener l) {
    if (objectUpdateListeners == null)
      objectUpdateListeners = new Vector();

    objectUpdateListeners.addElement(l);
    //System.out.println("in addObjectUpdateListener - adding "+ l.toString());
  }


 /**
  *
  *This method fires an ObjectUpdateEvent to all of the object registered
  * to the ObjectUpdateEvent=  of this item.
  *@param e An ObjectChange Event detailing the ObjectChange
  */
  private void fireObjectUpdated(ObjectUpdateEvent e) {

    //System.out.println("in fireObjectUpdated objectUpdateListeners = "+objectUpdateListeners.toString());
    java.util.Vector targets;
    synchronized (this) {
      if (objectUpdateListeners == null) {
	// System.out.println("in fireObjectUpdated - objectUpdateListeners are null");
	return;
      }
      targets = (java.util.Vector) objectUpdateListeners.clone();
    }

    //System.out.println("in fireObjectUpdated - cloned vector " + targets.size());
    for (int i = 0; i < targets.size(); i++) {
      ObjectUpdateListener target = (ObjectUpdateListener)targets.elementAt(i);
      target.objectUpdated(e);
    }

  }


  private void readObject(ObjectInputStream stream) throws IOException {
   try {
     stream.defaultReadObject();
     setIconComponentShowIconUpdates(showIconUpdates);
  } catch (Exception e) { throw new IOException(e.toString()); }
     oldURL = "";
  }


  /**
   *@undocumented
   */
  class ItemInfo {

    String host;
    String port;
    Symbol name;

    ItemInfo (String host, String port, Symbol name) {
      this.host = host;
      this.port = port;
      this.name = name;
    }
  }

}





