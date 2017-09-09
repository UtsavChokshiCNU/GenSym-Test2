package com.gensym.editor.icon.tools;

import com.gensym.editor.icon.shapes.IconImage;
import java.awt.*;
import java.awt.event.*;
import com.gensym.editor.icon.core.ToolContainer;
import java.lang.Math;
import java.net.URL;
import com.gensym.editor.icon.core.FileLocater;

/**
 */
public class IconImageTool extends IconRectangleTool
{
  private FileLocater fileLocater;
  public IconImageTool (ToolContainer parent, FileLocater fileLocater)
  {
    super(parent);
    this.fileLocater = fileLocater;
  }

  @Override
  public void mouseReleased(MouseEvent e)
  {
    if (e.isPopupTrigger()) {
      super.mouseReleased(e);
      return;
    }
     Point p = e.getPoint();
     int x = p.x;
     int y = p.y;

     if (mouse_is_down) {
       mouse_is_down = false;
       //ExtensionFileFilter filter = new ExtensionFileFilter();
       //filter.addExtension("jpg");
       //filter.addExtension("gif");
       //filter.setDescription("JPG & GIF Images");
       URL url = fileLocater.getFile(null);
       Image image = null;
       if (url != null) {
	 image = Toolkit.getDefaultToolkit().getImage(url);
	 IconImage elt = new IconImage(url.toString(),
				       image,
				       Math.min(x,start_x),
				       Math.min(y,start_y),
				       Math.abs(x - start_x)+1 , 
				       Math.abs(y - start_y)+1);
	 parent.addElement(elt);	 
       } 
     }
  }

}


