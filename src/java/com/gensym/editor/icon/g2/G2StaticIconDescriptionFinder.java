package com.gensym.editor.icon.g2;

import com.gensym.jgi.G2AccessException;
import com.gensym.classes.ClassDefinition;
import com.gensym.files.LocalFile;


public class G2StaticIconDescriptionFinder extends G2IconDescriptionFinder 
{
  public G2StaticIconDescriptionFinder(ClassDefinition classDefinition) {
    lastLocation = classDefinition;
  }

  public G2StaticIconDescriptionFinder(LocalFile localFile) {
    lastLocation = localFile;
  }
  
  @Override
  protected Object getLocation() throws G2AccessException {
    return lastLocation;
  }

}

