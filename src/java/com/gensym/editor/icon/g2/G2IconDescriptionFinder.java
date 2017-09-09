package com.gensym.editor.icon.g2;

import com.gensym.editor.icon.core.Finder;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.ClassDefinition;
import com.gensym.classes.G2Definition;
import com.gensym.classes.ImplAccess;
import com.gensym.jgi.G2Access;
import java.util.Enumeration;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.message.Trace;
import java.io.ObjectInputStream;
import java.io.InputStream;
import java.io.File;
import java.io.IOException;
import com.gensym.files.LocalFile;
import com.gensym.dlg.MessageDialog;

public class G2IconDescriptionFinder extends G2ObjectDefinitionLocater
implements Finder {

  @Override
  public Object find() {
    Object description = null;
    String title = "untitled";
    try {
      lastLocation = getLocation();
      if (lastLocation instanceof ClassDefinition) {
	description = ((ClassDefinition)lastLocation).getIconDescription();
	if (description == null) {
	  Sequence cip = ((ClassDefinition)lastLocation).getClassInheritancePath();
	  if (cip != null) {
	    G2Access cxn = ((ImplAccess)lastLocation).getContext();
	    Enumeration e = cip.elements();
	    while(description == null && e.hasMoreElements()) {
	      Symbol defName = (Symbol)e.nextElement();
	      G2Definition def = cxn.getDefinition(defName);
	      description = def.getIconDescription();
	    }
	  }
	}
      } else if (lastLocation instanceof LocalFile) 
	description = loadFromLocalFile((LocalFile)lastLocation);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
    return description;
  }

  private String writeG2FormatVersion(int version) {
    int majorVersion = (int)version>>2;
    int minorVersion = (int)version>>1 - majorVersion*10;
    int revision = version - (majorVersion*100 + minorVersion*10);
    return "G2" + majorVersion + "." + minorVersion + "r" + revision;
  }

  private String writeT2FormatVersion(int version) {
    int majorVersion = (int)version>>2;
    int minorVersion = (int)version>>1 - majorVersion*10;
    int revision = version - (majorVersion*100 + minorVersion*10);
    return "T2" + majorVersion + "." + minorVersion + "r" + revision;
  }  
  
  private Object loadFromLocalFile(LocalFile file)
  {
    Object description = null;
    try   {
      InputStream is = file.getInputStream();
      ObjectInputStream ois = new ObjectInputStream(is);
      boolean unsupportedFormat = false;
      int g2FormatVersion=-1, t2FormatVersion=-1;
      try {
	g2FormatVersion = ois.readInt();
	t2FormatVersion = ois.readInt();
	if (g2FormatVersion != G2IconFormat.g2FormatVersion ||
	    t2FormatVersion != G2IconFormat.t2FormatVersion)
	  unsupportedFormat = true;
      } catch (IOException ex) {
	unsupportedFormat = true;
      }
      if (unsupportedFormat) {
	String message =
	  writeG2FormatVersion(g2FormatVersion) + "\n" +
	  writeT2FormatVersion(t2FormatVersion);
	(new MessageDialog(null, "Unsupported format", true,
			   message, null)).setVisible(true);
	return null;
      }
      description = ois.readObject();
      is.close();
      //ois.close();
    } catch (IOException ex) {
      Trace.exception(ex);
    } catch (ClassNotFoundException cnfe) {
      Trace.exception(cnfe);
    }
    return description;
  }
  
}

