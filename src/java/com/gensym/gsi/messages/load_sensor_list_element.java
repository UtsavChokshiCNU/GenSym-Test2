
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class load_sensor_list_element implements ICPMessage {
    public static short messageCode = 61;
    private ICPStream stream = null;

    int corresponding_icp_object_index = 0;
    double collection_interval = 0.0;
    Object value_to_set = null;

    public load_sensor_list_element () {}
    public load_sensor_list_element (int corresponding_icp_object_index, double collection_interval, Object value_to_set) {
        this.corresponding_icp_object_index = corresponding_icp_object_index;
        this.collection_interval = collection_interval;
        this.value_to_set = value_to_set;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        corresponding_icp_object_index = CORRESPONDING_ICP_OBJECT_INDEX.read(inputStream);
        collection_interval = GSI_DS_UPDATE_INTERVAL.read(inputStream);
        value_to_set = GSI_PERMANENT_REMOTE_VALUE.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        outputStream.writeICPByte(messageCode);
        CORRESPONDING_ICP_OBJECT_INDEX.write(corresponding_icp_object_index,outputStream);
        GSI_DS_UPDATE_INTERVAL.write(collection_interval,outputStream);
        GSI_PERMANENT_REMOTE_VALUE.write(value_to_set,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
    }
}
