package com.gensym.beaneditor;

import java.beans.*;
import com.gensym.beansruntime.G2ClassLoader;

/**
 * Represents a loaded Jar file
 */

public class G2JarInfo
{
  /**
   * Private data
   */
  private G2ClassLoader   classLoader;
  private String[]        beanNames;
  private String[]        beanGroups;
  private BeanInfo[]      beanInfos;
  private boolean[]       fromPrototype;
  private G2MessageHeader[] manifestData;
  private String          jarName;

  private static final int MAX_NAME_SIZE = 16;

  public G2JarInfo (String jarName, G2ClassLoader cl, String[] beanNames, String[]
		    beanGroups, boolean[] fromPrototype, 
		    G2MessageHeader[] manifestData)
  {
    if (beanNames.length != fromPrototype.length)
      {
	throw new Error("beanNames and fromPrototype need to have the same length");
      }

    this.jarName = jarName;
    this.classLoader = cl;
    this.beanNames = beanNames;
    this.beanGroups = beanGroups;
    this.fromPrototype = fromPrototype;
    this.manifestData = manifestData;
    this.beanInfos = new BeanInfo[beanNames.length];

    for (int i = 0; i < beanNames.length; i++)
      {
	if (fromPrototype[i])
	  {
	    // delay instantiating it
	    continue;
	  }

	// get the BeanInfo data
	Class c = cl.findClass(beanNames[i]);

	if (c == null)
	  {
	    continue;
	  }

	BeanInfo bi;

	try
	  {
	    bi = Introspector.getBeanInfo(c);
	  }
	catch (Exception ex)
	  {
	    System.err.println("JarInfo: couldn't find BeanInfo for " +
			       c + "; caught "+ex);
	    continue;
	  }

	beanInfos[i] = bi;
      }
  }

  // Accessing the information in this G2JarInfo

    /**
     * Get the name of the file containing this JAR
     */

  public String getJarName()
  {
    return jarName;
  }

  /**
     * Get the short version of the JAR name
     */

  public String getShortJarName()
  {
    /*String shortName = new String(jarName);

    if (shortName.length() > MAX_NAME_SIZE)
      {
	int last = shortName.lastIndexOf(System.getProperty ("file.separator"));

	if (last != -1)
	  {       
	    String name      = shortName.substring(last + 1);
	    String shortPath = shortName.substring(0, 8);
	    shortName = new String(shortPath + "..." + System.getProperty ("file.separator") +
				   name);
	  }
      }

    return shortName;*/

    int i = jarName.lastIndexOf(System.getProperty("file.separator"));
    String string = jarName.substring(i + 1);
    return string;
  }

  /**
     * Get the number of beans in this Jar file
     */

  public int getCount()
  {
    return beanNames.length;
  }

  /**
     * Get the class loader for this Jar file
     */

  public G2ClassLoader getClassLoader()
  {
    return classLoader;
  }

  /**
     * Get the BeanInfo for the ith bean in this jar file
     */

  public BeanInfo getBeanInfo(int i)
  {
    if (beanInfos[i] != null)
      {
	return beanInfos[i];
      }
    else 
      {
	Object b = getInstance(beanNames[i]);
	if (b != null)
	  {
	    Class c = b.getClass();
	    BeanInfo bi;

	    try
	      {
		bi = Introspector.getBeanInfo(c);
	      } catch (Exception ex)
		{
		  System.err.println("JarInfo: couldn't find BeanInfo for "+c+"; caught "+ex);
		  return null;
		}

	      beanInfos[i] = bi;
	      return bi;
	  }

	return null;
      }
  }

  /**
     * The bean name of this bean
     */

  public String getName(int i)
  {
    return beanNames[i];
  }

  public String getGroup(int i){
    return beanGroups[i];
  }

  /**
     * Was this bean from a serialized prototype? -- unused so far?
     */

  public boolean isFromPrototype(String name)
  {
    return fromPrototype[indexForName(name)];
  }

  /**
     * Get to Manifest Headers for this bean
     */

  public G2MessageHeader getManifestData(String name)
  {
    return manifestData[indexForName(name)];
  }

  /**
     * Get a new Bean instance given its name
     */

  public Object getInstance(String name)
  {
    try
      {
	return Beans.instantiate(classLoader, name);
      }
    catch (Throwable th)
      {
	return null;
      }
  }

  private int indexForName(String name)
  {
    for (int i=0; i<beanNames.length ; i++)
      {
	if (beanNames[i].equals(name))
	  {
	    return i;
	  }
      }
    return -1;
  }

}
