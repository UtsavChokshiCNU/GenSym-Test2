package com.gensym.util;

import java.util.Date;
import java.util.Vector;
import java.io.Serializable;


/**
 * This class manages Historical data values.
 * (Used for G2 History of an Item normally found within a G2-Variable or G2-Parameter.
 * 
 */
public class HistorySpec implements Serializable {
  /*
   *	The history and history keeping spec of the item
   */
  long			lastUpdateTime = 0;
  Vector		timeStamps;
  Vector		historicalValues;
  int			maxCount;
  int			maxAge;		//  stored it as seconds 
  int			minInterval;    //  stored as miliseconds 
  Class			historyType;
  
  
  /**
   * Creates an empty HistorySpec.
   */
  public HistorySpec () {
    
  }
  
  
  /**
   * adds a new value to the history of an item taking into
   * account the history keeping spec.
   *
   *@param new_value - the value to be added to the history.
   */
  
  public void setValue (Object new_value)
  {
    /*
     * CAUTION
     *		 if data is sourced from a machine who's clock is set
     *		 to a different time(zone) to the clock on the machine
     *		 running this code, then the history keeping aspect may
     *		 be unpredictable
     */
    
    /* Are we to record history */
    if ((maxCount + maxAge + minInterval) > 0 )
      {
	
	if ((System.currentTimeMillis() - lastUpdateTime  >= minInterval))
	  {
	    
	    int	historyCount = timeStamps.size();
	    
	    // if we are bothered about the age of data and we have some history
	    if ( maxAge > 0 && historyCount > 0)
	      removeOldHistory();				
	    
	    // remember time and data
	    historicalValues.insertElementAt(new_value , 0);
	    timeStamps.insertElementAt( new java.util.Date(),0);
	    
	    // either let the vector grow, or set it to maxCount
	    if (maxCount != 0 )
	      {
		historyCount = java.lang.Math.min( historyCount + 1 , maxCount) ;
		historicalValues.setSize(historyCount);
		timeStamps.setSize(historyCount);
	      }
	  }
      }
    
    // shrink vector as small as need be - also because the vector size
    // may be used to calculate history_count;
    timeStamps.trimToSize();
    historicalValues.trimToSize();
    
  }
  
  
  /**
   *
   *@param targetDate - type Date - date looking for
   *@return index of nearest date or -1 if no history
   */
  private int getNearestDateIndex( Date targetDate)
  {
    
    long td = targetDate.getTime();
    int i =-1;
    boolean foundOne = false;
    
    int	historyCount = timeStamps.size();
    
    // see if there is any data
    if (historyCount > 0 )
      {
	
	Date foundDate = new Date();
	
	// thinking mans go to statement
      locate:
	//loop till we find a Date that is greater than target
	for (i = 0; i < historyCount ; i++)
	  {
	    foundDate = (Date)timeStamps.elementAt(i); 
	    if (foundDate.getTime() >= td ){
	      foundOne = true; // yes I know,
	      break locate;
	    }
	  }
	
	// assuming we found a date,(may well be the last one)
	if (i > 0)
	  {
	    // see if the one we found or the one before that is
	    // the closer of the two to the target
	    Date priorDate = (Date)timeStamps.elementAt(i - 1);
	    
	    if (java.lang.Math.abs(priorDate.getTime() - td ) < 
		java.lang.Math.abs( foundDate.getTime() - td )) 
	      {
		i = i - 1;
	      }
	  }
      }
    
    // will either be -1 --- no history
    // or the index of the Date closes to targetdate
    // which could be 0 ie the first
    if (foundOne){
    	return i;
    }
    else {
    	return -1;
    }
  }
  
  
  /**
   * Removes historical Values if they are older than maxAge
   * is only called if maxAge is > 0 so needs no internal check.
   */
  private void removeOldHistory()
  {
    //The moment we enter this procedure
    Date now = new Date();
    
    Date cutDate ;
    
    if (maxAge > 0)
      {
	cutDate = new Date((now.getTime() - (maxAge * 1000)));
	
	Vector tempTimeStamps = new Vector();
	Vector tempValues = new Vector();
	
	int	historyCount = timeStamps.size();
	
	// collate all the valid data
	for ( int i = 0  ; i < historyCount; i++)
	  {	
	    Date tempDate = (Date)timeStamps.elementAt(i);
	    Object tObj = (Object)historicalValues.elementAt(i);
	    
	    if (tempDate.getTime() > cutDate.getTime() )  
	      {
		tempTimeStamps.addElement(tempDate);
		tempValues.addElement(tObj);				
	      }
	  }		
	
	// replace old history with valid history (sounds Orwellian to me)
	timeStamps = tempTimeStamps;
	historicalValues = tempValues;
	
      }
    // shrink the vectors down to size
    timeStamps.trimToSize();
    historicalValues.trimToSize();
    
  }
  
  
  /**
   *
   *Return the historical value stored at or close to
   * the target Date given by the param d.
   *
   *@param d - Date object of the target time.
   *@returns the object closest to d.
   */
  
