package com.gensym.beaneditor;

import java.awt.Color;
import java.awt.Component;
import java.awt.Graphics;
import java.awt.Dimension;
import java.awt.Point;
import java.awt.Cursor;
import java.awt.Rectangle;
import java.awt.event.ComponentListener;
import java.awt.event.ComponentEvent;
import com.gensym.draw.*;
import java.util.Vector;
import java.beans.BeanInfo;
import java.beans.Introspector;
import java.beans.IntrospectionException;
import java.beans.EventSetDescriptor;
import java.beans.MethodDescriptor;
import java.lang.reflect.*;
import java.io.*;
import java.applet.*;
import java.net.URL;
import java.awt.Image;
import com.gensym.dlgruntime.PageLayout;
import com.gensym.dlgruntime.DefaultDialogReader;
import com.gensym.beansruntime.HookupDefinition;
import com.gensym.beansruntime.G2ClassLoader;
import com.gensym.beansruntime.BeanInputStream;

public class BeanCanvas extends PersistentCanvas implements ComponentListener
{
  private String newBeanClass = null;
  private Vector eventInfoTable = new Vector();
  private Vector beanClasses = new Vector();
  private Dimension containerSize = new Dimension (0, 0);
  private boolean containerSizeSet = false;
  private Vector jars;
  boolean containsBadBeans = false;

  public BeanCanvas(){
    addComponentListener(this);
  }

  void setNewBeanClass(String clazz)
  {
    newBeanClass = clazz;
    if (clazz == null)
      setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
    else
      setCursor(new Cursor(Cursor.CROSSHAIR_CURSOR));
  }

  boolean isNewBeanSelected()
  {
    if (newBeanClass != null && !newBeanClass.equals("None"))
      return true;
    else
      return false;
  }

  String getNewBeanClass()
  {
    return newBeanClass;
  }

  void setDebuggingEnabled(boolean b)
  {
    Component[] elements =  getComponents();
    int i, len = elements.length;
    
    for (i = len-1 ; i >= 0  ; i--)
      if (elements[i] instanceof Wrapper)
	((Wrapper)elements[i]).setDebuggingEnabled(b);
  }

  void setComponentAdapationEnabled(boolean enabled)
  {
    Component[] elements =  getComponents();
    int i, len = elements.length;
    
    for (i = len-1 ; i >= 0  ; i--)
      if (elements[i] instanceof Wrapper)
	{
	  Wrapper wrapper = (Wrapper) elements[i];
	  ComponentBeanAdapter adapter = wrapper.getComponentBeanAdapter();
	  if (adapter == null)
	    continue;
	  else if (enabled)
	    adapter.addListeners();
	  else
	    adapter.removeListeners();
	}
  }

  void updateForScroll(int shiftX, int shiftY)
  {
    Component[] elements = getComponents();
    for (int i = 0; i < elements.length; i++)
      if (elements[i] instanceof Wrapper)
	((Wrapper)elements[i]).updateForScroll(shiftX,shiftY);
  }

  void setContainerSize(int width, int height)
  {
    if (width < 10) width = 10;
    if (height < 10) height = 10;
    containerSize = new Dimension (width, height);
    if (containerSizeSet)
      removeSizingWidgetry();
    setupSizingWidgetry(width,height);
    containerSizeSet = true;
  }

  Dimension getContainerSize()
  {
    return containerSize;
  }

  boolean containsNonTrivialComponents()
  {
    Component[] elements = getComponents();
    
    for (int i = 0; i<elements.length; i++)
      if (!(elements[i] instanceof SizingWidget ||
	    elements[i] instanceof LineElement))
	return true;

    return false;
  }

  private void setupSizingWidgetry(int width, int height)
  {
    Color c = Preferences.currentPreferences.sizingWidgetLineColor;
    addElement(new SizingWidget(0,0,Directions.TOP_LEFT));
    addElement(new SizingWidget(width,0,Directions.TOP_RIGHT));
    addElement(new SizingWidget(0,height,Directions.BOTTOM_LEFT));   
    addElement(new SizingWidget(width,height,Directions.BOTTOM_RIGHT));
    addElement(new LineElement(c,0,0,width,0));
    addElement(new LineElement(c,0,0,0,height));
    addElement(new LineElement(c,width,0,width,height));
    addElement(new LineElement(c,0,height,width,height));
  }

