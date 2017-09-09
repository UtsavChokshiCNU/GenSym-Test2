package com.gensym.math.datafit;

import java.io.*;
import java.util.*;
import com.gensym.math.*;
import com.gensym.math.matrix.*;
import com.gensym.classes.FloatArray;
import com.gensym.classes.IntegerArray;

/** 5-layer Mimo Backprop network with linear or sigmoidal layers.
Not trainable, but compatible with NOL Classic.  To create a MimoBpn, 
pass a trained model to its constructor method. */

public class MimoBpn implements Model, Serializable {
	static final long serialVersionUID = 1L;
	protected Matrix[] weights;
	public int nlayers;
	public int[] tf;  // transfer functions 0=linear, 1=sigmoidal
	public int[] nodes;  // layer sizes
	public static final double SIGMOID_LIM = Math.log(Double.MAX_VALUE);
	public static final double NEG_SIGMOID_LIM = - SIGMOID_LIM;
	
	public MimoBpn() {
		super();
	}

	public MimoBpn(SisoBpn source) throws MathException {
		// Linear pass-through is approximated with an extra sigmoidal unit
		// whose output is approximately equal to the input (x) value.
		// The linear range is 1.0e-12 < abs(u) < 0.05.
		// (Below 1.0e-12, truncation errors occur; above 0.05, nonlinearities).
		// Scaling strategy assumes x is order(1), so multiply by 1.e-7
		// before the node, and 2.e7*linearWt after the node.  Factor of 2 is
		// required because the slope of the sigmoid is 1/2 as it crosses the origin.
		// Approximation will fail if abs(x) > 1.e5 or abs(x) < 1.e-5.
		super();
		int i,j,k;
		ArchitectureParameters AP = source.getArchitectureParameters();
		int nin = AP.nin;
		int nout = AP.nout;
		int nhidden = AP.nhidden + 1;  // one extra hidden node for linear pass-through
		tf = new int[3];
		tf[0]=0; 
		tf[1]=1; 
		tf[2]=0;
		nodes = new int[3];
		nodes[0] = nin;  // allow for bias
		nodes[1] = nhidden;  // allow for bias
		nodes[2] = nout;
		nlayers = 3;
		this.weights = new Matrix[2];
		Matrix w1 = Matlib.zeros(nin+1,nhidden);
		Matrix w2 = Matlib.zeros(nhidden+1,nout);
		// load weights columnwise into w1
		for(k=0,j=0;j<nhidden-1;j++) {  // skip the extra hidden node for now
			for(i=0;i<=nin;i++) {  // include bias
				w1.set(i,j,source.weights[k]);
				k++;
			}
		}
		// load weights columnwise into w2
		for(i=0;i<nhidden-1;i++) {  // again, skip last hidden node
			w2.set(i,0,source.weights[k]);
			k++;
		}
		// extra weights in w1, w2
		w2.set(nhidden-1,0,2.e7*source.weights[source.nweights-1]);  // linear weight from last hidden node
		w2.set(nhidden,0,source.weights[source.nweights-2]); // outputBias
		w1.set(0,nhidden-1,1.e-7);  // weight to extra hidden node
		weights[0] = w1;
		weights[1] = w2;
	}

	public MimoBpn(Pls source) throws MathException {
		// turn Pls model into a linear three-layer net
		super();
		int i,j,k;
		ArchitectureParameters AP = source.getArchitectureParameters();
		int nin = AP.nin;
		int nout = AP.nout;
		int nhidden = AP.nfactors;
		tf = new int[3];
		tf[0]=0; 
		tf[1]=0; 
		tf[2]=0;  // linear hidden layer
		nodes = new int[3];
		nodes[0] = nin;  
		nodes[1] = nhidden; 
		nodes[2] = nout;
		nlayers = 3;
		weights = new Matrix[2];
		Matrix w1 = Matlib.createMatrix();
		Matrix w2 = Matlib.createMatrix();
		Matrix temp = Matlib.createMatrix();
		Matlib.copy(source.R,w1);
		Matlib.multiply(source.Xmean,source.R,temp);   // (X - Xmean)*R = X*R - Xmean*R
		Matlib.unaryMinus(temp,temp);
		Matlib.appendRows(w1,temp,w1);  // bias row appended to bottom of w1
		Matlib.copy(source.S,w2);
		Matlib.transpose(source.B,temp);  // temp is nfactors by 1 (column vector)
		Matlib.multiplyElements(w2,temp,w2);  // fold B into rows of w2
		Matlib.appendRows(w2,source.Ymean,w2);
		weights[0] = w1;
		weights[1] = w2;
		temp.clear();
	}

