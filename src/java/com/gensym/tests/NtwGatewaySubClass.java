
package com.gensym.tests;

import com.gensym.ntw.*;
import com.gensym.jgi.*;
import com.gensym.core.*;
import com.gensym.util.*;
import com.gensym.message.*;

class G2GatewayBean {
  public void updateActionList (){}
}

public class NtwGatewaySubClass extends com.gensym.ntw.TwGateway {

    G2GatewayBean parent = null; 

    public void setParent(G2GatewayBean parent)
    {
      this.parent = parent;
    }

  /**
   * Initialize all Local RPC's used for this class connection.
   * This method will only be called once just before the first G2InitializeConnection 
   * is called for a connection to this class
   */
    @Override
    public void initializeLocalRPCs()
    {
      super.initializeLocalRPCs();
      registerJavaMethod (this, "updateActionList", Symbol.intern("UPDATE-ACTION-LIST"));
    }

    
    /*
     * Called by G2 with a new action list
     */
    public void updateActionList()
    {
      parent.updateActionList();
    }

  public static Symbol _getActionWorkspaces_Symbol =
    Symbol.intern ("GET-ACTION-WORKSPACES");

    @Override
    public void initializeConnectionRPCs()
    {
      super.initializeConnectionRPCs();
      //declareRemoteRPC (this._getActionWorkspaces_Symbol, 0,1, "async", 0);

      //G2Gateway.setInterfaceFundebug(true);
      //G2Gateway.setInterfaceFulldebug(true);

      // Set return types for procedures returning items - bug wont work
      setRemoteRPCReturnKind (this._getActionWorkspaces_Symbol, G2Gateway.PASS_BY_HANDLE);
    }



}