  private void removeSizingWidgetry()
  {
    Component[] elements = getComponents();
    Vector elementsToDelete = new Vector();
    int i,size;

    for (i = 0; i < elements.length; i++)
      if ((elements[i] instanceof SizingWidget) ||
	  (elements[i] instanceof LineElement))
	elementsToDelete.addElement(elements[i]);
    size = elementsToDelete.size();
    for (i = 0; i < size ; i++)
      removeElement((Component)elementsToDelete.elementAt(i));
  }
  
  protected Wrapper getWrapper(Object bean)
  {
    Component[] elements =  getComponents();
    int i, len = elements.length;
    
    for (i = len-1 ; i >= 0  ; i--)
      if (elements[i] instanceof Wrapper)
	{
	  Wrapper wrapper = (Wrapper) elements[i];
	  if (wrapper.bean == bean)
	    return wrapper;
	}
    return null;
  }

  void registerBeanClass(Class clazz)
  {
    if (beanClasses.indexOf(clazz) == -1) // not yet registered
      {
	try 
	  {
	    BeanInfo beanInfo = Introspector.getBeanInfo(clazz);
	    
	    EventSetDescriptor[] eventSetDescriptors 
	      = beanInfo.getEventSetDescriptors();
	    
	    int i, len = eventSetDescriptors.length;
	    for (i=0; i<len ; i++)
	      {
		EventSetDescriptor esd = eventSetDescriptors[i];

		MethodDescriptor[] methodDescriptors 
		  = esd.getListenerMethodDescriptors();
		Method[] methods = esd.getListenerMethods();
		
		for (int j = 0 ; j<methodDescriptors.length ; j++)
		  {
		    MethodDescriptor mDesc = methodDescriptors[j];
		    Method method = methods[j];
		    EventInfo eventInfo
		      = new EventInfo (mDesc.getName(), clazz, method, mDesc, null);
		    eventInfoTable.addElement(eventInfo);
		  }
	      }
	    beanClasses.addElement(clazz);
	  } catch (IntrospectionException exception)
	    { 
	      exception.printStackTrace();
	    }
      }
  }

  EventInfo getEventInfo(String name, Class clazz)
  {
    int i, size = eventInfoTable.size();
    
    for (i = 0; i<size; i++)
      {
	EventInfo eventInfo = (EventInfo)eventInfoTable.elementAt(i);
	
	if (eventInfo.name.equals(name) && eventInfo.clazz.equals(clazz))
	  {
	    return eventInfo;
	  }
      }

    //return null;
    return  new EventInfo (name, clazz, null, null, null);
  }

  void save(String filename, String directory)
  {
    if (filename != null && directory != null)
      {
	try {
	  File file = new File(directory, filename);
	  FileOutputStream fos = new FileOutputStream(file);
	  save(fos);
	} catch (Exception e)
	  {
	    System.out.println("beaneditor save failed to file: "+filename+
			       " in "+directory);
	    e.printStackTrace();
	  }
      }  
  }

  void save(OutputStream os)
  {
    try
      {    
	ObjectOutputStream oos = new ObjectOutputStream(os);
	saveContents(oos);
	oos.close();
	os.close();
      }
    catch (java.io.IOException ex)
      {
	System.out.println("beaneditor save failed due to IO problems");
	ex.printStackTrace();
      }
  }

  byte[] serializeToBytes()
       throws java.io.IOException
  {
    ByteArrayOutputStream baos = new ByteArrayOutputStream();
    ObjectOutputStream oos = new ObjectOutputStream(baos);
    saveContents(oos);
    byte[] serializedData = baos.toByteArray();
    oos.close();
    baos.close();
    return serializedData;
  }

