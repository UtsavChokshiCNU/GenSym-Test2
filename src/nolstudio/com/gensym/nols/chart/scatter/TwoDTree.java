package com.gensym.nols.chart.scatter;

import java.security.SecureRandom;

/**
 * TwoDTree
 * @version     1.1 June 11, 1998
 * @author      Brian O. Bush
 **/

public class TwoDTree {

	private double [] globalX;
	private double [] globalY;
	private boolean [] valid;

	private double [] query;
	private int MaxBucketSize = 20; /* Maximum number of nodes in a bucket */
	private int nodesCreated;		/* Node counters */
	public TwoDTreeNode treehead;   /* Top of the tree */
	private int[] bigbucket;		/* Dynamic array-individual buckets will point into this */
	public int[] foundItems;		/* items found in search */
	private int numFoundItems;

	private static final boolean DEBUG = false;

	private static final int X_AXIS = 0;
	private static final int Y_AXIS = 1;	
	private static final int MIN = 0;
	private static final int MAX = 1;

	private static final int XMIN = 0;
	private static final int XMAX = 1;
	private static final int YMIN = 2;
	private static final int YMAX = 3;

	private static final int DIM = 2;  // dimension will always be 2, x and y


  /**
   * Constructor.
   * @param two double arrays to search through
   * @param length of the arrays
   * @param the size of each bucket in the tree
   */ 			   
	public TwoDTree (double[] x, double[] y, int length, int depth) {
		if (x.length != y.length) 
			throw new IllegalArgumentException("X and Y Arrays are of unequal length!");

		
		/* initialize variables */
		
		globalX = x;
		globalY = y;

		MaxBucketSize = depth;
		nodesCreated = 0;
		int startindex = 0;

		/* create arrays */

		// create the 4 element array to hold the search query
		query = new double[4]; // bbush 8-14-98

		// create array to hold all that could possibly be found
		foundItems = new int[length];

		// set the number of found items to zero
		numFoundItems = 0;
	
		// this is the main index into the two double arrays
		bigbucket = new int[length];

		// create the array to hold the validity of each element in the bigbucket
		valid = new boolean[length];
		
		// Create an identity mapping
		for(int i = 0; i < length; i++){
			bigbucket[i] = i; 
		}

		// Go through all values looking for NaN values and note NaNs in valid array
		for(int i = 0; i < length; i++) {
			if((!Double.isNaN(globalX[i])) && (!Double.isNaN(globalY[i]))) 
				valid[i] = true;
			else 
				valid[i] = false;
			}

//		System.out.print("building tree...");

		// This call will recursively create everything
		treehead = createNode(bigbucket, startindex, bigbucket.length, true);

		if(DEBUG) {
			System.out.println("done, " + nodesCreated + " nodes created." );
		}

	}



	/**
     *
	 * Method: createNode
	 * by Brian O. Bush
	 * June 9, 1998
	 *
	 * Parameters to method:
	 * @param inputindices - int []  : array of row numbers of the X-Y data
	 * @param startindex   - int     : the start index into inputindices
	 * @param numpoints    - int     : number of points in this bucket
	 * @param split        - boolean : which axis to split on, X = 0, Y = 1
	 * @returns TwoDTreeNode
	 * Note: valid points run from inputindices[0] to [numpoints-1] 
     */

