
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class return_initialize_gsi_interface_status implements ICPMessage {
    public static short messageCode = 339;
    private ICPStream stream = null;

    String error_information = null;

    public return_initialize_gsi_interface_status () {}
    public return_initialize_gsi_interface_status (String error_information) {
        this.error_information = error_information;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        error_information = TEXT_STRING.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        outputStream.writeICPByte(messageCode);
        TEXT_STRING.write(error_information,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
    }
}
