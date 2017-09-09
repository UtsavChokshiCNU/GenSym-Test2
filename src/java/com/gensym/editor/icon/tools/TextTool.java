package com.gensym.editor.icon.tools;

import java.awt.*;
import java.awt.event.*;
import java.lang.Math;
import javax.swing.JTextField;
import javax.swing.JComboBox;
import com.gensym.editor.icon.shapes.IconText;
import com.gensym.editor.icon.shapes.IconElement;
import com.gensym.editor.icon.core.ToolContainer;
import com.gensym.editor.icon.core.IconEditorCanvas;
import com.gensym.editor.icon.core.Evaluator;
import com.gensym.editor.icon.dlgs.TextDialog;

/**
 */
public class TextTool extends ChangeTool
  implements MouseListener, MouseMotionListener
{

  private IconText iconText;
  private int x, y;
  
  public TextTool (ToolContainer parent)
  {
    super(parent);
    listenerTypes = MOUSELISTENER | MOUSEMOTIONLISTENER ;
  }

  @Override
  public void mouseReleased(MouseEvent e) {
    if (e.isPopupTrigger()) {
      super.mouseReleased(e);
      return;
    }
    Point p = e.getPoint();
    x = p.x;
    y = p.y;

    createIconText();
    Evaluator evaluator = iconText.getEvaluator();
    evaluator.getElementEditor(((IconEditorCanvas)parent).getIconEditor(), (IconElement)iconText, (IconEditorCanvas)parent).setVisible(true);
  }

  private void createIconText() {
    iconText = new IconText("", new Font("sansserif", Font.PLAIN, 14), x, y);
    parent.addElement(iconText);
  }
  

}