	private TwoDTreeNode createNode (final int[] inputindices, final int startindex, final int numpoints, final boolean split)
	{
		// variables
		int	nleft = 0,		// the number of elements on the left
			nright = 0;		// the number of elements on the right
		double val;			// current value from data used in sorting row values of data
		double sum = 0.0;	// used in computing mean to determine partitioning point

		// Create this node 
		if(DEBUG) {
			System.out.println("numpoints=" + numpoints + " start=" + startindex);
		}
		TwoDTreeNode thisnode = new TwoDTreeNode(inputindices, numpoints, startindex);
		
		// Base Case, this condition determines the terminal condition under
		// which recurrsion will halt. If number of points is smaller than bucket 
		// size, build a terminal node
		if (numpoints <= MaxBucketSize) {  
			thisnode.left = null;
			thisnode.right = null;
			storeBounds(thisnode);
			return thisnode;
		} 
		// else the numpoints is greater than MaxBucketSize, 
		// thus we need to split the node

		boolean splitFlag = split;
		// set this nodes discriminator, X is true and Y is false
		thisnode.discriminator = splitFlag;

		// invert the node discriminator for the next nodes
		splitFlag = !splitFlag;

		// now compute the partition, here it is the mean, or could be easily changed to be equal split
		if (thisnode.discriminator) { // compute mean over X
			for (int j = 0; j < numpoints; j++) {
				if(valid[inputindices[j + startindex]])
					sum += globalX[inputindices[j + startindex]];
			}
		}
		else { // compute mean over Y
			for (int j = 0; j < numpoints; j++) {
				if(valid[inputindices[j + startindex]])
					sum += globalY[inputindices[j + startindex]];
			}
		}

		thisnode.partition = (sum/(numpoints)); // now have the mean, which will be used as the partition

		// do a simple sort on the inputindices over the range
		do {
				int i = inputindices[nleft + startindex];

				if(thisnode.discriminator)			// use X
					val = globalX[i];
				else								// else use Y
					val = globalY[i];

	  			if (val <= thisnode.partition) { // It's on the left side  
	  				nleft++;        
				}
				else {				// Swap it with an element from the right side
	  				inputindices[nleft + startindex] = inputindices[numpoints - nright - 1 + startindex];
	  				inputindices[numpoints - nright - 1 + startindex] = i;
	  				nright++;
				}
		} while ((nleft + nright) != numpoints); 

		if(DEBUG) {
			System.out.println("Node has " + numpoints + " with " + nleft + " left and " + nright + " right leaves");
		}


		// to prevent recursing on the same points, and thus causing the stack to
		// overflow, we end this node if there are points all on one side
		if((nleft == numpoints) || (nright == numpoints)) {
			if(DEBUG)
				System.out.println("\tCreating Node with " + numpoints);
			thisnode.left = null;
			thisnode.right = null;
			storeBounds(thisnode);
			return thisnode;
		}

		
		if(DEBUG) {
			System.out.println("------------------------------------------");
		}

		// Create left child node 
		if(DEBUG) {
			System.out.println("LEFT: numpoints=" + numpoints + " nleft=" + nleft + " split=" + splitFlag );
		}
		thisnode.left = createNode(inputindices, startindex, nleft, splitFlag);
		nodesCreated++;
		
		// Create right child node
		if(DEBUG) {
			System.out.println("RIGHT: numpoints=" + numpoints + " nright=" + nright + " split=" + splitFlag );
		}
		thisnode.right = createNode(inputindices, startindex + numpoints - nright,  nright, splitFlag);
		nodesCreated++;

		// Code to fill up hyper-rectangle bounds arrays 
		thisnode.max = resolveUpperBounds(thisnode.left, thisnode.right);
		thisnode.min = resolveLowerBounds(thisnode.left, thisnode.right);

		return thisnode;
	}


	//
	//  Calculate the minimum and maximum bounds on the hyper-rectangle spanned by the points in the current terminal node
	//
	private void storeBounds(TwoDTreeNode thisnode) {
		int i;

		thisnode.min = new double[DIM];
		thisnode.max = new double[DIM];

		/* Initialize the arrays */
		thisnode.min[X_AXIS] = Double.MAX_VALUE;
		thisnode.max[X_AXIS] = -Double.MAX_VALUE;
		
		thisnode.min[Y_AXIS] = Double.MAX_VALUE;
		thisnode.max[Y_AXIS] = -Double.MAX_VALUE;
		
		for (i = thisnode.getStart();i < thisnode.getStart() + thisnode.numPoints(); i++) {
			// X AXIS
			if(valid[i]) {
				if (globalX[bigbucket[i]] < thisnode.min[X_AXIS]) {
					thisnode.min[X_AXIS] = this.globalX[bigbucket[i]];
				}	
 
				if (globalX[thisnode.bucket[i]] > thisnode.max[X_AXIS]) {
					thisnode.max[X_AXIS] = this.globalX[bigbucket[i]];
				}
			}

			// Y AXIS
			if(valid[i]) {
				if (globalY[bigbucket[i]] < thisnode.min[Y_AXIS]) {
					thisnode.min[Y_AXIS] = this.globalY[bigbucket[i]];
				}	
				
				if (globalY[thisnode.bucket[i]] > thisnode.max[Y_AXIS]) {
					thisnode.max[Y_AXIS] = this.globalY[bigbucket[i]];
				}
			}
		}
		return;
	}


