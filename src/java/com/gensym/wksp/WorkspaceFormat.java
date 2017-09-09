package com.gensym.wksp;

import java.awt.print.PageFormat;

public class WorkspaceFormat extends PageFormat {

  double scale = 1;
  boolean scaleToFit;

  public WorkspaceFormat(){
  }

  public WorkspaceFormat(PageFormat pageFormat){
    this.setOrientation(pageFormat.getOrientation());
    this.setPaper(pageFormat.getPaper());
  }

  public double getScale(){
    if (scaleToFit)
      return 0;
    return scale;
  }

  public void setScale(double scale){
    if (scale > 0)
      this.scale = scale;
    else
      throw new IllegalArgumentException("scale must be greater than 0");
  }

  public boolean isScaleToFit(){
    return scaleToFit;
  }

  public void setScaleToFit(boolean scaleToFit){
    this.scaleToFit = scaleToFit;
  }

}
