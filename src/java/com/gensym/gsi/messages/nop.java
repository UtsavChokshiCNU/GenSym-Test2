
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;
import java.util.*;

public class nop implements ICPMessage {
    public static short messageCode = 16;
    private ICPStream stream = null;

    Map number_of_icp_bytes_of_fill = null;

    public nop () {}
    public nop (Map number_of_icp_bytes_of_fill) {
        this.number_of_icp_bytes_of_fill = number_of_icp_bytes_of_fill;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        number_of_icp_bytes_of_fill = NUMBER_OF_ICP_BYTES_OF_FILL.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        outputStream.writeICPByte(messageCode);
        NUMBER_OF_ICP_BYTES_OF_FILL.write(number_of_icp_bytes_of_fill,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
    }
}
