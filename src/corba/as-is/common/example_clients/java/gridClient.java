

/*
 * This is a sample Java Client to run the Grid Example.  This assumes that the "feature.kb" 
 * KB is running and it has a Grid object with the id "Grid Server" at localhost:1594.  
 * 
 * To run this example, use G2 5.0 or latter, load and start the feature.kb example that comes
 * with G2-CORBALink.  
 */

import idlGlobal.*;
import org.omg.CORBA.*;

public class gridClient {
	public static void main(String args[]) {

		ORB orb = ORB.init(args, null); // Create the orb object  

		// This creates a object reference to a "Grid" object on localhost port 1594.
		// This IOR was obtained from G2 and cut and pasted here.  It could have come from
		// a Name Server
		org.omg.CORBA.Object objRef = orb.string_to_object(
"IOR:010000000d00000049444c3a677269643a312e3000000000010000000000000024000000010100000a0000006c6f63616c686f7374003a060c000000477269642053657276657200" );
		grid gridRef = gridHelper.narrow(objRef); // make it a grid object reference

		int Width = gridRef.width();
		int Height = gridRef.height();
		int val = gridRef.fetch((short) 3, (short) 4);
		System.out.println("Grid Width from G2: " + Width + ", Height: " + Height + ", fetch(3,4) = " + val);
	}
}


