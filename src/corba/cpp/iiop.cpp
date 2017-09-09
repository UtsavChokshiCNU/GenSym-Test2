#include <iostream_ver.h>
#include <string.h>
#include "iiop.h"
#include "G2ContainerClass.h"
#include "G2CorbaContainer.h"
#include "corba_main.h"


//
// Ok, here are the methods for the iiop object
//

iiop::iiop() {
	data_ptr = NULL;
	index = 0;
	len = 0;
	little_endian = NATURAL_CODING;
	overrun_detected = 0;
	owns_data = 1;
}

// copy constructor
const iiop& iiop::operator=(iiop *RHS) {
	little_endian = RHS->little_endian;
	overrun_detected = RHS->overrun_detected;
	index = RHS->index;
	len = RHS->len;
	owns_data = RHS->owns_data;
	RHS->owns_data = 0;		// steal data
	data_ptr = RHS->data_ptr;
	return *this;
}

iiop::~iiop() {
	if (!owns_data) return;
	if (data_ptr) delete (char *)data_ptr;
}

void iiop::alloc_mem(void) {
	data_ptr = new char[index];
	memset(data_ptr, 0, index);
	len = index;
	index = 0;
	owns_data = 1;
}

void iiop::reset(void) {
	index = 0;
}

//
// Routine to make encap sequences simpler
//
long iiop::pre_encode_len(int flag) {
	int temp = index;
	encode_ulong(0, flag);
	return temp;
}

void iiop::post_encode_len(long oldIndex, int flag) {
	int len = index - oldIndex - 4;
	int temp = index;
	index = oldIndex;
	encode_ulong(len, flag);
	index = temp;
}




//
// Bump the index so that we are alinged.
void iiop::align(unsigned char n)
{
  switch (n) {
	case 1: break;
	case 2: 
		if (index & 1) index++;
		break;
	case 4:
		if (index & 3) {
			index |= 3;
			index++;
		}
		break;
	case 8:
		if (index & 7) {
			index |= 7;
			index++;
		}
		break;
	default:
		cout << "Invalid alignment" << endl;
		break;
  }
}

void iiop::decode_prim(void *ptr, unsigned char n) {

	align(n);
	if (index + n > len) {
		overrun_detected = 1;
		memset(ptr, 0, n);
	}
	if (little_endian == NATURAL_CODING) {
		memcpy(ptr, (void *) ((unsigned char *) data_ptr + index), n);
	} else { // flip them
		unsigned char *sptr = (unsigned char *) data_ptr + index;
		unsigned char *dptr = (unsigned char *) ptr;
		for (int i = (int) n - 1; i >= 0; i--) {
			*dptr++ = sptr[i];
		}
	}
	index += n;
}

void iiop::encode_prim(void *ptr, unsigned char n, int flag) {

	align (n);

	if (flag) {
		if (little_endian == NATURAL_CODING) {
			memcpy((void *) ((unsigned char *) data_ptr + index), ptr, n);
		} else {
			unsigned char *sptr = (unsigned char *) ptr;
			unsigned char *dptr = (unsigned char *) data_ptr + index;
			for (int i = (int) n - 1; i >= 0; i--) {
				*dptr++ = sptr[i];
			}
		}
	}
	index += n;
}



unsigned char iiop::decode_oct(void)

{
	unsigned char ret;

	if (index + 1 > len) {
		overrun_detected = 1;
		return 0;
	}

	ret = *((unsigned char *) data_ptr + index);
	index++;
	return ret;
}

void iiop::encode_oct(unsigned char val, int flag)

{
	if (flag) *((unsigned char *) data_ptr + index) = val;
	index++;
}

unsigned long iiop::decode_ulong(void) {

	unsigned long ret;

	if (little_endian == NATURAL_CODING) { // opted for same coding
		if (index & 3) { // align
			index |= 3;
			index++;
		}	
		if (index + 4 > len) {
			overrun_detected = 1;
			return 0;
		}
		ret = *((unsigned long *) ((unsigned char *) data_ptr + index));
		index += 4;
	} else decode_prim(&ret, 4);
	return ret;
}

