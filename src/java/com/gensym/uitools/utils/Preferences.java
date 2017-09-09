package com.gensym.uitools.utils;

public interface Preferences {
  public String getPreference(String key);
  public void setPreference(String key, String value);
  public String[] getPublicKeys();
  public String[] getKeys();  
  public String getPrettyKeyName(String key);
  public void save();
  public void load();
}
