package com.gensym.beaneditor;

import java.awt.*;
import javax.swing.JComponent;
import java.util.Hashtable;

class PaletteFrame extends Dialog
{
    boolean alreadyShown;
    private static Hashtable paletteTable = new Hashtable();

    PaletteFrame(EditorFrame editorFrame, G2JarInfo g2JarInfo, String name)
    {
        super(editorFrame);
        alreadyShown = false;
        BeanPalette beanPalette = new BeanPalette(name, 3);
        String classes[] = new String[g2JarInfo.getCount()];
        for (int i = 0; i < g2JarInfo.getCount(); i++)
            classes[i] = g2JarInfo.getName(i);
        BeanCreator beanCreator = new BeanCreator(classes, g2JarInfo.getClassLoader());
        beanPalette.add(beanCreator);
        setTitle(name);
        setName(name);
        add(beanPalette, "Center");
        setSize(beanPalette.getPreferredSize());
        setBackground(Color.lightGray);
	paletteTable.put(beanPalette, this);
    }

  static PaletteFrame getPaletteFrame(BeanPalette palette){
    return (PaletteFrame)paletteTable.get(palette);
  }

}
