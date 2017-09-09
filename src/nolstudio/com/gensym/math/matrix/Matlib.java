package com.gensym.math.matrix;

import java.io.*;
import java.net.*;
import com.gensym.math.*;

public final class Matlib {
	public static final int INF = Integer.MAX_VALUE;   // used in norm
	public static final int NEG_INF = Integer.MIN_VALUE;  // used in norm
	public static final double SIGMOID_LIM = Math.log(Double.MAX_VALUE);
	public static final double NEG_SIGMOID_LIM = - SIGMOID_LIM;

/*  CALLING CONVENTIONS:

All methods in this class are type final static.  Many are void -- 
you pass the methods both the input and return arguments.  
If you want to overwrite the input with the output, you may pass
the same matrix as both input and output:

	Matrix X = ones(3,5);
	transpose(X, X);	  // OK

Internally, this is accomplished by using temporary storage to hold the result 
during the calculation, where necessary.  Developers must make sure
they follow this convention.
  
All methods redimension their outputs, so you don't have to worry 
about passing the right size output matrices.  For maximum efficiency,
do NOT pre-dimension the output arguments, since they are dimensioned
inside the methods.

  GETTING AND SETTING MATRIX ELEMENTS

Users of this package generally do not use methods on the class 
Matrix directly, except when getting and setting matrix elements.
To get or set a matrix element with zero-based indices r and c:

  // 0 <= r,c and r < X.rows, c < X.cols	(public -- use X.getRows())
  X.get(r,c);  
  X.set(r,c, value);

If r and c refer to 1-based indices, it may be convenient to use:

  // 0 < r,c and r <= X.rows, c <= X.cols	(public -- use X.getRows())
  X.get1(r,c);  
  X.set1(r,c, value);  // same as X.set(--r,--c, value);

To set a group of matrix elements, use the Matrix methods setPart,
setColumn, or setRow.  For one-based indexing, use setPart1, setColumn1,
or setRow1.

You can also reference elements by a single index, as if the matrix were
a long column vector.  The calls are X.get(index), X.get1(index), 
X.set(index, value), X.set1(index,value).  These operations are less
efficient when the X is not a vector.


  MEMORY MANAGEMENT:

To create a matrix, use 'createMatrix()' or functions
like ones, zeros, rand, etc.  DO NOT USE 'new Matrix()', because
this will bypass the memory pool.  You are responsible for freeing the 
memory for the matrix when you are finished with it.  The command
for freeing a matrix back to the memory pool is:

    Matlib.clear(X);  // Or use the protected method, X.clear();

After you clear a variable, you may not reference it again.


  ORGANIZATION OF THIS FILE

This class has a large number of methods.  They are organized into 
the following categories, roughly following Matlab's categorization. 
(methods not included in Matlab or given by Matlab operators are indicated
with an asterisk):

  1)	Managing variables and memory 
		(clear, disp, length, load, pack, save, size) 
  2)	Elementary matrices
		(colon*, createMatrix*, eye, linspace, logspace, ones, rand, randn, zeros)
  3)	Conversion to/from Java arrays
		(create1DArray*, create2DArray*, createMatrix*)
  4)	Matrix Manipulation
		(appendColumns*, appendRows*, copy*, diag, fliplr, flipud, redimension*,
		reshapeToColumn*, reshapeToRow*, rot90, tril, triu, transpose*)
  5)	Parts of a matrix
		(getPart*, getPart1*, getColumn*, getColumn1*, getRow*, getRow1*)
  6)	Elementary Math Operations
		(add*, divide*, divideElements*, dotProduct*, multiply*, multiplyElements*,
		power*, powerElements*, subtract*, unaryMinus*)
  7)	Elementary Math Functions
		(abs, ceil, exp, fix, floor, log, log10, rem, round, sign, sqrt)
  8)    Logical Operators
		(and*, not*, or*, xor)
  9)	Logical Functions
		(all, any, find, findFinite, findFiniteRows, findFiniteColumns, 
		isEmpty, findInf, hasInf, findNaN, hasNan, hasConstantColumns)
 10)	Relational Operators
		(equal*, ge*, gt*, le*, lt*, notEqual*)
 11)	Matrix Analysis
 12)	Linear Equations
 13)	Eigenvalues and Singular Values
 14)	Basic Data Analysis
 15)	Correlation
 16)	Special Matrices



/*  MANAGING VARIABLES AND MEMORY */

	/** Clears matrices from memory */
	public static final void clear(Matrix M) {
		if(M!=null){
			M.clear();
		}
	}

	/** Displays a matrix to five significant digits, by default */
	public static final void disp(Matrix M) {
		  M.display(5);
	}

	/** Displays a matrix to given significant digits */
	public static final void disp(Matrix M, int digits) {
		  M.display(digits);
	}


	/** Displays a matrix to full precision (to standard output) */
	public static final void dispFull(Matrix M) {
		  M.display();
	}

	public static final void disp(Matrix M, String S) {
		System.out.println(S+" ("+M.getRows()+" by "+M.getCols()+")");
		M.display(5);
	}

	public static final void showSize(Matrix M, String S) {
		System.out.println(S+" ("+M.getRows()+" by "+M.getCols()+")");
	}

	public static final void showSize(Matrix M) {
		System.out.println("Size = ("+M.getRows()+" by "+M.getCols()+")");
	}

	/** Length of a vector.  Equivalent to max(size(x)) */
	public static final int length(Matrix M) {
		if (M.rows > M.cols){
			return M.rows;
		}
		else {
			return M.cols;
		}
	}

	/** Load matrices from file   TBD */
	public static final void load(String S) {
	}

	/** Reclaim and consolidate memory */
	public static final void pack() {
		Matrix.clearPool();
	}

	/** Save . TBD */
	public static final void save(String S, Matrix[] matrices, int flags) {}

	/** Size of matrix. On output, Y will be a 1-by-2 matrix 
	containing the number of rows and cols of X **/
	public static final void size(Matrix X, Matrix Y) {
		int rows = X.rows;
		int cols = X.cols;
		Y.redimension(1,2);
		Y.set(0,rows);
		Y.set(1,cols);
	}


/*  ELEMENTARY MATRICES: COLON, CREATEMATRIX, EYE, ONES, LINSPACE, RAND, RANDN, ZEROS */
	
	/** Creates a row vector whose elements are distributed between lower and upper 
	bounds using an increment of 1. Returns an null matrix if ub < lb. */
		public static final Matrix colon(double lb, double ub) {
		return colon(lb, 1.0, ub);
	}

	/** Creates a row vector whose elements are distributed between lower and upper 
	bounds using the given increment*/
	public static final Matrix colon(double lb, double increment, double ub) {
		if (ub < lb){
			return createMatrix();
		}
		int elements = 1 + (int) Math.floor((ub - lb)/increment);
		Matrix M = createMatrix(1,elements);
		double val = lb;
		double[][] Md = M.data;
		if(M.transposed) {
			for(int i=0;i<elements;i++, val+=increment){
				Md[i][0] = val;
			}
		}else {
			for(int i=0;i<elements;i++, val+=increment){
				Md[0][i] = val;
			}
		}
		return M;
	}

	/** Creates a new empty matrix object with zero rows and columns. */
	public static final Matrix createMatrix() {
		return Matrix.newMatrix();
	}

	/** Create an uninitialized matrix of the given size.  This is
	faster than zeros(r,c) if the matrix does not need to be 
	initialized.*/
	public static final Matrix createMatrix(int r, int c) {
		return Matrix.newMatrix(r,c);
	}

	/** Create a matrix from an ascii file */
	public static final Matrix createMatrix(String Dir, String S) throws IOException {
		return Matrix.readFromFile(Dir,S);
	}

	/** Create a matrix from an ascii file */
	public static final Matrix createMatrix(URL url) throws IOException {
		return Matrix.readFromURL(url);
	}

	/** Creates a r-by-c matrix with ones on the diagonal */
	public static final Matrix eye(int r, int c) {
		Matrix M = createMatrix(r,c);
		M.initialize(Matrix.EYE);
		return M;
	}

	/** Creates a square identity matrix */
	public static final Matrix eye(int r) {
		return eye(r,r);
	}

	/** Generates N linearly-spaced points between lower bound and upper bound */
	public static final Matrix linspace(double lb, double ub, int n) {
		return colon(lb, (ub - lb)/(n - 1), ub);
	}

	/** Logspace - NOT YET IMPLEMENTED */
	public static final Matrix logspace() {
		return createMatrix();
	}

	/** Creates a r-by-c matrix containing ones */
	public static final Matrix ones(int r, int c) {
		Matrix M = createMatrix(r,c);
		M.initialize(Matrix.ONES);
		return M;
	}

	/** Creates a square matrix (r-by-r) containing ones */
	public static final Matrix ones(int r) {
		return ones(r,r);
	}

	/** Creates a r-by-c matrix containing random numbers in the range 0.0 - 1.0 */
	public static final Matrix rand(int r, int c) {
		Matrix M = createMatrix(r,c);
		M.initialize(Matrix.RAND);
		return M;
	}

	/** Creates a square matrix (r-by-r) containing uniform (0,1) random numbers*/
	public static final Matrix rand(int r) {
		return rand(r,r);
	}

	/** Creates a r-by-c matrix containing random numbers from a (0,1) normal distribution */
	public static final Matrix randn(int r, int c) {
		Matrix M = createMatrix(r,c);
		M.initialize(Matrix.RANDN);
		return M;
	}

	/** Creates a square matrix (r-by-r) containing (0,1) normally-distributed random numbers */
	public static final Matrix randn(int r) {
		return randn(r,r);
	}

	/** Creates a r-by-c matrix containing zeros */
	public static final Matrix zeros(int r, int c) {
		Matrix M = createMatrix(r,c);
		M.initialize(Matrix.ZEROS);
		return M;
	}

	/** Creates a square matrix (r-by-r) containing zeros*/
	public static final Matrix zeros(int r) {
		return zeros(r,r);
	}


/*	MATRIX CONVERSION TO/FROM JAVA ARRAYS */

	/** Creates a 2-D double array out of a matrix.  The dimensions of the double
	array are the same as the matrix. */
	public static final double[][] create2DArray(Matrix M) {
		double[][] array = new double[M.rows][M.cols];
		double[][] Md = M.data;
		if(M.transposed) {
			for(int i=0;i<M.rows;i++) {
				for(int j=0;j<M.cols;j++){
					array[i][j] = Md[j][i];
				}
			}
		} else {
			for(int i=0;i<M.rows;i++) {
				for(int j=0;j<M.cols;j++) {
					array[i][j] = Md[i][j];
				}
			}
		}
		return array;
	}

	/** Creates a 2-D boolean array out of a matrix. Non-zero elements
	returned as true, zeros returned as false */
	public static final boolean[][] create2DBooleanArray(Matrix M) {
		boolean[][] array = new boolean[M.rows][M.cols];
		double[][] Md = M.data;
		if(M.transposed) {
			for(int i=0;i<M.rows;i++) 
				for(int j=0;j<M.cols;j++) 
					array[i][j] = Double.compare(Md[j][i], 0.0) != 0;
		} else {
			for(int i=0;i<M.rows;i++) 
				for(int j=0;j<M.cols;j++) 
					array[i][j] = Double.compare(Md[i][j], 0.0) != 0;
		}
		return array;
	}

	/** Creates a 1-D double array out of a matrix.  The elements are
	taken columnwise from M */
	public static final double[] create1DArray(Matrix M) {
		double[] array = new double[M.elements];
		double[][] Md = M.data;
		int i,j,k=0;
		if(M.transposed) {
			for(j=0;j<M.cols;j++){
				for(i=0;i<M.rows;i++) {
					array[k] = Md[j][i];
					k++;
				}
			}
		} else {
			for(j=0;j<M.cols;j++){
				for(i=0;i<M.rows;i++) {
					array[k] = Md[i][j];
					k++;
				}
			}
		}
		return array;
	}

	/** Creates a 1-D boolean array from a matrix.  Non-zero elements
	returned as true, zeros returned as false */
	public static final boolean[] create1DBooleanArray(Matrix M) {
		boolean[] array = new boolean[M.elements];
		double[][] Md = M.data;
		int i,j,k=0;
		if(M.transposed) {
			for(j=0;j<M.cols;j++){
				for(i=0;i<M.rows;i++) {
					array[k] = Double.compare(Md[j][i], 0.0) != 0;
					k++;
				}
			}
		} else {
			for(j=0;j<M.cols;j++) {
				for(i=0;i<M.rows;i++) {
					array[k] = Double.compare(Md[i][j], 0.0) != 0;
					k++;
				}
			}
		}
		return array;
	}

	/** Create a matrix from a double array, oriented as a column vector.
	Data is copied, not shared.  If a row vector is desired, use transpose
	on the result. */
	public static final Matrix createMatrix(double[] array) {
		Matrix M = createMatrix(array.length, 1);
		double[][] d = M.data;
		if(M.transposed) {
			for(int i=0;i<array.length;i++){
				d[0][i] = array[i];
			}
		}else {
			for(int i=0;i<array.length;i++){
				d[i][0] = array[i];
			}
		}
		return M;
	}

	/** Create a matrix from a 2-dimensional double array.  Data is copied,
	not shared.  If the input matrix is ragged (has different row lengths), 
	the size of the matrix will reflect the longest row, and the unspecified 
	elements will be given as zeros */
	public static final Matrix createMatrix(double[][] array) {
		int i,j,cols = 0,rows = array.length;
		for(i=0;i<rows;i++) {
			if(array[i] != null){
				cols = Math.max(array[i].length, cols);
			}
		}
		Matrix M = zeros(rows,cols);
		double[][] Md = M.data;
		if (M.transposed) {
			for(i=0;i<rows;i++) {
				if (array[i] != null) {
					for(j=0;j<array[i].length;j++){
						Md[j][i] = array[i][j];
					}
				}
			}
		} else {
			for(i=0;i<rows;i++) {
				if (array[i] != null) {
					for(j=0;j<array[i].length;j++){
						Md[i][j] = array[i][j];
					}
				}
			}
		}
		return M;
	}

	/** Creates a 1-by-1 matrix from a scalar */
	public static final Matrix createMatrix(double d) {
		Matrix M = createMatrix(1,1);
		M.data[0][0] = d;
		return M;
	}

/*  MATRIX MANIPULATION */

	/** Create a matrix formed of the columns of two matrices.  Same as Matlab [X1 X2] */
	public static final void appendColumns(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		if(X1.cols==0 || X1.rows == 0) { // X1 is empty
			copy(X2,Y);
			return;
		}
		if (X1.rows != X2.rows)
			throw new MathException("appendColumns: row dimensions "+X1.rows+" and "+X2.rows+" do not match");
		if(X1==Y || X2==Y) {  // need temporary storage
			Matrix TY = createMatrix();
			appendColumns(X1,X2,TY); 
			TY.destructiveCopy(Y);
			return;
		}
		Y.redimension(X1.rows, X1.cols + X2.cols); 
		Y.setPart(0,0,X1);
		Y.setPart(0,X1.cols,X2);
	}

	/** Create a matrix formed of the rows of two matrices.  Same as Matlab [X1; X2] */
	public static final void appendRows(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		if(X1.rows==0 || X1.cols==0) {
			copy(X2,Y);
			return;
		}
		if (X1.cols != X2.cols)
			throw new MathException("appendRows: column dimensions "+X1.cols+" and "+X2.cols+" do not match");
		if(X1==Y || X2==Y) {  // need temporary storage
			Matrix TY = createMatrix();
			appendRows(X1,X2,TY); 
			TY.destructiveCopy(Y);
			return;
		}
		Y.redimension(X1.rows + X2.rows, X1.cols);
		Y.setPart(0,0,X1);
		Y.setPart(X1.rows,0,X2);
	}

	/** Copies the contents of the first matrix to the second matrix */
	public static final void copy(Matrix X, Matrix Y) {
		X.copy(Y);
	}

	/** Creates or extracts diagonal.  If X is a vector, diag returns a matrix with
	the elements of X on the main diagonal.  If X is a matrix, diag returns a column 
	vector of diagonal elements. */
	public static final void diag(Matrix X, Matrix Y) throws MathException {
		diag(X,0,Y);
	}

	/** Creates or extracts diagonal.  If X is a vector, diag returns a matrix with
	the elements of X on the k-th diagonal, where k=0 is the main diagonal, k=1 is 
	one above, and k=-1 is one below.  If X is a matrix, diag returns a column 
	vector of diagonal elements taken from the k-th diagonal of X. */
	public static final void diag(Matrix X, int k, Matrix Y) throws MathException {
		if(X==Y) {  // need temporary storage
			Matrix TY = createMatrix();
			diag(X, k, TY);	
			TY.destructiveCopy(Y);
			return;
		}
		if(X.rows==1 || X.cols==1) {
			Y.redimension(X.elements + Math.abs(k), X.elements + Math.abs(k));
			Y.initialize(Matrix.ZEROS);
			if(k>=0) {
				for(int i=0;i<X.elements;i++){
					Y.set(i,i+k,X.get(i));
				}
			}else {
				for(int i=0;i<X.elements;i++){
					Y.set(i-k,i,X.get(i));
				}
			}
		} else { // extract diagonal
			int n;
			if(k>=0){
				n = Math.min(X.rows,X.cols-k);
			} else{
				n = Math.min(X.cols,X.rows+k);
			}
			if (n<=0){
				throw new MathException("diag: no "+k+" diagonal in "+X.rows+" by "+X.cols+" matrix.");
			}
  			Y.redimension(n,1);
			Y.initialize(Matrix.ZEROS);
			if(k>=0) {
				for(int i=0;i<n;i++) {
					Y.set(i,X.get(i,i+k));
				}
			} else {
				for(int i=0;i<n;i++) {
					Y.set(i,X.get(i-k,i));
				}
			}
		}
	}

