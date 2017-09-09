
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class i_am_alive implements ICPMessage {
    public static short messageCode = 14;
    private ICPStream stream = null;

    int message_group_id = 0;

    public i_am_alive () {}
    public i_am_alive (int message_group_id) {
        this.message_group_id = message_group_id;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        message_group_id = UNSIGNED_INTEGER.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        outputStream.writeICPByte(messageCode);
        UNSIGNED_INTEGER.write(message_group_id,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
    }
}
