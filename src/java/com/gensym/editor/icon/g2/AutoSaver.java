package com.gensym.editor.icon.g2;

import com.gensym.editor.icon.core.Savable;
import com.gensym.editor.icon.core.ObjectChangedListener;
import com.gensym.classes.ClassDefinition;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Structure;
import com.gensym.editor.icon.core.IconFormat;

class AutoSaver implements Savable
{
  private ClassDefinition def;
  AutoSaver(ClassDefinition def) {
    this.def = def;
  }

  @Override
  public Savable getLastLocation() {
    return this;
  }

  @Override
  public String getLastLocationTitle() {
    try {
      return def.getClassName().toString();
    } catch (G2AccessException g2ae) {
      return "";
    }
  }
  
  @Override
  public boolean save(Object description) {
    if (def != null) {
      try {
	def.setIconDescription((Structure)description);
	return true;
      } catch (G2AccessException g2ae) {
	System.out.println("Couldn't set ID " + g2ae);
      }
    }
    return false;
  }

  @Override
  public IconFormat getIconFormat() {
    return new G2IconFormat(def);
  }
  
  @Override
  public void addObjectChangedListener(ObjectChangedListener objectChangedListener) {
    /*try {
      def.addItemListener(new G2ItemChangedAdapter(objectChangedListener));
    } catch (G2AccessException g2ae) {
      System.out.println(g2ae);
    }
    */
  }

  @Override
  public void removeObjectChangedListener(ObjectChangedListener objectChangedListener) {
  }
  
  
}
