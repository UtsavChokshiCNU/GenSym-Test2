
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class rpc_acknowledge_abort implements ICPMessage {
    public static short messageCode = 240;
    private ICPStream stream = null;

    int procedure_index = 0;

    public rpc_acknowledge_abort () {}
    public rpc_acknowledge_abort (int procedure_index) {
        this.procedure_index = procedure_index;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        procedure_index = UNSIGNED_INTEGER.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        outputStream.writeICPByte(messageCode);
        UNSIGNED_INTEGER.write(procedure_index,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
    }
}
