package com.gensym.editor.icon.g2;

import com.gensym.editor.icon.shell.IconEditor;
import java.awt.Component;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import com.gensym.core.ExitThread;
import javax.swing.UIManager;
import javax.swing.JLabel;
import javax.swing.JTextField;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.editor.icon.core.Parameter;
import com.gensym.editor.icon.core.LayerListener;
import com.gensym.editor.icon.core.Layer;
import com.gensym.wksp.SystemMenuChoiceCommands;
import com.gensym.editor.icon.core.IconEditorCanvas;

public class G2IconEditor extends IconEditor {
  private JTextField nameField = new JTextField();
  private static final Symbol WIDTH_ = Symbol.intern ("WIDTH"),
    HEIGHT_ = Symbol.intern ("HEIGHT");

  public G2IconEditor() {
    super();
    modifyStatusPanel();
    layerAdapter = new LayerAdapter();
  }
  
  public static void main(String[] commandLine)
  {
    com.gensym.ui.LookAndFeel.setUseSnappyLookAndFeel(true);    
    class WindowExiter extends WindowAdapter
    {
      @Override
      public void windowClosing(WindowEvent e) {
	ExitThread.exit();
      }      
    }
    
    try {
      UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
    } catch (Exception e) {
    }
    IconEditor app = new G2IconEditor();
    app.setDefaultIconFormat(new com.gensym.editor.icon.g2.G2IconFormat());
    app.setIconFinder(new com.gensym.editor.icon.g2.G2IconDescriptionFinder());
    app.setIconSaver(new com.gensym.editor.icon.g2.G2IconDescriptionSaver());
    Parameter[] vars = new Parameter[2];
    vars[0] = new Parameter("WIDTH", Integer.class,new Integer(50));
    vars[1] = new Parameter("HEIGHT", Integer.class,new Integer(50));
    app.setDefaultEvaluator(new G2ExpressionEvaluator(vars));
    app.addWindowListener(new WindowExiter());
    app.setVisible(true);
  }

  private void modifyStatusPanel() {
    JLabel nameLabel = new JLabel("Region name: ");
    nameField.setColumns(15);
    nameField.addActionListener(new NameAdapter());
    statusPanel.add(nameLabel, 1);
    statusPanel.add(nameField, 2);
  }

  //For jdk1.2 compilation
  private IconEditorCanvas getCurrentCanvas() {
    return currentCanvas;
  }

  public class NameAdapter implements ActionListener {
    @Override
    public void actionPerformed(ActionEvent e) {
      if (e.getSource() == nameField) {
	getCurrentCanvas().getCurrentLayer().setRegionName(nameField.getText());
	getCurrentCanvas().setHasChanged(true);
      }
    }
  }
  
  public class LayerAdapter extends IconEditor.LayerAdapter {
    @Override
    public void layerSelected(Layer layer) {
      nameField.setText(layer.getRegionName());
      super.layerSelected(layer);
    }
  }
}