  public Object getValueAtDate( Date d)
  {
    
    int index = getNearestDateIndex( d );
    
    if ( index > -1)
      return historicalValues.elementAt(index);
    else
      return null;
  }
  
  
  
  /**
   *
   *Return the historical value stored at or close to
   * the target time given by the param time.
   *
   *@param time - seconds of the time interested in.
   *@returns the object closest to traget time.
   *see HistorySpec.getValueAtDate
   */
  public Object getValueAtTime( int t )
  {
    
    Date d = new Date(t * 1000);
    return getValueAtDate( d );
    
  }
  
  
  /** 
   * Get the history as a String.
   */
  public String showHistory () 
  {
    int l = 0; // will be the same for both arrays
    String info = "";
    String vals = "";
    
    l = timeStamps.size() ;
    int	historyCount = timeStamps.size();
    
    info = "History Spec= history_count="+ historyCount + 
      " max_count=" + maxCount +
      " max_age="+ ( maxAge  * 1000) + "ms    "+ 
      " min_interval=" + minInterval;
    
    
    if ( l > 0 ){
      for ( int i = 0 ; i < l ; i++)
	vals = vals + " : @t= {" + timeStamps.elementAt(i) + "} = " + historicalValues.elementAt(i);
      
    }
    
    return info + vals;
    
  }

  /**
   * Return History information as a String.
   */
  @Override
  public String toString()
  {
    return showHistory();
  }
  
  
  /**
   * This gets the history at the specified datapoint.
   *
   * @param index The datapoint index
   */
  public Object getHistoryDataPoint(int index)
  {
    return historicalValues.elementAt( index );
  }
  
  
  
  /** 
   * Get the history information as an encoded array.
   */
   Object[] getHistory () {
    Object[] history;
    // thats the data, + the timestamps + the spec
    
    int	historyCount = timeStamps.size();
    
    Object[] g2HistoricalValues =new Object[historyCount];
    Date date;
    Double[] g2TimeStamps = new Double[historyCount];
    
    if (historyCount > 0 ){

	System.out.println("*-before remove JAVA-*  HistorySpec (Vectored)" + showHistory());
      
      removeOldHistory();
      
      history = new Object[ 7 ];
      
      history[0] = historyCount;
      history[1] = maxCount;
      history[2] = maxAge;		
      history[3] = minInterval;
      history[4] = historyType;
      
      // collect the time stamps and data
      
      for (int i = 0; i < historyCount; i++){
	Date tempDate = (Date)timeStamps.elementAt(i);
	g2TimeStamps[ i ] =  new Double(tempDate.getTime()/1000);
	g2HistoricalValues[i] = (Object) historicalValues.elementAt(i);
      }
      
      history[ 5 ] = g2TimeStamps;
      history[ 6 ] = g2HistoricalValues;

	  System.out.println("*-get end JAVA-*  HistorySpec (Vectored)" + showHistory());
      
      return history;
      
    }
    else // there is no history currently associated
      return null;
  }
  
  
  
  
  
  /** 
   * Set the history size
   *
   
   *@param	int max_count	,
   *@param	int max_age,		
   *@param	int min_interval,
   *@param	class history_class
   */
  public void setHistory (  int max_count	,
			    int max_age,		
			    int min_interval,
			    Class history_type) 
  {
    maxCount = java.lang.Math.max(0,max_count);
    maxAge= java.lang.Math.max( 0,max_age);
    minInterval= java.lang.Math.max( 0, min_interval);
    historyType = history_type;
  }
  
  
  
  
  /** 
   * Set the history size
   *
   *@param 	double[] timestamps, 
   *@param	Object[] values , 
   *@param	int max_count	,
   *@param	int max_age,		
   *@param	int min_interval,
   *@param	int history_type
   */
  public void setHistory (	double[] timestamps , 
				Object[] values , 
				int max_count	,
				int max_age,		
				int min_interval,
				Class history_type) 
  {
    
    int  nbOfDataPoints = values.length; // should == history_count
    int historyCount = java.lang.Math.max(0,nbOfDataPoints);
  
    setHistory(  max_count	,
		 max_age,		
		 min_interval,
		 history_type);
    
   
    
    timeStamps = new Vector( nbOfDataPoints) ;
    historicalValues = new Vector( nbOfDataPoints );
    
    // convert G2 time to java time
    for (int i = 0 ; i < nbOfDataPoints ;i++){
      historicalValues.addElement(values[i]);
      timeStamps.addElement(  new java.util.Date(new Double(timestamps[i] * 1000).longValue()));
      
    }
    // make certain the vectors are as small as need be
    // because the vector size is used elseware to set history_count
    timeStamps.trimToSize();
    historicalValues.trimToSize() ;

	 System.out.println("*-JAVA-*  HistorySpec (Vectored)" + showHistory());
    
  }
  

  /**
   * Prints the contents of the HistorySpec to stdout. Useful for debugging.
   */
  public void doprint () {
    System.out.println("***  HistorySpec (Vectored)" + showHistory());
    System.out.flush ();
  }
  
}



