/*
 * ManifestSection
 */

package com.gensym.jartools;
import java.io.Serializable;
import java.nio.charset.Charset;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Vector;

/**
 * Represents one section of a manifest from a jar file.
 */
public class ManifestSection
	implements Serializable, Cloneable
{
	private Vector pairs=new Vector();
	private boolean isJavaBean = false;

    public boolean getIsJavaBean(){
        return    isJavaBean;
    }

	private static class Pair implements Serializable
	{
		public final String name;
		public final String value;

		public Pair(String pname, String pvalue)
		{
			name=pname;
			value=pvalue;
		}

		public String header()
		{
			return name+": "+value;
		}

		@Override
		public boolean equals(Object o)
		{
			return name.equalsIgnoreCase(((ManifestSection.Pair)o).name);
		}
		
		@Override
		public int hashCode() {
			final int prime = 31;
			int result = 1;
			return prime * result + ((this.name == null) ? 0 : this.name.hashCode());
		}
	}

	/**
	 * Null constructor required for serialization.
	 */
	public ManifestSection()
	{
	}

	/**
	 * Normal constructor initializes the section name.
	 * @param id Path name.
	 */
	public ManifestSection(String id)
	{
		pairs.addElement(new Pair("Name",id.replace('\\','/')));
	}

	/**
	 * Normal constructor initializes the section name.
	 * @param id Path name.
	 */
	public ManifestSection(String id, boolean isBean)
	{
		pairs.addElement(new Pair("Name",id.replace('\\','/')));
		isJavaBean = isBean;
	}

	/**
	 * Load a pre-existing manifest section.
	 * @param header An array of strings in the form "name: value",
	 * 			or " value".
	 */
	public ManifestSection(String header[])
	{
		int l=header.length;
		int i;
		String lastName=null;
		String lastValue=null;
		String current;
		for (i=0;i<l;++i)
		{
			current=header[i];
			if (current.startsWith(" ")) //continuation
			{
				if (lastName!=null)
				{
					lastValue+=current.substring(1);
					add(lastName,lastValue);
				}
				//else ignore spurious continuation line
			}
			else
			{
				int colon=current.indexOf(": ");
				if (colon>0)
				{
					lastName=current.substring(0,colon);
					lastValue=current.substring(colon+2);
					add(lastName,lastValue);
				}
				//else ignore garbage
			}
		}
	}


//
/**
	 * Load a pre-existing manifest section.
	 * @param header An array of strings in the form "name: value",
	 * 			or " value".
	 */
	public ManifestSection(String header[], boolean isBean)
	{
    	int l=header.length;
		int i;
		String lastName=null;
		String lastValue=null;
		String current;
		for (i=0;i<l;++i)
		{
			current=header[i];
			if (current.startsWith(" ")) //continuation
			{
				if (lastName!=null)
				{
					lastValue+=current.substring(1);
					add(lastName,lastValue);
				}
				//else ignore spurious continuation line
			}
			else
			{
				int colon=current.indexOf(": ");
				if (colon>0)
				{
					lastName=current.substring(0,colon);
					lastValue=current.substring(colon+2);
					add(lastName,lastValue);
				}
				//else ignore garbage
			}
		}
        isJavaBean = isBean;
	}

//
	/**
	 * Clones the section.
	 */
	@Override
	public synchronized Object clone()
	{
		return new ManifestSection(get());
	}

	/**
	 * Returns true if the section names are equal.
	 * @param o Another ManifestSection.
	 */
	@Override
	public synchronized boolean equals(Object o)
	{
		return get("Name").equals(((ManifestSection)o).get("Name"));
	}
	
	@Override
	public int hashCode() {
		final int prime = 31;
    	int result = 1;
    	return prime * result + ((get("Name") == null) ? 0 : get("Name").hashCode());
	}

	/**
	 * Remove an item from the section.
	 * @param name Name of the item.
	 */
	public synchronized void remove(String name)
	{
		pairs.removeElement(new Pair(name,""));
	}

	/**
	 * Add an item to the section.
	 * @param name Name of the item.
	 * @param value Value assigned to the item.
	 */
	public synchronized void add(String name, String value)
	{
		Pair pair=new Pair(name,value);
		pairs.removeElement(pair);
		pairs.addElement(pair);
	}

	/**
	 * Returns the value of an item in the section, or null.
	 * @param name Name of the item.
	 * @return The assigned value.
	 */
	public synchronized String get(String name)
	{
		int i;
		int s=pairs.size();
		Pair pair;
		for (i=0;i<s;++i)
		{
			pair=(Pair)pairs.elementAt(i);
			if (name.equals(pair.name))
				return pair.value;
		}
		return null;
	}

	/**
	 * Returns the contents of the section as an array of strings.
	 */
	public synchronized String get()[]
	{
		int s=pairs.size();
		Vector e=new Vector();
		int i;
		for (i=0;i<s;++i)
		{
			String ln=((Pair)pairs.elementAt(i)).header();
			while (ln.length()>72)
			{
				e.addElement(ln.substring(0,72));
				ln=" "+ln.substring(72);
			}
			e.addElement(ln);
		}
		s=e.size();
		String rv[]=new String[s];
		e.copyInto(rv);
		return rv;
	}

	/**
	 * Returns a security hash as a base64 ASCII string.
	 * @param algorithm Security hash algorithm name.
	 * @param data The data to be hashed.
	 * @exception NoSuchAlgorithmException Unimplimented security hash.
	 */
	public static String base64Hash(String algorithm, byte data[])
		throws NoSuchAlgorithmException
	{
		MessageDigest md=MessageDigest.getInstance(algorithm);
//		MessageDigest md=MessageDigest.getMessageDigest(algorithm);
		byte hash[]=md.digest(data);
		return new String(Base64.binToAsc(hash), Charset.defaultCharset());
	}


	/**
	 * Add MD5 and SHA security hashes to the section.
	 * @param data The data associated with the section.
	 */
	public void addHash(byte data[])
	{
		try
		{
			add("Hash-Algorithms","MD5 SHA ");
			add("MD5-Hash",base64Hash("MD5",data));
			add("SHA-Hash",base64Hash("SHA",data));
		} catch (Exception e)
		{
e.printStackTrace();
			throw new Error(e.toString());
		}
	}

	/**
	 * Validate the security hash.
	 * @param data The data associated with the section.
	 * @return True when valid.
	 * @exception NoSuchAlgorithmException Unimplimented security hash.
	 */
	public boolean validate(byte data[])
		throws NoSuchAlgorithmException
	{
		String algorithm;
		String hash=get("SHA-Hash");
		if (hash!=null)
			algorithm="SHA";
		else
		{
			hash=get("MD5-Hash");
			if (hash!=null)
				algorithm="MD5";
			else
				return false;
		}
		return hash.equals(base64Hash(algorithm,data));
	}
}
