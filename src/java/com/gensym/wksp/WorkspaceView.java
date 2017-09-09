
package com.gensym.wksp;

import java.awt.datatransfer.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.ntw.util.*;
import com.gensym.ntw.util.SelectionListener;
import com.gensym.ntw.util.SelectionEvent;
import com.gensym.ntw.*;
import com.gensym.irm.*;
import com.gensym.draw.*;
import com.gensym.dlg.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ItemDeletedException;
import com.gensym.jgi.G2Gateway;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import com.gensym.classes.Item;
import com.gensym.classes.G2JavaBean;
import com.gensym.classes.NameBox;
import com.gensym.classes.TableItem;
import com.gensym.classes.Connection;
import com.gensym.classes.Entity;
import com.gensym.classes.TextBox;
import com.gensym.classes.Table;
import com.gensym.classes.FreeformTable;
import com.gensym.classes.Meter;
import com.gensym.classes.Dial;
import com.gensym.classes.CheckBox;
import com.gensym.classes.RadioButton;
import com.gensym.classes.ActionButton;
import com.gensym.classes.Slider;
import com.gensym.classes.TypeInBox;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.ClassDefinition;
import com.gensym.classes.ImageDefinition;
import com.gensym.classes.G2Definition;
import com.gensym.classes.G2ForeignObject;
import com.gensym.controls.ItemRetriever;
import com.gensym.controls.ItemRetrievalEvent;
import com.gensym.controls.ItemRetrievalListener;
import com.gensym.dlg.WarningDialog;    
import com.gensym.ui.palette.*;
import com.gensym.ntw.util.G2Palette;
import com.gensym.ui.*;
import com.gensym.util.symbol.WorkspaceShowingSymbols;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.shell.util.WorkspaceDocument;

/**
 *  A WorkspaceView is an interactive, visual "representation" of a <code>KbWorkspace</code>.
 * A <code>WorkspaceListener</code> may listen to a <code>KbWorkspace</code> for changes
 * to the data stored in the <code>KbWorkspace</code>, including changes to sub-elements.
 * A typical view will provide an API for updating its representation of changes in the
 * <code>KbWorkspace</code>.  This may be accomplished by making the view itself a
 * <code>WorkspaceListener</code>, or through the use of a <code>WorkspaceAdapter</code>. <p>
 *     The view delegates low level event handling to an <code>EventHandler</code>.  The default
 * <code>EventHandler</code> will interpret G2 configurations using the current user mode for
 * this <code>UiClientSession</code>. Modifications to item configurations after this view is shown
 * will not take effect, unless the user mode is changed.  Showing a new view of this
 * view's workspace will use all relevant item configurations that are present at that
 * time.  The use of G2 configurations can be turned on and off through
 * <code>setUseG2Configurations</code>
 *     In addition, this view provides an API for getting and setting the current set
 * of selected <code>WorkspaceElement</code>s.  Users may add themselves as
 * <code>SelectionListener</code>s to recieve notifications when this view's selection has changed.  
 */

