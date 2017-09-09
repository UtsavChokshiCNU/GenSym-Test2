//
// IOR and object reference support
//


#include <iostream_ver.h>
#include <stdlib.h> 
#include <string.h>                          
#include <stdio.h>
#include <ctype.h>

#include "G2ContainerClass.h"

#if defined( WIN32 )
#	include <windows.h>
#	include <windowsx.h>
#endif

#include "gsi_main_cpp.h"
#include "corba_main.h"
#include "iiop.h"


#define G2PROFILEID 0x4732

//
// We are able to read two kinds of object references.
// IOR's and URL's. We need to get a host name, port number
// and object key.  The object key is binary.
//
//
// Here is what our standard format looks like:
//   [HEXIOR],K:[IDL Kind],IH:[iiop host],IP:[iiop port],
//	  OK:[Object key],GK:[G2 host],GP:[G2 port]
//


// Return an error code to G2

void g2orb_return_symbol_string_error(char *code, char *mesg, void *call_index, gsi_int context_number)

{
	gsi_item *ret = gsi_make_items(2);
	gsi_set_sym(ret[0], code);
	gsi_set_str(ret[1], mesg);
	gsi_rpc_return_values(ret, 2, call_index, context_number);
	gsi_reclaim_items(ret);
}


// convert the kind field.  We throw out the version number and uppercase 
// everthing to make the match as liberal as possible.
void g2orb_simplify_idl_kind(char* p_dest, char* p_src) {

	int i;

	for (i = 0; p_src[i] != 0; i++) {
		if (p_src[i] == ':' && i > 3) {  // skip the version
			break;
		}

		p_dest[i] = toupper(p_src[i]);
	}

    p_dest[i] = 0;
}

// encode from binary to hex char
char objref2string_encodehex(unsigned char nib)

{
	nib &= 0x0f;
	if (nib < 10) return '0'+nib;
	return 'a'+nib-10;
}

void sequence2hex(iiop &seq, char *buf) {

	char *ptr = buf;
	unsigned char byte;
	for (unsigned i = 0; i < seq.len; i++) {
		byte = *(((unsigned char *) seq.data_ptr) + i);
		*ptr++ = objref2string_encodehex((byte >> 4) & 0x0f);
		*ptr++ = objref2string_encodehex(byte & 0x0f);
	}
	*ptr = 0;  // null term it
}

//
// This routine generates a text string of a decoded IOR.  This string is shorter and easyer to read
// than a standard IOR.  It is also easyer for G2 scan informaion from it.
//
// The return code depends on the IOR type.  There are a couple possiblites: 
//    1:  local object
//    2:  remote proxy
//    3:  remote g2 proxy
//
//
int binior2objref(iiop& ior, int context, G2String& decodedIOR)

{
	char *p_iiop_host = NULL;
    unsigned iiop_port = 0;
    unsigned char *p_object_key = NULL;
    int object_key_len = 0;
	char *p_object_kind = NULL;

    return binior2objrefEx(ior, context, decodedIOR, &p_iiop_host, &iiop_port,
        &p_object_key, &object_key_len, &p_object_kind);
}


//
// This routine generates a text string of a decoded IOR.  This string is shorter and easyer to read
// than a standard IOR.  It is also easyer for G2 scan informaion from it.
//
// The return code depends on the IOR type.  There are a couple possiblites: 
//    1:  local object
//    2:  remote proxy
//    3:  remote g2 proxy
//
//
int binior2objrefEx(iiop& ior, int context, G2String& decodedIOR,
                    char **pp_iiop_host, unsigned *p_iiop_port,
                    unsigned char **pp_object_key, int *p_object_key_len,
                    char **pp_object_kind)

