package com.gensym.editor.icon.tools;

import java.awt.*;
import java.awt.event.*;
import java.lang.Math;
import com.gensym.editor.icon.core.Tool;
import com.gensym.editor.icon.core.ToolContainer;
import com.gensym.editor.icon.core.DrawElement;
import com.gensym.editor.icon.core.Fillable;
import com.gensym.editor.icon.core.IconEditorCanvas;
import com.gensym.editor.icon.shapes.IconElement;
import com.gensym.editor.icon.shapes.IconRectangle;
import com.gensym.editor.icon.shapes.IconImage;
import com.gensym.editor.icon.shapes.IconText;
import com.gensym.editor.icon.dlgs.ExpressionEditDialog;
import com.gensym.editor.icon.dlgs.TextDialog;
import com.gensym.editor.icon.core.Evaluator;
import javax.swing.JButton;

public class ChangeTool extends Tool
implements MouseListener, ActionListener
{
  private PopupMenu popup;
  private Component element;
  protected ToolContainer parent;
  private MenuItem fillOutlineMI;

  public ChangeTool (ToolContainer parent)
  {
    this.parent = parent;
    listenerTypes = MOUSELISTENER;
  }

  @Override
  public void registerListeners(ToolContainer canvas)
  {
    super.registerListeners(canvas);
    MenuItem mi;
    popup = new PopupMenu("Change");

    mi = new MenuItem("Delete");
    mi.addActionListener(this);
    popup.add(mi);
    

    fillOutlineMI = new MenuItem("Fill");
    fillOutlineMI.addActionListener(this);
    popup.add(fillOutlineMI);

    popup.addSeparator();
    
    mi = new MenuItem("Properties...");
    mi.addActionListener(this);
    popup.add(mi);    

    parent.add(popup);
           
  }

  @Override
  public void deregisterListeners(ToolContainer canvas)
  {
    super.deregisterListeners(canvas);
    parent.remove(popup);
  }

  @Override
  public void actionPerformed(ActionEvent e) 
  {
    String command = e.getActionCommand();
    if (command.equals("Delete")) {
      parent.removeElement(element);
    } else if (command.equals("Fill")) {
      ((Fillable)element).setFilled(true);
    } else if (command.equals("Outline")) {
      ((Fillable)element).setFilled(false);
    } else if (command.equals("Properties...")) {
      if (element instanceof IconElement)
	editElement((IconElement)element);
    }
  }

  private void editElement(IconElement element) {
    Evaluator evaluator = element.getEvaluator();
    TextDialog textDialog = null;
    if (evaluator == null) return;
    Container frame = parent;
    while (frame != null && !(frame instanceof Frame)) 
      frame = frame.getParent();
    if (!(frame instanceof Frame))
      frame = null;
    String[] labels = element.getExpressionLabels();
    int[] indices = element.getExpressionIndices();
    if (element instanceof IconText) 
      textDialog = evaluator.getElementEditor(((IconEditorCanvas)parent).getIconEditor(), element, (IconEditorCanvas)parent);
    if (labels != null && indices != null && textDialog == null)
      (new ExpressionEditDialog(element, labels, indices, evaluator,(Frame)frame)).setVisible(true);
    if (textDialog != null) textDialog.setVisible(true);
  }
  
  @Override
  public void Draw (Graphics g)
  {
  }


  @Override
  public void mouseClicked(MouseEvent e)
  {
    // System.out.println("click isPopupTrig="+e.isPopupTrigger());
  }


  @Override
  public void mousePressed(MouseEvent e)
  {
    Point p = e.getPoint();
    int x = p.x;
    int y = p.y;
    element = parent.findElement(x,y);
    if (element instanceof Fillable) {
      fillOutlineMI.setEnabled(true);
      if (((Fillable)element).isFilled())
	fillOutlineMI.setLabel("Outline");
      else
	fillOutlineMI.setLabel("Fill");
    } else {
      fillOutlineMI.setEnabled(false);
      fillOutlineMI.setLabel("Fill/Outline");
    }
    
  }
  

  @Override
  public void mouseReleased(MouseEvent e)
  {
    if (element != null)
    {
      Point p = e.getPoint();
      int x = p.x;
      int y = p.y;

      Component element_at_release = parent.findElement(x,y);

      if ((element == element_at_release) &&
	  e.isPopupTrigger())
	popup.show(parent, x, y);
    }
  }
 

  @Override
  public void mouseEntered(MouseEvent e)
  {
  }
   
  @Override
  public void mouseExited(MouseEvent e)
  {
  }

}

