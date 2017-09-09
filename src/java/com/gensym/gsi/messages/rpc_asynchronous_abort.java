
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class rpc_asynchronous_abort implements ICPMessage {
    public static short messageCode = 235;
    private ICPStream stream = null;

    GSIRemoteProcedureIdentifier procedure_to_abort = null;

    public rpc_asynchronous_abort () {}
    public rpc_asynchronous_abort (GSIRemoteProcedureIdentifier procedure_to_abort) {
        this.procedure_to_abort = procedure_to_abort;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        procedure_to_abort = RESUMABLE_REMOTE_PROCEDURE_IDENTIFIER.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        RESUMABLE_REMOTE_PROCEDURE_IDENTIFIER.initialWrite(procedure_to_abort,outputStream);
        outputStream.writeICPByte(messageCode);
        RESUMABLE_REMOTE_PROCEDURE_IDENTIFIER.write(procedure_to_abort,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
    }
}
