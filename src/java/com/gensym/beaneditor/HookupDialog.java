package com.gensym.beaneditor;

import java.awt.*;
import java.util.*;
import java.awt.event.*;
import java.beans.*;
import java.lang.reflect.*;
import com.gensym.dlg.*;
import com.gensym.message.Trace;
import com.gensym.util.QuickSorter;

class HookupDialog implements StandardDialogClient {

  private Object             targetBean;
  private Object             sourceBean;
  private EventInfo          eventInfo;
  private Method             listenerMethod;
  private int                syntax;
  private MethodDescriptor   targetDescs[];
  private Vector             matchMethods = new Vector();
  private EventSetDescriptor esd;
  private Object             hookup = null;
  private Wrapper            sourceWrapper = null;
  private Wrapper            targetWrapper = null;
  private Port               port = null;
  private Frame              frame = null;

  Choice eventChoice = new Choice();

  private String methodName;

  HookupDialog (Wrapper targetWrapper, Port port,
		Frame frame, int syntax) 
  {	       
    targetBean     = targetWrapper.getBean();
    sourceWrapper  = port.getWrapper();
    sourceBean     = sourceWrapper.getBean();
    eventInfo      = port.getEventInfo();
    listenerMethod = eventInfo.method;
    this.targetWrapper = targetWrapper;
    this.port      = port;
    this.syntax    = syntax;
    // find the EventSetDescriptor that corresponds to the listener method

    EventSetDescriptor[] eventSetDescriptors = null; 

    try {
      eventSetDescriptors = Introspector.getBeanInfo
	(sourceBean.getClass()).getEventSetDescriptors();
    } catch (Exception e) {
      Trace.exception (e, null);
    }

    String  listenerName = listenerMethod.getName();
    /*
      System.out.println ("listenerName = " + listenerName +
      "\nsourceBean = " + sourceBean.getClass () +
      "\nBean       = " + targetBean);
      */

    boolean found = false;

    for (int i=0; i < eventSetDescriptors.length ; i++) {
      esd = eventSetDescriptors[i];
      //System.out.println ("Esd = " + esd);
      
      MethodDescriptor[] methodDescriptors = esd.getListenerMethodDescriptors();
      
      for (int j = 0; j < methodDescriptors.length ; j++) {
	MethodDescriptor mDesc = methodDescriptors[j];
	
	if (listenerName.equals((mDesc.getMethod()).getName())) {
	  found = true;
	  //System.out.println ("Found Method = " + mDesc);
	  break;
	}                 
      }
      
      if (found)
	break;
    }
    
    // build the event choices
    Class eventArgs[] = listenerMethod.getParameterTypes();
    Preferences preferences = Preferences.currentPreferences;
    
    try {
      BeanInfo beanInfo = Introspector.getBeanInfo(targetBean.getClass());
      targetDescs = beanInfo.getMethodDescriptors();
      PropertyDescriptor[] propertyDescs = beanInfo.getPropertyDescriptors();
      int p, plength = propertyDescs.length;
      EventSetDescriptor[] eventSetDescs = beanInfo.getEventSetDescriptors();
      int e, elength = eventSetDescs.length;
            
      for (int i = 0; i < targetDescs.length; i++) {
	Method method = targetDescs[i].getMethod();
	Class targetArgs[] = method.getParameterTypes();
	Class returnType = method.getReturnType ();
	
	boolean signatureMatches = true;
	switch (syntax)
	  {
	  case HookupFactory.AUTOMATIC_EXACT:
	    if (returnType == Void.TYPE) {
	      signatureMatches = (targetArgs.length == eventArgs.length); // until proven otherwise. t=0 -> true
	      for (int t=0; t<targetArgs.length; t++) {
		if (targetArgs[t] != eventArgs[t]) {
		  signatureMatches = false;
		  break;
		}
	      }
	    } else
	      signatureMatches = false;
	    break;
	  case HookupFactory.AUTOMATIC:
	    signatureMatches = (preferences.isExpertMode() || !targetDescs[i].isExpert());

	    if (!signatureMatches) //non-expert mode->include non-expert accessors
	      {
		boolean isPropertyAccessor = false;
		for (p=0; p<plength ; p++)
		  {
		    PropertyDescriptor property = propertyDescs[p];
		    if (!property.isExpert() && 
			(method.equals(property.getReadMethod()) ||
			 method.equals(property.getWriteMethod())))
		      {
			signatureMatches = true;
			break;
		      }
		  }
	      }
	    break;
	  case HookupFactory.JAVA:
	  case HookupFactory.G2SCRIPT:
	    if (!preferences.isExpertMode())
	      {
		boolean isAddRemoveListenerMethod = false;
		for (e=0; e<elength; e++)
		  {
		    EventSetDescriptor eventSet = eventSetDescs[e];
		    if (method.equals(eventSet.getAddListenerMethod()) ||
			method.equals(eventSet.getRemoveListenerMethod()))
		      {
			isAddRemoveListenerMethod = true;
			break;
		      }
		  }
		if (isAddRemoveListenerMethod)
		  signatureMatches = false;
	      }
	    break;
	  }
	
	if (signatureMatches) {
	  matchMethods.addElement(method);
	}
      }
    } catch (Exception e) {
      Trace.exception (e, null);
    }

    QuickSorter qs = 
      new QuickSorter ()
      {
	@Override
	public boolean lessThan(Object a, Object b)
	  {	    Method m1 = (Method) a;
	    Method m2 = (Method) b;
	    return m1.getName().toUpperCase().
	      compareTo(m2.getName().toUpperCase()) < 0;
	  }
      };
    qs.quickSortInPlace(matchMethods);
    int k,size = matchMethods.size();
    String[] methodNames = new String[size];
    String[] methodArguments = new String[size];
    String[] methodReturnTypes = new String[size];
    for (k=0; k<size ; k++)
      {
	Method methodChoice = (Method)matchMethods.elementAt(k);
	//if (preferences.isExpertMode() &&
	//  syntax != HookupFactory.AUTOMATIC)
	//methodNames[k] = makeDetailedMethodName(methodChoice);
	//else
	//methodNames[k] = methodChoice.getName();
	methodNames[k] = methodChoice.getName();
	methodArguments[k] = getMethodArguments(methodChoice);
	methodReturnTypes[k] = makeSimpleClassName(methodChoice.getReturnType());
      }

    if (syntax == HookupFactory.AUTOMATIC_EXACT) {
      if (methodNames.length == 0) {
	new com.gensym.dlg.WarningDialog (null, "No Match Found", true,
			   "No method exactly matches the arguments of the call",
			   null).setVisible (true);
      } else if (methodNames.length == 1)
	hookupToMethodAtIndex (0);
      else {
	SelectionDialog sd = new SelectionDialog (frame,
						  "Event Hookup: " + listenerMethod.getName (),
						  true,
						  "Choose target method:",
						  methodNames,
						  false, SelectionDialog.NO_SELECTION,
						  true,
						  this);
	sd.setVisible (true);
      }
    } else {      
      MultiColumnSelectionDialog o = 
	new MultiColumnSelectionDialog (frame,
					"Event Hookup: "+listenerMethod.getName(), // localize
					true,
					"Choose target method:", //localize
					new String[]{"Name", "Arguments", "Return Type"},
					new Object[]{methodNames, methodArguments, methodReturnTypes},
					false,
					MultiColumnSelectionDialog.NO_SELECTION,
					true,
					this);
      o.setVisible (true);
    }
  }

