
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class message_group_id implements ICPMessage {
    public static short messageCode = 181;
    private ICPStream stream = null;

    int message_group_id = 0;
    int number_of_icp_bytes = 0;

    public message_group_id () {}
    public message_group_id (int message_group_id, int number_of_icp_bytes) {
        this.message_group_id = message_group_id;
        this.number_of_icp_bytes = number_of_icp_bytes;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        message_group_id = UNSIGNED_INTEGER.read(inputStream);
        number_of_icp_bytes = UNSIGNED_INTEGER.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        outputStream.writeICPByte(messageCode);
        UNSIGNED_INTEGER.write(message_group_id,outputStream);
        UNSIGNED_INTEGER.write(number_of_icp_bytes,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
    }
}