	/** Reverses columns in left-right direction */
	public static final void fliplr(Matrix X, Matrix Y) {
		if(X==Y) {  // need temporary storage
			Matrix TY = createMatrix();
			fliplr(X, TY); 
			TY.destructiveCopy(Y);
			return;
		}
		Y.redimension(X.rows, X.cols, X.transposed);  // assure the same orientation
		int col, cols = X.cols, rows = X.rows;
		double[][] xd = X.data, yd = Y.data; 
		if (X.transposed) {
			for (int j=0; j<cols; j++) {
				col = cols - j - 1;
				for (int i=0; i<rows; i++){
					yd[col][i] = xd[j][i];
				}
			}
		}
		else {
			for (int j=0; j<cols; j++) {
				col = cols - j - 1;
				for (int i=0; i<rows; i++){
					yd[i][col] = xd[i][j];
				}
			}
		}
	}

	/** Reverses rows in up-down direction */
	public static final void flipud(Matrix X, Matrix Y) {
		if(X==Y) {  // need temporary storage
			Matrix TY = createMatrix();
			flipud(X,TY); 
			TY.destructiveCopy(Y);
			return;
		}
		Y.redimension(X.rows, X.cols, X.transposed);
		int row, cols = X.cols, rows = X.rows;
		double[][] xd = X.data, yd = Y.data; 
		if(X.transposed) {
			for (int i=0; i<rows; i++) {
				row = rows - i - 1;
				for (int j=0; j<cols; j++){
					yd[j][row] = xd[j][i];
				}
			}
		}
		else {
			for (int i=0; i<rows; i++) {
				row = rows - i - 1;
				for (int j=0; j<cols; j++){
					yd[row][j] = xd[i][j];
				}
			}
		}
	}

	/** Reshapes a matrix to given r, c dimension.  The number of 
	elements in the matrix must match.  Elements of X are in taken
	columnwise order.*/
	public static final void reshape(Matrix X, int r, int c, Matrix Y) throws MathException {
		if (r*c != X.elements)
			throw new MathException("reshape: number of elements do not match.");
		if(X==Y) {  // allocate temporary storage
			Matrix TY = createMatrix();
			reshape(X,r,c,TY); 
			TY.destructiveCopy(Y);
			return;
		}
		Y.redimension(r,c);
		int ii=0,jj=0,rows=X.rows,cols=X.cols;
		double[][] xd = X.data, yd = Y.data;
		if (!X.transposed && !Y.transposed) {
			for(int j=0;j<cols;j++){
				for(int i=0;i<rows;i++) {
					yd[ii][jj] = xd[i][j];
					ii++; 
					if(ii>=r) {
						ii=0;
						jj++;
					}
				}
			}
		} else if (X.transposed && !Y.transposed) {
			for(int j=0;j<cols;j++){
				for(int i=0;i<rows;i++) {
					yd[ii][jj] = xd[j][i];
					ii++; 
					if(ii>=r) {
						ii=0;
						jj++;
					}
				}
			}
		} else if (!X.transposed && Y.transposed) {
			for(int j=0;j<cols;j++){
				for(int i=0;i<rows;i++) {
					yd[jj][ii] = xd[i][j];
					ii++; 
					if(ii>=r) {
						ii=0;
						jj++;
					}
				}
			}
		} else { // both transposed 
			for(int j=0;j<cols;j++){
				for(int i=0;i<rows;i++) {
					yd[jj][ii] = xd[j][i];
					ii++; 
					if(ii>=r) {
						ii=0;
						jj++;
					}
				}
			}
		}
	}

	/** Reshapes a matrix into a column vector. */
	public static final void reshapeToColumn(Matrix X, Matrix Y) throws MathException {
		reshape(X, X.elements, 1, Y);
	}

	/** Reshapes a matrix into a row vector.*/
	public static final void reshapeToRow(Matrix X, Matrix Y) throws MathException {
		reshape(X, 1, X.elements, Y);
	}

	/** 90-Degree rotation of a matrix. */
	public static final void rot90(Matrix X, Matrix Y) {
		if(X==Y) {  // need temporary storage
			Matrix TY = createMatrix();
			rot90(X, TY); 
			TY.destructiveCopy(Y);
			return;
		}
		Y.redimension(X.cols, X.rows);
		for (int row=Y.rows-1, r=0; row>=0; row--,r++) {
			for (int col=0; col<Y.cols; col++){
				Y.set(r,col,X.get(col,row));
			}
		}
	}

	/** Lower triangular part of a matrix */
	public static final void tril(Matrix X, Matrix Y) {
		tril(X, 0, Y);
	}

	/** Lower triangular part of a matrix, where diag = 0 is the main
	diagonal, -1 is below the main diagonal, +2 is two above, etc. */
	public static final void tril(Matrix X, int diag, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);	// no temp storage needed
		double[][] xd = X.data, yd = Y.data;
		if(X.transposed) {
			for(int r=0;r<X.rows;r++){
				for(int c=0;c<X.cols;c++) {
					if (c <= r+diag) {
						yd[c][r] = xd[c][r];
					}
					else{
						yd[c][r] = 0.0;
					}
				}
			}
		} else {
  			for(int r=0;r<X.rows;r++) {
  				for(int c=0;c<X.cols;c++) {
  					if (c <= r+diag){
  						yd[r][c] = xd[r][c];
  					} else{
  						yd[r][c] = 0.0;
  					}
  				}
			}
		}
	}

	/** Upper triangular part of a matrix */
	public static final void triu(Matrix X, Matrix Y) {
		triu(X, 0, Y);
	}

	/** Upper triangular part of a matrix, where diag = 0 is the main
	diagonal, -1 is below the main diagonal, +2 is two above, etc. */
	public static final void triu(Matrix X, int diag, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		double[][] xd = X.data, yd = Y.data;
		if(X.transposed) {
 			for(int r=0;r<X.rows;r++){
 				for(int c=0;c<X.cols;c++) {
					if (c >= r+diag){
						yd[c][r] = xd[c][r];
					}
					else {
						yd[c][r] = 0.0;
					}
 				}
			}
		} else {
			for(int r=0;r<X.rows;r++){
				for(int c=0;c<X.cols;c++) {
					if (c >= r+diag){
						yd[r][c] = xd[r][c];
					}
					else{
						yd[r][c] = 0.0;
					}
				}
			}
		}
	}

	/** Transpose of a matrix. If Y==X, this operation is very fast.*/
	public static final void transpose(Matrix X, Matrix Y) {
		if(X==Y){
			X.transpose();
		}
		else {
			X.copy(Y); 
			Y.transpose();
		}
	}
	
/* GET/SET PARTS OF A MATRIX */

	/** Extract a submatrix of X starting at element r1, c1 and ending at r2,c2 */
	public static final void getPart(Matrix X, int r1, int c1, int r2, int c2, Matrix Y)  throws MathException {
		boolean condition = r1 < 0 || c1 < 0 || c2 < c1 || r2 < r1;
		if (condition || r2 >= X.rows || c2 >= X.cols)
			throw new MathException ("getPart: cannot extract submatrix ("+r1+","+c1+") to ("+r2+","+c2+") from a "+X.rows+" by "+X.cols+" matrix");
		if(X==Y) {  //create temporary storage
			Matrix TY = createMatrix();
			getPart(X,r1,c1,r2,c2,TY); 
			TY.destructiveCopy(Y);
			return;
		}
		int rows = r2-r1+1, cols = c2-c1+1; 
		Y.redimension(rows, cols);
		double[][] xd = X.data, yd = Y.data;
		if (!X.transposed && !Y.transposed) {
			for(int i=0;i<rows;++i){
				for(int j=0;j<cols;++j){
					yd[i][j] = xd[r1+i][c1+j];
				}
			}
		} else if (X.transposed && !Y.transposed) {
			for(int i=0;i<rows;++i){
				for(int j=0;j<cols;++j){
					yd[i][j] = xd[c1+j][r1+i];
				}
			}
		}else if (!X.transposed && Y.transposed){
			for(int i=0;i<rows;++i){
				for(int j=0;j<cols;++j){
					yd[j][i] = xd[r1+i][c1+j];
				}
			}
		} else {  // both transposed
			for(int i=0;i<rows;++i){
				for(int j=0;j<cols;++j){
					yd[j][i] = xd[c1+j][r1+i];
				}
			}
		}
	}

	/** Extract a submatrix from X using 1-based indexing */
	public static final void getPart1(final Matrix X, final int r1, final int c1, final int r2, final int c2, final Matrix Y)  throws MathException {
		getPart(X, r1-1, c1-1, r2-1, c2-1, Y);
	}

	/** Extract a column of a matrix.  Convenience function instead of getPart. */
	public static final void getColumn(Matrix X, int col, Matrix Y)  throws MathException {
		getPart(X, 0, col, X.rows - 1, col, Y);
	}

	/** Extract a column of a matrix using 1-based indexing.  Convenience function 
	instead of getPart1. */
	public static final void getColumn1(final Matrix X, final int col, final Matrix Y) throws MathException  {
		int column = col-1;
		getColumn(X, column, Y);
	}

	/** Extract a range of columns */
	public static final void getColumns(Matrix X, int firstCol, int lastCol, Matrix Y) throws MathException {
		getPart(X, 0, firstCol, X.rows - 1, lastCol, Y);
	}

	/** Extract the columns indicated by non-zero elements of the row vector S */
	public static final void getColumns(Matrix X, Matrix S, Matrix Y) throws MathException {
		if(X.cols != S.cols){
			throw new MathException("getColumns: number of columns in X and selector matrix S must match");
		}
		if(X==Y || X==S) {  //create temporary storage
			Matrix TY = createMatrix();
			getColumns(X,S,TY); 
			TY.destructiveCopy(Y);
			return;
		}
		int i,j,k=0,cols=0,rows=X.rows;
		for(j=0;j<S.cols;j++) 
			if(Double.compare(S.get(0,j), 0.0) != 0) 
				cols++;
		
		Y.redimension(X.rows, cols);
		double[][] xd = X.data, yd = Y.data;
		if (!X.transposed && !Y.transposed) {
			for(j=0;j<S.cols;++j) 
				if(Double.compare(S.get(0,j), 0.0) != 0) {
					for(i=0;i<rows;++i){
						yd[i][k] = xd[i][j];
					}
					k++;
				}
		}
		else if (X.transposed && !Y.transposed) {
			for(j=0;j<S.cols;++j) 
				if(Double.compare(S.get(0,j), 0.0) != 0) {
					for(i=0;i<rows;++i){
						yd[i][k] = xd[j][i];
					}
					k++;
				}
		}
		else if (!X.transposed && Y.transposed) {
			for(j=0;j<S.cols;++j) 
				if(Double.compare(S.get(0,j), 0.0) != 0) {
					for(i=0;i<rows;++i){
						yd[k][i] = xd[i][j];
					}
					k++;
				}
		}
		else {  // both transposed
			for(j=0;j<S.cols;++j) 
				if(Double.compare(S.get(0,j), 0.0) != 0) {
					for(i=0;i<rows;++i){
						yd[k][i] = xd[j][i];
					}
					k++;
				}
		}
	}


	/** Extract a row of a matrix.  Convenience function instead of getPart. */
	public static final void getRow(Matrix X, int row, Matrix Y)  throws MathException {
		getPart(X, row, 0, row, X.cols - 1, Y);
	}

	/** Extract rows of a matrix. */
	public static final void getRows(Matrix X, int firstRow, int lastRow, Matrix Y)  throws MathException {
		getPart(X, firstRow, 0, lastRow, X.cols - 1, Y);
	}

	/** Extract rows of a matrix indicated by non-zero elements of 
	column vector S */
	public static final void getRows(Matrix X, Matrix S, Matrix Y) throws MathException {
		if(S.rows != X.rows){
			throw new MathException("getRows: row dimension of X and selector matrix S must match");
		}
		if(X==Y) {
			Matrix TY = createMatrix();
			getRows(X,S,TY);
			TY.destructiveCopy(Y);
			return;
		}
		int i,j,k=0,cols=X.cols,rows=0;
		for(i=0;i<S.rows;i++) 
			if(Double.compare(S.get(i,0), 0.0) != 0) 
				rows++;
		
		Y.redimension(rows,cols);
		double[][] xd = X.data, yd = Y.data;
		if (!X.transposed && !Y.transposed) {
			for(i=0;i<S.rows;++i) 
				if(Double.compare(S.get(i,0), 0.0) != 0) {
					for(j=0;j<cols;++j){
						yd[k][j] = xd[i][j];
					}
					k++;
				}
		}
		else if (X.transposed && !Y.transposed) {
			for(i=0;i<S.rows;++i) 
				if(Double.compare(S.get(i,0), 0.0) != 0) {
					for(j=0;j<cols;++j){
						yd[k][j] = xd[j][i];
					}
					k++;
				}
		}
		else if (!X.transposed && Y.transposed) {
			for(i=0;i<S.rows;++i) 
				if(Double.compare(S.get(i,0), 0.0) != 0) {
					for(j=0;j<cols;++j){
						yd[j][k] = xd[i][j];
					}
					k++;
				}
		}
		else {  // both transposed
			for(i=0;i<S.rows;++i) 
				if(Double.compare(S.get(i,0), 0.0) != 0) {
					for(j=0;j<cols;++j){
						yd[j][k] = xd[j][i];
					}
					k++;
				}
		}
	}

	/** Extract a row of a matrix using 1-based indexing.  Convenience function 
	instead of getPart1. */
	public static final void getRow1(final Matrix X, final int row, final Matrix Y) throws MathException {
		getRow(X, row-1, Y);
	}

	/** Replaces elements of X1 with elements of matrix X2, beginning at row, col */
	public static final void setPart(Matrix X1, Matrix X2, int row, int col, Matrix Y)  throws MathException {
		int r1 = X1.getRows(), c1 = X1.getCols(), r2 = X2.getRows(), c2 = X2.getCols();
		if (row < 0 || col < 0 || r2 + row > r1 || c2 + col > c1)
			throw new MathException ("setPart: matrix X2 does not fit within matrix X1 with given origin");
		if(X2==Y) {  //create temporary storage
			Matrix TY = createMatrix();
			setPart(X1,X2,row,col,TY); 
			TY.destructiveCopy(Y);
			return;
		}
		if(X1!=Y){
			Matlib.copy(X1, Y);
		}
		double[][] xd = X2.data, yd = Y.data;
		if (!X2.transposed && !Y.transposed) {
			for(int i=0;i<r2;++i){
				for(int j=0;j<c2;++j){
					yd[i+row][j+col] = xd[i][j];
				}
			}
		}else if (X2.transposed && !Y.transposed) {
			for(int i=0;i<r2;++i){
				for(int j=0;j<c2;++j){
					yd[i+row][j+col] = xd[j][i];
				}
			}
		} else if (!X2.transposed && Y.transposed){
			for(int i=0;i<r2;++i){
				for(int j=0;j<c2;++j){
					yd[j+col][i+row] = xd[i][j];
				}
			}
		}else{ // both transposed
			for(int i=0;i<r2;++i){
				for(int j=0;j<c2;++j){
					yd[j+col][i+row] = xd[j][i];
				}
			}
		}		
	}


