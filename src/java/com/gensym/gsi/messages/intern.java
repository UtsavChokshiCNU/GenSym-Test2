
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

import com.gensym.util.Symbol;

public class intern implements ICPMessage {
    public static short messageCode = 81;
    private ICPStream stream = null;

    int corresponding_icp_object_index = 0;
    String text_string = null;

    public intern () {}
    public intern (int corresponding_icp_object_index, String text_string) {
        this.corresponding_icp_object_index = corresponding_icp_object_index;
        this.text_string = text_string;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        corresponding_icp_object_index = CORRESPONDING_ICP_OBJECT_INDEX.read(inputStream);
        text_string = TEXT_STRING.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        outputStream.writeICPByte(messageCode);
        CORRESPONDING_ICP_OBJECT_INDEX.write(corresponding_icp_object_index,outputStream);
        TEXT_STRING.write(text_string,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
	stream.standardIndexSpace.setObjectForIndex(corresponding_icp_object_index,
						    Symbol.intern(text_string));
    }
}