public class WorkspaceView extends PersistentCanvas implements
ItemView, SystemAttributeSymbols,
  com.gensym.util.ItemListener,
  WorkspaceRepresentationTypes, ClipboardOwner,
  PaletteListener, PaletteDropTarget,
  java.util.Observer, ItemRetrievalListener,
  WorkspaceShowingSymbols{
  //public static Component currentTransferItem = null;
  private int unitIncrement = 10;
  private int blockIncrement = 40;
  static final long serialVersionUID = -2782971940860755601L;
  static final boolean updateWorkspaceDebug = false;
  static boolean traceOn = false;
  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.wksp", WorkspaceView.class);
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.wksp.TraceMessages");
  private static Resource i18n=Resource.getBundle("com.gensym.wksp.WorkspaceMessages");
  private transient Color foregroundColor = Color.black;
  private transient Hashtable subblocks;
  private transient Vector heavyWeightList;
  private transient int prevHorizViewMin, prevVertViewMin;
  private transient KbWorkspace workspace;
  private transient WorkspaceViewAdapter workspaceViewAdapter;
  private static final Symbol ADMINISTRATOR_ = Symbol.intern ("ADMINISTRATOR");
  private static final Symbol FOREGROUND_ = Symbol.intern ("FOREGROUND");
  private static final Symbol BACKGROUND_ = Symbol.intern ("BACKGROUND");
  private static final Symbol DEFAULT_REPRESENTATION_ = Symbol.intern ("DEFAULT-REPRESENTATION");
  private static Symbol NAME_ = Symbol.intern ("NAME");
  private static final Symbol COLOR_PATTERN_CHANGES_ = Symbol.intern ("COLOR-PATTERN-CHANGES");
  private transient boolean receivingEvents = false;
  //private ItemRetriever itemRetriever;
  private static boolean secretUseG2ConfigurationsDefault = true;
  private boolean useG2Configurations = secretUseG2ConfigurationsDefault;
  private transient WorkspaceSelection currentSelection;
  private transient Vector selnListeners = new Vector ();  
  private boolean displaySelectionFrames = true;
  private Vector pendingItemsForSelection, pendingItemsCutStatus;

  /**
   * Constants
   */
  private static final boolean debugCmds = false;
  private static final Symbol IMAGE_NAME_ = Symbol.intern ("IMAGE-NAME");
  private static final Symbol IMAGE_DEFINITION_ = Symbol.intern ("IMAGE-DEFINITION");
  private static Symbol[] neededAttributes =
  {BACKGROUND_COLOR_, FOREGROUND_COLOR_, BACKGROUND_IMAGES_, ITEM_CONFIGURATION_};
  private static final Symbol X_ = Symbol.intern ("X"),
    Y_ = Symbol.intern ("Y"), 
    POINT_ = Symbol.intern ("POINT");

  private Vector backgroundImages, imageLocations, imageDefinitions;
  private ImageListener imageListener = new ImageListener ();
  
  static final int FATAL = 0;
  static final int ANOMALY = 1;
  private boolean hitFatalError = false;
  private boolean wkspDeleted = false;
  private static boolean[] currentAnnotationStates = new boolean[]{false};
  static boolean annotationsVisible;
  private static final String MANUALLY_DISABLED="manuallyDisabled";    

  /**
   * @undocumented
   */
  public boolean getHitFatalError()
  {
    return hitFatalError;
  }

    void handleG2AccessException(G2AccessException g2ae,
				 int severity)
       throws FatalWorkspaceException
  {
    handleG2AccessException(g2ae, severity, null);
  }

  private void clearView()
  {
    try {
      clearBackgroundImages ();
      setBackgroundColor (getOutOfBoundsColor ()); // So no edges are visible
      disposeChildren();
    } catch (FatalWorkspaceException fwe) {
      removeAll();//at least remove them from the container
    } finally {
      repaintCanvas();
    }
  }

  private void clearBackgroundImages () {
    backgroundImages = null;
    int index = 0;
    if (imageDefinitions != null) {
      for (index = 0; index < imageDefinitions.size(); index++)
	try {
	  ((ImageDefinition)(imageDefinitions.get(index))).removeItemListener(imageListener);
	} catch (Exception e) {Trace.exception (e);}
      imageDefinitions = null; 
    }
  }

    void handleG2AccessException(G2AccessException g2ae,
				 int severity,
				 String message)
       throws FatalWorkspaceException
  {
    if (workspace!=null&&!workspace.isValid()) {
      severity = FATAL;
      wkspDeleted = true;
    }
    switch (severity) {
    case FATAL:
      hitFatalError = true;
      //System.out.println("HIT FATAL ERROR" + g2ae);
      //g2ae.printStackTrace();
      clearView();
      Trace.exception(g2ae);
      if (message != null)
	throw new FatalWorkspaceException(g2ae, message);
      else
	throw new FatalWorkspaceException(g2ae);
     case ANOMALY:
       Trace.exception(g2ae);
       break;
     }
   }

   /**
    * Initializes the selection, scroll states, color table
    * and event handler. Enables double-buffering by default.
    */
   public WorkspaceView ()
   {
     initialize();
     setDoubleBuffered(!isScalingAvailable()); // default
   }

   /**
    * Initializes the selection, scroll states, color table and 
    * event handler, adds a <code>WorkspaceViewAdapter</code> as a
    * <code>WorkspaceListener</code> to the <code>KbWorkspace wksp</code>,
    * and renders the view.
    * @param <code>wksp</code> the workspace for which to create a view.
    */
   public WorkspaceView(KbWorkspace wksp) {
     this();
     try {
       setWorkspace(wksp);
       Rectangle bounds = new Rectangle(0,0,50,50);
       try {
	 bounds = ((ImplAccess)wksp).getBounds();
	 bounds.y = -bounds.y;
       } catch (G2AccessException g2ae) {
	 handleG2AccessException(g2ae, FATAL);//no wksp bounds
       }
       setBounds(bounds);
     } catch (FatalWorkspaceException fwe) {
       return;
     }
   }

   private static final Class thisClass = com.gensym.wksp.WorkspaceView.class;

    /**
     * Creates a WorkspaceView.  If scaling is available, a ScalableWorkspaceView is
     * returned; otherwise a WorkspaceView is returned.
     * @see com.gensym.wksp.ScalableWorkspaceView
     */
    public static WorkspaceView createWorkspaceView(Object requestor, KbWorkspace wksp){
     if (isScalingAvailable())
       return VersionHelper.createScalableWorkspaceView(requestor, wksp);
     else
       return new WorkspaceView(wksp);
    }

  static WorkspaceAnnotationDrawer annotationDrawer = new WorkspaceAnnotationDrawer();

    /**
     * @undocumented
     */
  public static WorkspaceAnnotationDrawer getAnnotationDrawer(){
      return annotationDrawer;
  }

   /**
    * @undocumented
    */
  public static void setAnnotationDrawer(WorkspaceAnnotationDrawer drawer){
    annotationDrawer = drawer;
  }

   /**
    * @undocumented
    */
   public static final String[] getAvailableAnnotations() {
     return annotationDrawer.getAvailableAnnotations();
   }
    
   /**
    * @undocumented
    */    
   public static boolean[] getCurrentAnnotationStates() {
     return annotationDrawer.getCurrentAnnotationStates();
   }

   /**
    * @undocumented
    */    
   public static void setCurrentAnnotationStates(boolean[] newStates) {
     annotationDrawer.setCurrentAnnotationStates(newStates);
   }        

   /**
    * @undocumented
    */        
   public static boolean getAnnotationsVisible(){
     return annotationsVisible;
   }

   /**
    * @undocumented
    */        
   public static void setAnnotationsVisible(boolean annotationsVisible){
     WorkspaceView.annotationsVisible = annotationsVisible;
   }
 
    
   /**
    * Returns true if scaling is available
    */
   public static boolean isScalingAvailable(){
     return VersionHelper.isUsingJava2D(thisClass);
   }

   /**
    * @undocumented
    * Show the KbWorkspace of this view according to the specification in the showingParticulars.
    * This method is typically called from a WorkspaceShowingListener
    */
   public void showWorkspace(Structure showingParticulars){
     if (showingParticulars == null)
       return;

     int wkspX = -1234567890, wkspY = -1234567890;

     Item itm  = (Item) showingParticulars.getAttributeValue (ITEM_, null);
     if (!(itm.equals (workspace))) {
       try {
	 wkspX = itm.getItemXPosition ();
	 wkspY = itm.getItemYPosition ();
       } catch (G2AccessException gae) {
	 Trace.exception(gae);
       }
     }

     Integer someInt;
     someInt = (Integer) showingParticulars.getAttributeValue (X_IN_WORKSPACE_, null);
     if (someInt != null)
       wkspX = someInt.intValue ();
     someInt = (Integer) showingParticulars.getAttributeValue (Y_IN_WORKSPACE_, null);
     if (someInt != null)
       wkspY = someInt.intValue ();
     if (wkspX == -1234567890)
       return;
     scrollToLocation(wkspX, -wkspY, true);
   }

    /**
     * Scrolls the workspace view to the given location.
     * @param x The x position in workspace coordinates
     * @param y The y position in workspace coordinates
     * @since Telewindows2 Toolkit 1.1 rev. 0
     */
    public void scrollToLocation(int x, int y)
    {
      scrollToLocation(x, y, false);
    }

    public void scrollToLocation(int x, int y, boolean center) {
      Component parent = getParent();
      if (parent instanceof javax.swing.JViewport){ 
	javax.swing.JViewport viewport = (javax.swing.JViewport)parent;
	Rectangle lbnds = getLogicalBounds();
	int hlmin = horizontal_state.getLogicalMin();
	int vlmin = vertical_state.getLogicalMin();
	Point p = new Point(x - hlmin, y - vlmin);
	
        Rectangle bnds = ((javax.swing.JViewport)parent).getViewRect();
	int width = bnds.width;
	int height = bnds.height;
	p.x= Math.max(0, p.x-width/2);
	p.y= Math.max(0, p.y-height/2);      
	viewport.setViewPosition(p);
      } else {
	scrollViewAbsolute (x, true);
	scrollViewAbsolute (y, false);
      }
    }


    /**
     * Gives the bounds of the workspace as visible to the user,
     * according to the scrolling state of the WorkspaceView.
     * Values are in workspace co-ordinates.
     */
    @Override
    public Rectangle getViewBounds() {
      return super.getViewBounds();
    }

    /**
     * This is called from both the constructor and the readObject method.
     */
   private void initialize()
   {
     currentSelection = new WorkspaceSelection (this);
     this.selnListeners = new Vector ();  
     if (this.subblocks != null) {
       this.subblocks.clear();
     }
     this.subblocks = new Hashtable();
     addScrollObserver (this, true);//for bean scrolling
     addScrollObserver (this, false);//for bean scrolling
     ColorTable table = WorkspaceColorTable.createDefaultColorTable();
     setColorTable(table);
     //     initializeEventHandler();
     menuGenerator = makeSelectionCommandGenerator ();
   }

  @Override
  public void setEventHandler(EventHandler eh)
  {
    WorkspaceViewEventHandler oldeh = (WorkspaceViewEventHandler)getEventHandler();
    super.setEventHandler(eh);
    if (eh == null && oldeh != null) {
      oldeh.clearDispatch();
    }
  }
    


   private void initializeEventHandler()
   {
     setEventHandler(new WorkspaceViewEventHandler());
   }

   void configureHandler(Symbol userMode)
	throws FatalWorkspaceException
   {
     if (getEventHandler() instanceof WorkspaceViewEventHandler &&
	 useG2Configurations) {
       WorkspaceViewEventHandler handler
	 = (WorkspaceViewEventHandler)getEventHandler();
       handler.deregisterListeners(this);
       handler.registerListeners(this);
       for (java.util.Enumeration e = getElements ();
	    e.hasMoreElements ();) {
	 WorkspaceElement wElt = (WorkspaceElement) e.nextElement ();
	 try {
	   handler.configureDispatch(wElt.getItem(), userMode);
	 } catch (G2AccessException g2ae) {
	   handleG2AccessException(g2ae, ANOMALY);//bad wksp item
	 }
       }
     }
   }

  /**
   * Returns whether or not this view is using G2 configurations
   * in its event handling.
   * @return true iff this view supports G2 configurations.
   */
   public boolean getUseG2Configurations()
   {
     return useG2Configurations;
   }

   /**
    * Sets whether or not this view should use G2 configurations
    * @param <code>state</code> a <code>boolean</code> representing whether to use
    * G2 configurations in the event handler.
    */
   public void setUseG2Configurations(boolean state)
   {
     if (hitFatalError) return;
     try {
       if (state == useG2Configurations)
	 return;
       useG2Configurations = state;
       initializeEventHandler();
       if (workspace != null && useG2Configurations) {
	 try {
	   TwAccess context
	     = (TwAccess)((ImplAccess)workspace).getContext(); //hack for now
	   Symbol userMode = context.getUserMode();
	   configureHandler(userMode);
	 } catch(G2AccessException g2ae) {
	   handleG2AccessException(g2ae, FATAL);//no user mode
	 }
       }
     } catch (FatalWorkspaceException fwe) {
       return;
     }
   }

   boolean isReceivingEvents() {
     return receivingEvents;
   }

   /**
    * Gets this view's item as a <code>KbWorkspace</code>.
    * @return The <code>KbWorkspace</code> for this view.
    */
   public KbWorkspace getWorkspace() {
     return workspace;
   }

   /**
    * Gets this view's workspace.
    * @return The <code>KbWorkspace</code> for this view.
    */
   @Override
  public Item getItem() {
     return (Item) workspace;
   }

   /**
    * Cleans up all objects listening to the <code>KbWorkspace</code>.
    * Removes the <code>WorkspaceViewAdapter</code> as a workspace listener from
    * the <code>KbWorkspace</code> and removes this view as an item
    * listener from the <code>KbWorkspace</code>.  
    */
   public void dispose() {
     //if (hitFatalError) return;//?????????//pbk review for any exceptions
     clearBackgroundImages ();
     setWorkspace(null);
     clipData = null;
     currentSelection = null;
     selnListeners.removeAllElements();
     if (this.subblocks != null) {
       this.subblocks.clear();
     }
     subblocks = null;
 //     deleteScrollObserver(this, true);
 //     deleteScrollObserver(this, false);
     EventHandler handler = getEventHandler();
     if (handler instanceof WorkspaceViewEventHandler)
       ((WorkspaceViewEventHandler)handler).dispose();
     setEventHandler(null);
     // System.out.println("Disposed of workspacevieweventhandler.");
     setColorTable(null);
     theMenuGenerator = null;
     menuGenerator = null;
     if (workspaceViewAdapter != null)
       workspaceViewAdapter.dispose();
     workspaceViewAdapter = null;
     // The following is to get rid of a leak of the TwGateway
     Palette.removePaletteListener(this);

   }

   private void disposeChildren()
	throws FatalWorkspaceException
   {
     Component[] components = getComponents();
     int length = components.length;
     for (int i = 0; i < length; i++) {
       Component c = components[i];
       if (c instanceof WorkspaceElement) {
	 try {
	   ((WorkspaceElement)c).dispose();
	 } catch (G2AccessException g2ae) {
	   handleG2AccessException(g2ae, ANOMALY);//bad wksp item
	 }
       }
     }
     removeAll();
   }

   /**
    * Disposes of this view once it is no longer referenced.
    * @see #dispose
    */
   @Override
  public void finalize() {
     dispose();
   }

   private void setBackgroundImages(Sequence images)
	throws FatalWorkspaceException
  {
    MediaTracker mt = new MediaTracker(this);
    if (backgroundImages != null)
      clearBackgroundImages ();
    backgroundImages = new Vector();
    imageLocations = new Vector();
    imageDefinitions = new Vector();
    if (images != null) {
      Enumeration e = images.elements();
      int counter = 0;
      while (e.hasMoreElements()) {
	Structure imageStruct = (Structure)e.nextElement();
	Symbol imageName = (Symbol)imageStruct.getAttributeValue(IMAGE_NAME_, null);
	if (imageName != null) {
	  com.gensym.jgi.G2Access context = ((ImplAccess)workspace).getContext();
	  ImageDefinition imageDef = null;
	  try {
	    imageDef =
	      (ImageDefinition)context.getUniqueNamedItem (IMAGE_DEFINITION_, imageName);
	    //currently, we are tracking only the image definitions
	    //which exist.  If we were good, then we would store not
	    //just the image definition, but the name of the image
	    //definition so that when it got filled in properly, we
	    //would be able to update.  However, there's no way to
	    //listen to that.  Workaround: change the background
	    //images slot of the workspace after the image definition
	    //has been fixed, and then this code will get run again.
	    if (imageDef != null) {
	      Structure imagePointStruct =
		(Structure)imageStruct.getAttributeValue(POINT_, null);
	      int imageWidth = 0, imageHeight = 0;
	      Image image = imageDef.getImage();
	      //Note that the image is assumed to be of size 0 if it is invalid.
	      if (image != null) {
		imageWidth = imageDef.getWidthOfImage().intValue();
		imageHeight = imageDef.getHeightOfImage().intValue();
	      }
	      int backgroundImageX =
		((Integer)imagePointStruct.getAttributeValue
		 (X_, new Integer(0))).intValue() - imageWidth/2;
	      int backgroundImageY= 
		(-((Integer)imagePointStruct.getAttributeValue
		   (Y_, new Integer(0))).intValue()) - imageHeight/2;
	      Rectangle imageLocation = new Rectangle(backgroundImageX, backgroundImageY,
						      imageWidth, imageHeight);
	      imageDefinitions.addElement (imageDef);
	      backgroundImages.addElement(image);
	      /*Image scaledImage =
		image.getScaledInstance(width, height, Image.SCALE_FAST);//SMOOTH);*/
	      imageDef.addItemListener (imageListener);
	      imageLocations.addElement(imageLocation);
	      if (image != null) {
		mt.addImage(image, counter);	  
		counter++;
	      }
	    }
	  } catch (G2AccessException g2ae) {
	    handleG2AccessException(g2ae, ANOMALY); //no image definition by that name
	  }
	}
      }
    }
    try {
      mt.waitForAll();
    } catch (InterruptedException ie) {
      Trace.exception(ie);
    }
  }

  void updateIndividualImage (ImageDefinition definition)  throws G2AccessException {
    MediaTracker mt = new MediaTracker(this);
    int index = imageDefinitions.indexOf(definition);
    if (index >= 0) {
      Image image = definition.getImage();
      backgroundImages.set(index, image);
      if (image != null) {
	mt.addImage(image, 0);
	try {
	  mt.waitForID(0);
	} catch (InterruptedException ie) {
	  Trace.exception(ie);
	}
      }
      //figure out what bounds to invalidate, based on the previously
      //cached location of this image.  what we have is coordinates
      //with x,y in the corner, and we need to get the center
      //coordinates, so that we can recompute the corner coordinates
      //of the new image.  then we need to invalidate the maximum of
      //the space covered by those two rectangles.
      Rectangle originalImageLocation = (Rectangle)imageLocations.elementAt(index);
      int centerX = originalImageLocation.x + originalImageLocation.width/2;
      int centerY = originalImageLocation.y + originalImageLocation.height/2;
      int newWidth = 0, newHeight = 0;
      if (image != null) {
	newWidth = definition.getWidthOfImage().intValue();
	newHeight = definition.getHeightOfImage().intValue();
      }
      int newX = centerX - newWidth/2;
      int newY = centerY - newHeight/2;
      Rectangle newImageLocation = new Rectangle (newX, newY, newWidth, newHeight);
      invalidate(new Rectangle[]
	{new Rectangle (Math.min(originalImageLocation.x, newX),
			Math.min(originalImageLocation.y, newY),
			Math.max(originalImageLocation.width, newWidth),
			Math.max(originalImageLocation.height, newHeight))});
      imageLocations.set(index, newImageLocation);
    }
  }

  class ImageListener implements com.gensym.util.ItemListener{
    @Override
    public void receivedInitialValues(com.gensym.util.ItemEvent e){}
    @Override
    public void itemModified (com.gensym.util.ItemEvent e){
      Sequence denotation = e.getDenotation();
      if (AttributeDenotation.isAttributeDenotation(denotation)){
	Symbol attributeName_ = AttributeDenotation.getAttributeName(denotation);
	if (attributeName_.equals(SystemAttributeSymbols.FILE_NAME_OF_IMAGE_)){
	  try{
	    ImageDefinition definition = (ImageDefinition)(e.getItem ());
	    updateIndividualImage(definition);
	  } catch (Exception ex) {Trace.exception (ex);}
	}  
      }
    }
    @Override
    public void itemDeleted(com.gensym.util.ItemEvent e) {}
  }


  /**
   * Cause this view to make this <code>KbWorkspace wksp</code> visible. Clears out
   * all subscriptions on the previous workspace, if any, and removes
   * all current AWT children from this view before rendering
   * the new workspace.  
   * @param <code>wksp</code> the workspace to render.
   */
  public void setWorkspace (KbWorkspace wksp) {
    // System.out.println("WorkspaceView set workspace.  Our workspace = " + workspace);
    try {
      try {
	if (workspace != null) {
	  disposeChildren();
	  clearBackgroundImages ();
	  setBackgroundColor (getOutOfBoundsColor ()); // So no edges are visible
	  workspace.removeItemListener((com.gensym.util.ItemListener)this, neededAttributes);
	  if (workspaceViewAdapter != null) 
	    workspace.removeWorkspaceListener(workspaceViewAdapter);
	  setEventHandler(null);
	}
      } catch (G2AccessException g2ae) {
	handleG2AccessException(g2ae, ANOMALY);//old wksp is bad, go on???
      }
      hitFatalError = false;//this is correct behavior
      wkspDeleted = false;
      this.workspace = wksp;
      //long t0 = System.currentTimeMillis ();
      if (workspace != null) {
	if (!workspace.isValid ()) {
	  hitFatalError = true;
	  wkspDeleted = true;
	  return;
	}
	if (workspaceViewAdapter == null)  
	  workspaceViewAdapter = new WorkspaceViewAdapter(this);      
	try {
	  //System.out.println ("Adding " + this + " as an item listener for " + workspace);
	  workspace.addItemListener((com.gensym.util.ItemListener)this, neededAttributes);
	  //System.out.println ("Adding " + workspaceViewAdapter + " as an workspace listener for " + workspace);
	  // null is asking for the default three attributes that
	  // let to all this junk: connection-style, item-configuration,
	  // and connection-position-sequence
	  workspace.refreshItemDataForWorkspace(null, workspaceViewAdapter); 
	  workspace.addWorkspaceListener (workspaceViewAdapter);
	  initializeEventHandler();
	  //System.out.println ("Finished adding listeners -> will render");
	} catch (G2AccessException g2ae) {
	    handleG2AccessException(g2ae, FATAL);//wksp is bad
	}
	//long t1 = System.currentTimeMillis ();
	if (useG2Configurations) {
	  try {
	    TwAccess context
	      = (TwAccess)((ImplAccess)workspace).getContext(); //hack for now
	    Symbol userMode = context.getUserMode();    
	    configureHandler(userMode);
	  } catch (G2AccessException g2ae) {
	      handleG2AccessException(g2ae, FATAL);//no user mode
	  }
	}
	//long t2 = System.currentTimeMillis ();
	renderWorkspace();
	//long t3 = System.currentTimeMillis ();
	/*System.out.println ("Get Wksp = " + (t1 - t0) +
	  " Configure = " + (t2 - t1) + 
	  " Render = " + (t3 - t2));*/
	receivingEvents = true;
	workspaceViewAdapter.decacheEvents();
      }
    } catch (FatalWorkspaceException fwe) {
      return;
    }
    initializeForPaletteDrop ();
    System.gc();
  }

  /**
   * Converts the workspace's items into <code>WorkspaceElements</code>
   * and adds them to the <code>Container</code>. Also sets the workspace's
   * bounds, foreground color and background color.
   * @see #createElement
   */    
  public void renderWorkspace () {
    if (hitFatalError) return;
    try {
      try {
	setBackgroundImages(workspace.getBackgroundImages());
      } catch (G2AccessException g2ae) {
	handleG2AccessException(g2ae, FATAL);//bad wksp
      }
      removeAll();
      if (this.subblocks != null) {
	// System.out.println("Clearing subblocks in renderWorkspace");
	//But dammit, WHY ARE THERE STILL TEXT BOX IMPLS KICKING AROUND?
	this.subblocks.clear();
      }
      this.subblocks = new Hashtable();
      Symbol foregroundColor = Symbol.intern ("BLACK");
      Symbol backgroundColor = Symbol.intern ("WHITE");
      Rectangle bounds = null;
      try {
	bounds = ((ImplAccess)workspace).getBounds();
	bounds.y = -bounds.y;
	backgroundColor = workspace.getBackgroundColor();
	foregroundColor = workspace.getForegroundColor();
      } catch (G2AccessException g2ae) {
	  handleG2AccessException(g2ae, FATAL);//bad wksp
      }
      setScroll(bounds.x, bounds.y,
		bounds.x + bounds.width,
		bounds.y + bounds.height);
      setBackgroundColor(getColorTable().lookup(backgroundColor));
      setForegroundColor(getColorTable().lookup(foregroundColor));
      setBackgroundColor(getColorTable().lookup(backgroundColor));
      setElements(workspace.getItems());
      validateTree();
    } catch (FatalWorkspaceException fwe) {
      return;
    }
  }

  private void setElements(Item[] items)
       throws FatalWorkspaceException
  {
    //System.out.println("setElements: " + com.gensym.core.DebugUtil.printArray(items));
    //removeAllElements();
    Symbol userMode = ADMINISTRATOR_;
    try {
      TwAccess context
	= (TwAccess)((com.gensym.classes.ImplAccess)workspace).getContext(); //hack for now
      userMode = context.getUserMode();
    } catch (G2AccessException g2ae) {
      handleG2AccessException(g2ae, FATAL);//no user mode
    }
    int count = items.length;
    Item item;
    for (int i = 0; i < count; i++) {
      item = items[i];
      if (item != null) {
	try {
	  WorkspaceElement newElement = createElement(item);
	  addElement(newElement, userMode);
	} catch (G2ItemDeletedException g2ide) {
	  addElement((WorkspaceElement)new DeletedItemElement (item));
	  // Ignore
	} catch (G2AccessException g2ae) {
	  handleG2AccessException(g2ae, ANOMALY);//bad element
	  // System.out.println("SET ELEMENTS COULD NOT CREATE WORKSPACE ELEMENT FOR " + item);
	}
      } else
	Trace.exception(new Exception("RECEIVED NULL ITEM IN WORKSPACE VIEW"));
    }
  }

    
  /**
   * Adds the <code>WorkspaceElement wsElement</code> to this view. 
   */
  public void addElement(WorkspaceElement wsElement)
  {
    if (hitFatalError) return;
    try {
      Item item = wsElement.getItem();
      try {
	TwAccess context
	  = (TwAccess)((ImplAccess)item).getContext(); //hack for now
	Symbol userMode = context.getUserMode();
	addElement(wsElement, userMode);
      } catch (G2AccessException g2ae) {
	handleG2AccessException(g2ae, FATAL);//no user mode
      }
    } catch (FatalWorkspaceException fwe) {
      return;
    }
  }
			  
  private void addElement(WorkspaceElement wsElement,
			  Symbol userMode)
       throws FatalWorkspaceException
  {
    Item item = wsElement.getItem();
    subblocks.put(item, wsElement);
    Trace.send(20, traceKey, i18nTrace, "wvaddElement", wsElement);
    if (getEventHandler() instanceof WorkspaceViewEventHandler &&
	useG2Configurations) {
      WorkspaceViewEventHandler handler
	= (WorkspaceViewEventHandler)getEventHandler();
      try {
	handler.configureDispatch(item, userMode);
      } catch (G2AccessException g2ae) {
	handleG2AccessException(g2ae, ANOMALY);//bad wksp item
      }	
    }
    addElement ((Component) wsElement);
  }

  private void addToHeavyWeightList (Component hElt) {
    if (heavyWeightList == null)
      heavyWeightList = new Vector();
    heavyWeightList.addElement (hElt);
  }

  @Override
  public void addElement(Component component)
  {
    if (hitFatalError) return;
    super.addElement(component);
    if (component instanceof BeanElement)
      addToHeavyWeightList (component);
    else {
      java.awt.peer.ComponentPeer peer = component.getPeer();
      if (peer != null &&
	  !(peer instanceof java.awt.peer.LightweightPeer)) {
	Rectangle vBnds = getViewBounds();
	int deltaX = vBnds.x, deltaY = vBnds.y;
	Point locn = component.getLocation();
	component.setLocation (locn.x - deltaX, locn.y - deltaY);
	addToHeavyWeightList (component);
      }
    }
  }
    
  /**
   * Adds the <code>WorkspaceElement wsElement</code>to this view at the z position 
   * given by <code>position</code>
   * @param <code>position</code> the z position at which to add this element.
   */
  public void addElement(WorkspaceElement wsElement,
			 int position)
  {
    if (hitFatalError) return;
    try {
      Item item = wsElement.getItem();
      try {
	TwAccess context
	  = (TwAccess)((ImplAccess)item).getContext(); //hack for now
	Symbol userMode = context.getUserMode();
	addElement(wsElement, position, userMode);
      } catch (G2AccessException g2ae) {
	handleG2AccessException(g2ae, FATAL); //no user mode
      }
    } catch (FatalWorkspaceException fwe) {
      return;
    }
  }
    
  private void addElement(WorkspaceElement wsElement,
			 int position,
			 Symbol userMode) 
       throws FatalWorkspaceException
  {
    Item item = wsElement.getItem();
    subblocks.put(item, wsElement);
    Trace.send(20, traceKey, i18nTrace, "wvaddElement", wsElement);
    if (getEventHandler() instanceof WorkspaceViewEventHandler &&
	useG2Configurations) {
      WorkspaceViewEventHandler handler
	= (WorkspaceViewEventHandler)getEventHandler();
      try {
	handler.configureDispatch(item, userMode);
      } catch (G2AccessException g2ae) {
	handleG2AccessException(g2ae, ANOMALY);//bad wksp item
      }
    }
    addElement ((Component) wsElement, position);
  }
      
  /**
   * Removes the <code>WorkspaceElement elt</code>from this view..
   * @param <code>elt</code> the <code>WorkspaceElement</code> to remove
   */
  public void removeElement(WorkspaceElement elt) {
    if (hitFatalError) return;
    if (elt.isSelected())
      removeElementFromSelection(elt);
    if (getEventHandler() instanceof WorkspaceViewEventHandler &&
	useG2Configurations) {
      WorkspaceViewEventHandler handler
	= (WorkspaceViewEventHandler)getEventHandler();
      Item item = elt.getItem();
      handler.unConfigureDispatch(item);
    }
    subblocks.remove(elt.getItem());
    removeElement((Component) elt);
  }

  /**
   * Find an element created from the <code>Item item</code>.
   * @param <code>item</code> the <code>Item</code> for which to find a
   * <code>WorkspaceElement</code>.
   * @return The last <code>WorkspaceElement</code> that was added
   * to this view whose item is equal to <code>item</code>, or null if no
   * such element exists.
   * @see com.gensym.wksp.WorkspaceElement#getItem()
   */
  public WorkspaceElement findElement(Item item) {
    if (hitFatalError) return null;
    return (WorkspaceElement) subblocks.get(item);
  }
    
  private Hashtable getSubblocks() {
    return subblocks;
  }

  /**
   * Returns all the workspace elements of this view.
   * @return an <code>Enumeration</code> of all the <code>WorkpaceElement</code>s contained
   *  within this view.
   */
  public Enumeration getElements() {
    if (hitFatalError) return null;
    if (subblocks == null)
      return new Enumeration()
      {
	@Override
	public boolean hasMoreElements() { return false;}
	@Override
	public Object nextElement() { return null;}
      };
    return subblocks.elements();
  }


  private void setSubblocks(Hashtable subblocks) {
    if (this.subblocks != null) {
      this.subblocks.clear();
    }
    this.subblocks = subblocks;
  }
  
  /**
   * Returns this view's foreground color
   * @return the <code>java.awt.Color</code> used for the foreground color of
   * this view.
   */
  public Color getForegroundColor() {
    if (hitFatalError) return null;
    return foregroundColor;
  }

  /**
   * Sets the foreground color used by this view.
   * Does not change the color in the <code>KbWorkspace</code>.
   * @param <code>foregroundColor</code> the new <code>java.awt.Color</code>
   * to use as this view's foreground color.
   */
  public void setForegroundColor(Color foregroundColor) {
    if (hitFatalError) {setForegroundColor(foregroundColor); return;}
    try {
      getColorTable().put(FOREGROUND_,foregroundColor);
      this.foregroundColor = foregroundColor;
      try {
	Symbol bgColor = workspace.getBackgroundColor();
	if (FOREGROUND_.equals(bgColor))
	  setBackgroundColor(foregroundColor);
      } catch (G2AccessException g2ae) {
	handleG2AccessException(g2ae, FATAL);//bad wksp
      }
    } catch (FatalWorkspaceException fwe) {
      return;
    }
  }

  /**
   * Sets the background color used by this view.
   * Does not change the color in the <code>KbWorkspace</code>.
   * @param <code>backgroundColor</code> the new <code>java.awt.Color</code>
   * to use as this view's background color.
   */
  @Override
  public void setBackgroundColor(Color backgroundColor) {
    if (hitFatalError) {super.setBackgroundColor(backgroundColor); return;}
    try {
      getColorTable().put(BACKGROUND_, backgroundColor);
      super.setBackgroundColor(backgroundColor);
      try {
	Symbol fgColor = workspace.getForegroundColor();
	if (BACKGROUND_.equals(fgColor))
	  setForegroundColor(backgroundColor);
      } catch (G2AccessException g2ae) {
	handleG2AccessException(g2ae, FATAL);//bad wksp
      }
    } catch (FatalWorkspaceException fwe) {
      return;
    }
  }
  
  /**
   * Method for handling the <code>KbWorkspace</code>'s initial values from the
   * first download.
   * @see #ItemListener
   */
  @Override
  public void receivedInitialValues (com.gensym.util.ItemEvent e) {
    if (hitFatalError) return;
  }

  /**
   * If the info within the <code>WorkspaceEvent event</code> contains
   * color pattern changes, this method will update the foreground or
   * background colors of this view.  Passes the <code>event</code> on to
   * all the <code>WorkspaceElement</code>s contained within this view.
   */
  public void handleColorsChanged(WorkspaceEvent event) {
    if (hitFatalError) return;
    boolean needInvalidation = false;
    Structure updateInfo = event.getInfo();
    Structure colorPatternChanges
      = (Structure) updateInfo.getAttributeValue(COLOR_PATTERN_CHANGES_, null);
    Symbol backgroundColor
      = (Symbol)colorPatternChanges.getAttributeValue(BACKGROUND_COLOR_, null);
    Symbol foregroundColor
      = (Symbol)colorPatternChanges.getAttributeValue(FOREGROUND_COLOR_, null);
    if (backgroundColor != null) {
      setBackgroundColor(getColorTable().lookup(backgroundColor));
      needInvalidation = true;
    }
    else if (foregroundColor != null) {
      setForegroundColor(getColorTable().lookup(foregroundColor));
      needInvalidation = true;
    }
    if (needInvalidation) {
      Enumeration elts = getElements();
      while (elts.hasMoreElements()) {
	WorkspaceElement elt = (WorkspaceElement) elts.nextElement();
	elt.handleWorkspaceItemColorsChanged(event);
      }
      repaintCanvas ();
    }
  }

  /**
   * Handles modifications to attributes of the <code>KbWorkspace</code> itself.
   * If the attribute is either the background or foreground color,
   * with create a <code>WorkpaceEvent</code> and call <code>handleColorsChanged</code>
   * with that event.
   * @see com.gensym.util.#ItemListener
   */
  @Override
  public void itemModified (com.gensym.util.ItemEvent e) {
    if (hitFatalError) return;
    try {
      Sequence denotationSequence = e.getDenotation();
      Structure denotation = (Structure) denotationSequence.elementAt(0);
      Symbol attributeName
	= (denotation!=null?(Symbol)denotation.getAttributeValue(NAME_, null):null);
      if (BACKGROUND_COLOR_.equals(attributeName) ||
	  FOREGROUND_COLOR_.equals(attributeName)) {
	Structure updateInfo = new Structure();
	Structure colorPatternChanges = new Structure();
	updateInfo.setAttributeValue(COLOR_PATTERN_CHANGES_, colorPatternChanges);
	colorPatternChanges.setAttributeValue(attributeName, e.getNewValue());
	handleColorsChanged(new WorkspaceEvent(e.getSource(),
					       WorkspaceEvent.getNotificationCode(WorkspaceEvent.ITEM_COLOR_PATTERN_CHANGE),
					       e.getItem(),
					       updateInfo));
      } else if (BACKGROUND_IMAGES_.equals(attributeName)) {
	setBackgroundImages((Sequence)e.getNewValue());
	invalidate(new Rectangle[] {getViewBounds()});
      }
    } catch (FatalWorkspaceException fwe) {
      return;
    }
  }
  
  /**
   * Handles the notification of this view's workspace being deleted.
   * This current performs no operations.
   * Users are responsible for calling the dispose method.
   */
  @Override
  public void itemDeleted (com.gensym.util.ItemEvent e) {
    if (hitFatalError) return;
    hitFatalError = true;
    wkspDeleted = true;
    clearView();
  }

  /**
   * Creates a <code>WorkspaceElement</code> for the
   * <code>Item item</code>based on its
   * representation type.  The mapping between representation type
   * and <code>WorkspaceElement</code> sub-interfaces is as follows.<p>
   * <code>TEXT_BOX_ ==> WorkspaceTextBox <p>
   * CONNECTION_ ==> WorkspaceConnection <p>
   * ICON_WITH_CONECTIONS ==> WorkspaceIcon <p>
   * ICON_WITHOUT_CONNECTIONS ==> WorkspaceIcon <p>
   * ACTION_BUTTON_ ==> WorkspaceButton <p>
   * CHECK_BOX_ ==> WorkspaceCheckBox <p>
   * RADIO_BUTTON_ ==> WorkspaceRadioButton <p>
   * TYPE_IN_BOX_ ==> WorkspaceTypeInBox <p>
   * SLIDER_ ==> WorkspaceSlider <p>
   * ATTRIBUTE_DISPLAY_ ==> WorkspaceTable <p>
   * ATTRIBUTE_TABLE_ ==> WorkspaceTable <p>
   * ATTRIBUTE_TABLE_WITH_HEADER_ ==> WorkspaceTable <p>
   * FREEFORM_TABLE_ ==> WorkspaceFreeformTable <p>
   * DIAL_ ==> WorkspaceDial <p>
   * METER_ ==> WorkspaceMeter <p>
   * CHART_ ==> WorkspaceChart <p>
   * TREND_CHART_ ==> WorkspaceTrendChart <p></code>
   * @exception G2AccessException <p>
   * @see com.gensym.classes.Item#getRepresentationType()
   * @see com.gensym.wksp.WorkspaceRepresentationTypes
   */
  public WorkspaceElement createElement(Item item)
       throws G2AccessException
  {
    if (hitFatalError) return null;
    try {
      if (!item.isValid()) return new DeletedItemElement (item);
      WorkspaceElement newelement = null;
      WorkspaceView view = this;
      Symbol type;
      try {
	type = item.getRepresentationType();
      } catch (G2AccessException g2ae) {
	handleG2AccessException(g2ae, ANOMALY);//bad wksp item
	type = DEFAULT_REPRESENTATION_;
      }      
      //Trace.send(5, traceKey, i18nTrace, "wvcreateElement", item, type);
      if (item instanceof G2JavaBean) {
	System.out.println ("RECEIVED Bean -> " + item);
	System.out.flush ();
	newelement = new TestBeanElement ((G2JavaBean)item, this);
      } else if (TEXT_BOX_.equals(type)) {
	newelement = new WorkspaceTextBoxImpl((TextBox)item, view);
      } else if (LOOSE_END_.equals(type)) {
	if (updateWorkspaceDebug)
	  System.out.println("RECEIVED DATA FOR A LOOSE-END " +
			     item);
	newelement = new WorkspaceLooseEndImpl(item, view);
      } else if (CONNECTION_.equals(type)) {
	if (updateWorkspaceDebug)
	  System.out.println("RECEIVED DATA FOR A CONNECTION " +
			     item);
	newelement = new WorkspaceConnectionImpl((Connection)item, view);
      } else if (ICON_WITH_CONNECTIONS.equals(type)||
		 ICON_WITHOUT_CONNECTIONS.equals(type)) {
	/*if (BeanElement.PROXY_CLASS_NAME.equals(item.getAttributeValue
	  (WorkspaceElement.tw_workspace_item_class_symbol, null))) {
	  System.out.println ("\n\nThis is a COM element that has already been added. Ignoring." + item);
	  return null;
	  }*/
	newelement = new WorkspaceIconImpl((Entity)item, view);
      } else if (ACTION_BUTTON_.equals(type)) {
	newelement = new WorkspaceActionButtonImpl((ActionButton)item, view);
      } else if (RADIO_BUTTON_.equals(type)) {
	newelement = new WorkspaceRadioButtonImpl((RadioButton)item, view);
      } else if (CHECK_BOX_.equals(type)) {
	newelement = new WorkspaceCheckBoxImpl((CheckBox)item, view);
      } else if (ATTRIBUTE_DISPLAY_.equals(type)) {
	newelement = new WorkspaceAttributeDisplayImpl((Table)item, view);
      } else if (ATTRIBUTE_TABLE_.equals(type)) {
	newelement = new WorkspaceAttributeTableImpl((Table)item, view);
      } else if (ATTRIBUTE_TABLE_WITH_HEADER_.equals(type)) {
	newelement = new WorkspaceAttributeTableWithHeaderImpl((Table)item, view);
      } else if (FREEFORM_TABLE_.equals(type)) {
	newelement = new WorkspaceFreeformTableImpl((FreeformTable)item, view);
      } else if (TREND_CHART_.equals(type)) {
	newelement = new WorkspaceTrendChartImpl(item, view);
      } else if (CHART_.equals(type)) {
	newelement = new WorkspaceChartImpl(item, view);
      } else if (DIAL_.equals(type)) {
	newelement = new WorkspaceDialImpl((Dial)item,view);
      } else if (METER_.equals(type)) {
	newelement = new WorkspaceMeterImpl((Meter)item,view);
      } else if (SLIDER_.equals(type)) {
	newelement = new WorkspaceSliderImpl((Slider)item,view);
      } else if (TYPE_IN_BOX_.equals (type)) {
	newelement = new WorkspaceTypeInBoxImpl ((TypeInBox)item,view);
      } else {
	newelement = new DefaultWorkspaceElement(item, view);
      }
      //Trace.send(5, traceKey, i18nTrace, "wvcreateElementRetn", item, newelement);
      return newelement;
    } catch (FatalWorkspaceException fwe) {
      return null;
    }
  }

  /**
   * @deprecated
   */
  @Override
  public void update (Observable o, Object arg) {
    if (hitFatalError) return;
    ViewScrollState viewState = (ViewScrollState)o;
    boolean isHorizontal = viewState.isHorizontal ();
    if (false)
      System.out.println ("Workspace View Notified of change:\n" +
			  " vmin=" + viewState.getViewMin () +
			  " vmax=" + viewState.getViewMax () +
			  " lmin=" + viewState.getLogicalMin () +
			  " lmax=" + viewState.getLogicalMax ());
    int viewMin = viewState.getViewMin ();
    int deltaX, deltaY;
    if (isHorizontal) {
      deltaX = viewMin - prevHorizViewMin;
      deltaY = 0;
      prevHorizViewMin = viewMin;
    } else {
      deltaX = 0;
      deltaY = viewMin - prevVertViewMin;
      prevVertViewMin = viewMin;
    }	
    if (heavyWeightList != null) {
      for (int i=0; i<heavyWeightList.size (); i++) {	
	Component hComponent = (Component)heavyWeightList.elementAt (i);
	Point locn = hComponent.getLocation();
	if (hComponent instanceof BeanElement) {
	  BeanElement beanElt = (BeanElement)hComponent;
	  beanElt.shiftForScroll (-deltaX, -deltaY);
	} else {
	  hComponent.setLocation (locn.x - deltaX, locn.y - deltaY);
	}
      }
    }
  }

  /**
   * Show the retrieved workspace.
   * @exception IllegalArgumentException when the event contains an
   * <code>Item</code> that is not a <code>KbWorkspace</code>.
   */
  @Override
  public void itemRetrieved(ItemRetrievalEvent event) {
    Item item = event.item;
    if (!(item instanceof KbWorkspace)) {
      throw new IllegalArgumentException();
    }
    setWorkspace((KbWorkspace)item);
    setLocation(getLocation().x, getLocation().y);//hack
  }    

      
  /**
   * Currently prints a message to standard out if an itemRetrieval
   * fails.
   */
  @Override
  public void itemRetrievalFailed(ItemRetrievalEvent event) {
    String message = event.message.getMessage();
    Throwable ex = event.exception;
    if (message != null) {
      WarningDialog errorDialog = new WarningDialog(null, message, true,
						    ex!=null?ex.getMessage():message,
						    null);
      errorDialog.setVisible(true);
      Trace.exception(ex);
    }
  }

  private void readObject(java.io.ObjectInputStream stream)
  throws java.io.IOException, ClassNotFoundException{
    try {
      stream.defaultReadObject();
    } catch (java.io.NotActiveException ex) {
      Trace.exception(ex);
    }
    initialize();
  }

  private void writeObject(java.io.ObjectOutputStream out)
  throws IOException {
    //System.out.println("writeObject called: " + this);
    removeAll();
    try {
      out.defaultWriteObject();
    } catch (java.io.NotActiveException ex) {
      Trace.exception(ex);
    }
  }    

  /**
   * Clears the selection and adds the given elements to the
   * selection.
   * @see #addElementsToSelection
   */
  public void selectElements (WorkspaceElement[] newSelection) {
    if (hitFatalError) return;
    clearSelection(false);
    addElementsToSelection (newSelection);
  }

  /**
   * Adds the given elements to the selection.
   */
  public void addElementsToSelection (WorkspaceElement[] newSelection) {
    if (hitFatalError) return;
    try {
      int newCount = newSelection.length;
      debug ("adding " + newCount + " elements to selection");
      int numSelected = currentSelection.size ();
      currentSelection.ensureCapacity (numSelected + newCount);
      long t0 = System.currentTimeMillis ();
      for (int i=0; i<newCount; i++) {
	WorkspaceElement wkspElt = newSelection[i];
	wkspElt.select ();
	currentSelection.setElementAt (wkspElt, numSelected + i);
      }
      long t1 = System.currentTimeMillis ();
      //System.out.println ("Time for Selection = " + (t1 - t0) + "ms");
      fireSelectionChangeEvent();
    } catch (FatalWorkspaceException fwe) {
      return;
    }
  }

  SelectionFrame getSelectionFrame(WorkspaceElement elt) {
    return new SelectionFrame(elt, this);
  }

  boolean haveSelectedConnections()
  {
    WorkspaceElement[] sel = getSelection();
    if (sel.length>0 &&sel[0] instanceof WorkspaceConnection)
      return true;
    return false;
  }
    
  boolean isDisplaySelectionFrames()
  {
    if (haveSelectedConnections())
      return false;
    return displaySelectionFrames;
  }
    
  void setDisplaySelectionFrames(boolean displaySelectionFrames)
  {
    this.displaySelectionFrames = displaySelectionFrames;
  }

  /**
   * Adds the given element to the selection.
   */
  public void addElementToSelection (WorkspaceElement newElt) {
    if (hitFatalError) return;
    WorkspaceElement[] newElts = {newElt};
    addElementsToSelection (newElts);
  }

  /**
   * Removes the given elements from the selection.
   */
  public void removeElementsFromSelection (WorkspaceElement[] eltsToRemove) {
    removeElementsFromSelection(eltsToRemove, true);
  }
    
  private void removeElementsFromSelection (WorkspaceElement[] eltsToRemove,
					    boolean updateSelectionListeners) {
    if (hitFatalError) return;
    int numEltsToRemove = eltsToRemove.length;
    if (numEltsToRemove == 0)
      return;
    for (int i=numEltsToRemove - 1; i>=0; i--) {
      WorkspaceElement wkspElt = eltsToRemove[i];
      wkspElt.unselect ();
      int eltIndex = currentSelection.indexOf (wkspElt);
      currentSelection.removeElementAt (eltIndex);
    }
    if (updateSelectionListeners)
      fireSelectionChangeEvent();
  }

  /**
   * Removes the given element from the selection.
   */
  public void removeElementFromSelection (WorkspaceElement eltToRemove) {
    if (hitFatalError) return;
    WorkspaceElement[] eltsToRemove = {eltToRemove};
    removeElementsFromSelection (eltsToRemove);
  }

  /**
   * Gets the currently selected <code>WorkspaceElement</code>s.
   * @return the current selection.
   */
  public WorkspaceElement[] getSelection () {
    if (hitFatalError) return null;
    if (currentSelection == null)
      return null;
    return currentSelection.getSelection ();
  }

  /**
   * For VB only
   * @undocumented
   */
  public Sequence getSelectionAsSequence()
  {
    if (hitFatalError) return null;
    WorkspaceElement[] sel = currentSelection.getSelection();
    int count = sel.length;
    Sequence seq = new Sequence(count);
    for (int i = 0;i<count;i++) {
      seq.addElement(sel[i]);
    }
    return seq;
  }

  /**
   * Clears the current selection.
   */
  public void clearSelection () {
    clearSelection(true);
  }
    
  private void clearSelection (boolean updateSelectionListeners) {
    if (hitFatalError) return;
    debug ("Clearing Selection!");
    WorkspaceElement[] eltsToRemove = currentSelection.getSelection ();
    debug ("Before clearing: there are " + eltsToRemove.length + " elements in the selection");
    removeElementsFromSelection (eltsToRemove,updateSelectionListeners);
    debug ("After clearing: There are now " + currentSelection.size () + " entries in the selection");
  }
    
  /**
   * @undocumented
   */
  public void addGhosts () {
    if (hitFatalError) return;
    currentSelection.addGhosts ();
  }
    
  /**
   * @undocumented
   */
  public void setConnectionGhost(ConnectionDraggingGhost cdg)
  {
    if (hitFatalError) return;
    currentSelection.setConnectionGhost(cdg);
  }
    
  /**
   * @undocumented
   */
  public ConnectionDraggingGhost getConnectionGhost()
  {
    if (hitFatalError) return null;
    return currentSelection.getConnectionGhost();
  }    
    
  /**
   * @undocumented
   */
  public void moveConnectionGhost(int deltaX, int deltaY)
  {
    if (hitFatalError) return;
    currentSelection.moveConnectionGhost(deltaX, deltaY);
  }    
    
  /**
   * @undocumented
   */
  public Vector getGhosts() {
    if (hitFatalError) return null;
    return currentSelection.getGhosts();
  }
    
  /**
   * @undocumented
   */
  public Rectangle getGhostBounds()
  {
    if (hitFatalError) return null;
    Rectangle rect = null;
    Vector ghosts = getGhosts();
    Enumeration e = ghosts.elements();
    while(e.hasMoreElements()) {
      DraggingGhost g = (DraggingGhost)e.nextElement();
      Rectangle gRect = g.getBounds();
      if (rect == null)
	rect = gRect;
      else
	rect = rect.union(gRect);
    }
    return rect;
  }

  /**
   * @undocumented
   */
  public void moveGhosts (int deltaX, int deltaY) {
    if (hitFatalError) return;
    currentSelection.moveGhosts (deltaX, deltaY);
  }
    
  /**
   * @undocumented
   */
  public void resizeGhosts (MarkerElement marker, int currentX, int currentY) {
    if (hitFatalError) return;
    currentSelection.resizeGhosts (marker, currentX, currentY);
  }
    
  /**
   * @undocumented
   */
  public void removeGhosts () {
    if (hitFatalError) return;
    currentSelection.removeGhosts ();
  }

  /**
   * @undocumented
   */    
  public void makeConnection(WorkspaceConnection wc,
			     WorkspaceElement we,
			     Symbol makeConnectionMode,
			     Sequence connectionPositionSequence)
  throws G2AccessException
  {
    if (hitFatalError) return;
    Connection wci = (Connection)wc.getItem();
    Item wei = null;
    if (we != null)
      wei = we.getItem();
    wci.setVerticesAndJoin(wei,
			   makeConnectionMode,
			   connectionPositionSequence);    
  }
    
  /**
   *@deprecated
   */
  public void moveSelection (int deltaX, int deltaY) {
    if (hitFatalError) return;
    moveSelection(deltaX, deltaY, true);
  }
    
  /**
   * Moves the currentSelection by the given deltas.
   * @param <code>deltaX</code> the horizontal distance by which each element should be moved.
   * @param <code>deltaY</code> the vertical distance by which each element should be moved.
   * @param <code>enlargeWorkspaceIfNecessary</code> if true instructs G2 to stretch the workspace,
   * otherwise the element is constrained within the workspace's margins.
   */    
  public void moveSelection (int deltaX, int deltaY, boolean enlargeWorkspaceIfNecessary) {
    if (hitFatalError) return;
    try {
      WorkspaceElement[] selection = currentSelection.getSelection ();
      int count = selection.length;
      Vector selectedItems = new Vector(), locations = new Vector();
      Point[] initialLocations = currentSelection.getInitialLocations();
      Item item;
      Point location;
      for (int i=0;i<=count-1;i++) {
	item = selection[i].getItem();
	location = initialLocations[i];
	if ((item instanceof NameBox) ||
	    (item instanceof TableItem)) {
	  locations.addElement(location);
	  selectedItems.addElement(item);
	} else if ((item instanceof Connection)) {
	  //System.out.("SHOULDN'T BE MOVING CONNECTION SELECTION");
	} else {
	  locations.insertElementAt(location,0);
	  selectedItems.insertElementAt(item,0);
	}
      }
      
      int newX, newY;
      Enumeration itemEnum = selectedItems.elements();
      Enumeration locationsEnum = locations.elements();
      while (itemEnum.hasMoreElements()) {
	try {
	  item = (Item)itemEnum.nextElement();
	  location = (Point)locationsEnum.nextElement();
	  newX = location.x + deltaX;
	  newY = location.y - deltaY;
	  /*System.out.println("LOCATION = " + location +
	    "DELTAX = " + deltaX +
	    "DELTAY = " + deltaY +
	    "NEWX = " + newX +
	    "NEWY = " + newY);*/
	  item.moveBy(deltaX, deltaY, enlargeWorkspaceIfNecessary);
	  //item.move(newX, newY,enlargeWorkspaceIfNecessary);
	  //??? BeanElement??
	  // put this hack in Item
	  //if (elt.tw_workspace_item_representation_type == null)
	  //wkspView.shiftElement (elt, deltaX, deltaY);
	} catch (G2AccessException g2ae) {
	  // fix this: notify user in some way.
	  // catching here because not necessarily every call will fail.
	  // However need to decide how many failures one should plow
	  // through before giving up.
	  handleG2AccessException(g2ae, ANOMALY);
	}
      }
      currentSelection.resetInitialLocations();
    } catch (FatalWorkspaceException fwe) {
      return;
    }
  }

  /**
   * If the current selection consists of one and only one
   * element then this method will resize it to the given bounds.
   * Otherwise, a RuntimeException is thrown stating that resizing
   * more than one item is not currently supported.
   *@deprecated
   */
  public void resizeSelection (int left, int top, int right, int bottom) {
    if (hitFatalError) return;
    try {
      WorkspaceElement[] selection = currentSelection.getSelection ();
      if (selection.length != 1)
	throw new RuntimeException ("Resize of more than 1 item is not currently supported");
      WorkspaceElement resizedElement = selection[0];
      try {
	Item item = resizedElement.getItem();
	TwAccess context
	  = (TwAccess)((ImplAccess)item).getContext(); //hack for now=
	item.setBounds(left,-top,right,-bottom);
      } catch (G2AccessException g2ae) {
	handleG2AccessException (g2ae, ANOMALY);//bad wksp item
      }
    } catch (FatalWorkspaceException fwe) {
      return;
    }
  }
    
  private boolean workspaceElementIsResizable(WorkspaceElement elt)
  {
    return !(elt instanceof WorkspaceButton ||
	     elt instanceof WorkspaceMeter ||
	     elt instanceof WorkspaceDial ||
	     elt instanceof WorkspaceTable);
  }
  
  void resizeSelection(MarkerElement marker, int currentX, int currentY)
       throws FatalWorkspaceException
  {
    WorkspaceElement orig = getWorkspaceElementFromMarker(marker);
    
    if (orig == null) {
      return;
    }
    Rectangle origBounds = ((DrawElement)orig).getExactBounds()[0];
    int origWidth = origBounds.width;
    int origHeight = origBounds.height;
    Rectangle origResized = getResizingBounds (marker, currentX, currentY);
    int origResizedWidth = origResized.width, origResizedHeight = origResized.height;
    int deltaX = origResized.x - origBounds.x, deltaY = origResized.y - origBounds.y;
    for (int i=0; i<currentSelection.size (); i++) {
      WorkspaceElement elt = (WorkspaceElement)(currentSelection.elementAt (i));
      if (workspaceElementIsResizable(elt)) {
	Rectangle bnds = ((DrawElement)elt).getExactBounds()[0];
	int newWidth = (bnds.width*origResizedWidth)/origWidth;
	int newHeight = (bnds.height*origResizedHeight)/origHeight;
	int deltaWidth = newWidth - bnds.width;
	int deltaHeight = newHeight - bnds.height;
	int newX = bnds.x, newY = bnds.y;
	if (deltaX != 0) 
	  newX -= deltaWidth;
	if (deltaY != 0)
	  newY -= deltaHeight;
	int left = newX, top = newY;
	int right = newX + newWidth, bottom = newY + newHeight;
	try {
	  Item item = elt.getItem();
	  TwAccess context = (TwAccess)((ImplAccess)item).getContext(); //hack for now=
	item.setBounds(left,-top,right,-bottom);
	} catch (G2AccessException g2ae) {
	  handleG2AccessException (g2ae, ANOMALY);//bad wksp item
	}
      }
    }
  }
    
  /**
   * @undocumented
   */        
  public void elementChanged (WorkspaceElement elt) {
    if (hitFatalError) return;
    currentSelection.elementChanged (this, elt);
    //clipboardData.elementChanged (elt);
  }

  static void debug (String verbosity) {
    if (debugCmds) {
      System.out.println (verbosity);
      System.out.flush ();
    }
  }
    
  /**
   * @undocumented
   */    
  public WorkspaceElement getWorkspaceElementFromMarker (MarkerElement marker) {
    if (hitFatalError) return null;
    return currentSelection.getWorkspaceElementFromMarker (marker);
  }

  Rectangle getResizingBounds (MarkerElement marker, int currentX, int currentY) {
    WorkspaceElement elt = getWorkspaceElementFromMarker(marker);
    int left, top, width, height;
    Rectangle eltBounds = (((DrawElement)elt).getExactBounds ())[0];
    int elementLeft = eltBounds.x,
        elementTop = eltBounds.y,
        elementRight = eltBounds.x + eltBounds.width,
        elementBottom = eltBounds.y + eltBounds.height;
    switch (marker.location) {
    case 0: // LT
      left = currentX; top = currentY;
      width = elementRight - currentX; height = elementBottom - currentY;
      break;
    case 1: // TOP
      left = eltBounds.x; top = currentY;
      width = eltBounds.width; height = elementBottom - currentY;
      break;
    case 2: // RT
      left = eltBounds.x; top = currentY;
      width = currentX - left; height = elementBottom - currentY;
      break;
    case 3: // RIGHT
      left = eltBounds.x; top = eltBounds.y;
      width = currentX - left; height = eltBounds.height;
      break;
    case 4: // RB
      left = elementLeft; top = elementTop;
      width = currentX - left; height = currentY - top;
      break;
    case 5: // BOTTOM
      left = eltBounds.x; top = eltBounds.y;
      width = eltBounds.width; height = currentY - top;
      break;
    case 6: // LB
      left = currentX; top = eltBounds.y;
      width = elementRight - currentX; height = currentY - top;
      break;
    case 7: // LEFT
      left = currentX; top = eltBounds.y;
      width = elementRight - currentX; height = eltBounds.height;
      break;
    default:
      left = eltBounds.x; top = eltBounds.y;
      width = eltBounds.width; height = eltBounds.height;
      break;
    }
    return new Rectangle (left, top, width, height);
  }

  /**
   * Adds all of workspace's elements to the current selection.
   */
  public void selectAll () {
    if (hitFatalError) return;
    clearSelection ();
    for (java.util.Enumeration e = getElements ();
	 e.hasMoreElements ();) {
      WorkspaceElement wElt = (WorkspaceElement) e.nextElement ();
      if (elementIsTransferrable (wElt))
	addElementToSelection (wElt);
    }
  }

 /**
  * Indicates if a particular element corresponds to a G2 Item
  * that is transferrable. Subblocks, name-boxes, attribute-displays,
  * and connections are not transferrable on their own.
  */
  boolean elementIsTransferrable (WorkspaceElement wElt) {
    return (!(wElt instanceof DeletedItemElement) &&
	    !(wElt instanceof WorkspaceConnection) &&
	    !(wElt instanceof WorkspaceAttributeDisplayImpl) &&
	    !((wElt instanceof WorkspaceTextBoxImpl) &&
	      (wElt.getItem () instanceof com.gensym.classes.NameBox)));
  }


  /**
   * Deletes the items corresponding to each of the elements
   * in the current selection.
   */
  public void deleteSelection () {
    if (hitFatalError) return;
    try {
      WorkspaceElement[] selection = currentSelection.getSelection ();
      if (selection.length == 0)
	return;
      WorkspaceElement deletedElement;
      for (int i=0; i<selection.length; i++) {
	deletedElement = selection[i];
	Item item = deletedElement.getItem();
	try {
	  item.delete (true, false);
	} catch (G2ItemDeletedException g2ide) {
	  // Do nothing. No trace!
	} catch (G2AccessException g2ae) {
	  handleG2AccessException (g2ae, ANOMALY);//bad wksp item
	}
      }
    } catch (FatalWorkspaceException fwe) {
      return;
    }
  }


  /**
   * Lifts the current selection to the front of all items on
   * the workspace.
   */
  public void liftSelectionToTop () {
    if (hitFatalError) return;
    try {
      WorkspaceElement[] selection = currentSelection.getSelection ();
      int numItems = selection.length;
      if (numItems == 0)
	return;
      Vector itemsToSelect = new Vector (numItems);
      WorkspaceElement elt;
      for (int i=0; i<numItems; i++) {
	elt = selection[i];
	Item item = elt.getItem();
	itemsToSelect.addElement (item);
      }
      setItemsPendingSelection (itemsToSelect, createVectorOfElementsForItems (itemsToSelect));
      for (int i=0; i<numItems; i++) {
	elt = selection[i];
	Item item = elt.getItem();
	try {
	  item.liftToTop ();
	} catch (G2AccessException g2ae) {
	  handleG2AccessException (g2ae, ANOMALY);//bad wksp item
	}
      }
    } catch (FatalWorkspaceException fwe) {
      return;
    }
  }


  /**
   * Drops the current selection behind all items on
   * the workspace.
   */
  public void dropSelectionToBottom () {
    if (hitFatalError) return;
    try {
      WorkspaceElement[] selection = currentSelection.getSelection ();
      int numItems = selection.length;
      if (numItems == 0)
	return;
      Vector itemsToSelect = new Vector (numItems);
      WorkspaceElement elt;
      for (int i=0; i<numItems; i++) {
	elt = selection[i];
	Item item = elt.getItem();
	itemsToSelect.addElement (item);
      }
      setItemsPendingSelection (itemsToSelect, createVectorOfElementsForItems (itemsToSelect));
      for (int i=0; i<numItems; i++) {
	elt = selection[i];
	Item item = elt.getItem();
	try {
	  item.dropToBottom ();
	} catch (G2AccessException g2ae) {
	  handleG2AccessException (g2ae, ANOMALY);//bad wksp item
	}
      }
    } catch (FatalWorkspaceException fwe) {
      return;
    }
  }

  /**
   * Support for selecting items that we know will
   * soon be transferred to this workspace.
   * Used for Paste (transfer on) and currently
   * for lift-to-top/drop-to-bottom, which are
   * essentially transfer off + transfer on.
   */
  void setItemsPendingSelection (Vector itemsToSelect,Vector previousElements) {
    //System.out.println ("setItemsPendingSelection (" + itemsToSelect + ")");
    if (itemsToSelect != null) {
      synchronized (itemsToSelect) {
	int numItems = itemsToSelect.size ();
	if (previousElements != null) {
	  pendingItemsCutStatus = new Vector (numItems);
	  for (int i=0;i<numItems; i++) {
	    WorkspaceElement elt = (WorkspaceElement) previousElements.elementAt (i);
	    pendingItemsCutStatus.addElement (elt.isCut () ? Boolean.TRUE : Boolean.FALSE);
	  }	  
	}
	//System.out.println ("Cut Status = " + pendingItemsCutStatus);
	pendingItemsForSelection = itemsToSelect;
	for (int i=numItems; i-->0;) {
	  Item itm = (Item)pendingItemsForSelection.elementAt (i);
	  /*if (workspace.equals (((ImplAccess)itm).getParentWorkspace ())) // Already on the workspace check */
	  WorkspaceElement currentElement = findElement (itm);
	  if (currentElement != null) {
	    //System.out.println ("  >> Found Element : removing from Pending list if " +
	    //		(previousElements == null || !previousElements.contains (currentElement)));
	    if (previousElements == null || !previousElements.contains (currentElement)) {
	      removeItemPendingSelection (itm);
	    }
	  }
	}
      }
    } else {
      pendingItemsForSelection = null;
      pendingItemsCutStatus = null;
    }
    System.out.flush ();
  }

  Vector getItemsPendingSelection () {
    return pendingItemsForSelection; // Orig list, not a clone!
  }

  void removeItemPendingSelection (Item itm) {
    //System.out.println ("  removeItemPendingSelection (" + itm + ") list = " + pendingItemsForSelection);
    if (pendingItemsForSelection != null) {
      synchronized (pendingItemsForSelection) {
	if (pendingItemsForSelection == null) return;
	int pendingItemIndex = pendingItemsForSelection.indexOf (itm);
	//System.out.println ("  Got Index " + pendingItemIndex + ", Adding to Selection!");
	if (pendingItemIndex >= 0) {
	  WorkspaceElement newElt = findElement (itm);
	  addElementToSelection (newElt); // Guaranteed to be found!
	  pendingItemsForSelection.removeElementAt (pendingItemIndex); // clear it!
	  if (pendingItemsCutStatus != null) {
	    Boolean cutStatus = (Boolean) pendingItemsCutStatus.elementAt (pendingItemIndex);
	    pendingItemsCutStatus.removeElementAt (pendingItemIndex);
	    System.out.println ("# " + itm + " -> " + pendingItemIndex + " = " + cutStatus);
	    if (cutStatus.booleanValue ())
	      newElt.setCut (true);
	  }
	  if (pendingItemsForSelection.isEmpty ())
	    setItemsPendingSelection (null, null);
	}
      }
    }
  }

  /**
   * Adds the <code>SelectionListener sl</code> to this view's list of
   * <code>SelectionListener</code>s.
   * @param <code>sl</code> the <code>SelectionListener</code> to add as a
   * <code>SelectionListener</code>
   */    
  public void addSelectionListener (SelectionListener sl) {
    selnListeners.addElement (sl);
  }

  /**
   * Removes <code>sl</code> from this view's list of
   * <code>SelectionListener</code>s.
   * @param <code>sl</code> the SelectionListener to remove as a
   * <code>SelectionListener</code>
   */    
  public void removeSelectionListener (SelectionListener sl) {
    selnListeners.removeElement (sl);
  }

  void fireSelectionChangeEvent () {
    int listenerCount;
    Vector listeners = null;
    synchronized (selnListeners) {
      listenerCount = selnListeners.size();
      if (listenerCount == 0)
	return;
      listeners = (Vector) selnListeners.clone();
    }
    SelectionEvent selnEvent = new SelectionEvent (this);
    for (int i=0; i<listenerCount; i++) {
      SelectionListener listener = ((SelectionListener)listeners.elementAt (i));
      if (listener != null)
 	listener.selectionChanged (selnEvent);
    }
  }
    
  /**
   * Sets the current block increment used for scrolling.
   * This is typically used for scrolling pages at a time.
   */
  public void setBlockIncrement(int blockIncrement)
  {
    this.blockIncrement = blockIncrement;
  }
    
  /**
   * Sets the current unit increment used for scrolling.
   * This is typically used for scrolling using the arrow keys.
   */
  public void setUnitIncrement(int unitIncrement)
  {
    this.unitIncrement = unitIncrement;
  }
    
  /**
   * Gets the current block increment.
   * This is typically used for scrolling pages at a time.
   * @return the current block increment used for scrolling.
   */
  public int getBlockIncrement()
  {
    return this.blockIncrement;
  }
    
  /**
   * Gets the current unit increment. This is typically used for
   * scrolling using the arrow keys.
   * @return the current unit increment used for scrolling.
   */
  public int getUnitIncrement()
  {
    return this.unitIncrement;
  }
    
  /**
   * Scrolls the view to the up by the current unit increment.
   */
  public void scrollUnitUp()
  {
    if (hitFatalError) return;
    scrollView(-unitIncrement, false);
  }
    
  /**
   * Scrolls the view to the down by the current unit increment.
   */    
  public void scrollUnitDown()
  {
    if (hitFatalError) return;
    scrollView(unitIncrement, false);
  }
    
  /**
   * Scrolls the view to the left by the current unit increment.
   */    
  public void scrollUnitLeft()
  {
    if (hitFatalError) return;
    scrollView(-unitIncrement, true);
  }
    
  /**
   * Scrolls the view to the right by the current unit increment.
   */  
  public void scrollUnitRight()
  {
    if (hitFatalError) return;
    scrollView(unitIncrement, true);
  }
    
  /**
   * Scrolls the view to the up by the current block increment.
   */
  public void scrollBlockUp()
  {
    if (hitFatalError) return;
    scrollView(-blockIncrement, false);
  }
    
  /**
   * Scrolls the view to the down by the current block increment.
   */    
  public void scrollBlockDown()
  {
    if (hitFatalError) return;
    scrollView(blockIncrement, false);
  }

  /**
   * Scrolls the view to the left by the current block increment.
   */    
  public void scrollBlockLeft()
  {
    if (hitFatalError) return;
    scrollView(-blockIncrement, true);
  }

  /**
   * Scrolls the view to the right by the current block increment.
   */
  public void scrollBlockRight()
  {
    if (hitFatalError) return;
    scrollView(blockIncrement, true);
  }

  @Override
  protected void paintBackground(Graphics g)
  {
    super.paintBackground(g);
    if (hitFatalError) {
      Dimension size = getSize();
      String msg = i18n.getString(wkspDeleted ? "WorkspaceDeleted" :
				  "problemRenderingWorkspace");
      int msgSize =
	WorkspaceButtonImpl.computeWidthOfTextString(msg, g.getFontMetrics());
      g.setColor(Color.black);
      g.drawString(msg,size.width/2 - msgSize/2, size.height/2);
      return;
    }
    if (backgroundImages == null) return;
    
    int shift_x = /*horizontal_state.logical_min */ 0 -
      horizontal_state.getViewMin();
    int shift_y = /* vertical_state.logical_min */ 0 -
      vertical_state.getViewMin();
    try {
      g.translate(shift_x, shift_y);
      int count = backgroundImages.size();
      for (int i=0; i<count;i++) {
	Image backgroundImage = (Image)backgroundImages.elementAt(i);
	if (backgroundImage != null) {
	  Rectangle imageLocation = (Rectangle)imageLocations.elementAt(i);
	  int backgroundImageX = imageLocation.x;
	  int backgroundImageY = imageLocation.y;	
	  g.drawImage(backgroundImage, backgroundImageX,backgroundImageY, null);
	}
      }
    } finally {
      g.translate(- shift_x, - shift_y);
    }
  }

    /* Test code to see how much is painted. Must be called on
       non-double-buffered wkspView*/
    /*
  public void paint1 (Graphics g) {
    System.out.print ("<" + g.getClipRect () + ">");
    g.setColor (Color.red);
    g.fillRect (-1000, -1000, 2000, 2000);
    try {
      Thread.currentThread().sleep (500);
    } catch (InterruptedException ie) {
    }
    super.paint (g);
  }
  */

  /**
   * Converts a point in the WorkspaceView's co-ordinate system to a point in
   * the KbWorkspace's co-ordinate system.
   */
  public void convertPointToKbWorkspace(Point point){
    if (hitFatalError) return;
    point.x = point.x + getScrollState(true).getViewMin();
    point.y = -(point.y + getScrollState(false).getViewMin());
  }

  /**
   * @undocumented
   */        
  @Override
  public void lostOwnership (Clipboard clpbd, Transferable contents) {
    //System.out.println (this + " lost ownership of clipboard!");
    ownClipboard = false;
    if (hitFatalError) return;
    resetClipboardContents ();
  }
 

  private transient SelectionCommandGenerator menuGenerator;
    
  private transient static SelectionCommandGenerator theMenuGenerator;
    
  public SelectionCommandGenerator getSelectionCommandGenerator () {
    return menuGenerator;
  }

  protected SelectionCommandGenerator makeSelectionCommandGenerator () {
    if (theMenuGenerator == null)
      theMenuGenerator = new SelectionCommandGenerator (this);
    return theMenuGenerator;
  }

  /**
   * Cut / Copy Buffer handling
   */
  static final boolean okToUseCutCopyPaste = true;
  static final Clipboard systemClipboard = new WorkspaceClipboard ("Gensym kb-workspace clipboard");
  private static boolean clipboardDataWasCut;
  WorkspaceClipboardData clipData;
  private boolean ownClipboard;
  private static final Symbol G2_TRANSFER_ITEMS_ = Symbol.intern ("G2-TRANSFER-ITEMS");
  private static final Symbol G2_CLONE_AND_TRANSFER_ITEMS_ = Symbol.intern ("G2-CLONE-AND-TRANSFER-ITEMS");

  private void setClipboardContents (boolean cutToBuffer) {
    synchronized (systemClipboard) {
      //System.out.println ("setClipboardContents (" + cutToBuffer + ")");
      resetClipboardContents ();
      clipData = new WorkspaceClipboardData (this, cutToBuffer);
      ownClipboard = true;
      systemClipboard.setContents (clipData, this);
      clipboardDataWasCut = cutToBuffer;
      if (!cutToBuffer)
	return;
      WorkspaceElement[] selection = clipData.getSelectionSnapshot ();
      for (int i=0; i<selection.length; i++)
	selection[i].setCut (true);
    }
  }

 /**
  * Access needed by Commands
  * @undocumented
  */
  public Clipboard getWorkspaceClipboard() {
    if (hitFatalError) return null;
    return systemClipboard;
  }

 /**
  * Access needed by Commands
  * @undocumented
  */
  public void copySelectionToClipboard () {
    if (hitFatalError) return;
    setClipboardContents (false);
  }

  /**
   * Access needed by Commands
   * @undocumented
   */
  public void cutSelectionToClipboard () {
    if (hitFatalError) return;
    setClipboardContents (true);
  }

  void resetClipboardContents () {
    synchronized (systemClipboard) {
      //System.out.println ("resetClipboardContents ()");
      if ((clipData == null) || !ownClipboard)
	return;
      boolean wasCut = clipData.wasCut ();
      if (wasCut) {
	WorkspaceElement[] selection = clipData.getSelectionSnapshot ();
	for (int i=0; i<selection.length; i++)
	  selection[i].setCut (false);
      }
      systemClipboard.setContents (null, null);
      clipData = null;
    }
  }

  void checkClipboard (WorkspaceElement wElt) {
    if (clipData != null)
      clipData.elementChanged (wElt);
  }

  /**
   * Access needed by Commands
   * @undocumented
   */
  public void pasteClipboardContents (Item[] data, int centerX, int centerY) throws G2AccessException {
    if (hitFatalError) return;
    synchronized (systemClipboard) {
      Sequence iList = createSequenceOfSelections (data);
      Point selnCenter = determineCenterOfSelection (data);
      Object[] rpcArgs = {iList, getItem (),
			  new Integer (centerX - selnCenter.x),
			  new Integer (centerY - selnCenter.y)};
      TwAccess cxn = (TwAccess)((ImplAccess)getItem ()).getContext ();
      Symbol rpcName_ = (clipboardDataWasCut ? G2_TRANSFER_ITEMS_ : G2_CLONE_AND_TRANSFER_ITEMS_);
      if (clipboardDataWasCut) {
	cxn.callRPC (rpcName_, rpcArgs);
	clipboardDataWasCut = false;
      } else
	iList = (Sequence) cxn.callRPC (rpcName_, rpcArgs);
      clearSelection ();
      setItemsPendingSelection (iList, null);
    }
  }

  /**
   * @undocumented
   */    
  public Point getCurrentSelectionCenter() throws G2AccessException {
     WorkspaceElement[] we = getSelection();
     if (we != null && we.length != 0) {
       Item[] items = new Item[we.length];
       for (int i=0; i<we.length; i++)
 	items[i] = we[i].getItem();
       return determineCenterOfSelection(items);
    } return null;
   }
    
  private Point determineCenterOfSelection (Item[] data) throws G2AccessException {
    int x = 0, y = 0;
    for (int i=0; i<data.length; i++) {
      Item itm = data[i];
      x += itm.getItemXPosition ();
      y += itm.getItemYPosition ();
    }
    return new Point (x/data.length, y/data.length);
  }

  private Sequence createSequenceOfSelections (Item[] data) {
    Sequence itemSequence = new Sequence (data.length);
    for (int i=0; i<data.length; i++)
      itemSequence.addElement (data[i]);
    return itemSequence;
  }

  private Vector createVectorOfElementsForItems (Vector itemList) {
    Vector itemSequence = new Vector (itemList.size ());
    for (int i=0; i<itemList.size (); i++)
      itemSequence.addElement (findElement ((Item)itemList.elementAt (i)));
    return itemSequence;
  }

  /**
   * Coordinate translation APIs
   */
  /**
   * Converts a point from AWT container co-ordinates to
   * PersistentCanvas view co-ordinates
   * @undocumented
   */
  public void translateWindowToView (Point pt) {
    if (hitFatalError) return;
    Rectangle viewBounds = getViewBounds ();
    int shiftX = viewBounds.x;
    int shiftY = viewBounds.y;
    pt.x += shiftX; pt.y += shiftY;
  }

  /**
   * Converts a point from PersistentCanvas view co-ordinates
   * to kb-workspace co-ordinates
   * @undocumented
   */
  public void translateViewToWorkspace (Point pt) {
    if (hitFatalError) return;
    pt.y = -pt.y;
  }

  /**
   * Converts a point from kb-workspace co-ordinates
   * PersistentCanvas view co-ordinates
   * @undocumented
   */
  public void translateWorkspaceToView (Point pt) {
    if (hitFatalError) return;
    pt.y = -pt.y;
  }

  /**
   * Converts a point from PersistentCanvas view co-ordinates
   * to AWT container co-ordinates
   * @undocumented
   */
  public void tranlateViewToWindow (Point pt) {
    if (hitFatalError) return;
    Rectangle viewBounds = getViewBounds ();
    int shiftX = viewBounds.x;
    int shiftY = viewBounds.y;
    pt.x -= shiftX; pt.y -= shiftY;
  }

    // Palette Support
  boolean pendingPaletteDrop = false;

  private void initializeForPaletteDrop () {
    Palette.removePaletteListener(this);
    Palette.addPaletteListener (this);
    Palette[] palettes = Palette.getPalettes ();
    for (int i=palettes.length; --i>=0;) {
      //System.out.println ("Hit Index ; " + i);
      Palette palette = palettes[i];
      if (palette instanceof G2Palette){
	palette.removePaletteDropTarget (this);
	if (workspace != null){
	  if (((G2Palette)palette).getConnection().equals(((ImplAccess)workspace).getContext()))//hack for now
	    palette.addPaletteDropTarget (this);
	}
      }
    }
    if (pendingPaletteDrop)
      resetPaletteDropState();
    //System.out.println ("Registered " + this + " with " + palettes.length + " palettes -> " + com.gensym.core.DebugUtil.printArray (palettes));
  }

  @Override
  public void paletteButtonStateChanged (PaletteEvent event) {
    if (hitFatalError) return;
    //System.out.println ("Target got Palette Event : " + event);
    int cursorType;
    if (event.getButton().isSelected()) {
      //System.out.println ("Pending Palette Drop!");
      pendingPaletteDrop = true;
      requestFocus ();
      cursorType = Cursor.CROSSHAIR_CURSOR;
      currentPalette = (Palette)event.getSource();
      currentButton = event.getButton();
      setCursor (new Cursor (cursorType));
    } else
      resetPaletteDropState();
  }

  private void resetPaletteDropState(){
    pendingPaletteDrop = false;
    currentPalette = null;
    currentButton = null;
    setCursor (new Cursor (Cursor.DEFAULT_CURSOR));
  }

  @Override
  public void paletteCreated(PaletteEvent event) {
    if (hitFatalError) return;
    //System.out.println ("New Palette Created -> " + event);
    if (workspace != null){
      Palette palette = (Palette)event.getSource();
      if (palette instanceof G2Palette){
	//System.out.println("palette="+palette);
	//System.out.println("cxn="+((G2Palette)palette).getConnection());
	//System.out.println("wksp="+workspace);
	if (((G2Palette)palette).getConnection().equals(((ImplAccess)workspace).getContext()))//hack for now
	  palette.addPaletteDropTarget (this);
      }
    }
  }

  void dropItem(MouseEvent me, Point startPoint) {//throws G2AccessException {
    //System.out.println ("Notifying Listeners of Drop!");
    //System.out.println ("Creating New Item!");
    clearSelection ();
    Item newG2Item = (Item) currentButton.createObject ();
    int x = me.getX (); int y = me.getY ();
    int top, right, left, bottom;
    Point pt = new Point (x, y);
    translateWindowToView (pt);
    translateViewToWorkspace (pt);
    try {
      newG2Item.transferTo (getWorkspace(), pt.x, pt.y);
      if (startPoint != null) {
	translateWindowToView (startPoint);
	translateViewToWorkspace (startPoint);
	if (pt.x<startPoint.x) {
	  left = pt.x;
	  right = startPoint.x;
	} else {
	  left = startPoint.x;
	  right = pt.x;
	}
	if (pt.y<startPoint.y) {
	  top = startPoint.y;
	  bottom = pt.y;
	} else {
	  top = pt.y;
	  bottom = startPoint.y;
	}
	if (left != right && top != bottom) 
	  newG2Item.setBounds(left, top, right, bottom);
      }
      //WorkspaceElement wElt = findElement (newG2Item); <- Select it when we get notified
      currentPalette.dropOccurred();
      if (workspace.getPermanent())//NOTE: attribute not cached!
	newG2Item.makePermanent();
      Vector itemsToSelect = new Vector();
      itemsToSelect.addElement(newG2Item);
      clearSelection ();
      setItemsPendingSelection(itemsToSelect, null);
    } catch (G2AccessException gae) {
      System.out.println("exception in sizing");
      try {
	handleG2AccessException (gae, ANOMALY);//bad palette transfer
      } catch (FatalWorkspaceException fwe) {
	return;
      }
    }
  }
  
  private Palette currentPalette;
  private PaletteButton currentButton;

  @Override
  protected void processKeyEvent (KeyEvent ke) {
    if (hitFatalError) return;
    //System.out.println (ke);
    if (pendingPaletteDrop) {
      if (ke.getID () == KeyEvent.KEY_PRESSED) {
	int keyCode = ke.getKeyCode ();
	if (keyCode == KeyEvent.VK_ESCAPE) {
	  currentPalette.dropCancelled();
	}
      }
    } else
      super.processKeyEvent (ke);
    if (com.gensym.core.GensymApplication.getDevOption () && 
	ke.getID () == KeyEvent.KEY_PRESSED && ke.getKeyChar () == 'd') {
      try {
	dumpItems ();
      } catch (FatalWorkspaceException fwe) {
	return;
      }
    }
  }

  void dumpItems ()
  throws FatalWorkspaceException
  {
      try {
	Component[] children = getComponents ();
	String name;
	for (int i=0; i<children.length; i++) {
	  Component c = children[i];
	  System.out.print ("# " + i + " = " + c);
	  if (c instanceof WorkspaceElement) {
	    Item itm = ((WorkspaceElement)c).getItem ();
	    if (itm != null && itm.isValid ())
	      name =  "" + ((com.gensym.classes.Block)itm).getNames ();
	    else
	      name = "";
	    System.out.println ("  -> " + itm + " : " + name);			
	  } else
	    System.out.println (" NO ITEM");
	}
	((com.gensym.classes.G2__BaseImpl)getItem ()).dumpWkspItemList ();
      } catch (G2AccessException g2ae) {
	handleG2AccessException (g2ae, ANOMALY);//debuging code
      }
    }
 
  private boolean allowDoubleClickToEdit = true;

  /**
   * Can be used to check if the double-click gesture
   * will allow editing the Item
   * @return true if this property is set, false otherwise
   * @see #setAllowDoubleClickToEdit
   */
  public boolean getAllowDoubleClickToEdit () {
    return allowDoubleClickToEdit;
  }

  /**
   * Determine if double-click should allow editing the Item
   * or not
   * @allowEdit true to set this property and allow editing, false otherwise
   */
  public void setAllowDoubleClickToEdit (boolean allowEdit) {
    allowDoubleClickToEdit = allowEdit;
  }

  protected MarkerElement createMarkerElement(int locn, int x, int y){
    return new MarkerElement(locn, x, y);
  }

  Component[] getSelectionMarkers(){
    if (currentSelection != null)
      return currentSelection.getSelectionMarkers();
    return null;
  }

  public void shrinkWrap () throws G2AccessException {
    workspace.shrinkWrap ();
    shrinkWrapDocument();
  }

  public void shrinkWrapDocument() {
    //shrink wrap the document around it
    Component parent = getParent();
    while (parent != null) {
      //note the modularity problem here: something that uses
      //WorkspaceView should not be required to depend upon
      //WorkspaceDocument, which is in shell.  What we're trying to
      //accomplish is having the shrinkwrap menu item affect the
      //document; in a better solution, we would need some kind of
      //listener within WorkspaceDocument, and some way for it to be
      //notified of changes to WorkspaceView.
      if (parent instanceof WorkspaceDocument) {
	((WorkspaceDocument)parent).shrinkWrapDocument ();
	break; //this breaks out of the while loop
      }
      parent = parent.getParent();
    }
  }
}