/*  ELEMENTARY MATH OPERATORS */

	/** Adds two matrices. If either input is a scalar, it is added to all elements.
	If X2 is a vector that matches the column dimension of X1, then X2 
	is added to each element in the corresponding column of X1 (a useful
	addition to Matlab behavior).*/
	public static final void add(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		if (X1.elements == 1){
			add(X2, X1.get(0), Y);
		} else if (X2.elements == 1){
			add(X1, X2.get(0), Y);
		} else if (X1.rows == X2.rows && X1.cols == X2.cols) {
			int rows = X1.rows, cols = X1.cols;
			Y.redimension(rows, cols);
			double[][] yd=Y.data, x1d=X1.data, x2d=X2.data;
			if(!X1.transposed && !X2.transposed){ 
				for(int i=0;i<rows;i++) {
					for(int j=0;j<cols;j++){
						yd[i][j] = x1d[i][j] + x2d[i][j];
					}
				}
			} else if(X1.transposed && !X2.transposed){ 
				for(int i=0;i<rows;i++){
					for(int j=0;j<cols;j++){
						yd[j][i] = x1d[j][i] + x2d[i][j];
					}
				}
			} else if(!X1.transposed && X2.transposed){ 
				for(int i=0;i<rows;i++){
					for(int j=0;j<cols;j++){
						yd[i][j] = x1d[i][j] + x2d[j][i];
					}
				}
			}else { // both tranposed
				for(int i=0;i<rows;i++){
					for(int j=0;j<cols;j++){
						yd[j][i] = x1d[j][i] + x2d[j][i];
					}
				}
			}
		} else if (X2.rows == 1 && X1.rows > 1 && X2.cols == X1.cols) { // add a matrix and a row vector
			if(X1==Y || X2==Y) {  //create temporary storage
				Matrix TY = createMatrix();
				add(X1,X2,TY);
				TY.destructiveCopy(Y);
				return;
			}
			Y.redimension(X1.rows,X1.cols,X1.transposed);
			double[][] xd = X1.data, yd = Y.data;
			double x2val;
			if (X1.transposed) {
				for(int j=0;j<X1.cols;j++) {
					x2val = X2.get(j);
					for(int i=0;i<X1.rows;i++){
						yd[j][i] = xd[j][i] + x2val;
					}
				}				
			} else {
				for(int j=0;j<X1.cols;j++) {
					x2val = X2.get(j);
					for(int i=0;i<X1.rows;i++){
						yd[i][j] = xd[i][j] + x2val;
					}
				}
			}
		} else if (X2.cols == 1 && X1.cols > 1 && X2.rows == X1.rows) { // add a matrix and a column vector
			if(X1==Y || X2==Y) {  //create temporary storage
				Matrix TY = createMatrix();
				add(X1,X2,TY);
				TY.destructiveCopy(Y);
				return;
			}
			Y.redimension(X1.rows,X1.cols,X1.transposed);
			double[][] xd = X1.data, yd = Y.data;
			double x2val;
			if (X1.transposed) {
				for(int i=0;i<X1.rows;i++) {
					x2val = X2.get(i);
					for(int j=0;j<X1.cols;j++){
						yd[j][i] = xd[j][i] + x2val;
					}
				}				
			} else {
				for(int i=0;i<X1.rows;i++) {
					x2val = X2.get(i);
					for(int j=0;j<X1.cols;j++){
						yd[i][j] = xd[i][j] + x2val;
					}
				}
			}
		}
		else throw new MathException("add: bad matrix dimensions "+X1.rows+"x"+X1.cols+" and "+X2.rows+"x"+X2.cols+".");
	}

	/** Addition of a scalar to a matrix */
	public static final void add(Matrix X, double d, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		for(int i=0;i<rows;i++) {
			for(int j=0;j<cols;j++){
				yd[i][j] = xd[i][j] + d;
			}
		}
	}

	/** Divide is the backslash, or left division operator of Matlab. 
	If X1 is a square matrix, divide(X1, X2, Y) is the solution of the
	equation X1*Y = X2.  If X1 is nonsquare, then Y is the solution to the
	equation in the least-squares sense. */
	public static final void divide(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		if(X2.elements==1) {
			divide(X1,X2.get(0),Y);
			return;
		}
		if(X1.rows != X2.rows) 
			throw new MathException("divide: number of rows do not match ("+X1.rows+" and "+X2.rows+")");
		if(X1.rows==X1.cols) {
			// always copy X1 because ludcmp replaces its first arg with its lu decomposition
			int n = X1.rows;
			Matrix temp = createMatrix();
			X1.directIndexCopy(temp);  // make sure temp is not stored as transpose
			int[] indx = new int[n];
  			Algorithms.ludcmp(temp.data,n,indx);
			X2.directIndexCopy(Y);
			Algorithms.lubksb(temp.data,n,indx,Y.data,Y.cols);
			temp.clear();
		} else {  // Use SVD (different than Matlab, which uses QR)
			Matrix U = createMatrix();
			Matrix S = createMatrix();
			Matrix V = createMatrix();
			int j,m = X1.rows, n = X1.cols;
			S.redimension(1,n,false);
			V.redimension(n,n,false);
			X1.directIndexCopy(U);
			double[][] u=U.data,v=V.data;
			double[] s = S.data[0];
			Algorithms.svdcmp(u,m,n,s,v);
			// zero out the small singular values
			double smax=0.0;
			for(j=0;j<n;j++) {
				if(s[j]>smax){
					smax = s[j];
				}
			}
			double smin = 1.0e-6*smax;
			for(j=0;j<n;j++){
				if(s[j]<smin){
					s[j] = 0.0;
				}
			}
			X2.forceDirectIndexing();
			Y.redimension(n,X2.cols,false);
			double[][] x2=X2.data, y=Y.data;
			Algorithms.svbksb(u,s,v,m,n,x2,X2.cols, y);
			U.clear();
			S.clear();
			V.clear();
		}
	}

	/** Division of a matrix by a scalar */
	public static final void divide(Matrix X, double d, Matrix Y) {
		multiply(X, 1.0/d, Y);
	}

	/** Element-by-element division of two matrices.  X2 can be a scalar, a vector with
	the same column dimension as X1, or a matrix matching X1's dimensions. */
	public static void divideElements(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		if (X2.elements==1){
			divide(X1,X2.get(0),Y);
		}
		else if (X1.rows == X2.rows && X1.cols == X2.cols) {
			int rows = X1.rows, cols = X1.cols;
			Y.redimension(rows, cols, X1.transposed);
			double[][] yd=Y.data, x1d=X1.data, x2d=X2.data;
			if(!X1.transposed && !X2.transposed){ 
				for(int i=0;i<rows;i++){
					for(int j=0;j<cols;j++){
						yd[i][j] = x1d[i][j]/x2d[i][j];
					}
				}
			} else if(X1.transposed && !X2.transposed) {
				for(int i=0;i<rows;i++){
					for(int j=0;j<cols;j++){
						yd[j][i] = x1d[j][i]/x2d[i][j];
					}
				}
			} else if(!X1.transposed && X2.transposed) {
				for(int i=0;i<rows;i++){
					for(int j=0;j<cols;j++){
						yd[i][j] = x1d[i][j]/x2d[j][i];
					}
				}
			} else {// both transposed
				for(int i=0;i<rows;i++) {
					for(int j=0;j<cols;j++) {
						yd[j][i] = x1d[j][i]/x2d[j][i];
					}
				}
			}
		} else if (X2.rows == 1 && X1.rows > 1 && X2.cols == X1.cols) { // divide a matrix and a vector
			if(X1==Y || X2==Y) {  //create temporary storage
				Matrix TY = createMatrix();
				divideElements(X1,X2,TY);
				TY.destructiveCopy(Y);
				return;
			}
			Y.redimension(X1.rows,X1.cols,X1.transposed);
			double[][] xd = X1.data, yd = Y.data;
			double x2val;
			if (X1.transposed) {
				for(int j=0;j<X1.cols;j++) {
					x2val = X2.get(j);
					for(int i=0;i<X1.rows;i++){
						yd[j][i] = xd[j][i]/x2val;
					}
				}				
			} else {
				for(int j=0;j<X1.cols;j++) {
					x2val = X2.get(j);
					for(int i=0;i<X1.rows;i++){
						yd[i][j] = xd[i][j]/x2val;
					}
				}
			}
		} else if (X2.cols == 1 && X1.cols > 1 && X2.rows == X1.rows) { // divide a matrix and a column vector
			if(X1==Y || X2==Y) {  //create temporary storage
				Matrix TY = createMatrix();
				divideElements(X1,X2,TY);
				TY.destructiveCopy(Y);
				return;
			}
			Y.redimension(X1.rows,X1.cols,X1.transposed);
			double[][] xd = X1.data, yd = Y.data;
			double x2val;
			if (X1.transposed) {
				for(int i=0;i<X1.rows;i++) {
					x2val = X2.get(i);
					for(int j=0;j<X1.cols;j++){
						yd[j][i] = xd[j][i]/x2val;
					}
				}				
			} else {
				for(int i=0;i<X1.rows;i++) {
					x2val = X2.get(i);
					for(int j=0;j<X1.cols;j++){
						yd[i][j] = xd[i][j]/x2val;
					}
				}
			}
		}
		else throw new MathException("divideElements: bad matrix dimensions "+X1.rows+"x"+X1.cols+" and "+X2.rows+"x"+X2.cols+".");
	}

	/** The dot product of two vectors, with orientations automatically
	determined.  A scalar is returned */
	public static final double dotProduct(Matrix X1, Matrix X2) throws MathException {
		double sum = 0.0;
		if (X1.elements != X2.elements) 
			throw new MathException("dotProduct: incommensurate lengths "+X1.elements+", "+X2.elements);	
		int n = X1.elements;
		boolean col1=false,col2=false;
		if(X1.rows>1) {
			if(!X1.transposed){
				col1 = true;
			}
		} else {
			if(X1.transposed){
				col1 = true;
			}
		}
		if(X2.rows>1) {
			if(!X2.transposed){
				col2 = true;
			}
		} else {
			if(X2.transposed){
				col2 = true;
			}
		}
		double[][] x1=X1.data,x2=X2.data;
		if(col1 && col2) {
			for(int i=0;i<n;i++){
				sum += x1[i][0]*x2[i][0];
			}
		} else if (!col1 && col2) {
			for(int i=0;i<n;i++){
				sum += x1[0][i]*x2[i][0];
			}
		} else if (col1 && !col2) {
			for(int i=0;i<n;i++) {
				sum += x1[i][0]*x2[0][i];
			}
		} else {
			for(int i=0;i<n;i++){
				sum += x1[0][i]*x2[0][i];
			}
		}
		return sum;
	}

	/** Inner product two matrices.  If either matrix is a scalar, it multiplies each element. 
	is used.  Otherwise, the column dimension of the first matrix must match the row dimension
	of the second matrix */
	public static final void multiply(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		if (X1.elements == 1){
			multiply(X2, X1.get(0), Y);
		} else if (X2.elements == 1){
			multiply(X1, X2.get(0), Y);
		} else if (X1.cols == X2.rows) {
			if(X1==Y||X2==Y) {  //create temporary storage
				Matrix TY = createMatrix();
				multiply(X1,X2,TY); 
				TY.destructiveCopy(Y);
				return;
			}
			Y.redimension(X1.rows,X2.cols);
			double sum;
			int row,col,id,rows=X1.rows,cols=X2.cols,ids=X1.cols;
			double[][] d1 = X1.data, d2 = X2.data;
			if(!X1.transposed && !X2.transposed) {
				for(row=0;row<rows;row++){
					for(col=0;col<cols;col++) {
				        sum = 0.0;
						for(id=0; id<ids;id++){
							sum += d1[row][id]*d2[id][col];
						}
						Y.set(row,col,sum);
					}
				}
			}
			else if (X1.transposed && !X2.transposed) {
				for(row=0;row<rows;row++){
					for(col=0;col<cols;col++) {
				        sum = 0.0;
						for(id=0; id<ids;id++) {
							sum += d1[id][row]*d2[id][col];
						}
						Y.set(row,col,sum);
					}
				}
			}
			else if (!X1.transposed && X2.transposed) {
				for(row=0;row<rows;row++){ 
					for(col=0;col<cols;col++) {
						sum = 0.0;
						for(id=0; id<ids;id++) {
							sum += d1[row][id]*d2[col][id];
						}
						Y.set(row,col,sum);
					}
				}
			}
			else { // both transposed
				for(row=0;row<rows;row++){ 
					for(col=0;col<cols;col++) {
						sum = 0.0;
						for(id=0; id<ids;id++) {
							sum += d1[id][row]*d2[col][id];
						}
						Y.set(row,col,sum);
					}
				}
			}
		}
		else{
			throw new MathException("multiply: bad matrix dimensions "+X1.rows+"x"+X1.cols+" and "+X2.rows+"x"+X2.cols+".");
		}
	}

	/** Multiplication of a matrix by a scalar */
	public static final void multiply(Matrix X, double d, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		for(int i=0;i<rows;i++) {
			for(int j=0;j<cols;j++) {
				yd[i][j] = d*xd[i][j];
			}
		}
	}

	/** Element-by-element multiplication of two matrices */
	public static void multiplyElements(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		if (X1.elements == 1){
			multiply(X2, X1.get(0), Y);
		}
		else if (X1.rows == X2.rows && X1.cols == X2.cols) {		
			int rows = X1.rows, cols = X1.cols;
			Y.redimension(rows, cols, X1.transposed);
			double[][] yd=Y.data, x1d=X1.data, x2d=X2.data;
			if(!X1.transposed && !X2.transposed) {
				for(int i=0;i<rows;i++) {
					for(int j=0;j<cols;j++){
						yd[i][j] = x1d[i][j]*x2d[i][j];
					}
				}
			} else if(X1.transposed && !X2.transposed) {
				for(int i=0;i<rows;i++) {
					for(int j=0;j<cols;j++){
						yd[j][i] = x1d[j][i]*x2d[i][j];
					}
				}
			} else if(!X1.transposed && X2.transposed) {
				for(int i=0;i<rows;i++){
					for(int j=0;j<cols;j++){
						yd[i][j] = x1d[i][j]*x2d[j][i];
					}
				}
			} else { // both transposed
				for(int i=0;i<rows;i++) {
					for(int j=0;j<cols;j++){
						yd[j][i] = x1d[j][i]*x2d[j][i];
					}
				}
			}
		} else if (X2.rows == 1 && X1.rows > 1 && X2.cols == X1.cols) { // multiply a matrix and a row vector
			if(X1==Y || X2==Y) {  //create temporary storage
				Matrix TY = createMatrix();
				multiplyElements(X1,X2,TY);
				TY.destructiveCopy(Y);
				return;
			}
			Y.redimension(X1.rows,X1.cols,X1.transposed);
			double[][] xd = X1.data, yd = Y.data;
			double x2val;
			if (X1.transposed) {
				for(int j=0;j<X1.cols;j++) {
					x2val = X2.get(j);
					for(int i=0;i<X1.rows;i++){
						yd[j][i] = xd[j][i]*x2val;
					}
				}				
			} else {
				for(int j=0;j<X1.cols;j++) {
					x2val = X2.get(j);
					for(int i=0;i<X1.rows;i++){
						yd[i][j] = xd[i][j]*x2val;
					}
				}
			}
		} else if (X2.cols == 1 && X1.cols > 1 && X2.rows == X1.rows) { // multiply a matrix and a column vector
			if(X1==Y || X2==Y) {  //create temporary storage
				Matrix TY = createMatrix();
				multiplyElements(X1,X2,TY);
				TY.destructiveCopy(Y);
				return;
			}
			Y.redimension(X1.rows,X1.cols,X1.transposed);
			double[][] xd = X1.data, yd = Y.data;
			double x2val;
			if (X1.transposed) {
				for(int i=0;i<X1.rows;i++) {
					x2val = X2.get(i);
					for(int j=0;j<X1.cols;j++){
						yd[j][i] = xd[j][i]*x2val;
					}
				}				
			} else {
				for(int i=0;i<X1.rows;i++) {
					x2val = X2.get(i);
					for(int j=0;j<X1.cols;j++){
						yd[i][j] = xd[i][j]*x2val;
					}
				}
			}
		}
		else throw new MathException("multiplyElements: bad matrix dimensions "+X1.rows+"x"+X1.cols+" and "+X2.rows+"x"+X2.cols+".");
	}

	/** TBD: Raise a square matrix to an integer power by successive multiplication */
	public static final void power(Matrix X, int p, Matrix Y) {

	}

	/** TBD:  Raise a matrix to any power using eigenvalue decomposition */
	public static final void power(Matrix X, double d, Matrix Y) {


	}

	/** Raise each element of a matrix to a scalar power */
	public static final void powerElements(Matrix X, double d, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		for(int i=0;i<rows;i++) {
			for(int j=0;j<cols;j++) {
				yd[i][j] = Math.pow(xd[i][j],d);
			}
		}
	}

	/** Each element of the first matrix is raised to the power of the element of the second matrix */
	public static void powerElements(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		if (X1.rows != X2.rows || X1.cols != X2.cols)
			throw new MathException("powerElements: bad matrix dimensions "+X1.rows+"x"+X1.cols+" and "+X2.rows+"x"+X2.cols+".");
		int rows = X1.rows, cols = X1.cols;
		Y.redimension(rows, cols, X1.transposed);
		double[][] yd=Y.data, x1d=X1.data, x2d=X2.data;
		if(!X1.transposed && !X2.transposed) {
			for(int i=0;i<rows;i++){
				for(int j=0;j<cols;j++){
					yd[i][j] = Math.pow(x1d[i][j],x2d[i][j]);
				}
			}
		} else if(X1.transposed && !X2.transposed) {
			for(int i=0;i<rows;i++) {
				for(int j=0;j<cols;j++) {
					yd[j][i] = Math.pow(x1d[j][i],x2d[i][j]);
				}
			}
		} else if(!X1.transposed && X2.transposed) {
			for(int i=0;i<rows;i++) {
				for(int j=0;j<cols;j++){
					yd[i][j] = Math.pow(x1d[i][j],x2d[j][i]);
				}
			}
		} else { // both tranposed
			for(int i=0;i<rows;i++) {
				for(int j=0;j<cols;j++){
					yd[j][i] = Math.pow(x1d[j][i],x2d[j][i]);
				}
			}
		}
	}

	/** Subtracts two matrices. If either is a scalar, it is subtracted from all elements.  
	If X1 is a matrix and X2 is a row vector with equal number of columns, then X2 
	is subtracted from each element in the corresponding column of X1 (a useful
	addition to Matlab behavior). */
	public static final void subtract(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		if (X2.elements == 1) {
			add(X1, -X2.get(0), Y);
		} else if (X1.rows == X2.rows && X1.cols == X2.cols) {
			int rows = X1.rows, cols = X1.cols;
			Y.redimension(rows, cols, X1.transposed);
			double[][] yd=Y.data, x1d=X1.data, x2d=X2.data;
			if(!X1.transposed && !X2.transposed) {
				for(int i=0;i<rows;i++) {
					for(int j=0;j<cols;j++){
						yd[i][j] = x1d[i][j] - x2d[i][j];
					}
				}
			} else if(X1.transposed && !X2.transposed) {
				for(int i=0;i<rows;i++) {
					for(int j=0;j<cols;j++) {
						yd[j][i] = x1d[j][i] - x2d[i][j];
					}
				}
			} else if(!X1.transposed && X2.transposed) {
				for(int i=0;i<rows;i++) {
					for(int j=0;j<cols;j++) {
						yd[i][j] = x1d[i][j] - x2d[j][i];
					}
				}
			} else { // both transposed
				for(int i=0;i<rows;i++) {
					for(int j=0;j<cols;j++) {
						yd[j][i] = x1d[j][i] - x2d[j][i];
					}
				}
			}
		} else if (X2.rows == 1 && X1.rows > 1 && X2.cols == X1.cols) { // subtract a matrix and a row vector
			if(X1==Y || X2==Y) {  //create temporary storage
				Matrix TY = createMatrix();
				subtract(X1,X2,TY);
				TY.destructiveCopy(Y);
				return;
			}
			Y.redimension(X1.rows,X1.cols,X1.transposed);
			double[][] xd = X1.data, yd = Y.data;
			double x2val;
			if (X1.transposed) {
				for(int j=0;j<X1.cols;j++) {
					x2val = X2.get(j);
					for(int i=0;i<X1.rows;i++) {
						yd[j][i] = xd[j][i] - x2val;
					}
				}				
			} else {
				for(int j=0;j<X1.cols;j++) {
					x2val = X2.get(j);
					for(int i=0;i<X1.rows;i++) {
						yd[i][j] = xd[i][j] - x2val;
					}
				}
			}
		} else if (X2.cols == 1 && X1.cols > 1 && X2.rows == X1.rows) { // subtract a matrix and a column vector
			if(X1==Y || X2==Y) {  //create temporary storage
				Matrix TY = createMatrix();
				subtract(X1,X2,TY);
				TY.destructiveCopy(Y);
				return;
			}
			Y.redimension(X1.rows,X1.cols,X1.transposed);
			double[][] xd = X1.data, yd = Y.data;
			double x2val;
			if (X1.transposed) {
				for(int i=0;i<X1.rows;i++) {
					x2val = X2.get(i);
					for(int j=0;j<X1.cols;j++){
						yd[j][i] = xd[j][i] - x2val;
					}
				}				
			} else {
				for(int i=0;i<X1.rows;i++) {
					x2val = X2.get(i);
					for(int j=0;j<X1.cols;j++){
						yd[i][j] = xd[i][j] - x2val;
					}
				}
			}
		}
		else throw new MathException("subtract: bad matrix dimensions "+X1.rows+"x"+X1.cols+" and "+X2.rows+"x"+X2.cols+"."); 
	}


	/** Subtraction of a scalar from a matrix */
	public static final void subtract(Matrix X, double d, Matrix Y) {
		add(X, -d, Y);
	}

	/** Flips the sign of every element of the matrix */
	public static final void unaryMinus(Matrix X, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		for(int i=0;i<rows;i++) {
			for(int j=0;j<cols;j++){
				yd[i][j] = -xd[i][j];
			}
		}
	}

