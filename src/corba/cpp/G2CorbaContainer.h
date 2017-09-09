#ifndef G2CORBACONTAINER
#define G2CORBACONTAINER

#include <time.h>
#include "G2ContainerClass.h"
#include "g2string.h"
#include "iiop.h"
#include "gsi_main_cpp.h"


class G2KindMap;

// Interface Sub-Class
// This object holds informaion about each interface definition.  IT mapps the interface name
// to a IR object.  It also holds a set of operations.
// The search key is the interface name.

class G2Interface:public G2OrbContained {
	public:
		G2String interface_name;		// Fully quailified Name of Interface
		G2String IRObj;					// Object id of IR object
		G2String kind;					// Kind field
		G2OrbContainer	operations;	// Collection of operations for this interface
		NoHashContainer  base_interfaces; // Collection of base interface objects
		virtual char * GetKey() {return (char *) interface_name;};	// Return interface name field
};

//
// This class holds a reference to a base interface
//

class G2BaseInterface:public G2OrbContained {
public:
	G2String Interface;		// pointer to base interface
};

// Context Sub-Class (Structure)
// This structure holds all of the informaion we need about a context
// The search key is the context number

class G2OrbContext:public G2OrbContained {
	public:
		gsi_item*		RepositoryHead;				// Pointer to G2 Repository Object for this context
		int				context_number;				// GSI context number
		G2OrbContainer	IRobjs;						// Collection of G2IRObjects objects
		G2OrbContainer	interfaces;					// Collection of G2Interface objects
		G2OrbContainer	proxies;					// Collection of Client objects
		G2OrbContainer	orbtypes;					// Collection of idl types
		G2OrbContainer  remoteDefs;					// remote method declarations
		G2OrbContainer	KindMap;					// object type to proxy type map
		G2String		G2Interface;				// Name of G2 interface	
		G2String		hostname;					// Name of G2 host
        G2String        principal;                  // The principal field for
                                                    //   outgoing GIOP headers
		unsigned		g2_port;					// G2 port number
		void *			rpc_locate_handle;			// GSI handle to receive locate requests
		void *			rpc_finalize_handle;		// GSI handle to receive finalize requests
		void *			rpc_purge_handle;			// GSI handle to purge objects
		void *			rpc_get_vers ; 			    // GSI handle to request versions of g2orb.kb & g2idl.kb
		unsigned char	paused;						// G2 paused flag
		unsigned char   has_locator;				// Has a locator

		G2OrbContext() {
						RepositoryHead = NULL;
						paused = 0;
						has_locator = 0;
						g2_port = 0;};				// Constructor
		virtual gsi_int GetHash() {return context_number;}; // Return context_number field
};

class RemoteDef:public G2OrbContained {
public:
	void * handle;
	G2String opName;
	virtual char *GetKey() { return (char *) opName;};
};

//
// This class holds a sequence of object handles that is used to nuke transient objects after decoding
//
class HandleHolder:public G2OrbContained {
public:
	long handle;
};

// Operation Sub-Class
// This is a quick way to map from an operation to the defining IR object

class G2Operation:public G2OrbContained {
	public:
		G2String	operation_name;					// Name of Operation
		G2String	IRObj;							// Object id of IR object
		unsigned char kind;							// 1 = op, 2 = get, 3 = set
		unsigned in_values;
		unsigned out_values;
		unsigned char isoneway;						// 1 if oneway, 0 if normal
		NoHashContainer inOrbTypes;
		NoHashContainer outOrbTypes;

		virtual char *  GetKey() {return (char *) operation_name;};	// Return Operation name field

};


// Client Request Sub-Class (Struccture)
// This object holds informaion about each pending client request.

