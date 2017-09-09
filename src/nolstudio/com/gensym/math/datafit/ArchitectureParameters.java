package com.gensym.math.datafit;

import java.io.*;

import com.gensym.math.matrix.Matrix;
import com.gensym.math.MathException;

public class ArchitectureParameters implements Serializable {
	static final long serialVersionUID = 1L;
	public int nin;
	public int nout;
	public int nhidden;
	public int nfactors;
	public double trainingFraction;

	public ArchitectureParameters(int nin, int nout, int nhidden, int nfactors) {
		this.nin = nin;
		this.nout = nout;
		this.nhidden = nhidden;
		this.nfactors = nfactors;
	}
	
	/**
	 * Copy constructor for cloning. 
	 * @param archParams
	 */
	public ArchitectureParameters(ArchitectureParameters archParams) {
		this.nin = archParams.nin;
		this.nout = archParams.nout;
		this.nhidden = archParams.nhidden;
		this.nfactors = archParams.nfactors;
	}

}