	//
	// Get the counter that holds the number of found items
	//
	public int getNumFoundItems() {
		return numFoundItems;
	}

	//
	// Reset counter that holds the number of found items
	//
	public void resetNumFoundItems() {
		numFoundItems = 0;
	}


	//
	// Search 2D Tree
	//
	public void searchTwoDTree(double xmin, double xmax, double ymin, double ymax) {
		resetNumFoundItems();
		query[XMIN] = xmin;
		query[XMAX] = xmax;
		query[YMIN] = ymin;
		query[YMAX] = ymax;
		searchNode(treehead);
	}

	//
	// Search TwoDTree Node
	//
	private void searchNode(TwoDTreeNode node) {

		// base case, node has nonzero number of points
		if((node.left == null) && (node.right == null)) {
			processTerminalNode(node);
			return;
		}

		if(node.discriminator) {  // cut on X axis
			if (query[XMAX] <= node.partition) 
				searchNode(node.left);
			else if (query[XMIN] > node.partition)
				searchNode(node.right);
			else {
				searchNode(node.left);
				searchNode(node.right);
			}
		}
		else {  // else cut on Y axis
			if (query[YMAX] <= node.partition)
				searchNode(node.left);
			else if (query[YMIN] > node.partition)
				searchNode(node.right);
			else {
				searchNode(node.left);
				searchNode(node.right);
			}
		}
	}


	//
	// Process Terminal Node
	//
	private void processTerminalNode(TwoDTreeNode node) {
		int[] index;

		index = node.getIndices();
		for(int i=0; i<node.numPoints(); i++) {
			if(valid[index[i]]) { 
				if((globalX[index[i]] <= query[XMAX]) && (globalX[index[i]] >= query[XMIN]))
						if((globalY[index[i]] <= query[YMAX]) && (globalY[index[i]] >= query[YMIN])) {
							foundItems[numFoundItems] = index[i];
							numFoundItems++;
//							System.out.print("[" + globalX[index[i]] + "," + globalY[index[i]] + "], ");
						}
			}
		}
	}

	//
	// Resolve Lower Bounds
	//
	private double[] resolveLowerBounds (TwoDTreeNode First, TwoDTreeNode Second ) {
		double[] bounds = new double[DIM];

		if (First.min[X_AXIS] < Second.min[X_AXIS]) {
				bounds[X_AXIS] = First.min[X_AXIS];
			}
		else bounds[X_AXIS] = Second.min[X_AXIS];	
		
		
		if (First.min[Y_AXIS] < Second.min[Y_AXIS]) {
				bounds[Y_AXIS] = First.min[Y_AXIS];
			}
		else bounds[Y_AXIS] = Second.min[Y_AXIS];	
		return bounds;
	}

	
	//
	// Resolve Upper Bounds
	//
	private double[] resolveUpperBounds (TwoDTreeNode First, TwoDTreeNode Second ) {
		double[] bounds = new double[DIM];

		if (First.max[X_AXIS] > Second.max[X_AXIS]) {
			bounds[X_AXIS] = First.max[X_AXIS];
		}
		else bounds[X_AXIS] = Second.max[X_AXIS];	
		
		if (First.max[Y_AXIS] > Second.max[Y_AXIS]) {
			bounds[Y_AXIS] = First.max[Y_AXIS];
		}
		else bounds[Y_AXIS] = Second.max[Y_AXIS];	
		return bounds;
	}

	class TwoDTreeNode {

		public boolean discriminator;    /* Which dimension to judge on? X (0) or Y (1) */
		public double partition;     /* What's the cutoff value */

