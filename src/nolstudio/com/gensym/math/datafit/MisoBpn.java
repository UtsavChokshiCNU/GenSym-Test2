package com.gensym.math.datafit;

import java.io.*;
import java.security.SecureRandom;
import java.util.*;
import com.gensym.math.*;
import com.gensym.math.matrix.*;

public class MisoBpn extends TrainableModel implements Serializable {
	static final long serialVersionUID = 1L;
	protected double[] weights;	
	public int nweights;
	public static final double SIGMOID_LIM = Math.log(Double.MAX_VALUE);
	public static final double NEG_SIGMOID_LIM = - SIGMOID_LIM;
	public final double STEP_TOL = 0.001;
	public final double ABS_TOL = 0.001;

	public MisoBpn(ArchitectureParameters AP) throws MathException {
		super(AP);
		// initialize weights to small random numbers
		if (AP.nout != 1) {
			this.AP = null;
			throw new MathException("Cannot create a MisoBpn with more than one output");
		}
		int nin=AP.nin, nhidden = AP.nhidden;
		nweights = (nin+1)*nhidden + nhidden + 1;
		weights = new double[nweights];
		SecureRandom random = new SecureRandom();
		for (int i=0;i<nweights;i++){
			weights[i] = 0.1*random.nextDouble();
		}
	}

/*	public void MisoBpn(String Filename) throws IOException {
		File SourceFile = new File(Filename);	
		BufferedReader Source = null;
		int nhidden = AP.nhidden, nin = AP.nin, nout = AP.nout;
		Source = new BufferedReader(new FileReader(SourceFile));
		Source.write("1; Version of this file save/restore protocol");
		Source.newLine();
		Source.write("3; Number of layers");
		Source.newLine();
		Source.write(""+nin+", "+nhidden+", 1; Layer sizes of network");
		Source.newLine();
		Source.write("0, 1, 0 ; Transfer functions of network");
		Source.newLine();
		double w;
		int from, to, from1, to1, outputweight=nweights-nhidden-1;
		for(from=0;from<=nin;from++) {   // le to include bias
			from1 = from + 1;
			for(to=0;to<nhidden;to++) {
				to1 = to + 1;
				w = weights[from + to*(nin+1)];
				Source.write(""+w+" ; "+from1+" "+to1+" 1");
				Source.newLine();
			}
		}
		for(from=0;from<=nhidden;from++) {
			from1 = from + 1;
			w = weights[outputweight + from];
			Source.write(""+w+" ; "+from1+" 1 2");
			Source.newLine();		
		}
		Source.close();
	} */


	/** Calculates values of Y, given X, using the current weights */
	@Override
	public void evaluate(Matrix X, Matrix Y) throws MathException {
		int row, weight, ndata = X.getRows();
		int nhidden = AP.nhidden, nin = AP.nin;
		double u, output;
		Y.redimension(ndata,1);
		int inputnode, hiddennode, outputweight=nweights-nhidden-1;
		for(row=0;row<ndata;row++) {
			// hidden layer
			for(output=0.0,weight=0,hiddennode=0;hiddennode<nhidden;hiddennode++) {
				u = 0.0;
				for(inputnode=0;inputnode<nin;inputnode++)
					u += X.get(row,inputnode)*weights[weight++];
				u += weights[weight++];  //bias
				if (u>=SIGMOID_LIM){
					u = 1.0;  // sigmoid
				} else if (u<=NEG_SIGMOID_LIM){
					u = -1.0;
				}else{
					u = 2.0/(1.0 + Math.exp(-u)) - 1.0;  
				}
				output += u*weights[outputweight+hiddennode];
			}
			output += weights[nweights-1];  // hidden layer bias
			Y.set(row,0,output);
		}
	}

