//
// This is a sample Java server to receive events from the publish.kb example
// Start G2 with the publish.kb, then run this applicaion.
//


import idlGlobal.*;
import org.omg.CORBA.*;

class consumerImpl extends _eventConsumerImplBase {

	public short event(eventCodes eventType) {
		switch ((int) eventType.value()) {
			case 0: System.out.println("Red"); break;
			case 1: System.out.println("Blue"); break;
			case 2: System.out.println("Green"); break;
		}
		return 1;
	}
}


public class consumer {
	public static void main(String args[]) {

		ORB orb = ORB.init(args, null); // create the orb object

		// Create the consumer object
		consumerImpl consumerRef = new consumerImpl(); 
		orb.connect(consumerRef); // tell the orb about it

		// Fetch the event channel in G2
		// This is a IOR from a G2 object
		org.omg.CORBA.Object objRef = orb.string_to_object("IOR:010000001600000049444c3a6576656e74436f6e73756d65723a312e30000000010000000000000028000000010100000a0000006c6f63616c686f7374003a06100000006576656e7420666f7277617264657200");
		eventChannel channelRef = eventChannelHelper.narrow(objRef);
		// Now subscribe to the G2 events
		try {channelRef.subscribe(consumerRef);}
		catch (idlGlobal.eventChannelPackage.reject e) {
		  System.err.println("Error: " + e.reason);
		}

		// Now, just wait for requests from G2
		System.out.println("Consumer started, waiting for events from G2\n");
		java.lang.Object sync = new java.lang.Object();
		synchronized (sync) {
			try {sync.wait();}
			catch (Exception e) {
			  System.err.println("Error: " + e);
			}
		}
	}
}