		public int[] bucket;         /* Indices of the vectors in this bucket, null if nonterminal node. */
		public int nbucket;          /* Number of vectors in the bucket */

		private int start;    /* Where in the bucket array where the vectors in this bucket start being referenced */
		public double[] min, max;    /* The upper and lower bounds of the hyper-rectangle */

		TwoDTreeNode left, right;    /* Child nodes */

		public TwoDTreeNode (int[] indices, int numpoints, int start) {
		//		System.out.println("\t*building node with "+numpoints+" points starting at " + start);
			this.setPoints(numpoints);   
			this.bucket = indices;
			this.setStart(start);
			this.left = null;
			this.right = null;
		}

		public int[] getIndices() {
			int i;
			int[] indices = new int[nbucket];
			
			for (i=0; i<nbucket; ++i) {
				indices[i] = bucket[i+start];
			}	
			
			return indices;
		}

		public double[] getMax() {
			return this.max;
		}

		public double[] getMin() {
			return this.min;
		}

		public int getStart() {
			return this.start;
		}

		public int numPoints() {
			return this.nbucket;
		}

		public void setPoints (int num ) {
			this.nbucket = num;
			return;
		}

		public void setStart(int st) {
			this.start = st;
			return;
		}
	}
	//
	// Main for testing purposes, run this after changes to make sure it still works
	//
	public static void main(String args[]) {
	
	int DATASETSIZE = 1000;

		int length;
		SecureRandom rand = new SecureRandom();
		rand.setSeed(10L);
		double [] x = new double [DATASETSIZE];
		double [] y = new double [DATASETSIZE];
			
		for(int i=0; i<DATASETSIZE; i++) {
			x[i] = rand.nextDouble();
			y[i] = rand.nextDouble();
	//		System.out.println("x: " +  x[i] + " y: " + y[i]);
		}

		for(int i=0; i<DATASETSIZE; i++) {
			if((rand.nextInt()*5) <= 2) {
				x[i] = Double.NaN;
				y[i] = Double.NaN;
			}
		}
/*
		for(int i=0; i<DATASETSIZE/2; i++) {
			x[i] = Double.NaN;
			y[i] = Double.NaN;
		}
*/
		/*
		// testing NaN for x[]
		x[1] = Double.NaN;
		x[16] = Double.NaN;
		x[26] = Double.NaN;
		x[27] = Double.NaN;
		x[28] = Double.NaN;
		x[29] = Double.NaN;
		x[31] = Double.NaN;
		x[41] = Double.NaN;
		x[44] = Double.NaN;

		// testing NaN for y[]
		y[23] = Double.NaN;
		y[13] = Double.NaN;
		y[26] = Double.NaN;
		y[3] = Double.NaN;
		y[7] = Double.NaN;
		y[6] = Double.NaN;
		y[42] = Double.NaN;
		y[43] = Double.NaN;
		y[44] = Double.NaN;
*/

		System.out.println("Two Dimensional Tree search algorithm");
		System.out.println("building tree...");

		length = x.length;
		TwoDTree tree = new TwoDTree(x, y, length, 12);
		
		// now query search tree
		double xmin = 0.1;
		double xmax = 0.4;
		double ymin = 0.0;
		double ymax = 0.5;

		
	//	System.out.println("searching tree...");
		tree.searchTwoDTree(xmin, xmax, ymin, ymax);

		System.out.println("results...");
		int count = tree.getNumFoundItems();
		for(int z = 0; z < count; z++)
			System.out.print(tree.foundItems[z] + ", ");
		tree.resetNumFoundItems();
		
		System.out.println("\nsearch found " + count + " items.\n");

		// brute force search to get count
		int totalCount = 0;
		for(int i=0; i<x.length; i++)
		{
			if((x[i] <= xmax) && (x[i] >= xmin))
			{
				if((y[i] <= ymax) && (y[i] >= ymin))
					totalCount++;
			}
		}

		System.out.println("\n\nTotal count of X-Y pairs within bounding rectangle: " + totalCount);

	}


}