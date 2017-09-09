package com.gensym.beaneditor;

import java.awt.*;
import java.beans.EventSetDescriptor;
import java.beans.Introspector;
import java.util.Vector;
import com.gensym.draw.*;
import java.lang.reflect.Method;
import com.gensym.message.Trace;
import com.gensym.util.Structure;
import com.gensym.beansruntime.Hookup;
import com.gensym.beansruntime.HookupDefinition;
import com.gensym.beansruntime.G2ClassLoader;

public class Port extends BasicDrawElement
{

  /*
   * Allow serialization
   */
  static final long serialVersionUID = -2086793336395656669L; 

  Wrapper wrapper;

  private boolean isInput = false;
  private int side = Directions.LEFT;
  private Color color;
  private Rectangle[] bounds;
  private Arrow arrow;
  private transient EventInfo eventInfo;
  private String eventName;  // allows re-establishment of above pointer
  private String sourceCode = null;
  private int sourceSyntax = -1;
  private EventConnection connection;
  protected static int looseEndSize = 12;
  protected static int defaultStubLength = 30;
  private String listenerType = null;
  private String removeListenerMethod = null;
  private Hookup hookup = null;
  private String methodName; //for tool tip info
  private Structure info; // extra info storage

  public Port (Wrapper wrapper, EventInfo eventInfo,
	       Color color, boolean isInput,
	       int x, int y, int w, int h)
  {
    bounds = new Rectangle[1];
    bounds[0] = new Rectangle(x,y,w,h);
    setLocation(x,y);
    setSize(w,h);
    this.wrapper = wrapper;
    this.eventInfo = eventInfo;
    if (eventInfo != null)
      eventName = eventInfo.name;
    this.isInput = isInput;
    this.color = color;
    int insetX = 2;
    int insetY = 2;
    wrapper.addPort(this);
    arrow = new Arrow(insetX, insetY , w - (insetX * 2),
    	      h - (insetY * 2), color, Color.black,
    	      Directions.LEFT);
  }

  // only works on output ports
  // a "link" is the combination of an output Port a connection
  // and either a inputPort or LooseEnd
  void removeLink() 
  {
    if (!isInput)
      {
	this.wrapper.removePort(this);
	canvas.removeElement(this);
	canvas.removeElement(connection);
	if (connection.output instanceof Port)
	  { 
	    Port outputPort = (Port) connection.output;
	    outputPort.wrapper.removePort(outputPort);
	  }
   
	// unregister the listener
	removeHookup();
	canvas.removeElement(connection.output);
      } 
  }

  private void removeHookup()
  {
    if (hookup != null && removeListenerMethod != null)
      {
	try
	  {
	    Object bean = wrapper.getBean();
	    // System.out.println("lmeth "+removeListenerMethod+
	    //	       " lType "+listenerType);
	    Class beanClass = bean.getClass();
	    ClassLoader beanClassLoader = beanClass.getClassLoader();
	    Class argSystemClass = Class.forName(listenerType);
	    // System.out.println("bean loader "+beanClassLoader);
	    // System.out.println("arg loader "+argSystemClass.getClassLoader());
	    Method method = null;
	    try {
	      method = beanClass.getMethod(removeListenerMethod, 
					   new Class[]{argSystemClass});
	    } catch (NoSuchMethodException nsme)
	      {
		// System.out.println("caught nsme :"+nsme);
		if (beanClassLoader != null &&
		    beanClassLoader instanceof G2ClassLoader)
		  {
		    Class argSiblingClass 
		      = ((G2ClassLoader)beanClassLoader).findClass(listenerType);
		    // System.out.println("argSiblingClass "+argSiblingClass);
		    method = beanClass.getMethod(removeListenerMethod, 
						 new Class[]{argSiblingClass});
		  }
	      }
	    method.invoke(bean, new Object[]{hookup});
	    HookupFactory.removeHookupDefinitionForClass(hookup.getClass());
	    hookup = null; // drop that pointer
	  }
	catch (Exception ex)
	  {
	    Trace.exception (ex, null);
	  }
      } 
  }

  void installNewHookup(Object newHookup, EventSetDescriptor esd, int syntax,
			Object sourceBean)
  {
    try {
      Object hookupArgs[] = new Object[1];
      hookupArgs[0] = newHookup;
      
      (esd.getAddListenerMethod()).invoke(sourceBean, hookupArgs);

      // Now setup the port with the hookup info (for later removal)
      setHookup(newHookup);
      setSourceCode(HookupFactory.getHookupClassSource(newHookup.getClass()),
		    syntax);
      setListenerType(esd.getListenerType().getName());
      setRemoveListenerMethod((esd.getRemoveListenerMethod()).getName());
    } catch (Exception ex) {
      Trace.exception (ex, null);
    }
  }


