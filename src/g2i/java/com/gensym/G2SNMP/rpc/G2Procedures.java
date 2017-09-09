package com.gensym.G2SNMP.rpc;

import com.gensym.util.Symbol;


/**
   Receiver procedures Interface. Seems to be never implemented.
   Maybe we should change it to public (abstract) class.
*/
public interface G2Procedures {
    public static final Symbol ReceiveMessage = Symbol.intern("OXSJ_G2SNMP_RECEIVE_MESSAGE");
    public static final Symbol ReceiveTrap = Symbol.intern("OXSJ_G2SNMP_RECEIVE_TRAP");
}