  private String makeDetailedMethodName(Method m)
  {
    StringBuffer buffer = new StringBuffer();
    buffer.append(m.getName()+" (");
    buffer.append(getMethodArguments(m));
    buffer.append(") -> "+makeSimpleClassName(m.getReturnType()));
    return buffer.toString();
  }

  private String getMethodArguments(Method m){
    StringBuffer buffer = new StringBuffer();
    Class[] parameterTypes = m.getParameterTypes();
    int i,length = parameterTypes.length;
    for (i=0; i<length ; i++)
      {
	if (i>0)
	  buffer.append(", ");
	buffer.append(makeSimpleClassName(parameterTypes[i]));
      }
    return buffer.toString();
  }

  private String makeSimpleClassName (Class c)
  {
    String name = c.getName();
    int lastIndex = name.lastIndexOf('.');
    if (lastIndex == -1)
      lastIndex = 0;
    else
      lastIndex++;
    return "<"+name.substring(lastIndex)+">";
  }

  @Override
  public synchronized void dialogDismissed (StandardDialog dlg, int cmdCode) {
    if (dlg.wasCancelled ())
      return;
    int chosenIndex;
    if (dlg instanceof MultiColumnSelectionDialog)
      chosenIndex = ((MultiColumnSelectionDialog)dlg).getResult ();
    else
      chosenIndex = ((SelectionDialog)dlg).getResult ();
    dlg.setVisible (false);
    hookupToMethodAtIndex (chosenIndex);
  }

  private void hookupToMethodAtIndex (int chosenIndex) {
    setMethodName(((Method)matchMethods.elementAt(chosenIndex)).getName()+"()");
    HookupCall hookupCall
      = new HookupCall((Method) matchMethods.elementAt (chosenIndex),
		       targetDescs[chosenIndex],
		       sourceWrapper,
		       targetWrapper);
    if (syntax == HookupFactory.AUTOMATIC ||
	syntax == HookupFactory.AUTOMATIC_EXACT) {
      //hookupCall.setupLegacyArguments();
      Class eventArgs[] = listenerMethod.getParameterTypes();
      Class eventType = null;
      if ((eventArgs != null) && (eventArgs.length > 0))
	eventType = eventArgs[0];//??is this right?(cmh)
      
      HookupArgument[] args = hookupCall.setupArguments(frame, eventType);
      if (args == null) return;
      hookupCall.arguments = args;
    }

    hookup = HookupFactory.generateHookup
      (esd, listenerMethod,
       sourceBean, targetBean,
       hookupCall,
       syntax,
       null,
       sourceWrapper.knownBeanNames(),
       sourceWrapper.knownBeans());
    if (hookup == null)
      return;
    else
      port.installNewHookup (hookup,esd,syntax,sourceBean);
  }

  
  public synchronized Object getHookup() {
    return hookup;
  }

  void setMethodName(String name){
    methodName = name;
    if (syntax == HookupFactory.AUTOMATIC_EXACT) {

    } else if (syntax == HookupFactory.AUTOMATIC) {
      methodName = name + "+";
    } else //if (syntax != HookupFactory.AUTOMATIC)
      methodName = name+"*";
  }

  String getMethodName(){
    return methodName;
  }
   
}
