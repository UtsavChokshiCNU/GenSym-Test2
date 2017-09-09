package com.gensym.nols.data;
/*
 */

import java.util.*;
import java.io.*;	   

import com.gensym.math.datafit.*;
import com.gensym.math.matrix.*;
import com.gensym.math.*;

public class NolModelTrainer implements Runnable,Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	
	public native void jbpn_trainer(String infile, String outfile);
	public native void jautoassociative_net(String infile, String outfile);
	public native void jrbfn_trainer(String infile, String outfile);
	public native void jrho_trainer(String infile, String outfile);
	public native void jfit_tester(String infile, String outfile);
	public native void jsensitivity_tester(String infile, String outfile);
	public native void joptimizer(String infile, String outfile);

	private NolModel model;
	private Vector itsListeners;

	public NolModelTrainer(NolModel model){
		super();
		this.model = model;
		itsListeners = new Vector();
	}

	public void addListener(ModelTrainerListener l) {
		itsListeners.addElement(l);
	}

	public void removeListener(ModelTrainerListener l) {
		itsListeners.removeElement(l);
	}

	private void informListeners() {
		for (int i=0; i<itsListeners.size(); ++i) {
			ModelTrainerListener l = (ModelTrainerListener) itsListeners.elementAt(i);
			l.trainingComplete();
		}
	}

	@Override
	public void run (){
		informListeners();
	}


}