class WorkspaceSelection implements java.io.Serializable {
  private Vector currentSelection = new Vector (),
                 locations = new Vector(),
		 frames = new Vector (),
		 ghosts = new Vector (),
		 markers = new Vector ();
  private ConnectionDraggingGhost connectionDraggingGhost;
  private WorkspaceView wksp;
  private Object lock = new Object();
  
  WorkspaceSelection (WorkspaceView wksp) {
    this.wksp = wksp;
  }

  int size () {
    return currentSelection.size ();
  }

  void ensureCapacity (int newSize) {
    wksp.debug ("ensureCapacity (" + newSize + ") called");
    synchronized(lock) {
      currentSelection.ensureCapacity (newSize);
      locations.ensureCapacity(newSize);
      frames.ensureCapacity (newSize);
      ghosts.ensureCapacity (newSize);
      markers.ensureCapacity (newSize);
    }
  }

  public int indexOf (WorkspaceElement elt) {
    synchronized(lock) {
      return currentSelection.indexOf (elt);
    }
  }

  public WorkspaceElement[] getSelection () {
    synchronized(lock) {
      int numSelected = currentSelection.size ();
      WorkspaceElement[] selection = new WorkspaceElement[numSelected];
      currentSelection.copyInto (selection);
      return selection;
    }
  }

