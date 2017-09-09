package com.gensym.demos.g2studiosample;

import java.io.File;
import com.gensym.uitools.utils.AbstractPreferences;

public class G2StudioPreferences extends AbstractPreferences {
  private static String preferenceFileName = "g2studiopreferences.txt";
  private static String studioPreferencesFileLocation
  = System.getProperty("user.home")+File.separator+preferenceFileName;
  public static String HOME_PAGE = "HomePage";
  public static String DEFAULT_USER_NAME = "Default user name";
  public static String DEFAULT_USER_MODE = "Default user mode";
  public static String DEFAULT_USER_PASSWORD = "Default user password";
  public static String DEFAULT_OK_FILE = "Default ok file";
  public static String MAXIMIZED = "Launch application maximized";
  public static String PLUGINS = "plugins";  

  public G2StudioPreferences() {
    super(studioPreferencesFileLocation);
  }
  
  @Override
  public void setPreference(String key, String value) {
    if (!HOME_PAGE.equals(key))
      value = preventEmptyString(value);
    else if (value == null)
      value = "";
    super.setPreference(key, value);
  }

  @Override
  public String[] getPublicKeys() {
    return new String[] {HOME_PAGE, DEFAULT_USER_NAME, DEFAULT_USER_MODE, DEFAULT_USER_PASSWORD};    
  }

  @Override
  public String[] getKeys() {
    return new String[] {HOME_PAGE, DEFAULT_USER_NAME, DEFAULT_USER_MODE, DEFAULT_USER_PASSWORD, PLUGINS};    
  }  
  
  @Override
  public String getPrettyKeyName(String key) {
    return key;//i18n
  }

  private static final String preventEmptyString(String str) {
    if (str != null && str.trim().equals(""))
      return null;
    else
      return str;
  }
  
}