	public MimoBpn(MisoBpn source) throws MathException {
		// convert three-layer miso net to mimo net
		super();
		int i,j,k;
		ArchitectureParameters AP = source.getArchitectureParameters();
		int nin = AP.nin;
		int nout = AP.nout;  // always 1
		int nhidden = AP.nhidden;
//System.out.println("nin="+nin+" nout = "+nout+" hidden = "+nhidden);
		tf = new int[3];
		tf[0]=0; 
		tf[1]=1; 
		tf[2]=0;
		nodes = new int[3];
		nodes[0] = nin; 
		nodes[1] = nhidden;
		nodes[2] = nout;
		nlayers = 3;
		this.weights = new Matrix[2];
		Matrix w1 = Matlib.zeros(nin+1,nhidden);
		Matrix w2 = Matlib.zeros(nhidden+1,nout);
		// load weights columnwise into w1
		for(k=0,j=0;j<nhidden;j++) {
			for(i=0;i<=nin;i++) {  // include bias
				w1.set(i,j,source.weights[k]);
				k++;
			}
		}
		// load weights columnwise into w2
		for(i=0;i<=nhidden;i++) {
			w2.set(i,0,source.weights[k]);
			k++;
		}
		weights[0] = w1;
		weights[1] = w2;
	}

	private MimoBpn(MimoBpn[] nets) throws MathException {
		// Convert a layer that is comprised of one or more single-output 
		// nets to one large Mimo net.  The inputs must be three-layer,
		// single-output networks, with sigmoidal hidden layer.
		super();
		int i,k;
		tf = new int[3];
		tf[0]=0; 
		tf[1]=1; 
		tf[2]=0;
		nodes = new int[3];
		nlayers = 3;
		int nout = nets.length;
		MimoBpn source = nets[0];
		int nin = source.nodes[0];
		int nhidden = 0;
		for(i=0;i<nout;i++){
			nhidden += nets[i].nodes[1];
		}
		nodes[0] = nin;  
		nodes[1] = nhidden; 
		nodes[2] = nout;
//System.out.println("MimoBpn[] to Mimo: nin = "+nin+" nhidden = "+nhidden+" nout = "+nout);
		this.weights = new Matrix[2];
		Matrix w1 = Matlib.createMatrix(0,0);
		Matrix w2 = Matlib.zeros(nhidden+1,nout);
		// append first layer weight matrices side-by-side
		for(i=0;i<nout;i++) {
			Matrix w1i = nets[i].weights[0];
			Matlib.appendColumns(w1,w1i,w1);
		}
		// second-layer matrices are block diagonal, with biases in last row
		for(i=0,k=0;i<nout;i++) {
			Matrix w2i = nets[i].weights[1];
			Matlib.setPart(w2,w2i,k,i,w2); 
			k += nets[i].nodes[1];
			// move bias to last row
			double bias = w2.get(k,i);
			w2.set(k,i,0.0);
			w2.set(nhidden,i,bias);
		}
		weights[0] = w1;
		weights[1] = w2;
	}

