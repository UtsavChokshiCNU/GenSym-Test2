package com.gensym.beaneditor;

/**
 * Read the contents of a JAR file.
 *
 */

import java.io.*;
import java.util.*;
import java.util.zip.*;
import java.beans.*;
import java.net.*;
import javax.swing.BoundedRangeModel;
import com.gensym.beansruntime.G2ClassLoader;
import com.gensym.message.Trace;

class G2JarLoader
{
  private InputStream       jarStream;     // Jar input stream
  private String            jarName;	      // name of the jar file
  private ZipFile           jarFile;
  private G2ClassLoader     loader;        // the loader instance
  private static Vector     loadedJarNames = new Vector (5);
  private static String[]   loadedJarNamesArray;
  private String            pathSeparator = System.getProperty ("path.separator");
  static String             extendedClassPath = System.getProperty ("java.class.path");

  public G2JarLoader(String jarName) throws IOException
  {
    this.jarName = jarName;
    InputStream is = new FileInputStream(jarName);
    jarStream = new BufferedInputStream(is);
    jarFile = new ZipFile(jarName);
    loader = G2ClassLoader.ourLoader;
    File file = new File(jarName);
    if (ComponentEditor.windowsPlatform)
      loadedJarNames.addElement (file.getAbsolutePath().toLowerCase());
    else
      loadedJarNames.addElement (file.getAbsolutePath());
    extendedClassPath += pathSeparator + jarName;
    loadedJarNamesArray = null;
  }

  public synchronized static String[] getLoadedJars () {
    if (loadedJarNamesArray == null) {
      int numJars = loadedJarNames.size ();
      loadedJarNamesArray = new String[numJars];
      loadedJarNames.copyInto (loadedJarNamesArray);
    }
    return loadedJarNamesArray;
  }

  public ClassLoader getLoader()
  {
    return loader;
  }

  /**
   * Determine if the Input Stream contains a serialized object
   */

  private String guessContentTypeFromStream(InputStream is) throws IOException
  {
    String type;
    type = URLConnection.guessContentTypeFromStream(is);
	
    if (type == null)
      {
	is.mark(10);
	int c1 = is.read();
	int c2 = is.read();
	int c3 = is.read();
	int c4 = is.read();
	int c5 = is.read();
	int c6 = is.read();
	is.reset();

	if (c1 == 0xAC && c2 == 0xED)
	  {
	    type = "application/java-serialized-object";
	  }

      }
    return type;
  }

  /**
   * Load the classes, resources, etc.
   */

  public G2JarInfo loadJar(BoundedRangeModel model)
  {

    ZipInputStream zis = null;
    G2Manifest mf = null;
    Vector classList = new Vector(); // the classes
    Vector serList = new Vector(); // the serialized objects

    byte buffer[] = new byte[1024];
    int count = 0;

    try
      {
	zis = new ZipInputStream(jarStream);
	ZipEntry ent = null;
	Enumeration entries = jarFile.entries();
	while (entries.hasMoreElements()){
	  entries.nextElement();
	  count++;
	}
	model.setMinimum(0);
	model.setMaximum(count*4);
	model.setValue(0);
	int i=0;
	while ((ent = zis.getNextEntry()) != null)
          {
	    i++;
	    model.setValue(i);
	    String name = ent.getName();
	    String type = null;

	    ByteArrayOutputStream baos = new ByteArrayOutputStream();

	    for (;;)
	      {
		int len = zis.read(buffer);
		if (len < 0)
		  {
		    break;
		  }
		baos.write(buffer, 0, len);
	      }

	    byte[] buf = baos.toByteArray();
	    int size = buf.length;

	    if (G2Manifest.isManifestName(name))
	      {
		type = "manifest/manifest";
	      }

	    if (type == null)
	      {
		InputStream tmpStream = new ByteArrayInputStream(buf);
		type = guessContentTypeFromStream(tmpStream);
		tmpStream.close();
	      }
	    /*
	      System.out.println ("Loading Jar: Entry = " + name +
	      "\nType = " + type);
	      */
	    if (type == null)
	      {
		type = "input-stream/input-stream";
	      }
	    loader.putLocalResource(name, buf, type);
	    if (type.startsWith("application/java-serialized-object"))
	      {
		String sername = name.substring(0, name.length() - 4);
		sername = sername.replace('/', '.');
		serList.addElement(sername);

	      }
	    else if (type.startsWith("application/java-vm"))
	      {
		/* remove the .class suffix */
		String classname = name.substring(0, name.length() - 6);
		classname = classname.replace('/', '.');          
		loader.setDefinition(classname, buf);
		classList.addElement(classname);

	      }
	    else if (type.equals("manifest/manifest"))
	      {
		mf = new G2Manifest(buf);
	      }
	    else
	      {
		// do nothing
	      }
	  }

      }
    catch (IOException e)
      {
	Trace.exception(e);
	e.printStackTrace();
      }
    catch (Throwable ex)
      {
	Trace.exception(ex);
	ex.printStackTrace();
      }
    finally
      {
	if (zis != null)
	  {
	    try
	      {
		zis.close();
	      }   catch (Exception ex)
		{
		  // ignore
		}
	  }
      }

    loader.applyDefinitions(classList, new ProgressCounter(model));
    G2JarInfo ji = createJarInfo (classList, serList, mf, model);
    for (int i= model.getValue(); i<=count*4; i++)
      model.setValue(i);
    return ji;
  }

