package com.gensym.math.opt;

import java.io.Serializable;

import com.gensym.math.MathException;
import com.gensym.math.datafit.Model;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;

public class NolObjective implements INolObjective, Serializable {
	static final long serialVersionUID = 1L;
	public static final int LOWER_BOUND = 0;
	public static final int SOFT_LOWER_BOUND = 1;
	public static final int SET_POINT = 2;
	public static final int SOFT_UPPER_BOUND = 3;
	public static final int UPPER_BOUND = 4;
	public static final int LINEAR_TERM = 0;
	public static final int QUAD_TERM = 1;
	public static final int LOWER_BOUNDS_TERM = 2;
	public static final int UPPER_BOUNDS_TERM = 3;

	public static final double HARD_COST = 1.0e100;
	
	private Model model;
	private boolean[] varMask;
	private Matrix xBounds;
	private Matrix xCosts;
	private Matrix yBounds;
	private Matrix yCosts;
	private int nx;
	private int ny;
	private int nindep;
	private Matrix X;
	private Matrix Y;
	
	/** Creates an objective function for optimizing around a model with inputs
	  * X and outputs Y, where nx = the number of columns in X,
	  * and ny = the number of columns in Y.
	  * The contribution to the objective function for each variable is:
	  *
	  * old: w0*z + w1*(z - sp)^2 + w2*(slb - z)/(slb - lb) +
	  *      + w3*(z - sub)/(ub - sub)
	  * changed to:	w0*z + w1*(z - sp)^2 + w2*(slb - z) + w3*(z - sub)
	  *
	  * where sp = set point, slb = soft lower bound, lb = (hard) lower bound,
	  *       sub = soft upper bound, ub = (hard) upper bound, and z = x or y.
	  * The w2 term is used only if z is between its lower bound
	  * and its soft lower bound;
	  * the w3 term is used only if z is between the soft upper bound 
	  * and upper bound.
      *
	  * Hard bounds must always be set. Use Double.NEGATIVE_INFINITY
	  * and Double.POSITIVE_INFINITY if hard bounds do not apply.
	  *
	  * varMask (1, nx) indicates whether model inputs are to be varied (true)
	  * or held fixed (false).
	  * If an input is to be held fixed, specify the fixed value
	  * as the set point in the bounds matrix.
      *
	  * xBounds (5, nx) contains (from first to last row) the lower bound,
	  * soft lb, set point, and	soft ub and ub for each X variable.
	  * Similar for yBounds;
      *
	  * xCosts(4, nx) indicates the costs associated with each X variable.
	  * Its rows contain w0 to w3.
	  * If a term is not applicable, set the corresponding cost to zero.
	  * Similar for yCosts. **/

	public NolObjective(Model M, boolean[] varMask, Matrix xBounds,
			Matrix xCosts, Matrix yBounds, Matrix yCosts) throws MathException {
		super();
		model = M;
		
		this.varMask = new boolean[varMask.length];//Gchen add 6.28.2000
		System.arraycopy(varMask, 0, this.varMask, 0, varMask.length);//Gchen add 6.28.2000 need to create a local copy of the varMask.

		// do not use the matrices passed to the constructor directly since the user might clear them
		// copy them instead!
		this.xBounds = Matlib.createMatrix();
		this.xCosts = Matlib.createMatrix();
		this.yBounds = Matlib.createMatrix();
		this.yCosts = Matlib.createMatrix();
		Matlib.copy(xBounds,this.xBounds);
		Matlib.copy(xCosts,this.xCosts);
		Matlib.copy(yBounds,this.yBounds);
		Matlib.copy(yCosts,this.yCosts);

		checkHardUBLB(); //Gchen add 6.28.2000
		
		nx = M.getNin();
		ny = M.getNout();
		// size of the simplex = nindep + 1
		int i;
		int nindepLocal=0;
		for(i=0;i<nx;i++) {
			if(varMask[i]) {
				nindepLocal++;
			}
		}
		this.nindep = nindepLocal;
		X = Matlib.zeros(nindepLocal+1,nx);
		Y = Matlib.zeros(nindepLocal+1,ny);
		// set up static columns of X
		fillStaticCols(X);
	}

	/** Check the hard upper and lower bound of the variable. If the UB and LB
	 *  of a variable other than exogenous variable are the same then set
	 *  the mask to false.
	 */
//Gchen add 6.28.2000
	private void checkHardUBLB()throws MathException{
		int n = varMask.length;
		for(int i=0;i<n;i++){
			if(varMask[i]){
				if(Double.compare(xBounds.get(LOWER_BOUND,i), xBounds.get(UPPER_BOUND,i)) == 0){
					varMask[i] = false;	
					xBounds.set(SET_POINT,i,xBounds.get(LOWER_BOUND,i));
				}else if(xBounds.get(LOWER_BOUND,i) > xBounds.get(UPPER_BOUND,i)){
					throw new MathException("Objective Error: LB is greater than UB");
				}
			}
		}
	}


	/** Given a point X0 in (feasible) X space, createSimplex forms a suitable
	initial simplex matrix.  X0 is a row vector. **/
	@Override
	public void createSimplex(Matrix X0, Matrix V) {
		V.redimension(nindep+1,nindep);
		double lengthScale, x;
		int k=0;
		for(int j=0;j<nx;j++) {
			if(varMask[j]) {
				x = X0.get(j);
				if(!Double.isInfinite(xBounds.get(LOWER_BOUND,j)) && !Double.isInfinite(xBounds.get(UPPER_BOUND,j))) {
					lengthScale = 0.1*(xBounds.get(UPPER_BOUND,j) - xBounds.get(LOWER_BOUND,j));
				} else { // unbounded, guess a length scale
					lengthScale = 0.01*x;
				}
				if(Double.compare(lengthScale, 0.0) == 0)
					lengthScale = 1.0;
				for(int i=0;i<=nindep;i++) {
					V.set(i,k,x);
				}
				// perturb lower diagonal element according to length scale
				V.set(k+1,k,x+lengthScale);
				k++;
			}
		}
		//Matlib.disp(V,"Initial simplex = ");
	}