void iiop::encode_ulong(unsigned long val, int flag) {

	if (little_endian == NATURAL_CODING) {
		if (index & 3) {
			index |= 3;
			index++;
		}
		if (flag) *((unsigned long *) ((unsigned char *) data_ptr + index)) = val;
		index += 4;
	} else encode_prim(&val, 4, flag);
}

long iiop::decode_long(void) {

	long ret;

	if (little_endian == NATURAL_CODING) { // opted for same coding
		if (index & 3) {
			index |= 3;
			index++;
		}	
		if (index + 4 > len) {
			overrun_detected = 1;
			return 0;
		}
		ret = *((long *) ((unsigned char *) data_ptr + index));
		index += 4;
	} else decode_prim(&ret, 4);
	return ret;
}

void iiop::encode_long(long val, int flag) {

	if (little_endian == NATURAL_CODING) {
		if (index & 3) {
			index |= 3;
			index++;
		}
		if (flag) *((long *) ((unsigned char *) data_ptr + index)) = val;
		index += 4;
	} else encode_prim(&val, 4, flag);
}

void iiop::decode_ullong(unsigned int *vals)
{
        short    vidx, incx, dst, offset ;

    align(8) ;

    if (little_endian)
    {
        vidx = 0 ;
        incx = 1 ;
        dst = 4 ;
    }
    else
    {
        vidx = 3 ;
        incx = -1 ;
        dst = -1 ;
    }
    while (vidx != dst)
    {
        vals[vidx]=0 ;
        offset = (NATURAL_CODING == 0) ? (sizeof(unsigned int)-2) : 0 ;
        decode_prim( ( (unsigned char*)(vals+vidx) + offset), 2) ;
        vidx += incx ;
    }
}

void iiop::encode_ullong(unsigned short vals[], int flag)
{
	if (little_endian == NATURAL_CODING)
    {
		if (index & 7)
        {
			index |= 7;
			index++;
		}
        for (int i = 0 ; i < 4 ; i++)
        {
		    if (flag) *((unsigned short *) ((unsigned char *) data_ptr + index)) = vals[i];
		    index += 2;
        }
	} else
    {
        encode_prim(&(vals[3]), 2, flag);
        encode_prim(&(vals[2]), 2, flag);
        encode_prim(&(vals[1]), 2, flag);
        encode_prim(&(vals[0]), 2, flag);
    }
}

unsigned short iiop::decode_ushort(void) {

	unsigned short ret;

	if (little_endian == NATURAL_CODING) { // opted for same coding
		if (index & 1) index++;
		if (index + 2 > len) {
			overrun_detected = 1;
			return 0;
		}
		ret = *((unsigned short *) ((unsigned char *) data_ptr + index));
		index += 2;
	} else decode_prim(&ret, 2);
	return ret;
}

void iiop::encode_ushort(unsigned short val, int flag) {

	if (little_endian == NATURAL_CODING) {
		if (index & 1) index++;
		if (flag) *((unsigned short *) ((unsigned char *) data_ptr + index)) = val;
		index += 2;
	} else encode_prim(&val, 2, flag);
}

short iiop::decode_short(void) {

	short ret;

	if (little_endian == NATURAL_CODING) { // opted for same coding
		if (index & 1) index++;
		if (index + 2 > len) {
			overrun_detected = 1;
			return 0;
		}
		ret = *((short *) ((unsigned char *) data_ptr + index));
		index += 2;
	} else decode_prim(&ret, 2);
	return ret;
}

void iiop::encode_short(short val, int flag) {

	if (little_endian == NATURAL_CODING) {
		if (index & 1) index++;
		if (flag) *((short *) ((unsigned char *) data_ptr + index)) = val;
		index += 2;
	} else encode_prim(&val, 2, flag);
}

float iiop::decode_float(void) {

	float ret;

	if (little_endian == NATURAL_CODING) { // opted for same coding
		if (index & 3) {
			index |= 3;
			index++;
		}	
		if (index + 4 > len) {
			overrun_detected = 1;
			return (float) 0.0;
		}
		ret = *((float *) ((unsigned char *) data_ptr + index));
		index += 4;
	} else decode_prim(&ret, 4);
	return ret;
}

