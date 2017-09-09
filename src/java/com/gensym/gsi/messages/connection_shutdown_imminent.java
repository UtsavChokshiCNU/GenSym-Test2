
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class connection_shutdown_imminent implements ICPMessage {
    public static short messageCode = 306;
    private ICPStream stream = null;


    public connection_shutdown_imminent () {}
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        outputStream.writeICPByte(messageCode);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
    }
}
