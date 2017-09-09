
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class resumable_rpc_return_values implements ICPMessage {
    public static short messageCode = 249;
    private ICPStream stream = null;

    int calling_procedure_index = 0;
    Object[] return_values_list = null;

    public resumable_rpc_return_values () {}
    public resumable_rpc_return_values (int calling_procedure_index, Object[] return_values_list) {
        this.calling_procedure_index = calling_procedure_index;
        this.return_values_list = return_values_list;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        calling_procedure_index = UNSIGNED_INTEGER.read(inputStream);
        return_values_list = RESUMABLE_RPC_ARGUMENT_LIST.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        outputStream.writeICPByte(messageCode);
        UNSIGNED_INTEGER.write(calling_procedure_index,outputStream);
        RESUMABLE_RPC_ARGUMENT_LIST.write(return_values_list,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
    }
}
