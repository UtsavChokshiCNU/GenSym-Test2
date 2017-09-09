//
// Mapping client example
//
// This shows how to send all of the IDL types from java to G2.
//

import idlGlobal.*;
import org.omg.CORBA.*;

public class mappingClient {
	public static void main(String args[]) {

		ORB orb = ORB.init(args, null);

		org.omg.CORBA.Object objRef = orb.string_to_object("IOR:010000001800000049444c3a666561747572652f6d617070696e673a312e3000010000000000000027000000010100000a0000006c6f63616c686f7374003a060f0000006d617070696e672073657276657200");
		feature.mapping mappingRef = feature.mappingHelper.narrow(objRef);

		// Start calling methods in G2
		mappingRef.callShort((short) -323);
		mappingRef.callLong(-12345);
		mappingRef.callUShort((short)23);
		mappingRef.callULong(123456);
		mappingRef.callOctet((byte) 65);
		mappingRef.callChar('G');
		mappingRef.callString("Hello from Java!");
		mappingRef.callFloat((float) 3.141592653);
		mappingRef.callDouble(3.141592653);
		mappingRef.callBoolean(true);

		feature.mappingPackage.myStruct aStruct = new feature.mappingPackage.myStruct(1234, "Hi There!", 32.234);
		mappingRef.callStruct(aStruct);

		mappingRef.callRef(mappingRef);
		mappingRef.callEnum(feature.mappingPackage.myEnum.optionb);

		String[] aSeq = {"String1", "String2", "String3"};
		mappingRef.callSequence(aSeq);

		short[] aArr = {10,9,8,7,6,5,4,3,2,1};
		mappingRef.callArray(aArr);
	}
}

