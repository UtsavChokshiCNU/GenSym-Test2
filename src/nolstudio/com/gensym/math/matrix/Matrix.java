package com.gensym.math.matrix;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.EOFException;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.Serializable;
import java.net.URL;
import java.nio.charset.Charset;
import java.security.SecureRandom;
import java.util.Vector;

import com.gensym.math.Algorithms;
import com.gensym.math.MathException;
import com.gensym.math.Utilities;


/* POOLED MEMORY MANAGEMENT IMPLEMENTATION.

	Data is stored in 2D arrays, oriented so the fewest objects are required.
	For example, a 10x100 matrix is represented by a 10 100-element arrays,
	and a 100x10 matrix is (likewise) represented as 10 100-elements arrays.
	A flag, transposed, is maintained to indicate a reversal of normal indexing.
*/

public final class Matrix implements Serializable, Cloneable {
	
	static final long serialVersionUID = 1L;
	protected int rows;
	protected int cols;
	protected int elements;
	private volatile int spineLength;
	private volatile int arrayLength;
	private volatile int arrayPoolIndex;
	private volatile int spinePoolIndex;
	private volatile int arrayCount;
	protected double[][] data;
	protected boolean transposed;
	private static boolean DEBUG = true;   // set to true to detect memory pool corruption
	private static int ARRAY_POOL_DIMENSION = 35;
	private static int SPINE_POOL_DIMENSION = 35;
	private static Vector[] arrayPool;
	private static int[] arrayAllocations;
	private static Vector[] spinePool;
	private static int[] spineAllocations;
	private static Vector matrixPool;
	private static int matrixAllocations;
	private static int POOL_EXPANSION_INCREMENT = 100;
	private static double BASE = 1.5;
	private static double LNBASE = Math.log(BASE);

	private static final Object TARGET_MONITOR = new Object();
	/* matrix types */
	public static final int ZEROS = 0;
	public static final int ONES = 1;
	public static final int EYE = 2;
	public static final int RAND = 3;
	public static final int RANDN = 4;
	private static final String MAT_ERROR_LOG_FILE = "MatError.log";
	
	static {
		// set up pool for matrix instances
		matrixAllocations = 0;
		matrixPool = new Vector(0,POOL_EXPANSION_INCREMENT);
		// set up pool to hold matrix rows
		arrayPool = new Vector[ARRAY_POOL_DIMENSION + 1];
		arrayAllocations = new int[ARRAY_POOL_DIMENSION + 1];
		for(int i=0; i<=ARRAY_POOL_DIMENSION; i++) {
			arrayPool[i] = new Vector(0,POOL_EXPANSION_INCREMENT);
		}
		// likewise for spines
		spinePool = new Vector[SPINE_POOL_DIMENSION + 1];
		spineAllocations = new int[SPINE_POOL_DIMENSION + 1];
		for(int i=0; i<=SPINE_POOL_DIMENSION; i++) {
			spinePool[i] = new Vector(0,POOL_EXPANSION_INCREMENT);
		}
	}


	private static BufferedWriter target = null;

	
	public Matrix() {
		matrixAllocations++;
		this.setInitialParameters();
	}
	
	public Matrix(Matrix matrix){
		rows = matrix.rows;
		cols = matrix.cols;
		elements = matrix.elements;
		spineLength = matrix.spineLength;
		arrayLength = matrix.arrayLength;
		arrayPoolIndex = matrix.arrayPoolIndex;
		spinePoolIndex = matrix.spinePoolIndex;
		arrayCount = matrix.arrayCount;
		data = matrix.data == null ? null : matrix.data.clone();
		transposed = matrix.transposed;
	}

