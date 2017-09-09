
package com.gensym.gsi;

import java.io.*;
import java.net.*;
import java.util.*;
import com.gensym.gsi.GSIMessageMap;

public class GSISocket extends Thread implements ICPSocket {

    String state;
    Socket sck;
    ICPInputStream in;
    ICPOutputStream out;
    Map remoteVersionInfo = null;
    String remoteProcessInitializationString;
    public int indexOfGSIInterface = -1;

    private Queue incomingUserMessages = new Queue();

    public void setRemoteProcessInitializationString(String text_string) {
	remoteProcessInitializationString = text_string;
    }

    GSISocket (Socket sck, boolean server) throws IOException {
	this.sck = sck;
	sck.setTcpNoDelay(true);
	in = new ICPInputStream (this, GSIMessageMap.map, sck.getInputStream());
	out = new ICPOutputStream (this, sck.getOutputStream());
	if (server) {
	    // send initial messages
	}
    }

    GSISocket(String host, int port) throws IOException {
	this (new Socket(host,port),false);
    }
    
    public void writeICPMessage(ICPMessage m) throws IOException{
	out.writeICPMessage(m);
    }

    void enqueueIncomingUserMessage (ICPMessage m) {
	incomingUserMessages.enqueueMessage(m);
    }

    public ICPMessage getNextMessage() {
	return (ICPMessage)(incomingUserMessages.getNextMessage());
    }	

    @Override
    public void run() {
	try {
	    while (true)
		in.readICPMessage().run(this);
	} catch (IOException e) {
	    close();
	}
    }

    public void close() {
	try {in.close();} catch (IOException e) {}
	in = null;
	try {out.close();} catch (IOException e) {}
	out = null;
	try {sck.close();} catch (IOException e) {}
	sck = null;
    }

}