{
	char retbuf[10240];
	char iortext[2048];
	char *kind = NULL;
	char *g2_host = NULL;
	unsigned g2_port = 0;
	G2String objkeybuf;
	G2OctSeq octobjkey;

	sequence2hex(ior, iortext);

	unsigned char flag = ior.decode_oct();  // byte ordering
	if (flag & 1) ior.little_endian = 1;
	else ior.little_endian = 0;
	
	kind = ior.decode_string();  //kind field
	*pp_object_kind = kind;

	int nprof = ior.decode_ulong();  // number of profiles
	if (ior.overrun_detected) return -1;

    // if the kind is empty and there are no profiles then
    //   this is a null object refercence so the iiop_host should
    //   point to an empty string, so will will use empty kind string.
    //   also the decoded IOR will just be an empty string.
    if (*kind == 0 && nprof == 0) {
        *pp_iiop_host = kind;
	    decodedIOR = "";

        // foriegn object
		return 2;
    }

	iiop profile;
	for (;nprof;nprof--) { // each profile
		int tag = ior.decode_ulong();
		if (ior.overrun_detected) return -1;
		if (!tag) { // internet_iop
			ior.decode_encap_sequence(profile);
			flag = profile.decode_oct();
          	if (flag & 1) profile.little_endian = 1;
			else profile.little_endian = 0;
			unsigned char major_ver = profile.decode_oct();
			unsigned char minor_ver = profile.decode_oct();
			if (major_ver != 1) return -1;
		
			*pp_iiop_host = profile.decode_string();
			*p_iiop_port = profile.decode_ushort();

			iiop objkey;
			profile.decode_encap_sequence(objkey);
			if (profile.overrun_detected) return -1;
			octobjkey.set_buf(objkey.data_ptr, objkey.len);
            
            *pp_object_key = (unsigned char*)objkey.data_ptr;
            *p_object_key_len = objkey.len;

            // IMPORTANT!!
            // This next statement has been removed because it causes
            // problems with any ORBs that allow the Object Key for
            // their server objects to have embedded nulls
            // or end in null.
            // This definitely caused OmniORB to not work with Corbalink
            // Erro msg was:  ...CORBA/OBJECT-NOT-EXIST...
            
            // if this is a correct g2 object the last byte of
            //   the object key should be zero anyways, but if
            //   not, setting it to zero will prevent and over
            //   run when we try to match the key

            // (*pp_object_key)[objkey.len - 1] = 0;

			char *tobjkeybuf = new char[(objkey.len * 2) + 1];
			sequence2hex(objkey, tobjkeybuf);
			objkeybuf = tobjkeybuf;
			delete tobjkeybuf;
		} else if (tag == G2PROFILEID) { // g2 profile
			ior.decode_encap_sequence(profile);
			flag = profile.decode_oct();
          	if (flag & 1) profile.little_endian = 1;
			else profile.little_endian = 0;

			// get version
			flag = profile.decode_oct();
			if (flag != 1) return -1;
			g2_port = profile.decode_ushort();
			g2_host = profile.decode_string();
		} else { // some tag we dont know anything about
			ior.decode_encap_sequence(profile);
		}
	}

	// Now, we have all of the pieces, make sure
	// that we did find a iiop profile

	if (*pp_iiop_host == NULL) return -1; // no iiop host
	// Now, check to see if this is a local object for this
	// g2.
	//   [HEXIOR],K=[IDL Kind],IH=[iiop host],IP=[iiop port],
	//	  OK:[Object key],GK:[G2 host],GP:[G2 port]
	int retcode;
	if (g2_host) {  // G2 object
		sprintf(retbuf,"%s,K=%s,IH=%s,IP=%u,OK=%s,GK=%s,GP=%d",
			iortext, kind, *pp_iiop_host, *p_iiop_port, (char *) objkeybuf,
			g2_host, g2_port);
		retcode = 3;
	} else { // foriegn object
		sprintf(retbuf,"%s,K=%s,IH=%s,IP=%u,OK=%s",
			iortext, kind, *pp_iiop_host, *p_iiop_port, (char *) objkeybuf);
		retcode = 2;
	} 

	decodedIOR = retbuf;

  if (debug_mode) {
    printf("  Decoded %s IOR: %s\n",
       profile.little_endian ? "little endian" : "big endian", retbuf);
  }

	return retcode;
}

void objref2string_encodeprofile(iiop &profile, char *host, unsigned port_number, 
								 G2OctSeq& obj_key,int flag) {
	iiop objkey;

	profile.encode_oct(profile.little_endian,flag);
	profile.encode_oct(1,flag);  // A IIOP 1.0 profile  
	profile.encode_oct(0,flag);
	profile.encode_string(host, flag);
	profile.encode_ushort(port_number, flag);
	objkey.data_ptr = obj_key.buf;
	objkey.len = obj_key.buf_len;
	objkey.owns_data = 0;
	profile.encode_encap_sequence(&objkey,flag);
}

