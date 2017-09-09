package com.gensym.rules;

import java.beans.IntrospectionException;
import java.beans.Introspector;
import java.beans.BeanInfo; 
import java.beans.EventSetDescriptor; 
import java.lang.reflect.*;
import java.io.IOException;
import java.util.Hashtable;
import java.util.Vector;
import java.util.Enumeration;
import java.util.EventObject;
import java.rmi.RemoteException;

import com.gensym.classtools.*;

import com.gensym.g2scriptruntime.RegistrationEvent;
import com.gensym.g2scriptruntime.RegistrationListener;
import com.gensym.g2scriptruntime.DefaultNamingService;

// for testing 
import java.awt.*;
import java.awt.event.*;

public class Rule implements java.io.Serializable
{
  int ruleType;
  Condition[][] wheneverConditions; // disjuncts
  Condition[] filterConditions; // conjuncts, all must be instantiated
  static transient Hashtable installedConditions = new Hashtable();
  
  transient volatile RuleManager ruleManager;
  transient int ruleSerialNumber = 0;
  String instanceClassName;
  transient volatile Class cachedInstanceClass;
  static boolean debug = false;
  long scanInterval;
  String[] domainClassNames;
  transient Class[] domainClasses;
  String[] domainInstanceVariableNames;
  transient volatile int remoteRuleSerialNumber;                 // Both of these are set iff
  transient volatile RemoteRuleManager remoteRuleManager = null; // rule is being installed remotely
  transient RuleScanner scanner;
  transient volatile boolean installed = false;
  
  public static final int WHENEVER = 1;
  public static final int IF = 2;
  public static final int WHEN = 3;
  public static final int UNCONDITIONALLY = 4;

  public Rule(int ruleType,
	      Condition[][] wheneverConditions, 
	      Condition[] filterConditions,
	      String instanceClassName)
  {
    this.ruleType = ruleType;
    this.wheneverConditions = wheneverConditions;
    this.filterConditions = filterConditions;
    this.instanceClassName = instanceClassName;
  }

  /** Getter for scanInterval property.  
    Non-positive scan intervals indicate no scanning will be performed
   */
  public long getScanInterval()
  {
    return scanInterval;
  }

  /** Setter for scanInterval property.  
    Non-positive scan intervals indicate no scanning will be performed
   */
  public void setScanInterval(long scanInterval)
  {
    this.scanInterval = scanInterval;
  }

  synchronized void install()
  {
    try {
    // cache what can be cached and throw exceptions otherwise
    if (debug)
      System.out.println("installing rule "+this);
    try {
      getInstanceClass();  // will cache cachedInstanceClass
      int sIndex, cIndex,len;
      if (wheneverConditions != null)
	{
	  len = wheneverConditions.length;
	  for (sIndex=0; sIndex<len; sIndex++)
	    {
	      Condition[] conditionSet = wheneverConditions[sIndex];
	      for (cIndex = 0; cIndex<conditionSet.length ; cIndex++)
		installCondition(conditionSet[sIndex]);
	    }
	}
      if ((filterConditions != null) && (ruleType == IF))
	{
	  len = filterConditions.length;
	  for (cIndex=0; cIndex<len; cIndex++)
	    installCondition(filterConditions[cIndex]);
	}
      if ((scanInterval > 0) && (ruleType != WHENEVER))
	scanner = new RuleScanner(this,scanInterval);
    } 
    catch (IntrospectionException ie)
      {
	throw new RuntimeException("Install Rule failed, "+
				   "Introspection failure on condition."+
				   " Reason given: "+ie.getMessage());
      }
    installed = true;
    } catch (Exception e) {
      e.printStackTrace();
      throw new RuntimeException(e.toString());
    }
  }

