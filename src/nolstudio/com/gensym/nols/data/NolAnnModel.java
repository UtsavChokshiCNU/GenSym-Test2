package com.gensym.nols.data;
/*
 *		Gensym Model Class.
 *		This class is extended from Object.class
 *		Modified 3/25/98 by Gchen
 */

import java.util.*;
import java.io.*;
import java.nio.charset.Charset;

import com.gensym.math.datafit.*;
import com.gensym.math.*;

/** Model class. */
public class NolAnnModel extends NolBpnModel{
	static final long serialVersionUID = 1L;
	protected double[] normalStd;
	protected int runMode; //0: filter noise only, 1: gross errors

/** Create a NolAnnModel object with given ClassicBpn object.*/	
	public NolAnnModel(ClassicBpn net, String name, Vector outs, 
		Vector ins, Vector oDelays, Vector iDelays, Preprocessor prep){
		super(net, name, outs, ins, oDelays, iDelays, prep);
		normalStd = new double[outs.size()];
		runMode = 0;
	}

	public void setNormalStd(double[] values){
		normalStd = values;
	}

	public double[] getNormalStd() { return normalStd; }

	public void setRunMode(int value){
		runMode = value;
	}

	public int getRunMode(){
		return runMode;
	}
	
	public void writeANNToFile(String outfile)throws IOException{
		ClassicBpn net = (ClassicBpn)model;
		File SourceFile = new File(outfile);
		
		FileOutputStream outStream = null;
	    Writer streamWriter = null;
	    BufferedWriter Source = null;
		try {
	        outStream = new FileOutputStream(SourceFile);
	        streamWriter = new OutputStreamWriter(outStream, Charset.defaultCharset());
			Source = new BufferedWriter(streamWriter);
			net.writeWeights(Source);
			Source.write(""+normalStd[0]);
			for(int i=1;i<normalStd.length;i++) {
				Source.write(", "+normalStd[i]);
			}
			Source.write("; Normal noise stdev");
			Source.newLine();
			if(runMode == 0){
				Source.write("FILTER-ONLY ; Run mode");
			}else{
				Source.write("CORRECT-GROSS-ERRORS ; Run mode");
			}
			Source.newLine();
		} finally {
			closeSilently(Source);
			closeSilently(streamWriter);
			closeSilently(outStream);
		}
	}

/** Return the model information as in a Vector */
	@Override
	public Vector getParametersVector() throws MathException {
		Vector info = super.getParametersVector();
		info.addElement(normalStd);
		info.addElement(new Double(runMode)); //0: filter noise only, 1: gross errors
		return info;
	}

/** Set the model information as in a Vector */
	@Override
	public void setParametersVector(Vector params) throws MathException {
		normalStd = (double[])params.elementAt(params.size()-2);
		runMode = ((Number)params.elementAt(params.size()-1)).intValue();
		params.removeElementAt(params.size()-1);
		params.removeElementAt(params.size()-1);
		ClassicBpn net = (ClassicBpn)getModel();
		net.setParametersVector(params);
	}
}

