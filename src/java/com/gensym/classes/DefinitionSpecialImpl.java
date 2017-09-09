
package com.gensym.classes;

import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.ItemListener;
import com.gensym.util.ItemEvent;
import com.gensym.util.DefinitionListener;
import com.gensym.util.DefinitionEvent;
import com.gensym.util.EventMulticaster;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.util.UnexpectedException;
import com.gensym.message.Trace;
import java.util.Enumeration;

public class DefinitionSpecialImpl extends ItemImpl implements ItemListener, com.gensym.classes.G2Definition {

/*implements AttributeInitializationSymbols */

  private static final Symbol
    SYSTEM_ATTRIBUTE_DESIGNATION_ = Symbol.intern ("SYSTEM-ATTRIBUTE-DESIGNATION");
  private static final Symbol
    INITIALIZATION_               = Symbol.intern ("INITIALIZATION");
  private static final Symbol
    USER_ATTRIBUTE_NAME_          = Symbol.intern ("USER-ATTRIBUTE-NAME");

  /**
   * Returns a sequence containing the elements of the linearized
   * inheritance-path of the class defined by this Definition
   * @return The Sequnce of all classes (including "hidden" system
   * classes) in the linearized inheritance path. The last class
   * in this Sequence should be ROOT.
   * @exception G2AccessException If an error occurs during
   * communication with G2.
   */
  @Override
  public Sequence getSystemClassInheritancePath () throws G2AccessException {
    synchronized (data) {
      DefinitionData defnData = (DefinitionData)data;
      // NOTE: in three-tier this will be always slow for
      // unitialized definitions: can't tell the difference
      // between the instance in this VM being uninitialized
      // and the definition in G2 having no direct superiors.
      if (defnData.systemClassInhPath == null) {
	defnData.systemClassInhPath =
	  ((G2Gateway)context).getSystemClassInheritancePath(this);
      }
      return defnData.systemClassInhPath;
    }
  }

  /**
   * @undocumented
   */
  public void setSystemClassInheritancePath (Sequence newClassInhPath) {
    synchronized (data) {
      ((DefinitionData)data).systemClassInhPath = newClassInhPath;
    }
  }

  /**
   * Return the value of a static attribute of the class named
   * by the argument. Will return null if the attribute does
   * not exist.
   * @return An item-or-value that is the value of the named atttribute
   * @exception G2AccessException If an error occurs during
   * communication with G2.
   */
  @Override
  public java.lang.Object getClassAttributeValue (com.gensym.util.Symbol attrName) throws G2AccessException {
    java.lang.Object attrValue = null;
    try {
      attrValue = getAttributeValue (attrName);
    } catch (Exception e) {
      Trace.exception (e, "Error looking for attribute " + attrName + " in class ");
    }
    if (attrValue == null) {
      Sequence inhAttrInitlzns = getAttributeInitializations ();
      if (inhAttrInitlzns != null) {
	Enumeration e = inhAttrInitlzns.elements ();
	while (e.hasMoreElements ()) {
	  Structure attrInitlzn = (Structure) e.nextElement ();
	  Symbol initializedAttrName =
	    (Symbol) attrInitlzn.getAttributeValue (SYSTEM_ATTRIBUTE_DESIGNATION_, null);
	  if (initializedAttrName!= null && attrName.equals (initializedAttrName)) {
	    attrValue = attrInitlzn.getAttributeValue (INITIALIZATION_, null);
	    break;
	  }
	}
      }
    }
    return attrValue;
  }



  /**
   * Register to be notified of changes to the class-definition
   * @see #com.gensym.util.DefinitionListener
   * @exception G2AccessException If an error occurs during
   * communication with G2.
   */
  public void addDefinitionListener (DefinitionListener newListener) throws G2AccessException {
    DefinitionData defnData = (DefinitionData)data;
    synchronized (defnData) {
      if (defnData.defnListener == null)
	addItemListener (this);
      defnData.defnListener = EventMulticaster.add (defnData.defnListener, newListener);
    }
  }

  /**
   * Deregister for changes to the class defined by this Item
   * @exception G2AccessException If an error occurs during
   * communication with G2.
   */
  public void removeDefinitionListener (DefinitionListener oldListener) throws G2AccessException {
    DefinitionData defnData = (DefinitionData)data;
    synchronized (defnData) {
      defnData.defnListener = EventMulticaster.remove (defnData.defnListener, oldListener);
      if (defnData.defnListener == null)
	removeItemListener (this);
    }
  }

  private boolean inheritanceFlag = false;
  
