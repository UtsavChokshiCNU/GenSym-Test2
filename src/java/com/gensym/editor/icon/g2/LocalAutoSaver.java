package com.gensym.editor.icon.g2;

import com.gensym.editor.icon.core.Savable;
import com.gensym.editor.icon.core.ObjectChangedListener;
import com.gensym.util.Structure;
import com.gensym.editor.icon.core.IconFormat;
import com.gensym.message.Trace;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.io.File;
import java.io.IOException;
import com.gensym.files.LocalFile;

class LocalAutoSaver implements Savable
{
  private LocalFile file;
  
  LocalAutoSaver(LocalFile file) {
    this.file = file;
  }

  @Override
  public Savable getLastLocation() {
    return this;
  }

  @Override
  public String getLastLocationTitle() {
    return file.getPath();
  }
  
  @Override
  public boolean save(Object description) {
    if (file != null) {
      saveToLocalFile(description, file);
      return true;
    }
    return false;
  }

  private void saveToLocalFile(Object contents, LocalFile file)
  {
    try   {
      OutputStream os = file.getOutputStream();
      ObjectOutputStream oos = new ObjectOutputStream(os);
      //oos.writeObject(new Integer(formatVersion);
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
  }

  @Override
  public void removeObjectChangedListener(ObjectChangedListener objectChangedListener) {
  }
  
  
}
