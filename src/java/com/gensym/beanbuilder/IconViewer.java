
package com.gensym.beanbuilder;

import java.awt.*;
import java.lang.reflect.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.jgi.*;
import com.gensym.classes.*;

/**
 * This class is a component that will read and display a G2 Icon for a g2 class
 */
public class IconViewer extends Component {

  static final long serialVersionUID = -6224243325478303745L;

  private static final Symbol ITEM_ = Symbol.intern ("ITEM");
  private static final Symbol WIDTH_ = Symbol.intern ("WIDTH");
  private static final Symbol HEIGHT_ = Symbol.intern ("HEIGHT");
  private static final Symbol NAME_ = Symbol.intern ("NAME");

  private transient boolean noIcon = true;

  public IconViewer(){}

  @Override
  public Dimension getPreferredSize () {
    return new Dimension (50, 50);
  }

  private transient IconRepresentation irep = null;


  /**
   * The icon description is fetched for a g2Clazz, but it will only be rendered
   * if Telewindows2 icon rendering tools are available
   */
  public boolean getIconDescriptionForClass(G2Connection g2Connection, Symbol g2clazz) {

    // If we have not got access to an Iconrenderinf manager
    // then forget this
    java.lang.Object irm = null;

    try  {

      Class irmClass = Class.forName("com.gensym.irm.IconRenderingManager");
      java.lang.reflect.Constructor cons = irmClass.getConstructor(new Class[0]);

      irm = cons.newInstance(new java.lang.Object[0]);

    } catch (NoSuchMethodException E) { Trace.exception(E); }
    catch (InstantiationException E) {Trace.exception(E); }
    catch (InvocationTargetException E) {Trace.exception(E); }
    catch (ClassNotFoundException E) {Trace.exception(E); }
    catch (IllegalAccessException E) {Trace.exception(E); }
	if (irm == null) 
		return false;

    try {


      // Must try to get the icon description, it may be
      // in a superclass

      Definition classDef = (Definition)g2Connection.getUniqueNamedItem(
					 com.gensym.util.symbol.G2ClassSymbols.CLASS_DEFINITION_,
					 g2clazz);

      Structure iconDescription = classDef.getIconDescription ();
      Structure iconVariables   = classDef.getIconVariables ();
      Structure iconRegions     = classDef.getItemColorPattern ();

      if (iconDescription == null) {
	Sequence classInhPath = classDef.getClassInheritancePath();

	for (java.util.Enumeration e = classInhPath.elements(); e.hasMoreElements();) {

	  classDef = (Definition)g2Connection.getUniqueNamedItem(
					  com.gensym.util.symbol.G2ClassSymbols.CLASS_DEFINITION_,
					  (Symbol)e.nextElement());

	  //System.out.println("Trying " + classDef);

	  iconDescription = classDef.getIconDescription ();
	  iconVariables   = classDef.getIconVariables ();
	  iconRegions     = classDef.getItemColorPattern ();

	  if (iconDescription != null)
	    break;
	}
      }

      if (iconDescription == null) {
	// This should not happen, but as a catch all
	// for a bug  08/Apr/98, where we cant get
	// at the object definitions for a build in class
	System.err.println("Can't read icon as, can not get class-definition for build in class");
	return false;
      }

      //System.out.println ("Icon Description for" + classDef + "  " + iconDescription +
      //		  "\n" + "Icon Variables = " + iconVariables +
      //		  "\n" + "Icon Regions = " + iconRegions);
       width = ((Integer) iconVariables.getAttributeValue (WIDTH_, null)).intValue ();
       height = ((Integer) iconVariables.getAttributeValue (HEIGHT_, null)).intValue ();

      //IconRenderingManager irm = new IconRenderingManager ();

      //create a new representation for the icon
      irep = null;
      try {
	Class iconDesClass = Class.forName("com.gensym.icons.IconDescription");
	java.lang.reflect.Constructor iconDesCons = iconDesClass.getConstructor(new Class[] {Structure.class});
	java.lang.Object iconDes = iconDesCons.newInstance(new java.lang.Object[] {iconDescription});

	java.lang.reflect.Method irmMethod = irm.getClass().getMethod("GetIconRendering",
	       new Class[] {iconDesClass, Integer.TYPE, Integer.TYPE, Integer.TYPE} );

	irep = new IconRepresentation(irmMethod.invoke(irm,
						       new java.lang.Object[] { iconDes, width, height, 0 } ) );
       
      } catch (NoSuchMethodException E) { Trace.exception(E);  }
      catch (InstantiationException E) { Trace.exception(E);}
      catch (InvocationTargetException E) { 
          Trace.exception(E); 
          Trace.exception(E.getTargetException());
      }
      catch (ClassNotFoundException E) { Trace.exception(E); }
      catch (IllegalAccessException E) { Trace.exception(E); }

      if (irep == null) 
    	  return false;
      // All the above just to do this !
	//irep.ir = irm.GetIconRendering( new IconDescription(iconDescription) ,
	//			      width , height , Symbol.intern("NORMAL"));


      //drawElement = new IconElement (new IconDescription (iconDescription),
      //			     iconVariables,
      //			     iconRegions,
      //			     Symbol.intern ("NORMAL"),
      //			     0, 0, width + 1, height + 1,
      //			     ((TwAccess)((com.gensym.classes.ImplAccess)entity).getContext()).getIconManager());


      repaint ();
      noIcon = false;
      setSize (width + 1, height + 1);
    } catch (G2AccessException gae) {
      //gae.printStackTrace ();
      return false;
    }

    return true;
  }


  private Image img ;


  public Image getImg() {
    return img;
  }

  static int width;
  static int height;

  @Override
  public void paint (Graphics g) {

    img = createImage(width, height);

    paintIconDescription (img.getGraphics());
    g.drawImage(img, 0,0,this);

    paintIconDescription (g);
  }

  void paintIconDescription (Graphics g) {

    irep.draw(g, 0, 0);
  }


  void paintIrep (IconRepresentation theIrep , Graphics g) {
    theIrep.draw(g, 0, 0);
  }



// given an IconRepresentation from G2 to be displayed at x,y
//
class IconRepresentation  implements java.io.Serializable
{
  int x;
  int y;
  java.lang.Object  ir = null;
  java.lang.reflect.Method irDrawMethod = null;

  //constructors
  IconRepresentation(){

  }

  IconRepresentation(java.lang.Object iconrendering)
  {
    ir = iconrendering;
    try {
      //System.out.println("1" + ir.getClass() + " ");
      irDrawMethod = ir.getClass().getMethod("Draw",
		new Class[] {Graphics.class, Integer.TYPE, Integer.TYPE} );
      //System.out.println("2" + irDrawMethod);
    } catch (NoSuchMethodException E) {  }
    
    if (irDrawMethod == null)
  	  // ahh this should never happen !
  	  throw new RuntimeException("Could not get Draw Method on IconRendering");

  }


  void draw(Graphics g, int x, int y) {
    boolean didIt = false;
    try {
      //System.out.println(ir + " " + irDrawMethod + " " + g);
      irDrawMethod.invoke(ir, new java.lang.Object[] {g, x, y} );
      didIt = true;
    } catch (Exception e) {
	  throw new RuntimeException("Could not Draw icon..."+ e.toString());
    }
  }

  /**
   *	indicates that the IconRepresentation is nolonger
   * of use to the system
   *
   */
  void delete(){
    ir = null;
  }

 }





}

