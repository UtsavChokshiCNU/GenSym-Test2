/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      java_gsi.h
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):
 +               17-Sep-1996   M,D,Gribble
 +
 + Description:  This file contains the general H definitions for the
 +				 Java GSI
 +               
 +               
 + 
 + Key:
 +   +++++++ Module Header.   Used for file-wide information.
 +   %%%%%%% Section Header.  Used to delimit logical sections.
 +   ******* Function Header. Used to define a single function.
 +
 +   0000000 Externally visible function
 +   1111111 Internal (static) function
 +   ??????? Function existence is questionable.
 +
 +   A function banner may contain the following: 
 +      Multiply Defined       Function appears multiple times, each definition
 +                             for an #ifdef specified platform.
 +      Conditionally Defined  Defined for some but not all platforms
 +      Mixed Ifdefs           Single definition for function containing
 +                             platform specific code #ifdef's.
 +
 + File Organization:
 +   Section:      INCLUDE FILES 
 +   Section:      DEFINES
 +   Section:      GLOBALS
 +   Section:      DECLARATION FUNCTIONS
 +
 +      
 + External Interface:
 +
 + Dependencies:
 +      This file has no external dependencies.
 +
 + Notes:
 +
 + Modifications:
 +   usage: All modifications to this file should be listed here, with most
 +          recent first. In general, modification comments should merely
 +          provide a reference to a detailed modification comment in the
 +          appropriate section/function header.
 +
 +
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      INCLUDE FILES
 %
 % Description:  All required include files are referenced here.
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#include <stdarg.h>
#include <stdio.h>

#include "com_gensym_jgsi_GsiInterface.h"
#include "com_gensym_jgsi_GsiLoopThread.h"
/*#include "com_gensym_jgsi_GsiRemoteRPCThread.h" */
#include "com_gensym_jgsi_GsiRemoteRPCThreadData.h"
#include "jgsi_locks.h"
#include "gsi_main.h"
#include "gsi_misc.h"

#include "com_gensym_util_G2ItemProxy.h"
#include "com_gensym_util_Structure.h"
#include "com_gensym_util_Sequence.h"
#include "com_gensym_util_Symbol.h"


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      DEFINES
 %
 % Description:  Module specific macros defined in this section. 
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#define MSVM 0
#undef MSVM

#ifdef MSVM
#include <windows.h>
#define GC_ACCESS(obj) gc.obj
#else
#include <StubPreamble.h>
#define GC_ACCESS(obj) obj
#endif


#define TCPIP_PORT_NUMBER  0

#define JAVA_ITEM_OK		0
#define JAVA_ITEM_BAD		1
#define JAVA_ITEM_VOID		2


#define JAVA_GSIITEM_NAME				"GsiItem"
#define JAVA_GSIOBJECT_NAME				"GsiObject"
#define JAVA_GSIINT_NAME				"GsiInt"
#define JAVA_GSIFLOAT_NAME				"GsiFLoat"
#define JAVA_GSISYMBOL_NAME				"GsiSymbol"
#define JAVA_GSISTRING_NAME				"GsiString"
#define JAVA_GSILOG_NAME				"GsiLog"
#define JAVA_GSIINTARRAY_NAME			"GsiIntArray"
#define JAVA_GSIFLOATARRAY_NAME			"GsiFloatArray"
#define JAVA_GSISYMBOLARRAY_NAME		"GsiSymbolArray"
#define JAVA_GSISTRINGARRAY_NAME		"GsiStringArray"
#define JAVA_GSIITEMARRAY_NAME			"GsiItemArray"
#define JAVA_GSIVALUEARRAY_NAME			"GsiValueArray"
#define JAVA_GSILOGARRAY_NAME			"GsiLogArray"
#define JAVA_GSIINTLIST_NAME			"GsiIntList"
#define JAVA_GSIFLOATLIST_NAME			"GsiFloatList"
#define JAVA_GSISYMBOLLIST_NAME			"GsiSymbolList"
#define JAVA_GSISTRINGLIST_NAME			"GsiStringList"
#define JAVA_GSIITEMLIST_NAME			"GsiItemList"
#define JAVA_GSIVALUELIST_NAME			"GsiValueList"
#define JAVA_GSILOGLIST_NAME			"GsiLogList"
		