  Point[] getInitialLocations() {
    synchronized(lock) {
    int count = locations.size ();
    Point[] locs = new Point[count];
    locations.copyInto (locs);
    return locs;
    }
  }

  void resetInitialLocations()
  throws FatalWorkspaceException
  {
    synchronized(lock) {    
      locations.removeAllElements();
      for (Enumeration e = currentSelection.elements();
	   e.hasMoreElements();) {
	WorkspaceElement elt = (WorkspaceElement)e.nextElement();
	try {
	  Item item = elt.getItem();
	  
	  //Possible deadlock on the item data caused by the following two
	  //lines of code.
	  int x = item.getItemXPosition();
	  int y = item.getItemYPosition();
	  locations.addElement(new Point(x,y));
	} catch (G2AccessException g2ae) {
	  wksp.handleG2AccessException(g2ae, WorkspaceView.ANOMALY);//bad wksp item
	}
      }
    }
  }

  public WorkspaceElement elementAt (int index) {
    synchronized(lock) {    
      return (WorkspaceElement)currentSelection.elementAt (index);
    }
  }

  void setElementAt (WorkspaceElement elt, int index)
       throws FatalWorkspaceException
  {
    synchronized(lock) {    
      if (index != currentSelection.size ())
	throw new RuntimeException ("Tell vkp his assumptions were violated");
      currentSelection.addElement (elt);
      try {
	Item item = elt.getItem();
	int x = item.getItemXPosition();
	int y = item.getItemYPosition();
	locations.addElement(new Point(x,y));
      } catch (G2AccessException g2ae) {
	wksp.handleG2AccessException(g2ae, WorkspaceView.ANOMALY);//bad wksp item
      }
      SelectionFrame sf = wksp.getSelectionFrame(elt);
      if (wksp.isDisplaySelectionFrames())
	sf.display (wksp);
      frames.addElement (sf);
    }
  }

