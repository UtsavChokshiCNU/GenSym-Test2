/*
 * Manifest
 */

package com.gensym.jartools;
import java.io.*;
import java.nio.charset.Charset;
import java.util.*;

/**
 * Represents a manifest of a jar file.
 */
public class Manifest implements Serializable, Cloneable
{
	private Vector sections=new Vector();

	public Manifest()
	{
	}

	/**
	 * Create a manifest from an array of strings.
	 */
	public Manifest(String txt[])
	{
		establish(txt);
	}

	/**
	 * Create a manifest from an array of bytes.
	 */
	public Manifest(byte data[])
	{
		try
		{
			ByteArrayInputStream bais=new ByteArrayInputStream(data);
			InputStreamReader isr=new InputStreamReader(bais, Charset.defaultCharset());
			BufferedReader br=new BufferedReader(isr);
			Vector ln=new Vector();
			String s;
			for(s=br.readLine();s!=null;s=br.readLine())
				ln.addElement(s);
			int l=ln.size();
			String sa[]=new String[l];
			ln.copyInto(sa);
			establish(sa);
		}
		catch(IOException e)
		{
			throw new Error(e.toString());
		}
	}

	/**
	 * Create a manifest from an array of strings.
	 */
	private synchronized void establish(String txt[])
	{
		int l=txt.length;
		int i=0;
		for(;i<l&&txt[i].length()>0;++i){ } //locate empty line
		for(;i<l&&txt[i].length()==0;++i){ } //locate non-empty line
		while(i<l)
		{
			Vector lnv=new Vector();
			for(;i<l&&txt[i].length()>0;++i) //process non-empty lines
				lnv.addElement(txt[i]);
			int s=lnv.size();
			String ln[]=new String[s];
			lnv.copyInto(ln);
			ManifestSection m = new ManifestSection(ln);
			sections.addElement(m);
			for(;i<l&&txt[i].length()==0;++i) { } //locate non-empty line
		}
	}



	/**
	 * Clones the manifest.
	 */
	@Override
	public synchronized Object clone()
	{
		return new Manifest(get());
	}

	/**
	 * Empty the manifest.
	 */
	public synchronized void clear()
	{
		sections=new Vector();
	}

	/**
	 * Returns the array of strings comprising the manifest.
	 */
	public synchronized String get()[]
	{
		Vector lnv=new Vector();
		lnv.addElement("Manifest-Version: 1.0");
		lnv.addElement("");
		int s=sections.size();
		int i;
		boolean addedBeanTrueFlag = true;
		for (i=0;i<s;++i)
		{
			ManifestSection ms=(ManifestSection)sections.elementAt(i);

            // if the file is tagged as a bean, add a true flag
			if (ms.getIsJavaBean()) {
			       addedBeanTrueFlag = false;
			}
			else {// say we have added one to stop it adding another
			    addedBeanTrueFlag = true;
			}

			String ln[]=ms.get();
			int t=ln.length;
			int j;
            String name="";


			for (j=0;j<t;++j){

			    //if ((!addedBeanTrueFlag) && ( j >0)){
			    if ((!addedBeanTrueFlag) && ( j >0) && ((ln[j].toCharArray())[0] != ' ') ){
    				lnv.addElement("Java-Bean: True");
    				addedBeanTrueFlag = true;
	    		}

			    lnv.addElement(ln[j]);
			}


			lnv.addElement("");
		}
		String rv[]=new String[lnv.size()];
		lnv.copyInto(rv);

		return rv;
	}

	/**
	 * Returns the manifest as an array of bytes.
	 */
	public byte getBytes()[]
	{
		try
		{
			ByteArrayOutputStream baos=new ByteArrayOutputStream();
			OutputStreamWriter osw=new OutputStreamWriter(baos, Charset.defaultCharset());
			BufferedWriter bw=new BufferedWriter(osw);
			String sa[]=get();
			int l=sa.length;
			int i;
			for (i=0;i<l;++i)
			{
				bw.write(sa[i],0,sa[i].length());
				bw.newLine();
			}
			bw.flush();
			return baos.toByteArray();
		} catch (IOException e)
		{
			throw new Error(e.toString());
		}
	}

	/**
	 * Returns the named manifest section. Null is returned if
	 * there is no matching section.
	 */
	public synchronized ManifestSection get(String name)
	{
		int s=sections.size();
		int i;
		for (i=0;i<s;++i)
		{
			ManifestSection ms=(ManifestSection)sections.elementAt(i);
			if (name.equals(ms.get("Name")))
				return (ManifestSection)sections.elementAt(i);
		}
		return null;
	}

	/**
	 * Returns the named manifest section. The section is created if necessary.
	 */
	public synchronized ManifestSection force(String name)
	{
		ManifestSection ms=get(name);
		if (ms!=null)
			return ms;
		ms=new ManifestSection(name);
		add(ms);
		return ms;
	}


	/**
	 * Returns the named manifest section. The section is created if necessary.
	 */
	public synchronized ManifestSection force(String name , boolean isBean)
	{
		ManifestSection ms=get(name);
		if (ms!=null)
			return ms;
		ms=new ManifestSection(name,isBean);
		add(ms);
		return ms;
	}

	/**
	 * Removes the named manifest section.
	 */
	public synchronized void remove(String name)
	{
		ManifestSection ms=new ManifestSection(name);
		sections.removeElement(ms);
	}

	/**
	 * Adds the manifest section, unless the name starts with
	 * META-INF/ or /META-INF/
	 */
	public synchronized void add(ManifestSection ms)
	{
		String name=ms.get("Name");
		if (name.startsWith("META-INF/") ||
			name.startsWith("/META-INF/"))
			return;
		sections.removeElement(ms);
		sections.addElement(ms);
	}

	/**
	 * Returns an enumeration of the sections of the manifest.
	 */
	public synchronized Enumeration sections()
	{
		return sections.elements();
	}
}