#define JAVA_VOID_SIGNATURE	"V"
#define JAVA_GSIITEM_SIGNATURE			"LGsiItem;"
#define JAVA_GSIOBJECT_SIGNATURE		"LGsiObject;"
#define JAVA_GSIINT_SIGNATURE			"LGsiInt;"
#define JAVA_GSIFLOAT_SIGNATURE			"LGsiFLoat;"
#define JAVA_GSISYMBOL_SIGNATURE		"LGsiSymbol;"
#define JAVA_GSISTRING_SIGNATURE		"LGsiString;"
#define JAVA_GSILOG_SIGNATURE			"LGsiLog;"
#define JAVA_GSIINTARRAY_SIGNATURE		"LGsiIntArray;"
#define JAVA_GSIFLOATARRAY_SIGNATURE	"LGsiFloatArray;"
#define JAVA_GSISYMBOLARRAY_SIGNATURE	"LGsiSymbolArray;"
#define JAVA_GSISTRINGARRAY_SIGNATURE	"LGsiStringArray;"
#define JAVA_GSIITEMARRAY_SIGNATURE		"LGsiItemArray;"
#define JAVA_GSIVALUEARRAY_SIGNATURE	"LGsiValueArray;"
#define JAVA_GSILOGARRAY_SIGNATURE		"LGsiLogArray;"
#define JAVA_GSIINTLIST_SIGNATURE		"LGsiIntList;"
#define JAVA_GSIFLOATLIST_SIGNATURE		"LGsiFloatList;"
#define JAVA_GSISYMBOLLIST_SIGNATURE	"LGsiSymbolList;"
#define JAVA_GSISTRINGLIST_SIGNATURE	"LGsiStringList;"
#define JAVA_GSIITEMLIST_SIGNATURE		"LGsiItemList;"
#define JAVA_GSIVALUELIST_SIGNATURE		"LGsiValueList;"
#define JAVA_GSILOGLIST_SIGNATURE		"LGsiLogList;"


#define NOT_SIMPLE_ITEM 0
#define IS_SIMPLE_ITEM 1


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      GLOBALS
 %
 % Description:  Module specific typedefs, variables, & externs defined here
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


/* None as this file is included by multiple C file

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      DECLARATIONS
 %
 % Description:  Declarations of function prototypes and externs
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/* Forward reference */

/*
int convert_java_gsiitem_to_gsiitem(struct Hcom_gensym_jgsi_GsiObject *java_gsiitem, 
				    gsi_item *gsiitem, 
				    int is_simple_item );
				    */

/* externs */
extern int test;
extern int debug;
extern int fundebug;
extern int fulldebug;

extern char* get_method_signature_from_gsi_args();
extern int get_gsiitems_from_java_gsiitems();
extern HObject* create_java_sequence_from_gsiitems(gsi_item*, int);
extern HObject* create_java_gsiobject_from_gsiitem (gsi_item*, char**);
extern HObject *create_java_object_from_gsiitem(gsi_item, int);
extern HArrayOfObject* AllocClassArray (ClassClass*, int);
extern char* allocateCString (Hjava_lang_String*);

/* GsiInterfaces that have been registered, allow only one allowed for now !!!! */
#ifdef MSVM
	extern Hcom_gensym_jgsi_GsiInterface **registeredGsiInterface;
#define UNHAND_GLOBAL(ptr) (*ptr)
#else
	extern Hcom_gensym_jgsi_GsiInterface *registeredGsiInterface;
#define UNHAND_GLOBAL(ptr) ptr
#endif

#define java_intern_symbol(x) (HObject*) execute_java_static_method (ee, SymbolClass, "intern", interning_signature, makeJavaString (x, strlen(x)))
#define interning_signature "(Ljava/lang/String;)Lcom/gensym/util/Symbol;"
