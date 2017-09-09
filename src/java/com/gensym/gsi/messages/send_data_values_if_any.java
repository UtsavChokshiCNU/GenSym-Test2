
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

public class send_data_values_if_any implements ICPMessage {
    public static short messageCode = 73;
    private static final int GSI_INTERFACE_RUNNING_OK = 2;
    private ICPStream stream = null;

    int gsi_interface = 0;
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    int second = 0;

    public send_data_values_if_any () {}
    public send_data_values_if_any (int gsi_interface, int year, int month, int day, int hour, int minute, int second) {
        this.gsi_interface = gsi_interface;
        this.year = year;
        this.month = month;
        this.day = day;
        this.hour = hour;
        this.minute = minute;
        this.second = second;
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
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
	// not written by GSI
        stream = outputStream;
        outputStream.writeICPByte(messageCode);
        CORRESPONDING_ICP_OBJECT_INDEX.write(gsi_interface,outputStream);
        INTEGER.write(year,outputStream);
        INTEGER.write(month,outputStream);
        INTEGER.write(day,outputStream);
        INTEGER.write(hour,outputStream);
        INTEGER.write(minute,outputStream);
        INTEGER.write(second,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
	if (sck.indexOfGSIInterface == -1) {
	    sck.indexOfGSIInterface = gsi_interface;
	} else {
	    sck.writeICPMessage(new receive_value_for_ping_request
				(gsi_interface, 
				 year, month, day, hour, minute, second,
				 GSI_INTERFACE_RUNNING_OK));
	    // queue a gsi-g2-poll
	}
    }
}
