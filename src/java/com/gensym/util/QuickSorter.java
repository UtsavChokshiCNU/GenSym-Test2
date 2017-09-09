package com.gensym.util;

import java.util.Vector;

public abstract class QuickSorter
{
  public void quickSortInPlace(Vector v)
  {
    quickSortInPlace(v, 0, v.size()-1);
  }

  public void quickSortInPlace(Object[] a)
  {
    quickSortInPlace(a, 0, a.length - 1);
  }

  public boolean lessThan(Object a, Object b)
  {
    return true;
  }

  private void swap(Vector a, int i, int j) {
    Object T = a.elementAt(i); 
    a.setElementAt(a.elementAt(j), i);
    a.setElementAt(T, j);
  }
  
  // Liberated from the 1.1 SortDemo
  /** This is a generic version of C.A.R Hoare's Quick Sort 
   * algorithm.  This will handle arrays that are already
   * sorted, and arrays with duplicate keys.<BR>
   *
   * If you think of a one dimensional array as going from
   * the lowest index on the left to the highest index on the right
   * then the parameters to this function are lowest index or
   * left and highest index or right.  The first time you call
   * this function it will be with the parameters 0, a.length - 1.
   *
   * @param a       an integer array
   * @param lo0     left boundary of array partition
   * @param hi0     right boundary of array partition
   */
  private void quickSortInPlace(Vector v, int lo0, int hi0)
  {
    int lo = lo0;
    int hi = hi0;
    Object mid;
    
    if ( hi0 > lo0)
      {
	
	/* Arbitrarily establishing partition element as the midpoint of
	 * the array.
	 */
	mid = v.elementAt(( lo0 + hi0 ) / 2);
	
	// loop through the array until indices cross
	while( lo <= hi )
	  {
	    /* find the first element that is greater than or equal to 
	     * the partition element starting from the left Index.
	     */
	    // Nasty to have to cast here. Would it be quicker
	    // to copy the vectors into arrays and sort the arrays?
	    while( ( lo < hi0 ) && 
		   lessThan( v.elementAt(lo), mid ) )
	      ++lo;
	    
	    /* find an element that is smaller than or equal to 
	     * the partition element starting from the right Index.
	     */
	    while( ( hi > lo0 ) && 
		   lessThan( mid, v.elementAt(hi) ) )
	      --hi;
	    
	    // if the indexes have not crossed, swap
	    if( lo <= hi ) 
	      {
		swap(v, lo, hi);
		++lo;
		--hi;
	      }
	  }
	
	/* If the right index has not reached the left side of array
	 * must now sort the left partition.
	 */
	if( lo0 < hi )
	  quickSortInPlace( v, lo0, hi );
	
	/* If the left index has not reached the right side of array
	 * must now sort the right partition.
	 */
	if( lo < hi0 )
		quickSortInPlace( v, lo, hi0 );
	
      }
  }
   

  private void quickSortInPlace(Object[] a, int lo0, int hi0)
  {
    int lo = lo0;
    int hi = hi0;
    Object mid;
    
    if ( hi0 > lo0)
      {
	
	/* Arbitrarily establishing partition element as the midpoint of
	 * the array.
	 */
	mid = a[( lo0 + hi0 ) / 2];
	
	// loop through the array until indices cross
	while( lo <= hi )
	  {
	    /* find the first element that is greater than or equal to 
	     * the partition element starting from the left Index.
	     */
	    // Nasty to have to cast here. Would it be quicker
	    // to copy the vectors into arrays and sort the arrays?
	    while( ( lo < hi0 ) && 
		   lessThan( a[lo], mid ) )
	      ++lo;
	    
	    /* find an element that is smaller than or equal to 
	     * the partition element starting from the right Index.
	     */
	    while( ( hi > lo0 ) && 
		   lessThan( mid, a[hi] ))
	      --hi;
	    
	    // if the indexes have not crossed, swap
	    if( lo <= hi ) 
	      {
		Object temp = a[lo];
		a[lo] = a[hi];
		a[hi] = temp;
		++lo;
		--hi;
	      }
	  }
	
	/* If the right index has not reached the left side of array
	 * must now sort the left partition.
	 */
	if( lo0 < hi )
	  quickSortInPlace( a, lo0, hi );
	
	/* If the left index has not reached the right side of array
	 * must now sort the right partition.
	 */
	if( lo < hi0 )
		quickSortInPlace( a, lo, hi0 );
	
      }
  }
  
  public static void main(String[] args)
  {
    QuickSorter qs = 
      new QuickSorter ()
      {
	@Override
	public boolean lessThan(Object a, Object b)
	  {
	    return a.toString().toLowerCase().
	      compareTo(b.toString().toLowerCase()) < 0;
	  }
      };

    Vector v = new Vector();
    v.addElement("Foo");
    v.addElement("Yada");
    v.addElement("Bar");
    v.addElement("Baz");
    v.addElement("Blah");
    
    System.out.println("input is "+v);
    qs.quickSortInPlace(v);
    System.out.println("output is "+v);

    Object[] foo = new Object[] { "qwer", "asdf", "rtuy", "ery"};
    System.out.println("input is ");
    int i, len = foo.length;
    for (i=0; i<len; i++)
      System.out.println("  "+foo[i]);
    qs.quickSortInPlace(foo);
    System.out.println("output is "+foo);
    for (i=0; i<len; i++)
      System.out.println("  "+foo[i]);
  }

}
