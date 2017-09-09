
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class return_peer_version implements ICPMessage {
    public static short messageCode = 66;
    private static final int GSI_INTERFACE_RUNNING_OK = 2;
    private ICPStream stream = null;

    int major_version_number = 0;
    int minor_version_number = 0;

    public return_peer_version () {}
    public return_peer_version (int major_version_number, int minor_version_number) {
        this.major_version_number = major_version_number;
        this.minor_version_number = minor_version_number;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        major_version_number = UNSIGNED_INTEGER.read(inputStream);
        minor_version_number = UNSIGNED_INTEGER.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        outputStream.writeICPByte(messageCode);
        UNSIGNED_INTEGER.write(major_version_number,outputStream);
        UNSIGNED_INTEGER.write(minor_version_number,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
	// unless (call-initialize-context-and-maybe-reject-connection)
	Integer icpindex = stream.standardIndexSpace.lookupIndexForObject(sck);
	sck.writeICPMessage(new receive_value_for_ping_request
			    (icpindex.intValue(), 
			     0, 0, 0, 0, 0, 0,
			     GSI_INTERFACE_RUNNING_OK));
    }
}