	/** Evaluate the objective function given current values 
	 * of independent variables V. **/
	@Override
	public void evaluate(Matrix V, Matrix F) throws MathException {
		// V (input) contains the current values of the independent variables
		// F (output) contains the value of the objective function at these values
		F.redimension(V.getRows(),1);
		F.initialize(Matrix.ZEROS);
		evaluateModel(V,this.X,this.Y); // re-use X and Y to save time
		calcObjective(X,xBounds,xCosts,F);
		calcObjective(Y,yBounds,yCosts,F);
		//Matlib.disp(F,"F = ");
	}

	/** Return model values at given values of independent variables **/
	@Override
	public void evaluateModel(Matrix V, Matrix X, Matrix Y) throws MathException {
		int rows = V.getRows();
		if (!X.equals(this.X) || rows != X.getRows()) {
			// when called by Simplex, the row dimension of V is always nindep+1,
			// but this insurance is necessary 
			X.redimension(rows,nx);
			fillStaticCols(X);
		}
		// put columns of V into X matrix
		int i,j,k=0;
		for(j=0;j<nx;j++) {
			if(varMask[j]) {
				for(i=0;i<rows;i++) {
					X.set(i,j,V.get(i,k));
				}
				k++;
			}
		}
		// run model
		model.evaluate(X,Y);
	}
	
	private void calcObjective(Matrix X, Matrix bounds, Matrix costs, Matrix F) throws MathException {
		// This applies to either X or Y with appropriate bounds and costs
		double cost,term,sp,slb,lb,sub,ub,x;
		int j;
		int i;
		int nxLocal = X.getCols();
		int rows=X.getRows();
		// evaluate objective function for X variable
		for(j=0;j<nxLocal;j++) {
			// term 0: linear contribution
			cost = costs.get(LINEAR_TERM,j);
			if(Double.compare(cost, 0.0) != 0) {
				for(i=0;i<rows;i++) {
					F.set(i,0,F.get(i,0)+cost*X.get(i,j));
				}
			}
			// term 1: quadratic contribution
			cost = costs.get(QUAD_TERM,j);
			if(Double.compare(cost, 0.0) != 0) {
				sp = bounds.get(SET_POINT,j);
				for(i=0;i<rows;i++) {
					term = X.get(i,j)-sp;
					//System.out.println("x = "+X.get(i,j)+" sp = "+sp+" term = "+term+" cost = "+cost);
					F.set(i,0,F.get(i,0)+cost*term*term);
				}
			}
			// term 2: lower bound term
			cost = costs.get(LOWER_BOUNDS_TERM,j);
			if(Double.compare(cost, 0.0) != 0) {
				slb = bounds.get(SOFT_LOWER_BOUND,j);
				lb = bounds.get(LOWER_BOUND,j);
				for(i=0;i<rows;i++) {
					x = X.get(i,j);
					if(x < slb) {
						term = (slb - x);
						F.set(i,0,F.get(i,0)+cost*term);
					}
				}
			}
			// term 3: upper bound term
			cost = costs.get(UPPER_BOUNDS_TERM,j);
			if(Double.compare(cost, 0.0) != 0) {
				sub = bounds.get(SOFT_UPPER_BOUND,j);
				ub = bounds.get(UPPER_BOUND,j);
				for(i=0;i<rows;i++) {
					x = X.get(i,j);
					if(x > sub) {
						term = x - sub;
						F.set(i,0,F.get(i,0)+cost*term);
					}
				}
			}
			// hard lb constraint
			lb = bounds.get(LOWER_BOUND,j);
			if(!Double.isInfinite(lb)) {
				for(i=0;i<rows;i++) {
					if(X.get(i,j) < lb){
						F.set(i,0,F.get(i,0)+HARD_COST*(lb - X.get(i,j)));
//System.out.println("low hard bound j="+j+"  x = "+X.get(i,j)+" lb = "+lb+" cost = "+F.get(i,0));
					}
				}
			}
			// hard ub constraint
			ub = bounds.get(UPPER_BOUND,j);
			if(!Double.isInfinite(ub)) {
				for(i=0;i<rows;i++) {
					if(X.get(i,j) > ub){
						F.set(i,0,F.get(i,0)+HARD_COST*(X.get(i,j) - ub));
//System.out.println("upper hard bound j="+j+"  x = "+X.get(i,j)+" lb = "+lb+" cost = "+F.get(i,0));
					}
				}
			}
		}
	}

	private void fillStaticCols(Matrix X) {
		// fill up the X matrix to contains constant set points in columns where varMask = false
		for(int j=0;j<nx;j++) {
			if(!varMask[j]) {
				double sp = xBounds.get(SET_POINT,j);
				for(int i=0;i<X.getRows();i++) {
					X.set(i,j,sp);	
				}
			}
		}
	}

	@Override
	public void clearMatrices() {
		model = null;
		varMask = null;
		Matlib.clear(xBounds);
		Matlib.clear(xCosts);
		Matlib.clear(yBounds);
		Matlib.clear(yCosts);
		Matlib.clear(X);
		Matlib.clear(Y);
		xBounds = null;
		xCosts = null;
		yBounds = null;
		yCosts = null;
		X = null;
		Y = null;
	}

	@Override
	public boolean[] getVariableMasks() {
		return varMask;
	}
}