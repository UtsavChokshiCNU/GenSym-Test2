#ifndef IIOP_H
#define IIOP_H

#include "gsi_main_cpp.h"
#include "G2ContainerClass.h"


#define G2C_LITTLE_ENDIAN 1
#define G2C_BIG_ENDIAN 0
#if defined(WIN32) || defined(linux)
#define NATURAL_CODING G2C_LITTLE_ENDIAN
#else
#define NATURAL_CODING G2C_BIG_ENDIAN
#endif

//
// IIOP object header
//


//
// Structure to hold a iiop message.  This is a single encaspulation 
//

class iiop {
public:
	unsigned short  decode_ushort(void);
	short           decode_short(void);
	long            decode_long(void);
	unsigned long   decode_ulong(void);
	void            decode_ullong(unsigned int *) ;
	unsigned char   decode_oct(void);
	float           decode_float(void);
	double          decode_double(void);
	char            *decode_string(void);
	void            decode_encap_sequence(iiop& profile);
	iiop(void);  
	~iiop();
	const iiop& operator=(iiop *);

	void encode_ushort(unsigned short val, int flag);
	void encode_short(short val, int flag);
	void encode_long(long val, int flag);
	void encode_ulong(unsigned long val, int flag);
	void encode_ullong(unsigned short vals[], int flag) ;
	void encode_oct(unsigned char val, int flag);
	void encode_string(char *ptr, int flag);
	void encode_encap_sequence(iiop *ptr, int flag);
	void encode_float(float val, int flag);
	void encode_double(double val, int flag);
	void align(unsigned char n);
	void encode_prim(void *ptr, unsigned char n, int flag);
	void decode_prim(void *ptr, unsigned char n);
	void *data_ptr;
	unsigned char little_endian;
	unsigned char overrun_detected;
	unsigned long index;
	unsigned long len;
	unsigned char owns_data;
	void alloc_mem(void);
	void reset(void);
	long pre_encode_len(int flag);
	void post_encode_len(long index, int flag);
};


#endif