	@Override
	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}
	
	public final  void setInitialParameters() {
		rows = 0;
		cols = 0;
		elements = 0;
		spineLength = 0;
		arrayLength = 0;
		arrayPoolIndex = 0;
		arrayCount = 0;
		spinePoolIndex = 0;
		transposed = false;
		data = null;
	}
	
	protected static final synchronized  Matrix newMatrix() {
		Matrix M;
		// allocate from pool if possible, otherwise create it
		if (matrixPool.isEmpty()) {
			M = new Matrix();
		} else {
			M = (Matrix) matrixPool.lastElement();
			matrixPool.removeElementAt(matrixPool.size() - 1);
		}
		M.setInitialParameters();
		return M;
	}

	protected static final synchronized  Matrix newMatrix(int r, int c) {
		Matrix M = newMatrix();
		if (r>0 && c>0){
			M.redimension(r,c);
		}
		return M;
	}

   	protected static final synchronized  Matrix newMatrix(int r, int c, boolean transposed) {
		Matrix M = newMatrix();
		if (r>0 && c>0) {
			M.redimension(r,c,transposed);
		}
		return M;
	}

	private static final int getPoolIndex(int size) {
		// find the pool index that contains an array large enough for the given size
	/*	int i=0;
		--size;  // this assures that if the size is an even power of 2, we'll return the row that fits exactly
		while(size > 0) {size = size>>1; ++i;}
		return i; */
		if(size<4) {
			return size-1;
		}
		else {
			return (int) Math.ceil(Math.log((double)size-1)/LNBASE);
		}
	}

	private static final int getArrayLength(int index) {
		return (int) Math.ceil(Math.pow(BASE,index));
	}

	public final void redimension(int r, int c) {
		// use orientation that minimizes number of arrays
		if(r>c){
			redimension(r,c,true);
		}
		else {
			redimension(r,c,false);
		}
	}

	protected final  void redimension(int r, int c, boolean transpose) {
		if(rows==r && cols==c && transposed==transpose){
			return;
		}
		if(r<=0 || c<=0) {  // do not return matrix to matrix pool, just eviscerate it
			deallocateSpine(); 
			rows = 0;
			cols = 0;
			return;
		}  		
		int newSpineLength;
		int newArrayLength;
		int newArrayCount;
		int newArrayPoolIndex;
		int newSpinePoolIndex;
		// figure out new dimensions
		if (transpose) {
			transposed = true;
			newSpinePoolIndex = getPoolIndex(c);
			newArrayPoolIndex = getPoolIndex(r);
			newArrayCount = c;
		} else {
			transposed = false;
			newSpinePoolIndex = getPoolIndex(r);
			newArrayPoolIndex = getPoolIndex(c);
			newArrayCount = r;
		}
		//newArrayLength = (1<<newArrayPoolIndex);
		//newSpineLength = (1<<newSpinePoolIndex);
		newArrayLength = getArrayLength(newArrayPoolIndex);
		newSpineLength = getArrayLength(newSpinePoolIndex);
//System.out.println("r="+r+" c="+c+" sl="+newSpineLength+" al="+newArrayLength+" spi="+newSpinePoolIndex+" api="+newArrayPoolIndex);
		// create new spine if length has changed
		if(newSpineLength != spineLength) {
			deallocateSpine();   // sets spineLength = 0; also deallocates arrays
			spineLength=newSpineLength;
			spinePoolIndex = newSpinePoolIndex;
			allocateSpine();
		}
		if(newArrayLength != arrayLength){
			deallocateArrays();
		}
		arrayLength = newArrayLength;
		arrayPoolIndex = newArrayPoolIndex;
		if(newArrayCount > arrayCount){
			allocateArrays(arrayCount, newArrayCount);
		}
		else if(newArrayCount < arrayCount){
			deallocateArrays(arrayCount, newArrayCount);
		}
		rows = r;
		cols = c;
		elements = r*c;




  // Try one more time with non-optimal method, this may lead to memory leak.

		if(data == null){
			data = new double[spineLength][]; 
			for (int i=0; i<data.length; i++) {
				data[i] = new double[arrayLength];
			}
		}else{
			for(int h=0;h<data.length;h++){
				if(data[h] == null){
					data[h] = new double[arrayLength];
				}
			}
		}

		boolean falseData = false;
		int falseIndex = -1;
		if(data == null){
			falseData = true;
		}else{
			for(int h=0;h<data.length;h++){
				if(data[h] == null){
					falseData = true;
					falseIndex = h;
					break;
				}
			}
		}

		if(falseData){
			String str = "ERROR:  Fail to redimension new data, index = "+falseIndex+"\n"
				+" rows="+rows+"\n"
				+" cols="+cols+"\n"
				+" elements="+elements+"\n"
				+" spineLength="+spineLength+"\n"
				+" arrayLength="+arrayLength+"\n"
				+" arrayPoolIndex="+arrayPoolIndex+"\n"
				+" spinePoolIndex="+spinePoolIndex+"\n"
				+" transposed="+transposed+"\n"
				+" arrayCount="+arrayCount+"\n"	;
			
			synchronized (TARGET_MONITOR) {
				try { 
					if(target == null){
						File targetFile = new File(MAT_ERROR_LOG_FILE);
						if(!targetFile.canWrite()){
							targetFile.delete();
							targetFile = new File(MAT_ERROR_LOG_FILE);
						}
						target = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(targetFile), Charset.defaultCharset()));
					}else{
						target.newLine();
					}
					
					target.write(str,0,str.length());
					target.flush();
				}catch(IOException e){		
					System.err.println("ERROR: can not write to " + MAT_ERROR_LOG_FILE + " : " + e.getMessage());
				}
			}

		}
	}

	private final void deallocateArrays() {
		deallocateArrays(arrayCount, 0);
	}

	private final void deallocateArrays(int currentCount, int targetCount) {
		if (data == null)
			return; // already deallocated
		synchronized (arrayPool) {
			Vector pool = arrayPool[arrayPoolIndex];
			for (int i = targetCount; i < currentCount; i++) {
				if (DEBUG && pool.contains(data[i])) {
					String str = "ERROR:  Attempted to return an array to the pool twice";
					synchronized (TARGET_MONITOR) {
						try {
							if (target == null) {
								File targetFile = new File(MAT_ERROR_LOG_FILE);
								if (!targetFile.canWrite()) {
									targetFile.delete();
									targetFile = new File(MAT_ERROR_LOG_FILE);
								}
								target = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(targetFile), Charset.defaultCharset()));
							} else {
									target.newLine();
							}
							
							target.write(str, 0, str.length());
							target.flush();
						} catch (IOException e) {
							System.err.println("ERROR: can not write to " + MAT_ERROR_LOG_FILE + " : " + e.getMessage());
						}
					}
					System.err.println("ERROR:  Attempted to return an array to the pool twice");
				} else
					pool.addElement(data[i]);
				data[i] = null;
			}
			arrayCount = targetCount;
			if (targetCount == 0) {
				arrayPoolIndex = 0;
				arrayLength = 0;
			}
		}
	}

	private final  void deallocateSpine() {
		// System.out.println("deallocating spine, array count = "+arrayCount);
		if (data == null)
			return; // already deallocated
		synchronized (spinePool) {
			if (arrayCount > 0)
				deallocateArrays();
			spinePool[spinePoolIndex].addElement(data);
			spinePoolIndex = 0;
			spineLength = 0;
			data = null;
		}
	}
		
	private final  void allocateSpine() {
		synchronized (spinePool) {
			Vector pool = spinePool[spinePoolIndex];
			if (pool.isEmpty()) {
				spineAllocations[spinePoolIndex]++;
				data = new double[spineLength][];
			} else {
				data = (double[][]) pool.lastElement();
				pool.removeElementAt(pool.size() - 1);
			}
		}
	}

	private final void allocateArrays(int currentCount, int targetCount) {
		// System.out.println("current = "+currentCount+" target =
		// "+targetCount+" index = "+arrayPoolIndex);
		synchronized (arrayPool) {
			Vector pool = arrayPool[arrayPoolIndex];
			int rowsAvailable = pool.size();
			for (int i = currentCount; i < targetCount; ++i) {
				if (rowsAvailable == 0) {
					arrayAllocations[arrayPoolIndex]++;
					data[i] = new double[arrayLength];
				} else {
					rowsAvailable--;
					data[i] = (double[]) pool.lastElement();
					pool.removeElementAt(rowsAvailable);
				}
			}
			arrayCount = targetCount;
		}
	}

	public static final synchronized  void clearPool() {
		// releases arrays in pool, to be returned to operating system by the garbage collector
		//System.out.println("About to clear pool, matrix allocations = "+matrixAllocations+", pool size = "+matrixPool.size());
		//Matrix.showPoolStatus();
		for (int i=0; i<=ARRAY_POOL_DIMENSION; i++) {
			arrayAllocations[i] -= arrayPool[i].size();
			arrayPool[i].removeAllElements();
		}
		for (int i=0; i<=SPINE_POOL_DIMENSION; i++) {
			spineAllocations[i] -= spinePool[i].size();
			spinePool[i].removeAllElements();
		}
		//note that matrixAllocations is decremented in the finalizer, so we don't do it here
		matrixPool.removeAllElements();
		// ask for garbage collection
		Runtime.getRuntime().gc();
		//System.out.println("Done clearing pool, current pool status");
		//Matrix.showPoolStatus();
	}


	public static final synchronized  void showPoolStatus() {
		// prints the pool status
		System.out.println("Memory Pool Status:");
		int matricesInUse = matrixAllocations - matrixPool.size();
		System.out.println("Matrices  total = "+matrixAllocations+" in use = "+matricesInUse); 
		System.out.println("			ARRAYS			SPINES");
		System.out.println("	length		total	in use		total	in use");
		int length = 1;
		int arraysTotal;
		int arraysInUse;
		int spinesTotal;
		int spinesInUse;
		int doubles=0;
		int n = Math.max(ARRAY_POOL_DIMENSION, SPINE_POOL_DIMENSION);
		for (int i=0; i<=n; i++) {
			if(i<=ARRAY_POOL_DIMENSION) {	
				arraysTotal = arrayAllocations[i];
				doubles += arraysTotal*length;
				arraysInUse = arraysTotal - arrayPool[i].size();
			} else {
				arraysTotal = 0;
				arraysInUse = 0;
			}
			if(i<=SPINE_POOL_DIMENSION) {	
				spinesTotal = spineAllocations[i];
				spinesInUse = spinesTotal - spinePool[i].size();
			} else {
				spinesTotal = 0;
				spinesInUse = 0;
			}
			if (spinesTotal>0 || arraysTotal>0){
				System.out.println("	"+length+"		"+arraysTotal+"	"+arraysInUse+"		"+spinesTotal+"	"+spinesInUse);
			}
			//length*=2;
			length = getArrayLength(i+1);
		}
		System.out.println("Total "+doubles+" doubles ("+16*doubles+" bytes)");
		long totalMemory = Runtime.getRuntime().totalMemory();
		System.out.println("Total process memory = "+totalMemory);
		System.out.println("");
	}
		 
	public final synchronized  void clear() {
		// return matrix, spine and rows to memory pool
		deallocateSpine(); // will call deallocateArrays() if required
		synchronized (matrixPool) {
			if (DEBUG && matrixPool.contains(this)) {
				String str = "WARNING:  Attempted to clear a matrix twice";
				synchronized (TARGET_MONITOR) {
					try {
						if (target == null) {
							File targetFile = new File(MAT_ERROR_LOG_FILE);
							if (!targetFile.canWrite()) {
								targetFile.delete();
								targetFile = new File(MAT_ERROR_LOG_FILE);
							}
							target = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(targetFile), Charset.defaultCharset()));
						} else {
							target.newLine();
						}
						
						target.write(str, 0, str.length());
						target.flush();
					} catch (IOException e) {
					}
				}
				System.out.println("WARNING:  Attempted to clear a matrix twice");
				return;
			}
			matrixPool.addElement(this);
		}
	}

	protected final void copy(Matrix Y) {
		// make Y the same as this matrix
		Y.redimension(rows,cols,this.transposed);
		int n;
		if(transposed){
			n=rows; 
		}
		else {
			n=cols;
		}
		for(int i=0;i<arrayCount;i++) {
			System.arraycopy(data[i], 0, Y.data[i], 0, n);
		}
	}

	protected final void forceDirectIndexing() {
		if(!transposed) {
			return;
		}
		Matrix temp = newMatrix();	
		directIndexCopy(temp);
		temp.destructiveCopy(this);
	}

	protected final void directIndexCopy(Matrix Y) {
		if (transposed) {
			Y.redimension(rows,cols,false);  // do not allow transpose storage
			for(int i=0;i<rows;i++){
				for(int j=0;j<cols;j++){
					Y.data[i][j] = data[j][i];	
				}
			}
		} else copy(Y);
	}

	public final double[][] getData() {
		forceDirectIndexing();
		return data;
	}

	protected final void transpose() {
		transposed = !transposed;
		int temp = rows;
		rows = cols;
		cols = temp;
	}


	/** Initialize matrix elements, type given by static variables ZEROS, ONES, EYE, RAND, RANDN */
	public final void initialize(int type) {
		int i;
		int j;
		int nr;
		int nc;
		if(transposed) {
			nr=cols;
			nc=rows;
		} else {
			nr=rows;
			nc=cols;
		}
		switch (type) {
		case 0 : {  /*zeros*/
			for (i=0; i<nr; i++){
				for (j=0; j<nc; j++) {
					data[i][j] = 0.0;
				}
			}
			break;
				  }
		case 1 : {  /*ones*/
			for (i=0; i<nr; i++){
				for (j=0; j<nc; j++){
					data[i][j] = 1.0;
				}
			}
			break;
				  }
		case 2 : {  /*eye*/
			for (i=0; i<nr; i++){
				for (j=0; j<nc; j++) {
					data[i][j] = 0.0;
				}
			}
			for (i=0; i<Math.min(nr,nc);i++){
				data[i][i] = 1.0;
			}
			break;
				 }
		case 3 : {  /*rand*/
			SecureRandom Ran = new SecureRandom();
			Ran.setSeed((long)(new SecureRandom().nextDouble() * 1.0e6));
			for (i=0; i<nr; i++) {
				for (j=0; j<nc; j++){
					data[i][j] = Ran.nextDouble();
				}
			}
			Ran = null;
			break;
				 }
		case 4 : {  /*randn*/
			SecureRandom Ran = new SecureRandom();
			Ran.setSeed((long)(new SecureRandom().nextDouble() * 1.0e6));
			for (i=0; i<nr; i++){
				for (j=0; j<nc; j++) {
					data[i][j] = Ran.nextGaussian();
				}
			}
			Ran = null;
			break;
				 }
		default:
			}
	}

	public final int getRows() {
		return rows;
	}

	public final int getCols() {
		return cols;
	}

	public final int getElements() {
		return elements;
	}

	@Override
	protected final void finalize() {
		/* just in case a someone forgets to clear a matrix, reclaim the spine and rows */
		matrixAllocations--;
		deallocateSpine();
	}

	protected final void destructiveCopy(Matrix m) {
		/*
		 * clears m, then copies the internal properties m, destroying the
		 * source matrix
		 */
		synchronized (matrixPool) {
			m.deallocateSpine(); // make room for new data;
			m.rows = rows;
			m.cols = cols;
			m.elements = elements;
			m.spineLength = spineLength;
			m.arrayLength = arrayLength;
			m.arrayPoolIndex = arrayPoolIndex;
			m.spinePoolIndex = spinePoolIndex;
			m.transposed = transposed;
			m.arrayCount = arrayCount;
			m.data = data;
			data = null; // lose the pointer to the data
			matrixPool.addElement(this); // returns this matrix to the matrix pool
		}
	}

