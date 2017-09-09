package com.gensym.editor.icon.g2;

import com.gensym.editor.icon.core.Savable;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.classes.ClassDefinition;
import com.gensym.classes.ObjectDefinition;
import com.gensym.classes.KbWorkspace;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2ConnectionInfo;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwConnectionInfo;
import com.gensym.ntw.util.OpenFileFilter;
import com.gensym.files.URLFile;
import javax.swing.JFileChooser;
import java.awt.Rectangle;
import java.io.File;
import com.gensym.files.LocalFile;

public class G2ObjectDefinitionLocater 
{
  public static OpenFileFilter gidFileFilter
  = new OpenFileFilter("gid", "G2 Icon Descriptor Files");
  private static final Symbol
  CLASS_DEFINITION_ = Symbol.intern ("CLASS-DEFINITION"),
    KB_WORKSPACE_ = Symbol.intern ("KB-WORKSPACE");
  
  protected Object lastLocation;
  private static final int SUCCESS = 0;
  
  static {
    com.gensym.net.g2.G2ProtocolRegistry.loadInterpreters();
  }

  protected Object getLocation() throws G2AccessException {
    ClassInstancesFileSystemView fsv =
      new ClassInstancesFileSystemView("g2:",
				       CLASS_DEFINITION_,
				       Symbol.intern("CLASS-NAME"));
    JFileChooser fileChooser = new JFileChooser(fsv);
    fileChooser.addChoosableFileFilter(gidFileFilter);
    fileChooser.setFileFilter(gidFileFilter);
    if (fileChooser.showDialog(null, "Choose") != SUCCESS)
      return null;
    File file = fileChooser.getSelectedFile();
    if (file instanceof ItemFile) {
      ItemFile classDefinitionFile = (ItemFile)file;
      ClassDefinition def = null;
      try {
	def = (ClassDefinition)classDefinitionFile.getItem(CLASS_DEFINITION_);
      } catch (G2AccessException g2ae) {
	def = (ClassDefinition)
	  classDefinitionFile.getConnectionForItem().createItem(CLASS_DEFINITION_);
	def.setClassName(Symbol.intern(classDefinitionFile.getName().toUpperCase()));
	
	//need to show the ws containment in the file chooser and place the
	//new definition accordingly
	KbWorkspace ws = (KbWorkspace)
	  classDefinitionFile.getConnectionForItem().createItem(KB_WORKSPACE_);
	if (ws != null) {
	  Rectangle bounds = ws.getBounds();
	  def.transferTo(ws,bounds.x+bounds.width/2,bounds.y+bounds.height/2);
	}
      }
      return def;
    } else {
      return file;
    }
  }

  public Savable getLastLocation() {
    if (lastLocation instanceof ClassDefinition) 
      return new AutoSaver((ClassDefinition)lastLocation);
    else if (lastLocation instanceof LocalFile) {
      return new LocalAutoSaver((LocalFile)lastLocation);
    } else
      return null;
  }
  
  public String getLastLocationTitle() {
    if (lastLocation instanceof ClassDefinition) {    
      try {
	if (lastLocation != null)
	  return ((ClassDefinition)lastLocation).getClassName().toString();
	else
	  return "";
      } catch (G2AccessException g2ae) {
	return "";
      }
    } else if (lastLocation instanceof LocalFile) {
      return ((LocalFile)lastLocation).getPath();//getName();
    } else
      return lastLocation.toString();
  }
  
}
    