  void saveContents(ObjectOutputStream oos)
       throws IOException
  {
    Vector 
      hookups = HookupFactory.getHookups(),
      beans = new Vector(),
      jarNames = new Vector();
    int i = 0;
    try
      {
	setDebuggingEnabled(false);
	Component[] components = getComponents();
	
	for (i = 0; i<components.length ; i++)
	  if (components[i] instanceof Wrapper)
	    beans.addElement(((Wrapper)components[i]).getBean());
	Object[] beanArray = new Object[beans.size()];
	beans.copyInto(beanArray);
	PageLayout page = new PageLayout(containerSize.width,
					 containerSize.height,
					 beanArray);

	String[] loadedJars = G2JarLoader.getLoadedJars();
	for (int j=0; j<loadedJars.length; j++)
	  jarNames.addElement(loadedJars[j]);
	if (containsBadBeans && jars!=null){
	  for (int n=0; n<jars.size(); n++){
	    Object jarName = jars.elementAt(n);
	    if (!jarNames.contains(jarName))
	      jarNames.addElement(jarName);
	  }
	}
	oos.writeObject(new Integer(DefaultDialogReader.defaultDialogFormatVersion));
	oos.writeObject(jarNames);
	oos.writeObject(hookups);
	oos.writeObject(page);
	oos.writeObject(components);
      }
    finally
      {
	setDebuggingEnabled(true);
      }
  }

  void loadContents(BeanInputStream ois)
       throws IOException, ClassNotFoundException
  {
    containsBadBeans = false;
    Object firstObject = ois.readObject();
    Vector hookups, jars;
    if (firstObject instanceof Integer){ // i.e. a protocol version
      Integer version = (Integer)firstObject;
      if (version.intValue() == 2){
	jars = (Vector)ois.readObject();
	this.jars = jars;
	if (jars != null)
	  for (int i=0; i<jars.size(); i++)
	    ((ComponentEditor)ComponentEditor.getApplication()).loadJar((String)jars.elementAt(i), false);
      }
      hookups = (Vector)ois.readObject();
    }
    else
      hookups = (Vector)firstObject;
    int size = hookups.size();
    
    for (int h=0; h < size; h++)
      {
	HookupDefinition def = (HookupDefinition)hookups.elementAt(h);
	Class c = (G2ClassLoader.ourLoader).loadClass(def.name, def.bytes);
	HookupFactory.addHookup (def);
      }
    
    PageLayout page = (PageLayout)ois.readObject();
    setContainerSize(page.getWidth(), page.getHeight());
    
    Object[] components = (Object[]) ois.readObject();
    Vector objectVector = new Vector();
    
    for (int i=0; i < components.length; i++) 
      {      
	Object object = components[i];
	if (object instanceof Wrapper ||
	    object instanceof Port    ||
	    object instanceof EventConnection ||
	    object instanceof LooseEnd)
	  {
	    if (object instanceof Wrapper &&
		((Wrapper)object).bean != null)
	      {
		Object bean = ((Wrapper)object).bean;
		registerBeanClass (bean.getClass());
		if (bean instanceof Applet)
		  {
		    // The applet stub is important in order
		    // for the bean to find it's resources
		    assignAppletStub((Applet) bean, G2ClassLoader.ourLoader,
				     bean.getClass());
		  }
	      }
	    objectVector.addElement(object);                      
	  }
      }
    BeanEditTool tool = (BeanEditTool) getEventHandler();
    tool.addElements(objectVector);
    setDebuggingEnabled(true);
  }

  // Guess a codebase for a class in a classloader
  
