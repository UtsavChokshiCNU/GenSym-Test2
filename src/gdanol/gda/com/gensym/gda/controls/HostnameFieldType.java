
package com.gensym.gda.controls;

import java.io.IOException;
import java.io.EOFException;
import java.net.InetAddress;
import java.net.UnknownHostException;


import com.gensym.types.G2TokenizerException;
import com.gensym.types.G2ParserException;
import com.gensym.controls.FieldType;

/**
*Field Type class for valid host name
*/
public class HostnameFieldType extends FieldType {
    
    /**
    *Construct the object by calling super("Text")
    */
    public HostnameFieldType() {
        super("Text");
    }

    /**
    *Trys to convert a string to a valid host name.
    *@param s string that is candidat for the host name
    *@throws G2ParserException when it is impossible to create
    *InetAddress from the string
    *@see java.net.InetAddress InetAddress
    */
    public Object stringToObject(String s)
        throws G2TokenizerException, G2ParserException, EOFException, IOException {

        String str = (String)super.stringToObject(s);
        
        if("".equals(str))
            return str;
            
        try
        {
            InetAddress adr = InetAddress.getByName(str);
            return adr.getHostName();
        }
        catch(UnknownHostException unknownhostexception)
        {
            throw new G2ParserException("Invalid host name");
        }
    }
    
}