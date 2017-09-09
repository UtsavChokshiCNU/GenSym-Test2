package com.gensym.core;

class PropertiesFileInfo {

  private String name;
  private String value;
  private String annotation;

  PropertiesFileInfo (String name, String value, String annotation) {
    this.name = name;
    this.value = value;
    this.annotation = annotation;
  }

  PropertiesFileInfo (String key, String value) {
    this.name = name;
    this.value = value;
  }

  public String getName () {
    return this.name;
  }

  public String getValue () {
    return this.value;
  }

  public String getAnnotation () {
    return this.annotation;
  }
}
