
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class receive_value_for_ping_request implements ICPMessage {
    public static short messageCode = 67;
    public static int GSI_INTERFACE_RUNNING_OK = 2;
    private ICPStream stream = null;

    int gsi_interface = 0;
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    int second = 0;
    int status = 0;

    public receive_value_for_ping_request () {}
    public receive_value_for_ping_request (int gsi_interface, int year, int month, int day, int hour, int minute, int second, int status) {
        this.gsi_interface = gsi_interface;
        this.year = year;
        this.month = month;
        this.day = day;
        this.hour = hour;
        this.minute = minute;
        this.second = second;
        this.status = status;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
        gsi_interface = CORRESPONDING_ICP_OBJECT_INDEX.read(inputStream);
        year = INTEGER.read(inputStream);
        month = INTEGER.read(inputStream);
        day = INTEGER.read(inputStream);
        hour = INTEGER.read(inputStream);
        minute = INTEGER.read(inputStream);
        second = INTEGER.read(inputStream);
        status = INTEGER.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        outputStream.writeICPByte(messageCode);
        CORRESPONDING_ICP_OBJECT_INDEX.write(gsi_interface,outputStream);
        INTEGER.write(year,outputStream);
        INTEGER.write(month,outputStream);
        INTEGER.write(day,outputStream);
        INTEGER.write(hour,outputStream);
        INTEGER.write(minute,outputStream);
        INTEGER.write(second,outputStream);
        INTEGER.write(status,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
    }
}
