package com.gensym.jgi;

import java.lang.reflect.*;
import com.gensym.util.Sequence;

import java.beans.*;

import com.gensym.util.G2ClassTranslator;
import com.gensym.core.CmdLineArgHandler;


/**
 *  Given a java class clazz(for which to generate stubs) this class returns a sequence
 *  of all of the ancestors of clazz, interfaces and parameter types of methods of clazz.
 *  This data is then used to create a stub hierarchy in G2 for clazz
 */
class JavaClassStubGeneratorHierarchy  {

  //===================


   private Sequence generateReport(final Class clazz, final Class stopBefore, final Sequence seq) {
	 Sequence sequence = seq;
     try {
       BeanInfo bi ;
       if (stopBefore != null) {
	 bi = Introspector.getBeanInfo(clazz, stopBefore);
       } else {
	 bi = Introspector.getBeanInfo(clazz);
       }
       
       Method java_methods[]      = clazz.getMethods();
       for (int i = 0; i < java_methods.length; i++) {
	 //                System.out.println("**  Method "+java_methods[i].getName());
	 sequence = storeArgsOfMethod(java_methods[i],clazz,sequence);
       }
       
       Constructor java_constructors[] = clazz.getConstructors();
       for (int i = 0; i < java_constructors.length; i++) {
	 sequence = storeArgsOfConstructor(java_constructors[i],clazz,sequence);
       }
       
     } catch (IntrospectionException ex) {
       throw new RuntimeException(ex.toString());
     }
     return sequence;
   }

  private static void decomposeMethodParameters(MethodDescriptor md) {
    ParameterDescriptor[] pd = md.getParameterDescriptors();

    if (pd!=null) {
      for (int i = 0; i < pd.length; i++) {
	System.out.println(pd[i].toString()+"<<<<");
      }
    }
    else {
      System.out.println("no args");
    }

  }


  private boolean informG2AboutjavaClass(Class java_class) {
    // if the java class is not in either of the hash tables, return it back to G2
    return((G2ClassTranslator.getG2TypeFromJavaClassOrNull(java_class) == null) );
  }


  private Sequence storeClassType(final Class clazz, final Class baseClass, final Sequence seq)
  {
    //   if (seq==null) 
    //     System.out.println("  Request to storeClassType "+clazz.getName());
	Class targetClass = clazz;
    if( informG2AboutjavaClass(targetClass)) {
      if (targetClass != baseClass) {
	if(!targetClass.isPrimitive()) {   
	  if (targetClass.isArray()) {
		  targetClass = G2JavaStubGenerator.getArrayComponent(targetClass);
	  }
	  if(seq.isEmpty()) {
	    seq.addElement(targetClass.getName());
	  } else {
	    if( seq.contains(targetClass.getName()))  {
	      //System.out.println("Skipping duplicate entry.");
	    } else {
	      seq.addElement(targetClass.getName());
	      //System.out.println("Stored. "+clazz.getName());
	    }
	  }
	} else  {
	  //System.out.println("Skipping clazz.isPrimitive() || (clazz.isArray()");
	}
      }
    }  else  {
      //System.out.println("Sorry dude, G2 need not know about "+clazz.getName());
    }
    return seq;
  }



    private Sequence storeClassType(Class clazz,Class baseClass, Sequence seq ,boolean atHead) {
      //         System.out.println("  Request to storeClassType "+clazz.getName());
      if( informG2AboutjavaClass(clazz))  {
	if (clazz != baseClass)  {
	  if(!clazz.isPrimitive() && (!clazz.isArray()))  {
	    if(seq.isEmpty()) {
	      seq.addElement(clazz.getName());
	    }  else  {
	      if( seq.contains(clazz.getName())) {
		//                                System.out.println("Skipping duplicate entry.");
	      }  else {
		if(atHead) {
		  seq.insertElementAt(clazz.getName(),0);
		} else {
		  seq.addElement(clazz.getName());
		}
		//                            System.out.println("Stored. "+clazz.getName());
	      }
	    }
	  }  else  {
	    //                    System.out.println("Skipping clazz.isPrimitive() || (clazz.isArray()");
	  }
	}
      }  else  {
	//            System.out.println("G2 need not know about "+clazz.getName());
      }
      return seq;
    }