	public MimoBpn(PlsBpn source) throws MathException {
		// convert to a four-layer net
		super();
		int i,j,k;
		ArchitectureParameters AP = source.getArchitectureParameters();
		int nin = AP.nin;
		int nout = AP.nout;
		int nfactors = AP.nfactors;
		int nhidden = AP.nhidden;
		tf = new int[4];
		tf[0]=0; 
		tf[1]=0; 
		tf[2]=1; 
		tf[3]=0;  
		nodes = new int[4];
		nodes[0] = nin;
		nodes[1] = nfactors;
		nodes[2] = nout*nhidden;    // MK FIX 5/19, nhidden is per output
		nodes[3] = nout;
		nlayers = 4;
		weights = new Matrix[3];
		Matrix w1 = Matlib.createMatrix();
		Matrix temp = Matlib.createMatrix();
		// Since (X - Xmean)*R = X*R - Xmean*R, R = w1 and bias = - Xmean*R
		Matlib.copy(source.R,w1);
		Matlib.multiply(source.Xmean,source.R,temp);   
		Matlib.unaryMinus(temp,temp);
		Matlib.appendRows(w1,temp,w1);  // bias row appended to bottom of w1
		// Now convert plurality of output nets to a single MimoBpn
		MimoBpn[] singleNets = new MimoBpn[nout];
		for(i=0;i<nout;i++) {
			MisoBpn misonet = (MisoBpn) source.Nets.elementAt(i);
			MimoBpn mimonet = new MimoBpn(misonet);
			singleNets[i] = mimonet;
		}
		MimoBpn combinedNet = new MimoBpn(singleNets);
		weights[0] = w1;
		weights[1] = combinedNet.weights[0];
		weights[2] = combinedNet.weights[1];
		temp.clear();
	}

	public MimoBpn(Nlpls source) throws MathException {
		// turn Nlpls model into a five-layer net
		super();
		int i,j,k;
		ArchitectureParameters AP = source.getArchitectureParameters();
		int nin = AP.nin;
		int nout = AP.nout;
		int nfactors = AP.nfactors;
		int nhidden = AP.nhidden;
		tf = new int[5];
		tf[0]=0; 
		tf[1]=0; 
		tf[2]=1; 
		tf[3]=0; 
		tf[4]=0;  // linear hidden layer
		nodes = new int[5];
		nodes[0] = nin;  
		nodes[1] = nfactors;
		nodes[2] = nhidden + nfactors;  // one extra hidden node for each siso net, accounting for pass-through
		nodes[3] = nfactors;
		nodes[4] = nout;
		nlayers = 5;
		weights = new Matrix[4];
		Matrix w1 = Matlib.createMatrix();
		Matrix w4 = Matlib.createMatrix();
		Matrix temp = Matlib.createMatrix();
		Matlib.copy(source.R,w1);
		Matlib.multiply(source.Xmean,source.R,temp);   // (X - Xmean)*R = X*R - Xmean*R
		Matlib.unaryMinus(temp,temp);
		Matlib.appendRows(w1,temp,w1);  // bias row appended to bottom of w1
		Matlib.copy(source.S,w4);
		Matlib.appendRows(w4,source.Ymean,w4);
		weights[0] = w1;
		weights[3] = w4;
		temp.clear();
		// convert internal SisoBpns to one MimoBpn
		MimoBpn[] singleNets = new MimoBpn[nfactors];
		for(i=0;i<nfactors;i++) {
			SisoBpn sisonet = (SisoBpn) source.Nets.elementAt(i);
			MimoBpn mimonet = new MimoBpn(sisonet);
			mimonet.addBlankInputs(nfactors,i);
			singleNets[i] = mimonet;
		}
		MimoBpn combinedNet = new MimoBpn(singleNets);
		weights[1] = combinedNet.weights[0];
		weights[2] = combinedNet.weights[1];
	}

	/** pad a single-input network out to nin inputs, making the current input node
	appear on input m.  To do this, take the first row of the current weights and 
	make it the m-th row; take the last (bias) row, and make it the last (bias) row
	of the new weight matrix. */
	private void addBlankInputs(int nin, int m) throws MathException {
		int nhidden = nodes[1];
		Matrix w1 = weights[0];
		Matrix w1new = Matlib.zeros(nin+1,nhidden);
		Matrix row = Matlib.createMatrix(1,nhidden);
		Matlib.getRow(w1,0,row);
		Matlib.setPart(w1new,row,m,0,w1new);
		Matlib.getRow(w1,1,row);
		Matlib.setPart(w1new,row,nin,0,w1new);   // last row of w1new
		row.clear();
		w1.clear();
		weights[0]=w1new;
		nodes[0]=nin;
	}

