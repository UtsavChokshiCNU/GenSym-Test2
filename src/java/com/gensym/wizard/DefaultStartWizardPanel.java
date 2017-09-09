package com.gensym.wizard;

import java.awt.Panel;
import java.awt.Insets;
import java.awt.BorderLayout;
import java.awt.Label;
import java.awt.GridLayout;
import java.awt.Font;

public class DefaultStartWizardPanel extends StartWizardPanel
{

  public DefaultStartWizardPanel(String title, 
                                 WizardPanel[] panels)
  {
    super(title);
    int length = panels.length;

    Panel contents = new Panel();
    contents.setLayout(new GridLayout(length, 1));
    for (int i = 0 ; i < length; i++) 
    {
      String title2 = panels[i].getTitle();
      Label newLabel= new Label("Step "+ (i + 1) + " : " +
            title2);
      newLabel.setFont(new Font("TimesRoman", Font.BOLD, 16));
      contents.add(newLabel);
    }
    add(contents, "South");
  }
}