  void removeElementAt (int index) {
    synchronized(lock) {    
      currentSelection.removeElementAt (index);
      SelectionFrame sframe = (SelectionFrame)frames.elementAt (index);
      if (wksp.isDisplaySelectionFrames())
	sframe.dispose (wksp);
      frames.removeElementAt (index);
      locations.removeElementAt(index);
    }
  }

  void removeElement (WorkspaceElement elt) {
    synchronized(lock) {
      int eltIndex = currentSelection.indexOf (elt);
      removeElementAt (eltIndex);
    }
  }

  void elementChanged (WorkspaceView wkspView, WorkspaceElement elt) {
    synchronized(lock) {    
      for (int i=0; i<currentSelection.size (); i++) {
	if (elt == currentSelection.elementAt (i))
	  frames.setElementAt (((SelectionFrame)frames.elementAt(i)).elementChanged (wkspView, elt), i);
      }
    }
  }

  ConnectionDraggingGhost getConnectionGhost()
  {
    return connectionDraggingGhost;
  }
  
  void setConnectionGhost(ConnectionDraggingGhost cdg)
  {
    if (connectionDraggingGhost != null)
      connectionDraggingGhost.dispose(wksp);
    if (cdg != null)
      cdg.display(wksp);
    connectionDraggingGhost = cdg;
  }
  
