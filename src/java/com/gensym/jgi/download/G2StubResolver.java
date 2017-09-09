package com.gensym.jgi.download;

import com.gensym.classes.Item;
import com.gensym.util.*;
import com.gensym.classes.G2__BaseImpl;


/**
 * This class provides access to a G2 Stub implementation, given a particular G2 exported Interface.
 */
public class G2StubResolver {

  /**
   * Return a G2 Stub instance that implements the exported interface for
   * a G2 Class.
   *@exception G2StubCreationException if no stub can be created.
   */
  public static Item createStubForG2Interface(Class g2InterfaceClass) throws G2StubCreationException {

    if (!g2InterfaceClass.isInterface() || !Item.class.isAssignableFrom(g2InterfaceClass))
      throw new G2StubCreationException(g2InterfaceClass.getName() + "is not a G2 Interface class");
    String g2ClassNameStr = g2InterfaceClass.getName();
    g2ClassNameStr = g2InterfaceClass.getName().substring(g2ClassNameStr.lastIndexOf(".")+1);
    Symbol g2ClassName = G2ClassTranslator.createG2ClassNameFromJavaClassName(g2ClassNameStr);

    String stubclassName = getG2StubClassName(g2InterfaceClass.getName());    
    try {
      Class stubClass = Class.forName(stubclassName);
      Item stub = (Item) stubClass.newInstance();
      ((G2__BaseImpl)stub).setInternalG2ClassName(g2ClassName);
      return stub;
    } catch (Exception e) {
      throw new G2StubCreationException("Could not create G2Stub [" + stubclassName + "] because " +
					e.toString());  
    }
  }


  static String getG2StubClassName(String interfaceName) {

    return interfaceName + "Impl";
  }

}