  private  Sequence storeArgsOfConstructor(final Constructor method, final Class baseClass, final Sequence seq) {
    Class[] clazzes = method.getParameterTypes();
    Sequence sequence = seq;
    for (int i = 0; i < clazzes.length; i++) { 
      //System.out.println("method "+method.getName()+" " +clazzes[i].toString() );
      sequence = storeClassType(clazzes[i],baseClass,sequence);
    }
    
    return sequence;
  }

  private  Sequence storeInterfaceClasses(final Class clazzes[], final Class baseClass, final Sequence seq) {
	Sequence sequence = seq;
	for (int i = 0; i < clazzes.length; i++) {  
      //System.out.println("method "+method.getName()+" " +clazzes[i].toString() );
      if (baseClass.isInterface() && i == 0) {}  // ignore first extend (as this will be parent
      else
    	  sequence=storeClassType(clazzes[i],baseClass,sequence);
    }

    return sequence;
  }


  private  Sequence storeArgsOfMethod(final Method method, final Class baseClass, final Sequence seq) {
    Class[] clazzes = method.getParameterTypes();
    Sequence sequence = seq;
    for (int i = 0; i < clazzes.length; i++) { 
      //System.out.println("method "+method.getName()+" " +clazzes[i].toString() );
      sequence=storeClassType(clazzes[i],baseClass,sequence);
    }

    return (Sequence)storeClassType(method.getReturnType(),baseClass,sequence);
  }

  public  Sequence detailAncestry(Class clazz) {   // create an empty sequence for this class query
    Sequence starter=new Sequence();
    Sequence selfInfo=new Sequence();
    String parentName="";
    //     System.out.println("/n/n-------Start of call ------------");

    Class parentClass = clazz.getSuperclass();
    Class java_interfaces[] = clazz.getInterfaces();
    if(parentClass==null)  {
      //  System.out.println("class "+clazz.getName()+" parent from  JGI-JAVA-PROXY" );
      if (clazz.isInterface() && java_interfaces.length > 0) 
	// get the most direct superior interface
	parentName = java_interfaces[0].getName();
      else
	parentName= G2JavaStubController.JGI_PROXY_MIXIN_CLASS_.getPrintValue();
      selfInfo=this.generateReport(clazz  , null,starter); 
    }  else  {
      parentName=parentClass.getName();
      //  System.out.println("class "+clazz.getName()+" parent from " + parentName);
      selfInfo=this.generateReport(clazz  , null,starter);
    }

    // a wee print out

    Sequence implementedInterfaces = new Sequence();

    if (java_interfaces.length > 0) {
      implementedInterfaces = storeInterfaceClasses(java_interfaces,clazz,implementedInterfaces);
    }
    
    //      System.out.println("\n-------End---------");
    // decomposeVector(selfInfo);

    // return the sequence of parent class's and parameters to G2
    Sequence returnSequence = new Sequence();

    returnSequence.addElement(G2ClassTranslator.createG2NameFromJavaName(clazz.getName()));
    returnSequence.addElement(selfInfo);
    returnSequence.addElement(implementedInterfaces);
    returnSequence.addElement(parentName);

    returnSequence.addElement(G2ClassTranslator.createG2NameFromJavaName(parentName));

    //System.out.println("/n/nReturning "+returnSequence);
    
    return returnSequence;
  }



  public static void main(String args[]) {
    JavaClassStubGeneratorHierarchy jce = new JavaClassStubGeneratorHierarchy();

    CmdLineArgHandler cmdLine = new CmdLineArgHandler (args);

    // see what command lines args were passed in to the program


    String givenClazz  = cmdLine.getOptionValue ("-class");
    System.out.println("\n\n"+givenClazz);
    Class clazz=null;

    try{
      clazz = Class.forName(givenClazz);
    }catch(Exception e){System.out.println("problem : " + e);}

    Sequence seq = jce.detailAncestry(clazz);
    System.out.println (seq);
  }
}

