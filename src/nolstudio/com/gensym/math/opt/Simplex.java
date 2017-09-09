package com.gensym.math.opt;

import java.io.*;
import java.nio.charset.Charset;

import com.gensym.math.*;
import com.gensym.math.matrix.*;	

public class Simplex extends Optimizer implements Serializable {
	static final long serialVersionUID = 1L;
	public int iteration;
	public double objectiveFunction;
	public double ftol;
	public double atol;
	public int NMAX;
	private int statusFlag = 0;	  
	private String statusMessage = "Simplex.optimize: Normal exit.";
 
	//0=converge normal;1=Feasible,but not converge(maximum iteration);
	//2=could not find feasible solution(maximum iteration);
	//3=Normal exit, but some variables hit their hard bound; 4=other error condition



	private static boolean simDebug = false;
	private transient BufferedWriter target = null;

	public Simplex() {
		super();
		// user can override any of the following settings
		ftol = 1.e-8; 
		atol = 1.e-8;
		NMAX = 100000; 
		statusFlag = 0;
	}

	public void optimize(Function F, Matrix P){
		
		if(simDebug){
			try { 
				File targetFile = new File("Simplex.log");
				target = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(targetFile), Charset.defaultCharset()));
			}catch(IOException e){		
			}
		}
		int ndim = P.getCols();
		if (P.getRows() != ndim+1){
			statusFlag = 4;
			statusMessage = "Simplex.optimize: P must contain ndim+1 trial points as its rows";
			return;
		}
		int i,ihi,ilo,inhi,j,mpts=ndim+1;
		double rtol,sum,swap,ysave,ytry,dum;
		Matrix Psum = Matlib.zeros(1,ndim);
		double[] psum = (Psum.getData())[0];
		Matrix Ptry = Matlib.zeros(1,ndim);
		double[] ptry = (Ptry.getData())[0];
		Matrix Y = Matlib.zeros(mpts,1);
		double[] y = new double[mpts];  // y is NOT the data matrix of Y
		double[][] p = P.getData();
		double[] dumm;
		iteration = 0;
		//Matrix PY = Matlib.createMatrix();
		// initialize y to contain the values of the function at the rows of p
		try{
			F.evaluate(P,Y);
		}catch(MathException evt){
			statusFlag = 4;
			statusMessage = evt.getMessage();
			Matlib.clear(Psum); 
			Matlib.clear(Ptry);	
			Matlib.clear(Y);				
			return;
		}
		for(j=0;j<mpts;j++) {
			y[j] = Y.get(j,0);  // unload the result into y
		}
		for (j=0;j<ndim;j++) {
			for (sum=0.0,i=0;i<mpts;i++) {
				sum += p[i][j];
			}
			psum[j]=sum;
		}

		if(simDebug){
			try { 
				String str = "NMAX="+NMAX;
				target.write(str,0,str.length());
				target.newLine();
				target.flush();
			}catch(IOException e){		
			}
		}		

		try{
			for (;;) {
				StringBuffer sb = new StringBuffer();		
				ilo=0;
				if (y[0]>y[1]) {
					inhi = 1;
					ihi = 0;
				} else {
					inhi = 0;
					ihi = 1;
				}
				for (i=0;i<mpts;i++) {
					if (y[i] <= y[ilo]) {
						ilo=i;
					}
					if (y[i] > y[ihi]) {
						inhi=ihi;
						ihi=i;
					} else if (y[i] > y[inhi] && i != ihi) {
						inhi=i;
					}
				}
				rtol=2.0*Math.abs(y[ihi]-y[ilo])/(Math.abs(y[ihi])+Math.abs(y[ilo]));
		//System.out.println("ilo = "+ilo+" ihi = "+ihi+" inhi = "+inhi+" rtol = "+rtol);
				// atol is needed to terminate when solution is heading toward 0.0
	/*			if (iteration >= NMAX || rtol < ftol || Math.abs(y[ihi]-y[ilo]) < atol) {
					dum=y[0]; y[0]=y[ilo]; y[ilo]=dum;
					dumm=p[0]; p[0]=p[ilo]; p[ilo]=dumm;
					break;
				}
	*/  //This is Marks code Gchen changed temporally to the following
		
				if(simDebug){
					sb.append("ilo = "+ilo+" ihi = "+ihi+" inhi = "+inhi+" rtol = "+rtol
						+" iteration="+iteration); 
				}
				
				if (iteration >= NMAX ){
					dum=y[0]; 
					y[0]=y[ilo]; 
					y[ilo]=dum;
					dumm=p[0]; 
					p[0]=p[ilo]; 
					p[ilo]=dumm;
					objectiveFunction = y[ilo];
					//Add status flag for abnormal exit
					if(objectiveFunction > NolObjective.HARD_COST*0.000001){
						statusFlag = 2;
						statusMessage = "Simplex.optimize: Could not find feasible solution(maximum iteration) and some variables may reach their hard bounds.";
					}else{
						statusMessage = "Simplex.optimize: Feasible,but not converge(maximum iteration).";
						statusFlag = 1;
					}
					break;
				}
				if(Math.abs(y[ihi]-y[ilo]) < atol || rtol < ftol) {
					dum=y[0]; 
					y[0]=y[ilo]; 
					y[ilo]=dum;
					dumm=p[0]; 
					p[0]=p[ilo]; 
					p[ilo]=dumm;
					objectiveFunction = y[ilo];
					//Add status flag for normal exit
					if(objectiveFunction > NolObjective.HARD_COST*0.000001){
						statusFlag = 3;
						statusMessage = "Simplex.optimize: Could not find feasible solution because some variables may reach their hard bounds.";
					}else{
						statusFlag = 0;
						statusMessage = "Simplex.optimize: Normal exit.";
					}
					break;
				}
				//Gchen 8.4.99
				iteration += 2;
				ytry=amotry(P,Y,y,psum,ndim,F,ihi,-1.0,Ptry);
				if (ytry <= y[ilo]) {

					if(simDebug){
						sb.append(" ytry lower than lowest value, ytry = "+ytry); 
					}
		//System.out.println("ytry lower than lowest value, ytry = "+ytry);
					ytry=amotry(P,Y,y,psum,ndim,F,ihi,2.0,Ptry);
				}
				else if (ytry >= y[inhi]) {
		//System.out.println("ytry higher than second highest value, ytry = "+ytry);
					if(simDebug){
						sb.append(" ytry higher than second highest value, ytry = "+ytry); 
					}
					ysave=y[ihi];
					ytry=amotry(P,Y,y,psum,ndim,F,ihi,0.5,Ptry);
					p = P.getData();  // rebind
					if (ytry >= ysave) {
						for (i=0;i<mpts;i++) {
							if (i != ilo) {
								for (j=0;j<ndim;j++) {
									p[i][j]=psum[j]=0.5*(p[i][j]+p[ilo][j]);
								}
								F.evaluate(Psum,Y);
								psum = (Psum.getData())[0];  // re-bind, just in case
								y[i] = Y.get(0,0);
							}
						}
						iteration += ndim;
						for (j=0;j<ndim;j++) {
							for (sum=0.0,i=0;i<mpts;i++){
								sum += p[i][j];
							}
							psum[j]=sum;
						}
					}
				} else --iteration;
				objectiveFunction = y[ilo];
			
				
				if(simDebug){
					sb.append(" objectiveFunction= "+objectiveFunction); 
					try { 
						String str = sb.toString();
						target.write(str,0,str.length());
						target.newLine();
						target.flush();
					}catch(IOException e){		
					}
				}
		//Matlib.disp(P,"Current simplex = ");
		//System.out.println("Current function values (rtol = "+rtol+")");
		//Utilities.disp(y);
			}
		}catch(MathException evt){
			statusFlag = 3;
			statusMessage = evt.getMessage();
		}
		Matrix.clearPool();
		Matlib.clear(Psum); //Gchen 6.26.2000
		Matlib.clear(Ptry);	//Gchen 6.26.2000
		Matlib.clear(Y);	//Gchen 6.26.2000
	}

	private double amotry(Matrix P, Matrix Y, double[] y,double[] psum, int ndim, Function F, int ihi, double fac, Matrix Ptry) throws MathException {
		int j;
		double fac1,fac2,ytry;
		double[][] p = P.getData();
		double[] ptry = (Ptry.getData())[0];
		fac1=(1.0-fac)/ndim;
		fac2=fac1-fac;
		for (j=0;j<ndim;j++) {
			ptry[j]=psum[j]*fac1-p[ihi][j]*fac2;
		}
		F.evaluate(Ptry,Y);
		ptry = (Ptry.getData())[0];
		ytry = Y.get(0,0);
		if (ytry < y[ihi]) {
			y[ihi]=ytry;
			for (j=0;j<ndim;j++) {
				psum[j] += ptry[j]-p[ihi][j];
				p[ihi][j]=ptry[j];
			}
		}
		return ytry;
	}

	public void setMaxIteration(int n){
		NMAX = n;
	}

	public int getMaxIteration(){
		return NMAX;
	}

	public int getStatusFlag(){
		return statusFlag;
	}

	public String getStatusMessage(){
		return statusMessage;
	}
} 

