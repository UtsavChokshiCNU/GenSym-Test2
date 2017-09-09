package com.gensym.jgi;

import java.lang.reflect.*;
import java.util.Hashtable;
import java.beans.*;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.G2ClassTranslator;
import com.gensym.util.NtwIllegalArgumentException;
import com.gensym.jgi.download.G2StubCreationException;


/**
 * This class provides the methods to generate G2 stub for a Java Class.
 */
class G2JavaStubGenerator implements G2JavaStubClassReflectionProvider {

  private static final Symbol 
    jgiG2CallRpcName       = Symbol.intern("JGI-CALL-JAVA-PROXY-METHOD"),
    jgiG2CallStaticRpcName = Symbol.intern("JGI-CALL-JAVA-PROXY-STATIC-METHOD"),
    jgiG2CallG2ItemListenerRpcName = Symbol.intern("JGI-CALL-JAVA-PROXY-G2ITEM-LISTENER-METHOD"),
    jgiG2CreateProxyName   = Symbol.intern("JGI-JAVA-CLASS-DEFINITION::NEW"),
    jgiG2FullDisposeMethodName = Symbol.intern("JGI-JAVA-PROXY::DISPOSE"),
    jgiG2DisposeMethodName = Symbol.intern("DISPOSE"),
    NONE_                  = Symbol.intern("NONE"),
    CLASS_INFO_            = Symbol.intern("CLASS-INFO"),
    IS_ABSTRACT_           = Symbol.intern("IS-ABSTRACT"),
    METHOD_NAME_           = Symbol.intern("METHOD_NAME"),
    METHOD_TEXT_           = Symbol.intern("METHOD_TEXT"),
    METHOD_DECLARATION_    = Symbol.intern("METHOD_DECLARATION"),
    STATIC_DEFINITION_     = Symbol.intern("STATIC_DEFINITION"),
    JAVA_PARAMETER_TYPES_  = Symbol.intern("JAVA_PARAMETER_TYPES");

  private static final String VOID_DISPATCH_METHOD = "_t2beans-dispatch-void";
  private static final String DISPATCH_METHOD_WITH_RETURN = "_t2beans-dispatch";

  private static final String 
             ROOT_G2_EVENT_LISTENER_CLASS_NAME = "com.gensym.classes.modules.g2evliss.G2EventListener",
	     ROOT_G2_EVENT_OBJECT_CLASS_NAME = "com.gensym.classes.modules.g2evliss.G2EventObject";


  /**                
   * Return a sequence containing any classes that clazz is dependant on, including
   * dependant hierarchy and method parameters.
   */
  @Override
  public Sequence findDependentClasses(String class_name, Class clazz, boolean recurse)
       throws ClassNotFoundException, G2StubCreationException
  {
    JavaClassStubGeneratorHierarchy jce = new JavaClassStubGeneratorHierarchy();

    return jce.detailAncestry( clazz);

  }

  /**
   * Return information enabling G2 to build G2 stubs
   * that allow access to a named Java class properties and methods.
   *
   */
  @Override
  public Structure getG2StubDetailsForJavaClass(String class_name, 
						Class the_class, 
						Symbol G2_class_name, 
						boolean recurse,
						boolean forG2BeanWrapper)
       throws ClassNotFoundException, G2StubCreationException
  {

    Symbol[] propnames = new Symbol[4];
    Object[] propvalues = new Object [4];
    Structure ret_val = new Structure();

    try {
    // construct the return Structure
    propnames[0]= Symbol.intern("CLASS_NAME");
    propvalues[0]	=  G2_class_name;

    propnames[1]= Symbol.intern("BEANINFO_STUBS");
    if (forG2BeanWrapper)
      propvalues[1] = getG2StubsForWrapper (the_class, G2_class_name, recurse);
    else
      propvalues[1]= getG2StubsForBeanInfo(the_class, G2_class_name, recurse);

    propnames[2]= Symbol.intern("CONSTRUCTOR_STUBS");
    propvalues[2]= getG2StubsForConstructors(the_class, G2_class_name);

    propnames[3]= Symbol.intern("BEANINFO_PROPERTIES");
    propvalues[3]= getG2BeanInfoProperties(the_class, G2_class_name, recurse);

    ret_val = new  Structure ( propnames , propvalues);
    }
    catch (Exception E) {
      E.printStackTrace();
      throw new G2StubCreationException(
		     "The following Exception was raised while constructing Bean Info for "
                     + the_class.getName() + "\n" + E.toString());
    }

    return ret_val ;
  }

