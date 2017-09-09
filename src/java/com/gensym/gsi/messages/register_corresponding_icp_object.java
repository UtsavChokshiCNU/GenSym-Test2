
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

import com.gensym.util.Symbol;

public class register_corresponding_icp_object implements ICPMessage {
    public static short messageCode = 322;
    private ICPStream stream = null;

    int corresponding_icp_object_index = 0;
    Symbol name_of_item = null;
    Symbol class_of_item = null;
    Object parameter1 = null;
    Object parameter2 = null;
    Object parameter3 = null;
    Object parameter4 = null;
    Object parameter5 = null;
    Object parameter6 = null;

    public register_corresponding_icp_object () {}
    public register_corresponding_icp_object (int corresponding_icp_object_index, Symbol name_of_item, Symbol class_of_item, Object parameter1, Object parameter2, Object parameter3, Object parameter4, Object parameter5, Object parameter6) {
        this.corresponding_icp_object_index = corresponding_icp_object_index;
        this.name_of_item = name_of_item;
        this.class_of_item = class_of_item;
        this.parameter1 = parameter1;
        this.parameter2 = parameter2;
        this.parameter3 = parameter3;
        this.parameter4 = parameter4;
        this.parameter5 = parameter5;
        this.parameter6 = parameter6;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        corresponding_icp_object_index = CORRESPONDING_ICP_OBJECT_INDEX.read(inputStream);
        name_of_item = SYMBOL.read(inputStream);
        class_of_item = SYMBOL.read(inputStream);
        parameter1 = GSI_PERMANENT_REMOTE_VALUE.read(inputStream);
        parameter2 = GSI_PERMANENT_REMOTE_VALUE.read(inputStream);
        parameter3 = GSI_PERMANENT_REMOTE_VALUE.read(inputStream);
        parameter4 = GSI_PERMANENT_REMOTE_VALUE.read(inputStream);
        parameter5 = GSI_PERMANENT_REMOTE_VALUE.read(inputStream);
        parameter6 = GSI_PERMANENT_REMOTE_VALUE.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        SYMBOL.initialWrite(name_of_item,outputStream);
        SYMBOL.initialWrite(class_of_item,outputStream);
        outputStream.writeICPByte(messageCode);
        CORRESPONDING_ICP_OBJECT_INDEX.write(corresponding_icp_object_index,outputStream);
        SYMBOL.write(name_of_item,outputStream);
        SYMBOL.write(class_of_item,outputStream);
        GSI_PERMANENT_REMOTE_VALUE.write(parameter1,outputStream);
        GSI_PERMANENT_REMOTE_VALUE.write(parameter2,outputStream);
        GSI_PERMANENT_REMOTE_VALUE.write(parameter3,outputStream);
        GSI_PERMANENT_REMOTE_VALUE.write(parameter4,outputStream);
        GSI_PERMANENT_REMOTE_VALUE.write(parameter5,outputStream);
        GSI_PERMANENT_REMOTE_VALUE.write(parameter6,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
    }
}
