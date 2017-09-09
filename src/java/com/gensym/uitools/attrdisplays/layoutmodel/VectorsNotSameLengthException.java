package com.gensym.uitools.attrdisplays.layoutmodel;

public class VectorsNotSameLengthException extends Exception {
  public  VectorsNotSameLengthException(String msg) {
    super(msg);
  }

  public  VectorsNotSameLengthException(Exception nestedException) {
    super(nestedException.getMessage());
  }  
}