 /**
   * Construct a Sequence containing info about any properties found a bean class.
   *
   */
  Structure getG2BeanInfoProperties(Class beanClass, Symbol G2_class_name, boolean recurse)
       throws ClassNotFoundException,
	      G2StubCreationException
  {

    // getters and setters are redundant -- will be removed asap
    Sequence attributes = new Sequence();
    Sequence types = new Sequence();
    Sequence getters = new Sequence();
    Sequence setters = new Sequence();
    Symbol[] propnames = new Symbol[4];
    Object[] propvalues = new Object [4];
    Sequence ret_val = new Sequence();

    Class arrayClass=null;

    try {
      if (false) {

	//Class stopBefore = Class.forName("java.awt.Component");
	BeanInfo bi = Introspector.getBeanInfo(beanClass);

	// System.out.println("CLASS: " + beanClass.getName());

	String correspondingG2Type ="";

	// Get Bean Property Descriptors.
	PropertyDescriptor[] properties = bi.getPropertyDescriptors();
	// Print bean Properties
	//System.out.println(" Property Descriptors:");
	Method m;
	for (int i = 0 ;i < properties.length;i++){
	  PropertyDescriptor pd = properties[i];

	  attributes.addElement(G2ClassTranslator.checkAndReMapAttributeNames(pd.getName()));

	  if(pd.getPropertyType() == null )
	    { //probably indexed property
	    System.out.println("WARNING "+
	        pd.getName() +
			       " probably is an indexed property that does not support non-indexed access. ");
	    types.addElement("sequence");
	    } else  {
	      // Get G2 equivalent type
	      //    System.out.println("Java ="+pd.getPropertyType().toString()+
	      //			     "G2=>"+G2ClassTranslator.getG2ReturnTypeFromjavaClass(pd.getPropertyType()));

	      correspondingG2Type = G2ClassTranslator.getG2TypeFromJavaClassOrNull(pd.getPropertyType());
	      //       System.out.println("here - correspondingG2Type <"+correspondingG2Type+">");

	      if(correspondingG2Type==null){
		//System.out.println(" - ammended <"+pd.getPropertyType());

                if (pd.getPropertyType().isArray()) {
		  // System.out.println(" Is array " +pd.getPropertyType().getName() );
		  arrayClass = pd.getPropertyType().getComponentType();
		  types.addElement(arrayClass.getName().trim()+"-array");
                 // System.out.println(" of type  " +arrayClass.getName() );
                } else {
		  // System.out.println(" Not array "+ pd.getPropertyType().getName());
		  types.addElement(pd.getPropertyType().getName().trim());
                }
	      } else {
		if(correspondingG2Type.startsWith("CLASS "))
		  {    String temp=correspondingG2Type.trim();
		  types.addElement(temp.substring(6,temp.length() ));
		  // System.out.println("    mod chop "+temp.substring(6,temp.length() ));
		  }
		else
		  types.addElement(correspondingG2Type.trim());
	      }
	    }

	  m = pd.getReadMethod();
	  if (m == null) {
	    getters.addElement("");
	  } else {
	    getters.addElement(m.getName());
	  }

	  m = pd.getWriteMethod();
	  if (m == null) {
	    setters.addElement("");
	  } else {
	    setters.addElement(m.getName());
	  }


	  getters.addElement("");
	  setters.addElement("");
	  /*
	    if (pd instanceof IndexedPropertyDescriptor)
	    {
	    IndexedPropertyDescriptor ipd =
	    (IndexedPropertyDescriptor) pd;
	    types.addElement.ipd.getIndexedPropertyType();
	    getters.ipd.getIndexedReadMethod();
	    setters.ipd.getIndexedWriteMethod();
	    
	  }
	  */
	}

      String 	G2_args_type = "";
      } else {
      getters.addElement("");
      setters.addElement("");
      }

    propnames[0]= Symbol.intern("METHOD_NAMES");   
    propvalues[0] = attributes;
    propnames[1]= Symbol.intern("METHOD_TYPES");   
    propvalues[1] = types;
    propnames[2]= Symbol.intern("METHOD_GETTERS"); 
    propvalues[2] = getters;
    propnames[3]= Symbol.intern("METHOD_SETTERS"); 
    propvalues[3] = setters;

    // getters and setters are redundant -- will be removed asap

      Structure beanProperties = new Structure ( propnames , propvalues);

      return beanProperties;

    }
    catch (Exception E)
      {
	throw new G2StubCreationException(
	       "The following Exception was raised while constructing G2 attribute for Java class "
                 + beanClass.getName() + "\n" + E.toString());
      }
  }

 
 public Sequence getG2StubsForBeanInfo(Class beanClass, Symbol G2_class_name, boolean recurse)
       throws ClassNotFoundException,
	      G2StubCreationException
  {
    
    try {
      
      String G2_method_text;
      String G2_args_text;
      String G2_jgi_RPC_name = jgiG2CallRpcName.toString();
      String G2_jgi_RPC_static_name = jgiG2CallStaticRpcName.toString();
      String proxy_static_relate_text = "conclude that interface is the-jgi-interface-of ret_val;";
      String proxy_relate_text = "conclude that the gsi-interface that is the-jgi-interface-of self is the-jgi-interface-of ret_val;";
      Class parameter_classes[];
      Hashtable existing_method_calls = new Hashtable(); // Method names must be unique
      Class return_class;
      boolean bad_method;
      String G2_mangled_class_name = G2_class_name.toString();
      
      //Class stopBefore = Class.forName("java.awt.Component");
      //BeanInfo bi = Introspector.getBeanInfo(beanClass , null );
      
      boolean isG2EventListenerClass = isClassInstanceOf(beanClass, ROOT_G2_EVENT_LISTENER_CLASS_NAME);

      // Use reflection to get the methods
      Method java_methods[] = beanClass.getMethods();
      Hashtable methodParamsTable = buildMethodParamConflicts(java_methods);
      
      Symbol[] propnames = new Symbol[5];
      Object[] propvalues = new Object [5];
      Sequence ret_val = new Sequence();
      Symbol G2_static_name;
      for (int i=0; i<java_methods.length; i++)
	if (recurse || (!recurse && (java_methods[i].getDeclaringClass()) == beanClass)) {
	  String javaMethodName = java_methods[i].getName();
	  Symbol G2_method_name_sym = G2ClassTranslator.createG2NameFromJavaName(javaMethodName);
	  String G2_method_name = G2_method_name_sym.toString(); 
	  G2_method_name = G2ClassTranslator.checkAndReMapAttributeNames(G2_method_name);
	  G2_method_name_sym = Symbol.intern(G2_method_name.toUpperCase());
	  
	  if (!G2_method_name.equals("<CLINIT>")) // Hack too loose <clinit> when looking at interfaces
	    {
	      
	      // Get the parameter classes
	      parameter_classes = java_methods[i].getParameterTypes();
	      
	      // Can not have same G2 class method with same number of attributes
	      Hashtable methodParams = (Hashtable)methodParamsTable.get(java_methods[i].getName());
	      Integer numParams = parameter_classes.length;
	      Integer numParamsForThisMethodSig = (Integer)methodParams.get(numParams);
	      boolean includeThisMethod = true;
	      boolean methodParamConflict = false;
	      if (numParamsForThisMethodSig == null)
		includeThisMethod = false;
	      else {
		methodParamConflict = numParamsForThisMethodSig.intValue() > 1;
		// signal that we have already generated a method with this name and number of parameters
		methodParams.remove(numParams); 
	      }
	      
	      String declaring_class = java_methods[i].getDeclaringClass().getName();
	      
	      String static_method;
	      boolean is_static;
	      if (Modifier.isStatic(java_methods[i].getModifiers()))
		{
		  static_method = "STATIC";
		  is_static = true;
		  // Static are methods on the class-definition and therefore may conflict
		  // with other statics, always play safe
		  //methodParamConflict = true;
		}
	      else
		{
		  static_method = "";
		  is_static = false;
		  G2_static_name = NONE_;
		}
	      
	      // Make sure the java method description is not too large
	      String java_method_descr = java_methods[i].toString();
	      
	      G2_method_text = "{ G2 Stub for Java " + static_method + " Method \n " +
		java_method_descr + "}\n\n" + 
		G2_method_name + (is_static ? 
		 "( self: class " + G2_mangled_class_name + "_definition, interface : CLASS OBJECT" :
		 "( self: class " + G2_mangled_class_name);
	      
	      // need interface if this is a static call, as we dont have
	      // a valid class instance
	      G2_args_text = "";
	      String G2_pars_text = "";
	      String G2_nontyped_pars_text = "";
	      Sequence parameterTypesTextSeq = new Sequence(parameter_classes.length);
	      bad_method = false;
	      
	      // parameter types
	      for (int y=0; y<parameter_classes.length; y++)
		{
		  parameterTypesTextSeq.addElement(parameter_classes[y].getName());
		  String G2_type = G2ClassTranslator.getG2TypeFromJavaClass(parameter_classes[y]);
		  if (G2_type == null){
			  G2_type = getG2Type(parameter_classes[y], beanClass, G2_mangled_class_name);
		  }
		  String G2_par_name = "par"+(y);
		  G2_pars_text = G2_pars_text + ",\n" + G2_par_name +  " : " + G2_type;
		  G2_nontyped_pars_text = G2_nontyped_pars_text + ",\n" + G2_par_name +  " : ITEM-OR-VALUE";
		  if ( parameter_classes.length == 1 ){
		    G2_args_text = G2_args_text + G2_par_name;
		  } else {
		    if (y < parameter_classes.length - 1){
		      G2_args_text = G2_args_text + G2_par_name + ",";
		    } else {
		      G2_args_text = G2_args_text + G2_par_name;
		    }
		  }
		}
	      
	      boolean isG2EventObjectMethod = 
		(isG2EventListenerClass && 
		 parameter_classes.length == 1 &&
		 isClassInstanceOf(parameter_classes[0],ROOT_G2_EVENT_OBJECT_CLASS_NAME));

	      // return types
	      return_class = java_methods[i].getReturnType();
	      //System.out.println("return class is" + return_class);
	      
	      boolean return_type_is_proxy = false;
	      String return_type;
	      
	      if (return_class == null)
    		return_type = "";
	      else {
		return_type = G2ClassTranslator.getG2ReturnTypeFromjavaClass(return_class);
		
		// need to stop proxy production
		if (return_type == null) 
		  return_type = getG2Type(return_class, beanClass, G2_mangled_class_name);
		
		if (return_type.indexOf("CLASS") > -1) {
		  // Must change all [ to @[
		  String className = return_class.getName();
		  StringBuffer mangledClassName;
		  if (className.charAt(0) == '[') {
		    mangledClassName = new StringBuffer(className.length());
		    for (int x = 0; x<className.length(); x++) {
		      char ch = className.charAt(x);
		      if (ch == '[') 
			mangledClassName.append('@');
		      mangledClassName.append(ch);
		    }
		  } else
		    mangledClassName = new StringBuffer(className);
		}
		
	      }
	      
	      String G2_method_declaration; 
	      // Declarative text of this method visible to the user, should 
	      // therefore contain the correct parameter types, even if the args are actually nontyped
	      if (methodParamConflict) {
		G2_method_declaration = G2_method_text + G2_pars_text;
		G2_method_text = G2_method_text + G2_nontyped_pars_text;
	      } else {
		G2_method_text = G2_method_text + G2_pars_text;
		G2_method_declaration = G2_method_text;
	      }
	      G2_method_text = G2_method_text + " ) = ( " + return_type + " )\n";
	      G2_method_declaration = G2_method_declaration + " ) = ( " + return_type + " )\n";

	      String seq_text = "   args = Sequence (" + G2_args_text +");";
	      
	      String call_text, relate_text;
	      if (is_static)
		{
		  call_text =  "CALL " + G2_jgi_RPC_static_name
		    + "(self, interface, \"" + java_methods[i].getName() + "\"" 
		    + (methodParamConflict ? "" : ",this procedure")
		    + ",args); ";
		  relate_text = proxy_static_relate_text;
		}
	      else
		{
		  if (!isG2EventObjectMethod)
		    call_text =  "CALL " + G2_jgi_RPC_name
		      + "(self, \"" + java_methods[i].getName() + "\""
		      + (methodParamConflict ? "" : ",this procedure")  
		      + ",args); ";
		  else 
		    call_text =  "CALL " +jgiG2CallG2ItemListenerRpcName.toString()
		      + "(self, \"" + java_methods[i].getName() + "\""
		      + (methodParamConflict ? "" : ",this procedure")  
		      + ",par0, true); "; // true == default to asynch dispatch

		  // note: if methodParamConflict is true then one G2 method will
		  //       be used for multiple java methods (same name, number but different param types)
		  //       In the case we can not use "this procedure" to use as a specific methods reference
		  
		  relate_text = proxy_relate_text;
		}
	      
	      
	      if (return_type.equals(""))
		{ // no return
		  G2_method_text = G2_method_text + "\nargs: Sequence; \n"+ 
		    "\nBEGIN \n" +
		    seq_text +
		    "\n  " + call_text +    // internal dispose name also needs to get called
		    ((parameter_classes.length == 0 && G2_method_name_sym.equals(jgiG2DisposeMethodName)) ?
		     "call " + jgiG2FullDisposeMethodName + "(self);\n" : "") +  
		    "\nEND";
		}
	      else
		{
		  
		  G2_method_text = G2_method_text +
		    "\nret_val : " + return_type +
		    ";\nargs: Sequence; \nBEGIN \n" +
		    seq_text +
		    " \n " +
		    " \n  ret_val = " + call_text +
		    (return_type_is_proxy ? relate_text :  "") +
		    "\n return ret_val; \nEND";
		}
	      
	      if (bad_method)
		G2_method_text = "BAD-" + G2_method_name +
		  "()=() begin end \n { ** AN ERROR WAS FOUND DURING STUB GENERATION **\n" +
		  G2_method_text + "\n }";
	      
	      propnames[0]= METHOD_NAME_ ; 
	      propvalues[0] = G2_method_name_sym;
	      propnames[1]= METHOD_TEXT_; 
	      propvalues[1] = (includeThisMethod ? G2_method_text : "");
	      propnames[2]= METHOD_DECLARATION_; 
	      propvalues[2] = G2_method_declaration;
	      propnames[3]= STATIC_DEFINITION_;  
	      propvalues[3] = new Boolean(is_static);
	      propnames[4]= JAVA_PARAMETER_TYPES_; 
	      propvalues[4] = parameterTypesTextSeq;
	      
	      Structure G2_method_information = new Structure ( propnames , propvalues);
	      
	      ret_val.addElement( G2_method_information );
	      
	    }
	}
      
      return ret_val;
      
    } catch (NtwIllegalArgumentException e) {
    	e.printStackTrace();
    	throw new G2StubCreationException(
    			"The following Exception was raised while constructing G2 stubs for Java class " +
    		    beanClass.getName() + "\n" + e.toString());
    } catch (ClassNotFoundException e) {
    	e.printStackTrace();
    	throw new G2StubCreationException(
    			"The following Exception was raised while constructing G2 stubs for Java class " +
    			beanClass.getName() + "\n" + e.toString());
    } catch (RuntimeException e) {
    	e.printStackTrace();
    	throw new G2StubCreationException(
    			"The following Exception was raised while constructing G2 stubs for Java class " +
    			beanClass.getName() + "\n" + e.toString());
    }
  }
  

