
package com.gensym.gsi;

import com.gensym.gsi.*;

public class GSIRemoteProcedureIdentifier {
    static final byte OUTSTANDING = 1;
    byte state = OUTSTANDING;
    boolean awaiting_acknowledge_abort = false;
    Symbol name = null;

    int tag; // outgoing RPI's get their tag from an IndexSpace on the ICPOutputStream
    boolean uses_variable_args = false;
    List argument_info = null;

    GSIRemoteProcedureIdentifier(int tag, boolean uses_variable_args, Enumerator args) {
    } 

    GSIRemoteProcedureIdentifier(int tag, List internedInfo) {
    } 

}