void objref2string_encodeior(iiop &binior, char *kind, iiop &profile, iiop &g2profile, int flag) {

	int g2obj = g2profile.len;

	binior.encode_oct(binior.little_endian,flag); // little endian
	binior.encode_string(kind, flag); 
	if (g2obj) binior.encode_ulong(2,flag); // 2 profiles
	else binior.encode_ulong(1,flag); // 1 encoded profile
	binior.encode_ulong(0,flag);  // TAG_INTERNET_IOP profile
	binior.encode_encap_sequence(&profile, flag);
	if (g2obj) { // add g2 profile
		binior.encode_ulong(G2PROFILEID, flag);
		binior.encode_encap_sequence(&g2profile, flag);
	}
}

void objref2string_encodeg2profile(iiop &profile, char *host, unsigned port_number, int ver, int flag) {

	profile.encode_oct(profile.little_endian,flag); // byte order
	profile.encode_oct(ver, flag);
	profile.encode_ushort(port_number, flag);
	profile.encode_string(host, flag);
}

//
// Encode a object reference as a IOR
//
void genbinior(iiop& ior, char *kind, char *host, unsigned port_number, G2OctSeq& obj_key, char *g2host, 
				unsigned g2port, unsigned g2profilever) {

	iiop profile;
	iiop g2profile;

	// build the encoded profile
	objref2string_encodeprofile(profile, host, port_number, obj_key, 0);  // calc size
	profile.alloc_mem();
	objref2string_encodeprofile(profile, host, port_number, obj_key, 1);  // store it

	// build g2 profile, if needed
	if (g2host) {
		objref2string_encodeg2profile(g2profile, g2host, g2port, g2profilever, 0);
		g2profile.alloc_mem();
		objref2string_encodeg2profile(g2profile, g2host, g2port, g2profilever, 1);
	}

	// build the ior
	objref2string_encodeior(ior, kind, profile, g2profile, 0); 
	ior.alloc_mem();
	objref2string_encodeior(ior, kind, profile, g2profile, 1);
}


// Decode a url
// The url looks like //iiop host:iiop port[G2host:g2 port]/key

int url2binior(char *objref, char *inter, iiop& ior)

{
	G2String Host;
	G2String G2Host;
	unsigned port_number = 0;
	unsigned g2_port = 0;
	G2OctSeq object_key;
	char *ptr, *ptr1;

	for (ptr = &objref[2]; *ptr; ptr++) {
		if (*ptr == ':') break;
	}
	if (!*ptr) return 1;
	*ptr = 0;
	Host = &objref[2];
	ptr++;
	port_number = atoi(ptr);
	for (;*ptr; ptr++) {
		if (*ptr == '/') break;  // do not be picky about the seperator
		if (*ptr == '\\') break;
		if (*ptr == ':') break;
		if (*ptr == '[') break;
	}
	if (!*ptr) return 1;
	if (*ptr == '[') { // has g2 host and port
		ptr++;
		ptr1 = ptr;
		for (;*ptr;ptr++) {  // find the end
			if (*ptr == ':') break;
		}
		if (!*ptr) return 1;
		*ptr = 0;  // null term g2 host name
		G2Host = ptr1;  // save it
		ptr++;
		g2_port = atoi(ptr);
		for (;*ptr; ptr++) { // closing bracket
			if (*ptr == ']') break;
		}
		if (!*ptr) return 1;
		ptr++;  // skip seperator
	}
	// the rest is the object key
	ptr++;
	object_key.set_buf(ptr, strlen(ptr) + 1);

	genbinior(ior, inter, (char *) Host, port_number, object_key, G2Host, g2_port, 1);
	return 0;
}

int decodehex(char *hex, iiop& bin)