/*  get AND set ALLOW ACCESS TO MATRIX ELEMENTS USING ZERO-BASED INDEXING
    get1 AND set1 SIMULATE 1-BASED INDEXING.  */

	public final double get(int r, int c) {
		return transposed? data[c][r] : data [r][c];
	}

	public final double get(int index) {
		if(rows==1) {
			return transposed? data[index][0]: data[0][index];
		}
		else if (cols==1){
			return transposed? data[0][index]: data[index][0];
		}
		else{
			return get(Algorithms.remainder(index,rows),(int) Math.floor(((double)index)/rows));
		}
	}

	public final void set(int r, int c, double val) {
		if(transposed){
			data[c][r]=val; 
		}else{ 
			data[r][c]=val;
		}
	}

	public final void set(int index, double val) {
		if(rows==1) {
			if(transposed){
				data[index][0] = val;
			}
			else {
				data[0][index] = val;
			}
		} else if (cols==1) {
			if(transposed) {
				data[0][index] = val; 
			}
			else {
				data[index][0] = val;
			}
		} else set(Algorithms.remainder(index,rows),(int) Math.floor(((double)index)/rows), val);
	}

	public final double get1(int r, int c) {
		return transposed? data[c-1][r-1]: data [r-1][c-1];
	}

	public final double get1(int index) {
		if(rows==1) {
			return transposed? data[index-1][0]: data[0][index-1];
		} else if (cols==1){
			return transposed? data[0][index-1]: data[index-1][0];
		} else {
			return get(Algorithms.remainder(index-1,rows),(int) Math.floor(index-1/(double)rows));
		}
	}

	public final void set1(int r, int c, double val) {
		if(transposed){
			data[c-1][r-1] = val; 
		}else {
			data[r-1][c-1] = val;
		}
	}

	public final void set1(int index, double val) {
		if(rows==1) {
			if(transposed) {
				data[index-1][0] = val; 
			} else { 
				data[0][index-1] = val;
			}
		} else if (cols==1) {
			if(transposed) {
				data[0][index-1] = val; 
			} else {
				data[index-1][0] = val;
			}
		} else {
			set(Algorithms.remainder(index-1,rows),(int) Math.floor(((double)(index-1))/rows), val);
		}
	}

	/** Set the elements of a matrix to the elements of another matrix M2, 
	starting at r1, c1 */
	public final void setPart(int r1, int c1, Matrix M2) throws MathException {
		int r2 = r1 + M2.rows - 1;
		int c2 = c1 + M2.cols - 1;
		if (r1 < 0 || c1 < 0 || r2 >= rows || c2 >= cols)
			throw new MathException ("setPart: cannot set submatrix ("+r1+","+c1+") to ("+r2+","+c2+") in a "+rows+" by "+cols+" matrix");		
		double[][] d2 = M2.data;
		double[][] d1 = data; 
		if (!transposed && !M2.transposed) 
			for(int i=0;i<M2.rows;i++){
				for(int j=0;j<M2.cols;j++){
					d1[r1+i][c1+j] = d2[i][j];
				}
			}
		else if(transposed && !M2.transposed)
			for(int i=0;i<M2.rows;i++){
				for(int j=0;j<M2.cols;j++){
					d1[c1+j][r1+i] = d2[i][j];
				}
			}
		else if(!transposed && M2.transposed)
			for(int i=0;i<M2.rows;i++) {
				for(int j=0;j<M2.cols;j++){
					d1[r1+i][c1+j] = d2[j][i];
				}
			}
		else // both transposed
			for(int i=0;i<M2.rows;i++) {
				for(int j=0;j<M2.cols;j++){
					d1[c1+j][r1+i] = d2[j][i];
				}
			}
	}

	public final void setPart1(int r1, int c1, Matrix M2) throws MathException {
		setPart(r1-1, c1-1, M2);
	}

	public final void setColumn(int col, Matrix M2)  throws MathException {
		setPart(0, col, M2);
	}

	public final void setColumn1(int col, Matrix M2) throws MathException  {
		setColumn(col-1, M2);
	}

	public final void setRow(int row, Matrix M2)  throws MathException {
		setPart(row, 0, M2);
	}

	public final void setRow1(int row, Matrix M2)  throws MathException {
		setRow(row-1, M2);
	}

	/** Display matrix */
	public void display() {
		String s;
		for(int r=0;r<rows;r++)	{
			s = "";
		 	for(int c=0;c<cols;c++){
		 		s = s + "		" + get(r,c);
		 	}
			System.out.println(s);
		}
	}

	/** Display matrix */
	public void display(int digits) {
		String s = "";
		String num = "";
		String spaces = "               ";
		String inf = "            Inf";
		String nan = "            NaN";
		int fieldWidth = digits + 9;
		int nspaces;
		double val;
		for(int r=0;r<rows;r++)	{
			s = "";
		 	for(int c=0;c<cols;c++) {
				val = get(r,c);
				if (Double.isNaN(val)) {
					s += nan;
				}
				else if (Double.isInfinite(val)){
					s += inf;
				}
				else {
					num = Utilities.formatDouble(get(r,c), digits);
					nspaces = fieldWidth - num.length();
//if(nspaces<1) System.out.println("Display problem, val = "+ get(r,c)+", formatted val = "+num);
		 			s += spaces.substring(1,nspaces) + num;
				}
			}
			System.out.println(s);
		}
	}

