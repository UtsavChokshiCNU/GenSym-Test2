package com.gensym.classes;

import java.util.Hashtable;
import java.lang.reflect.Constructor;
import java.lang.reflect.Method;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.message.Trace;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;

/**
 * This class is the root class of all External Event object
 * classes generated from G2 Event Classes
 */
public abstract class G2_ExternalEventObjectRoot extends com.gensym.util.SerializableSourceEvent {

  private static final Hashtable constructorTable = new Hashtable(11);
  private static final Hashtable attributeListTable = new Hashtable(11);
  protected static final Symbol SOURCE_ = Symbol.intern("SOURCE");
  protected Structure attributes = null;

  /**
   * Public stratic method called on an external Event class, to get a Sequence of attributes
   * to pre download from G2.
   */
  public static final String GET_ATTRIBUTELIST_METHODNAME_ = "getAttributeList";

  public G2_ExternalEventObjectRoot(java.lang.Object source, Item g2EventObject) {
    super(source);
  }


  public java.lang.Object getAttributeValue(Symbol attName) {
    return attributes.getAttributeValue(attName, null);
  }


  public static G2_ExternalEventObjectRoot createExternalEventObject(final java.lang.Object source, 
								      final Item item,
								      final Class externalEventClass)
  throws G2AccessException {


    try {
      Constructor cons = (Constructor)constructorTable.get(externalEventClass);
      Sequence itemAttributesList = (Sequence)attributeListTable.get(externalEventClass);
      if (cons == null) {
	Method attsMethod = externalEventClass.getMethod(GET_ATTRIBUTELIST_METHODNAME_, 
							 new Class[] {});
	itemAttributesList = (Sequence)attsMethod.invoke(null, new Object[] {});
	attributeListTable.put(externalEventClass, itemAttributesList);
	cons = 
	  externalEventClass.getConstructor(new Class[] {java.lang.Object.class, Item.class });
	constructorTable.put(externalEventClass, cons);
      }
     
      Structure itemAttributes = item.getAttributeValues(itemAttributesList);
      //System.out.println(itemAttributes);
      // Attempt to get the source from the G2 event
      // As the source attribute is at the KB level, play safe access the property generically
      java.lang.Object srcObj = source;
      if (srcObj == null) {
	java.lang.Object sourceSeqObj = itemAttributes.getAttributeValue(SOURCE_, null);
	if (sourceSeqObj != null && sourceSeqObj instanceof Sequence) {
	  Sequence sourceSeq = (Sequence)sourceSeqObj;
	  if (!sourceSeq.isEmpty()) {
		  srcObj = (Item)sourceSeq.elementAt(0);
	  }
	} else {
	  // For backward compatibilty, we should should not fail, but inform
	  // really need access to the item context so we can inform G2 !!
	  System.err.println("Warning cound not get Source Sequence attribute from G2 Event Object");
	  System.err.println("G2 Event Support Module may need upgrading, or G2-EVENT-CREATE-EVENT not used");
	}
      }

      G2_ExternalEventObjectRoot evt = 
	(G2_ExternalEventObjectRoot) cons.newInstance(new java.lang.Object[] {srcObj, item});
      
      // This could have been passed in the constructor, but keeping existing constructor for backward
      // compatibility
      evt.attributes = itemAttributes;
      return evt;
    } catch (Exception e) {
      Trace.exception(e);
      e.printStackTrace();
      throw new RuntimeException("Exception creating external event, Exception was " + e.toString());
    }

  }

  public static G2_ExternalEventObjectRoot createExternalEventObject(java.lang.Object source,
								     Structure attributes,
								     Symbol g2EventClassSymbol,
								     G2Access connection)
  throws G2AccessException {

    try {
      
      Constructor cons = (Constructor)constructorTable.get(g2EventClassSymbol);
      if (cons == null) {
	// Make sure the class is loaded
	connection.getDefinition(g2EventClassSymbol);
	Class g2EventClass = connection.getInterfaceForG2Class(g2EventClassSymbol);
	String externalEventClassName = getExternalG2EventClassName(g2EventClass.getName());
	Class externalEventClass = Class.forName(externalEventClassName);
	Method attsMethod = externalEventClass.getMethod(GET_ATTRIBUTELIST_METHODNAME_, 
							 new Class[] {});
	Sequence itemAttributesList = (Sequence)attsMethod.invoke(null, new Object[] {});
	attributeListTable.put(externalEventClass, itemAttributesList);
	cons = 
	  externalEventClass.getConstructor(new Class[] {java.lang.Object.class, Item.class });
	constructorTable.put(g2EventClassSymbol, cons);
      }
     

      //System.out.println(attributes);

      G2_ExternalEventObjectRoot evt = 
	(G2_ExternalEventObjectRoot) cons.newInstance(new java.lang.Object[] {source, null});
      
      // This could have been passed in the constructor, but keeping existing constructor for backward
      // compatibility
      evt.attributes = attributes;
      return evt;
    } catch (Exception e) {
      Trace.exception(e);
      e.printStackTrace();
      throw new RuntimeException("Exception creating external event, Exception was " + e.toString());
    }

  }



  /**
   * Return the External name of an G2 Listener Interface class
   */
  static String getExternalG2EventClassName(String className) {
    // check for package
    int dotPos = className.lastIndexOf(".");
    if (dotPos > 1) {
      return className.substring(0, dotPos) + ".G2_" + className.substring(dotPos + 1);
    }
    return "G2_" + className;
  }
    

}
