
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class define_temporary_index_space implements ICPMessage {
    public static short messageCode = 301;
    private ICPStream stream = null;

    IndexSpace index_space = null;

    public define_temporary_index_space () {}
    public define_temporary_index_space (IndexSpace index_space) {
        this.index_space = index_space;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        index_space = INDEX_SPACE.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        outputStream.writeICPByte(messageCode);
        INDEX_SPACE.write(index_space,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
    }
}
