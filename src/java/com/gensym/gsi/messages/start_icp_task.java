
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class start_icp_task implements ICPMessage {
    public static short messageCode = 245;
    private ICPStream stream = null;

    boolean resumable_p = false;
    int icp_task_index = 0;
    int icp_task_priority = 0;

    public start_icp_task () {}
    public start_icp_task (boolean resumable_p, int icp_task_index, int icp_task_priority) {
        this.resumable_p = resumable_p;
        this.icp_task_index = icp_task_index;
        this.icp_task_priority = icp_task_priority;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        resumable_p = ICP_TASK_RESUMABLE_P.read(inputStream);
        icp_task_index = UNSIGNED_INTEGER.read(inputStream);
        icp_task_priority = UNSIGNED_INTEGER.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        outputStream.writeICPByte(messageCode);
        ICP_TASK_RESUMABLE_P.write(resumable_p,outputStream);
        UNSIGNED_INTEGER.write(icp_task_index,outputStream);
        UNSIGNED_INTEGER.write(icp_task_priority,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
    }
}