	/** X is a matrix and Y is a vector */
	@Override
	public void learn(Matrix X, Matrix Y) throws MathException {
		int nhidden = AP.nhidden, nin = AP.nin, ndata = X.getRows();
		int i,j,l,maxIters = 1000;
		double abstol = ABS_TOL*ndata;
		double chisq,ochisq,alamda=1.0;
		Matrix Xmean = Matlib.createMatrix();
		Matrix Ymean = Matlib.createMatrix();
		Matrix Xstd = Matlib.createMatrix();
		Matrix Ystd = Matlib.createMatrix();
		Matrix Xnorm = Matlib.createMatrix();
		Matrix Ynorm = Matlib.createMatrix();
		Matlib.mean(X,Xmean);
		Matlib.stdnonzero(X,Xstd);
		Matlib.mean(Y,Ymean);
		Matlib.stdnonzero(Y,Ystd);
		Matlib.normalize(X,Xmean,Xstd,Xnorm);
		Matlib.normalize(Y,Ymean,Ystd,Ynorm); 
		// store x and y as transposes to minimize the number of 
		// objects required
		Matlib.transpose(Xnorm,Xnorm);
		double[][] x = Matlib.create2DArray(Xnorm);
		Matlib.transpose(Ynorm,Ynorm);
		double[] y = Matlib.create1DArray(Ynorm);
		double[] wtry = new double[nweights];
		double[][] covar = new double[nweights][nweights];  
		double[][] alpha = new double[nweights][nweights]; 
		double[] beta = new double[nweights]; 
		double[] dw = new double[nweights];
		double[] zeros = new double[nweights];
		double[] dydw = new double[nweights];
		double[] act = new double[nhidden];
		double[] delta = new double[nhidden];
		double[] bestweights = new double[nweights];
		SecureRandom random = new SecureRandom();
		for(j=0;j<nweights;j++){
			zeros[j] = 0.0;
		}
		for (i=0;i<nweights;i++){
			weights[i] = random.nextDouble() - 0.5; 
		}
		ochisq = chisq = mrqcof(x,y,ndata,weights,alpha,beta,zeros,delta,act,dydw);
		int iter=1,smallSteps=0,rejectedSteps=0;
		// main loop
		while(iter<=maxIters && smallSteps<4 && rejectedSteps<8 && chisq>abstol) { 
//System.out.println("iteration "+iter+" rms error = "+Math.sqrt(chisq/ndata));
			for(j=0;j<nweights;j++) {
				System.arraycopy(alpha[j],0,covar[j],0,nweights);
				covar[j][j]=alpha[j][j]*(1.0+alamda);
			}
			try{
				Algorithms.cholsky(covar,nweights,beta,dw); 
			} catch (MathException e) {
				rejectedSteps = 9999;   // staturated one or more nodes in the net -- stuck.
			}
			for (l=0;l<nweights;l++){
				wtry[l] = weights[l] + dw[l];
			}
			chisq = mrqcof(x,y,ndata, wtry,covar,dw,zeros,delta,act,dydw);
			if(chisq>=ochisq) { // a bad step
				rejectedSteps++;
				alamda *= 20.0;
				chisq=ochisq;
			}
			else {  // a good step
				System.arraycopy(wtry,0,weights,0,nweights);
				if(Math.abs((ochisq-chisq)/ochisq) < STEP_TOL){
					smallSteps++;
				}
				else smallSteps=rejectedSteps=0;  // a significant step, reset counters
				alamda *= 0.5;
				ochisq=chisq;
				for(j=0;j<nweights;j++) {
					System.arraycopy(covar[j],0,alpha[j],0,nweights);
					beta[j] = dw[j];
				}
			}
			iter++;
		}
		incorporateScaleFactors(Xmean, Xstd, Ymean, Ystd);
		Matlib.clear(Xnorm);
		Matlib.clear(Ynorm);
		Matlib.clear(Xmean);
		Matlib.clear(Ymean);
		Matlib.clear(Xstd);
		Matlib.clear(Ystd);
	}
	
