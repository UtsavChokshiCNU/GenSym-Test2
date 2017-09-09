
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class initialize_data_server implements ICPMessage {
    public static short messageCode = 69;
    private ICPStream stream = null;

    String text_string = null;

    public initialize_data_server () {}
    public initialize_data_server (String text_string) {
        this.text_string = text_string;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        text_string = TEXT_STRING.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
	// never written by GSI
        stream = outputStream;
        outputStream.writeICPByte(messageCode);
        TEXT_STRING.write(text_string,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
	sck.setRemoteProcessInitializationString(text_string);
    }
}