  class ProgressCounter implements com.gensym.beansruntime.Counter{

    private BoundedRangeModel model;

    ProgressCounter(BoundedRangeModel model){
      this.model = model;
    }

    @Override
    public void click(){
      model.setValue(model.getValue() + 1);
    }
  }


  /**
   * Create a G2JarInfo from a manifest and a class list
   */

  private G2JarInfo createJarInfo (Vector classList, Vector serList, G2Manifest mf, BoundedRangeModel model)
  {
    Hashtable beans;
    Hashtable groups = null;
    Hashtable headersTable = new Hashtable();
    if (mf == null)
      {
	beans = new Hashtable();
	for (Enumeration keys = classList.elements(); keys.hasMoreElements(); )
	  {
	    String key = (String) keys.nextElement();
	    beans.put(key, new Boolean(false)); // not from serializable
	    model.setValue(model.getValue() + 1);
	  }

	for (Enumeration keys = serList.elements(); keys.hasMoreElements(); )
	  {
	    String key = (String) keys.nextElement();
	    beans.put(key, new Boolean(true)); // from class definition
	    model.setValue(model.getValue() + 1);
	  }
      }
    else
      {
	beans = new Hashtable();
	groups = new Hashtable();

	for (Enumeration entries = mf.entries(); entries.hasMoreElements(); )
	  {
	    G2MessageHeader mh = (G2MessageHeader) entries.nextElement();
	    String name = mh.findValue("Name");
	    String isBean = mh.findValue("Java-Bean");
	    String beanGroup = mh.findValue("Bean-Group");

	    if (isBean != null && isBean.equalsIgnoreCase("True"))
	      {
		String beanName;
		boolean fromPrototype = true;

		if (name.endsWith(".class"))
		  {
		    fromPrototype = false;
		    beanName = name.substring(0, name.length() - 6);
		  }
		else if (name.endsWith(".ser"))
		  {
		    beanName = name.substring(0, name.length() - 4);
		  } else
		    {
		      beanName = name;
		    }

		beanName = beanName.replace('/', '.');
		beans.put(beanName, new Boolean(fromPrototype));
		if (beanGroup != null)
		  groups.put(beanName, beanGroup);
		headersTable.put(beanName, mh);
	      }
	       model.setValue(model.getValue() + 1);
	  }
      }

    String beanNames[] = new String[beans.size()];
    String beanGroups[] = new String[beans.size()];
    boolean fromPrototype[] = new boolean[beans.size()];
    G2MessageHeader headers[] = new G2MessageHeader[beans.size()];

    Enumeration keys;
    int i;
    for (keys = beans.keys(), i = 0; keys.hasMoreElements(); i++)
      {
	String key = (String) keys.nextElement();
	beanNames[i] = key;
	beanGroups[i] = (String)groups.get(key);
	fromPrototype[i] = ((Boolean)beans.get(key)).booleanValue();
	headers[i] = (G2MessageHeader) headersTable.get(key);
	model.setValue(model.getValue() + 1);
      }

    return new G2JarInfo (jarName, loader, beanNames, beanGroups, fromPrototype, headers);
  }


}