  synchronized void uninstall()
  {
    // cache what can be cached and throw exceptions otherwise
    if (debug)
      System.out.println("uninstalling rule "+this);
    int sIndex, cIndex,len;
    if (wheneverConditions != null)
      {
	len = wheneverConditions.length;
	for (sIndex=0; sIndex<len; sIndex++)
	  {
	    Condition[] conditionSet = wheneverConditions[sIndex];
	    for (cIndex = 0; cIndex<conditionSet.length ; cIndex++)
	      uninstallCondition(conditionSet[sIndex]);
	  }
      }
    if ((filterConditions != null) && (ruleType == IF))
      {
	len = filterConditions.length;
	for (cIndex=0; cIndex<len; cIndex++)
	  uninstallCondition(filterConditions[cIndex]);
      }
    if (scanner != null)
      scanner.stop();
    installed = false;
  }

  Class getInstanceClass()
  {
    if (cachedInstanceClass != null)
      return cachedInstanceClass;
    else
      {
	try 
	  {
	    cachedInstanceClass 
	      = ruleManager.classManager.findInstanceClass(instanceClassName);
	    return cachedInstanceClass;
	  }
	catch (ClassNotFoundException e)
	  {
	    throw new RuntimeException("Install Rule failed, class "+
				       instanceClassName+ "not found");
	  }
      }
  }

  private void installCondition(Condition condition)
       throws IntrospectionException
  {
    if (debug)
      System.out.println("installing condition "+condition);
    condition.rule = this;
    Class conditionClass;
    try 
      { conditionClass = condition.getDomainClass();
      } catch (ClassNotFoundException cnfe)
	{
	  throw new RuntimeException("Install rule failed, "+condition.className+
				     " not found");
	}
    if (condition.canChain())
      {
	BeanInfo info = Introspector.getBeanInfo(conditionClass);
	EventSetDescriptor[] eventDescriptors = info.getEventSetDescriptors();
	boolean found = false;
	for (int i = 0; i<eventDescriptors.length; i++)
	  {
	    Method methods[] = eventDescriptors[i].getListenerMethods();
	    for (int j = 0; j<methods.length ; j++)
	      {
		if (methods[j].getName().equals(condition.eventName))
		  {
		    if (found)
		      throw new RuntimeException("Install Rule failed, "+
						 "duplicate listenerMethod: "+
						 condition.eventName);
						 
		    else
		      {
			condition.eventSetDescriptor = eventDescriptors[i];
			condition.listenerMethod = methods[j];
			found = true;
		      }
		  }
	      }
	  }
	if (!found)
	  throw new RuntimeException("Install Rule failed, no listenerMethod found for"+
				     condition.eventName);
	condition.adapterClass = getOrMakeAdapterClass(condition);
	if (debug)
	  System.out.println("installing "+condition+
			     " adapter will be "+condition.adapterClass);
	if (condition.adapterClass != null)
	  {
	    try {
	      condition.adapter = condition.adapterClass.newInstance();
	    } catch (InstantiationException ie)
	      {
		throw new RuntimeException("Install Rule failed, could not instantiate "+
					   condition.adapterClass);
	      }
	    catch (IllegalAccessException iae)
	      {
		throw new RuntimeException("Install RuleFailed, access protection problems"+
					   " while instantiating "+condition.adapterClass);
	      }
	    String key = condition.getOrMakeKey();
	    // Here, worry about next two lines.
	    installedConditions.put(key,condition);
	    condition.noteForClass();
	    Enumeration domain 
	      = ruleManager.namingService.lookup(conditionClass);
	    //System.out.println("Looking up domain for " + conditionClass);
	    RegistrationListener registrar 
	      = ruleManager.namingService.getRegistrationListener();
	    while (domain.hasMoreElements())
	      {
		RegistrationEvent event = new RegistrationEvent(this,domain.nextElement());
		registrar.registerObject(event);
	      }
	  }
      }
  }

