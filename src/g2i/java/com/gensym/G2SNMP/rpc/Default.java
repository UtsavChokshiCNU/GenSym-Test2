package com.gensym.G2SNMP.rpc;

import com.gensym.jgi.G2Connection;
//import com.gensym.G2SNMP;

/**
   Default "stub" interface for Task class.
*/
public interface Default {

    /**
       @roseuid 365D6CE1007E
     */
    public void registerRPCs(G2Connection g2connection) throws com.gensym.G2SNMP.TaskInitException;
}