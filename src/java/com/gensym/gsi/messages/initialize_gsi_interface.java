
package com.gensym.gsi.messages;

import com.gensym.gsi.*;
import com.gensym.gsi.types.*;
import java.io.IOException;

import com.gensym.util.Symbol;

public class initialize_gsi_interface implements ICPMessage {
    public static short messageCode = 338;
    private ICPStream stream = null;

    Symbol interface_name = null;
    Symbol class_name = null;
    boolean keep_connection_on_g2_reset = false;
    Symbol listener_network_type = null;
    String listener_host_name = null;
    String listener_port_name = null;
    String remote_process_initialization_string = null;

    public initialize_gsi_interface () {}
    public initialize_gsi_interface (Symbol interface_name, Symbol class_name, boolean keep_connection_on_g2_reset, Symbol listener_network_type, String listener_host_name, String listener_port_name, String remote_process_initialization_string) {
        this.interface_name = interface_name;
        this.class_name = class_name;
        this.keep_connection_on_g2_reset = keep_connection_on_g2_reset;
        this.listener_network_type = listener_network_type;
        this.listener_host_name = listener_host_name;
        this.listener_port_name = listener_port_name;
        this.remote_process_initialization_string = remote_process_initialization_string;
    }
    @Override
    public void read (ICPInputStream inputStream)
        throws IOException {
	// never read by GSI
        interface_name = SYMBOL.read(inputStream);
        class_name = SYMBOL.read(inputStream);
        keep_connection_on_g2_reset = BOOLEAN.read(inputStream);
        listener_network_type = SYMBOL.read(inputStream);
        listener_host_name = TEXT_STRING.read(inputStream);
        listener_port_name = TEXT_STRING.read(inputStream);
        remote_process_initialization_string = TEXT_STRING.read(inputStream);
        inputStream.readICPMessageGroupEnd();
    }
    @Override
    public void write (ICPOutputStream outputStream)
        throws IOException {
        stream = outputStream;
        SYMBOL.initialWrite(interface_name,outputStream);
        SYMBOL.initialWrite(class_name,outputStream);
        SYMBOL.initialWrite(listener_network_type,outputStream);
        outputStream.writeICPByte(messageCode);
        SYMBOL.write(interface_name,outputStream);
        SYMBOL.write(class_name,outputStream);
        BOOLEAN.write(keep_connection_on_g2_reset,outputStream);
        SYMBOL.write(listener_network_type,outputStream);
        TEXT_STRING.write(listener_host_name,outputStream);
        TEXT_STRING.write(listener_port_name,outputStream);
        TEXT_STRING.write(remote_process_initialization_string,outputStream);
        outputStream.endICPMessageGroup();
    }
    @Override
    public void run (GSISocket sck) throws IOException {
	// never read by GSI
    }
}
