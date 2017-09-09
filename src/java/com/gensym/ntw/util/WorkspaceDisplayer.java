
package com.gensym.ntw.util;

import com.gensym.classes.KbWorkspace;
import com.gensym.util.Structure;
import com.gensym.ntw.TwConnection;

public interface WorkspaceDisplayer {

  public boolean displayWorkspace (TwConnection cxn,
				   KbWorkspace wksp,
				   Structure showingParticulars);
  
  public boolean removeWorkspace (TwConnection cxn,
				  KbWorkspace wksp,
				  Structure hideParticulars);

}