void iiop::encode_float(float val, int flag) {

	if (little_endian == NATURAL_CODING) {
		if (index & 3) {
			index |= 3;
			index++;
		}
		if (flag) *((float *) ((unsigned char *) data_ptr + index)) = val;
		index += 4;
	} else encode_prim(&val, 4, flag);
}

double iiop::decode_double(void) {

	double ret;

	if (little_endian == NATURAL_CODING) { // opted for same coding
		if (index & 7) {
			index |= 7;
			index++;
		}	
		if (index + 8 > len) {
			overrun_detected = 1;
			return 0.0;
		}
		ret = *((double *) ((unsigned char *) data_ptr + index));
		index += 8;
	} else decode_prim(&ret, 8);
	return ret;
}

void iiop::encode_double(double val, int flag) {


	if (little_endian == NATURAL_CODING) {
		if (index & 7) {
			index |= 7;
			index++;
		}
		if (flag) *((double *) ((unsigned char *) data_ptr + index)) = val;
		index += 8;
	} else encode_prim(&val, 8, flag);
}


void iiop::decode_encap_sequence(iiop& iiopObj)

{
	unsigned long elen = decode_ulong();
	if (index + elen > len) {
		overrun_detected = 1;
		return;
	}
	if (iiopObj.owns_data && iiopObj.data_ptr!=NULL) delete (char *)data_ptr;
	iiopObj.data_ptr = (void *) (((char *) data_ptr) + index);
	iiopObj.index = 0;
	iiopObj.len = elen;
	iiopObj.little_endian = little_endian;
	iiopObj.owns_data = 0;  // this is a copy of data
	index += elen;
}

void iiop::encode_encap_sequence(iiop *iiopObj, int flag)

{
	encode_ulong(iiopObj->len, flag);
	if (flag) memcpy((char *) data_ptr + index, iiopObj->data_ptr,
		iiopObj->len);
	index += iiopObj->len;
}



char *iiop::decode_string(void)

{
	static char null_buf[1] = "";

	char *ptr;
	unsigned long elen = decode_ulong();
	if (index + elen > len) {
		overrun_detected = 1;
		return NULL;
	}
	ptr = ((char *) data_ptr) + index;
	if (elen) ptr[elen-1] = 0;  // make sure it is terminated
	else return null_buf; // zero length string 
	index += elen;
	return ptr;
}

void iiop::encode_string(char *buf, int flag)

{
	if (!buf) {
		encode_ulong(1, flag);
		encode_oct(0, flag);
		return;
	}
	unsigned len = strlen(buf) + 1;
	encode_ulong((unsigned long) len, flag);
	if (flag) {
		char *ptr = ((char *) data_ptr) + index;
		strcpy(ptr, buf);
	}
	index += len;
}


void process_iiop_request(iiop *iiopObj, socket_data *sdata)

{
	if (debug_mode) cout << "  Request message" << endl;
	unsigned long nsrv = iiopObj->decode_ulong();
	iiop srvreq;
	for (unsigned long i = 0; i < nsrv; i++) {
		// Decode service request data
		unsigned long srv_id = iiopObj->decode_ulong();
                // cout << "  Service Request Packet of type: " << srv_id << endl;
		iiopObj->decode_encap_sequence(srvreq);
	}
	unsigned long requestid = iiopObj->decode_ulong();
	unsigned char resp_expected = iiopObj->decode_oct();
	char *objectkey = iiopObj->decode_string();
	char *opname = iiopObj->decode_string();
	char *principal = iiopObj->decode_string();
	if (iiopObj->overrun_detected) {
		cout << "Received Invalid IIOP Request Header" << endl;
		return;
	}
	if (debug_mode) {
		cout << "  Request Id: " << requestid << endl;
    printf("  Response Expected: %s\n", resp_expected ? "true" : "false");
		cout << "  Object Key: " << objectkey << endl;
		cout << "  Operation: " << opname << endl;
		cout << "  Principal: " << principal << endl;
	}

	got_server_request(iiopObj, requestid, resp_expected, objectkey, 
 		opname, principal, sdata);
}


void process_iiop_reply(iiop *iiopObj)

