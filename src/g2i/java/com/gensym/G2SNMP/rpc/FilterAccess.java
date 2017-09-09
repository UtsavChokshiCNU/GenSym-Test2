package com.gensym.G2SNMP.rpc;

import com.gensym.util.Structure;

/**
   Filter interface
*/
public interface FilterAccess extends Default {

    /**
       Name in remote system: "G2SNMP_ADD_FILTERED_TRAP"
       @roseuid 365D191D0051
     */
    public void AddFilteredTrap(Structure params);

    /**
       Name in remote system: "G2SNMP_DELETE_FILTERED_TRAP"
       @roseuid 365D194000FB
     */
    public void DeleteFilteredTrap(Structure params);
}
