
package com.gensym.util;

import java.lang.reflect.*;
import java.util.Vector;
import java.util.Arrays;
import java.util.Hashtable;

public class Dispatcher extends Object
{

  public void listMethods(String name, Object object)
  {
    Class start_class = object.getClass();
    Class the_class;

    for (the_class = start_class;
         the_class != null;
         the_class = the_class.getSuperclass())
      {
	Method[] methods
	  = the_class.getDeclaredMethods();
	int length = methods.length;

	for (int i = 0; i<length ; i++) 
	  {
	    if (methods[i].getName().equals(name))
	      System.out.println(methods[i]);
	  }
      }      

  }

  public static boolean isSubclass(Class c1, Class c2)
  {
    Class object_class = null;
    try {
      object_class = Class.forName("java.lang.Object");
    } catch (ClassNotFoundException e)
      {
        System.out.println("java.lang.Object class not found !!");
      }

    /* rule out primitive types */
    if (object_class.isAssignableFrom(c1) &&
        object_class.isAssignableFrom(c2))
      {
        Class the_class;

        for (the_class = c1;
             the_class != null;
             the_class = the_class.getSuperclass())
	  {
	    //System.out.println(the_class+" has super = "+
	    //	       the_class.getSuperclass());
	    if (the_class == c2){
	    	return true;
	    }
	  }
        return false;
      }
    else
      return false;
  }

  public static boolean memberIsMoreSpecific(Member m1, Member m2)
  {
    if (!(m2.getDeclaringClass().isAssignableFrom
	  (m1.getDeclaringClass())))
      return false;

    Class[] classes1, classes2;
    if (m1 instanceof Method) {
      classes1 = ((Method)m1).getParameterTypes();
      classes2 = ((Method)m2).getParameterTypes();
    } else {
       classes1 = ((Constructor)m1).getParameterTypes();
       classes2 = ((Constructor)m2).getParameterTypes();
    }
    int len = classes1.length;

    for (int i = 0; i<len ; i++)
      //      if (!(classes2[i].isAssignableFrom(classes1[i])))
      //      replaced by ML. 7/18/99
      if (!(isReallyAssignableFrom(classes2[i], classes1[i])))
	return false;
                        
    return true;
  }
  
  public Member findBestApplicableMember(Vector members)
  {
    Member best_member = null;
    Member candidate_member, other_member;
    int i,j,lim;
    lim = members.size();

    if (lim == 1)
      return (Member) members.elementAt(0);
    for (i=0; i<lim ; i++)
      {
	candidate_member = (Member) members.elementAt(i);
	boolean candidate_is_most_specific = true;
	for (j=0 ; j<lim ; j++) /* not the IDE */
	  {
	    if (i == j){
	    	continue;
	    }
	    other_member = (Member) members.elementAt(j);
        
	    if (!memberIsMoreSpecific(candidate_member,other_member))
	      {
		candidate_is_most_specific = false;
		break;
	      }
	  } /* j loop */
	if (candidate_is_most_specific)
	  {
	    if (best_member == null)
              best_member = candidate_member;
            else 
              {
                //System.out.println("ambiguous methods "+best_method+
		//		   " "+candidate_method);
                return null;
              }
	  }
      }  /* outer "i" loop */
    if (best_member == null)
      {
	//System.out.println("No best method");
      }
    return best_member;
  }


  public void searchForApplicableMethods(String name,
					Class the_class,
					int arg_count,
					boolean findStatic,
					Class[] arg_classes,
					Vector applicable_methods) 
  {
  	Method[] methods
	  = the_class.getDeclaredMethods();
	int length = (methods != null ? methods.length : 0);

	for (int i = 0; i<length ; i++) 
	  {
	    Method method = methods[i];
	    int modifiers = method.getModifiers();
	    Class[] param_classes = method.getParameterTypes();
	    int param_count = param_classes.length;
	    boolean isStatic = (modifiers & Modifier.STATIC) != 0;

	    if (method.getName().equals(name) && arg_count == param_count && isStatic == findStatic)
	      {
		boolean add_method_p = true;
           
		/* System.out.println("len="+param_count+" "+
		   ((param_count > 0) ? param_classes[0] : null)); */

		/* check whether arg classes match */
		for (int j = 0 ; j<param_count ; j++)
		  {
		    //		    if (!param_classes[j].isAssignableFrom(arg_classes[j]))
		    // changed by ML. 7/18/99
		    if (!(isReallyAssignableFrom(param_classes[j], arg_classes[j])))
		      {
			add_method_p = false;
			break;
		      }
		  }
		if (add_method_p)
		  {
		    //System.out.println("applicable = "+method);
		    applicable_methods.addElement(method);
		  }
	      }
	  }
  }

