package com.gensym.shell.dialogs;

import java.awt.Frame;
import com.gensym.ntw.util.LoadSaveKBTools;
import com.gensym.ntw.util.uitools.ModuleKBTools;
import com.gensym.util.Symbol;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.classes.Module;
import com.gensym.dlg.ErrorDialog;
import com.gensym.dlg.InputDialog;
import com.gensym.ntw.TwAccess;
import com.gensym.classes.Kb;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.ModuleInformation;
import com.gensym.util.Sequence;

public class NewModuleDialog extends InputDialog {

  private static Resource i18n = Resource.getBundle("com/gensym/shell/commands/Messages");
  private TwAccess connection;
  private ModuleInformation parentModule;
  
  public NewModuleDialog(Frame frame, TwAccess connection) {
    super(frame, i18n.getString("NewModuleTitle"), true,  
	  new String[] {i18n.getString("NewModuleNamePrompt"),
			  i18n.getString("RequiredModulesPrompt")}, 
	  new String[] {"",""}, null);
    this.connection = connection;
  }

  public NewModuleDialog(Frame frame, TwAccess connection, ModuleInformation parentModule) {
    this(frame, connection);
    this.parentModule = parentModule;
  }  

  public void saveResults() {
    try {
      String[] results = getResults();
      String name = results[0].trim();
      if (name != "") {
	Symbol moduleName_ = Symbol.intern(results[0].toUpperCase());
	Kb kb = connection.getKb();
	Module module = kb.getModule(moduleName_);
	if (module == null) {
	  LoadSaveKBTools.createModule(connection, moduleName_);
	  if (parentModule != null) {
	    Sequence requiredModules = parentModule.getDirectlyRequiredModules();
	    requiredModules.addElement(moduleName_);
	    parentModule.setDirectlyRequiredModules(requiredModules);
	  }
	  String requiredModules = results[1];
	  if (!"".equals(requiredModules)) {
	    module = kb.getModule(moduleName_);
	    ModuleInformation moduleInfo = module.getModuleInformation();	    
	    //moduleInfo.setDirectlyRequiredModules();
	  }
	} else {
	  new ErrorDialog(null, i18n.getString("Error"), true, 
			  i18n.getString("ModuleAlreadyExists"), 
			  null).setVisible(true);
	}
      }
    } catch (G2AccessException gae) {
      Trace.exception(gae);
      if (gae.getMessage() != null)
	new ErrorDialog (null, i18n.getString("Error"), true, 
			 gae.getMessage(), null).setVisible(true);
    }
  }
}
