
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class acknowledge_shutdown implements ICPMessage {
    public static short messageCode = 336;
    private ICPStream stream = null;


    public acknowledge_shutdown () {}
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
	try {sck.close();}
	catch (Exception e) {}
    }
}
