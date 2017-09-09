package com.gensym.nols.chart.scatter;

public class ProjectionException extends Exception {

  public ProjectionException (String ErrorDetails) {
    super(ErrorDetails);
  }

  @Override
  public String toString () {
	return (""+ super.toString());
  }
  
}