  private void uninstallCondition(Condition condition)
  {
    if (condition.canChain())
      {
	String key = condition.getOrMakeKey();
	Condition installedCondition 
	  = (Condition) installedConditions.get(key);
	if (installedCondition != null)
	  {
	    Class conditionClass;
	    try {
	      conditionClass = installedCondition.getDomainClass();
	    } catch (ClassNotFoundException cnfe)
	      {
		// this is not going to happen if the condition was installed
		// in the first place
		throw new RuntimeException("Unexpected failure");
	      }
	    Enumeration domain 
	      = ruleManager.namingService.lookup(conditionClass);
	    RegistrationListener registrar 
	      = ruleManager.namingService.getRegistrationListener();
	    while (domain.hasMoreElements())
	      {
		RegistrationEvent event = new RegistrationEvent(this,domain.nextElement());
		registrar.deregisterObject(event);
	      }
	    condition.unnoteForClass();
	    installedConditions.remove(key);
	  }
      }
  }

  // De-install condition
  // 1 get adapter object
  // 2. and key;
  // 3. remove from installed conditions ht
  // 4. undo whatever not for class does

  private static String descriptorForType(Class type)
  {
    if (type == Integer.TYPE)
      return "I";
    else if (type == Long.TYPE)
      return "J";
    else if (type == Byte.TYPE)
      return "B";
    else if (type == Character.TYPE)
      return "C";
    else if (type == Short.TYPE)
      return "S";
    else if (type == Float.TYPE)
      return "F";
    else if (type == Double.TYPE)
      return "D";
    else if (type == Boolean.TYPE)
      return "Z";
    else if (type == Void.TYPE)
      return "V";
    else
      return "L"+type.getName().replace('.','/')+";";
  }
  
  private static String descriptorForMethod(Method method)
  {
    String descriptor = "(";
    Class[] parameterTypes = method.getParameterTypes();
    for (int i = 0; i<parameterTypes.length ; i++)
      descriptor += descriptorForType(parameterTypes[i]);
    return descriptor + ")"+descriptorForType(method.getReturnType());
  }

  
  private Class getOrMakeAdapterClass(Condition condition)
  {
    String packageName = ruleManager.classManager.getAdapterPackageName();
    String simpleClassName = condition.getOrMakeKey()+ "Adapter";
    String className = packageName + "." + simpleClassName;
    Class c = null;
    try 
      {
	c = ruleManager.classManager.findAdapterClass(className);
      }
    catch (ClassNotFoundException cnfe)
      {
	// do nothing - class will be generated
      }
    if (c == null)
      {
	try {
	  
	  ClassAccess access 
	    = new ClassAccess(RuntimeConstants.ACC_PUBLIC);
	  ClassInfo classInfo = new ClassInfo(access,
					      className,
					      "java.lang.Object",
					      true);
	  classInfo.add(new InterfaceInfo(condition.eventSetDescriptor.getListenerType()
					  .getName()));
	  Method methods[] = condition.eventSetDescriptor.getListenerMethods();
	  for (int i = 0; i < methods.length; i++)
	    {
	      int j;
	      Class argTypes[] = methods[i].getParameterTypes();
	      String[] argNames = new String[argTypes.length];
	      for (j = 0; j<argTypes.length ; j++)
		argNames[j] = "arg"+j;
	      String descriptor = descriptorForMethod(methods[i]);
	      Block block = new Block();
	      
	      if ((condition.listenerMethod.getName()).equals(methods[i].getName()))
		{
		  // created method fill forward object to rule engine by calling
		  // Rule.invokeRuleEngine(evt,"key");
		  MethodRef invokeMethodRef
		    = new MethodRef(
				    "com.gensym.rules.Rule",
				    "invokeRuleEngine",
				    "(Ljava/util/EventObject;Ljava/lang/String;)V");
		  Expression[] methodArgs = new Expression[2];
		  // event/ event set name / listener Method name
		  methodArgs[0] = new Variable(argNames[0],
					       descriptorForType(argTypes[0]));
		  methodArgs[1]
		    = condition.makeKeyBuilderExpression((Variable)methodArgs[0]);
		  // methodArgs[1] = new Value(eventDescriptor.getName());
		  // methodArgs[2] = new Value(listenerMethod.getName());
		  MethodCall invokeCall
		    = new MethodCall(invokeMethodRef, 
				     methodArgs,
				     RuntimeConstants.MTH_CALL_STATIC);
		  block.add(new ExpressionStatement(invokeCall));
		}
	      MethodRef methodRef = new MethodRef(className,methods[i].getName(),
						  descriptor);
	      block.add(new Return());
	      MethodInfo methodInfo = new MethodInfo(new Access(RuntimeConstants.ACC_PUBLIC),
						     methodRef,
						     block,
						     argNames,
						     new ClassRef[0]); // exceptions thrown
	      classInfo.add(methodInfo);
	    }
	  classInfo.emit();
	  if (debug)
	    classInfo.toStdout();
	  ruleManager.classManager.storeAdapterClass(simpleClassName,
						     classInfo.getBytes());
	}
	catch (ClassException ce)
	  {
	    System.out.println("Classtools-oriented failure to make rule adapter");
	    ce.printStackTrace();
	    return null;
	  }
	catch (IOException ioe)
	  {
	    System.out.println("Failed to write adapter class");
	    ioe.printStackTrace();
	    return null;
	  }
	try 
	  {
	    c = ruleManager.classManager.findAdapterClass(className);
	  }
	catch (ClassNotFoundException cnfe)
	  {
	    System.out.println("Adapter class "+className+"not found");
	    cnfe.printStackTrace();
	  }
	return c;
      }
    else
      return c;
  }