 public Sequence getG2StubsForWrapper (Class beanClass, Symbol G2_class_name, boolean recurse)
       throws ClassNotFoundException,
	      G2StubCreationException
  {
    
    try {
      
      String G2_method_text;
      String G2_args_text;
      String G2_jgi_RPC_name = jgiG2CallRpcName.toString();
      String G2_jgi_RPC_static_name = jgiG2CallStaticRpcName.toString();
      String proxy_static_relate_text = "conclude that interface is the-jgi-interface-of ret_val;";
      String proxy_relate_text = "conclude that the gsi-interface that is the-jgi-interface-of self is the-jgi-interface-of ret_val;";
      Class parameter_classes[];
      Hashtable existing_method_calls = new Hashtable(); // Method names must be unique
      Class return_class;
      boolean bad_method;
      String G2_mangled_class_name = G2_class_name.toString();
      Symbol beanClassName_ = G2_class_name; //G2ClassTranslator.getBeanClassNameForG2ProxyClassName (G2_class_name);
      String beanClassName = beanClassName_.getPrintValue ();
      
      //Class stopBefore = Class.forName("java.awt.Component");
      //BeanInfo bi = Introspector.getBeanInfo(beanClass , null );
      
      // Use reflection to get the methods
      Method java_methods[] = beanClass.getMethods();
      Hashtable methodParamsTable = buildMethodParamConflicts(java_methods);
      
      Symbol[] propnames = new Symbol[5];
      Object[] propvalues = new Object [5];
      Sequence ret_val = new Sequence();
      Symbol G2_static_name;
      for (int i=0; i<java_methods.length; i++)
	if (recurse || (!recurse && (java_methods[i].getDeclaringClass()) == beanClass)) {
	  String javaMethodName = java_methods[i].getName();
	  Symbol G2_method_name_sym = G2ClassTranslator.createG2NameFromJavaName(javaMethodName);
	  String G2_method_name = G2_method_name_sym.toString(); 
	  G2_method_name = G2ClassTranslator.checkAndReMapAttributeNames(G2_method_name);
	  G2_method_name_sym = Symbol.intern(G2_method_name.toUpperCase());
	  
	  if (!G2_method_name.equals("<CLINIT>")) // Hack too loose <clinit> when looking at interfaces
	    {
	      
	      // Get the parameter classes
	      parameter_classes = java_methods[i].getParameterTypes();
	      
	      // Can not have same G2 class method with same number of attributes
	      Hashtable methodParams = (Hashtable)methodParamsTable.get(java_methods[i].getName());
	      Integer numParams = parameter_classes.length;
	      Integer numParamsForThisMethodSig = (Integer)methodParams.get(numParams);
	      boolean includeThisMethod = true;
	      boolean methodParamConflict = false;
	      if (numParamsForThisMethodSig == null)
		includeThisMethod = false;
	      else {
		methodParamConflict = numParamsForThisMethodSig.intValue() > 1;
		// signal that we have already generated a method with this name and number of parameters
		methodParams.remove(numParams); 
	      }
	      
	      String declaring_class = java_methods[i].getDeclaringClass().getName();
	      
	      String static_method;
	      boolean is_static;
	      if (Modifier.isStatic(java_methods[i].getModifiers()))
		{
		  static_method = "STATIC";
		  is_static = true;
		  // Static are methods on the class-definition and therefore may conflict
		  // with other statics, always play safe
		  //methodParamConflict = true;
		}
	      else
		{
		  static_method = "";
		  is_static = false;
		  G2_static_name = NONE_;
		}
	      
	      // Make sure the java method description is not too large
	      String java_method_descr = java_methods[i].toString();
	      
	      G2_method_text = "{ G2 Stub for Java " + static_method + " Method \n " +
		java_method_descr + "}\n\n" + 
		G2_method_name + (is_static ? 
		 "( self: class " + G2_mangled_class_name + "_definition, interface : CLASS OBJECT" :
		 "( self: class " + beanClassName);
	      
	      // need interface if this is a static call, as we dont have
	      // a valid class instance
	      G2_args_text = "";
	      String G2_pars_text = "";
	      String G2_nontyped_pars_text = "";
	      Sequence parameterTypesTextSeq = new Sequence(parameter_classes.length);
	      bad_method = false;
	      
	      // parameter types
	      for (int y=0; y<parameter_classes.length; y++)
		{
		  parameterTypesTextSeq.addElement(parameter_classes[y].getName());
		  String G2_type = G2ClassTranslator.getG2TypeFromJavaClass(parameter_classes[y]);
		  if (G2_type == null){
			  G2_type = getG2Type(parameter_classes[y], beanClass, G2_mangled_class_name);
		  }
		  String G2_par_name = "par"+(y);
		  G2_pars_text = G2_pars_text + ",\n" + G2_par_name +  " : " + G2_type;
		  G2_nontyped_pars_text = G2_nontyped_pars_text + ",\n" + G2_par_name +  " : ITEM-OR-VALUE";
		  if ( parameter_classes.length == 1 ){
		    G2_args_text = G2_args_text + G2_par_name;
		  } else {
		    if (y < parameter_classes.length - 1){
		      G2_args_text = G2_args_text + G2_par_name + ",";
		    } else {
		      G2_args_text = G2_args_text + G2_par_name;
		    }
		  }
		}
	      
	      // return types
	      return_class = java_methods[i].getReturnType();
	      //System.out.println("return class is" + return_class);
	      
	      boolean return_type_is_proxy = false;
	      String return_type;
	      
	      if (return_class == null)
    		return_type = "";
	      else {
		return_type = G2ClassTranslator.getG2ReturnTypeFromjavaClass(return_class);
		
		// need to stop proxy production
		if (return_type == null) 
		  return_type = getG2Type(return_class, beanClass, G2_mangled_class_name);
		
		if (return_type.indexOf("CLASS") > -1) {
		  // Must change all [ to @[
		  String className = return_class.getName();
		  StringBuffer mangledClassName;
		  if (className.charAt(0) == '[') {
		    mangledClassName = new StringBuffer(className.length());
		    for (int x = 0; x<className.length(); x++) {
		      char ch = className.charAt(x);
		      if (ch == '[') 
			mangledClassName.append('@');
		      mangledClassName.append(ch);
		    }
		  } else
		    mangledClassName = new StringBuffer(className);
		}
		
	      }
	      
	      String G2_method_declaration; 
	      // Declarative text of this method visible to the user, should 
	      // therefore contain the correct parameter types, even if the args are actually nontyped
	      if (methodParamConflict) {
		G2_method_declaration = G2_method_text + G2_pars_text;
		G2_method_text = G2_method_text + G2_nontyped_pars_text;
	      } else {
		G2_method_text = G2_method_text + G2_pars_text;
		G2_method_declaration = G2_method_text;
	      }
	      G2_method_text = G2_method_text + " ) = ( " + return_type + " )\n";
	      G2_method_declaration = G2_method_declaration + " ) = ( " + return_type + " )\n";
	      
	      String seq_text = "   args = Sequence (" + G2_args_text +");";
	      
	      String call_text, relate_text;
	      if (is_static)
		{
		  call_text =  "CALL " + G2_jgi_RPC_static_name
		    + "(self, interface, \"" + java_methods[i].getName() + "\"" 
		    + (methodParamConflict ? "" : ",this procedure")
		    + ",args); ";
		  relate_text = proxy_static_relate_text;
		}
	      else
		{
		  call_text =  "CALL " + G2_jgi_RPC_name
		    + "(self, \"" + java_methods[i].getName() + "\""
		    + (methodParamConflict ? "" : ",this procedure")  
		    + ",args); ";
		  // note: if methodParamConflict is true then one G2 method will
		  //       be used for multiple java methods (same name, number but different param types)
		  //       In the case we can not use "this procedure" to use as a specific methods reference
		  
		  relate_text = proxy_relate_text;
		}
	      

	      int numMethodParams = parameter_classes.length;
	      StringBuffer params = new StringBuffer (numMethodParams*4);
	      for (int m=0; m<numMethodParams; m++)
		params.append (", par").append (m);

	      if (return_type.equals(""))
		{ // no return
		  G2_method_text +=
		    "\nBEGIN\n\n    call " +
		    VOID_DISPATCH_METHOD +
		    "(self, the symbol " + G2_method_name_sym +
		    params + ");\n\nEND";
		}
	      else
		{
		  G2_method_text +=
		    "\nret_val : " + return_type +
		    ";\n\nBEGIN\n\n    ret_val = call " +
		    DISPATCH_METHOD_WITH_RETURN +
		    "(self, the symbol " + G2_method_name_sym +
		    params + ");\n    return ret_val;\n\nEND";
		}
	      
	      if (bad_method)
		G2_method_text = "BAD-" + G2_method_name +
		  "()=() begin end \n { ** AN ERROR WAS FOUND DURING STUB GENERATION **\n" +
		  G2_method_text + "\n }";
	      
	      propnames[0]= METHOD_NAME_ ; 
	      propvalues[0] = G2_method_name_sym;
	      propnames[1]= METHOD_TEXT_; 
	      propvalues[1] = (includeThisMethod ? G2_method_text : "");
	      propnames[2]= METHOD_DECLARATION_; 
	      propvalues[2] = G2_method_declaration;
	      propnames[3]= STATIC_DEFINITION_;  
	      propvalues[3] = new Boolean(is_static);
	      propnames[4]= JAVA_PARAMETER_TYPES_; 
	      propvalues[4] = parameterTypesTextSeq;
	      
	      Structure G2_method_information = new Structure ( propnames , propvalues);
	      
	      ret_val.addElement( G2_method_information );
	      
	    }
	}
      Structure classInfo = new Structure ();
      classInfo.setAttributeValue (METHOD_NAME_, CLASS_INFO_);
      classInfo.setAttributeValue (IS_ABSTRACT_, new Boolean (Modifier.isAbstract (beanClass.getModifiers())));
      classInfo.setAttributeValue (METHOD_TEXT_, "");
      classInfo.setAttributeValue (METHOD_DECLARATION_, "");
      classInfo.setAttributeValue (STATIC_DEFINITION_, Boolean.TRUE);
      classInfo.setAttributeValue (JAVA_PARAMETER_TYPES_, new Sequence ());
      ret_val.addElement (classInfo);
      return ret_val;
      
    } catch (NtwIllegalArgumentException e) {
    	e.printStackTrace();
    	throw new G2StubCreationException(
		 "The following Exception was raised while constructing G2 stubs for Java class " +
		 beanClass.getName() + "\n" + e.toString());
    } catch (RuntimeException e)
    {
    	e.printStackTrace();
    	throw new G2StubCreationException(
		 "The following Exception was raised while constructing G2 stubs for Java class " +
		 beanClass.getName() + "\n" + e.toString());
    }
  }

