#include "packaging.h"

long isG2Enterprise() {

#ifdef PACKAGING_G2_ENTERPRISE
	return 1;
#else 
	return 0;
#endif

}
