package com.gensym.g2export.denali;

import java.util.Hashtable;
import java.util.Enumeration;
import java.util.Vector;
import com.gensym.denali.model.*;
import com.gensym.fida.*;

public class DenaliServiceImpl implements DenaliService
{
  private ServerImpl server;
  private static DenaliServiceImpl denaliService;
  private Environment environment;
  private Hashtable modulesTable = new Hashtable();
  private Hashtable itmWorkspaces = new Hashtable();
  public static final String _DENALI_SERVICE_NAME = "#WKSP-SERVICE#";

  private DenaliServiceImpl()
  {
    try {
      server = new ServerImpl();
    } catch (java.rmi.RemoteException e) {
      throw new RuntimeException(e.toString());
    }
  }

  public static DenaliService getDenaliService(Environment environment)
  {
    try {
      if (denaliService != null)
	return denaliService;
      // Denali only allows one app currently, see register at the top level
      denaliService = new DenaliServiceImpl();
      denaliService.environment = environment;
      FIDARuntime runtime = environment.getRuntime();
      Application app = runtime.getApplication("", "");
      ObjectContainer container = app.getObjectManager().register(denaliService.server);
      container.setRegisteredName(_DENALI_SERVICE_NAME);
      return denaliService;
    } catch (Exception e) {
      // Should not happen
      e.printStackTrace();
    }
    return denaliService;
  }

  @Override
  public void registerItem(com.gensym.g2export.G2__Base itmb)
  {
    if (itmb instanceof com.gensym.g2export.Entity) {
      com.gensym.g2export.Entity itm = (com.gensym.g2export.Entity)itmb;
      if (itmWorkspaces.get(itm) != null) 
	return;
      // Just deal with subworkspace for now
      com.gensym.g2export.KbWorkspace subworkspace = 
	((com.gensym.g2export.Entity)itm).getSubworkspace();
      if (subworkspace == null)
	return;
      WorkspaceData wsdata = (WorkspaceData)subworkspace.getDenaliWorkspaceData();
      if (wsdata == null) {
	System.out.println("SubWorkspace Data was null for " + itm);
	return;
      }
      
      String wsName = itm.getObjectContainer().getUuid();
      com.gensym.denali.model.Workspace dws = 
	getDenaliWorkspace(wsdata,
			   wsName);
      subworkspace._setInternalWs(dws);
      itmWorkspaces.put(itm, dws);
    } 
  }

  public Enumeration getItems(com.gensym.g2export.KbWorkspace workspace)
  {
    throw new RuntimeException("NOT Implemented");
  }


  com.gensym.denali.model.Workspace getDenaliWorkspace(WorkspaceData wsdata,
						       String wsName)
  {
    String moduleName = wsdata.getModuleName();
    try {
      Module module = (com.gensym.denali.model.Module)modulesTable.get(moduleName);
      if (module == null) {
	module = new Module(moduleName.toString());
	modulesTable.put(moduleName, module);
	server.addModule(module);
      }
      com.gensym.denali.model.Workspace ws = 
	module.addNewTopLevelWorkspace(wsName);
      for (Enumeration e = wsdata.getClassNamesToRegister().elements(); e.hasMoreElements();) {
	// Should use ClassManager here, but denali uses forName
	Class clazz = Class.forName((String)e.nextElement());
	module.addClass(clazz);
      }
      wsdata.setupWorkspaceFromData(module, ws);
      System.out.println("Added denali ws " + wsName + " " + ws);
      return ws;
    } catch (Exception e) {
      e.printStackTrace();
    }
    return null;
  }

  public static String getWorkspaceName(ObjectProxy proxy)
  {
    return proxy.getUuid();
  }

}