	/** Calculates values of Y, given X, using the current weights */
	@Override
	public void evaluate(Matrix X, Matrix Y) throws MathException {
//	System.out.println("in evaluate");
		int nrows = X.getRows();
		Matrix u = Matlib.createMatrix();
		Matrix ones = Matlib.ones(nrows,1);
//System.out.println("nrows="+nrows);
//Matlib.disp(weights[0],"weights[0]=");
//Matlib.disp(weights[1],"weights[1]=");

		if(tf[0]==1) {
			Matlib.copy(X,u);
			Matlib.sigmoid(u,u);
			Matlib.appendColumns(u,ones,u);
		} else Matlib.appendColumns(X,ones,u);
		for(int l=0;l<nlayers-1;l++) {
			Matlib.multiply(u,weights[l],u);
			if(tf[l+1]==1){
				Matlib.sigmoid(u,u);
			}
//if(l==0)Matlib.disp(u,"u=");
			if(l==nlayers-2){
				Matlib.copy(u,Y);
			}else{
				Matlib.appendColumns(u,ones,u);
			}
		}
//		Matlib.disp(Y,"YP=");
		u.clear();
		ones.clear();
	}

	/** write a MimoBpn to a file in NOL format */
	public void writeWeights(BufferedWriter Source) throws IOException {
		Source.write("1; Version of this file save/restore protocol");
		Source.newLine();
		Source.write(nlayers+"; Number of layers");
		Source.newLine();
		Source.write(""+nodes[0]);
		for(int i=1;i<nlayers;i++){
			Source.write(", "+nodes[i]);
		}
		Source.write("; Layer sizes of network");
		Source.newLine();
		Source.write(""+tf[0]);
		for(int i=1;i<nlayers;i++){
			Source.write(", "+tf[i]);
		}
		Source.write("; Transfer functions of network");
		Source.newLine();
		for(int l=0;l<nlayers-1;l++) {
			Matrix w = weights[l];
//Matlib.disp(w,"weight matrix "+l+" = ");
			for(int from=0;from<=nodes[l];from++) {   // le to include bias
				for(int to=0;to<nodes[l+1];to++) {
					Source.write(w.get(from,to)+" ; "+(from+1)+" "+(to+1)+" "+(l+1));
					Source.newLine();
				}
			}
		}
	}

	@Override
	public int getNin() {
		return nodes[0];
	}

	@Override
	public int getNout() {
		return nodes[nlayers-1];
	}

	@Override
	public ArchitectureParameters getArchitectureParameters() {
		ArchitectureParameters AP = new ArchitectureParameters(getNin(), getNout(), -1, -1);
		return AP;
	}


	public String getModelParameters(String modelName, int index) throws MathException {

		String str ="SUBMODELPARAMETERS subpara"+index+";\n";
		str = str+"subpara"+index+".nLayers="+nlayers+";\n";
		str = str+"int size"+index+"["+nlayers+"]={"+nodes[0];
		for(int i=1;i<nlayers;i++){
			str = str+", "+nodes[i];
		}
		str = str+"};\n";
		str = str+"int type"+index+"["+nlayers+"]={"+tf[0];
		for(int i=1;i<nlayers;i++){
			str = str+", "+tf[i];
		}
		str = str+"};\n";
		str = str+"subpara"+index+".layerSize = size"+index+";\n";
		str = str+"subpara"+index+".funType = type"+index+";\n";
		str = str+"subpara"+index+".weights = new double **["+(nlayers-1)+"];\n";
	
		for(int l=0;l<nlayers-1;l++){
			str = str+"double  "+modelName+"weights"+index+"_"+l+"["+(nodes[l]+1)+"]["+nodes[l+1]+"]=\n {";
			Matrix w = weights[l];
			for(int from=0;from<=nodes[l];from++) {   // le to include bias
				str = str+"{"+w.get(from,0)+"\n";
				for(int to=1;to<nodes[l+1];to++) {
					str = str+","+w.get(from,to)+"\n";
				}
				if(from<nodes[l]){
					str = str+"},\n";
				}else{
					str = str+"}";
				}
			}
			str = str+"};\n";
			str = str+"subpara"+index+".weights["+l+"]=new double*["+(nodes[l]+1)+"];\n";
			str = str+"for(j=0;j<"+(nodes[l]+1)+";j++){\n";
			str = str+"subpara"+index+".weights["+l+"][j]=new double["+nodes[l+1]+"];\n";
			str = str+"for(t=0;t<"+nodes[l+1]+";t++){\n";
			str = str+"subpara"+index+".weights["+l+"][j][t]="+modelName+"weights"+index+"_"+l+"[j][t];\n}\n}\n";
		}
		return str;
	}


