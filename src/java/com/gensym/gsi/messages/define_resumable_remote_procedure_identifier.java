
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class define_resumable_remote_procedure_identifier implements ICPMessage {
    public static short messageCode = 352;
    private ICPStream stream = null;

    int corresponding_icp_object_index = 0;
    int remote_procedure_identifier_tag = 0;
    Object remote_procedure_item_passing_info = null;

    public define_resumable_remote_procedure_identifier () {}
    public define_resumable_remote_procedure_identifier (int corresponding_icp_object_index, int remote_procedure_identifier_tag, Object remote_procedure_item_passing_info) {
        this.corresponding_icp_object_index = corresponding_icp_object_index;
        this.remote_procedure_identifier_tag = remote_procedure_identifier_tag;
        this.remote_procedure_item_passing_info = remote_procedure_item_passing_info;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        corresponding_icp_object_index = CORRESPONDING_ICP_OBJECT_INDEX.read(inputStream);
        remote_procedure_identifier_tag = UNSIGNED_INTEGER.read(inputStream);
        remote_procedure_item_passing_info = INTERNED_LIST.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        INTERNED_LIST.initialWrite(remote_procedure_item_passing_info,outputStream);
        outputStream.writeICPByte(messageCode);
        CORRESPONDING_ICP_OBJECT_INDEX.write(corresponding_icp_object_index,outputStream);
        UNSIGNED_INTEGER.write(remote_procedure_identifier_tag,outputStream);
        INTERNED_LIST.write(remote_procedure_item_passing_info,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
	GSIRemoteProcedureIdentifier id 
	    = GSIRemoteProcedureIdentifier(remote_procedure_identifier_tag,
					   (List)remote_procedure_item_passing_info);
	stream.standardIndexSpace.setObjectForIndex(corresponding_icp_object_index,id);
    }
}
