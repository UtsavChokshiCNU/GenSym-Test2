package com.gensym.jgi.download.local;

import java.util.Enumeration;
import java.lang.reflect.Field;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.Hashtable;
import com.gensym.fida.*;
import com.gensym.fida.support.*;
import com.gensym.classes.Item;
import com.gensym.classes.Definition;
import com.gensym.classes.G2__BaseImpl;
import com.gensym.classes.Entity;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Connection;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.G2ClassTranslator;
import com.gensym.util.Sequence;

/**
 * This is the G2 version of the ClassManager, which can be used to export classes from 
 * G2 to the FIDAruntime application.
 */
public class ExternalG2RTClassManager extends ClassManagerImpl
{

  public ExternalG2RTClassManager(Environment environment)
  {
    super(environment);
  }


  public void export(Item itemToExport)
       throws ClassManagerException,
	      G2AccessException
  {
    
    if (itemToExport instanceof Definition) {
      Symbol g2ClassName = ((Definition)itemToExport).getClassName();
      G2Access connection = ((G2__BaseImpl)itemToExport).getContext();
      LocalStubClassLoader classLoader = 
	DownloadLocalClasses.getLocalStubClassLoaderForConnection(connection, false);
      classLoader.setClassManager(this);

      DownloadLocalClasses.redownloadClass(connection, 
					   g2ClassName,
					   true,
					   false, //onlystub
					   null );
    } else {
      throw new ClassManagerException("Do not know how to export " + itemToExport.toString());
    }

  }

}