  /**
   * @undocumented Called from the item-change notification
   * and from com.gensym.util.ClassManager for affected subclasses.
   */
  public void processDefinitionEvent (DefinitionEvent defnEvent) {
    //System.out.println (":: " + defnEvent);
    int eventType = defnEvent.getEventType ();
    DefinitionData defnData = (DefinitionData)data;
    if (defnData.defnListener != null) {
      synchronized (defnData) {
    	switch (eventType) {
	case DefinitionEvent.CLASS_NAME_CHANGED:
	  // when the class name changes, G2 will send two inheritance
	  // path changes *before* it sends the changed name. Listeners
	  // to inheritance changes get very confused if the class itself
	  // is not in the inheritance path by its current name
	  // (the main example was
	  // AttributesDialogInfo). The following code sends an inheritance
	  // path change, after all the internal data is correct.
	  DefinitionEvent inhEvent = null;
	  try {
	    Sequence inhPath = getClassInheritancePath();
	    Sequence oldPath = (Sequence)inhPath.clone();
	    // NOTE: the following two lines destructively
	    // modifies the internal data structure
	    inhPath.removeElementAt(0);
	    inhPath.insertElementAt((Symbol)defnEvent.getNewValue(), 0);
	    inhEvent =
	      new DefinitionEvent(this,
				  DefinitionEvent.CLASS_INHERITANCE_PATH_CHANGED,
				  this,
				  CLASS_INHERITANCE_PATH_,
				  inhPath,
				  oldPath);
	    invalidateSystemInheritancePath();
	    // NOTE: the stubclassloader must be updated
	    // before the classManager is
	    ((G2Gateway)context).unloadClass((Symbol)defnEvent.getOldValue());
	    context.getDefinition((Symbol)defnEvent.getNewValue());
	  } catch (G2AccessException g2ae) {
	    throw new UnexpectedException(g2ae);	      
	  }
	  defnData.defnListener.classNameChanged (defnEvent);
	  defnData.defnListener.classInheritancePathChanged(inhEvent);
	  break;
	case DefinitionEvent.CLASS_SPECIFIC_ATTRIBUTES_CHANGED:
	  defnData.defnListener.classSpecificAttributesChanged (defnEvent); break;
	case DefinitionEvent.DIRECT_SUPERIOR_CLASSES_CHANGED:
	  defnData.defnListener.directSuperiorClassesChanged (defnEvent); break;
	case DefinitionEvent.CLASS_INHERITANCE_PATH_CHANGED:
	  boolean inhFlag = true;
	  java.lang.Object newValue = defnEvent.getNewValue();
	  if (newValue != null) {
	    Sequence newPath = (Sequence)newValue;
	    try {
	      if (!getClassName().equals(newPath.firstElement())) {
		// swallow all inheritance class changes that come from
		// changing the name of the class.
		break; 
	      }
	    } catch (G2AccessException g2ae) {
	      Trace.exception(g2ae);
	    }
	  }
	  // Designed to swallow only the first event where the new
	  // inheritancePath is null. If it comes in as null, G2 will
	  // always be sending another event (as far as we know)
	  if (newValue == null || inheritanceFlag) {
	    inhFlag = inheritanceFlag;
	    inheritanceFlag = !inhFlag;
	  }
	  if (inhFlag) {
	    invalidateSystemInheritancePath();
	    defnData.defnListener.classInheritancePathChanged (defnEvent);
	  } else
	    ; //swallow the event.
	  break;
	case DefinitionEvent.STATIC_ATTRIBUTE_CHANGED:
	  defnData.defnListener.staticAttributeChanged (defnEvent); break;
	case DefinitionEvent.DELETED:
	  defnData.defnListener.deleted (defnEvent); break;
	default:
	}
      }
    }
  }

  private void invalidateSystemInheritancePath() {
    synchronized(data) {
      ((DefinitionData)data).systemClassInhPath = null;
    }
  }

  /**
   * Can't have no inner classes in SpecialImpls. :)
   * Maybe fix? -vkp, 8/18/98
   * @undocumented
   */
  @Override
  public void receivedInitialValues (ItemEvent e) {
    ((DefinitionData)data).defnAttributesStructure = (Structure)e.getNewValue ();
  }

  /**
   * @undocumented
   *
   */
  @Override
  public void itemModified (ItemEvent e) {
    Sequence changedDenotation = e.getDenotation ();
    Symbol attributeName = com.gensym.util.AttributeDenotation.getAttributeName (changedDenotation);
    int eventID;
    DefinitionData defnData = (DefinitionData)data;
    java.lang.Object newValue = e.getNewValue ();
    java.lang.Object oldValue = defnData.defnAttributesStructure.getAttributeValue (attributeName, null);
    if (oldValue == newValue ||	// both null or same object?
	(oldValue != null && oldValue.equals (newValue))) // equivalence check
      return;
    defnData.defnAttributesStructure.setAttributeValue (attributeName, newValue);
    Symbol staticAttributeName = null;
    if (attributeName.equals (SystemAttributeSymbols.CLASS_NAME_))
      eventID = DefinitionEvent.CLASS_NAME_CHANGED;
    else if (attributeName.equals (SystemAttributeSymbols.DIRECT_SUPERIOR_CLASSES_))
      eventID = DefinitionEvent.DIRECT_SUPERIOR_CLASSES_CHANGED;
    else if (attributeName.equals (SystemAttributeSymbols.CLASS_INHERITANCE_PATH_))
      eventID = DefinitionEvent.CLASS_INHERITANCE_PATH_CHANGED;
    else if (attributeName.equals (SystemAttributeSymbols.CLASS_SPECIFIC_ATTRIBUTES_)) {
      eventID = DefinitionEvent.CLASS_SPECIFIC_ATTRIBUTES_CHANGED;
    } else {
      eventID = DefinitionEvent.STATIC_ATTRIBUTE_CHANGED;
      staticAttributeName = attributeName;
    }
    processDefinitionEvent (new DefinitionEvent ((Definition)this,
						 eventID,
						 (Definition)this,
						 staticAttributeName,
						 e.getNewValue (),
						 oldValue));
  }

  /**
   * @undocumented
   */
  @Override
  public void itemDeleted (ItemEvent e) {
    processDefinitionEvent (new DefinitionEvent ((Definition)this,
						 DefinitionEvent.DELETED,
						 (Definition)this,
						 null,
						 e.getNewValue (),
						 null));
  }

  /**
   * @undocumented
   * Sets up the data to store information about the Definition
   */
  @Override
  protected ItemData makeDataForItem () {
    return new DefinitionData();
  }

}
