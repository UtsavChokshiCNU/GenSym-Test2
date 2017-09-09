/*
 * Base64
 */

package com.gensym.jartools;

/**
 * Base64 is a standard for passing binary data as ASCII.
 */
public class Base64
{
	private static byte t[]=null;

	private static synchronized void init()
	{
		if (t!=null)
			return;
		t=new byte[64];
		int i;
		for (i=0;i<26;++i)
			t[i]=(byte)('A'+i);
		for (i=26;i<52;++i)
			t[i]=(byte)('a'+i-26);
		for (i=52;i<62;++i)
			t[i]=(byte)('0'+i-52);
		t[62]=(byte)'+';
		t[63]=(byte)'/';
	}

	/**
	 * Convert an array of binary bytes to an array of ASCII bytes.
	 * <p>
	 * ASCII characters used are A-Z, a-z, 0-9, /, and +.
	 * The '=' is used to pad the ascii to a multiple of 4 bytes.
	 * @param bin The binary data.
	 * @return The equivalant ASCII data.
	 */
	public static synchronized byte binToAsc(byte bin[])[]
	{
		init();
		int binLen=bin.length;
		int ascLen=((binLen+2)/3)*4;
		byte asc[]=new byte[ascLen];
		int binNdx;
		int ascNdx=0;
		int tmp;
		for(binNdx=0;binNdx<binLen;binNdx+=3)
		{
			asc[ascNdx++]=t[(bin[binNdx]>>2)&63];
			tmp=(bin[binNdx]&3)<<4;
			if ((binNdx+1)<binLen)
				tmp|=(bin[binNdx+1]>>4)&15;
			asc[ascNdx++]=t[tmp];
			if ((binNdx+1)<binLen)
			{
				tmp=(bin[binNdx+1]&15)<<2;
				if ((binNdx+2)<binLen)
					tmp|=(bin[binNdx+2]>>6)&3;
				asc[ascNdx++]=t[tmp];
			}
			else
				asc[ascNdx++]=(byte)'=';
			if ((binNdx+2)<binLen)
			{
				asc[ascNdx++]=t[bin[binNdx+2]&63];
			}
			else
				asc[ascNdx++]=(byte)'=';
		}
		return asc;
	}
}