  void editExistingHookup()
  {
    if (hookup == null)
      return;
      
    System.out.println("edit existing hookup with "+eventName+" and listener "+
		       listenerType);
    Object sourceBean = wrapper.bean;
    Object targetBean = ((Port)connection.output).wrapper.bean;
    EventSetDescriptor esd = null;
    Method listenerMethod = null;
    try {
      EventSetDescriptor[] eventSetDescriptors = Introspector.getBeanInfo
	(sourceBean.getClass()).getEventSetDescriptors();
      for (int i=0; i < eventSetDescriptors.length ; i++) {
	esd = eventSetDescriptors[i];
	Method[] methods = esd.getListenerMethods();
	boolean found = false;
	for (int j = 0; j < methods.length ; j++)
	  if (methods[j].getName().equals(eventName)) // should have been called method
	    {
	      listenerMethod = methods[j];
	      // System.out.println("method for "+listenerType+" is "+listenerMethod);
	      found = true;
	      break;
	    }
	if (found) break;
      }
    } catch (Exception e) {
      Trace.exception (e, null);
    }

    Object newHookup = HookupFactory.generateHookup
      (esd, listenerMethod,
       sourceBean, targetBean,
       null,
       sourceSyntax,
       sourceCode,
       new String[0],
       new Object[0]);

    if (newHookup != null) // null means cancelled
      {
	removeHookup();
	try {
	  Object hookupArgs[] = new Object[1];
	  hookupArgs[0] = newHookup;
	  
	  (esd.getAddListenerMethod()).invoke(sourceBean, hookupArgs);
	  
	  // Now setup the port with the hookup info (for later removal)
	  setHookup(newHookup);
	  setSourceCode(HookupFactory.getHookupClassSource(newHookup.getClass()),
			sourceSyntax);
	  setListenerType(esd.getListenerType().getName());
	  setRemoveListenerMethod((esd.getRemoveListenerMethod()).getName());
	} catch (Exception ex) {
	  Trace.exception (ex, null);
	}
      }
   
  }
  
