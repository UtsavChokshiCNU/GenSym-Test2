/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ModuleKBTools.java
 *
 */
package com.gensym.ntw.util.uitools;

import java.util.Vector;

import com.gensym.classes.Kb;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Module;
import com.gensym.classes.ModuleInformation;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Gateway;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.KbEvent;
import com.gensym.ntw.util.KbModuleListener;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.ntw.util.LoadSaveKBTools;

public abstract class ModuleKBTools {

  private static final Symbol MODULE_INFORMATION_ = Symbol.intern("MODULE-INFORMATION");
  private static final Symbol UNSPECIFIED_ = Symbol.intern("UNSPECIFIED");

  private static final int OK = 1;
  private static final int MODULE_REQUIRES_ITSELF = 2;

  public static boolean isModularized(TwAccess cxn) throws G2AccessException {
    //System.out.println("running isModularized");
    boolean isModularized = true;

    Kb kb = cxn.getKb();
    if (kb != null) {
      Module[] allMods = kb.getModules();

      Vector requiredModules = new Vector();
      Module topMod = kb.getTopLevelModule();
      if (topMod == null) {
	// this case did happen, my guess is that it's a timing issue with unnaming the top-level-mod
	isModularized = false;
      } else {
	Symbol name_ = topMod.getName();
	if (name_ != null) {
	  requiredModules.addElement(topMod);
	  ModuleKBTools.getLinearizedHierarchyForModule(cxn, topMod, requiredModules);
	
	  // compare linearized Vector with Module array for "unrequired" modules
	  for (int k=0; k<allMods.length; k++) {
	    if (!(requiredModules.contains(allMods[k])))
	      isModularized = false;
	  }
	} else {
	  // completely unmodularized
	  isModularized = false;
	}
      }
    }

    //System.out.println("isModularized? : "+isModularized);
    return isModularized;
  }

  /**
   * @param cxn The TwAccess connection for the G2 that is the target of this query
   * @param unrequiredModules A Vector that will contain the names, as Symbols, of the 
   * unrequired modules.
   * if the top-level-module is "unrequired", a place-holder of UNSPECIFIED_ will be 
   * inserted to represent the unnamed top-level-module.
   */
  public static void getUnrequiredModules(TwAccess cxn, Vector unrequiredModules) throws G2AccessException {
    //System.out.println("running getUnrequiredModules");
    if (!(isModularized(cxn))) {
      //System.out.println("kb is not modularized");
      Kb kb = cxn.getKb();
      Module topMod = kb.getTopLevelModule();
      Module[] allMods = kb.getModules();
      if (topMod == null || topMod.getName() == null) {
	//System.out.println("topLevelModule is un-named, return all modules");
	Symbol name_;
	for (int i=0; i<allMods.length; i++) {
	  name_ = allMods[i].getName();
	  name_ = (name_ != null ? name_ : UNSPECIFIED_);
	  unrequiredModules.addElement(name_);    
	}
      } else {
	//System.out.println("top-level-module is named: "+topMod.getName());
	Vector linearMods = new Vector();
	linearMods.addElement(topMod);
	getLinearizedHierarchyForModule(cxn, topMod, linearMods);
	Symbol name_;
	for (int j=0; j<allMods.length; j++) {
	  //name_ = allMods[j].getName();
	  //name_ = (name_ != null ? name_ : UNSPECIFIED_);
	  //if (!(linearMods.contains(name_)))
	  // unrequiredModules.addElement(name_);
	  if (!linearMods.contains(allMods[j])) {
	    name_ = allMods[j].getName();
	    name_ = (name_ != null ? name_ : UNSPECIFIED_);
	    unrequiredModules.addElement(name_);
	  }
	}
      }
    }
  } 

