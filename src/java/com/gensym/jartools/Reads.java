/*
 * Reads
 */

package com.gensym.jartools;

import java.io.*;

/**
 * This is a fast variable-length reader.
 * <p>
 * It reads into a series of buffers,
 * each buffer being twice as large as the last.
 * <p>
 * At the end, it allocates a single buffer
 * exactly equal in length to the total bytes read.
 * It then copies everything into this final buffer.
 */
public final class Reads
{
    public static byte read(InputStream is)[] throws IOException
	{
		byte v[][]=new byte[22][];
		int vc=0;
		int s=1024;
		int t=0;
		byte b[]=new byte[s];
		v[vc]=b;
		int chunk=0;
		int offset=0;
		while (chunk!=-1)
		{
			chunk=is.read(b,offset,s-offset);
			if (chunk!=-1)
			{
				offset+=chunk;
				t+=chunk;
				if (offset==s) //not always true with a ZipInputStream
				{
					s*=2;
					vc++;
					b=new byte[s];
					v[vc]=b;
					offset=0;
				}
			}
		}
		byte o[]=new byte[t];
		int i;
		s=1024;
		int off=0;
		for (i=0;i<vc;++i)
		{
			System.arraycopy(v[i],0,o,off,s);
			off+=s;
			s*=2;
		}
		System.arraycopy(v[vc],0,o,off,offset);
		return o;
	}
}