/** read a two-dimensional double array (not ragged) from an ascii file */
	public static final Matrix readFromFile(String Filename) throws IOException {
		return readFromFile(null, Filename);
	}
	
	public static final Matrix readFromFile(String Directory, String Filename) throws IOException {
		File sourceFile;
		if(Directory==null)
			sourceFile = new File(Filename);	
		else
			sourceFile = new File(Directory,Filename);
		BufferedReader Source = null;
		String dataString;
		int rows=1;
		int cols=0;
		int row;
		int col;
        // First make sure the specified source file exists and is readable
        if (!sourceFile.canRead()){
        	throw new IOException();
        }
        // If here, then everything is okay
		try {
			Source = new BufferedReader(new InputStreamReader(new FileInputStream(sourceFile), Charset.defaultCharset()));
			dataString = Source.readLine(); // sample the first line
			cols = Utilities.getNumberCount(dataString);
			for(;;) {
				dataString = Source.readLine();
				if (dataString==null){
					break;
				}
				rows++;
			}
		}
		catch (EOFException e) { }
		finally { 
			if (Source != null) 
			try {
				Source.close();
			}catch (IOException e) { }
        }
		Matrix M = Matlib.zeros(rows,cols);
		// now actually parse the file
		double[] dataArray = new double[cols];
		try {
			Source = new BufferedReader(new InputStreamReader(new FileInputStream(sourceFile), Charset.defaultCharset()));
			for(row=0;row<rows;row++) {
				dataString = Source.readLine();
				Utilities.string2Data(dataString, cols, dataArray);
				for(col=0;col<cols;col++){
					M.set(row,col,dataArray[col]);
				}
			}
		}
		catch (EOFException e) {  }
		finally {
			if (Source != null) 
			try {
				Source.close();
			} catch (IOException e) { }
        }
		return M;
	}

	protected static final Matrix readFromURL(URL url) throws IOException {
		BufferedReader Source = null;
		String dataString;
		int rows=1;
		int cols=0;
		int row;
		int col;
        // If here, then everything is okay
		try {
			Source = new BufferedReader(new InputStreamReader(url.openStream(), Charset.defaultCharset()));
			dataString = Source.readLine(); // sample the first line
			cols = Utilities.getNumberCount(dataString);
			for(;;) {
				dataString = Source.readLine();
				if (dataString==null){
					break;
				}
				rows++;
			}
		}
		catch (EOFException e) {  }
		finally { 
			if (Source != null) 
			try {
				Source.close();
			}catch (IOException e) { }
        }
		Matrix M = Matlib.zeros(rows,cols);
		// now actually parse the file
		double[] dataArray = new double[cols];
		try {
			Source = new BufferedReader(new InputStreamReader(url.openStream(), Charset.defaultCharset()));
			for(row=0;row<rows;row++) {
				dataString = Source.readLine();
				Utilities.string2Data(dataString, cols, dataArray);
				for(col=0;col<cols;col++){ 
					M.set(row,col,dataArray[col]);
				}
			}
		}
		catch (EOFException e) {  }
		finally {
			if (Source != null) 
			try {
				Source.close();
			} catch (IOException e) { }
        }
		return M;
	}

	/** write a Matrix as a tab-separated ascii file */
	public void writeToFile(String Filename) throws IOException {
		PrintWriter out;
		FileOutputStream fileStream = null;
		BufferedWriter buff = null;
		String tab = "	";
		try {
			fileStream = new FileOutputStream(Filename);
			buff = new BufferedWriter(new OutputStreamWriter(fileStream, Charset.defaultCharset()));
			out = new PrintWriter(buff);
			for(int r=0;r<rows;r++)	{
		 		for(int c=0;c<cols-1;c++) {
					out.print(get(r,c));
					out.print(tab);
				}
				out.print(get(r,cols-1));
				buff.newLine();
			}
		} catch (IOException e) {
			System.out.println("Error writing to file : " + e.getMessage());
		} catch (RuntimeException e) {
			System.out.println("Error writing to file : " + e.getMessage());
		} finally { 
			if (buff != null) {
				try {
					buff.close();
				}catch (IOException e) {
					System.out.println("Error closing writer: " + e.getMessage());
				}
			}
			
			if(fileStream != null){
				try {
					fileStream.close();
				}catch (IOException e) { 
					System.out.println("Error closing file stream: " + e.getMessage());
				}
			}
        }
	} 


}

