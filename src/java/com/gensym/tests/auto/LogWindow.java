package com.gensym.tests.auto;

import java.awt.Button;
import java.awt.Color;
import java.awt.Frame;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.awt.TextArea;
import java.awt.event.*;

public class LogWindow extends Frame{
  private Button saveBtn, dsmsBtn, clearBtn;
  private TextArea txtArea;

  public LogWindow() {
    GridBagLayout gridBagLayout = new GridBagLayout();
    GridBagConstraints gridBagConstraints = new GridBagConstraints();
    setLayout(gridBagLayout);

    setBackground(Color.lightGray);

		gridBagConstraints.weighty = 1.0;    
    gridBagConstraints.weightx = 1.0;
    gridBagConstraints.gridwidth = GridBagConstraints.REMAINDER;
    gridBagConstraints.gridheight = GridBagConstraints.RELATIVE;
    gridBagConstraints.fill = GridBagConstraints.BOTH;
    gridBagConstraints.insets = new Insets(5, 5, 15, 5);
    
    txtArea = new TextArea();
    gridBagLayout.setConstraints(txtArea, gridBagConstraints);
    add(txtArea);

    gridBagConstraints.fill = 0;
    gridBagConstraints.weightx = 0.0;
		gridBagConstraints.weighty = 0.0;    
    gridBagConstraints.gridwidth = 1;
    gridBagConstraints.insets = new Insets(15, 5, 5, 5);

    clearBtn = new Button("Clear");
    clearBtn.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
        clearText();
      }
    });
    gridBagLayout.setConstraints(clearBtn, gridBagConstraints);
    add(clearBtn);

    saveBtn = new Button("Save to File...");
    saveBtn.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
      }
    });
    saveBtn.setEnabled(false);
    gridBagLayout.setConstraints(saveBtn, gridBagConstraints);
    add(saveBtn);

    dsmsBtn = new Button("Dismiss");
    dsmsBtn.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
        hideLog();
      }
    });
    gridBagLayout.setConstraints(dsmsBtn, gridBagConstraints);
    add(dsmsBtn);

		addWindowListener (new WindowAdapter () {
		  @Override
		  public void windowClosing (WindowEvent we) {
		    dispose(); 
			}
		});
  }

  public void hideLog() {
    dispose();
  }

  public void setText(String txt) {
    txtArea.append(txt);
  }

  public void append(String txt) {
    txtArea.append(txt);
  }

  public void clearText() {
    txtArea.setText("");
  }

  public static void main (String[] args) {
    LogWindow lw = new LogWindow();

    lw.setVisible(true);
    lw.pack();
    lw.append("appended error");
  }
}
