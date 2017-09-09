package com.gensym.uitools.utils;

import java.util.Hashtable;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.File;
import java.io.IOException;
import com.gensym.message.Trace;

public abstract class AbstractPreferences implements Preferences 
{
  private static final String PREFERENCE_SEPARATOR  = "\n";
  private static final String KEY_SEPERATOR = "=";  
  private String preferencesFileLocation;
  private Hashtable values = new Hashtable();  

  public AbstractPreferences(String preferencesFileLocation) {
    this.preferencesFileLocation = preferencesFileLocation;
  }

  @Override
  public String getPreference(String preferenceKey) {
    return (String)values.get(preferenceKey);
  }

  @Override
  public void setPreference(String key, String value) {
    if (value == null)
      values.remove(key);
    else
      values.put(key, value);
  }

  @Override
  public void load() {
    try {
      String prefs = loadData();
      if (prefs != null) {
	String[] keys = getKeys();
	for (int i=0;i<keys.length;i++) {
	  String key = keys[i];
	  setPreference(key, getPreference(prefs, key));
	}
      }
    } catch (IOException ex) {
      Trace.exception(ex);
    }
  }

  @Override
  public void save() {
    try {
      String[] keys = getKeys();
      FileWriter writer = new FileWriter(preferencesFileLocation);
      for (int i=0;i<keys.length;i++) {
	String key = keys[i];
	String value = getPreference(key);
	if (value != null)
	  writer.write(key+KEY_SEPERATOR+value+PREFERENCE_SEPARATOR);
      }
      writer.close();
    } catch (IOException ex) {
      Trace.exception(ex);
    }
  }
  
  private String getPreference(String prefs, String preferenceKey) {
    preferenceKey+=KEY_SEPERATOR;
    int startIndex = prefs.indexOf(preferenceKey);
    if (startIndex < 0)
      return null;
    else {
      startIndex+=preferenceKey.length();
      int endIndex = prefs.indexOf(PREFERENCE_SEPARATOR, startIndex);
      return prefs.substring(startIndex, endIndex);
    }
  }
  
  private String loadData() throws IOException {
    File file = new File(preferencesFileLocation);
    if (file.exists()) {
      FileReader reader = new FileReader(file);
      int count = (int)file.length();
      char[] chars = new char[count];
      for (int i=0;i<count;i++)
	chars[i]=(char)reader.read();
      reader.close();
      return new String(chars);
    }
    return null;
  }
  
}