/*  ELEMENTARY MATH FUNCTIONS */

  	/**  The absolute value of a matrix */
	public static final void abs(Matrix X, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++){
				yd[i][j] = Math.abs(xd[i][j]);
			}
		}
	}
	
	/** Elements of X are rounded up to the nearest integer value */
	public static final void ceil(Matrix X, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++){
				yd[i][j] = Math.ceil(xd[i][j]);
			}
		}
	}

	/** Exponential, element-by-element */
	public static final void exp(Matrix X, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++) {
				yd[i][j] = Math.exp(xd[i][j]);
			}
		}
	}

	/** Elements of X rounded towards zero */
	public static final void fix(Matrix X, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		double d;
		for(int i=0;i<rows;i++) {
			for(int j=0;j<cols;j++) {
				d = xd[i][j];
				if(d<0){
					yd[i][j] = Math.ceil(d);
				} else {
					yd[i][j] = Math.floor(d);
				}
			}
		}
	}

	/** Elements of X rounded down to next-lowest integer */
	public static final void floor(Matrix X, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++){
				yd[i][j] = Math.floor(xd[i][j]);
			}
		}
	}

	/** Natural log, element-by-element */
	public static final void log(Matrix X, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++){
				yd[i][j] = Math.log(xd[i][j]);
			}
		}
	}

	/** Base-10 logarithm */
	public static final void log10(Matrix X, Matrix Y) {
		log(X, Y);
		multiply(Y, 1.0/Math.log(10.0), Y);
	}

	/** Remainders from dividing X1 by X2, element-by-element  */
	public static final void rem(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		if (X1.rows != X2.rows || X1.cols != X2.cols) 
			throw new MathException("rem: bad matrix dimensions "+X1.rows+"x"+X1.cols+" and "+X2.rows+"x"+X2.cols+".");
		int rows = X1.rows, cols = X1.cols;
		Y.redimension(rows, cols, X1.transposed);
		double[][] yd=Y.data, x1d=X1.data, x2d=X2.data;
		if(!X1.transposed && !X2.transposed) {
			for(int i=0;i<rows;i++){
				for(int j=0;j<cols;j++){
					yd[i][j] = Algorithms.remainder(x1d[i][j],x2d[i][j]);
				}
			}
		} else if(X1.transposed && !X2.transposed) {
			for(int i=0;i<rows;i++){
				for(int j=0;j<cols;j++){
					yd[j][i] = Algorithms.remainder(x1d[j][i],x2d[i][j]);
				}
			}
		} else if(!X1.transposed && X2.transposed) {
			for(int i=0;i<rows;i++){
				for(int j=0;j<cols;j++) {
					yd[i][j] = Algorithms.remainder(x1d[i][j],x2d[j][i]);
				}
			}
		} else { // both tranposed
			for(int i=0;i<rows;i++) {
				for(int j=0;j<cols;j++){
					yd[j][i] = Algorithms.remainder(x1d[j][i],x2d[j][i]);
				}
			}
		}
	}

	/** Rounding to the nearest integer value */
	public static final void round(Matrix X, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++) {
				yd[i][j] = Math.round(xd[i][j]);
			}
		}
	}

	/** Applies a sigmoid function with limits -1 to 1 to the matrix */
	public static final void sigmoid(Matrix X, Matrix Y) {
		if(X!=Y){
			Y.redimension(X.rows,X.cols,X.transposed);
		}
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		double d;
		for(int i=0;i<rows;i++) {
			for(int j=0;j<cols;j++) {
				d = xd[i][j];
				if (d>=SIGMOID_LIM){
					yd[i][j] = 1.0;
				} else if (d<=NEG_SIGMOID_LIM){
					yd[i][j] = -1.0;
				} else {
					yd[i][j] = 2.0/(1.0 + Math.exp(-d)) - 1.0;
				}
			}
		}
	}

	/** Returns -1,0,1 depending on the elements being <0, ==0, >0 */
	public static final void sign(Matrix X, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		double d;
		for(int i=0;i<rows;i++){ 
			for(int j=0;j<cols;j++) {
				d = xd[i][j];
				if (d<0){
					yd[i][j] = -1.0;
				} else if (d>0){
					yd[i][j] = 1.0;
				} else{
					yd[i][j] = 0.0;
				}
			}
		}
	}

	/** Square root, element-by-element */
	public static final void sqrt(Matrix X, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++) {
				yd[i][j] = Math.sqrt(xd[i][j]);
			}
		}
	}


/* LOGICAL OPERATORS */

	/** AND operator on two matrices */ 
	public static final void and(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		if (X1.rows != X2.rows || X1.cols != X2.cols)
			throw new MathException("and: bad matrix dimensions "+X1.rows+"x"+X1.cols+" and "+X2.rows+"x"+X2.cols+".");
		int i,j,rows = X1.rows, cols = X1.cols;
		Y.redimension(rows, cols, X1.transposed);
		Y.initialize(Matrix.ZEROS);
		double[][] yd=Y.data, x1d=X1.data, x2d=X2.data;
		if(!X1.transposed && !X2.transposed) 
			{
			for(i=0;i<rows;i++) 
				for(j=0;j<cols;j++) 
					if(Double.compare(x1d[i][j], 0.0) != 0 && Double.compare(x2d[i][j], 0.0) != 0) 
						yd[i][j] = 1.0;
			}
		else if(X1.transposed && !X2.transposed) 
			{
			for(i=0;i<rows;i++) 
				for(j=0;j<cols;j++) 
					if(Double.compare(x1d[j][i], 0.0) != 0 && Double.compare(x2d[i][j], 0.0) != 0) 
						yd[j][i] = 1.0;
			}
		else if(!X1.transposed && X2.transposed) 
			{
			for(i=0;i<rows;i++) 
				for(j=0;j<cols;j++) 
					if(Double.compare(x1d[i][j], 0.0) != 0 && Double.compare(x2d[j][i], 0.0) != 0) 
						yd[i][j] = 1.0;
			}
		else // both tranposed
			{
			for(i=0;i<rows;i++) 
				for(j=0;j<cols;j++) 
					if(Double.compare(x1d[j][i], 0.0) != 0 && Double.compare(x2d[j][i], 0.0) != 0) 
						yd[j][i] = 1.0;
			}
	 }

	 /** NOT operator on a matrix */
	 public static final void not(Matrix X, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		for(int i=0;i<rows;i++) {
			for(int j=0;j<cols;j++) {
				if(Double.compare(xd[i][j], 0.0) == 0) 
					yd[i][j]=1.0; 
				else 
					yd[i][j]=0.0;
			}
		}
	 }

	 /** OR operator on two matrices */
	 public static final void or(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		if (X1.rows != X2.rows || X1.cols != X2.cols)
			throw new MathException("or: bad matrix dimensions "+X1.rows+"x"+X1.cols+" and "+X2.rows+"x"+X2.cols+".");
		int i,j,rows = X1.rows, cols = X1.cols;
		Y.redimension(rows, cols, X1.transposed);
		Y.initialize(Matrix.ZEROS);
		double[][] yd=Y.data, x1d=X1.data, x2d=X2.data;
		if(!X1.transposed && !X2.transposed) 
			{
			for(i=0;i<rows;i++) 
				for(j=0;j<cols;j++) 
					if(Double.compare(x1d[i][j], 0.0) != 0 || Double.compare(x2d[i][j], 0.0) != 0) 
						yd[i][j] = 1.0;
			}
		else if(X1.transposed && !X2.transposed) 
			{
			for(i=0;i<rows;i++) 
				for(j=0;j<cols;j++) 
					if(Double.compare(x1d[j][i], 0.0) != 0 || Double.compare(x2d[i][j], 0.0) != 0) 
						yd[j][i] = 1.0;
			}
		else if(!X1.transposed && X2.transposed) 
			{
			for(i=0;i<rows;i++) 
				for(j=0;j<cols;j++) 
					if(Double.compare(x1d[i][j], 0.0) != 0 || Double.compare(x2d[j][i], 0.0) != 0) 
						yd[i][j] = 1.0;
			}
		else // both tranposed
			{
			for(i=0;i<rows;i++) 
				for(j=0;j<cols;j++) 
					if(Double.compare(x1d[j][i], 0.0) != 0 || Double.compare(x2d[j][i], 0.0) != 0) 
						yd[j][i] = 1.0;
			}
	 }

	 /** Exclusive or operator on two matrices */
	 public static final void xor(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		if (X1.rows != X2.rows || X1.cols != X2.cols)
			throw new MathException("xor: bad matrix dimensions "+X1.rows+"x"+X1.cols+" and "+X2.rows+"x"+X2.cols+".");
		int i,j,rows = X1.rows, cols = X1.cols;
		Y.redimension(rows, cols, X1.transposed);
		Y.initialize(Matrix.ZEROS);
		double[][] yd=Y.data, x1d=X1.data, x2d=X2.data;
		if(!X1.transposed && !X2.transposed) 
			{
			for(i=0;i<rows;i++) 
				for(j=0;j<cols;j++) 
					if((Double.compare(x1d[i][j], 0.0) != 0 || Double.compare(x2d[i][j], 0.0) != 0)
							&& (Double.compare(x1d[i][j], 0.0) == 0 || Double.compare(x2d[i][j], 0.0) == 0)) 
						yd[i][j] = 1.0;
			}
		else if(X1.transposed && !X2.transposed) 
			{
			for(i=0;i<rows;i++) 
				for(j=0;j<cols;j++) 
					if((Double.compare(x1d[j][i], 0.0) != 0 || Double.compare(x2d[i][j], 0.0) != 0)
							&& (Double.compare(x1d[j][i], 0.0) == 0 || Double.compare(x2d[i][j], 0.0) == 0)) 
						yd[j][i] = 1.0;
			}
		else if(!X1.transposed && X2.transposed) 
			{
			for(i=0;i<rows;i++) 
				for(j=0;j<cols;j++) 
					if((Double.compare(x1d[i][j], 0.0) != 0 || Double.compare(x2d[j][i], 0.0) != 0)
						&& (Double.compare(x1d[i][j], 0.0) == 0 || Double.compare(x2d[j][i], 0.0) == 0)) 
							yd[i][j] = 1.0;
			}
		else // both tranposed
			{
			for(i=0;i<rows;i++) 
				for(j=0;j<cols;j++) 
					if((Double.compare(x1d[j][i], 0.0) != 0 || Double.compare(x2d[j][i], 0.0) != 0)
					&&(Double.compare(x1d[j][i], 0.0) == 0 || Double.compare(x2d[j][i], 0.0) == 0)) 
							yd[j][i] = 1.0;
			}
	 }