  void moveConnectionGhost (int deltaX, int deltaY) {
    if (connectionDraggingGhost != null)
      connectionDraggingGhost.shift (wksp, deltaX, deltaY);
  }
  
  void addGhosts () {
    synchronized(lock) {    
      for (int i=0; i<currentSelection.size (); i++) {
	WorkspaceElement wkspElt = (WorkspaceElement)currentSelection.elementAt (i);
	if (wkspElt instanceof ConnectionElement) {
	  //System.out.println("SHOULDN'T BE ADDING CONNECTION GHOSTS THIS WAY");
	} else {
	  DraggingGhost ghost = wkspElt.getDraggingGhost ();
	  ghosts.addElement (ghost);
	  ghost.display (wksp);
	}
      }
    }
  }

  void addGhosts (MarkerElement marker, int currentX, int currentY) {
    synchronized(lock) {    
      WorkspaceElement orig = getWorkspaceElementFromMarker(marker);
      Rectangle origBounds = ((DrawElement)orig).getExactBounds()[0];
      int origWidth = origBounds.width;
      int origHeight = origBounds.height;
      Rectangle origResized = wksp.getResizingBounds (marker, currentX, currentY);
      int origResizedWidth = origResized.width, origResizedHeight = origResized.height;
      int deltaX = origResized.x - origBounds.x, deltaY = origResized.y - origBounds.y;
      for (int i=0; i<currentSelection.size (); i++) {
	WorkspaceElement elt = (WorkspaceElement)(currentSelection.elementAt (i));
	Rectangle bnds = ((DrawElement)elt).getExactBounds()[0];
	int newWidth = (bnds.width*origResizedWidth)/origWidth;
	int newHeight = (bnds.height*origResizedHeight)/origHeight;
	int deltaWidth = newWidth - bnds.width;
	int deltaHeight = newHeight - bnds.height;
	int newX = bnds.x, newY = bnds.y;
	if (deltaX != 0) 
	  newX -= deltaWidth;
	if (deltaY != 0)
	  newY -= deltaHeight;
	DraggingGhost ghost  = elt.getDraggingGhost (newX, newY, newWidth, newHeight);
	ghosts.addElement (ghost);
	ghost.display (wksp);
      }
    }
  }

