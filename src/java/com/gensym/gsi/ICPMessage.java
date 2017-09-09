package com.gensym.gsi;

import java.io.IOException;

public interface ICPMessage extends ICPType {
    public void read (ICPInputStream inputStream)
        throws IOException;
    public void write (ICPOutputStream outputStream)
        throws IOException;
    public void run (GSISocket sck)
	throws IOException;
}