  /**
   * Construct G2 stubs for the public constructors of a Java class
   */
 public Sequence getG2StubsForConstructors(Class the_class, Symbol G2_class_name)
       throws G2StubCreationException
  {
    try {

      String G2_method_name;
      String G2_method_text;
      String G2_args_text;
      String G2_jgi_RPC_name = jgiG2CreateProxyName.toString();
      String G2_jgi_RPC_start_name = "NEW";
      Class parameter_classes[];
      Hashtable existing_method_calls = new Hashtable(); // Method names must be unique
      boolean bad_method;
      
      String G2_mangled_class_name = G2_class_name.toString();


      // Use reflection to get the methods
      Constructor java_constructors[] = the_class.getConstructors();

      Symbol[] propnames = new Symbol[4];
      Object[] propvalues = new Object [4];

      Sequence ret_val = new Sequence();

      Hashtable methodParamsTable = buildMethodParamConflicts(java_constructors);

      for (int i=0; i<java_constructors.length; i++)
	{
	  // declaration
	  G2_method_name = G2_jgi_RPC_start_name;
	  // Get the parameter classes
	  parameter_classes = java_constructors[i].getParameterTypes();

	  // Can not have same G2 class method with same number of attributes
	  Hashtable methodParams = (Hashtable)methodParamsTable.get(java_constructors[i].getName());
	  Integer numParams = parameter_classes.length;
	  Integer numParamsForThisMethodSig = (Integer)methodParams.get(numParams);
	  boolean includeThisMethod = true;
	  boolean methodParamConflict = false;
	  if (numParamsForThisMethodSig == null)
	    includeThisMethod = false;
	  else {
	    methodParamConflict = numParamsForThisMethodSig.intValue() > 1;
	    // signal that we have already generated a method with this name and number of parameters
	    methodParams.remove(numParams); 
	  }

	  // Make sure the java method description is not too large
	  String java_method_descr = java_constructors[i].toString();
	  if (java_method_descr.length() > 140)
	    java_method_descr = java_method_descr.substring(0,java_method_descr.length()/2) + "\n" +
	      java_method_descr.substring(java_method_descr.length()/2);


	  G2_method_text = "{ G2 Stub for java constructor \n "+
                            java_method_descr + "}\n\n"+
                            G2_method_name  + "( class : CLASS " + G2_mangled_class_name + "_definition" + 
                            ", interface: CLASS OBJECT";
	  G2_args_text = "";
	  bad_method = false;
	  String G2_pars_text = "";
	  String G2_nontyped_pars_text = "";
	  Sequence parameterTypesTextSeq = new Sequence(parameter_classes.length);
	  // parameter types
	  for (int y=0; y<parameter_classes.length; y++) {
	      parameterTypesTextSeq.addElement(parameter_classes[y].getName());
	      String G2_type = G2ClassTranslator.getG2TypeFromJavaClass(parameter_classes[y]);
	      if (G2_type == null) {
	    	  G2_type = getG2Type(parameter_classes[y], the_class, G2_mangled_class_name);
	      }

	      String G2_par_name = "par"+(y);
	      G2_pars_text = G2_pars_text + ",\n" + G2_par_name +  " : " + G2_type;
	      G2_nontyped_pars_text = G2_nontyped_pars_text + ",\n" + G2_par_name +  " : ITEM-OR-VALUE";
	      if ( parameter_classes.length == 1 ){
    		G2_args_text = G2_args_text + G2_par_name;
	      }
	      else {
		if (y < parameter_classes.length - 1){
		  G2_args_text = G2_args_text + G2_par_name + ",";
		} else {
		  G2_args_text = G2_args_text + G2_par_name;
		}

	      }
	  }
	  String G2_method_declaration = "";
	  // Declarative text of this method visible to the user, should 
	  // therefore contain the correct parameter types, even if the args are actually nontyped
	  if (methodParamConflict) {
	    G2_method_declaration = G2_method_text + G2_pars_text;
	    G2_method_text = G2_method_text + G2_nontyped_pars_text;
	  } else {
	    G2_method_text = G2_method_text + G2_pars_text;
	    G2_method_declaration = G2_method_text;
	  }
	  G2_method_text = G2_method_text + " ) = ( CLASS " + G2_mangled_class_name + "  )\n";
	  G2_method_declaration = G2_method_declaration + " ) = ( CLASS " + G2_mangled_class_name + ")\n";

	  // guts
	  String array_text = "   args = Sequence (" + G2_args_text +");";

	  G2_method_text = G2_method_text
	    + "\nret: class " + G2_mangled_class_name + ";\nargs: sequence; \nBEGIN \n"
            + array_text
	    + " \n  ret = CALL " + G2_jgi_RPC_name + "(class, interface, args);\n"
            + " \n  return ret;" 
            + "\nEND";

	  if (bad_method)
	    G2_method_text = "BAD-" + G2_method_name
	      + "()=() begin end \n { ** AN ERROR WAS FOUND DURING STUB GENERATION **\n"
	      + G2_method_text + "\n }";

	  propnames[0]= METHOD_NAME_; 
	  propvalues[0] = jgiG2CallRpcName;
	  propnames[1]= METHOD_TEXT_; 
	  propvalues[1] = (includeThisMethod ? G2_method_text : "");
	  propnames[2]= METHOD_DECLARATION_;
	  propvalues[2] = G2_method_declaration;
	  propnames[3]= JAVA_PARAMETER_TYPES_; 
	  propvalues[3] = parameterTypesTextSeq;

	  Structure G2_method_information = new Structure ( propnames , propvalues);

	  ret_val.addElement( G2_method_information );

	}
      return ret_val;
    } catch (NtwIllegalArgumentException e) {
    	throw new G2StubCreationException(
	      "The following Exception was raised while constructing G2 stubs for Constructor for "
              + the_class.getName() + "\n" + e.toString());
    } catch (RuntimeException e) {
    	throw new G2StubCreationException(
	      "The following Exception was raised while constructing G2 stubs for Constructor for "
            + the_class.getName() + "\n" + e.toString());
   }
  }

