package com.gensym.demos.g2studiosample.util;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.JLabel;
import javax.swing.JTabbedPane;
import com.gensym.uitools.utils.Preferences;
import com.gensym.uitools.utils.MultiEditPanel;
import java.awt.Dimension;
import java.awt.Component;

public class PreferencesPanel extends JTabbedPane {
  private Preferences preferences;
  private MultiEditPanel generalPanel,proxiesPanel;
  private String[] keys;

  public PreferencesPanel(Preferences preferences) {
    this.preferences = preferences;
    keys = preferences.getPublicKeys();
    addTab("General", (generalPanel = createGeneralPreferencePanel()));
    addTab("Proxies", (proxiesPanel = createProxiesPreferencePanel()));        
    //addTab("Appearance", (generalPanel = createGeneralPreferencePanel()));    
    setPreferredSize(new Dimension(400,170));
  }

  private String getPreference(String key) {
    String value = preferences.getPreference(key);
    if (value == null)
      value = "";
    return value;
  }
  
  private MultiEditPanel createGeneralPreferencePanel() {
    int count = keys.length;
    String[] labels = new String[count];
    String[] values = new String[count];
    for (int i=0;i<count;i++) {
      String key = keys[i];
      labels[i] = preferences.getPrettyKeyName(key);
      values[i] = preferences.getPreference(key);
      if (values[i] == null) values[i] = "";
    }
    MultiEditPanel mep = new MultiEditPanel(labels, values);
    Component[] comps = mep.getComponents();
    for (int i=0;i<comps.length;i++) 
      comps[i].setFont(com.gensym.uitools.utils.FontUtil.sanserifPlain11);
    return mep;
  }

  private MultiEditPanel createProxiesPreferencePanel() {
    MultiEditPanel mep = new MultiEditPanel
      (new String[] {"Internet proxy", "G2 middle tier proxy"},
      new String[] {"",""});
    Component[] comps = mep.getComponents();
    for (int i=0;i<comps.length;i++) 
      comps[i].setFont(com.gensym.uitools.utils.FontUtil.sanserifPlain11);
    return mep;
  }
  
  public void save() {
    String[] generalResults = generalPanel.getResults();
    for (int i=0;i<keys.length;i++) 
      preferences.setPreference(keys[i], generalResults[i]);
  }
  
}