  @Override
  public synchronized void paint (Graphics g)
  {
    Rectangle b_rect = bounds[0];
    g.setColor(Preferences.currentPreferences.getContainerBackgroundColor());
    g.fillRect(0, 0, b_rect.width, b_rect.height);
    int inset = 1;
    if (!isInput){
      //g.fill3DRect(0, 0, b_rect.width, b_rect.height, true);
      //g.setColor(Color.black);
      //g.drawRect(0, 0, b_rect.width - 1, b_rect.height - 1);
      //arrow.paint(g); 
      switch(side){
      case Directions.LEFT:
	g.setColor(Color.black);
	g.fillRect(b_rect.width/2, 0, b_rect.width/2, b_rect.height);
	g.drawRect(b_rect.width/2, 0, b_rect.width/2, b_rect.height);
	g.setColor(Color.lightGray);
	g.fillRect(0, inset, b_rect.width/2, b_rect.height - (2 * inset));
	g.setColor(Color.black);
	g.drawRect(0, inset, b_rect.width/2, b_rect.height - (2 * inset) - 1);
	g.setColor(Color.white);
	g.drawLine(1, inset + 2, b_rect.width/2 - 2, inset + 2);
	g.drawLine(b_rect.width/2 + 1, 2, b_rect.width - 1, 2);
	break;
      case Directions.RIGHT:
	g.setColor(Color.black);
	g.fillRect(0, 0, b_rect.width/2, b_rect.height);
	g.drawRect(0, 0, b_rect.width/2, b_rect.height);
	g.setColor(Color.lightGray);
	g.fillRect(b_rect.width/2, inset, b_rect.width/2, b_rect.height - (2 * inset));
	g.setColor(Color.black);
	g.drawRect(b_rect.width/2, inset, b_rect.width/2 - 1, b_rect.height - (2 * inset) - 1);
	g.setColor(Color.white);
	g.drawLine(1, 2, b_rect.width/2 - 1, 2);
	g.drawLine(b_rect.width/2 + 1, inset + 2, b_rect.width - 2, inset + 2);
	break;
      case Directions.BOTTOM:
	g.setColor(Color.black);
	g.fillRect(0, 0, b_rect.width, b_rect.height/2);
	g.drawRect(0, 0, b_rect.width, b_rect.height/2);
	g.setColor(Color.lightGray);
	g.fillRect(inset, b_rect.height/2, b_rect.width - (2 * inset), b_rect.height/2);
	g.setColor(Color.black);
	g.drawRect(inset, b_rect.height/2, b_rect.width - (2 * inset) - 1, b_rect.height/2 - 1);
	g.setColor(Color.white);
	g.drawLine(2, 1, 2, b_rect.height/2 - 1);
	g.drawLine(inset + 2, b_rect.height/2 + 1, inset + 2, b_rect.height - 2);
	break;
      case Directions.TOP:
	g.setColor(Color.black);
	g.fillRect(0, b_rect.height/2, b_rect.width, b_rect.height/2);
	g.drawRect(0, b_rect.height/2, b_rect.width, b_rect.height/2);
	g.setColor(Color.lightGray);
	g.fillRect(inset, 0, b_rect.width - (2 * inset), b_rect.height/2);
	g.setColor(Color.black);
	g.drawRect(inset, 0, b_rect.width - (2 * inset) - 1, b_rect.height/2 - 1);
	g.setColor(Color.white);
	g.drawLine(inset + 2, 1, inset + 2, b_rect.height/2 - 2);
	g.drawLine(2, b_rect.height/2 + 1, 2, b_rect.height - 2);
	break;
      }
    }
    else{
      switch(side){
      case Directions.LEFT:
	g.setColor(Color.black);
	g.drawArc(0, 0, b_rect.width - 1, b_rect.height - 1, 270, -180);
	g.drawLine(b_rect.width - 1, 0, b_rect.width - 1, b_rect.height - 1);
	g.drawLine(b_rect.width/2, 0, b_rect.width - 1, 0);
	g.drawLine(b_rect.width/2, b_rect.height - 1, b_rect.width - 1, b_rect.height - 1);

	g.setColor(Color.gray);
	g.drawLine(b_rect.width - 4, 3, b_rect.width - 4, b_rect.height- 3);
	g.drawLine(b_rect.width - 6, 3, b_rect.width - 6, b_rect.height- 3);
	break;
      case Directions.RIGHT:
	g.setColor(Color.black);
	g.drawArc(0, 0, b_rect.width - 1, b_rect.height - 1, 270, 180);
	g.drawLine(0, 0, 0, b_rect.height - 1);
	g.drawLine(0, 0, b_rect.width/2, 0);
	g.drawLine(0, b_rect.height - 1, b_rect.width/2, b_rect.height - 1);

	g.setColor(Color.gray);
	g.drawLine(2, 3, 2, b_rect.height- 3);
	g.drawLine(4, 3, 4, b_rect.height- 3);
	break;
      case Directions.TOP:
	g.setColor(Color.black);
	g.drawArc(0, 0, b_rect.width - 1, b_rect.height - 1, 0, 180);
	g.drawLine(0, b_rect.height - 1, b_rect.width - 1, b_rect.height - 1);
	g.drawLine(0, b_rect.height - 1, 0, b_rect.height/2);
	g.drawLine(b_rect.width - 1, b_rect.height - 1, b_rect.width - 1, b_rect.height/2);

	g.setColor(Color.gray);
	g.drawLine(3, b_rect.height- 0 - 3, b_rect.width - 3, b_rect.height- 0 - 3);
	g.drawLine(3, b_rect.height- 0 - 5, b_rect.width - 3, b_rect.height- 0 - 5);
	break;
      case Directions.BOTTOM:
	g.setColor(Color.black);
	g.drawArc(0, 0, b_rect.width - 1, b_rect.height - 1, 0, -180);
	g.drawLine(0, 0, b_rect.width - 1, 0);
	g.drawLine(0, 0, 0, b_rect.height/2);
	g.drawLine(b_rect.width - 1, 0, b_rect.width - 1, b_rect.height/2);

	g.setColor(Color.gray);
	g.drawLine(3, b_rect.height - 5, b_rect.width - 3, b_rect.height - 5);
	g.drawLine(3, b_rect.height - 7, b_rect.width - 3, b_rect.height - 7);
	break;
      }
    }
  }
  
  @Override
  public void changeColor(Object logicalColor, Color color)
  {
    this.color = color;
    canvas.invalidateElement(this);
  }

  @Override
  public void changeColor(Object logicalColor, Object colorKey)
  {
    Color color =  canvas.getColorTable().lookup(colorKey);
    if (color != null)
      changeColor(logicalColor, color);
  }

  /* coordinates are local to component */
  @Override
  public boolean contains(int x, int y)
  {
    Rectangle theBounds = bounds[0];
    return theBounds.contains(x + theBounds.x ,y + theBounds.y);
  }

  @Override
  public void shift (int shiftX, int shiftY)
  {
    Rectangle rect = bounds[0];
    rect.translate(shiftX,shiftY);
    setLocation(rect.x, rect.y);
    if (connection != null)
      connection.adjustForPortChange(this);
  }
    
  @Override
  public Rectangle[] getExactBounds ()
  {
     return bounds;
  }

  int getSide()
  {
    return side;
  }

  void setSourceCode(String sourceCode, int sourceSyntax)
  {
    this.sourceCode = sourceCode;
    this.sourceSyntax = sourceSyntax;
  }

  String getSourceCode()
  {
    return sourceCode;
  }

  int getSyntax()
  {
    return sourceSyntax;
  }

