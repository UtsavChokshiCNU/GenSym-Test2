
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class define_gsi_interface implements ICPMessage {
    public static short messageCode = 77;
    private ICPStream stream = null;

    int corresponding_icp_object_index = 0;

    public define_gsi_interface () {}
    public define_gsi_interface (int corresponding_icp_object_index) {
        this.corresponding_icp_object_index = corresponding_icp_object_index;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        corresponding_icp_object_index = CORRESPONDING_ICP_OBJECT_INDEX.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        outputStream.writeICPByte(messageCode);
        CORRESPONDING_ICP_OBJECT_INDEX.write(corresponding_icp_object_index,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
	stream.standardIndexSpace.setObjectForIndex(corresponding_icp_object_index,sck);
    }
}
