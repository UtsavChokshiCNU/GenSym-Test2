

//
// This is a example grid server in Java
//
// To run this example, use G2 5.0 or latter, load and start the feature.kb example
//

import idlGlobal.*;
import feature.*;
import org.omg.CORBA.*;


class gridImpl extends _gridImplBase {
	public int fetch(short x, short y) {
	    System.out.println("Got fetch request from G2");
		return 123;
	}

	public short width() {
	  System.out.println("Got get width request from G2");
	  return 100;
	}

	public short height() {
	  System.out.println("Got get height request from G2");
	  return 200;
	}
}



public class gridServer {
	public static void main(String args[]) {

		ORB orb = ORB.init(args, null); // create the orb object

		// Create the grid server object
		gridImpl gridRef = new gridImpl(); 
		orb.connect(gridRef); // tell the orb about it

		// Fetch the target in G2
		// This is a IOR from a G2 object
		org.omg.CORBA.Object objRef = orb.string_to_object("IOR:010000001d00000049444c3a666561747572652f636c69656e745461726765743a312e300000000001000000000000001f000000010100000a0000006c6f63616c686f7374003a060700000054617267657400");
		clientTarget targetRef = clientTargetHelper.narrow(objRef);
		// Now give G2 the object reference for the local server object
		targetRef.reg("grid", gridRef);


		// Now, just wait for requests from G2
		System.out.println("Server started, waiting for requests from G2\n");
		java.lang.Object sync = new java.lang.Object();
		synchronized (sync) {
			try {sync.wait();}
			catch (Exception e) {
			  System.err.println("Error: " + e);
			}
		}
	}
}