  // here 1. rule binding initialization
  //      2. the scanning thread
  
  public static void invokeRuleEngine(EventObject event, 
				      String key)
  {
    Condition condition = (Condition) installedConditions.get(key);
    if (condition != null)
      try 
      {
	Rule rule = condition.rule;
	if (debug)
	  System.out.println("would like to fire rule on "+key);
	if (!rule.installed)
	  return;
	// filterConditions is a hack until we fix up whenever rules
	if (rule.ruleType != WHENEVER)
	  rule.runAntecedents(rule.filterConditions,0,condition,event,
			      new Vector(), new Vector(), -1);
	else
	  rule.runWheneverAntecedents(condition,event);
      } catch (Exception e)
	{
	  e.printStackTrace();
	  System.out.println("could not fire rule");
	}
    else if (debug)
      System.out.println("invoking rule engine on bogus event "+key);
  }

  synchronized void runWheneverAntecedents(Condition condition, EventObject event)
       throws ClassNotFoundException, InstantiationException, NoSuchFieldException,
    IllegalAccessException
  {
    int conditionIndex = -1;
    for (int i = 0; i<wheneverConditions.length ; i++)
      {
	Condition[] conditionSet = wheneverConditions[i];
	boolean found = false;
	for (int j = 0; j<conditionSet.length; j++)
	  if (conditionSet[j].equals(condition))
	    {
	      found = true;
	      break;
	    }
	if (found)
	  {
	    conditionIndex = i;
	    break;
	  }
      }
    if (conditionIndex != -1)
      {
	Condition[] wheneverConditionSet = wheneverConditions[conditionIndex];
	Condition[] conditionsForAntecedent = new Condition[wheneverConditionSet.length +
							   filterConditions.length];
	System.arraycopy(wheneverConditionSet,0,conditionsForAntecedent,0,
			 wheneverConditionSet.length);
	System.arraycopy(filterConditions,0,conditionsForAntecedent,
			 wheneverConditionSet.length,filterConditions.length);
	runAntecedents(conditionsForAntecedent,0,
		       condition,event,
		       new Vector(), new Vector(),
		       conditionIndex);
      }
  }

  synchronized void runAntecedents(Condition[] conditions, 
		      int index,
		      Condition matchingCondition,  // These two may be null iff
		      EventObject event,            // called from scanning thread
		      Vector bindingNames,
		      Vector boundValues,
		      int wheneverConditionIndex)
       throws ClassNotFoundException, InstantiationException, NoSuchFieldException,
				IllegalAccessException
				
