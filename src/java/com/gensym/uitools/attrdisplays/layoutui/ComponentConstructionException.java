package com.gensym.uitools.attrdisplays.layoutui;

public class ComponentConstructionException extends Exception {
  public  ComponentConstructionException(String msg) {
    super(msg);
  }

  public  ComponentConstructionException(Exception nestedException) {
    super(nestedException.getMessage());
  }  
}