	private double mrqcof(double[][] x, double[] y, int ndata, double[] weights, double[][] alpha, double[] beta, 
		double[] zeros, double[] delta, double[] act, double[] dydw) throws MathException {
		double TINY = 1.e-100;
		int nhidden = AP.nhidden, nin = AP.nin;
		int j,k,l,m;
		int count,row,weight,inputnode, hiddennode, outputweight=nweights-nhidden-1;
		double wt,dy,csq=0.0,u,output,activation,dum;
		for (j=0;j<nweights;j++){
			System.arraycopy(zeros,0,alpha[j],0,nweights);
		}
		System.arraycopy(zeros,0,beta,0,nweights);
		for(row=0;row<ndata;row++) {
			for(output=0.0,weight=0,hiddennode=0;hiddennode<nhidden;hiddennode++) {
				for(u=0.0,inputnode=0;inputnode<nin;inputnode++)
					u += x[inputnode][row]*weights[weight++];
				u += weights[weight++]; // bias
				/*if(u>=0.0) {u2 = 2.0/(u+2.0); dum = u2*u2; act[hiddennode] = 1.0 - dum;}
				else {u2 = 2.0/(2.0-u);dum = u2*u2;act[hiddennode] = dum - 1.0;}
				delta[hiddennode] = dum*u2*weights[outputweight+hiddennode];*/
				if (u>=SIGMOID_LIM){
					activation = 1.0;  // sigmoid
				}else if (u<=NEG_SIGMOID_LIM){
					activation = -1.0;
				}else{
					activation = 2.0/(1.0 + Math.exp(-u)) - 1.0;  
				}
				act[hiddennode] = activation;
				delta[hiddennode] = TINY + 0.5*(1.0+activation)*(1.0-activation)*weights[outputweight+hiddennode];
				output += activation*weights[outputweight+hiddennode];
			}
			output += weights[nweights-1];  // hidden layer bias
			dy = y[row] - output;
			for(weight=0,hiddennode=0;hiddennode<nhidden;hiddennode++) {
				for(inputnode=0;inputnode<nin;inputnode++,weight++) 
					dydw[weight]=delta[hiddennode]*x[inputnode][row];
				dydw[weight]=delta[hiddennode]; // bias
				weight++;
				dydw[outputweight+hiddennode] = act[hiddennode];
			}
			dydw[nweights-1] = 1.0;
			for (l=0;l<nweights;l++) {
				wt=dydw[l];
				for (m=0;m<=l;m++){
					alpha[l][m] += wt*dydw[m];
				}
				beta[l] += dy*wt;
			}
			csq += dy*dy;
		}
		for (j=1;j<nweights;j++){
			for (k=0;k<j;k++){
				alpha[k][j]=alpha[j][k];
			}
		}
		return csq;
	}

	private void incorporateScaleFactors(Matrix Xmean, Matrix Xstd, Matrix Ymean, Matrix Ystd) {
		double xm,xs,w,ym=Ymean.get(0,0),ys=Ystd.get(0,0);
		int nhidden = AP.nhidden, nin = AP.nin;
		int weight=0,hiddennode,inputnode,biasweight,outputweight=nweights-nhidden-1;
		for(hiddennode=0;hiddennode<nhidden;hiddennode++) {
			// input layer weights
			biasweight = weight+nin;
			for(inputnode=0;inputnode<nin;inputnode++) {
				xm = Xmean.get(0,inputnode);
				xs = Xstd.get(0,inputnode);
				w = weights[weight];
				weights[biasweight] -= w*xm/xs;
				weights[weight] = w/xs;
				weight++;
			}
			weight++; //skip bias weight, already calculated
			// output layer weights
			weights[outputweight+hiddennode] *= ys;
		}
		// lastly, the output bias
		weights[nweights-1] = ys*weights[nweights-1] + ym;
	}

	/** write a MisoBpn to a file in NOL format */
	@Override
	public void writeWeights(BufferedWriter Source) throws IOException {
		int nhidden = AP.nhidden, nin = AP.nin, nout = AP.nout;
		Source.write("1; Version of this file save/restore protocol");
		Source.newLine();
		Source.write("3; Number of layers");
		Source.newLine();
		Source.write(""+nin+", "+nhidden+", 1; Layer sizes of network");
		Source.newLine();
		Source.write("0, 1, 0 ; Transfer functions of network");
		Source.newLine();
		double w;
		int from, to, from1, to1, outputweight=nweights-nhidden-1;
		for(from=0;from<=nin;from++) {   // le to include bias
			from1 = from + 1;
			for(to=0;to<nhidden;to++) {
				to1 = to + 1;
				w = weights[from + to*(nin+1)];
				Source.write(""+w+" ; "+from1+" "+to1+" 1");
				Source.newLine();
			}
		}
		for(from=0;from<=nhidden;from++) {
			from1 = from + 1;
			w = weights[outputweight + from];
			Source.write(""+w+" ; "+from1+" 1 2");
			Source.newLine();		
		}
	}


