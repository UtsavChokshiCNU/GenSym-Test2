/*
 * Bucket
 */

package com.gensym.jartools;
import java.util.zip.*;
import java.util.*;
import java.io.*;
import java.beans.*;

/**
 * Holds the contents of a jar file.
 */
public class Bucket implements Cloneable, Serializable
{
	/**
	 * Bucket holding all external classes.
	 */
	private static final Bucket common=new Bucket();

	/**
	 * Empty token.
	 */
	private static final String empty="";

	/**
	 * File name of the manifest.
	 */
	protected static final String MANIFEST_NAME="META-INF/MANIFEST.MF";

	/**
	 * The manifest.
	 */
	protected volatile Manifest manifest;

	/**
	 * A serializable set of key/value associations.
	 */
	private Vector pairs;

	/**
	 * Provides rapid indexing into the pairs vector.
	 */
	transient volatile Hashtable table;

	/**
	 * Loads classes and instantiates objects from this bucket.
	 */
	transient volatile JarClassLoader jcl;

	/**
	 * Associates a key with a value and a set of properties
	 */
	private static final class Entry implements Serializable
	{
		public final String key;
		public final byte value[];
		public final long modified;

		public Entry(String nam, byte v[], long tim)
		{
			key=nam;
			value=v;
			modified=tim;
		}
	}

	/**
	 * Enumerates file names
	 */
	private final class EnumNames implements Enumeration, Serializable
	{
		int index;
		Object name;

		public EnumNames()
		{
			index=0;
			name=null;
		}

		@Override
		public boolean hasMoreElements()
		{
			synchronized (Bucket.this)
			{
				if (name!=null)
					return true;
				Object e=empty;
				while (pairs.size()>index && empty.equals(e))
					e=pairs.elementAt(index++);
				if (empty.equals(e))
					return false;
				name=((Bucket.Entry)e).key;
				return true;
			}
		}

		@Override
		public Object nextElement()
			throws NoSuchElementException
		{
			if (name==null && !hasMoreElements())
				throw new NoSuchElementException();
			Object rv=name;
			name=null;
			return rv;
		}
	}

	/**
	 * Loads classes from a Bucket.
	 */
	private class JarClassLoader extends ClassLoader
	{
		private Hashtable classes=new Hashtable();

		public JarClassLoader()
		{
			super();
		}

		@Override
		public synchronized Class loadClass(String name, boolean resolveIt)
	      	throws ClassNotFoundException
		{
			Class result=(Class)classes.get(name);
			if (result!=null)
			{
		        	if (resolveIt)
		            	resolveClass(result);
				return result;
			}
			byte  classData[];
	        	/* Check with the primordial class loader */
	        	try
			{
	            	result = super.findSystemClass(name);
	            	return result;
	        	} catch (ClassNotFoundException e)
			{
	        	}
			if (!Bucket.this.equals(common))
			{
				/* If external, load from common */
				String fileName=name.replace('.','/')+".class";
				if (manifest.force(fileName).get("External")!=null)
			        	try
					{
						if (common.table==null)
							common.restore();
						result = (Class)(common.jcl.classes.get(name));
						if (result==null)
						{
							byte bytes[]=get(fileName);
							if (bytes==null)
								throw new ClassNotFoundException();
							common.put(fileName,bytes,modified(fileName));
				            	result = common.jcl.loadClass(name,false);
						}
				        	if (resolveIt)
				            	resolveClass(result);
			            	return result;
			        	} catch (ClassNotFoundException e)
					{
			        	}
			}
	        	/* Try to load it from our repository */
			String fileName=name.replace('.','/')+".class";
	        	classData = get(fileName);
	        	if (classData == null)
			{
	            	throw new ClassNotFoundException();
	        	}
	        	/* Define it (parse the class file) */
	        	result = defineClass(name,classData, 0, classData.length);
	        	if (result == null)
			{
	            	throw new ClassFormatError();
	        	}
			classes.put(name,result);
	        	if (resolveIt)
			{
	            	resolveClass(result);
	        	}
	        	return result;
	    	}