/*  LOGICAL FUNCTIONS */

	/** For vectors, returns 1 (as a matrix) if all the elements of X are nonzero.
	For a matrix, all operates on the columns of X, returning a row vector of 0's and 1's. */
	public static final void all(Matrix X, Matrix Y) {
		/* return 0.0 if any single element is zero */
		if(X==Y) {  // create temporary storage
			Matrix TY = createMatrix();
			all(X,TY); 
			TY.destructiveCopy(Y);
			return;
		}
		if (X.rows == 1 || X.cols == 1) {
			Y.redimension(1,1);
			Y.data[0][0] = 1.0;
			double[][] xd = X.data;
			if(X.rows==1 && X.transposed || X.cols==1 && !X.transposed) {
				for (int i=0;i<X.elements;i++) 
					if (Double.compare(xd[i][0], 0.0) == 0) {
						Y.data[0][0] = 0.0; 
						return;
					}
			} else {
   				for (int i=0;i<X.elements;i++) 
					if (Double.compare(xd[0][i], 0.0) == 0) {
						Y.data[0][0] = 0.0; 
						return;
					}
			}
		} else {
			Y.redimension(1,X.cols,false);
			Y.initialize(Matrix.ONES);
			double[][] xd = X.data, yd = Y.data;
			if(X.transposed) {
   				for (int j=0;j<X.cols; j++) {
   					for(int i=0;i<X.rows; i++) {
						if(Double.compare(xd[j][i], 0.0) == 0) {
							yd[0][j] = 0.0; 
							break;
						}
   					}
   				}
			} else {
				for (int j=0;j<X.cols; j++){
					for(int i=0;i<X.rows; i++) {
						if(Double.compare(xd[i][j], 0.0) == 0) {
							yd[0][j] = 0.0; 
							break;
						}
					}
				}
			}
		}
	}

	/** For vectors, returns 1 (as a matrix) if any the elements of X are nonzero.
	For a matrix, all operates on the columns of X, returning a row vector of 0's and 1's. */
	public static final void any(Matrix X, Matrix Y) {
		/* returns 1.0 if any elements are nonzero */
		if(X==Y) {  // create temporary storage
			Matrix TY = createMatrix();
			any(X,TY); 
			TY.destructiveCopy(Y);
			return;
		}
		if (X.rows == 1 || X.cols == 1) {
			Y.redimension(1,1);
			Y.data[0][0] = 0.0;
			double[][] xd = X.data;
			if(X.rows==1 && X.transposed || X.cols==1 && !X.transposed) {
				for (int i=0;i<X.elements;i++) 
					if (Double.compare(xd[i][0], 0.0) != 0) {
						Y.data[0][0]=1.0; 
						return;
					}
			} else {
				for (int i=0;i<X.elements;i++) 
					if (Double.compare(xd[0][i], 0.0) != 0) {
						Y.data[0][0]=1.0; 
						return;
					}
			}
		} else {
			Y.redimension(1,X.cols,false);
			Y.initialize(Matrix.ZEROS);
			double[][] xd = X.data, yd = Y.data;
			if(X.transposed) {
				for (int j=0;j<X.cols; j++) {
					for(int i=0;i<X.rows; i++) {
						if(Double.compare(xd[j][i], 0.0) != 0) {
							yd[0][j]=1.0; 
							break;
						}
					}
				}
			} else {
				for (int j=0;j<X.cols; j++) {
					for(int i=0;i<X.rows; i++){ 
						if(Double.compare(xd[i][j], 0.0) != 0) {
							yd[0][j]=1.0; 
							break;
						}
					}
				}
			}
		}
	}

	/** Find the non-zero elements of X, putting the indices in Y */
	public static final void find(Matrix X, Matrix Y) throws MathException {
		int nfound = 0;
		Matrix temp = Matrix.newMatrix(X.elements, 1, true); // always need temp matrix, since we don't know final dimensions
		double[][] xd = X.data, td = temp.data;
		if(X.transposed) {
	  		for(int i=0;i<X.rows;i++){ 
	  			for(int j=0;j<X.cols;j++) {
					if (Double.compare(xd[j][i], 0.0) != 0) {
						td[0][nfound] = i; 
						nfound++;
					}
	  			}
	  		}
		} else {
	  		for(int i=0;i<X.rows;i++){ 
	  			for(int j=0;j<X.cols;j++) {
					if (Double.compare(xd[i][j], 0.0) != 0) {
						td[0][nfound] = i; 
						nfound++;
					}
	  			}
	  		}
		}
		if (nfound == 0){
			Y.redimension(0,0);
		}
		else {
			getPart(temp,0,0,nfound-1, 0, Y);	 // Y redimensioned in getPart
		}
		temp.clear();
	}

	/** Find the non-zero elements of X, putting the rows and column indices
	of the non-zero elements in Rows and Cols */
	public static final void find(Matrix X, Matrix Rows, Matrix Cols) throws MathException {
		Matrix temp = createMatrix();
		find(X, Rows, Cols, temp);
		temp.clear();
	}

	/** Find the non-zero elements of X, putting the rows and columns in Rows and Cols,
	respectively, and the values of the non-zero elements in Values */
	public static final void find(Matrix X, Matrix Rows, Matrix Cols, Matrix Values) throws MathException {
		int nfound = 0;
		Matrix tempRows = Matrix.newMatrix(X.elements, 1, true);
		Matrix tempCols = Matrix.newMatrix(X.elements, 1, true);
		Matrix tempVals = Matrix.newMatrix(X.elements, 1, true);
		double[][] xd=X.data,tr=tempRows.data,tc=tempCols.data,tv=tempVals.data;
		if (X.transposed) {
			for (int i=0;i<X.rows;i++){
				for(int j=0; j<X.cols; j++) {
					if (Double.compare(xd[j][i], 0.0) != 0) {
						tr[0][nfound] = i;
						tc[0][nfound] = j;
						tv[0][nfound] = xd[j][i];
						nfound++;
					}
				}
			}
		} else {	
			for (int i=0;i<X.rows;i++){
				for(int j=0; j<X.cols; j++) {
					if (Double.compare(xd[i][j], 0.0) != 0) {
						tr[0][nfound] = i;
						tc[0][nfound] = j;
						tv[0][nfound] = xd[i][j];
						nfound++;
					}
				}
			}
		}
		if (nfound == 0) {
			Rows.redimension(0,0);
			Cols.redimension(0,0);
			Values.redimension(0,0);
		} else {
			getPart(tempRows,0,0,nfound-1,0, Rows);
			getPart(tempCols,0,0,nfound-1,0, Cols);
			getPart(tempVals,0,0,nfound-1,0, Values);
		}
		tempRows.clear();
		tempCols.clear();
		tempVals.clear();
	}

	/** Finds the finite values in X, returning a matrix of 0's and 1's.
	A value is finite if it is not infinite and not a NaN */
	public static final void findFinite(Matrix X, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		int rows, cols;
		double d;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++) {
				d = xd[i][j];
				if(Double.isNaN(d) || Double.isInfinite(d)){
					yd[i][j]= 0.0;
				}else {
					yd[i][j]=1.0;
				}
			}
		}
	}

	/** Finds the finite rows of X, returning a matrix of 0's and 1's.
	A value is finite if it is not infinite and not a NaN.
	This function is faster than calling findFinite, and applying logical
	functions on the resulting logical matrix */
	public static final void findFiniteRows(Matrix X, Matrix Y) {
		Y.redimension(X.rows, 1);
		int rows, cols;
		double d;
		double[][] xd=X.data;
		boolean isFinite;
		if(!X.transposed) {
			for(int i=0;i<X.rows;i++) {
				isFinite = true;
				for(int j=0;j<X.cols;j++) {
					d = xd[i][j];
					if(Double.isNaN(d) || Double.isInfinite(d)) {
						isFinite = false;
						break;
					}
				}
				if(isFinite){
					Y.set(i,1.0);
				} else{
					Y.set(i,0.0);
				}
			}
		} else {
			for(int i=0;i<X.rows;i++) {
				isFinite = true;
				for(int j=0;j<X.cols;j++) {
					d = xd[j][i];
					if(Double.isNaN(d) || Double.isInfinite(d)) {
						isFinite = false;
						break;
					}
				}
				if(isFinite){
					Y.set(i,1.0);
				} else {
					Y.set(i,0.0);	
				}
			}
		}
	}

	/** Finds the finite columns of X, returning a row vector 0's and 1's.
	A value is finite if it is not infinite and not a NaN.
	This function is faster than calling findFinite, and subsequently applying 
	logical functions to find the columns  */
	public static final void findFiniteColumns(Matrix X, Matrix Y) {
		Y.redimension(1, X.cols);
		int rows, cols;
		double d;
		double[][] xd=X.data;
		boolean isFinite;
		if(!X.transposed) {
			for(int j=0;j<X.cols;j++) {
				isFinite = true;
				for(int i=0;i<X.rows;i++) {
					d = xd[i][j];
					if(Double.isNaN(d) || Double.isInfinite(d)) {
						isFinite = false;
						break;
					}
				}
				if(isFinite){
					Y.set(j,1.0);
				} else {
					Y.set(j,0.0);
				}
			}
		} else {
			for(int j=0;j<X.cols;j++) {
				isFinite = true;
				for(int i=0;i<X.rows;i++) {
					d = xd[j][i];
					if(Double.isNaN(d) || Double.isInfinite(d)) {
						isFinite = false;
						break;
					}
				}
				if(isFinite) {
					Y.set(j,1.0);
				} else{
					Y.set(j,0.0);
				}
			}
		}
	}

	/** returns true if matrix contains any infinite values */
	public static final boolean isFinite(Matrix X) {
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] xd=X.data;
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++) {
				if(Double.isNaN(xd[i][j])) {
					return true;
				}
			}
		}
		return false;
	}

	/** Detects an empty matrix */
	public static final boolean isEmpty(Matrix M) {
		return M.rows == 0 || M.cols ==0 ;
	}

	/** Finds the infinite values in X, returning a matrix of 0's and 1's */
	public static final void findInf(Matrix X, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		for(int i=0;i<rows;i++) {
			for(int j=0;j<cols;j++) {
				if(Double.isInfinite(xd[i][j])){
					yd[i][j]=1.0;
				} else{
					yd[i][j]=0.0;
				}
			}
		}
	}

	/** Finds not-a-number elements in X, returning a matrix of 0's and 1's */
	public static final void findNaN(Matrix X, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++) {
				if(Double.isNaN(xd[i][j])){
					yd[i][j]=1.0;
				}else {
					yd[i][j]=0.0;
				}
			}
		}
	}

	/** returns true if matrix contains any NaNs.  
	If you want to check for infinite values, use isFinite */
	public static final boolean hasNaN(Matrix X) {
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] xd=X.data;
		for(int i=0;i<rows;i++) {
			for(int j=0;j<cols;j++) {
				if(Double.isNaN(xd[i][j])){
					return true;
				}
			}
		}
		return false;
	}

/* RELATIONAL OPERATORS */

	/** Generate a 0-1 matrix showing where X1 > X2 */
	public static final void gt(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		if (X1.rows != X2.rows || X1.cols != X2.cols)
			throw new MathException("gt: bad matrix dimensions "+X1.rows+"x"+X1.cols+" and "+X2.rows+"x"+X2.cols+".");
		int i,j,rows = X1.rows, cols = X1.cols;
		Y.redimension(rows, cols, X1.transposed);
		double[][] yd=Y.data, x1d=X1.data, x2d=X2.data;
		if(!X1.transposed && !X2.transposed) {
			for(i=0;i<rows;i++) {
				for(j=0;j<cols;j++) {
					if(x1d[i][j]>x2d[i][j]) {
						yd[i][j]=1.0;
					}else {
						yd[i][j]=0.0; 
					}
				}
			}
		} else if(X1.transposed && !X2.transposed) {
			for(i=0;i<rows;i++){
				for(j=0;j<cols;j++) {
					if(x1d[j][i]>x2d[i][j]) {
						yd[j][i]=1.0; 
					}else {
						yd[j][i]=0.0; 
					}
				}
			}
		} else if(!X1.transposed && X2.transposed) {
			for(i=0;i<rows;i++){
				for(j=0;j<cols;j++){
					if(x1d[i][j]>x2d[j][i]){
						yd[i][j]=1.0; 
					} else{
						yd[i][j]=0.0; 
					}
				}
			}
		} else {// both tranposed
			for(i=0;i<rows;i++) {
				for(j=0;j<cols;j++) {
					if(x1d[j][i]>x2d[j][i]) {
						yd[j][i]=1.0; 
					}else {
						yd[j][i]=0.0; 
					}
				}
			}
		}
	}

	/** Generates a matrix of 1's and 0's, showing where the elements of X1 > d */
	public static final void gt(Matrix X, double d, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++) {
				if(xd[i][j]>d){
					yd[i][j]=1.0;
				}else{
					yd[i][j]=0.0;
				}
			}
		}
	}

	/** Generate a 0-1 matrix showing where X1 < X2 */
	public static final void lt(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		if (X1.rows != X2.rows || X1.cols != X2.cols)
			throw new MathException("lt: bad matrix dimensions "+X1.rows+"x"+X1.cols+" and "+X2.rows+"x"+X2.cols+".");
		int i,j,rows = X1.rows, cols = X1.cols;
		Y.redimension(rows, cols, X1.transposed);
		double[][] yd=Y.data, x1d=X1.data, x2d=X2.data;
		if(!X1.transposed && !X2.transposed) {
			for(i=0;i<rows;i++) {
				for(j=0;j<cols;j++) {
					if(x1d[i][j]<x2d[i][j]){
						yd[i][j]=1.0; 
					} else { 
						yd[i][j]=0.0; 
					}
				}
			}
		} else if(X1.transposed && !X2.transposed) {
			for(i=0;i<rows;i++) {
				for(j=0;j<cols;j++) {
					if(x1d[j][i]<x2d[i][j]) {
						yd[j][i]=1.0; 
					} else { 
						yd[j][i]=0.0; 
					}
				}
			}
		} else if(!X1.transposed && X2.transposed) {
			for(i=0;i<rows;i++){
				for(j=0;j<cols;j++){
					if(x1d[i][j]<x2d[j][i]){
						yd[i][j]=1.0; 
					} else {
						yd[i][j]=0.0; 
					}
				}
			}
		} else { // both tranposed
			for(i=0;i<rows;i++){
				for(j=0;j<cols;j++) {
					if(x1d[j][i]<x2d[j][i]) {
						yd[j][i]=1.0; 
					} else {
						yd[j][i]=0.0; 
					}
				}
			}
		}
	}

	/** Generates a matrix of 1's and 0's, showing where the elements of X1 < d */
	public static final void lt(Matrix X, double d, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		for(int i=0;i<rows;i++) {
			for(int j=0;j<cols;j++) {
				if(xd[i][j]<d){
					yd[i][j]=1.0;
				}else {
					yd[i][j]=0.0;
				}
			}
		}
	}

	/** Generate a 0-1 matrix showing where X1 >= X2 */
	public static final void ge(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		if (X1.rows != X2.rows || X1.cols != X2.cols)
			throw new MathException("ge: bad matrix dimensions "+X1.rows+"x"+X1.cols+" and "+X2.rows+"x"+X2.cols+".");
		int i,j,rows = X1.rows, cols = X1.cols;
		Y.redimension(rows, cols, X1.transposed);
		double[][] yd=Y.data, x1d=X1.data, x2d=X2.data;
		if(!X1.transposed && !X2.transposed) {
			for(i=0;i<rows;i++){
				for(j=0;j<cols;j++){
					if(x1d[i][j]>=x2d[i][j]){
						yd[i][j]=1.0; }
					else{ 
						yd[i][j]=0.0;
					}
				}
			}
		} else if(X1.transposed && !X2.transposed) {
			for(i=0;i<rows;i++) {
				for(j=0;j<cols;j++) {
					if(x1d[j][i]>=x2d[i][j]) {
						yd[j][i]=1.0; 
					} else {
						yd[j][i]=0.0;
					}
				}
			}
		} else if(!X1.transposed && X2.transposed) {
			for(i=0;i<rows;i++) {
				for(j=0;j<cols;j++) {
					if(x1d[i][j]>=x2d[j][i]) {
						yd[i][j]=1.0; 
					} else {
						yd[i][j]=0.0;
					}
				}
			}
		} else {// both tranposed
			for(i=0;i<rows;i++) {
				for(j=0;j<cols;j++) {
					if(x1d[j][i]>=x2d[j][i]) {
						yd[j][i]=1.0; 
					} else {
						yd[j][i]=0.0;
					}
				}
			}
		}
	}

	/** Generates a matrix of 1's and 0's, showing where the elements of X1 >= d */
	public static final void ge(Matrix X, double d, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		for(int i=0;i<rows;i++) {
			for(int j=0;j<cols;j++) {
				if(xd[i][j]>=d){
					yd[i][j]=1.0;
				}else{
					yd[i][j]=0.0;
				}
			}
		}
	}

	/** Generate a 0-1 matrix showing where X1 <= X2 */
	public static final void le(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		if (X1.rows != X2.rows || X1.cols != X2.cols)
			throw new MathException("le: bad matrix dimensions "+X1.rows+"x"+X1.cols+" and "+X2.rows+"x"+X2.cols+".");
		int i,j,rows = X1.rows, cols = X1.cols;
		Y.redimension(rows, cols, X1.transposed);
		double[][] yd=Y.data, x1d=X1.data, x2d=X2.data;
		if(!X1.transposed && !X2.transposed) { 
			for(i=0;i<rows;i++) {
				for(j=0;j<cols;j++) {
					if(x1d[i][j]<=x2d[i][j]) {
						yd[i][j]=1.0; 
					}  else {
						yd[i][j]=0.0;
					}
				}
			}
		} else if(X1.transposed && !X2.transposed) {
			for(i=0;i<rows;i++) {
				for(j=0;j<cols;j++) {
					if(x1d[j][i]<=x2d[i][j]) {
						yd[j][i]=1.0; 
					} else { 
						yd[j][i]=0.0;
					}
				}
			}
		} else if(!X1.transposed && X2.transposed) {
			for(i=0;i<rows;i++) {
				for(j=0;j<cols;j++) {
					if(x1d[i][j]<=x2d[j][i]) {
						yd[i][j]=1.0; 
					} else {
						yd[i][j]=0.0; 
					}
				}
			}
		} else { // both tranposed
			for(i=0;i<rows;i++) {
				for(j=0;j<cols;j++) {
					if(x1d[j][i]<=x2d[j][i]) {
						yd[j][i]=1.0; 
					} else {
						yd[j][i]=0.0; 
					}
				}
			}
		}

	}

	/** Generates a matrix of 1's and 0's, showing where the elements of X1 <= d */
	public static final void le(Matrix X, double d, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++) {
				if(xd[i][j]<=d) 
					yd[i][j]=1.0;
				else 
					yd[i][j]=0.0;
			}
		}
	}

	/** Returns true if matrices are equal in element-by-element comparison */
	public static final boolean isEqual(Matrix X1, Matrix X2) {
		if (X1.rows != X2.rows || X1.cols != X2.cols) {
			return false;
		}
		int i,j,rows = X1.rows, cols = X1.cols;
		double[][] x1d=X1.data, x2d=X2.data;
		if(!X1.transposed && !X2.transposed) {
			for(i=0;i<rows;i++) {
				for(j=0;j<cols;j++) {
					if(Double.compare(x1d[i][j], x2d[i][j]) != 0) 
						return false;
				} 
			}
		} else if(X1.transposed && !X2.transposed) {
			for(i=0;i<rows;i++) {
				for(j=0;j<cols;j++) {
					if(Double.compare(x1d[j][i], x2d[i][j]) != 0) {
						return false;
					} 
				}
			}
		} else if(!X1.transposed && X2.transposed) {
			for(i=0;i<rows;i++){
				for(j=0;j<cols;j++) {
					if(Double.compare(x1d[i][j], x2d[j][i]) != 0) {
						return false;
					} 
				}
			}
		} else { // both tranposed
			for(i=0;i<rows;i++) {
				for(j=0;j<cols;j++) {
					if(Double.compare(x1d[j][i], x2d[j][i]) != 0) {
						return false;
					}
				}
			}
		}
		return true;
	}

	/** Generate a 0-1 matrix showing where elements of X1 and X2 are equal */
	public static final void isEqual(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		if (X1.rows != X2.rows || X1.cols != X2.cols)
			throw new MathException("equals: bad matrix dimensions "+X1.rows+"x"+X1.cols+" and "+X2.rows+"x"+X2.cols+".");
		int i,j,rows = X1.rows, cols = X1.cols;
		Y.redimension(rows, cols, X1.transposed);
		double[][] yd=Y.data, x1d=X1.data, x2d=X2.data;
		if(!X1.transposed && !X2.transposed) {
			for(i=0;i<rows;i++){
				for(j=0;j<cols;j++) {
					if(Double.compare(x1d[i][j], x2d[i][j]) == 0) 
						yd[i][j]=1.0; 
					else 
						yd[i][j]=0.0;
				} 
			}
		} else if(X1.transposed && !X2.transposed){
			for(i=0;i<rows;i++) {
				for(j=0;j<cols;j++) {
					if(Double.compare(x1d[j][i], x2d[i][j]) == 0) 
						yd[j][i]=1.0; 
					else 
						yd[j][i]=0.0;
				}
			}
		} else if(!X1.transposed && X2.transposed) {
			for(i=0;i<rows;i++) {
				for(j=0;j<cols;j++) {
					if(Double.compare(x1d[i][j], x2d[j][i]) == 0) 
						yd[i][j]=1.0; 
					else 
						yd[i][j]=0.0;
				}
			}
		} else { // both tranposed
			for(i=0;i<rows;i++){
				for(j=0;j<cols;j++) {
					if(Double.compare(x1d[j][i], x2d[j][i]) == 0) 
						yd[j][i]=1.0; 
					else 
						yd[j][i]=0.0;
				}
			} 
		}

	}

	/** Generates a matrix of 1's and 0's, showing where the elements of X1 == d */
	public static final void isEqual(Matrix X, double d, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++) {
				if(Double.compare(xd[i][j], d) == 0) 
					yd[i][j]=1.0;
				else 
					yd[i][j]=0.0;
			}
		}
	}

	/** Generate a 0-1 matrix showing where X1 != X2 */
	public static final void notEquals(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		if (X1.rows != X2.rows || X1.cols != X2.cols)
			throw new MathException("notEqual: bad matrix dimensions "+X1.rows+"x"+X1.cols+" and "+X2.rows+"x"+X2.cols+".");
		int i,j,rows = X1.rows, cols = X1.cols;
		Y.redimension(rows, cols, X1.transposed);
		double[][] yd=Y.data, x1d=X1.data, x2d=X2.data;
		if(!X1.transposed && !X2.transposed) {
			for(i=0;i<rows;i++) {
				for(j=0;j<cols;j++) {
					if(Double.compare(x1d[i][j], x2d[i][j]) != 0) 
						yd[i][j]=1.0; 
					else 
						yd[i][j]=0.0;
				}
			}
		} else if(X1.transposed && !X2.transposed) {
			for(i=0;i<rows;i++){
				for(j=0;j<cols;j++) { 
					if(Double.compare(x1d[j][i], x2d[i][j]) != 0) 
						yd[j][i]=1.0; 
					else 
						yd[j][i]=0.0;
				}
			}
		} else if(!X1.transposed && X2.transposed){
			for(i=0;i<rows;i++) {
				for(j=0;j<cols;j++) {
					if(Double.compare(x1d[i][j], x2d[j][i]) != 0) 
						yd[i][j]=1.0; 
					else 
						yd[i][j]=0.0;
				}
			}
		} else {// both tranposed
			for(i=0;i<rows;i++){
				for(j=0;j<cols;j++) {
					if(Double.compare(x1d[j][i], x2d[j][i]) != 0) 
						yd[j][i]=1.0; 
					else 
						yd[j][i]=0.0;
				} 
			}
		}
	}

	/** Generates a matrix of 1's and 0's, showing where the elements of X1 != d */
	public static final void notEquals(Matrix X, double d, Matrix Y) {
		Y.redimension(X.rows, X.cols, X.transposed);
		int rows, cols;
		if(X.transposed) {
			rows=X.cols; 
			cols=X.rows;
		} else {
			rows=X.rows; 
			cols=X.cols;
		}
		double[][] yd=Y.data, xd=X.data;
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++) {
				if(Double.compare(xd[i][j], d) != 0) 
					yd[i][j]=1.0;
				else 
					yd[i][j]=0.0;
			}
		}
	}

