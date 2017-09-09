
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class receive_gsi_sensor_value_vector implements ICPMessage {
    public static short messageCode = 78;
    private ICPStream stream = null;

    int gsi_sensor = 0;
    int error_code = 0;
    Object value = null;
    GSIValueVector vector = null;

    public receive_gsi_sensor_value_vector () {}
    public receive_gsi_sensor_value_vector (int gsi_sensor, int error_code, Object value, GSIValueVector vector) {
        this.gsi_sensor = gsi_sensor;
        this.error_code = error_code;
        this.value = value;
        this.vector = vector;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        gsi_sensor = RETURNED_GSI_SENSOR.read(inputStream);
        error_code = GSI_VALUE_ERROR_CODE.read(inputStream);
        value = GSI_DS_VALUE.read(inputStream);
        vector = GSI_VALUE_VECTOR.read(inputStream);
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
        GSI_VALUE_VECTOR.write(vector,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
    }
}
