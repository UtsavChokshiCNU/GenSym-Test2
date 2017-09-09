package com.gensym.jgope.deploy;

import java.io.*;
import java.lang.*;


/** An OnlineManager object provides a way to run the GopeStudio optimization online.
* The object maintains a data buffer for storing the online data. 
* The steps for online deployment: 
* 1. Create a OnlineManager using default constructor.
* 2. Load exported optimization parameters from data file.
* 3. You can check the variable names and tags by call corresponding methods. 
* 4. Follow the user's guide for setting the optimization parameters.
* 5. Calculate the optimization.
* 6. Follow the user's guide to get output values. 
*/
public class OnlineManager {

	static final long serialVersionUID = 1L;

	private boolean isCalculated;
	private int objsen = 1;
	private String[] indepNames;
	private String[] extraNames;
	private double[] lb = new double[0];
	private double[] ub = new double[0];
	private double[] exog = new double[0];
	private double[] rhs = new double[0];
	private double[] initx;
	private int status;
	private double[] resultx;
	private double objective;
	private int numberOfConst;
	private int numberOfVar;

	private String dllName = "";
	private String name;
	private String sense ="";
	
	private native double[] jsolveNLP(int objsen, double[] x, double[] lb, double[] ub, double[] exog, int numberOfX, int numberOfConst, double[] rhs, String sense);
	private JGopeG2Gateway g2Gateway;
	

/** Create an OnlineManager with all parameters */
	public OnlineManager(String name) {
		this.name = name;
		isCalculated = false;
	}

	public void setG2Gateway(JGopeG2Gateway g2Gateway){
		this.g2Gateway = g2Gateway;
	}
	
	public void setDLLName(String name){
		dllName = name;
	}

	public boolean isCalculated(){
		return isCalculated;
	}

	public int getStatus(){
		return status;
	}

	public double[] getResultX(){
		return resultx;
	}

	public double getObjective(){
		return objective;
	}

	public void setInitX(double[] x){
		isCalculated = false;
		initx = x;
		numberOfVar = x.length;
	}
	
	public void setIndepNames(String[] ns){
		isCalculated  =false;
		indepNames = ns;
	}
	
	public void setExtraNames(String[] ns){
		isCalculated  =false;
		extraNames = ns;
	}
	
	public double[] getInitX(){
		return initx;
	}
	
	public void setIndependentUpperBounds(double[] bounds){
		isCalculated  =false;
		ub = bounds;
	}
	
	public double[] getIndependentUpperBounds(){
		return ub;
	}
	
	public void setIndependentLowerBounds(double[] bounds){
		isCalculated  =false;
		lb = bounds;
	}

	public double[] getIndependentLowerBounds(){
		return lb;
	}
	
	public void setExtraParameters(double[] param){
		isCalculated  =false;
		exog = param;
	}

	public double[] getExtraParameters(){
		return exog;
	}

	public int getNumberOfIndependentVariables(){
		return indepNames.length;
	}

	public int getNumberOfExtraVariables(){
		return extraNames.length;
	}

	public void reset(){
		isCalculated  =false;
	}

	public void setNumberOfConstraints(int n){
		numberOfConst  =n;
	}
	
	public void setSenseForConstraints(String s){
		sense  =s;
	}
	
	public void setRhsForConstraints(double[] v){
		 rhs =v;
	}
	
	public void setMinimize(boolean flag){
		 if(flag)
			 objsen = 1;
		 else
			 objsen = -1;
	}
	
	public void run(){
		System.loadLibrary(dllName);
		if(!isCalculated){
			double[] result = jsolveNLP(objsen, initx,lb,ub,exog,numberOfVar,numberOfConst,rhs,sense);
			isCalculated = true;
			status = (int)result[0];
			objective = result[1];
			resultx = new double[initx.length];
			for(int i=0;i<resultx.length;i++){
				resultx[i] = result[i+2];
			}
		}
	}

	public double g2ObjFunction(double[] x){
		double obj = g2Gateway.g2ObjFunction(x);
		return obj;
	}

	public double g2ConstraintFunction(double[] x, int index){
		double lhs = g2Gateway.g2ConstraintFunction(x, index);
		return lhs;
	}

}

