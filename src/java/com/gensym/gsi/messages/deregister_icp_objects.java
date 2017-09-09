
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;
import java.util.List;

import com.gensym.util.Symbol;

public class deregister_icp_objects implements ICPMessage {
    public static short messageCode = 326;
    private ICPStream stream = null;

    Symbol name_of_corresponding_icp_object_index_space = null;
    byte deregister_icp_objects_operation = 0;
    List corresponding_icp_object_index_list = null;

    public deregister_icp_objects () {}
    public deregister_icp_objects (Symbol name_of_corresponding_icp_object_index_space, byte deregister_icp_objects_operation, List corresponding_icp_object_index_list) {
        this.name_of_corresponding_icp_object_index_space = name_of_corresponding_icp_object_index_space;
        this.deregister_icp_objects_operation = deregister_icp_objects_operation;
        this.corresponding_icp_object_index_list = corresponding_icp_object_index_list;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        name_of_corresponding_icp_object_index_space = SYMBOL.read(inputStream);
        deregister_icp_objects_operation = DEREGISTER_ICP_OBJECTS_OPERATION.read(inputStream);
        corresponding_icp_object_index_list = CORRESPONDING_ICP_OBJECT_INDEX_LIST.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        SYMBOL.initialWrite(name_of_corresponding_icp_object_index_space,outputStream);
        outputStream.writeICPByte(messageCode);
        SYMBOL.write(name_of_corresponding_icp_object_index_space,outputStream);
        DEREGISTER_ICP_OBJECTS_OPERATION.write(deregister_icp_objects_operation,outputStream);
        CORRESPONDING_ICP_OBJECT_INDEX_LIST.write(corresponding_icp_object_index_list,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
    }
}