  Vector getGhosts() {
    return ghosts;
  }
  
  void moveGhosts (int deltaX, int deltaY) {
    synchronized(lock) {
      for (int i=0; i<ghosts.size (); i++) {
	DraggingGhost ghost = (DraggingGhost) (ghosts.elementAt (i));
	ghost.shift (wksp, deltaX, deltaY);
      }
    }
  }

  void resizeGhosts (MarkerElement marker, int currentX, int currentY) {
    //    if (marker.location < 3 || marker.location > 5)
    //throw new RuntimeException ("Cannot resize from that corner!");
    removeGhosts ();
    addGhosts (marker, currentX, currentY);
  }

  void removeGhosts () {
    synchronized(lock) {    
      for (int i=ghosts.size () - 1; i>=0; i--) {
	DraggingGhost ghost = (DraggingGhost) (ghosts.elementAt (i));
	ghost.dispose (wksp);
	ghosts.removeElementAt (i);
      }
    }
  }

  WorkspaceElement getWorkspaceElementFromMarker (MarkerElement marker) {
    synchronized(lock) {    
      int locationIndex = marker.location;
      for (int i=0; i<currentSelection.size(); i++)
	if (((SelectionFrame)(frames.elementAt(i))).getMarkers().elements[locationIndex] == marker)
	  return (WorkspaceElement)currentSelection.elementAt(i);
      return null;
    }
  }

