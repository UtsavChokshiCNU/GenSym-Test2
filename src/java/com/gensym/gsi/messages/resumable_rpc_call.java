
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

import com.gensym.util.Symbol;

public class resumable_rpc_call implements ICPMessage {
    public static short messageCode = 248;
    private ICPStream stream = null;

    Symbol remote_procedure_name = null;
    GSIRemoteProcedureIdentifier resumable_remote_procedure_identifier = null;
    Object[] rpc_argument_list = null;

    public resumable_rpc_call () {}
    public resumable_rpc_call (Symbol remote_procedure_name, GSIRemoteProcedureIdentifier resumable_remote_procedure_identifier, Object[] rpc_argument_list) {
        this.remote_procedure_name = remote_procedure_name;
        this.resumable_remote_procedure_identifier = resumable_remote_procedure_identifier;
        this.rpc_argument_list = rpc_argument_list;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        remote_procedure_name = REMOTE_PROCEDURE_NAME.read(inputStream);
        resumable_remote_procedure_identifier = RESUMABLE_REMOTE_PROCEDURE_IDENTIFIER.read(inputStream);
        rpc_argument_list = RESUMABLE_RPC_ARGUMENT_LIST.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        REMOTE_PROCEDURE_NAME.initialWrite(remote_procedure_name,outputStream);
        RESUMABLE_REMOTE_PROCEDURE_IDENTIFIER.initialWrite(resumable_remote_procedure_identifier,outputStream);
        outputStream.writeICPByte(messageCode);
        REMOTE_PROCEDURE_NAME.write(remote_procedure_name,outputStream);
        RESUMABLE_REMOTE_PROCEDURE_IDENTIFIER.write(resumable_remote_procedure_identifier,outputStream);
        RESUMABLE_RPC_ARGUMENT_LIST.write(rpc_argument_list,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
    }
}
