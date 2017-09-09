
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class create_item_reference implements ICPMessage {
    public static short messageCode = 355;
    private ICPStream stream = null;

    Object item = null;

    public create_item_reference () {}
    public create_item_reference (Object item) {
        this.item = item;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        item = ITEM_REFERENCE_2.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        outputStream.writeICPByte(messageCode);
        ITEM_REFERENCE_2.write(item,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
    }
}
