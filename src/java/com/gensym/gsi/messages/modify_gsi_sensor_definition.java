
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class modify_gsi_sensor_definition implements ICPMessage {
    public static short messageCode = 59;
    private ICPStream stream = null;

    int corresponding_icp_object_index = 0;
    double update_interval = 0.0;
    int value_type = 0;
    Object name_of_item = null;
    Object name_of_class = null;

    public modify_gsi_sensor_definition () {}
    public modify_gsi_sensor_definition (int corresponding_icp_object_index, double update_interval, int value_type, Object name_of_item, Object name_of_class) {
        this.corresponding_icp_object_index = corresponding_icp_object_index;
        this.update_interval = update_interval;
        this.value_type = value_type;
        this.name_of_item = name_of_item;
        this.name_of_class = name_of_class;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        corresponding_icp_object_index = CORRESPONDING_ICP_OBJECT_INDEX.read(inputStream);
        update_interval = GSI_DS_UPDATE_INTERVAL.read(inputStream);
        value_type = UNSIGNED_INTEGER.read(inputStream);
        name_of_item = REMOTE_VALUE.read(inputStream);
        name_of_class = REMOTE_VALUE.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        outputStream.writeICPByte(messageCode);
        CORRESPONDING_ICP_OBJECT_INDEX.write(corresponding_icp_object_index,outputStream);
        GSI_DS_UPDATE_INTERVAL.write(update_interval,outputStream);
        UNSIGNED_INTEGER.write(value_type,outputStream);
        REMOTE_VALUE.write(name_of_item,outputStream);
        REMOTE_VALUE.write(name_of_class,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
    }
}
