
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class abort_icp_task implements ICPMessage {
    public static short messageCode = 250;
    private ICPStream stream = null;

    int icp_task_index = 0;

    public abort_icp_task () {}
    public abort_icp_task (int icp_task_index) {
        this.icp_task_index = icp_task_index;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        icp_task_index = UNSIGNED_INTEGER.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        outputStream.writeICPByte(messageCode);
        UNSIGNED_INTEGER.write(icp_task_index,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
	// not called if resumability is disabled
    }
}
