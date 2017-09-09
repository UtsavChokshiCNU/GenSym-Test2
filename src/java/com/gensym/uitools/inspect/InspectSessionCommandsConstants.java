package com.gensym.uitools.inspect;

import com.gensym.util.Symbol;
import com.gensym.uitools.inspect.trees.ColumnSpecification;
import com.gensym.message.Resource;

public interface InspectSessionCommandsConstants {

  static final String shortResource = "InspectShortResource";
  static final String longResource = "InspectLongResource";
  static final String mnemonicResource = "InspectMnemonicResource";
  static final Resource inspectResource
  = Resource.getBundle("com/gensym/uitools/inspect/InspectShortResource");
  static final String CLASS_NAME = inspectResource.getString("ClassName");
  static final String PROCEDURE_NAME = inspectResource.getString("ProcedureName");
  static final String METHOD_NAME = inspectResource.getString("MethodName");
  static final String OPTIONAL_METHOD_NAME
  = inspectResource.getString("OptionalMethodName");
  static final String OPTIONAL_CLASS_NAME
  = inspectResource.getString("OptionalClassName");
  static final String OPTIONAL_MODULE_NAME
  = inspectResource.getString("OptionalModuleName");
  static final String OPTIONAL_WORKSPACE_NAME
  = inspectResource.getString("OptionalWorkspaceName");

  public static final String INSPECT = "Inspect";
  public static final String CHECK_MODULARIZATION = "CheckModularization";
  public static final String METHOD_INHERITANCE_PATH = "MethodInheritancePath";
  public static final String METHOD_HIERARCHY = "MethodHierarchy";
  public static final String PROCEDURE_INVOCATION_HIERARCHY = "ProcedureInvocationHierarchy";
  public static final String PROCEDURE_CALLING_HIERARCHY = "ProcedureCallingHierarchy";
  public static final String PROCEDURE_CALLER_HIERARCHY = "ProcedureCallerHierarchy";
  public static final String CLASS_HIERARCHY = "ClassHierarchy";
  public static final String MODULE_HIERARCHY = "ModuleHierarchy";
  public static final String WORKSPACE_HIERARCHY = "WorkspaceHierarchy";
  public static final String METHOD_HIERARCHIES = "MethodHierachies";
  public static final String PROCEDURAL_HIERARCHIES = "ProceduralHierachies";

  static final String METHOD_INHERITANCE_PATH_TITLE
  = inspectResource.getString(METHOD_INHERITANCE_PATH);
  static final String METHOD_HIERARCHY_TITLE 
  = inspectResource.getString(METHOD_HIERARCHY);   
  static final String PROCEDURE_INVOCATION_HIERARCHY_TITLE 
  = inspectResource.getString(PROCEDURE_INVOCATION_HIERARCHY);     
  static final String PROCEDURE_CALLING_HIERARCHY_TITLE 
  = inspectResource.getString(PROCEDURE_CALLING_HIERARCHY);     
  static final String PROCEDURE_CALLER_HIERARCHY_TITLE 
  = inspectResource.getString(PROCEDURE_CALLER_HIERARCHY);     
  static final String CLASS_HIERARCHY_TITLE 
  = inspectResource.getString(CLASS_HIERARCHY);     
  static final String MODULE_HIERARCHY_TITLE 
  = inspectResource.getString(MODULE_HIERARCHY);
  static final String WORKSPACE_HIERARCHY_TITLE 
  = inspectResource.getString(WORKSPACE_HIERARCHY);  

  static final String[] CLASS_HIERARCHY_LABELS
  = new String[] {OPTIONAL_CLASS_NAME};
  static final String[] MODULE_HIERARCHY_LABELS
  = new String[] {OPTIONAL_MODULE_NAME};
  static final String[] WORKSPACE_HIERARCHY_LABELS
  = new String[] {OPTIONAL_WORKSPACE_NAME};
  static final String[] PROCEDURE_CALLING_HIERARCHY_LABELS
  = new String[] {PROCEDURE_NAME};
  static final String[] PROCEDURE_CALLER_HIERARCHY_LABELS
  = new String[] {PROCEDURE_NAME};        
  static final String[] METHOD_INHERITANCE_PATH_HIERARCHY_LABELS 
  = new String[] {CLASS_NAME, OPTIONAL_METHOD_NAME};
  static final String[] METHOD_HIERARCHY_LABELS
  = new String[] {METHOD_NAME};

  static final Symbol
  TABLE_HEADER_ = Symbol.intern ("TABLE-HEADER"),
    NAMES_ = Symbol.intern ("NAMES"),
    CLASS_ = Symbol.intern ("CLASS"),
    TEXT_ = Symbol.intern ("TEXT"),
    AUTHORS_ = Symbol.intern ("AUTHORS"),
    CHANGE_LOG_ = Symbol.intern ("CHANGE-LOG");  
  static final Symbol[] defaultColumnNames
  = {TABLE_HEADER_,CLASS_,TEXT_,AUTHORS_,CHANGE_LOG_};
  static final boolean[] defaultColumnViewAsTexts
  = {false, false, false, true, true};
  static final int[] defaultPreferredColumnWidths
  = {175,80,65,65,50};
  static final ColumnSpecification defaultColumnSpec
  = new ColumnSpecification(defaultColumnNames,
			    defaultColumnViewAsTexts,
			    defaultPreferredColumnWidths);
  
  static final Symbol
  G2_GET_METHOD_INHERITANCE_PATH_ = Symbol.intern ("G2-GET-METHOD-INHERITANCE-PATH"),
    G2_GET_METHOD_HIERARCHY_ = Symbol.intern ("G2-GET-METHOD-HIERARCHY"),
    G2_GET_PROCEDURE_INVOCATION_HIERARCHY_ = Symbol.intern ("G2-GET-PROCEDURE-INVOCATION-HIERARCHY"),
    G2_GET_PROCEDURE_CALLING_HIERARCHY_ = Symbol.intern ("G2-GET-PROCEDURE-CALLING-HIERARCHY"),
    G2_GET_PROCEDURE_CALLER_HIERARCHY_ = Symbol.intern ("G2-GET-PROCEDURE-CALLER-HIERARCHY"),
    G2_GET_CLASS_HIERARCHY_ = Symbol.intern ("G2-GET-CLASS-HIERARCHY"),
    G2_GET_MODULE_HIERARCHY_ = Symbol.intern ("G2-GET-MODULE-HIERARCHY"),
    G2_GET_WORKSPACE_HIERARCHY_ = Symbol.intern ("G2-GET-WORKSPACE-HIERARCHY");

}