{
	// look for end of string
	char *endptr;
	int slen = 0;
	for (endptr = hex; *endptr; endptr++) {
		if (*endptr == ',') break;

		slen++;
	}

	if (slen & 1) return 1; // odd number of chars

	if (bin.owns_data && bin.data_ptr) delete (char *)bin.data_ptr;

    // we are done if there are no chars
	if (slen == 0) {
		bin.len = 0;
		bin.data_ptr = NULL;
		bin.owns_data = 0;
		return 0;
	}

    bin.len = slen >> 1;
	bin.data_ptr = new char[bin.len];
	bin.owns_data = 1;

	// Now convert the hex to binary
	char oldchar = *endptr;
	*endptr = 0; // make it null term
	unsigned char *dptr = (unsigned char *) bin.data_ptr;
	unsigned char work = 0;
	unsigned char odd = 0;
	for (unsigned char *cptr = (unsigned char *) hex; *cptr; cptr++) {
		work <<= 4;
		work &= 0xf0;
		if (*cptr >=  '0' && *cptr <= '9') 
			work |= 0x0f & (*cptr - '0');
		else if (*cptr >= 'a' && *cptr <= 'f') 
			work |= 0x0f & (*cptr - 'a' + 10);
		else if (*cptr >= 'A' && *cptr <= 'F')
			work |= 0x0f & (*cptr - 'A' + 10);
		else return 1; // invalid hex
		odd = !odd;
		if (!odd) *dptr++ = work;
	}
	*endptr = oldchar; // restore it
	return 0; // ok
}



// Unpack a user IOR

int ior2binior(char *objref, iiop& ior)

{
	int temp = decodehex(objref, ior);
	return temp;
}

//
// This rpc call convert a object ref from a URL or IOR to a decoded IOR.  Will also return a object handle
//.if the object is local.
//
//  Input:  String IOR or URL
//			Symbol Interface
//
//  Output:  Symbol status
//			 Text decoded IOR
//

void g2orb_decode_user_ref(void *proc_data, gsi_item args[], gsi_int count, void *call_index)

{
	if (count != 2 || gsi_type_of(args[0]) != GSI_STRING_TAG
		|| gsi_type_of(args[1]) != GSI_STRING_TAG) {
		g2orb_return_symbol_string_error("INVALID-ARGS", "", call_index, current_context);
		cout << "Invalid arguments to decode user ref" << endl;
		return;
	}

	char *objref = gsi_str_of(args[0]);
	char *inter = gsi_str_of(args[1]);

	iiop ior;  // create it in binary
	int temp;

	if (!strncmp(objref, "IOR:", 4)) {
		temp = ior2binior(&objref[4], ior);
	} else if ((!strncmp(objref, "//", 2)) ||
			(!strncmp(objref, "\\\\", 2))) {
		temp = url2binior(objref, inter, ior);
	} else temp = 1; // invalid
	if (temp) {
		g2orb_return_symbol_string_error("INVALID-REF", "", call_index, current_context);
		cout << "Attempt to convert invalid object ref:" << objref << " Interface:" << inter << endl;
		return;
	}

	// Ok, we now have a binary IOR, lets unpack it
	// We get a kind field, a integer object handle and a string

	ior.index = 0;
	G2String decodedIOR;
	temp = binior2objref(ior, current_context, decodedIOR);
	//
	// The possiblities are: error, local, remote
	if (temp == 2) { // remote
		g2orb_return_symbol_string_error("REMOTE", (char *) decodedIOR, call_index, current_context);
	} else if (temp ==3 ) { // remote G2
		g2orb_return_symbol_string_error("REMOTEG2", (char *) decodedIOR,  call_index, current_context);
	} else { // error
		g2orb_return_symbol_string_error("INVALID-REF", "", call_index, current_context);
		cout << "Attempt to convert invalid object ref:" << objref << " Interface:" << inter << endl;
	}
}

//
// Here we need to fetch the encap object ref in hex.
//
int objref2binior(char *objref, iiop& binior)

{

	int temp = ior2binior(objref, binior);
	if (temp) return -1;
	return 0;
}

//
// Pull the host, port and object key info out of a objref
//
int decodeobjref(char *objref, G2String& iiop_host, 
				 unsigned& iiop_port, G2OctSeq& objkey)

