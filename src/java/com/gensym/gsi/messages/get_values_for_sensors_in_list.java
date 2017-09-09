
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class get_values_for_sensors_in_list implements ICPMessage {
    public static short messageCode = 63;
    private ICPStream stream = null;


    public get_values_for_sensors_in_list () {}
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
