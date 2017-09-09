
package com.gensym.gsi;

import java.util.*;
import com.gensym.gsi.*;

public class Queue {

    private LinkedList messages = new LinkedList();

    public synchronized void enqueueMessage(Object message) {
	messages.addLast(message);
	notifyAll();
    }

    public synchronized Object dequeueMessage() {
	return messages.removeFirst();
    }

    public synchronized Object getNextMessage() {
	while (messages.size() == 0) {
	    try {wait();}
	    catch (InterruptedException e) {}
	}
	return dequeueMessage();
    }

    public synchronized boolean nextMessageAvailable() {
	return messages.size() > 0;
    }

}