  Component[] getSelectionMarkers(){
    synchronized(lock) {    
      Component[] markers = new Component[currentSelection.size()*8];
      for (int i=0; i<frames.size(); i++){
	SelectionFrame frame = (SelectionFrame)frames.elementAt(i);
	Component[] markerSet = frame.getMarkers().elements;
	for (int j=0; j<markerSet.length; j++)
	  markers[j+i*8] = markerSet[j];
      }
      return markers;
    }
  }

}


class SelectionFrame {
  
  Component[] elements;
  private Color selectionFrameColor = Color.black;
  private int left, top, width, height;
  private SelectionMarkers markers;
  
  SelectionFrame (WorkspaceElement elt, WorkspaceView view) {
    
    Rectangle[] eltExactBounds = ((DrawElement)elt).getExactBounds();
    int length = eltExactBounds.length;
    elements = new Component[length*4];
    for (int i=0; i<length;i++) {
      Rectangle eltBounds = eltExactBounds[i];
      left = eltBounds.x; top = eltBounds.y;
      width = eltBounds.width; height = eltBounds.height;
      left -=1; top -=1; width +=1; height +=1;
      int offset = i*4;
      elements[offset] = new LineElement (selectionFrameColor, left, top, left+width, top);
      elements[offset+1] = new LineElement (selectionFrameColor, left+width, top, left+width, top+height);
      elements[offset+2] = new LineElement (selectionFrameColor, left+width, top+height, left, top+height);
      elements[offset+3] = new LineElement (selectionFrameColor, left, top+height, left, top);
    }
    markers = new SelectionMarkers (elt, view);
  }

  void display (WorkspaceView wksp) {
    int length = elements.length;
    for (int i=0;i<length;i++) {
      wksp.addElement (elements[i]);
    }
    markers.display (wksp);
  }

  void dispose (WorkspaceView wksp) {
    int length = elements.length;
    for (int i=0;i<length;i++) {
      wksp.removeElement (elements[i]);
    }
    markers.dispose (wksp);
  }

  SelectionFrame elementChanged (WorkspaceView wkspView, WorkspaceElement elt) {
    Rectangle eltBounds = ((DrawElement)elt).getExactBounds()[0];
    int bleft = eltBounds.x, btop = eltBounds.y,
      bwidth = eltBounds.width, bheight = eltBounds.height;
    bleft -=1; btop -=1; bwidth +=1; bheight +=1;
    if ((bwidth == width) && (bheight == height))
      return elementMoved (wkspView, bleft - left, btop - top);
    else
      return elementResized (wkspView, elt);
  }

  SelectionFrame elementMoved (WorkspaceView wksp, int deltaX, int deltaY) {
    left += deltaX; top += deltaY;
    int length = elements.length;
    for (int i=0;i<length;i++) {
      wksp.shiftElement(elements[i],deltaX, deltaY);
    }
    Rectangle[] bnds = {new Rectangle (left, top, width, height)};
    wksp.invalidate (bnds);
    markers.elementMoved (wksp, deltaX, deltaY);
    return this;
  }

  SelectionFrame elementResized (WorkspaceView wksp, WorkspaceElement elt) {
    dispose (wksp);
    SelectionFrame newFrame = new SelectionFrame (elt, wksp);
    newFrame.display (wksp);
    return newFrame;
  }

  SelectionMarkers getMarkers () {
    return markers;
  }

}




class SelectionMarkers {
  private static final int markerWidth = 6;

  Component[] elements;
  
  SelectionMarkers (WorkspaceElement elt, WorkspaceView view) {
    Rectangle[] eltExactBounds = ((DrawElement)elt).getExactBounds();
    int length = eltExactBounds.length;
    elements = new Component[length*8];
    for (int i=0;i<length;i++) {
      Rectangle eltBounds = eltExactBounds[i];
      int left = eltBounds.x, top = eltBounds.y,
	width = eltBounds.width, height = eltBounds.height;
      left -=1; top -=1; width +=1; height +=1;
      int offset = i*8;
      elements[offset] = view.createMarkerElement (0, left, top);
      elements[offset+1] = view.createMarkerElement (1, left + (width >> 1), top);
      elements[offset+2] = view.createMarkerElement (2, left + width, top);
      elements[offset+3] = view.createMarkerElement (3, left + width, top + (height >> 1));
      elements[offset+4] = view.createMarkerElement (4, left + width, top + height);
      elements[offset+5] = view.createMarkerElement (5, left + (width >> 1), top + height);
      elements[offset+6] = view.createMarkerElement (6, left, top + height);
      elements[offset+7] = view.createMarkerElement (7, left, top + (height >> 1));
    }
  }

  
  void display (WorkspaceView wksp) {
    for (int i=0; i<elements.length; i++)
      wksp.addElement (elements[i]);
  }

  void dispose (WorkspaceView wksp) {
    for (int i=0; i<elements.length; i++)
      wksp.removeElement (elements[i]);
  }

  void elementMoved (WorkspaceView wksp, int deltaX, int deltaY) {
    for (int i=0; i<elements.length; i++)
      wksp.shiftElement (elements[i], deltaX, deltaY);
  }
}
