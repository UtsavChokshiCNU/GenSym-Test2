/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 LoadSaveKBTools.java
 *
 */
package com.gensym.ntw.util;

import java.io.FileNotFoundException;

import com.gensym.classes.Kb;
import com.gensym.classes.Module;
import com.gensym.files.URLFile;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.TimeoutException;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;

public abstract class LoadSaveKBTools {

  private static Symbol WIN32_ = Symbol.intern("WIN32");
  private static Symbol UNIX_  = Symbol.intern("UNIX");
  private static Symbol VMS_   = Symbol.intern("VMS");

  private static Symbol NONE_  = Symbol.intern("NONE");
  private static final Symbol SAVE_KB_ = Symbol.intern ("SAVE-KB");

  private static Symbol G2_TYPE_OF_FILE_SYSTEM_     = Symbol.intern("G2-TYPE-OF-FILE-SYSTEM");
  private static Symbol G2_FILE_EXISTS_             = Symbol.intern("G2-FILE-EXISTS");
  private static Symbol G2_LOAD_KB_                 = Symbol.intern("G2-LOAD-KB");
  private static Symbol G2_LOAD_KB_1_               = Symbol.intern("G2-LOAD-KB-1");
  private static Symbol G2_DEFAULT_DIRECTORY_       = Symbol.intern("G2-DEFAULT-DIRECTORY");
  private static Symbol G2_SAVE_MODULE_             = Symbol.intern("G2-SAVE-MODULE");
  private static Symbol G2_START_SAVE_MODULE_       = Symbol.intern("G2-START-SAVE-MODULE");
  private static Symbol G2_START_SAVE_MODULE_1_     = Symbol.intern("G2-START-SAVE-MODULE-1");  
  private static Symbol G2_CONTINUE_SAVE_KB_        = Symbol.intern("G2-CONTINUE-SAVE-KB");
  private static Symbol G2_FINISH_SAVE_KB_          = Symbol.intern("G2-FINISH-SAVE-KB");
  private static Symbol G2_ABORT_SAVE_IN_PROGRESS_  = Symbol.intern("G2-ABORT-SAVE-IN-PROGRESS");
  private static Symbol G2_SAVE_KB_                 = Symbol.intern("G2-SAVE-KB");
  private static Symbol G2_START_SAVE_KB_           = Symbol.intern("G2-START-SAVE-KB");
  private static Symbol G2_CREATE_MODULE_           = Symbol.intern("G2-CREATE-MODULE");
  private static Symbol G2_DELETE_MODULE_           = Symbol.intern("G2-DELETE-MODULE");
  private static Symbol G2_MERGE_KB_                = Symbol.intern("G2-MERGE-KB");
  private static Symbol G2_MERGE_KB_1_              = Symbol.intern("G2-MERGE-KB-1");
  private static Symbol G2_SNAPSHOT_                = Symbol.intern("G2-SNAPSHOT");
  private static Symbol G2_WARMBOOT_KB_             = Symbol.intern("G2-WARMBOOT-KB");
  private static Symbol G2_CLEAR_KB_                = Symbol.intern("G2-CLEAR-KB");

  // params for LoadKB
  private static Boolean RESOLVE_CONFLICTS = Boolean.TRUE;
  private static Boolean BRING_FORMATS_UPTODATE = Boolean.FALSE;
  private static Boolean UPDATE_BEFORE_LOADING = Boolean.FALSE;  
  // params for SaveModule
  private static Boolean SHOW_PROGRESS = Boolean.TRUE;
  private static Boolean SAVE_WORKSPACE_LAYOUT = Boolean.TRUE;
  private static Boolean SAVE_REQUIRED_MODULES = Boolean.TRUE;
  private static Boolean USING_CLEAR_TEXT = Boolean.FALSE;
  private static Boolean EMITTING_C_CODE = Boolean.FALSE;
  private static String LOG_MESSAGE_FOR_COMMIT_AFTER_SAVING = null;	  

  // params for DeleteModule
  private static Boolean DELETE_ASSOCIATED_WORKSPACES = Boolean.TRUE;

  // params for MergeModule
  private static Boolean INSTALL_SYSTEM_TABLES = Boolean.FALSE;