{
	if (debug_mode) cout << "  Reply message" << endl;
	unsigned long nsrv = iiopObj->decode_ulong();
	iiop srvreq;
	for (unsigned long i = 0; i < nsrv; i++) {
		// Decode service request data
		unsigned long srv_id = iiopObj->decode_ulong();
                // cout << "  Service Request Packet of type: " << srv_id << endl;
		iiopObj->decode_encap_sequence(srvreq);
	}
	unsigned long requestid = iiopObj->decode_ulong();
	unsigned char reply_status = (unsigned char) iiopObj->decode_ulong();
	if (iiopObj->overrun_detected) {
		cout << "** Received Invalid IIOP Reply Header" << endl;
		return;
	}
	if (debug_mode) {
		cout << "  Request Id: " << requestid << endl;
		cout << "  Status: " <<  (int) reply_status << endl;
	}
	//
	// Ok, we got a valid reply message.  Now find the
	// request object
	//
	G2CRequest *rObj = (G2CRequest *) RequestObjs.FindObj(requestid);
	if (!rObj) {
		cout << "  Request ID for reply not valid" << endl;
		return;
	}
	got_request_reply(rObj, iiopObj, reply_status);
}

void process_iiop_cancel_request(iiop *iiopObj)

{
	cout << "  Cancel request message- no action" << endl;
}

void process_iiop_locate_request(iiop *iiopObj, socket_data *sdata)

{
	if (debug_mode) cout << "  Locate request message" << endl;
	
	unsigned long requestid = iiopObj->decode_ulong();
	char *objectkey = iiopObj->decode_string();

	if (debug_mode) {
		cout << "  Request Id: " << requestid << endl;
		cout << "  Object Key: " << objectkey << endl;
	}

	got_locate_request(objectkey, requestid, sdata);
}

void process_iiop_locate_reply(iiop *iiopObj)

{ 
	if (debug_mode) cout << "  Locate reply message" << endl;

	unsigned long requestid = iiopObj->decode_ulong();
	unsigned char reply_status = (unsigned char) iiopObj->decode_ulong();
	if (iiopObj->overrun_detected) {
		cout << "Received Invalid IIOP Locate Reply Header" << endl;
		return;
	}
	if (debug_mode) {
		cout << "  Request Id: " << requestid << endl;
		cout << "  Status: " <<  (int) reply_status << endl;
	}
	//
	// Ok, we got a valid reply message.  Now find the
	// request object
	//
	G2CRequest *rObj = (G2CRequest *) RequestObjs.FindObj(requestid);
	if (!rObj) {
		cout << "Request ID for reply not valid" << endl;
		return;
	}
	got_locate_request_reply(rObj, iiopObj, reply_status);
}

void process_iiop_close_connection(iiop *iiopObj)

{
	cout << "Unable to process close connection" << endl;
}

void process_iiop_message_error(iiop *iiopObj)

{
	cout << "Unable to process message error" << endl;
}

void process_iiop_message_fragment(iiop *iiopObj)

{
	cout << "Unable to process message fragment" << endl;
}



//
// This file has the core routines for using IIOP messages.
//

void  process_iiop_message(void *iiopmesg, unsigned long mesg_len, unsigned char little_endian, 
						   unsigned char mesg_type, socket_data *sdata)

{
	iiop iiopObj;
	iiopObj.data_ptr = iiopmesg;
	iiopObj.owns_data = 0;
	iiopObj.index = 12;
	iiopObj.little_endian = little_endian & 1;
	iiopObj.len = mesg_len + 12;

	switch (mesg_type) {
	case 0: // Request
		process_iiop_request(&iiopObj,sdata);
		break;
	case 1: // Reply
		process_iiop_reply(&iiopObj);
		break;
	case 2: // cancel request
		process_iiop_cancel_request(&iiopObj);
		break;
	case 3: // locaterequest
		process_iiop_locate_request(&iiopObj, sdata);
		break;
	case 4: // locate reply
		process_iiop_locate_reply(&iiopObj);
		break;
	case 5: // close connection
		process_iiop_close_connection(&iiopObj);
		break;
	case 6: // message error
		process_iiop_message_error(&iiopObj);
		break;
	case 7: // fragment
		process_iiop_message_fragment(&iiopObj);
		break;

	}
}