		@Override
		public InputStream getResourceAsStream(String name)
		{
			InputStream is=getSystemResourceAsStream(name);
			if (is!=null)
				return is;
			byte buffer[]=get(name);
			if (buffer==null)
				return null;
			return new ByteArrayInputStream(buffer);
		}
	}


	/**
	 * Creates a Bucket with no content.
	 */
	public Bucket()
	{
		pairs=new Vector();
		table=null;
		manifest=new Manifest();
	}

	/**
	 * Creates a bucket with the content of a jar file.
	 *
	 * @param 		is			The input stream for the jar file.
	 *
	 * @exception	IOException		May be thrown when
	 *						reading from the input stream.
	 *
	 * @exception	ZipException 	May be thrown when
	 *						processing the contents of the
	 *						jar.
	 */
	public Bucket(InputStream is)
		throws IOException, ZipException
	{
		pairs=new Vector();
		table=null;
		manifest=new Manifest();
		ZipInputStream zis=new ZipInputStream(is);
		ZipEntry ze=zis.getNextEntry();
		while(ze!=null)
		{
			String name=ze.getName();
			put(name,Reads.read(zis),ze.getTime());
			zis.closeEntry();
			ze=zis.getNextEntry();
		}
	}

	/**
	 * Write the bucket in jar file format
	 *
	 * @param 		os			The output stream for the jar file.
	 *
	 * @exception	IOException		May be thrown when
	 *						writting to the output stream.
	 *
	 * @exception	ZipException 	May be thrown when
	 *						processing the contents of the
	 *						jar.
	 */
	public synchronized void jar(OutputStream os)
		throws IOException, ZipException
	{
		put(MANIFEST_NAME,manifest.getBytes());
		ZipOutputStream zos=new ZipOutputStream(os);
		int s=pairs.size();
		int i;
		for (i=0; i<s; ++i)
		{
			Object o=pairs.elementAt(i);
			if (!empty.equals(o))
			{
				Entry entry=(Entry)o;
				ZipEntry ze=new ZipEntry(entry.key);
				ze.setTime(entry.modified);
				zos.putNextEntry(ze);
				byte d[]=(byte[])entry.value;
				zos.write(d,0,d.length);
				zos.closeEntry();
			}
		}
		zos.flush();
		zos.close();
	}

	/**
	 * Clones the Bucket.
	 */
	@Override
	public Object clone()
	{
		Bucket b=new Bucket();
		b.pairs=(Vector)pairs.clone();
		b.manifest=(Manifest)manifest.clone();
		return b;
	}

	/**
	 * Initialize the transient table to provide
	 * fast access by file name.
	 */
	void restore()
	{
		jcl=new JarClassLoader();
		table=new Hashtable();
		int i;
		int s=pairs.size();
		for (i=0; i<s; ++i)
		{
			Object o=pairs.elementAt(i);
			if (empty.equals(o))
			{
				pairs.setElementAt(empty,i);
			}
			else
			{
				Integer ndx=i;
				Entry pair=(Entry)o;
				table.put(pair.key,ndx);
			}
		}
	}

	/**
	 * Either deserialize an existing object or, if there is no such object,
	 * create a new object using the null constructor of the class with the
	 * same name.
	 * @param		name	A dot-seperated name, with no file extension.
	 * @exception	IOException	Error occurred while deserializing.
	 * @exception	ClassNotFoundException	No object or class by that name.
	 */
	public Object getObject(String name)
		throws IOException, ClassNotFoundException
	{
		if (table==null)
			restore();
		return Beans.instantiate(jcl,name);
	}

