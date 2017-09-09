
package com.gensym.gsi;

import java.io.*;
import java.net.*;
import java.util.*;

public class GSIListener extends Thread {
    int port = 22041;
    LinkedList gsisockets = new LinkedList();

    public GSIListener (int port) {
	this.port = port;
    }

    @Override
    public void run() {
	try {
	    ServerSocket ssck = new ServerSocket(port);
	    while (true) {
		Socket sck = ssck.accept();
		GSISocket gsisck = new GSISocket(sck,true);
		gsisockets.add(gsisck);
	    }
	} catch( IOException ex ) {
	    System.err.println( ex.toString() );
	}
    }

}