class G2CRequest:public G2OrbContained {
	public:
		int			Context;					// G2 Context that initiated the request
		void *		CallIndex;					// G2 call index for request
		G2String	Interface;					// name of interface
		G2String	operation;					// name of operation
		unsigned long request_id;				// id for this req
		time_t		timeout_time;				// when the request times out
		unsigned char response_expected;
		unsigned char is_request;				// 1 = request, 0 = locate
		G2OctSeq	object_key;					// binary key value
		gsi_int		ObjHandle;					// object handle
		virtual gsi_int GetHash() {return request_id;};
};

//
// Server side request object
//

class G2SRequest:public G2OrbContained {
public:
	int Context;			// G2Context to handle request
	int CallIndex;			// used to match the GSI call
	unsigned long request_id; // request id from iiop message
	time_t timeout_time;  // when the request timeouts
	unsigned char response_expected;
	unsigned char reply_status;
	G2String Interface;		// name of interface for request
	G2String opname;		// name of operation
	unsigned long connection_id;  // socket connection to return request on
	virtual gsi_int GetHash() {return CallIndex;};
};

//
// Serverside Locate request object
//

class G2LRequest:public G2OrbContained {
public:
	iiop iiopObj;
	unsigned long requestid;
	unsigned long CallIndex;  // used to match GSI call
	unsigned char resp_expected;
	G2String objectkey;
	G2String opname;
	G2String principal;
	time_t timeout_time; // when the request timeouts
	gsi_int socket_id;
	unsigned char is_request;  // 1 = request, 0 = locate
	virtual gsi_int GetHash() {return CallIndex;};
};




// Client Objects Sub-Class

class G2CObject:public G2OrbContained {
	public:
		gsi_int			ObjHandle;					// G2 Object handle for Proxy object
		G2String		Interface;					// ID or IR Interface Object
		unsigned		port_number;				// Port Number
		G2String		Host;						// Host name
		unsigned		connection_id;				// Id of connection
		G2OctSeq		object_key;		
		G2OctSeq		forwarded_object_key;		// Id to use for existing connection
		virtual gsi_int GetHash() {return ObjHandle;};	// Return context_socket field
};



// Server Objects Sub-Class
// Since objects are tied to a G2, but the requests come in on no particular context,
// We need this data structure to resolve the context.

class G2SObject:public G2OrbContained {
	public:
		int				ObjHandle;					// G2 Object handle for Server object
		G2String		Marker;						// Object Id
		int				Context;					// Context Number
		G2String		Interface;					// full name of interface

		virtual char *  GetKey() {return (char *) Marker;};	// Return Marker field
		virtual unsigned char is_valid_for_connection(int C) { return 1; }
		virtual unsigned char add_private_connection(int C) { return 0; }
		virtual void remove_private_connection(void) { }
		virtual unsigned char can_finalize(void) { return 0; }
};

// Private Server Objects

class G2PSObject:public G2SObject {
public:
	int ref_count;		// Number of connections allowing this private object
	virtual unsigned char is_valid_for_connection(int C);
	virtual unsigned char add_private_connection(int C);
	virtual void remove_private_connection(void);
	virtual unsigned char can_finalize(void) { if (!ref_count) return 1; else return 0;}
	virtual ~G2PSObject();
	G2PSObject() {ref_count = 0;};
};
	
	
// IR Objects Sub-Class
// This structure provides quick way to find IR objects in a given context given the Id

class G2IRObject:public G2OrbContained {
	public:
		G2String		ID;						// Text string of object id from G2
		gsi_item		ref;					// pointer to gsi object

		virtual char * GetKey() {return (char *) ID;};	// Return ID field
};

class G2SubString: public G2OrbContained {
public:
	G2String	str;
	G2SubString(char *ptr) { str = ptr;};
	~G2SubString();
	virtual char *GetKey() { return (char *) str;};
};

// Kind Map.  This object is used to map a object type to its proxy class

class G2KindMap : public G2OrbContained {
public:
	G2String kind;
	G2String objectClass;
	virtual char *GetKey() {return (char *) kind;};
};



#endif

