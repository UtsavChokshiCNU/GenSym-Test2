package com.gensym.wksp;

import java.awt.*;
import java.io.IOException;
import java.beans.Beans;
import java.awt.event.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.draw.*;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;

/**
 * A BeanElement is a wrapper class that can be added to a WorkspaceView.
 * It create a Bean initially and then manages only the changes in
 * its view position. When the window scroll state changes, the Bean
 * component needs to be "scrolled." and not just "repainted" at its
 * new location, as is usual for other WorkspaceElements
 */
public class BeanElement extends DefaultWorkspaceElement
{

  private Object bean;
  private Component beanComponent;
  //These should be here(pbk)
  static Symbol sleft = Symbol.intern("LEFT");
  static Symbol stop = Symbol.intern("TOP");
  static Symbol sright = Symbol.intern("RIGHT");
  static Symbol sbottom = Symbol.intern("BOTTOM");
  
  static final Symbol _classID   = Symbol.intern ("CLASS-ID");
  static final Symbol _itmBounds = Symbol.intern("TW-WORKSPACE-ITEM-BOUNDS");
  static final Symbol swidth     = Symbol.intern ("WIDTH");
  static final Symbol sheight    = Symbol.intern ("HEIGHT");
  static final Symbol sbounds    = Symbol.intern ("BOUNDS");
  static final Symbol PROXY_CLASS_NAME = Symbol.intern ("GENSYM-BEAN-PROXY");
  private static final boolean beanDebug = false;
  int top, left, width, height;

  public BeanElement (Item item, WorkspaceView view) throws G2AccessException {
    super(item,view);
  }

  public void initialize () {
  }

  private static final java.io.PrintStream o = System.out;
  @Override
  public void addNotify () {
    System.out.println("BeanElement::addNotify () called");
    com.gensym.wksp.WorkspaceView w = (WorkspaceView) getParent();
    com.gensym.wksp.WorkspaceView wksp = (WorkspaceView) getParent();
    System.out.println("CanvasContainer (A WorkspaceView?) = " + w + "\nbeanComponent = " + beanComponent);
    /*if (w != wksp) why do we need this ? pbk
      throw new RuntimeException ("Parent is not the expected WorkspaceView");*/
    Rectangle viewBounds = w.getViewBounds (); // set in WorkspaceElement
    int       vLeft      = viewBounds.x;
    int       vTop       = viewBounds.y;
    beanComponent.setBounds (left - vLeft, top - vTop, width, height);
    /*Container pc = c.getParent ();*/
    wksp.add (beanComponent);
    new BeanHookup (wksp, beanComponent);
    // wksp.list ();
    super.addNotify ();
    System.out.println("Raising ActiveXControl to Top>>>>>>>>");
    System.out.println("Layout Manager for WorkspaceView = " + wksp.getLayout ());
    //WindowUtil.raise (beanComponent);
    // wksp.list ();
    TwAccess context = null;
    KbWorkspace workspace = wksp.getWorkspace();
    if (workspace == null) {
      System.out.println("workspace is null");
      Thread.dumpStack();
    } else
      context = (TwAccess)((com.gensym.classes.ImplAccess)workspace).getContext ();//hack
    if (false) {
      System.out.println("Inserting BeanElement in non-null context!");
      String wsName = "SORRY NO NAME";//(String) wksp.getWorkspace().getNames();
      System.out.println("Workspace Name = " + wsName);
      Structure beanInfoStructure = new Structure ();
      Structure bounds = new Structure ();
      bounds.setAttributeValue (sleft, new Integer (left));
      bounds.setAttributeValue (stop,  new Integer (top));
      bounds.setAttributeValue (swidth, new Integer (width));
      bounds.setAttributeValue (sheight, new Integer (height));
      System.out.println("Bounds = " + bounds);
      beanInfoStructure.setAttributeValue (sbounds, bounds);
      beanInfoStructure.setAttributeValue (_classID, beanComponent.getClass().getName ());
      System.out.println("Full Structure = " + beanInfoStructure);
      System.out.println("Making call to createBeanProxy ()");
      /*try {
	item = context.createBeanProxy (wsName, beanInfoStructure);
      } catch (G2AccessException g2ae) {
	// fix this: can't be thrown because subclassed from draw.DrawElement
	g2ae.printStackTrace();
	}
	*/
	}
  }

  @Override
  public boolean contains(int x, int y)
  {
    if (beanDebug)
      System.out.println("BeanElement::inside called for " + this + "(" + x + ", " + y + ")");
    /*Rectangle bounds = new Rectangle (left, top, width, height);
      if (beanDebug)
      System.out.println("BeanElement bounds are " + bounds + "\nReturning " + bounds.contains (x, y));
      return (bounds.contains(x,y));*/
    return super.contains(x,y);
  }

  @Override
  public Rectangle[] getExactBounds()
  {
    //System.out.println("BeanElement::Bounds () called");
    //Rectangle[] bnds = { new Rectangle (left, top, width, height) };
    //System.out.println("BeanElement::Bounds () returning " + bnds[0]);
    return super.getExactBounds();
  }