	/** write a MimoBpn to a string buffer as in C code format */
	public void writeParamVariable(StringBuffer sb, int index) {
		sb.append("long nlayer"+(index+1)+" = "+nlayers+";\n"); 
		for(int i=0;i<nlayers;i++){
			sb.append("long n"+(index+1)+""+(i+1)+" = "+nodes[i]+";\n");
		}
		sb.append("long tf"+(index+1)+"["+nlayers+"] = {");
		sb.append(tf[0]);
		for(int i=1;i<nlayers;i++){
			sb.append(", "+tf[i]);
		}
		sb.append("};\n");
		for(int i=1;i<nlayers;i++)
			sb.append("double **w"+(index+1)+""+i+";\n");
	}


	/** write a MisoBpn to a string buffer as in C code format */
	public void writeMatrixInit(StringBuffer sb, int index) {
		for(int i=1;i<nlayers;i++)
			sb.append("w"+(index+1)+""+i+" = matrix("+(nodes[i-1]+1)+","+nodes[i]+");\n");
	}

	/** write a MimoBpn to a string buffer as in C code format */
	public void writeWeightAsC(StringBuffer sb, int index) {
		for(int l=0;l<nlayers-1;l++) {
			Matrix w = weights[l];
//Matlib.disp(w,"weight matrix "+l+" = ");
			for(int from=0;from<=nodes[l];from++) {   // le to include bias
				for(int to=0;to<nodes[l+1];to++) {
					sb.append("w"+(index+1)+""+(l+1)+"["+from+"]["+to+"] = "+ w.get(from,to)+";\n");
				}
			}
		}
	}

/** Return the model information as in a Vector */
	public Vector getParametersVector() {
		Vector infors = new Vector();
		infors.addElement(nlayers);
		infors.addElement(nodes);
		infors.addElement(tf);
		
		for(int l=0;l<nlayers-1;l++) {
			Matrix w = weights[l];
			for(int from=0;from<=nodes[l];from++) {
				double[] w1 = new double[nodes[l+1]];
				for(int to=0;to<nodes[l+1];to++) {
					w1[to] = w.get(from,to);
				}
				infors.addElement(w1);
			}
		}
		return infors;
	}

/** Set the model information as in a Vector */
	public void setParametersVector(Vector params) {
		try{
			nlayers = ((Number)params.elementAt(0)).intValue();
	System.out.println("Mimobpn nlayers="+nlayers);
			nodes  = ((IntegerArray)params.elementAt(1)).getIntegerArrayContents();
	System.out.println("Mimobpn nodes="+nodes[0]);
			tf  = ((IntegerArray)params.elementAt(2)).getIntegerArrayContents();
	System.out.println("Mimobpn tf="+tf[0]);
			int count = 3;
			weights = new Matrix[nlayers - 1];
			for(int i=0;i<weights.length;i++) {
				Matrix w = Matlib.zeros(nodes[i]+1, nodes[i+1]);
				weights[i] = w;
			}
			for(int l=0;l<nlayers-1;l++) {
				Matrix w = weights[l];
				for(int from=0;from<=nodes[l];from++) {
					double[] w1 = ((FloatArray)params.elementAt(count)).getFloatArrayContents();
					for(int to=0;to<nodes[l+1];to++) {
						w.set( from,to,w1[to]);
					}
					count = count +1;
				}
			}
		}catch(Exception evt){
			System.out.println("evt="+evt.toString());
		}
	}


