package com.gensym.editor.icon.g2;

import com.gensym.editor.icon.core.Savable;
import com.gensym.editor.icon.core.ObjectChangedListener;
import com.gensym.editor.icon.core.IconFormat;
import com.gensym.util.Structure;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.ClassDefinition;
import com.gensym.message.Trace;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.io.File;
import java.io.IOException;
import com.gensym.files.LocalFile;

public class G2IconDescriptionSaver extends G2ObjectDefinitionLocater
implements Savable
{
  
  @Override
  public boolean save(Object description) {
    try {
      lastLocation = getLocation();
      if (lastLocation instanceof ClassDefinition) {
	((ClassDefinition)lastLocation).setIconDescription((Structure)description);
	return true;
      } else if (lastLocation instanceof LocalFile) {
	saveToLocalFile(description, (LocalFile)lastLocation);
	return true;
      }
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
    return false;
  }

  private void saveToLocalFile(Object contents, LocalFile file)
  {
    //String formatName = getIconFormat().getFormatName();
    try   {
      OutputStream os = file.getOutputStream();
      ObjectOutputStream oos = new ObjectOutputStream(os);
      oos.writeInt(G2IconFormat.g2FormatVersion);
      oos.writeInt(G2IconFormat.t2FormatVersion);
      oos.writeObject(contents);
      oos.flush();
      os.close();
    } catch (IOException ex) {
      Trace.exception(ex);
    }
  }
  
  @Override
  public IconFormat getIconFormat() {
    return new G2IconFormat();
  }
  
  @Override
  public void addObjectChangedListener(ObjectChangedListener objectChangedListener) {
    /*if (lastLocation instanceof ClassDefinition) {
      try {
	((ClassDefinition)lastLocation).addItemListener
	  (new G2ItemChangedAdapter(objectChangedListener));
      } catch (G2AccessException g2ae) {
	System.out.println(g2ae);
      }
    }
    */
  }

  @Override
  public void removeObjectChangedListener(ObjectChangedListener objectChangedListener) {
  }
  
}
    