	/**
	 * Return the byte array associated with the given file name.
	 *
	 * @param 		name	A /-seperated path name, complete with
	 *				file extensions.
	 *
	 * @return			The associated byte array or null.
	 */
	public byte get(String name)[]
	{
		if (table==null)
			restore();
		if (name.equals(MANIFEST_NAME))
			put(MANIFEST_NAME,manifest.getBytes());
		Integer ndx=(Integer)table.get(name);
		if (ndx==null)
			return null;
		Entry entry=(Entry)pairs.elementAt(ndx.intValue());
		if (entry==null)
			return null;
		return entry.value;
	}

	/**
	 * Return the time when an entry was last modified.
	 *
	 * @param 		name	A /-seperated path name, complete with
	 *				file extensions.
	 *
	 * @return			The time in milliseconds, or 0.
	 */
	public long modified(String name)
	{
		if (table==null)
			restore();
		Integer ndx=(Integer)table.get(name);
		if (ndx==null)
			return 0;
		Entry entry=(Entry)pairs.elementAt(ndx.intValue());
		if (entry==null)
			return 0;
		return entry.modified;
	}

	/**
	 * Serialize an object and save it as a named resource file in the jar.
	 * This is the exact reverse of java.beans.Beans.instantiate.
	 * Security hashes are included in the manifest.
	 *
	 * @param		name	A dot-seperated name, with no file extension.
	 *				The '.'s are replaced by '/' and ".ser" is appended.
	 *
	 * @param		obj	Object to be saved.
	 *
	 * @exception	IOException	Error occurred while adding the object.
	 *
	 * @see java.beans.Beans#instantiate
	 */
	public synchronized void putObject(final String name, final Object obj)
		throws IOException
	{
		ByteArrayOutputStream baos=new ByteArrayOutputStream();
		ObjectOutputStream oos=new ObjectOutputStream(baos);
		oos.writeObject(obj);
		oos.flush();
		put(name.replace('.','/')+".ser" , baos.toByteArray());
	}

	/**
	 * Associates a name and a value.
	 * Security hashes are included in the manifest.
	 *
	 * @param 		name	A /-seperated path name, complete with
	 *				file extensions.
	 *
	 * @param		value	The associated byte array.
	 */
	public void put(String name, byte value[])
	{
		put(name,value,System.currentTimeMillis());
		if (!name.equals(MANIFEST_NAME))
			manifest.force(name).addHash(value);
	}

	void put(String name, byte value[], long tim)
	{
		if (table==null)
			restore();
		Entry pair=new Entry(name,value,tim);
		int s=pairs.size();
		int elem;
		Object obj=null;
		int found=-1;
		for (elem=0;elem<s;++elem)
		{
			obj=pairs.elementAt(elem);
			if (empty.equals(obj))
			{
				found=elem;
			}
			else
			{
				Entry p=(Entry)obj;
				if (name.equals(p.key))
				{
					break;
				}
			}
		}
		if (elem==s)
		{
			if (found==-1)
				pairs.addElement(pair);
			else
			{
				elem=found;
				pairs.setElementAt(pair,elem);
			}
		}
		else
			pairs.setElementAt(pair,elem);
		Integer ndx= elem;
		table.put(name,ndx);
		if (name.equals(MANIFEST_NAME))
			manifest=new Manifest(value);
	}

	/**
	 * Return an enumeration of the file names.
	 */
	public Enumeration resources()
	{
		return this.new EnumNames();
	}

	/**
	 * Remove an object and its manifest entry from the bucket.
	 * @param	name		A dot-seperated path,
	 *				with NO file extension.
	 */
	public void removeObject(final String name)
	{
		remove(name.replace('.','/')+".ser");
	}

	/**
	 * Remove a file and its manifest entry from the bucket.
	 *
	 * @param 		name	A /-seperated path name, complete with
	 *				file extensions.
	 */
	public void remove(String name)
	{
		if (table==null)
			restore();
		manifest.remove(name);
		Integer ndx=(Integer)table.get(name);
		if (ndx==null)
			return;
		pairs.setElementAt(empty,ndx.intValue());
		table.remove(name);
	}

	/**
	 * Returns the manifest.
	 */
	public Manifest getManifest()
	{
		return manifest;
	}
}
