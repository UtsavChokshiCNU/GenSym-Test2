/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.License.java
 *   
 *   Author: Allan Scott
 */
package com.gensym.com;

import java.io.Serializable;

public class License implements Serializable
{
  static final long serialVersionUID = 3041805874309115950L;
  
  private String licenseKey;
  
  public License(String licenseKey)
  {
    this.licenseKey = licenseKey;
  }

  public String getLicenseKey()
  {
      return licenseKey;
  }
}