  /**
   * @param cxn The TwAccess connection 
   * @param module The Module to get the linearized hierarchy of
   * @param moduleVector A Vector of Module(s)
   */
  public static int getLinearizedHierarchyForModule(TwAccess cxn, Module module, Vector moduleVector) throws G2AccessException {
    Sequence modules = module.getRequiredModules(); // sequence of symbols

    // check for the case where a module requires itself, then return error immediately
    if (module.getName() != null && modules.contains(module.getName())) {
      return MODULE_REQUIRES_ITSELF;
    }

    Module mod;
    Sequence requiredModules;
    Kb kb = cxn.getKb();
    for (int i=0; i<modules.size(); i++) {
      mod = kb.getModule((Symbol)modules.elementAt(i));

      if (mod != null) {
	if (!(moduleVector.contains(mod))) {
	  moduleVector.addElement(mod);
	}
      
	requiredModules = mod.getRequiredModules();
	if (requiredModules.size() != 0)
	  getLinearizedHierarchyForModule(cxn, mod, moduleVector);
      }
    }

    return OK;
  }

  public static void getRequiringModules(TwAccess cxn, Symbol moduleName_, Vector requiringModules) throws G2AccessException {
    Kb kb = cxn.getKb();
    Module[] allMods = kb.getModules();
    ModuleInformation modInfo;
    Module mod;
    Symbol name_;
    for (int i=0; i<allMods.length; i++) {
      mod = allMods[i];
      name_ = mod.getName();
      if (name_ == null) {
	name_ = UNSPECIFIED_;
	modInfo = (ModuleInformation)((G2Gateway)cxn).getUniqueNamedItem(MODULE_INFORMATION_, MODULE_INFORMATION_);
      }
      else
	modInfo = mod.getModuleInformation();

      Sequence requiredModules = modInfo.getDirectlyRequiredModules();
      if (requiredModules.contains(moduleName_))
	requiringModules.addElement(name_);
    }
  }

  public static String getFileSpecificationForModule(TwAccess cxn, Symbol moduleName_) throws G2AccessException {
    String filespec = "";
    Kb kb = cxn.getKb();
    Module module = kb.getModule(moduleName_);
    ModuleInformation modInfo = module.getModuleInformation();
    String moduleFileName = (String)modInfo.getModuleFileName();
    if (moduleFileName == null)
      moduleFileName = moduleName_.toString() + ".KB";
    String defaultDir = (String)LoadSaveKBTools.defaultDirectory(cxn);
    filespec = defaultDir + moduleFileName;
    return filespec;
  }

  public static void renameModule(TwAccess cxn, Symbol fromModule_, Symbol toModule_) throws G2AccessException {
    Kb kb = cxn.getKb();
    Module module;
    if (fromModule_.equals(UNSPECIFIED_))
      module = kb.getTopLevelModule();
    else
      module = kb.getModule(fromModule_);
    if (fromModule_ != null)
      ModuleKBTools.renameModule(cxn, module, toModule_);
  }

  public static void renameModule(TwAccess cxn, Module module, Symbol newName_) throws G2AccessException {
   
    // 1. first: reassign all top-level workspaces
    KbWorkspace[] tlw = module.getTopLevelKbWorkspaces();
    for (int j=0; j<tlw.length; j++) {
      tlw[j].setModuleAssignment(newName_);
    }
    
    // 2. second: set the top-level-module att of the ModuleInformation to new name
    Symbol oldName_ = module.getName();
    ModuleInformation modInfo = module.getModuleInformation();
    modInfo.setTopLevelModule(newName_);

    // 3. third: fix the hierarchy, replacing "oldName_" with "newName_"
    if (oldName_ != null) {
      Kb kb = cxn.getKb();
      if (kb != null) {
	Module[] modules = kb.getModules();
	Sequence requiredModules;
	for (int i=0; i<modules.length; i++) {
	  modInfo = modules[i].getModuleInformation();
	  requiredModules = modInfo.getDirectlyRequiredModules();
	  if (requiredModules != null && requiredModules.size() > 0) {
	    if (requiredModules.contains(oldName_)) {
	      int index = requiredModules.indexOf(oldName_);
	      requiredModules.setElementAt(newName_, index);
	      modInfo.setDirectlyRequiredModules(requiredModules);
	    }
	  }
	}
      }
    }
  }