  // params for Warmboot
  private static Boolean RUN_IN_CATCH_UP_MODE = Boolean.FALSE;

  // BEGIN: Symbols used by state/continue/finish save-kb stuff
  private static final Symbol RESULT_CODE_   = Symbol.intern("RESULT-CODE");
  private static final Symbol ERROR_MESSAGE_ = Symbol.intern("ERROR-MESSAGE");

  private static final Symbol READ_ONLY_   = Symbol.intern("READ-ONLY");
  private static final Symbol OK_          = Symbol.intern("OK");
  private static final Symbol FINISHED_    = Symbol.intern("FINISHED");
  private static final Symbol CONTINUE_    = Symbol.intern("CONTINUE");
  // END:

  public static void setResolveConflicts(Boolean resolveConflicts) {
    RESOLVE_CONFLICTS = resolveConflicts;
  }

  public static void setBringFormatsUpToDate(Boolean bringFormatsUpToDate) {
    BRING_FORMATS_UPTODATE = bringFormatsUpToDate;
  }
  
  public static void setShowProgress(Boolean showProgress) {
    SHOW_PROGRESS = showProgress;
  }

  public static void setSaveWorkspaceLayout(Boolean saveWorkspaceLayout) {
    SAVE_WORKSPACE_LAYOUT = saveWorkspaceLayout;
  }

  public static void setSaveRequiredModules(Boolean saveRequiredModules) {
    SAVE_REQUIRED_MODULES = saveRequiredModules;
  }

  public static void setDeleteAssociatedWorkspaces(Boolean deleteAssociatedWorkspaces) {
    DELETE_ASSOCIATED_WORKSPACES = deleteAssociatedWorkspaces;
  }

  public static void setInstallSystemTables(Boolean installSystemTables) {
    INSTALL_SYSTEM_TABLES = installSystemTables;
  }

  public static void setRunInCatchUpMode(Boolean catchUp) {
    RUN_IN_CATCH_UP_MODE = catchUp;
  }

  public static Symbol typeOfFileSystem(TwAccess connection) throws G2AccessException {
    return (Symbol)connection.callRPC(G2_TYPE_OF_FILE_SYSTEM_, new Object[]{});
  }

  public static String getModuleNameFromFileSpec(String filespec) {
    String moduleName = filespec;
    char[] charArray = new char[1];
    charArray[0] = com.gensym.files.URLFile.separatorChar;
    String searchString = new String(charArray);
    int iPos = filespec.lastIndexOf(searchString);
    if (iPos > 0) {
      moduleName = filespec.substring(iPos+1, filespec.length());
    }

    searchString = ".";
    iPos = moduleName.lastIndexOf(searchString);
    if (iPos > 0) {
      moduleName = moduleName.substring(0, iPos);
    }

    return moduleName;
  }

  public static String getG2FileSpecificationFromURL(TwAccess connection, URLFile urlFile) {
    char sepChar = URLFile.separatorChar;

    String path = urlFile.getPath();
    String searchString = "serverFileSystem";
    int index = path.indexOf(searchString);
    char backslash = (char)47;
    try {
      Symbol systemType = typeOfFileSystem(connection);
      if (systemType.equals(WIN32_)) 
	path = path.substring(index+searchString.length()+1, path.length());
      else
	path = path.substring(index+searchString.length(), path.length());

      if (systemType.equals(WIN32_)) {
	path = path.replace(backslash, sepChar);
      }
      else if (systemType.equals(VMS_)) {
	// who knows what?
      }
    } catch (G2AccessException gae) {
      Trace.exception(gae);
      // assume most people are on PCs
      path = path.replace(backslash, sepChar);
      return path;
    }
    return path;
  }