/*  MATRIX ANALYSIS */

	/** Condition number of a matrix, the ratio of the largest to smallest eigenvalues */
	public static final double cond(Matrix M)  throws MathException {
		Matrix S = createMatrix();
		Matrix V = createMatrix();
		Matrix U = createMatrix();
		int m = M.rows, n = M.cols;
		S.redimension(1,n,false);
		V.redimension(n,n,false);
		M.directIndexCopy(U);
		Algorithms.svdcmp(U.data,m,n,S.data[0],V.data);
		double small = select(S,0);
		double large = select(S,S.elements - 1);
		S.clear();
		V.clear();
		U.clear();
		return large/small;
	}

	/** Determinant of a square matrix */
	public static final double det(Matrix M) throws MathException {
		if (M.rows != M.cols)
			throw new MathException("det: nonsquare matrix, "+M.rows+" by "+M.cols);
		int n = M.rows;
		Matrix temp = createMatrix();
		M.directIndexCopy(temp);
		double[][] a = temp.data;
		int[] indx = new int[n];
		double d = Algorithms.ludcmp(a,n,indx);
		for (int i=0;i<n;i++){
			d*=a[i][i];
		}
		temp.clear();
		return d;
	}

	/** Norm of a matrix or vector.  When M is a matrix, the norm is the largest singular
	value.  For a vector, the norm is the 2-norm, the square root of the sum of squares */
	public static final double norm(Matrix M)  throws MathException {
		double norm;
		if(M.rows==1 || M.cols==1) {
			norm = Matlib.dotProduct(M,M);
			norm = Math.sqrt(norm);
		} else {
			Matrix S = createMatrix();
			svd(M,S);
			norm = S.get(0);
			S.clear();
		}
		return norm;
	}

	/** The p-norm of a matrix or vector, p > 0.  For finite p, when M is a vector, the p-norm is
	the sum of the absolute values of the elements raised to the p-th power, taken to the 
	1/p power.  When M is a matrix, the 1-norm is calculated, for p=1 or p=2.  For other finite
	values of p, the matrix norm is not defined.  
	If p = Matlib.INF, when M is a vector, the infinity norm, the maximum absolute value
	of X is calculated.   If M is a matrix, the largest row sum is calculated.  
	If p = Matlib.NEG_INF is the minimum absolute value of X, when X is a vector.  */
	public static final double norm(Matrix M, int p) throws MathException {
		double norm;
		if(M.rows==1 || M.cols==1) {
			if (p == Matlib.INF) {
				norm = 0.0;	
				for(int i=0; i<M.elements; ++i){
					if(Math.abs(M.get(i))>norm) {
						norm = Math.abs(M.get(i));
					}
				}
			} else if (p > 0) {
				norm = 0.0;	
				for(int i=0;i<M.elements;++i) {
					norm += Math.pow(Math.abs(M.get(i)), p);
				}
				norm = Math.pow(norm, 1.0/p);
			} else if (p == Matlib.NEG_INF) {
				norm = Matlib.INF;
	  			for(int i=0; i<M.elements; ++i){
	  				if(Math.abs(M.get(i))<norm){
	  					norm = Math.abs(M.get(i));
	  				}
	  			}
			} else throw new MathException("norm: only positive or infinite values of p allowed");
		} else {
			if (p==1 || p==2) {
				/* largest column sum of absolute values of elements */
				norm = 0.0;
				double colsum;
				for (int j=0;j<M.cols;j++) {
					colsum = 0.0;
					for (int i=0;i<M.rows;i++){
						colsum += Math.abs(M.get(i,j));
					}
					if (colsum > norm) {
						norm = colsum;
					}
				}
			} else if (p == Matlib.INF) {
				/* largest row sum of absolute values */
  				norm = 0.0;
				double rowsum;
				for (int i=0;i<M.rows;i++) {
					rowsum = 0.0;
					for (int j=0;j<M.cols;j++) {
						rowsum += Math.abs(M.get(i,j));
					}
					if (rowsum > norm) {
						norm = rowsum;
					}
				}
			} else throw new MathException("norm: matrix norm undefined for p = "+p);
		}
		return norm;
	}

	/** Nullspace (like Matlab's null) */
	public static final void nullspace(Matrix X, Matrix Y)  throws MathException {
		if(X==Y) {  // need temporary storage
			Matrix TY = createMatrix();
			nullspace(X, TY); 
			TY.destructiveCopy(Y);
			return;
		}
		Matrix W = createMatrix();
		Matrix V = createMatrix();
		Matrix U = createMatrix();
		svd(X, U, W, V, false);
		double eps = 2.2204e-16;  /* why this value ??? */
		double tol = 1.0e-10;  /* ??? */
		int nullCols[] = new int[X.cols];
		int nulls = 0;
		int len = Math.min(W.rows,W.cols);
		for(int i=0;i<len;i++) {
			if(W.get(i,i) < tol && W.get(i,i) > eps) { 
				nullCols[i]=1;
				nulls += 1;
			}
		}
		if (W.rows < W.cols && Double.compare(W.get(W.rows-1, W.cols-1), 0.0) == 0) {
			nullCols[X.cols-1]=1;
			nulls=1;
		}
		Y.redimension(X.cols,nulls);
		for(int i=0,c=0;i<X.cols;i++) {				    
			if(nullCols[i] == 1) {
				for(int r=0;r<V.rows;r++){
					Y.set(r,c,V.get(r,i));
				}
				c++;
			}	
		}
		U.clear();
		W.clear();
		V.clear();
	}

	public static final void orth() {}

  	public static final void rank() {}	

	public static final void trace() {}


/*  LINEAR EQUATIONS (also see divide) */

	public static final void chol() {}

	public static final void inv(Matrix X, Matrix Y) throws MathException {
		if(X.rows != X.cols) 
			throw new MathException("inv: non-square matrix");
		//always copy X, since luSolve destroys its first argument
		Matrix I = eye(X.rows);
		divide(X, I, Y);
		I.clear();
	}

	/** Least squares solution to overdetermined linear equations
	with standard deviations of each observation. Uses SVD method
	for robustness.  Returns the coefficients A. */
	public static final void leastsq(Matrix X, Matrix Y, Matrix Sig, Matrix A) throws MathException {
		if(A==X||A==Y||A==Sig) {
			Matrix TA = createMatrix();
			leastsq(X,Y,Sig,TA); 
			TA.destructiveCopy(A);
			return;
		}
		if(X.rows<=X.cols){
			throw new MathException("leastsq: system not overdetermined");
		}
		if(Sig.rows!=X.rows || Y.rows!=X.rows){
			throw new MathException("leastsq: X, Y, and Sig must have the same row dimension");
		}
		int i,j;
		double s;
		Matrix U = createMatrix();
		Matrix B = createMatrix();
		copy(X,U);
		copy(Y,B);
		double[][] u=U.data,b=B.data;
		if(!U.transposed) {
			for(i=0;i<U.rows;i++) {
				s = 1.0/Sig.get(i,0);
				for(j=0;j<U.cols;j++){
					u[i][j] = s*u[i][j];
				}
			}
		} else {
			for(i=0;i<U.rows;i++) {
				s = 1.0/Sig.get(i,0);
				for(j=0;j<U.cols;j++){
					u[j][i] = s*u[j][i];
				}
			}
		}
		if(!B.transposed) {
			for(i=0;i<B.rows;i++) {
				s = 1.0/Sig.get(i,0);
				for(j=0;j<B.cols;j++){
					b[i][j] = s*b[i][j];
				}
			}
		} else {
			for(i=0;i<B.rows;i++) {
				s = 1.0/Sig.get(i,0);
				for(j=0;j<B.cols;j++){
					b[j][i] = s*b[j][i];
				}
			}
		}
		divide(U,B,A);
		U.clear();
		B.clear();
	}

	public static final void lscov() {}

	/** Computes the LU decomposition of X, returning a permuted lower-
	triangular matrix L and an upper-triangular matrix U, such that X = L*U */
	public static final void lu(Matrix X, Matrix L, Matrix U) throws MathException {
		if(X.rows != X.cols)
			throw new MathException("lu: non-square matrix");
		int i, n = X.rows, dum;
		Matrix A = createMatrix();
		X.directIndexCopy(A);
		int[] indx = new int[n];
		Algorithms.ludcmp(A.data,n,indx);
		Matrix LL = Matrix.newMatrix(n,n,false);  // temp matrix to hold un-permuted L
		tril(A,-1,LL);
		double[][] lld = LL.data;
		for(i=0;i<n;i++){
			lld[i][i] = 1.0;
		}
		triu(A,U);
		int[] swaps = new int[n];
		for(i=0;i<n;i++){
			swaps[i] = i;
		}
		for(i=0;i<n;i++){ 
			if(indx[i] != i) {
				dum = swaps[i]; 
				swaps[i]=swaps[indx[i]]; 
				swaps[indx[i]]=dum;
			}
		}
		L.redimension(n,n,false);
		double[][] ld = L.data;
		for(i=0;i<n;i++) {
			//System.out.println("i = "+i+" indx="+indx[i]+" swaps="+swaps[i]);
			for(int j=0;j<n;j++){
				ld[swaps[i]][j] = lld[i][j];
			}
		}
		LL.clear();
		A.clear();
	} 

	/** Computes the LU decomposition of X and stores the result as a 
	lower-triangular matrix L, an upper-triangular matrix U, and a permutation
	matrix P, such that L*U = P*X */
	public static final void lu(Matrix X, Matrix L, Matrix U, Matrix P) throws MathException {
		if(X.rows != X.cols)
			throw new MathException("lu: non-square matrix");
		int i, n = X.rows;
		Matrix A = createMatrix();
		X.directIndexCopy(A);
		int[] indx = new int[n];
		Algorithms.ludcmp(A.data,n,indx);
		tril(A,-1,L);
		double[][] ld = L.data;
		for(i=0;i<n;i++){
			ld[i][i]=1.0;
		}
		triu(A,U);
		// now recover the row swaps from indx. 
		//indx = (1 3 2 3) means swap(0,1), swap(1,3), swap(2,2), swap(3,3).
		int[] swaps = new int[n];
		int dum;
		for(i=0;i<n;i++){
			swaps[i] = i;
		}
		for(i=0;i<n;i++){ 
			if(indx[i] != i) {
				dum = swaps[i]; 
				swaps[i]=swaps[indx[i]]; 
				swaps[indx[i]]=dum;
			}
		}
		// the result is now encoded in the matrix P
		P.redimension(n,n,false);
		P.initialize(Matrix.ZEROS);
		for(i=0;i<n;i++){
			P.data[i][swaps[i]]=1.0;
		}
		A.clear();
	} 

	/** Solves E*x = F in a least-squares sense, where elements of x > 0 **/
/*	public static final void nnls(Matrix E, Matrix f, Matrix x) {
		double eps = 2.2204e-016;
		int m = X.getRows();
		int n = X.getCols();
		double tol = 10.0*eps*norm(E,1)*Math.max(m,n);
		Matrix P = zeros(1,n);
		Matrix Z = colon(1,n,1);
		transpose(P,x);
		Matrix ZZ = createMatrix();
		copy(Z,ZZ);
		Matrix w = createMatrix();
		Matrix temp = createMatrix();
		Matrix temp2 = createMatrix();
		multiply(E,x,temp);
		subtract(f,temp, temp);
		transpose(E,temp2);
		multiply(temp2,temp,w);
		int iter = 0;
		int itmax = 3*n;
		for(;;) {
		YIKES!
		clear(temp);
		clear(temp2);
		clear(w);
		clear(ZZ);
		clear(P);
		clear(Z);
	}	

*/

	public static final void pinv() {}

	public static final void qr() {}

	/** Equivalent to the slash operator in Matlab.  X1/X2 is roughly
	equivalent to X1*inv(X2).  More precisely X1/X2 = (X1'\X2')'. */
	public static final void rightDivide(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		Matrix TX1 = createMatrix();
		Matrix TX2 = createMatrix();
		transpose(X1,TX1);
		transpose(X2,TX2);
		divide(TX2,TX1,Y);
		transpose(Y,Y);
		TX1.clear();
		TX2.clear();
	}

/* EIGENVALUES AND SINGULAR VALUES */

	public static final void svd(Matrix X, Matrix U, Matrix S, Matrix V) throws MathException {
		svd(X,U,S,V,true);
	}

	public static final void svd(Matrix X, Matrix U, Matrix S, Matrix V, boolean fullU) throws MathException {
		if(U!=X){
			X.directIndexCopy(U);
		}
		else X.forceDirectIndexing();
		int m = X.rows, n = X.cols;
		S.redimension(1,n,false);
		V.redimension(n,n,false);
		Algorithms.svdcmp(U.data,m,n,S.data[0],V.data);
		Matrix I = createMatrix();
		unaryMinus(S,S);
		sort(S,S,I);
		unaryMinus(S,S);
		permuteColumns(U,I,U);
		permuteRows(V,I,V);
		Matlib.clear(I);
		diag(S,S);
		if (fullU && m>n) {
			// fill up the last m-n columns of U with orthonormal vectors
			// Gang Chen's algorithm
			int i,j,k;
			Matrix Z = rand(m,m-n);
			appendColumns(U,Z,U);
			Z.forceDirectIndexing();
			U.forceDirectIndexing();
			double[][] u = U.data, z = Z.data;
			double nz, nu, nzu;  // norms
			for(i=n;i<m;i++){ 
				for (j=0;j<i;j++) {
					nz=0;
					nu=0;
					for(k=0;k<m;k++) {
						nz += z[k][i-n]*u[k][j];
						nu += u[k][j]*u[k][j];
					}
					nzu = nz/nu;
					for(k=0;k<m;k++){
						u[k][i] -= nzu*u[k][j];
					}
				}
			}
			// now normalize the new columns to length 1
			for(i=n;i<m;i++) {
				nu = 0;
				for(k=0;k<m;k++){
					nu += u[k][i]*u[k][i];
				}
				nu = Math.sqrt(nu);
				for(k=0;k<m;k++){
					u[k][i] /= nu;
				}
			}
		}
	}

	/** Returns singular values in a vector, in descending order */
	public static final void svd(Matrix X, Matrix S) throws MathException {
		Matrix U = createMatrix();
		Matrix V = createMatrix();
		svd(X,U,S,V,false);
		U.clear();
		V.clear();
		unaryMinus(S,S);
		sort(S,S);
		unaryMinus(S,S);
	}

