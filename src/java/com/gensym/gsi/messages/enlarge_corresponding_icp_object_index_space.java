
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

import com.gensym.util.Symbol;

public class enlarge_corresponding_icp_object_index_space implements ICPMessage {
    public static short messageCode = 15;
    private ICPStream stream = null;

    Symbol name_of_corresponding_icp_object_index_space = null;
    int new_index_limit_plus_one = 0;

    public enlarge_corresponding_icp_object_index_space () {}
    public enlarge_corresponding_icp_object_index_space (Symbol name_of_corresponding_icp_object_index_space, int new_index_limit_plus_one) {
        this.name_of_corresponding_icp_object_index_space = name_of_corresponding_icp_object_index_space;
        this.new_index_limit_plus_one = new_index_limit_plus_one;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        name_of_corresponding_icp_object_index_space = SYMBOL.read(inputStream);
        new_index_limit_plus_one = UNSIGNED_INTEGER.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        SYMBOL.initialWrite(name_of_corresponding_icp_object_index_space,outputStream);
        outputStream.writeICPByte(messageCode);
        SYMBOL.write(name_of_corresponding_icp_object_index_space,outputStream);
        UNSIGNED_INTEGER.write(new_index_limit_plus_one,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
	// not used.  no handling necessary, anyway.
    }
}