  public static String revertG2FileSpecificationToURLString (TwAccess connection, String path) {
    char sepChar = URLFile.separatorChar;
    char backslash = (char)47;
      try {
      Symbol systemType = typeOfFileSystem(connection);
      if (systemType.equals(WIN32_)) {
	path = path.replace(sepChar, backslash);
      }
      else if (systemType.equals(VMS_)) {
	// who knows what?
      }
    } catch (G2AccessException gae) {
      Trace.exception(gae);
      // assume most people are on PCs
      path = path.replace(sepChar, backslash);
      return path;
    }

    return path;
  }

  
  public static Boolean loadKB(TwAccess connection, String fileSpec) throws G2AccessException, FileNotFoundException {
    boolean isG260 = (connection.getG2Version().getMajorVersion() >= 6);
    if (fileExists(connection, fileSpec)) {
      if (isG260) {
	Object[] args = new Object[] {fileSpec,
					RESOLVE_CONFLICTS,
					BRING_FORMATS_UPTODATE,
					UPDATE_BEFORE_LOADING};
	return (Boolean)connection.callRPC(G2_LOAD_KB_1_, args);	
      } else {
	Object[] args = new Object[] {fileSpec, RESOLVE_CONFLICTS, BRING_FORMATS_UPTODATE};
	return (Boolean)connection.callRPC(G2_LOAD_KB_, args);
      }
    } else {
      throw new FileNotFoundException(fileSpec);
    }
  }

  public static boolean fileExists(TwAccess connection, String fileSpec) throws G2AccessException {
    //System.out.println("running fileExists for: "+fileSpec);
    Object[] args = new Object[] {fileSpec};
    Object returnObject = connection.callRPC(G2_FILE_EXISTS_, args);
    
    //System.out.println("G2 returned: "+returnObject);

    return (returnObject != null && (((Boolean)returnObject)).booleanValue());
  }

  public static Object defaultDirectory(TwAccess connection) throws G2AccessException {
    return connection.callRPC(G2_DEFAULT_DIRECTORY_, new Object[0]); 
  }

  public static Boolean mergeKB(TwAccess connection, String fileSpec) throws G2AccessException, FileNotFoundException {
    if (fileExists(connection, fileSpec)) {
      //System.out.println("file exists, call "+G2_MERGE_KB_);
      boolean isG260 = (connection.getG2Version().getMajorVersion() >= 6);
      if (isG260) {
	Object[] args = new Object[] {fileSpec,
					RESOLVE_CONFLICTS,
					BRING_FORMATS_UPTODATE,
					INSTALL_SYSTEM_TABLES,
					UPDATE_BEFORE_LOADING};
	connection.setG2State(((com.gensym.jgi.G2Gateway)connection).RUNNING_);//needed in 6.0?
	return (Boolean)connection.callRPC(G2_MERGE_KB_1_, args, 0);	
      } else {
	Object[] args = new Object[] {fileSpec, RESOLVE_CONFLICTS, BRING_FORMATS_UPTODATE, INSTALL_SYSTEM_TABLES};
	connection.setG2State(((com.gensym.jgi.G2Gateway)connection).RUNNING_);
	return (Boolean)connection.callRPC(G2_MERGE_KB_, args, 0);
      } 
    } else {
      throw new FileNotFoundException(fileSpec);
    }
  }

 public static Sequence saveModule(TwAccess connection, Symbol moduleName, String path) throws G2AccessException {
    boolean thereAreReadOnlyModules = false;
    boolean needsCleanup = false;
    Sequence results;
    Symbol resultCode;
    boolean isG260 = (connection.getG2Version().getMajorVersion() >= 6);    
    try {
      if (moduleName == null) {
	Object[] args = {path,
			 SAVE_KB_,
			 SHOW_PROGRESS,
			 NONE_};
	results = (Sequence)connection.callRPC(G2_START_SAVE_KB_, args);	
	
      } else if (isG260) {
	Object[] args = {path,
			 SHOW_PROGRESS,
			 SAVE_WORKSPACE_LAYOUT,
			 moduleName,
			 SAVE_REQUIRED_MODULES,
			 USING_CLEAR_TEXT,
			 EMITTING_C_CODE,
			 LOG_MESSAGE_FOR_COMMIT_AFTER_SAVING};
			   
	results = (Sequence)connection.callRPC(G2_START_SAVE_MODULE_1_, args);	
      } else {
	Object[] args = {path,
			 SHOW_PROGRESS,
			 SAVE_WORKSPACE_LAYOUT,
			 moduleName,
			 SAVE_REQUIRED_MODULES};
	results = (Sequence)connection.callRPC(G2_START_SAVE_MODULE_, args);
      }
      resultCode = (Symbol)results.elementAt(0);
      String errorMessage = (String)results.elementAt(1);
      //System.out.println("save start res="+resultCode+" msg="+errorMessage);
      
      if (resultCode.equals(READ_ONLY_)) thereAreReadOnlyModules = true;
      
      if ((!(resultCode.equals(OK_))) && 
	  (!(resultCode.equals(READ_ONLY_)))) {
	// signal error
	needsCleanup = true;
      } else {
	do {
	  results = (Sequence)connection.callRPC(G2_CONTINUE_SAVE_KB_, new Object[] {Boolean.FALSE});
	  resultCode = (Symbol)results.elementAt(0);
	  errorMessage = (String)results.elementAt(1);
	  //System.out.println("save cont res="+resultCode+" msg="+errorMessage);
	  
	} while (resultCode.equals(CONTINUE_));
	
	if (!(resultCode.equals(FINISHED_))) {
	  needsCleanup = true;
	} else {
	  results = (Sequence)connection.callRPC(G2_FINISH_SAVE_KB_, new Object[] {Boolean.FALSE});
	  resultCode = (Symbol)results.elementAt(0);
	  errorMessage = (String)results.elementAt(1);
	  //System.out.println("save finish res="+resultCode+" msg="+errorMessage);
	  if (!(resultCode.equals(OK_))) {
	    needsCleanup = true;
	  } else if (thereAreReadOnlyModules) {
	    System.out.println("\nThere are READ ONLY modules\n");
	    needsCleanup = true;
	  }
	}
      }
    } finally
      {
	if (needsCleanup)
	  abortSave(connection);
      }
    if (!resultCode.equals(OK_))
      return results;
    else
      return null;
 }