  public void shiftForScroll (int deltaX, int deltaY) {
    Point locn = beanComponent.getLocation ();
    //System.out.println("----> Moving Bean by (" + deltaX + ", " + deltaY + ")");
    beanComponent.setLocation (locn.x + deltaX, locn.y + deltaY);
  }

  @Override
  public void shift (int deltaX, int deltaY) {
    top += deltaY;
    left += deltaX;
    shiftForScroll (deltaX, deltaY);
    //pbk fix((WorkspaceView)getParent()).elementChanged (this);
  }


  public void resize(int left, int top, int width, int height) {
    this.left   = left;
    this.top    = top;
    this.width  = width;
    this.height = height;
    com.gensym.wksp.WorkspaceView w = (WorkspaceView) getParent ();
    Rectangle viewBounds = w.getViewBounds (); // set in WorkspaceElement
    int       vLeft      = viewBounds.x;
    int       vTop       = viewBounds.y;
    setBounds (left - vLeft, top - vTop, width, height);
    beanComponent.setBounds (left - vLeft, top - vTop, width, height);
    beanComponent.repaint ();
    // pbk fix((WorkspaceView)getParent()).elementChanged (this);
  }

  @Override
  public void paint(Graphics g) {
    // This is now a no-op because all BeanElements have
    // their own windows
  }

  public void editItem () {
  }

  @Override
  public DraggingGhost getDraggingGhost (int left, int top, int width, int height) {
    Color Xcolor = Color.orange;
    Color ghostColor = Color.gray;
    DraggingGhost ghost = new DraggingGhost ();
    ghost.elements = new Component[6];
    ghost.elements[2] = new LineElement (ghostColor, left, top, left+width, top);
    ghost.elements[3] = new LineElement (ghostColor, left+width, top, left+width, top+height);
    ghost.elements[4] = new LineElement (ghostColor, left+width, top+height, left, top+height);
    ghost.elements[5] = new LineElement (ghostColor, left, top+height, left, top);
    int[] xPts = new int [4];
    int[] yPts = new int [4];
    xPts[0] = left;  xPts[1] = left + Math.round (width*0.1f);
    xPts[2] = left + width; xPts[3] = left + Math.round (width*0.9f);
    yPts[0] = top; yPts[1] = top; yPts[2] = top + height; yPts[3] = top + height;
    ghost.elements[0] = new PolygonElement (Xcolor, 4, xPts, yPts);
    xPts[0] = left + Math.round (0.9f*width); xPts[1] = left + width;
    xPts[2] = left + Math.round (0.1f*width); xPts[3] = left;    
    ghost.elements[1] = new PolygonElement (Xcolor, 4, xPts, yPts);
    if (beanDebug)
      System.out.println("Ghost created for (" + left + ", " + top + ") -> " + width + ", " + height);
    ghost.boundsArray[0] = new Rectangle (left, top, width+2, height+2);
    return ghost;
  }

  public static Structure createBeanInfo (Point p) {
    int x = p.x, y = p.y;
    Structure beanInfo = new Structure ();
    return beanInfo;
  }


  public static Structure createBeanInfo () {
    return createBeanInfo (new Point (200, 200));
  }

}


class BeanHookup implements MouseListener, MouseMotionListener {

  private WorkspaceView wksp;
  private PersistentCanvas canvas;
  private Component bean;

  BeanHookup (WorkspaceView wksp, Component bean) {
    this.wksp   = wksp;
    this.canvas = wksp;
    this.bean   = bean;
    bean.addMouseListener (this);
    bean.addMouseMotionListener (this);
  }
  
  private static final java.io.PrintStream o = System.out;
  public void forwardMouseEvent(MouseEvent e) {
    Point locn = bean.getLocation ();
    e.translatePoint (locn.x, locn.y);
    MouseEvent newEvent = new MouseEvent (canvas, e.getID (), e.getWhen (),
					  e.getModifiers (), e.getX (), e.getY (),
					  e.getClickCount (), e.isPopupTrigger ());
    canvas.dispatchEvent (newEvent);
  }
  public boolean isCut () {
    return false;
  }

  public void setCut (boolean newCutState) {
    // Do nothing!
  }

  @Override
  public void mouseClicked(MouseEvent e) {forwardMouseEvent (e);}
  @Override
  public void mousePressed(MouseEvent e) {forwardMouseEvent (e);}
  @Override
  public void mouseReleased(MouseEvent e) {forwardMouseEvent (e);}
  @Override
  public void mouseEntered(MouseEvent e) {forwardMouseEvent (e);}
  @Override
  public void mouseExited(MouseEvent e) {forwardMouseEvent (e);}
  @Override
  public void mouseDragged(MouseEvent e) {forwardMouseEvent (e);}
  @Override
  public void mouseMoved (MouseEvent e) {forwardMouseEvent (e);}
}