{
	//
	// The string is comma deliminated
	//
	// look for each comma and look at the case
	//
//   [HEXIOR],K=[IDL Kind],IH=[iiop host],IP=[iiop port],
//	  OK=[Object key],GK=[G2 host],GP=[G2 port]
	char *ptr  = objref;
	char *ptr1;
	unsigned char has_ok = 0;
	unsigned char has_ih = 0;
	unsigned char has_ip = 0;

	for (;1;) {
		for (;*ptr; ptr++) {
			if (*ptr == ',') {ptr++; break;}
		}
		if (!*ptr) break;

		if (*ptr == 'I') {
			ptr++;
			if (*ptr == 'H') { // iiop host
				ptr++; 
				if (*ptr != '=') return -1;
				ptr++;
				for (ptr1 = ptr; *ptr1; ptr1++) {  // look for end
					if (*ptr1 == ',') break;
				}
				if (!*ptr1) return -1;
				*ptr1 = 0;
				iiop_host = ptr; // save host
				*ptr1 = ','; // restore
				ptr = ptr1;
				has_ih = 1;
			} else if (*ptr == 'P') { // iiop port
				ptr++;
				if (*ptr != '=') return -1;
				ptr++;
				iiop_port = atoi(ptr); // get it
				has_ip = 1;
			}
		} else if (*ptr == 'O') { // should be object key
			ptr++;
			if (*ptr == 'K') { // got object key field
				ptr++;
				if (*ptr != '=') return -1;
				ptr++;
				iiop key;
				if (decodehex(ptr, key)) return -1;
				objkey.set_buf(key.data_ptr, key.len);
				has_ok = 1;
			}
		} // if
	} // for
	if (!has_ok || !has_ip || !has_ih) return -1;
	return 0;
}
				

//
// This rpc call will return the IOR of a registered server object
// This generates two profiles, a IIOP and a G2 profile.
//

void g2orb_object_to_string(void *proc_data, gsi_item args[], gsi_int count, void *call_index)

{
	if (count != 1 || gsi_type_of(args[0]) != GSI_STRING_TAG) {
		g2orb_return_symbol_string_error("INVALID-ARGS", "", call_index, current_context);
		cout << "Invalid args in object to string" << endl;
		return;
	}

	char *objid = gsi_str_of(args[0]);

	G2SObject *sObj = (G2SObject *) Objects.FindObj(objid);
	if (!sObj) { // object not registered
		g2orb_return_symbol_string_error("ERROR", "Object not registered", call_index, current_context);
		cout << "Attempt to generate a IOR of a unregistered object" << endl;
	}

	// Ok, now we need to find the interface and the kind

	char *inter = (char *) sObj->Interface;

	G2OrbContext *cObj = (G2OrbContext *) ContextObjs.FindObj(current_context);
	if (!cObj) {
		cout << "Unable to find context" << endl;
		g2orb_return_symbol_string_error("ERROR", "Unable to find context", call_index, current_context);
		return;
	}

	// Get Interface Object
	G2Interface *iObj = (G2Interface *) cObj->interfaces.FindObj(inter);
	if (!iObj) {
		cout << "Unable to find interface " << (char *) sObj->Interface
			<< " in context" << endl;
		g2orb_return_symbol_string_error("ERROR", "Unable to find interface", call_index, current_context);
		return;
	}

	char *kind = (char *) iObj->kind; // get kind
	G2OctSeq obj_key;
	obj_key.set_buf(objid, strlen(objid) + 1);

  	// We should have everything we need to generate the IOR

	iiop binior;
	genbinior(binior, kind, (char *) hostname, hostport, obj_key, (char *) cObj->hostname, cObj->g2_port, 1);

	// Now, convert it to text
	char buf1[4096];
	char buf2[4096];
	sequence2hex(binior, buf1);
	strcpy(buf2, "IOR:");
	strcat(buf2, buf1);
	if (debug_mode) {
		cout << "Generated IOR:" << buf1 << endl;
	}
	g2orb_return_symbol_string_error("SUCCESS", buf1, call_index, current_context);
}

//
// Register a G2 host and port number
// This must be called before G2 will geneate object references with g2 routing information
//


void g2orb_reg_g2(void *proc_data, gsi_item args[], gsi_int count, void *call_index)

{
	if (count != 2 || gsi_type_of(args[0]) != GSI_STRING_TAG 
		|| gsi_type_of(args[1]) != GSI_INTEGER_TAG) {
		g2orb_return_symbol_string_error("INVALID-ARGS", "", call_index, current_context);
		cout << "Invalid args in object to string" << endl;
		return;
	}

	// just find the context object and update it


	G2OrbContext *cObj = (G2OrbContext *) ContextObjs.FindObj(current_context);
	if (!cObj) {
		cout << "Unable to find context" << endl;
		g2orb_return_symbol_string_error("ERROR", "Unable to find context", call_index, current_context);
		return;
	}

	cObj->hostname = gsi_str_of(args[0]);
	cObj->g2_port = gsi_int_of(args[1]);
	g2orb_return_symbol_string_error("SUCCESS", "", call_index, current_context);
}

