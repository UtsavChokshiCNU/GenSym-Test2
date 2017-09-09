
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

import com.gensym.util.Symbol;

public class resumable_rpc_error implements ICPMessage {
    public static short messageCode = 353;
    private ICPStream stream = null;

    Symbol error_name = null;
    int error_level = 0;
    String error_description = null;
    Object[] error_argument_list = null;

    public resumable_rpc_error () {}
    public resumable_rpc_error (Symbol error_name, int error_level, String error_description, Object[] error_argument_list) {
        this.error_name = error_name;
        this.error_level = error_level;
        this.error_description = error_description;
        this.error_argument_list = error_argument_list;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        error_name = SYMBOL.read(inputStream);
        error_level = UNSIGNED_INTEGER.read(inputStream);
        error_description = TEXT_STRING.read(inputStream);
        error_argument_list = RESUMABLE_RPC_ARGUMENT_LIST.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        SYMBOL.initialWrite(error_name,outputStream);
        outputStream.writeICPByte(messageCode);
        SYMBOL.write(error_name,outputStream);
        UNSIGNED_INTEGER.write(error_level,outputStream);
        TEXT_STRING.write(error_description,outputStream);
        RESUMABLE_RPC_ARGUMENT_LIST.write(error_argument_list,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
    }
}