  private void assignAppletStub(Applet applet, ClassLoader cl, Class k)
  {
    String className = k.getName();
    String resourceName = className.replace('.','/').concat(".class");
    
    // This code is identical to portions of Beans.intantiate()
    URL objectUrl = null;
    URL codeBase = null;
    URL docBase = null;
    
    // Now get the URL correponding to the resource name.
    if (cl == null) {
      objectUrl = ClassLoader.getSystemResource(resourceName);
    } else {
      objectUrl = cl.getResource(resourceName);
    }
    
    // If we found a URL, we try to locate the docbase by taking
    // of the final path name component, and the code base by taking
    // of the complete resourceName.
    // So if we had a resourceName of "a/b/c.class" and we got an
    // objectURL of "file://bert/classes/a/b/c.class" then we would
    // want to set the codebase to "file://bert/classes/" and the
    // docbase to "file://bert/classes/a/b/"
    
    if (objectUrl != null) {
      String s = objectUrl.toExternalForm();
      if (s.endsWith(resourceName)) {
	try{ 
	  int ix = s.length() - resourceName.length();
	  codeBase = new URL(s.substring(0,ix));
	  docBase = codeBase;
	  ix = s.lastIndexOf('/');
	  if (ix >= 0) {
	    docBase = new URL(s.substring(0,ix+1));
	  }
	} catch (Exception ex) {
	  docBase = codeBase = null;
	}
      }
    }
    
    // Setup a default context and stub.
    G2AppletContext context = new G2AppletContext(applet);
    G2AppletStub stub = new G2AppletStub(applet, context, codeBase, docBase);
    applet.setStub(stub);
    
    // object is always deserialized
    stub.active = true;
  }
  
  
  void hideEvents()
  {
    Component[] elements = getComponents();

    for (int i = 0; i < elements.length; i++)
      {
	if (elements[i] instanceof Port ||
	    elements[i] instanceof EventConnection ||
	    elements[i] instanceof Wrapper)
	  elements[i].setVisible(false);
      }
  }

  void showEvents()
  {
    Component[] elements = getComponents();

    for (int i = 0; i < elements.length; i++)
      {
	if (elements[i] instanceof Port ||
	    elements[i] instanceof EventConnection ||
	    elements[i] instanceof Wrapper)
	  elements[i].setVisible(true);
      }
  }

  @Override
  public Component findElement (int mouse_x, int mouse_y, boolean allowCanvas){
    Component c = super.findElement(mouse_x, mouse_y, allowCanvas);
    if ((c != null) &&(!(c.getPeer() instanceof java.awt.peer.LightweightPeer))){
      Point offset = getScrollOffset();
      c = super.findElement(mouse_x + offset.x, mouse_y + offset.y, allowCanvas);
      if ((c != null) &&(!(c.getPeer() instanceof java.awt.peer.LightweightPeer)))
	return c;
      else
	return null;
    }
    else return c;
  }

  @Override
  public void paintBackground (Graphics g)
  {
    super.paintBackground(g);

    Point offset = getScrollOffset();
    g.setColor(Preferences.currentPreferences.containerBackgroundColor);
    g.fillRect(offset.x,offset.y,containerSize.width,containerSize.height);
    
    // testing hax:
    if (false)
      {
	g.setColor(Color.blue);
	for (int i = 0; i<11; i++)
	  {
	    g.fillRect(0,i*50,2,2);
	    g.fillRect(i*50,0,2,2);
	  }
      }
  }

  @Override
  public void update (Graphics g)
  {
    paint(g);
  }

  @Override
  public synchronized void repaint (int x, int y, int width, int height)
  {
    super.repaint (x, y, width, height);
  }

  Vector areAllLoadedBeansFromJars(){
    Vector badBeans = null;
    Component[] elements = getComponents();
    for (int i=0; i<elements.length; i++){
      if (elements[i] instanceof Wrapper){
	Wrapper wrapper = (Wrapper)elements[i];
	if (wrapper.bean.getClass().getClassLoader() == null){
	  if (badBeans == null) badBeans = new Vector();
	  badBeans.addElement(wrapper.bean.getClass().getName());
	}
      }
    }
    return badBeans;
  }

  Dimension getMinimumLogicalSize(){
    int width = -123456789;
    int height = -123456789;
    Component[] elements = getComponents();
    for (int i=0; i<elements.length; i++){
      Rectangle bounds = elements[i].getBounds();
      if (bounds.x + bounds.width > width)
	width = bounds.x + bounds.width;
      if (bounds.y + bounds.height > height)
	height = bounds.y + bounds.height;
    }
    if (width == -123456789) return null;
    return new Dimension(width, height);
  }

  void setMinimumLogicalSize(){
    Dimension size = getMinimumLogicalSize();
    Rectangle logicalBounds = getLogicalBounds();
    if (size.width > logicalBounds.width) growLogical(size.width - logicalBounds.width, true, false);
    if (size.height > logicalBounds.height) growLogical(size.height - logicalBounds.height, false, false);
  }