/* BASIC DATA ANALYSIS */

	public static final void cumprod(Matrix X, Matrix Y) {
		double prod = 1.0;
		Y.redimension(X.rows, X.cols);
		if(X.rows==1 || X.cols==1) {
			for(int i=0;i<X.elements;i++) {
				prod *= X.get(i);
				Y.set(i,prod);
			}
		} else {
			for(int j=0;j<X.cols;j++) {
				prod = 1.0;
				for(int i=0;i<X.rows;i++) {
					prod *= X.get(i,j);
					Y.set(i,j,prod);
				}
			}
		}
	}

	public static final void cumsum(Matrix X, Matrix Y) {
		double sum = 0.0;
		Y.redimension(X.rows, X.cols);
		if(X.rows==1 || X.cols==1) {
			for(int i=0;i<X.elements;i++) {
				sum += X.get(i);
				Y.set(i,sum);
			}
		} else {
			for(int j=0;j<X.cols;j++) {
				sum = 0.0;
				for(int i=0;i<X.rows;i++) {
					sum += X.get(i,j);
					Y.set(i,j,sum);
				}
			}
		}
	}

	/** For vectors, max(X) is the largest element in X. 
	For matrices, max(X) is a vector containing the maximum element
  	from each column.  */
	public static final void max(Matrix X, Matrix Y) {
		Matrix I = createMatrix();
		max(X,Y,I);
		I.clear();
	}

	/** max(X, Y, I) stores the indices of the maximum values in the
	output I. If X is a vector, Y contains the largest element.  
	If X is a matrix, Y contains the maximum element from each column. */
	public static final void max(Matrix X, Matrix Y, Matrix I) {
		if(X==Y) {  // need temporary storage
			Matrix TY = createMatrix();
			max(X, TY, I); 
			TY.destructiveCopy(Y);
			return;
		} else if(X==I) {
			Matrix TI = createMatrix();
			max(X,Y,TI);
			TI.destructiveCopy(I);
			return;
		}
		if(X.rows==1 || X.cols==1) {
			double maxval = X.get(0);
			double index = 0;
			for(int i=1;i<X.elements;i++){ 
				if(X.get(i)>maxval) {
					maxval = X.get(i);
					index = i;
				}
			}
			Y.redimension(1,1);
			Y.set(0,maxval);
			I.redimension(1,1);
			I.set(0,index);
		} else {
			Y.redimension(1, X.cols);
			I.redimension(1, X.cols);
			double maxval, index;
			for(int j=0;j<X.cols;j++) {
				 maxval = X.get(0,j);
				 index = 0;
				 for(int i=1;i<X.rows;i++){ 
					 if(X.get(i,j)>maxval) {
						 maxval = X.get(i,j);
						 index = i;
					 }
				 }
				 Y.set(j,maxval);
				 I.set(j,index);
			}
		}
	}


	/** maxSelect(X1,X2,Y) returns a matrix containing the largest elements
	selected from X1 or X2. */
	public static final void maxSelect(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		if (X1.rows != X2.rows || X1.cols != X2.cols)
			throw new MathException("max: bad matrix dimensions "+X1.rows+"x"+X1.cols+" and "+X2.rows+"x"+X2.cols+".");
		Y.redimension(X1.rows, X1.cols);
		for (int i=0;i<X1.rows; i++){ 
			for(int j=0;j<X1.cols; j++) {
				if (X2.get(i,j) > X1.get(i,j)){
					Y.set(i,j, X2.get(i));
				}else{
					Y.set(i,j,X1.get(i,j));
				}
			}
		}
	}

	public static final void maxSelect(Matrix X, double d, Matrix Y) throws MathException {
		Y.redimension(X.rows, X.cols);
		for (int i=0;i<X.elements; i++) {
			if(d>X.get(i)){
				Y.set(i,d);
			}
			else{
				Y.set(i,X.get(i));
			}
		}
	}

	public static final void mean(Matrix X, Matrix Y) {
		int n;
		if (X.rows==1 || X.cols==1){
			n = X.elements;
		}
		else{
			n = X.rows;
		}
		sum(X,Y);
		divide(Y,n,Y);
	}

	/** Finds the median element.  If X is a matrix, the median of 
	each column is returned in a vector. (NRIC 341) */
   	public static final void median(Matrix X, Matrix Y) throws MathException {
		if(X==Y) {  // need temporary storage
			Matrix TY = createMatrix();
			median(X, TY); 
			TY.destructiveCopy(Y);
			return;
		}
		if(X.rows==1 || X.cols==1) {
			double med;
			// added 2.1:  Ignore NaN elements in calculating median
			boolean hasNaN = false;
			Matrix TR;
			if(Matlib.hasNaN(X)) {
				hasNaN = true;
				TR = Matlib.createMatrix();
				Matrix S = Matlib.createMatrix();
				Matlib.findNaN(X,S);
				Matlib.not(S,S);
				if(X.cols==1){
					Matlib.getRows(X,S,TR);
				}
				else Matlib.getColumns(X,S,TR);
				Matlib.clear(S);
			} else TR = X;
			int n = TR.elements;
			if(n==0){
				med = Double.NaN;
			} else if(n==1){
				med = TR.get(0);
			} else if(n==2){
				med = 0.5*(TR.get(0) + TR.get(1));
			} else {
				if ((n&1)==1){
					med = select(TR,(n + 1)/2 - 1);  
				} else if (n <= 100){
					med = 0.5*(select(TR,n/2 - 1) + select(TR,n/2));
				}else{
					med = select(TR, n/2 - 1);
				}
			}
			Y.redimension(1,1);
			Y.set(0,med);
			if(hasNaN){
				Matlib.clear(TR);
			}
		} else {
			double med;
			Y.redimension(1,X.cols);
			Matrix TR = createMatrix();
			Matrix S = Matlib.createMatrix();
			for(int j=0;j<X.cols;j++) {
				getColumn(X,j,TR);
				if(Matlib.hasNaN(TR)) {
					Matlib.findNaN(TR,S);
					Matlib.not(S,S);
					Matlib.getRows(TR,S,TR);
				}
				int n = TR.rows;
				if(n==0){
					med = Double.NaN;
				} else if(n==1){
					med = TR.get(0);
				} else if(n==2){
					med = 0.5*(TR.get(0) + TR.get(1));
				} else {
					if ((n&1)==1){
						med = select(TR,(n + 1)/2 - 1);
					} else if (n <= 100){
						med = 0.5*(select(TR,n/2 - 1) + select(TR,n/2));
					} else{
						med = select(TR, n/2 - 1);
					}
				}
				Y.set(j,med);
			}
			TR.clear();
			S.clear();
		}
	} 

	/** For vectors, min(X) is the largest element in X. 
	For matrices, min(X) is a vector containing the minimum element
  	from each column.  */
	public static final void min(Matrix X, Matrix Y) {
		Matrix I = createMatrix();
		min(X,Y,I);
		I.clear();
	}

	/** min(X, Y, I) stores the indices of the minimum values in the
	output I. If X is a vector, Y contains the largest element.  
	If X is a matrix, Y contains the minimum element from each column. */
	public static final void min(Matrix X, Matrix Y, Matrix I) {
		if(X==Y) {  // need temporary storage
			Matrix TY = createMatrix();
			min(X, TY, I); 
			TY.destructiveCopy(Y);
			return;
		} else if(X==I) {
			Matrix TI = createMatrix();
			min(X,Y,TI);
			TI.destructiveCopy(I);
			return;
		}
		if(X.rows==1 || X.cols==1) {
			double minval = X.get(0);
			double index = 0;
			for(int i=1;i<X.elements;i++) { 
				if(X.get(i)<minval) {
					minval = X.get(i);
					index = i;
				}
			}
			Y.redimension(1,1);
			Y.set(0,minval);
			I.redimension(1,1);
			I.set(0,index);
		} else {
			Y.redimension(1, X.cols);
			I.redimension(1, X.cols);
			double minval, index;
			for(int j=0;j<X.cols;j++) {
				 minval = X.get(0,j);
				 index = 0;
				 for(int i=1;i<X.rows;i++){ 
					 if(X.get(i,j)<minval) {
						 minval = X.get(i,j);
						 index = i;
					 }
				 }
				 Y.set(j,minval);
				 I.set(j,index);
			}
		}
	}

	/** minSelect(X1,X2,Y) returns a matrix containing the largest elements
	selected from X1 or X2. */
	public static final void minSelect(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		if (X1.rows != X2.rows || X1.cols != X2.cols)
			throw new MathException("min: bad matrix dimensions "+X1.rows+"x"+X1.cols+" and "+X2.rows+"x"+X2.cols+".");
		Y.redimension(X1.rows, X1.cols);
		for (int i=0;i<X1.elements; i++) {
			if (X2.get(i) < X1.get(i)){
				Y.set(i, X2.get(i));
			}else {
				Y.set(i, X1.get(i));
			}
		}
	}

	/** minSelect(X,d,Y) returns a matrix in which the elements of X that are less
	than d are replaced by d */
	public static final void minSelect(Matrix X, double d, Matrix Y) throws MathException {
		Y.redimension(X.rows, X.cols);
		for (int i=0;i<X.elements; i++) {
			if(d<X.get(i)){
				Y.set(i,d);
			} else {
				Y.set(i,X.get(i));
			}
		}
	}

	/** Scale a matrix with the given mean and std vectors, calculated
	from mean and std.  If any column is constant (std==0.0), it is left unchanged.
	See unnormalize.  Xstd must not contain zero elements. */
	public static final void normalize(Matrix X, Matrix Xmean, Matrix Xstd, Matrix Y) throws MathException {
		subtract(X,Xmean,Y);
		Matrix temp = Matlib.createMatrix();
		copy(Xstd,temp);
		for(int i=0;i<temp.getElements();i++) {
			if(Double.compare(temp.get(i), 0.0) == 0) 
				temp.set(i,1.0);
		}
		divideElements(Y,temp,Y);
		Matlib.clear(temp);
	}


	public static final void permuteColumns(Matrix X, Matrix P, Matrix Y) {
		if(X==Y) {
			Matrix TY = createMatrix();
			permuteColumns(X, P, TY); 
			TY.destructiveCopy(Y);
			return;
		}
		Y.redimension(X.rows,X.cols,X.transposed);
		double[][] yd = Y.data, xd = X.data;
		int pj;
		if(Y.transposed) {
			for(int j=0;j<X.cols;j++) {
				pj = (int) P.get(j);
				for(int i=0;i<X.rows;i++){
					yd[pj][i] = xd[j][i];
				}
			}

		} else {
			for(int j=0;j<X.cols;j++) {
				pj = (int) P.get(j);
				for(int i=0;i<X.rows;i++){
					yd[i][pj] = xd[i][j];
				}
			}
		}
	}

	public static final void permuteRows(Matrix X, Matrix P, Matrix Y) {
	 	if(X==Y) {
			Matrix TY = createMatrix();
			permuteRows(X, P, TY); 
			TY.destructiveCopy(Y);
			return;
		}
		Y.redimension(X.rows,X.cols,X.transposed);
		double[][] yd = Y.data, xd = X.data;
		int pj;
		if(!Y.transposed) { // only need to swap arrays
			for(int j=0;j<X.rows;j++) {
				pj = (int) P.get(j);
				for(int i=0;i<X.cols;i++){
					yd[pj][i] = xd[j][i];
				}
			}
		} else { // must swap element-by-element
			for(int j=0;j<X.rows;j++) {
				pj = (int) P.get(j);
				for(int i=0;i<X.cols;i++){
					yd[i][pj] = xd[i][j];
				}
			}
		}
	}

	/** Product of the elements.  For a matrix, returns the products of the columns.*/
   	public static final void prod(Matrix X, Matrix Y) {
		if(X==Y) {  // need temporary storage
			Matrix TY = createMatrix();
			prod(X, TY); 
			TY.destructiveCopy(Y);
			return;
		}
		if(X.rows==1 || X.cols==1) {
			double prod = 1.0;
			for(int i=0;i<X.elements;i++){
				prod *= X.get(i);
			}
			Y.redimension(1,1);
			Y.set(0,prod);
		} else {
			Y.redimension(1,X.cols);
			double prod;
			for(int j=0;j<X.cols;j++) {
				prod = 1.0;
				for(int i=0;i<X.rows;i++){
					prod *= X.get(i,j);
				}
				Y.set(j,prod);
			}
		}
	}

	/** Select the k-th largest element of X, where X is a vector */
	public static final double select(Matrix X, int k) {
		Matrix temp = createMatrix();
		if(X.rows==1){
			X.directIndexCopy(temp);
		}
		else { // column vector
			X.copy(temp);
			transpose(temp,temp); // convert to row vector
			temp.forceDirectIndexing();
		}
		int n = temp.elements;
		double[] arr = temp.data[0];
		int i,ir,j,l,mid;
		double a;
		l=0;
		ir=n-1;
		for (;;) {
			if (ir <= l+1) {
				if (ir == l+1 && arr[ir] < arr[l]){
					SWAP(arr,l,ir);
				}
				a = arr[k];
				temp.clear();
				//System.out.println("element "+k+" is "+a);
				return a;
			} else {
				mid=((l+ir+2) >> 1) - 1;  // replaces (l+ir)>>1
				SWAP(arr,mid,l+1);
				if (arr[l+1] > arr[ir]){
					SWAP(arr,l+1,ir);
				}
				if (arr[l] > arr[ir]){
					SWAP(arr,l,ir);
				}
				if (arr[l+1] > arr[l]){
					SWAP(arr,l+1,l);
				}
				i=l+1;
				j=ir;
				a=arr[l];
				for (;;) {
					do {
						i++; 
					}while (arr[i] < a);
					do{ 
						j--; 
					}while (arr[j] > a);
					if (j < i){
						break;
					}
					SWAP(arr,i,j);
				}
				arr[l]=arr[j];
				arr[j]=a;
				if (j >= k){
					ir=j-1;
				}
				if (j <= k){
					l=i;
				}
			}
		}
	}

	private static final void SWAP(double[] a, int i, int j) {
		double temp = a[i];	
		a[i]=a[j]; 
		a[j]=temp;
	}

	/** Sort the columns of X into ascending order, putting the result into Y */
   	public static final void sort(Matrix X, Matrix Y) {
		boolean transposed = false;
		if(X!=Y){
			X.copy(Y);
		}
		if(Y.rows>1) { // force the columns to appear as arrays in the internal representation
			transposed=true; 
			transpose(Y,Y); 
		} 
		Y.forceDirectIndexing();
		for(int j=0;j<Y.rows;j++) {
			Algorithms.hpsort(Y.data[j], Y.cols);
		}
		if(transposed){
			transpose(Y,Y);
		}
	}

	/** Sorts X into ascending order sorts matrix I using the same
	permutations.  Matrix I is returned as a permutation
	of colon(0:X.rows-1) */
	public static final void sort(Matrix X, Matrix Y, Matrix I) {
		boolean transposed = false;
		int i,j;
		if(X!=Y){
			X.copy(Y);
		}
		if(Y.rows>1) { // force the columns to appear as arrays in the internal representation
			transposed=true; 
			transpose(Y,Y); 
		}
		Y.forceDirectIndexing();
		I.redimension(Y.rows,Y.cols,false);
		double id[][]=I.data;
		for(i=0;i<I.rows;i++){
			for (j=0;j<I.cols;j++){
				id[i][j] = j;
			}
		}
		for(j=0;j<Y.rows;j++){
			Algorithms.hpsort(Y.data[j], Y.cols, I.data[j]);
		}
		if(transposed) {
			transpose(Y,Y);	
			transpose(I,I);
		}
	}

	/** Sorts the rows or columns of auxiliary matrix X2 according to the permutations of 
	vector X1, which is sorted into ascending order. If X1 is a column vector, the rows of X2
	are permuted. If X1 is a row vector, the columns of X2 are permuted.  If X1 and X2 are matices
	of the same size, the columns of X2 are permuted according to the sorting order of X1. */
	public static final void sort(Matrix X1, Matrix X2, Matrix Y1, Matrix Y2) throws MathException {
		if(X1.rows!=1 && X1.cols!=1 && X1.rows == X2.rows && X1.cols == X2.cols) {
			boolean transposed = false;
			int i,j;
			if(X1!=Y1){
				X1.copy(Y1);
			}
			if(Y1.rows>1) { // force the columns to appear as arrays in the internal representation
				transposed=true; 
				transpose(Y1,Y1); 
			}
			Y1.forceDirectIndexing();
			if(X2!=Y2){
				X2.copy(Y2);
			}
			if(transposed){
				transpose(Y2,Y2); 
			}
			Y2.forceDirectIndexing();
			for(j=0;j<Y1.rows;j++){
				Algorithms.hpsort(Y1.data[j], Y1.cols, Y2.data[j]);
			}
			if(transposed) {
				transpose(Y1,Y1); 
				transpose(Y2,Y2);
			}
			return;
		}
		else if(X1.rows != X2.rows && X1.cols != X2.cols)
			throw new MathException("sort (4 args): vector dimension must match row or column dimension of matrix");
		boolean transposed1 = false, transposed2 = false;
		int i,j;
		if(X1!=Y1){
			X1.copy(Y1);
		}
		if(X2!=Y2){
			X2.copy(Y2);
		}
		if(Y1.rows>1) { // force the columns to appear as arrays in the internal representation
			transposed1=true; 
			transpose(Y1,Y1);
		} else {
			transposed2=true;
			transpose(Y2,Y2);
		}
		Y1.forceDirectIndexing();
		Y2.forceDirectIndexing();
		Algorithms.hpsort(Y1.data[0], Y1.cols, Y2.data);
		if(transposed1){
			transpose(Y1,Y1);
		}
		if(transposed2){
			transpose(Y2,Y2);
		}
	}

	/** Standard devation.  For a matrix, this method returns the standard
	deviations of the columns.  This method normalizes by the sample size - 1 */
	public static final void std(Matrix X, Matrix Y) throws MathException {
		var(X,Y);
		sqrt(Y,Y);
	}

	/** Non-zero standard devation, for use with normalize/unnormalize.
	Replaces any zero elements with 1.0 */
	public static final void stdnonzero(Matrix X, Matrix Y) throws MathException {
		std(X,Y);
		for(int i=0;i<Y.getCols();i++) {
			if(Double.compare(Y.get(0,i), 0.0) == 0) {
				Y.set(0,i,1.0);
			}
		}
	}

	/** Sum of the elements.  For a matrix, returns the sums of the columns.*/
   	public static final void sum(Matrix X, Matrix Y) {
		if(X==Y) {  // need temporary storage
			Matrix TY = createMatrix();
			sum(X, TY); 
			TY.destructiveCopy(Y);
			return;
		}
		if(X.rows==1 || X.cols==1) {
			double sum = 0.0;
			for(int i=0;i<X.elements;i++){
				sum += X.get(i);
			}
			Y.redimension(1,1);
			Y.set(0,sum);
		} else {
			Y.redimension(1,X.cols);
			double sum;
			for(int j=0;j<X.cols;j++) {
				sum = 0.0;
				for(int i=0;i<X.rows;i++){
					sum += X.get(i,j);
				}
				Y.set(j,sum);
			}
		}
	}

	/** Reverses the effect of normalize */
	public static final void unnormalize(Matrix X, Matrix Xmean, Matrix Xstd, Matrix Y) throws MathException {
		multiplyElements(X,Xstd,Y);
		add(Y,Xmean,Y);
	}

	/*	CORRELATION */

	/** Returns the correlation coefficients in a matrix where element i,j is
	the correlation coefficient between column i and column j of X */
	public static final void corrcoef(Matrix X, Matrix Y) throws MathException {
		if(X==Y) {  // need temporary storage
			Matrix TY = createMatrix();
			corrcoef(X, TY); 
			TY.destructiveCopy(Y);
			return;
		}
		cov(X,Y);
		for(int i=0;i<Y.rows;i++){ 
			for(int j=0;j<Y.cols;j++) {
				if(i!=j) {
					Y.set(i,j,Y.get(i,j)/Math.sqrt(Y.get(i,i)*Y.get(j,j)));
				}
			}
		}
		for(int i=0;i<Y.rows;i++){
			Y.set(i,i,1.0);
		}
	}

	/** Correlation coefficient between the columns of two matrices X1 and X2.
	A row vector is returned, where element i is the correlation coefficient
	between column i of X1 and column i of X2 */
	public static final void corrcoef(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		if(X1.rows!=X2.rows || X1.cols!=X2.cols) 
			throw new MathException("Corrcoef: Input matrices must have the same dimensions");
		if(X1==Y || X2==Y) {  // need temporary storage
			Matrix TY = createMatrix();
			corrcoef(X1,X2,TY); 
			TY.destructiveCopy(Y);
			return;
		}
		Matrix x1 = createMatrix();
		Matrix x2 = createMatrix();
		Matrix TX = createMatrix();
		Matrix Corr = createMatrix();
		Y.redimension(1,X1.cols);
		for(int i=0;i<X1.cols;i++) {
			getColumns(X1,i,i,x1);
			getColumns(X2,i,i,x2);
			appendColumns(x1,x2,TX);
			corrcoef(TX,Corr);
			Y.set(0,i,Corr.get(0,1));
		}
		x1.clear();
		x2.clear();
		TX.clear();
		Corr.clear();
	}

	/** Covariance.  If X is a vector, this returns the variance.  For a 
	matrix, it is assumed that each row is an observation and each column is a
	variable. */
	public static final void cov(Matrix X, Matrix Y) throws MathException {
		if (X.rows==1 || X.cols==1){
			var(X,Y);
		}
		else {
			Matrix M = createMatrix();
			Matrix D = createMatrix();
			mean(X,M); 
			subtract(X,M,D); // note: matrix - vector is defined in subtract
			xTx(D,M);  // M = transpose(D)*D
			divide(M,((double)X.rows)-1,M);
			M.destructiveCopy(Y);
			D.clear();
		}
	}

	/** Calculates X'X (transpose(X)*X). Result is a symmetric matrix Y. */
	public static final void xTx(Matrix X, Matrix Y) {
		if(X==Y) {  //create temporary storage
			Matrix TY = createMatrix();
			xTx(X,TY); 
			TY.destructiveCopy(Y);
			return;
		}
		double sum;
		int row,col,id,rows=X.cols,cols=X.cols,ids=X.rows;
		Y.redimension(cols,cols);
		double[][] d = X.data;
		if(!X.transposed) {
			for(row=0;row<rows;row++) {
				for(col=0;col<=row;col++) {
					sum = 0.0;
					for(id=0; id<ids;id++){
						sum += d[id][row]*d[id][col];
					}
					Y.set(row,col,sum);
				}
			}
		}
		else { // X is transposed
			for(row=0;row<rows;row++) {
				for(col=0;col<=row;col++) {
					sum = 0.0;
					for(id=0; id<ids;id++){
						sum += d[row][id]*d[col][id];
					}
					Y.set(row,col,sum);
				}
			}
		}
		// fill up upper triangle via symmetry
		for(row=0;row<rows-1;row++) {
			for(col=row+1;col<cols;col++) {
				Y.set(row,col,Y.get(col,row));
			}
		}
	}


	/** Finds the autocorrelation sequence for a vector X, defined as the expected
	value E[x(i)*x(i+n)], where n=minN,increment+minN,2*increment+minN, n<maxN */
	public static final void autocorr(Matrix X, int minN, int increment, int maxN, Matrix Y) throws MathException {
		if(X.rows!=1 && X.cols!=1){
			throw new MathException("autocorr only works with vectors");
		}
		if(X==Y) {  // need temporary storage
			Matrix TY = createMatrix();
			autocorr(X,minN,increment,maxN,TY); 
			TY.destructiveCopy(Y);
			return;
		}
		if(X.rows==1) {   // transpose to column vector
			Matrix TX = Matlib.createMatrix();
			transpose(X,TX);
			autocorr(TX,minN,increment,maxN,Y);
			TX.clear();
			return;
		}
		int nrows = X.rows;
		Matrix M = createMatrix();
		mean(X,M);
		subtract(X,M,M);
		transpose(M,M);
		M.forceDirectIndexing();  // after transpose, M is a row vector, so this is safe
		double[] m = (M.data)[0];
		int i=0,n;
		for(n=minN;n<=maxN;n+=increment){
			i++;  // cheesy way to calculate how many coefficients will be returned
		}
		Y.redimension(1,i);
		double sum,corr0 = 0.0;
		// calculate the covariance of the series with itself
		for(i=0;i<nrows;i++){
			corr0 += m[i]*m[i];
		}
		corr0 /= (nrows-1);
		for(i=0,n=minN;n<=maxN;n+=increment,i++) {
			sum = 0.0;
			for(i=0;i<nrows-n;i++){
				sum+=m[i]*m[i+n];
			}
			sum /= nrows-n-1;
			Y.set(0,i,sum/corr0);
		}
		M.clear();
	}

	/** Same as cov([X1 X2]) */
	public static final void cov(Matrix X1, Matrix X2, Matrix Y) throws MathException {
		appendColumns(X1,X2,Y);
		cov(Y,Y);
	}

	public static final void var(Matrix X, Matrix Y) throws MathException {
		if(X==Y) {  // need temporary storage
			Matrix TY = createMatrix();
			var(X, TY); 
			TY.destructiveCopy(Y);
			return;
		}
		if(X.elements == 1) {
			Y.redimension(1,1);
			Y.set(0,0.0);
			return;
		}
		Matrix M = createMatrix();
		mean(X,M);
		double dev, ssq, meanval;
		if(X.rows==1 || X.cols ==1) {
			ssq = 0.0;
			meanval = M.get(0);
			for(int i=0;i<X.elements;i++) {
				dev = X.get(i) - meanval;
				ssq += dev*dev;
			}
			Y.redimension(1,1);
			Y.set(0,ssq/(X.elements - 1));
		} else {
			Y.redimension(1,X.cols);
			for(int j=0;j<X.cols;j++) {
				ssq = 0.0;
				meanval = M.get(j);
				for(int i=0;i<X.rows;i++) {
					dev = X.get(i,j) - meanval;
					ssq += dev*dev;
				}
				Y.set(j,ssq/(X.rows - 1));
			}
		}
		M.clear();	
	}