  {
    System.out.println("binding names "+bindingNames+" bound values "+boundValues);
    if (index == conditions.length)
      {
	if (debug)
	  System.out.println("would like to run antecedent of "+cachedInstanceClass);
	RuleInstance ruleInstance = (RuleInstance) cachedInstanceClass.newInstance();
	for (int i = 0; i<bindingNames.size(); i++)
	  {
	    if (debug)
	      System.out.println("  with "+bindingNames.elementAt(i)+
				 " = "+boundValues.elementAt(i));
	    Field field = cachedInstanceClass.getField((String)bindingNames.elementAt(i));
	    field.set(ruleInstance,boundValues.elementAt(i));
	  }
	if (((ruleType != WHENEVER) || ruleInstance.wheneverTest(wheneverConditionIndex)) &&
	    (ruleInstance.filter()))
	  {
	    if (remoteRuleManager == null)
	      {
		if (debug)
		  System.out.println("rule passed filter - firing locally");
		Thread thread = new Thread(ruleInstance);
		thread.start();
	      }
	    else
	      {
		try {
		  if (debug)
		    System.out.println("rule passed filter - firing remotely");
		  remoteRuleManager
		    .fireRemoteConsequent(remoteRuleSerialNumber,
					  new RuleEvent(remoteRuleManager,
							bindingNames,
							boundValues));
		} catch (RemoteException re)
		  {
		    System.out.println("remote exception firing to remoteConsequent "+
				       re.getMessage());
		    re.printStackTrace();
		  }
	      }
	  }
	else if (debug)
	  System.out.println("rule failed filter: condIndex = "+wheneverConditionIndex);
      }
    else
      {
	Condition condition = conditions[index];
	if (condition.equals(matchingCondition))
	  {
	    int size = bindingNames.size();
	    bindingNames.addElement(condition.bindingName);
	    boundValues.addElement(condition.getDomainValue(event));
	    condition.extendBindingsIfNecessary(event,bindingNames,boundValues);
	    runAntecedents(conditions,index+1,matchingCondition,event,
			   bindingNames,boundValues,wheneverConditionIndex);
	    condition.retractBindingsIfNecessary(event,bindingNames,boundValues);
	    bindingNames.removeElementAt(size);
	    boundValues.removeElementAt(size);
	  }
	else
	  {
	    Enumeration domain 
	      = ruleManager.namingService.lookup(condition.getDomainClass());
	    int size = bindingNames.size();
	    bindingNames.addElement(condition.bindingName);
	    boundValues.addElement(null);
	    while (domain.hasMoreElements())
	      {
		boundValues.setElementAt(domain.nextElement(),size);
		runAntecedents(conditions,index+1,matchingCondition,event,
			       bindingNames,boundValues,wheneverConditionIndex);
	      }
	    bindingNames.removeElementAt(size);
	    boundValues.removeElementAt(size);
	  }
      }
  }

  public static void main(String args[])
  {
    try {
      Condition[] conditions = new Condition[] { new Condition(null,
							       "java.awt.Component",
							       "mouseMoved") };
      Rule rule = new Rule(WHENEVER,new Condition[][] {conditions},
			   null,"com.gensym.rules.TestRuleInstance");
      rule.install();
      DefaultNamingService ns = new DefaultNamingService();
      RegistrationAdapter ra = new RegistrationAdapter();
      ns.setRegistrationListener(ra);
      
      Frame frame = new Frame();
      ns.put("Bob",frame);
      frame.setSize(600,600);
      frame.addWindowListener
	(
	 new WindowAdapter ()
	 {
	   @Override
	   public void windowClosing(WindowEvent e)
	     {
	       System.exit(0);
	     }
	 } ) ;
      
      frame.show();
    } catch (Exception e)
      {
	e.printStackTrace();
      }
  }
}