  void findInterfaceMethods(String name,
			    Class thisInterface,
			    int argCount,
			    boolean findStatic,
			    Class[] argClasses,
			    Vector applicableMethods,
			    Hashtable visited) 
  {
    if (visited.get(thisInterface) != null){
    	return;
    }
    visited.put(thisInterface, thisInterface);
    searchForApplicableMethods(name, 
			       thisInterface, 
			       argCount, 
			       findStatic, 
			       argClasses, 
			       applicableMethods);
    Class[] extendedInterfaces = thisInterface.getInterfaces();
    for (int i=0; i<extendedInterfaces.length; i++)
      findInterfaceMethods(name, 
			   extendedInterfaces[i], 
			   argCount, 
			   findStatic, 
			   argClasses, 
			   applicableMethods, 
			   visited);
  }

  Method findMethod(String name,
                            Class target_class,
                            Class[] arg_classes,
			    boolean findStatic)
  {
    Class start_class = target_class;
    Class the_class;
    int arg_count = arg_classes.length;
    Vector applicable_methods = new Vector();

    if (target_class.isInterface())
      findInterfaceMethods(name,
			   target_class,
			   arg_count,
			   findStatic,
			   arg_classes,
			   applicable_methods,
			   new Hashtable());
    else
      for (the_class = start_class;
	   the_class != null;
	   the_class = the_class.getSuperclass())
	{
	  searchForApplicableMethods(name, 
				     the_class, 
				     arg_count, 
				     findStatic, 
				     arg_classes,
				     applicable_methods);
	}

    return (Method)findBestApplicableMember(applicable_methods);

  }

  public Method findInstanceMethod(String name,
                                   Class target_class,
                                   Class[] arg_classes) {
    return findMethod(name, target_class, arg_classes, false);
  }

  public Method findStaticMethod(String name,
                                   Class target_class,
                                   Class[] arg_classes) {
    return findMethod(name, target_class, arg_classes, true);
  }
 

  public Constructor findConstructor(Class target_class,
				Class[] arg_classes)
  {
    Class start_class = target_class;
    Class the_class;
    int arg_count = arg_classes.length;
    Vector applicable_constructors = new Vector();

    for (the_class = start_class;
         the_class != null;
         the_class = the_class.getSuperclass())
      {
	Constructor[] constructors
	  = the_class.getDeclaredConstructors();
	int length = (constructors != null ? constructors.length : 0);

	for (int i = 0; i<length ; i++) 
	  {
	    Constructor constructor = constructors[i];
	    int modifiers = constructor.getModifiers();
	    Class[] param_classes = constructor.getParameterTypes();
	    int param_count = param_classes.length;

	    if (arg_count == param_count)
	      {
		boolean add_method_p = true;
           
		/* System.out.println("len="+param_count+" "+
		   ((param_count > 0) ? param_classes[0] : null)); */

		/* check whether arg classes match */
		for (int j = 0 ; j<param_count ; j++)
		  {
		    if (!isReallyAssignableFrom(param_classes[j],arg_classes[j]))
		      {
			add_method_p = false;
			break;
		      }
		  }
		if (add_method_p)
		  {
		    //System.out.println("applicable = "+method);
		    applicable_constructors.addElement(constructor);
		  }
	      }
	  }
      }
    return (Constructor)findBestApplicableMember(applicable_constructors);

  }

  
  static final Class pboolean = Boolean.TYPE;
  static final Class pchar = Character.TYPE;
  static final Class pbyte = Byte.TYPE;
  static final Class pshort = Short.TYPE;
  static final Class pint = Integer.TYPE;
  static final Class plong = Long.TYPE;
  static final Class pfloat = Float.TYPE;
  static final Class pdouble = Double.TYPE;


