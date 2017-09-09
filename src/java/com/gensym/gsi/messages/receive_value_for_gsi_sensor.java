
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class receive_value_for_gsi_sensor implements ICPMessage {
    public static short messageCode = 68;
    private ICPStream stream = null;

    int gsi_sensor = 0;
    int error_code = 0;
    Object value = null;

    public receive_value_for_gsi_sensor () {}
    public receive_value_for_gsi_sensor (int gsi_sensor, int error_code, Object value) {
        this.gsi_sensor = gsi_sensor;
        this.error_code = error_code;
        this.value = value;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        gsi_sensor = RETURNED_GSI_SENSOR.read(inputStream);
        error_code = GSI_VALUE_ERROR_CODE.read(inputStream);
        value = GSI_DS_VALUE.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        outputStream.writeICPByte(messageCode);
        RETURNED_GSI_SENSOR.write(gsi_sensor,outputStream);
        GSI_VALUE_ERROR_CODE.write(error_code,outputStream);
        GSI_DS_VALUE.write(value,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
    }
}
