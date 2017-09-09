
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class intern_list implements ICPMessage {
    public static short messageCode = 351;
    private ICPStream stream = null;

    int corresponding_icp_object_index = 0;
    InternedList list = null;

    public intern_list () {}
    public intern_list (int corresponding_icp_object_index, InternedList list) {
        this.corresponding_icp_object_index = corresponding_icp_object_index;
        this.list = list;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        corresponding_icp_object_index = CORRESPONDING_ICP_OBJECT_INDEX.read(inputStream);
        list = InternedList.intern(ICP_TREE.read(inputStream));
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        outputStream.writeICPByte(messageCode);
        CORRESPONDING_ICP_OBJECT_INDEX.write(corresponding_icp_object_index,outputStream);
        ICP_TREE.write(list.value(), outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
	stream.standardIndexSpace.setObjectForIndex(corresponding_icp_object_index,list);
    }
}