/* SPECIAL MATRICES -- USEFUL FOR TESTING */

	public static final Matrix gallery(int n) {
		Matrix A = createMatrix();
		if (n==3) {
			A.redimension(3,3);
			A.set(0,0,-149.0);
			A.set(0,1,-50.0);
			A.set(0,2,-154.0);
			A.set(1,0,537.0);
			A.set(1,1,180.0);
			A.set(1,2,546.0);
			A.set(2,0,-27.0);
			A.set(2,1,-9.0);
			A.set(2,2,-25.0);
		} else if (n==5) {
			A.redimension(5,5);
			A.set(0,0,-9);
			A.set(0,1,11);
			A.set(0,2,-21);
			A.set(0,3,63);
			A.set(0,4,-252);
			A.set(1,0,70);
			A.set(1,1,-69);
			A.set(1,2,141);
			A.set(1,3,-421);
			A.set(1,4,1684);
			A.set(2,0,-575);
			A.set(2,1,575);
			A.set(2,2,-1149);
			A.set(2,3,3451);
			A.set(2,4,-13801);
			A.set(3,0,3891);
			A.set(3,1,-3891);
			A.set(3,2,7782);
			A.set(3,3,-23345);
			A.set(3,4,93365);
			A.set(4,0,1024);
			A.set(4,1,-1024);
			A.set(4,2,2048);
			A.set(4,3,-6144);
			A.set(4,4,24572);
		}
		return A;
	}

	public static final Matrix hilb(int n) {
		int i,j;
		Matrix H = zeros(n);
		H.forceDirectIndexing();
		double[][] h = H.data;
		for(i=1;i<=n;i++) {
			for(j=1;j<=n;j++){
				h[i-1][j-1]=1.0/(i+j-1);
			}
		}
		return H;
	}

	public static final Matrix invhilb(int n) {
		int i,j,r,p = n;
		Matrix H = zeros(n);
		H.forceDirectIndexing();
		double[][] h = H.data;
		for(i=1;i<=n;i++) {
			if (i>1){
				p = ((n-i+1)*p*(n+i-1))/((i-1)*(i-1));
			}
			r = p*p;
			h[i-1][i-1] = ((double)r)/(2*i-1);
			for(j=i+1;j<=n;j++) {
				r = -((n-j+1)*r*(n+j-1))/((j-1)*(j-1));
				h[i-1][j-1] = h[j-1][i-1] = ((double)r)/(i+j-1);
			}
		}
		return H;
	}

	public static final Matrix pascal(int n) throws MathException {
		Matrix P = pascal(n,0);
		return P;
	}

	public static final Matrix pascal(int n, int k) throws MathException {
		if(k<0 || k>2){
			throw new MathException("pascal: k must be 0, 1, or 2");
		}
		Matrix P = eye(n);
		P.forceDirectIndexing();
		int i,j;
		double[][] p = P.data;
		double neg = 1.0;
		for(i=0; i<n; i++) {
			p[i][i] = neg*p[i][i];
			neg = -neg;
			p[i][0] = 1.0;
		}
		for(j=1;j<n-1;j++){ 
			for (i=j+1;i<n;i++) {
				p[i][j] = p[i-1][j] - p[i-1][j-1];
			}
		}
		if(k==0) {
			Matrix PT = createMatrix();
			transpose(P,PT);
			multiply(P,PT,P);
			clear(PT);
		} else if (k==2) {
			transpose(P,P);
			flipud(P,P);
			P.forceDirectIndexing();
			p = P.data;
			for(i=0;i<n-1;i++) {
				for(j=0;j<n;j++){
					p[i][j] = -p[i][j];
				}
				for(j=0;j<n;j++){
					p[j][i] = -p[j][i]; 
				}
			}
			if((n&1)==0){
				unaryMinus(P,P);
			}
		}
		return P;
	}

	public static final Matrix rosser() throws MathException {
		double[] r = {611., 196., -192., 407.,-8.,-52.,-49., 29.,
			196.,899.,113., -192.,-71.,-43., -8.,-44.,
			-192.,113.,899.,196., 61., 49.,  8., 52.,
			407.,-192.,196.,611.,8., 44., 59.,-23.,
			-8.,-71., 61.,8.,411., -599.,208.,208.,
			-52.,-43., 49., 44., -599.,411.,208.,208.,
			-49., -8.,  8., 59.,208.,208., 99., -911.,
			29.,-44., 52.,-23.,208.,208., -911., 99.};
		Matrix R = createMatrix(r);
		reshape(R,8,8,R);
		transpose(R,R);
		return R;
	}

	/** wilkinson(n) is J a symmetric, tridiagonal matrix with 
	pairs of nearly equal eigenvalues.,The most frequently used 
	case is n = 21 */
	public static final Matrix wilkinson(int n) {
		int m = -(n - 1)/2;
		Matrix W = zeros(n,n);
		for(int i=0;i<n;i++) {
			W.set(i,i,Math.abs(m));
			m++;
			if(i!=0) {
				W.set(i,i-1,1.0);
				W.set(i-1,i,1.0);
			}
		}
		return W;
	}

	/*  UNROLLED VERSION OF DOT PRODUCT.  DOESN'T SEEM TO SAVE ANY TIME FOR
INTERPRETED CODE (2% OR LESS). THIS RESULT WAS VERIFIED USING INTERPRETED
AND JIT COMPILER.
	public static double dotProduct2(Matrix X1, Matrix X2) throws MathException {
		double sum = 0.0;
		if (X1.elements != X2.elements) 
			throw new MathException("dotProduct: incommensurate lengths "+X1.elements+", "+X2.elements);	
		int n = X1.elements;
		int m = (n&3);
		for(int i=0;i<m;i++) sum += X1.get(i)*X2.get(i);
		for(int i=m;i<n;i+=4) sum += X1.get(i)*X2.get(i) + X1.get(i+1)*X2.get(i+1)
			+ X1.get(i+2)*X2.get(i+2) + X1.get(i+3)*X2.get(i+3);
//System.out.println("fastresult = "+sum);
		return sum;
	} 		 */


	/** Finds the columns of X containing no finite values, returning a row
	vector of 0's and 1's -- 1's representing columns that are entirely NaN. */
	public static final void findAllNaNColumns(Matrix X, Matrix Y) {
		Y.redimension(1, X.cols);
		int rows, cols;
		double d;
		double[][] xd=X.data;
		boolean allNaN;
		if(!X.transposed) {
			for(int j=0;j<X.cols;j++) {
				allNaN = true;
				for(int i=0;i<X.rows;i++) {
					d = xd[i][j];
					if(!Double.isNaN(d) && !Double.isInfinite(d)) {
						allNaN = false;
						break;
					}
				}
				if(allNaN){
					Y.set(j,1.0);
				}
				else{
					Y.set(j,0.0);
				}
			}
		} else {
			for(int j=0;j<X.cols;j++) {
				allNaN = true;
				for(int i=0;i<X.rows;i++) {
					d = xd[j][i];
					if(!Double.isNaN(d) && !Double.isInfinite(d)) {
						allNaN = false;
						break;
					}
				}
				if(allNaN){
					Y.set(j,1.0);
				}
				else{
					Y.set(j,0.0);
				}
			}
		}
	}

	/** Finds the constant columns of X, returning a row vector 0's and 1's. */
	public static final void findZeroVarianceColumns(Matrix X, Matrix Y) {
		Y.redimension(1, X.cols);
		int rows, cols;
		double d, val;
		double[][] xd=X.data;
		boolean constant;
		if(!X.transposed) {
			for(int j=0;j<X.cols;j++) {
				constant = true;
				val = xd[0][j];
				for(int i=1;i<X.rows;i++) {
					if(Double.compare(xd[i][j], val) != 0) {
						constant = false;
						break;
					}
				}
				if(constant){
					Y.set(j,1.0);
				}
				else {
					Y.set(j,0.0);
				}
			}
		} else {
			for(int j=0;j<X.cols;j++) {
				constant = true;
				val = xd[j][0];
				for(int i=1;i<X.rows;i++) {
					if(Double.compare(xd[j][i], val) != 0) {
						constant = false;
						break;
					}
				}
				if(constant){
					Y.set(j,1.0);
				}
				else {
					Y.set(j,0.0);
				}
			}
		}
	}

 /** 
pinv(X,Y) produces a matrix Y of the same dimensions as X' so that X*Y*X = X, 
Y*X*Y = Y and XY and YX are Hermitian. The computation is based on SVD() and any 
singular values less than a tolerance are treated as zero. The default tolerance 
is MAX(SIZE(X)) * NORM(X) * EPS.
*/
	public static final void pinv(Matrix X, Matrix Y)  throws MathException {
		Y.redimension(X.cols, X.rows);
		int rows, cols;
		Matrix U = createMatrix();
		Matrix S = createMatrix();
		Matrix V = createMatrix();
		svd(X,U,S,V);
		double eps = 2.2204e-16;  /* why this value ??? */
		double tol = Math.max(X.cols,X.rows)*S.get(0,0)*eps;
		diag(S,S);
		int r = 0;
		for(int i=0;i<S.rows;i++){
			if(S.get(i,0)>tol){
				r++;
			}
		}
		if(r == 0){
			for(int i=0;i<Y.rows;i++){
				for(int j=0;j<Y.cols;j++){
					Y.set(i,j,0);
				}
			}

		}else{
			Matrix temp = ones(r,1);
			getRows(S,0,r-1,S);
			divideElements(temp,S,S);
			diag(S,S);
			getColumns(V,0,r-1,V);
			getColumns(U,0,r-1,U);
			transpose(U,U);
			multiply(V,S,temp);
			multiply(temp,U,Y);
			clear(temp);
		}
		clear(U);
		clear(S);
		clear(V);
	}

	/** Sum of the elements.*/
   	public static final double sum(Matrix X) {
		if(X.rows==1 || X.cols==1) {
			double sum = 0.0;
			for(int i=0;i<X.elements;i++){
				if (!(Double.isNaN(X.get(i)) || Double.isInfinite(X.get(i)))) {
					sum += X.get(i);
				}
			}
			return sum;
		} else {
			double sum = 0.0;
			for(int j=0;j<X.cols;j++) {
				for(int i=0;i<X.rows;i++){
					if (!(Double.isNaN(X.get(i,j)) || Double.isInfinite(X.get(i,j)))) {
						sum += X.get(i,j);
					}
				}
			}
			return sum;
		}
	}

	/** returns true if matrix contains any column with constant value.*/
	public static final double[] hasConstantColumns(Matrix X) {
		Matrix Y = createMatrix();
		findZeroVarianceColumns(X, Y);
		int count = 0;
		for(int i=0;i<Y.cols;i++){
			if(Double.compare(Y.get(0,i), 1) == 0) {
				count = count + 1;
			}
		}
		if (count >0) { 
			return new double[0];
		}else{
			double[] indexes = new double[count];
			count = 0;
			for(int i=0;i<Y.cols;i++){
				if(Double.compare(Y.get(0,i), 1) == 0) {
					indexes[count] = i;
					count = count + 1;
				}
			}
		}
		return new double[0];
	}
}

 