  private static void abortSave(TwAccess connection) throws G2AccessException {
    connection.callRPC(G2_ABORT_SAVE_IN_PROGRESS_, new Object[0]);
  }

  public static void createModule(TwAccess cxn, Symbol moduleName_) throws G2AccessException {
    Object obj = cxn.callRPC(G2_CREATE_MODULE_, new Object[] {moduleName_});
  }

  public static void deleteModule(TwAccess cxn, Symbol moduleName_) throws G2AccessException {
    //System.out.println("LoadSaveKBTools.deleteModule: "+moduleName_+"  calling "+G2_DELETE_MODULE_+" with Delete Assoc. Wksps: "+DELETE_ASSOCIATED_WORKSPACES);
    try {
      cxn.callRPC(G2_DELETE_MODULE_, new Object[] {moduleName_, DELETE_ASSOCIATED_WORKSPACES});
    } catch (TimeoutException toe) {
      Trace.exception(toe);
    }
  }

  public static Boolean snapshot(TwAccess cxn, String filespec) throws G2AccessException {
    return (Boolean)cxn.callRPC(G2_SNAPSHOT_, new Object[] {filespec, Boolean.FALSE, SAVE_WORKSPACE_LAYOUT});
  }

  public static Boolean warmbootKB(TwAccess cxn, String filespec) throws G2AccessException {
    return (Boolean)cxn.callRPC(G2_WARMBOOT_KB_, new Object[] {filespec, RUN_IN_CATCH_UP_MODE});
  }

  public static Boolean saveKB(TwAccess cxn, String filespec) throws G2AccessException {
    saveModule(cxn, null, filespec);
    return Boolean.TRUE;
  }

  public static Boolean saveAsAllFile(TwAccess cxn) throws G2AccessException {
    /*
     * 1. mod = the text of the top-level-module of module-information
     * 2. dir = call g2-default-directory
     * 3. path = "[dir][mod]-ALL.kb"
     * 4. call g2-save-kb (path, true, the symbol none)
     */
    Boolean saveStatus = Boolean.FALSE;
    Kb kb = cxn.getKb();
    if (kb != null) {
      Module module = kb.getTopLevelModule();
      if (module != null) {
	Symbol moduleName = module.getName();
	String modName_ = "NO-NAME";
	if (moduleName != null)
	  modName_ = moduleName.toString();
	String defaultDir = (String)defaultDirectory(cxn);
	String path = defaultDir+modName_+"-ALL.kb";
	saveStatus = saveKB(cxn, path);
      }
    }
    return saveStatus;
  }

  public static void clearKB(TwAccess cxn) throws G2AccessException {
    cxn.callRPC(G2_CLEAR_KB_, new Object[]{});
  }


}
