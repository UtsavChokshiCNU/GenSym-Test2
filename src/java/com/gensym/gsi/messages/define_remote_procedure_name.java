
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

import com.gensym.util.Symbol;

public class define_remote_procedure_name implements ICPMessage {
    public static short messageCode = 221;
    private ICPStream stream = null;

    int corresponding_icp_object_index = 0;
    Symbol remote_procedure_name_symbol = null;

    public define_remote_procedure_name () {}
    public define_remote_procedure_name (int corresponding_icp_object_index, Symbol remote_procedure_name_symbol) {
        this.corresponding_icp_object_index = corresponding_icp_object_index;
        this.remote_procedure_name_symbol = remote_procedure_name_symbol;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        corresponding_icp_object_index = CORRESPONDING_ICP_OBJECT_INDEX.read(inputStream);
        remote_procedure_name_symbol = SYMBOL.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        SYMBOL.initialWrite(remote_procedure_name_symbol,outputStream);
        outputStream.writeICPByte(messageCode);
        CORRESPONDING_ICP_OBJECT_INDEX.write(corresponding_icp_object_index,outputStream);
        SYMBOL.write(remote_procedure_name_symbol,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
    }
}
