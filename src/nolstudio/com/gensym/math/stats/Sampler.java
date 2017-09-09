package com.gensym.math.stats;

import java.security.SecureRandom;

/** This class implements sampling without replacement */
public class Sampler extends Object {
	private int n;
	private int[] ia;
	private int nremaining;

	public Sampler(int n) {
		ia = new int[n];
		for(int i=0;i<n;i++) {
			ia[i] = i;
		}
		this.n = n;
		nremaining = n;
	}

	public int nextSample() {
		if (nremaining <= 0) {
			return -1;
		}
		SecureRandom random = new SecureRandom();
		int samplePoint = (int) Math.floor(nremaining*random.nextDouble());
		int sample = ia[samplePoint];
		// swap used element to just beyond the partition 
		nremaining--;
		ia[samplePoint] = ia[nremaining];
		ia[nremaining]=sample;
		return sample;
	}

	/** Resets sampler so it can sample any integer up to ndata */
	public void reset() {
		nremaining = n;
	}

}