  public static boolean isReallyAssignableFrom(Class s, Class t) {
    if (s.isAssignableFrom(t)) 
    	return true;
    // P. 54, bottom for definition of widening primitive conversion
    if (s == pdouble)
      return Arrays.asList(pfloat, plong, pint, pshort, pchar, pbyte).contains(t);

	if (s == pfloat)
	  return Arrays.asList(plong, pint, pshort, pchar, pbyte).contains(t);	

	if (s == plong)
	  return Arrays.asList(pint, pshort, pchar, pbyte).contains(t);	

	if (s == pint)
	  return Arrays.asList(pshort, pchar, pbyte).contains(t);
    if (s == pshort)
      return t == pbyte;
    
    return false;
  }




  /* Testing Code

  public static void main(String[] args)
  {
    Dispatcher d = new Dispatcher();
    Class target_class = null;
    Class a_class = null;
    Class b_class = null;
    Class integer_class = null;
    Class object_class = null;
    Class[] arg_classes1 = new Class[1];
    Method other_method;
     
    try {
      target_class = Class.forName("java.lang.Integer");
    } catch (ClassNotFoundException e)
      {
	System.out.println("class not found");
      }

    d.listMethods("toString",new Integer(3));
    System.out.println("find:");
    Method the_method = d.findInstanceMethod("toString",
					     target_class,
					     new Class[0]);
    System.out.println("best= "+the_method);
    
    try {
      b_class = Class.forName("com.gensym.util.ClassB");
    } catch (ClassNotFoundException e)
      {
	System.out.println("class not found");
      }

    try {
      a_class = Class.forName("com.gensym.util.ClassA");
    } catch (ClassNotFoundException e)
      {
	System.out.println("class not found");
      }

    try {
      integer_class = Class.forName("java.lang.Integer");
    } catch (ClassNotFoundException e)
      {
	System.out.println("class not found");
      }
    try {
      object_class = Class.forName("java.lang.Object");
    } catch (ClassNotFoundException e)
      {
	System.out.println("class not found");
      }


    System.out.println("a from b = "+a_class.isAssignableFrom(b_class));
    System.out.println("b from a = "+b_class.isAssignableFrom(a_class));
    System.out.println("a from a = "+a_class.isAssignableFrom(a_class));
    System.out.println("b from b = "+b_class.isAssignableFrom(b_class));
    System.out.println("o from i = "+object_class.isAssignableFrom(
								   integer_class));
    System.out.println("i from o = "+integer_class.isAssignableFrom(
								    object_class));
    System.out.println("o from b = "+object_class.isAssignableFrom(
								   b_class));
    System.out.println("b from o = "+b_class.isAssignableFrom(
							      object_class));

    System.out.println("a sub? b = "+isSubclass(a_class,b_class));
    System.out.println("b sub? a = "+isSubclass(b_class,a_class));
    System.out.println("a sub? a = "+isSubclass(a_class,a_class));
    System.out.println("b sub? b = "+isSubclass(b_class,b_class));
    System.out.println("i sub? o = "+isSubclass(
						integer_class,object_class));
    System.out.println("o sub? i = "+isSubclass(
						object_class,integer_class));
    System.out.println("b sub? o = "+isSubclass(
						b_class,object_class));
    System.out.println("o sub? b = "+isSubclass(
						object_class,b_class));

    System.out.println("______________________________");
    arg_classes1[0] = b_class;
    other_method = d.findInstanceMethod("M1",
					b_class,arg_classes1);
    System.out.println("b.M1(b) best= "+other_method);
     
    System.out.println("______________________________");
    arg_classes1[0] = a_class;
    other_method = d.findInstanceMethod("M1",
					b_class,arg_classes1);
    System.out.println("b.M1(a) best= "+other_method);
  
    System.out.println("______________________________");
    arg_classes1[0] = integer_class;
    other_method = d.findInstanceMethod("M2",
					b_class,arg_classes1);
    System.out.println("b.M2(Integer) best= "+other_method);
  
    System.out.println("______________________________");
    arg_classes1[0] = object_class;
    other_method = d.findInstanceMethod("M2",
					b_class,arg_classes1);
    System.out.println("b.M2(Object) best= "+other_method);
  
    System.out.println("______________________________");
    arg_classes1[0] = integer_class;
    other_method = d.findInstanceMethod("M2",
					a_class,arg_classes1);
    System.out.println("a.M2(Integer) best= "+other_method);
  
    System.out.println("______________________________");
    arg_classes1[0] = object_class;
    other_method = d.findInstanceMethod("M2",
					a_class,arg_classes1);
    System.out.println("a.M2(Object) best= "+other_method);
  }
  
  end of testing code */

}
