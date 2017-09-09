
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class receive_values_for_gsi_sensors implements ICPMessage {
    public static short messageCode = 80;
    private ICPStream stream = null;

    GSIValues gsi_values = null;

    public receive_values_for_gsi_sensors () {}
    public receive_values_for_gsi_sensors (GSIValues gsi_values) {
        this.gsi_values = gsi_values;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        gsi_values = GSI_VALUES.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        outputStream.writeICPByte(messageCode);
        GSI_VALUES.write(gsi_values,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
    }
}