	/** write a MimoBpn to a file in XML format */
	public int writeXMLFile(final BufferedWriter target, final int indentNumber) throws IOException {

		int indent = indentNumber;
		String dataString = Utilities.indent(indent)+"<bpn>\n";
		target.write(dataString,0,dataString.length());
		indent++;
		dataString = Utilities.indent(indent)+"<layer index=\"0\">\n";
		target.write(dataString,0,dataString.length());
		indent++;
		for(int i=0;i<nodes[0];i++){
			dataString = Utilities.indent(indent)+"<node index=\""+i+"\" type=\"input\"/>\n";
			target.write(dataString,0,dataString.length());
		}
		dataString = Utilities.indent(indent)+"<node index=\""+nodes[0]+"\" type=\"bias\"/>\n";
		target.write(dataString,0,dataString.length());
		indent--;
		dataString = Utilities.indent(indent)+"</layer>\n";
		target.write(dataString,0,dataString.length());

		for(int l=0;l<nodes.length-1;l++){
			Matrix w = weights[l];
			String tfs = "linear";
            if (tf[l+1] == 1){
            	tfs = "sigmoid";
            }
			dataString = Utilities.indent(indent)+"<layer index=\""+(l+1)+"\" transferFunction=\""+tfs+"\">\n";
			target.write(dataString,0,dataString.length());
			indent++;

			for(int to=0;to<nodes[l+1];to++) {
				if (l == nodes.length-2) {
					dataString = Utilities.indent(indent)+"<node index=\""+to+"\" type=\"output\">\n";
				}else {
					dataString = Utilities.indent(indent)+"<node index=\""+to+"\">\n";
				}
				target.write(dataString,0,dataString.length());
				indent++;
				for(int from=0;from<=nodes[l];from++) {   
					dataString = Utilities.indent(indent)+"<input layer=\""+l+"\" node=\""+from+"\" weight=\""+w.get(from,to)+"\"/>\n";
					target.write(dataString,0,dataString.length());
				}
				indent--;
				dataString = Utilities.indent(indent)+"</node>\n";
				target.write(dataString,0,dataString.length());
			}
 			if (l != nodes.length-2){
				dataString = Utilities.indent(indent)+"<node index=\""+nodes[l+1]+"\" type=\"bias\"/>\n";
				target.write(dataString,0,dataString.length());
			}
			indent--;
			dataString = Utilities.indent(indent)+"</layer>\n";
			target.write(dataString,0,dataString.length());
		}
		indent--;
		dataString = Utilities.indent(indent)+"</bpn>\n";
		target.write(dataString,0,dataString.length());

		return indent;
	}

	public MimoBpn(final ArchitectureParameters AP, final int[] tf, final int[] nodes) {
		super();
		this.tf = tf;
		this.nodes = nodes;
		int layerCount = nodes.length;
		weights = new Matrix[layerCount - 1];
		for(int i=0;i<weights.length;i++) {
			Matrix w = Matlib.zeros(nodes[i], nodes[i+1]);
			weights[i] = w;
		}
	}
/** Set the model information as in a Vector */
	public int setParametersVector(final Vector params, final int count) {
		int countLocal = count;
System.out.println("Mimobpn count="+countLocal);
		nlayers = (Integer.parseInt(params.elementAt(countLocal).toString()));
System.out.println("Mimobpn nlayers="+nlayers);
		countLocal = countLocal +1;
		nodes  = (int[])params.elementAt(countLocal);
System.out.println("Mimobpn nodes="+nodes[0]);
		countLocal = countLocal +1;
		tf  = (int[])params.elementAt(countLocal);
		countLocal = countLocal +1;
		weights = new Matrix[nlayers - 1];
		for(int i=0;i<weights.length;i++) {
			Matrix w = Matlib.zeros(nodes[i], nodes[i+1]);
			weights[i] = w;
		}
		for(int l=0;l<nlayers-1;l++) {
			Matrix w = weights[l];
			for(int from=0;from<=nodes[l];from++) {
				double[] w1 = (double[])params.elementAt(countLocal);
				for(int to=0;to<nodes[l+1];to++) {
					w.set( from,to,w1[to]);
				}
				countLocal = countLocal +1;
			}
		}
		return countLocal;
	}
}