  // Runtime lookup of a class, as we cant rely on user classes begin
  // around during BOOTSTRAPPING class download from G2.
  boolean isClassInstanceOf(Class lowerClass, String superClassName) throws ClassNotFoundException {
      Class superClass = Class.forName(superClassName);
      return superClass.isAssignableFrom(lowerClass);
  }

  /** 
   * returns a table listing for each method a table that lists the number of signatures that have the same
   * number of parameters
   */
  private static Hashtable buildMethodParamConflicts(Member[] methods) {
    Hashtable methodParamConflicts = new Hashtable(21);
    for (int i=0; i<methods.length; i++) {
      String methodName = methods[i].getName();
      Class[] paramTypes;
      if (methods[i] instanceof Method) 
	paramTypes = ((Method)(methods[i])).getParameterTypes();
      else
	paramTypes = ((Constructor)(methods[i])).getParameterTypes();
      Integer numparams = paramTypes.length;
      Hashtable methodSigs = (Hashtable)methodParamConflicts.get(methodName);
      if (methodSigs == null) {
	methodSigs = new Hashtable(2);
	methodSigs.put(numparams, 1);
	methodParamConflicts.put(methodName, methodSigs);
      } else {
	Integer numParamsCount = (Integer)methodSigs.get(numparams);
	if (numParamsCount == null) 
	  methodSigs.put(numparams, 1);
	else
	  methodSigs.put(numparams, numParamsCount.intValue() + 1);
      }
    }
    return methodParamConflicts;
  }

  private static String getG2Type(Class param_class,  
			   Class thisClass,
			   String thisG2ClassName) {


    String G2_type = "";

    // We know are own class, as we have created a proxy for it
    if ( param_class == thisClass)
      G2_type = "CLASS " + thisG2ClassName;
    else {

      String paratype = param_class.getComponentType() == null ? 
	param_class.getName() :
	getArrayComponent(param_class).getName()+ "@[@]";

      G2_type="CLASS "+ G2ClassTranslator.createG2NameFromJavaName(paratype);

    }

    return G2_type;
  }

  /** Find actual type for multi-dimensional arrays */
  static Class getArrayComponent(final Class java_class) {
	Class javaClass = java_class;
    while (javaClass.isArray()) {
      javaClass = javaClass.getComponentType();
    }

    return javaClass;
  }		   


}