  void setSide(int side)
  {
    this.side = side;
    arrow.setHeading( isInput ? 
    	      Directions.invertDirection(side) :
    	      side);
  }

  int getHeading()
  {
    return arrow.getHeading();
  }

  boolean getIsInput()
  {
    return isInput;
  }

  void setIsInput(boolean value)
  {
    isInput = value;
    arrow.setHeading( isInput ? 
    	      Directions.invertDirection(side) :
    	      side);
  }

  Wrapper getWrapper()
  {
    return wrapper;
  }

  EventInfo getEventInfo()
  {
    return eventInfo;
  }

  void reestablishEventInfo(BeanCanvas canvas)
  {
    if (eventName != null)
      {
	EventInfo eventInfo = canvas.getEventInfo(eventName,wrapper.bean.getClass());
	this.eventInfo = eventInfo;
      }
 }

  void setListenerType(String type)
  {
     listenerType = type;
  }

  void setRemoveListenerMethod(String method)
  {
     removeListenerMethod = method;
  }

  void setHookup(Object hookup)
  {
    this.hookup = (Hookup) hookup;
  }

  void setDebuggingEnabled(boolean b)
  {
    if (hookup != null)
      hookup.setDebug(b);
  }

  void addOutputConnection(int length)
  {
    Rectangle theBounds = bounds[0];
    int portLeft = theBounds.x;
    int portTop = theBounds.y;
    int portRight = theBounds.x + theBounds.width;
    int portBottom = theBounds.y + theBounds.height;
    int portHCenter = portLeft + (theBounds.width / 2);
    int portVCenter = portTop + (theBounds.height / 2);
    int halfLooseEndSize = (looseEndSize / 2);
    int looseEndX = 0;
    int looseEndY = 0;
    Point point1 = null;
    Point point2 = null;

    if (eventInfo != null && !isInput)
      {
	switch (side)
	  {
	  case Directions.LEFT:
	    point1 = new Point(portLeft, portVCenter);
	    point2 = new Point(portLeft - length, portVCenter);
	    looseEndX = point2.x - looseEndSize;
	    looseEndY = point2.y - halfLooseEndSize;
	    break;
	  case Directions.RIGHT:
	    point1 = new Point(portRight, portVCenter);
	    point2 = new Point(portRight + length, portVCenter);
	    looseEndX = point2.x;
	    looseEndY = point2.y - halfLooseEndSize;
	    break;
	  case Directions.TOP:
	    point1 = new Point(portHCenter, portTop);
	    point2 = new Point(portHCenter, portTop - length);
	    looseEndX = point2.x - halfLooseEndSize;
	    looseEndY = point2.y - looseEndSize;
	    break;
	  case Directions.BOTTOM:
	    point1 = new Point(portHCenter, portBottom);
	    point2 = new Point(portHCenter, portBottom + length);
	    looseEndX = point2.x - halfLooseEndSize;
	    looseEndY = point2.y;
	    break;
	  }
      }
    Point[] points = { point1, point2 };
    int[] widths = { 1, 2, 1 };
    String[] stripeNames = { "border", "inside", "border" };
    Color[] colors = { Color.black, eventInfo.color };
    String[] colorNames = { "border", "inside" };

    LooseEnd looseEnd = new LooseEnd(looseEndX, looseEndY, 
				     looseEndSize, looseEndSize);
    boolean visible = isVisible();
    if (!visible) looseEnd.setVisible(false);
    canvas.addElement(looseEnd);
    connection = new EventConnection (this, looseEnd,
				      points,widths,stripeNames,
				      colorNames,colors);
    if (!visible) connection.setVisible(false);
    looseEnd.setConnection(connection);
    canvas.addElement(connection);
  }
  
  Point getPortConnectionPoint()
  {
    Rectangle theBounds = bounds[0];
    int portLeft = theBounds.x;
    int portTop = theBounds.y;
    int portRight = theBounds.x + theBounds.width;
    int portBottom = theBounds.y + theBounds.height;
    int portHCenter = portLeft + (theBounds.width / 2);
    int portVCenter = portTop + (theBounds.height / 2);
    int x = 0,y = 0;

    switch (side)
      {
      case Directions.LEFT:
	x = portLeft; y = portVCenter;
	break;
      case Directions.RIGHT:
	x = portRight; y = portVCenter;
	break;
      case Directions.TOP:
	x = portHCenter; y = portTop;
	break;
      case Directions.BOTTOM:
	x = portHCenter; y = portBottom;
	break;
      }
    return new Point(x,y);
  }

  void setConnection(EventConnection connection)
  {
    this.connection = connection;
  }

  EventConnection getConnection()
  {
    return connection;
  }

  void setMethodName(String name){
    methodName = name;
  }

  String getMethodName(){
    return methodName;
  }
}