	@Override
	public String getModelParameters(String modelName, int index) throws MathException {

		String str = "double  "+modelName+"_weights"+index+"["+3+"]["+6+"]["+5+"] =\n";
		


/*		int nhidden = AP.nhidden, nin = AP.nin, nout = AP.nout;
		Source.write("1; Version of this file save/restore protocol");
		Source.newLine();
		Source.write("3; Number of layers");
		Source.newLine();
		Source.write(""+nin+", "+nhidden+", 1; Layer sizes of network");
		Source.newLine();
		Source.write("0, 1, 0 ; Transfer functions of network");
		Source.newLine();
		double w;
		int from, to, from1, to1, outputweight=nweights-nhidden-1;
		for(from=0;from<=nin;from++) {   // le to include bias
			from1 = from + 1;
			for(to=0;to<nhidden;to++) {
				to1 = to + 1;
				w = weights[from + to*(nin+1)];
				Source.write(""+w+" ; "+from1+" "+to1+" 1");
				Source.newLine();
			}
		}
		for(from=0;from<=nhidden;from++) {
			from1 = from + 1;
			w = weights[outputweight + from];
			Source.write(""+w+" ; "+from1+" 1 2");
			Source.newLine();		
		}
		return equivalentBpn.getModelParameters(modelName);
*/
		return str;
	}
	/** write a MisoBpn to a string buffer as in C code format */
	@Override
	public void writeParamVariable(StringBuffer sb, int index) {
		int nhidden = AP.nhidden, nin = AP.nin, nout = AP.nout;
		sb.append("long nlayer"+(index+1)+" = 3;\n"); 
		sb.append("long n"+(index+1)+"1 = "+nin+";\n");
		sb.append("long n"+(index+1)+"2 = "+nhidden+";\n");
		sb.append("long n"+(index+1)+"3 = 1;\n");

		sb.append("long tf"+(index+1)+"[3] = {0,1,0};\n");
		sb.append("double **w"+(index+1)+"1;\n");
		sb.append("double **w"+(index+1)+"2;\n");
	}

	/** write a MisoBpn to a string buffer as in C code format */
	@Override
	public void writeMatrixInit(StringBuffer sb, int index) {
		int nhidden = AP.nhidden, nin = AP.nin, nout = AP.nout;
		sb.append("w"+(index+1)+"1 = matrix("+(nin+1)+", "+nhidden+");\n");
		sb.append("w"+(index+1)+"2 = matrix("+(nhidden+1)+", 1);\n");

	}

	/** write a MimoBpn to a string buffer as in C code format */
	@Override
	public void writeWeightAsC(StringBuffer sb, int index) {
		int nhidden = AP.nhidden, nin = AP.nin, nout = AP.nout;
		double w;
		int from, to, from1, to1, outputweight=nweights-nhidden-1;
		for(from=0;from<=nin;from++) {   // le to include bias
			from1 = from + 1;
			for(to=0;to<nhidden;to++) {
				to1 = to + 1;
				w = weights[from + to*(nin+1)];
				sb.append("w"+(index+1)+"1["+from1+"]["+to1+"] = "+ w+";\n");
			}
		}
		for(from=0;from<=nhidden;from++) {
			from1 = from + 1;
			w = weights[outputweight + from];
			sb.append("w"+(index+1)+"2["+from1+"][1] = "+ w+";\n");
		}
	}
/** Return the model information as in a Vector */
	@Override
	public Vector getParametersVector() {
		int nhidden = AP.nhidden, nin = AP.nin, nout = AP.nout;
		Vector infors = new Vector();
		infors.addElement(new Double(3));
		int[] nodes = new int[3];
		nodes[0] = nin;
		nodes[1] = nhidden;
		nodes[2] = 1;
		infors.addElement(nodes);
		int[] tf = new int[3];
		tf[0] = 0;
		tf[1] = 1;
		tf[2] = 0;
		infors.addElement(tf);
		int from, to, from1, to1, outputweight=nweights-nhidden-1;
		for(from=0;from<=nin;from++) {   // le to include bias
			from1 = from + 1;
			double[] w1 = new double[nhidden];
			for(to=0;to<nhidden;to++) {
				to1 = to + 1;
				w1[to] = weights[from + to*(nin+1)];
			}
			infors.addElement(w1);
		}
		for(from=0;from<=nhidden;from++) {
			from1 = from + 1;
			double[] w1 = new double[1];
			w1[0] = weights[outputweight + from];
			infors.addElement(w1);
		}
		return infors;
	}