  //ComponentListener Interface
  @Override
  public void componentHidden(ComponentEvent e){}
  @Override
  public void componentShown(ComponentEvent e){}
  @Override
  public void componentResized(ComponentEvent e){
    Rectangle logicalBounds = getLogicalBounds();
    Dimension d = getSize();
    if (d.width > logicalBounds.width)
      growLogical(d.width - logicalBounds.width, true, false);
    if (d.height > logicalBounds.height)
      growLogical(d.height - logicalBounds.height, false, false);
  }
  @Override
  public void componentMoved(ComponentEvent e){}

  void repaintIt(){
    super.repaintCanvas();
  }

  void repaintIt (int x, int y, int width, int height)
  {
    super.repaintCanvas (x, y, width, height);
  }
 
}

/**
 * Package private support class.  This provides a default AppletContext
 * for beans which are applets.
 */
class G2AppletContext implements AppletContext
{
  Applet target;
  java.util.Hashtable imageCache = new java.util.Hashtable();
  
  G2AppletContext(Applet target)
  {
    this.target = target;
  }
  
  @Override
  public AudioClip getAudioClip(URL url)
  {
    // We don't currently support audio clips in the Beans.instantiate
    // applet context, unless by some luck there exists a URL content
    // class that can generate an AudioClip from the audio URL.
    try
      {
	return (AudioClip) url.getContent();
      }
    catch (Exception ex)
      {
	return null;
      }
  }
  
  @Override
  public synchronized Image getImage(URL url)
  {
    Object o = imageCache.get(url);
    
    if (o != null)
      {
	return (Image)o;
      }
    
    try
      {
	o = url.getContent();
	if (o == null)
          {
	    return null;
	  }
	
	if (o instanceof Image)
          {
	    imageCache.put(url, o);
	    return (Image) o;
	  }
	
	// Otherwise it must be an ImageProducer.
	Image img = target.createImage((java.awt.image.ImageProducer)o);
	imageCache.put(url, img);
	return img;
	
      }
    catch (Exception ex)
      {
	return null;
      }
  }
  
  @Override
  public Applet getApplet(String name)
  {
    return null;
  }
  
  @Override
  public java.util.Enumeration getApplets()
  {
    java.util.Vector applets = new java.util.Vector();
    applets.addElement(target);
    return applets.elements();	
  }
  
  @Override
  public void showDocument(URL url)
  {
    // We do nothing.
  }
  
  @Override
  public void showDocument(URL url, String target)
  {
    // We do nothing.
  }
  
  @Override
  public void showStatus(String status)
  {
    // We do nothing.
  }

  @Override
  public java.util.Iterator getStreamKeys()
  {
    return null;
  }

  @Override
  public InputStream getStream(String key)
  {
    return null;
  }

  @Override
  public void setStream(String key, InputStream stream)
  {
    // We do nothing.
  }
}


/**
 * Package private support class.  This provides an AppletStub
 * for beans which are applets.
 */
class G2AppletStub implements AppletStub
{
  transient boolean active;
  transient Applet target;
  transient AppletContext context;
  transient URL codeBase;
  transient URL docBase;
  
  G2AppletStub(Applet target,
	       AppletContext context, URL codeBase, 
	       URL docBase)
  {
    this.target   = target;
    this.context  = context;
    this.codeBase = codeBase;
    this.docBase  = docBase;
  }
  
  @Override
  public boolean isActive()
  {
    return active;
  }
  
  @Override
  public URL getDocumentBase()
  {
    // use the root directory of the applet's class-loader
    return docBase;
  }
  
  @Override
  public URL getCodeBase()
  {
    // use the directory where we found the class or serialized object.
    return codeBase;
  }
  
  @Override
  public String getParameter(String name)
  {
    return null;
  }
  
  @Override
  public AppletContext getAppletContext()
  {
    return context;
  }
  
  @Override
  public void appletResize(int width, int height)
  {
    // we do nothing.
  }
}