  private static Symbol moduleJustCreated_ = null;
  public static void executeInsertTopLevelModule(TwAccess cxn, String moduleName) throws G2AccessException {
    /*
     * 1. create new module "FOO"
     * 2. make "top" require "FOO"
     * 3. change all workspaces in "top" to "FOO"
     * 4. change "top" to applicationName
     * 5. make applicationName require "top"
     * 6. create new module "top"
     * 7. change all workspaces in "FOO" to "top"
     * 8. delete FOO
     * 9. remove FOO from applicationName's directly-required-modules att.
     */
    
    Kb kb = cxn.getKb();
    kb.addKbModuleListener(new KbModuleListener() {
      @Override
      public void receivedInitialModules (KbEvent e) {}
      @Override
      public void moduleDeleted (KbEvent e) {}
      @Override
      public void kbCleared (KbEvent e) {}
      @Override
      public void moduleNameChanged (KbEvent e) {}
      @Override
      public void moduleCreated (KbEvent e) {
	Module newModule = e.getModule();
	moduleJustCreated_ = newModule.getName();
      }
      @Override
      public void moduleDependencyChanged (KbEvent e) {}
      @Override
      public void topLevelWorkspaceAdded (KbEvent e) {}
      @Override
      public void topLevelWorkspaceDeleted (KbEvent e) {}
    });
    Module origTopMod = kb.getTopLevelModule();
    Symbol origTopModName_ = origTopMod.getName();
    KbWorkspace[] origTopModWorkspaces = origTopMod.getTopLevelKbWorkspaces();

    // 1. create new module "FOO"
    Symbol fooModule_ = Symbol.intern("FOOXYZ");
    LoadSaveKBTools.createModule(cxn, fooModule_);
    while ((moduleJustCreated_ == null) || (!(moduleJustCreated_.equals(fooModule_)))){}
    Module fooModule = kb.getModule(fooModule_);
    ModuleInformation fooModInfo = fooModule.getModuleInformation();
    fooModInfo.setDirectlyRequiredModules(origTopMod.getRequiredModules());

    // 2. make "top" require "FOO"
    ModuleInformation modInfo = (ModuleInformation)((G2Gateway)cxn).getUniqueNamedItem(MODULE_INFORMATION_, MODULE_INFORMATION_);
    Sequence requiredModules = modInfo.getDirectlyRequiredModules();
    if (!(requiredModules.contains(fooModule_))) {
      requiredModules.addElement(fooModule_);
      modInfo.setDirectlyRequiredModules(requiredModules);
    }

    // 3. change all workspaces in "top" to "FOO"
    for (int i=0; i<origTopModWorkspaces.length; i++) {
      origTopModWorkspaces[i].setModuleAssignment(fooModule_);
    }

    // 4. change "top" to moduleName
    Symbol userAppName_ = Symbol.intern(moduleName);
    modInfo.setTopLevelModule(userAppName_);

    // 5. make moduleName require origTopMod
    requiredModules = modInfo.getDirectlyRequiredModules();
    if (!(requiredModules.contains(origTopModName_))) {
      requiredModules.addElement(origTopModName_);
      modInfo.setDirectlyRequiredModules(requiredModules);
    }

    // 6. create new module origTopModName_
    LoadSaveKBTools.createModule(cxn, origTopModName_);
    while ((moduleJustCreated_ == null) || (!(moduleJustCreated_.equals(origTopModName_)))){}
    Module newOrigModule = kb.getModule(origTopModName_);
    ModuleInformation newOrigModInfo = newOrigModule.getModuleInformation();
    newOrigModInfo.setDirectlyRequiredModules(fooModule.getRequiredModules());

    // 7. change all workspaces in "FOO" to origTopModName_
    for (int j=0; j<origTopModWorkspaces.length; j++) {
      origTopModWorkspaces[j].setModuleAssignment(origTopModName_);
    }

    // 8. delete "FOO"
    LoadSaveKBTools.setDeleteAssociatedWorkspaces(Boolean.TRUE);
    LoadSaveKBTools.deleteModule(cxn, fooModule_);

    // 9. remove "FOO" from moduleName's directly-required-modules att.
    requiredModules = modInfo.getDirectlyRequiredModules();
    if (requiredModules.contains(fooModule_)) {
      requiredModules.removeElement(fooModule_);
      modInfo.setDirectlyRequiredModules(requiredModules);
    }
  }
}
