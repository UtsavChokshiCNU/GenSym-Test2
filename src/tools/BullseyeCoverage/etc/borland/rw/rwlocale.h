// $Revision: 5049 $ $Date: 2004-11-18 13:47:54 -0800 (Thu, 18 Nov 2004) $
// Copyright (c) Bullseye Testing Technology
// Work around syntax errors in the Borland C++Builder header rw/rwlocale.h

#if _RWSTD_VER == 0x020101
	// C++Builder version 5 and 6
	#include <rw/rwlocale.h-5.5>
#elif  _RWSTD_VER == 0x020100
	// C++Builder version 4
	#include <rw/rwlocale.h-5.4>
#elif  _RWSTD_VER == 0x0201
	// C++Builder version 3
	#include <rw/rwlocale.h-5.3>
#else
	#error Contact Bullseye Testing Technology - www.bullseye.com
#endif
