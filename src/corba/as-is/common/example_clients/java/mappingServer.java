//
// This shows the mapping server java applet
// To run this applet, start G2 5.0 or higher and load the feature.kb
// Then run this applet
//

import idlGlobal.*;
import feature.*;
import org.omg.CORBA.*;

class mappingImpl extends _mappingImplBase {

	public void callShort(short val) {
		System.out.println(val);
	}

	public void callLong(int val) {
		System.out.println(val);
	}

	public void callUShort(short val) {
		System.out.println(val);
	}

	public void callULong(int val) {
		System.out.println(val);
	}

	public void callOctet(byte val) {
		System.out.println(val);
	}

	public void callChar(char val) {
		System.out.println(val);
	}

	public void callString(String val) {
		System.out.println(val);
	}

	public void callFloat(float val) {
		System.out.println(val);
	}

	public void callDouble(double val) {
		System.out.println(val);
	}

	public void callBoolean(boolean val) {
		System.out.println(val);
	}

	public void callStruct(feature.mappingPackage.myStruct val) {
		System.out.println(val);
	}

	public void callEnum(feature.mappingPackage.myEnum val) {
		System.out.println(val);
	}

	public void callSequence(String[] val) {
		System.out.println(val);
	}

    public void callRef(org.omg.CORBA.Object val) {
		System.out.println(val);
	}

	public void callArray(short[] val) {
		System.out.println(val);
	}

	public void callComplex(feature.mappingPackage.complexStruct[] val) {
		System.out.println(val);
	}
}


public class mappingServer {
	public static void main(String args[]) {

		ORB orb = ORB.init(args, null); // create the orb object

		// Create the grid server object
		mappingImpl mappingRef = new mappingImpl(); 
		orb.connect(mappingRef); // tell the orb about it

		// Fetch the target in G2
		// This is a IOR from a G2 object
		org.omg.CORBA.Object objRef = orb.string_to_object("IOR:010000001d00000049444c3a666561747572652f636c69656e745461726765743a312e300000000001000000000000001f000000010100000a0000006c6f63616c686f7374003a060700000054617267657400");
		clientTarget targetRef = clientTargetHelper.narrow(objRef);
		// Now give G2 the object reference for the local server object
		targetRef.reg("mapping", mappingRef);


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