	/** write a MisoBpn to a file in XML format */
	@Override
	public int writeXMLFile(final BufferedWriter target, final int indentNumber) throws IOException {
		int nhidden = AP.nhidden;
		int nin = AP.nin;
		int indent = indentNumber;
		String dataString = Utilities.indent(indent)+"<bpn>\n";
		target.write(dataString,0,dataString.length());
		indent++;
		dataString = Utilities.indent(indent)+"<numberOfLayers>"+3+"</numberOfLayers>\n";
		target.write(dataString,0,dataString.length());

		dataString = Utilities.indent(indent)+"<layer>\n";
		target.write(dataString,0,dataString.length());
		indent++;
		dataString = Utilities.indent(indent)+"<layerIndex>"+1+"</layerIndex>\n";
		target.write(dataString,0,dataString.length());
		dataString = Utilities.indent(indent)+"<layerSize>"+nin+"</layerSize>\n";
		target.write(dataString,0,dataString.length());
		dataString = Utilities.indent(indent)+"<transferFunction>"+0+"</transferFunction>\n";
		target.write(dataString,0,dataString.length());
		indent--;
		dataString = Utilities.indent(indent)+"</layer>\n";
		target.write(dataString,0,dataString.length());

		dataString = Utilities.indent(indent)+"<layer>\n";
		target.write(dataString,0,dataString.length());
		indent++;
		dataString = Utilities.indent(indent)+"<layerIndex>"+2+"</layerIndex>\n";
		target.write(dataString,0,dataString.length());
		dataString = Utilities.indent(indent)+"<layerSize>"+nhidden+"</layerSize>\n";
		target.write(dataString,0,dataString.length());
		dataString = Utilities.indent(indent)+"<transferFunction>"+1+"</transferFunction>\n";
		target.write(dataString,0,dataString.length());
		indent--;
		dataString = Utilities.indent(indent)+"</layer>\n";
		target.write(dataString,0,dataString.length());
	
		dataString = Utilities.indent(indent)+"<layer>\n";
		target.write(dataString,0,dataString.length());
		indent++;
		dataString = Utilities.indent(indent)+"<layerIndex>"+3+"</layerIndex>\n";
		target.write(dataString,0,dataString.length());
		dataString = Utilities.indent(indent)+"<layerSize>"+1+"</layerSize>\n";
		target.write(dataString,0,dataString.length());
		dataString = Utilities.indent(indent)+"<transferFunction>"+0+"</transferFunction>\n";
		target.write(dataString,0,dataString.length());
		indent--;
		dataString = Utilities.indent(indent)+"</layer>\n";
		target.write(dataString,0,dataString.length());
		double w;
		int from, to, from1, to1, outputweight=nweights-nhidden-1;
		for(from=0;from<=nin;from++) {   // le to include bias
			from1 = from + 1;
			for(to=0;to<nhidden;to++) {
				to1 = to + 1;
				w = weights[from + to*(nin+1)];
				dataString = Utilities.indent(indent)+"<nodes>\n";
				target.write(dataString,0,dataString.length());
				indent++;
				dataString = Utilities.indent(indent)+"<weight>"+w+"</weight>\n";
				target.write(dataString,0,dataString.length());
				dataString = Utilities.indent(indent)+"<layerIndex>"+1+"</layerIndex>\n";
				target.write(dataString,0,dataString.length());
				dataString = Utilities.indent(indent)+"<row>"+from1+"</row>\n";
				target.write(dataString,0,dataString.length());
				dataString = Utilities.indent(indent)+"<column>"+to1+"</column>\n";
				target.write(dataString,0,dataString.length());
				indent--;
				dataString = Utilities.indent(indent)+"</nodes>\n";
				target.write(dataString,0,dataString.length());
			}
		}
		for(from=0;from<=nhidden;from++) {
			from1 = from + 1;
			w = weights[outputweight + from];
			dataString = Utilities.indent(indent)+"<nodes>\n";
			target.write(dataString,0,dataString.length());
			indent++;
			dataString = Utilities.indent(indent)+"<weight>"+w+"</weight>\n";
			target.write(dataString,0,dataString.length());
			dataString = Utilities.indent(indent)+"<layerIndex>"+2+"</layerIndex>\n";
			target.write(dataString,0,dataString.length());
			dataString = Utilities.indent(indent)+"<row>"+from1+"</row>\n";
			target.write(dataString,0,dataString.length());
			dataString = Utilities.indent(indent)+"<column>"+1+"</column>\n";
			target.write(dataString,0,dataString.length());
			indent--;
			dataString = Utilities.indent(indent)+"</nodes>\n";
			target.write(dataString,0,dataString.length());
		}
		indent--;
		dataString = Utilities.indent(indent)+"</bpn>\n";
		target.write(dataString,0,dataString.length());
		return indent;
	}
}

