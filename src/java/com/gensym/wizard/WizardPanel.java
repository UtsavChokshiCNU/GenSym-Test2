package com.gensym.wizard;

import java.awt.Panel;
import java.awt.Insets;
import java.awt.Font;
import java.awt.BorderLayout;
import java.awt.Label;

public class WizardPanel extends Panel
{
    protected String title;
    protected Label textLabel;

    public WizardPanel(String prompt)
    {
      setLayout(new BorderLayout(0, 5));

      if (prompt != null) {
        textLabel = new Label (prompt, Label.CENTER); 
        Font font = new Font("TimesRoman", Font.PLAIN, 14);
        textLabel.setFont(font);
        add(textLabel, "North");
        title = prompt;
      }          
    }

    @Override
    public Insets getInsets () {
      return new Insets (15, 20, 15, 20);
    }

    public String getTitle() {
      return title;
    }

    public void setTitle(String title)
    {
        this.title = title;
        if (textLabel != null)
          textLabel.setText(title);
        return;
    }
}
