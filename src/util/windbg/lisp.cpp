// lisp.cpp -- A windbg/cdb debugger extension for printing and describing
// Chestnut lisp objects.

// TODO:
// xx print symbols
// xx print wide strings
// xx describe structures
// xx describe double-float arrays (= managed-float)
// xx Use DML to mark substructures
// xx Create nmake file, check into cvs under utils/windbg
// xx Get Chestnut includes from %SRCBOX%/rtl/c
// xx Save copy of lisp.dll in /home/development/util
// xx Slot names for structures
// xx available-frame-vector-p
// xx print_class_description
// xx Slot names for frames (retrieve from class-description)
// xx print-logbook-messages
// xx princ-wide-string (without quotes)
// xx print-text (eg, strip lost-spaces crud)
// xx describe_symbol

// find_symbol (intern-soft)
// print-managed-array
// x print-schedule equivalent
// print_schedule_task
// print G2 backtrace for task (see write-stack-evaluator-backtrace)
// calling-procedure-invocation, clear-procedure-invocations
// top-level-procedure-invocations-array
//  WRITE-STACK-EVALUATOR-BACKTRACE
//  computation-frame #<PROCEDURE bar @2117>
//  computation-component-particulars NIL
//  computation-instance  #<PROCEDURE-INVOCATION BAR @2118>
//  stack #<Simple-Vector T 8192 @2119>
//  top-of-stack 3
//  stack-frame-base  0

// print-wide-string with escaped quotes
// print-symbol with escapes
// print user slots

// Decode UTF-G strings into Unicode. See map-gensym-character-code-to-unicode-1-1-character
// Heuristically prefix "poi " to expressions

// Command to print all lisp objects in address range
// Command check entire forest of G2 objects for consistency
// Command to print bunch of well-known roots ((gi 'item), ...)

// UTF-G
// ~\   ==  \
// ~~   ==  ~
// \ab  ==  packed 16bit char.  Eg, \6'  ==  0x30B9

#include <windows.h>
#include <stdio.h>
#include <math.h>

#define KDEXT_64BIT
#include <WdbgExts.h>
#include <dbgeng.h>

/*
 * Chestnut Interface
 */

#define HAVE_MEMCPY
#define HAVE_MEMMOVE

#include "config.h"
#define SI_RUNTIME_INTERNAL
#include "object.h"
#include "runint.h"
#include "inline.h"

// From packages.c
#define HASH_ALLOC_SMALL  1000
#define HASH_ALLOC_LARGE 40000
#define HASH_ALLOC(pkg) ((SI_Dimension)((pkg==GetExpr("g2_ab_package"))?HASH_ALLOC_LARGE:HASH_ALLOC_SMALL))

#undef SI_STORED_OBJECT_FIELD
#define SI_STORED_OBJECT_FIELD(o, t, f) ((t *)FetchObject((ULONG)o))->f

// C++ didn't like Chestnut's inline structure cast.
typedef struct {
  SI_Noninitial_symbol h;
  char name[1];
} NamedSymbol;

#undef MSYMBOL_NAME
#define MSYMBOL_NAME(o) SI_STORED_OBJECT_FIELD(o, NamedSymbol, name)



/*
 * Debug Engine Interface
 */

#define Export extern "C" __declspec(dllexport) HRESULT _cdecl

#define CACHE_SIZE 80		// For FetchObject, in longs.

static WINDBG_EXTENSION_APIS64 ExtensionApis;
static PDEBUG_CLIENT4 g_pClient;

static PDEBUG_CONTROL GetDebugControl(IUnknown *pClient)
{
  static PDEBUG_CONTROL g_ExtControl;
  pClient->QueryInterface(__uuidof(IDebugControl), (void **)&g_ExtControl);
  return g_ExtControl;
}

Export 
DebugExtensionInitialize(PULONG Version, PULONG Flags)
{
  IDebugClient *pClient;
  PDEBUG_CONTROL pControl;
  HRESULT hr;

  *Version = DEBUG_EXTENSION_VERSION(1, 0);
  *Flags = 0;

  hr = DebugCreate(__uuidof(IDebugClient), (void **)&pClient);
  if(hr != S_OK) return hr;

  pControl = GetDebugControl(pClient);
  ExtensionApis.nSize = sizeof(ExtensionApis);
  pControl->GetWindbgExtensionApis64(&ExtensionApis);

  pControl->Release();
  pClient->Release();
  return hr;
}

static void hprintf(PCSTR fmt, ...)
{
  PDEBUG_CONTROL pControl;
  va_list args;

  pControl = GetDebugControl(g_pClient);

  va_start(args, fmt);
  pControl->ControlledOutputVaList(DEBUG_OUTCTL_AMBIENT_DML, DEBUG_OUTPUT_NORMAL, fmt, args);
  va_end(args);
  pControl->Release();
}

// Retrieve bytes from target, and return pointer to local cache. We guess how
// many we need, and never bother to reclaim.
static ULONG *FetchObject(ULONG addr)
{
  static ULONG lastAddr = NULL;
  static ULONG *lastBuf = NULL;

  if(addr == lastAddr && lastBuf != NULL)
    return lastBuf;

  ULONG *buf = (ULONG *) calloc(CACHE_SIZE, sizeof(ULONG));
  ReadMemory(addr, buf, CACHE_SIZE*sizeof(ULONG), NULL);
  lastAddr = addr;
  lastBuf = buf;
  return buf;
}

static Object GetExpr(PCSTR expr)
{
  return (Object) GetExpression(expr);
}



/*
 * Selected Chestnut RTL routines
 */

static BOOL Print_array = FALSE;
static BOOL Print_escape = TRUE;
static int Max_length = 25;	// For printing lists
static int Max_slots = 75;	// For describe. Depends on cache size!

static char *downcase (char *str)
{
  int i;
  static char buf[256];
  for(i=0; *str && i<sizeof(buf)-1; i++)
    buf[i] = tolower(str[i]);
  buf[i++] = 0;
  return buf;
}

Object cdouble_to_double (double a)
{
  Object result = NIL;
//   result = SI_ALLOC(SI_Double_float, DOUBLE_TYPE, SI_NUMBER_TAG, SI_BORING);
//   SI_UNTAG_DOUBLE_FLOAT(result) = a;
  return result;
}

static char *array_element_type(Object arr)
{
  // See enum SI_gcls
  static char *types[] = {
    "NIL",
    "NIL",
    "NIL",
    "NIL",
    "NIL",
    "T",			// 5
    "STRING-CHAR",		// 6
    "SINGLE-FLOAT",		// 7
    "DOUBLE-FLOAT",		// 8
    "BIT",			// 9
    "(SIGNED-BYTE 8)",		// 10 A
    "(SIGNED-BYTE 16)",		// 11 B
    "(SIGNED-BYTE 32)",		// 12 C
    "(UNSIGNED-BYTE 8)",	// 13 D
    "(UNSIGNED-BYTE 16)",	// 14 E
    "(UNSIGNED-BYTE 32)"};	// 15 F
  // types[(int)((enum SI_gcls) (((SI_Header *)LispObject(arr, sizeof(SI_Header)))->stuff & 15))];
  return types[(int)SI_ARRAY_ETYPE(arr)];
}

static int array_dimensions(Object arr)
{
  SI_Dimension rank;

  if (SI_PRIMITIVE_VECTOR_P(arr))
    // Length field is an Object, by always a fixnum, hence right shift.
    // ((SI_Primitive_vector *)LispObject(arr, sizeof(SI_Primitive_vector)))->length) >> 2
    return SI_PRIMITIVE_VECTOR_LENGTH(arr);
  else {
    rank = SI_GENERAL_ARRAY_RANK(arr);
    if (rank == 1)
      return SI_GENERAL_VECTOR_TOTAL_SIZE(arr);
    else
      return -1;		// FIXME: was consing a list here.
  }
}

void *SI_array_contents (Object arr)
{
  Object pv = arr;
  void *result;
  enum SI_etype etype;

  while (!SI_VECTOR_PRIMITIVE_P(pv))
    pv = SI_GENERAL_ARRAY_DISPLACED_TO(pv);
  etype = SI_PRIMITIVE_VECTOR_ETYPE(pv);

  switch (etype) {
    case A_T:
      result = (void *)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Object);
      break;
    case A_STRING_CHAR:
      result = (void *)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Char);
      break;
    case A_SINGLE_FLOAT:
      result = (void *)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Float);
      break;
    case A_DOUBLE_FLOAT:
      result = (void *)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Double);
      break;
    case A_BIT:
      result = (void *)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Bits);
      break;
    case A_BYTE_8:
      result = (void *)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Char);
      break;
    case A_BYTE_16:
      result = (void *)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Short);
      break;
    case A_BYTE_32:
      result = (void *)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Long);
      break;
    case A_UNSIGNED_BYTE_8:
      result = (void *)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Uchar);
      break;
    case A_UNSIGNED_BYTE_16:
      result = (void *)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Ushort);
      break;
    case A_UNSIGNED_BYTE_32:
      result = (void *)SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Ulong);
      break;
    default:
      dprintf("<<aref: unknown element type>>");
      result = (void *)NULL;
      break;
  }

  return (result);
}

long ilength (Object sequence)
{
  long len = 0L;

  if (sequence == NIL)
    len = 0;
  else if (VECTORP(sequence))
    len = SI_VECTOR_LENGTH(sequence);
  else if (CONSP(sequence))
    do {
      len++;
      sequence = M_CDR(sequence);
    } while(CONSP(sequence));
  else
    dprintf("ilength: invalid argument");
  return len;
}

/* This is CLtL II's ROW-MAJOR-AREF */
Object aref (Object arr, long i)
{
  Object pv = arr;
  Object result = NIL;
  long iresult;
  unsigned long uresult;
  enum SI_etype etype;

  while (!SI_VECTOR_PRIMITIVE_P(pv))
    pv = SI_GENERAL_ARRAY_DISPLACED_TO(pv);
  etype = SI_PRIMITIVE_VECTOR_ETYPE(pv);

  switch (etype) {
    case A_T:
      result = SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Object)[i];
      break;
    case A_STRING_CHAR:
      result = MAKE_CHR(SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Char)[i], 0);
      break;
    case A_SINGLE_FLOAT:
      result = cdouble_to_double((double) SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Float)[i]);
      break;
    case A_DOUBLE_FLOAT:
      result = cdouble_to_double(SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Double)[i]);
      break;
    case A_BIT:
      result = (SI_SBIT_ACCESS(pv,i) & SI_SBIT_MASK(i)) ? FIX(1) : ZERO;
      break;
    case A_BYTE_8:
      iresult = SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Char)[i];
      result = FIX(iresult);
      break;
    case A_BYTE_16:
      iresult = SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Short)[i];
      result = FIX(iresult);
      break;
    case A_BYTE_32:
//       iresult = SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Long)[i];
//       result = MAKE_INTEGER(iresult);
      break;
    case A_UNSIGNED_BYTE_8:
      uresult = SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Uchar)[i];
      result = FIX(uresult);
      break;
    case A_UNSIGNED_BYTE_16:
      uresult = SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Ushort)[i];
      result = FIX((long)uresult);
      break;
    case A_UNSIGNED_BYTE_32:
//       uresult = SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Ulong)[i];
//       result = MAKE_INTEGER((long)uresult);
      break;
    default:
      dprintf("<<aref: unknown element type>>");
      result = NIL;
      break;
  }
  return result;
}

BOOL float_array_p(Object o)
{
  Object pv = o;
  enum SI_etype etype;

  if(!ARRAYP(o)) return FALSE;

  while (!SI_VECTOR_PRIMITIVE_P(pv))
    pv = SI_GENERAL_ARRAY_DISPLACED_TO(pv);
  etype = SI_PRIMITIVE_VECTOR_ETYPE(pv);

  return (etype == A_SINGLE_FLOAT) || (etype == A_DOUBLE_FLOAT);
}

double aref_d(Object arr, int i)
{
  Object pv = arr;
  enum SI_etype etype;

  while (!SI_VECTOR_PRIMITIVE_P(pv))
    pv = SI_GENERAL_ARRAY_DISPLACED_TO(pv);
  etype = SI_PRIMITIVE_VECTOR_ETYPE(pv);

  switch (etype) {
   case A_SINGLE_FLOAT:
     return SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Float)[i];
   case A_DOUBLE_FLOAT:
     return SI_PRIMITIVE_VECTOR_CONTENTS(pv, SI_PVT_Double)[i];
   default:
     return -666.0;
  }
}



/*
 * Symbols
 */

char *isymbol_name (Object sym);

char *SI_istring (Object o)
{
  SI_Dimension i = 0;
  Object arg = o;

  if (!SIMPLE_STRING_P(o)) {
    if (SYMBOLP(o))
      return isymbol_name(o);
    if (CHARACTERP(o))
      return "<<ch>>";		// o = make_string(FIX(1L), o);
    return (char *)SI_array_contents(o); // FIXME: bogus
  }
  return &SI_ISCHAR(o, i);
}

char *isymbol_name (Object sym)
{
  Object name;

  if (sym == NIL)
    return "NIL";
  switch (ISYMBOL_TYPE(sym)) {
    case USYMBOL_TYPE:
      name = USYMBOL_NAME(sym);
      return ISTRING(name);
    case MSYMBOL_TYPE:
    case EMSYMBOL_TYPE:
    case MKEYWORD_TYPE:
      return MSYMBOL_NAME(sym);
    case SYMBOL_TYPE:
    case ESYMBOL_TYPE:
    case KEYWORD_TYPE:
      return "ISYMBOL_NAME(sym)"; // ISYMBOL_NAME(sym);
    default:
      return "#<symbol_name: not a symbol>";
  }
}



static char *lisp_typeof(Object a)
{
  int simplep;

  if (SI_IMMEDIATEP(a)) {
    if (a == NIL)
      return "NULL";
    else if (FIXNUMP(a))
      return "FIXNUM";
    else if (CHARACTERP(a))
      return "CHARACTER";
    else
      return "T";

  } else if (ARRAYP(a)) {
    simplep = SIMPLE_ARRAY_P(a);
    if (!VECTORP(a))
      return "ARRAY";
    else switch (SI_ARRAY_ETYPE(a)) {
      case A_STRING_CHAR:
	if (simplep)
	  return "SIMPLE-STRING";
	else
	  return "STRING";

      case A_BIT:
	if (simplep)
	  return "SIMPLE-BIT-VECTOR";
	else
	  return "BIT-VECTOR";

      case A_T:
	if (simplep)
	  return "SIMPLE-VECTOR";
	else
	  return "VECTOR";

      default:
	return "VECTOR";
      }

  } else
    switch (SI_STORED_OBJECT_TYPE(a))
      {
      case SYMBOL_TYPE:
      case USYMBOL_TYPE:
      case MSYMBOL_TYPE:
      case ESYMBOL_TYPE:
      case EMSYMBOL_TYPE:
      case KEYWORD_TYPE:
      case MKEYWORD_TYPE:
	return "SYMBOL";

      case INDIRECT_TYPE:
      case EINDIRECT_TYPE:
	return "Indirect?";

      case OBIGNUM_TYPE:
	return "BIGNUM";

      case DOUBLE_TYPE:
	return "DOUBLE-FLOAT";

      case CONS_TYPE:
	return "CONS";

      case RATIO_TYPE:
	return "RATIO";

      case COMPLEX_TYPE:
	return "COMPLEX";

      case SI_FUNCTION_TYPE:
	return "FUNCTION";

      case COBJECT_TYPE:
	return ARRAYP(a) ? "COBJECT" : "FOREIGN-POINTER";

      case SI_STRUCTURE_TYPE:
	return "STRUCTURE"; /* FIXME: SI_STRUCTURE_NAME(a); */

      case PACKAGE_TYPE:
	return "PACKAGE";

      case HASH_TABLE_TYPE:
	return "HASH-TABLE";

      case STREAM_TYPE:
	return "STREAM";

      case RANDOM_STATE_TYPE:
	return "RANDOM-STATE";

      case READTABLE_TYPE:
	return "READTABLE";

      case PATHNAME_TYPE:
	return "PATHNAME";

      default:
	return "UnknownType";
      }
  return "???";
}



/*
 * Printing
 */

void prints(Object arg);

static void terpri()
{
  dprintf("\n");
}

static void prints_name(char *str, int n)
{
  dprintf("%s", str);
}

static void prints_str(char *str, int n)
{
  dprintf("%s", str);
}

static void prints_string(char *str)
{
  dprintf("%s", str);
}

static void prints_number(Object arg)
{
  if(FIXNUMP(arg))
    dprintf("%d", IFIX(arg));
  else {
    switch(SI_STORED_OBJECT_TYPE(arg)) {
//       case XBIGNUM_TYPE:
// 	prints_bignum(arg, base);
// 	return;
      case DOUBLE_TYPE:
	dprintf("%f", IDOUBLE(arg));
	break;
      default:
	dprintf("#<Non-number %lx>", (long) arg);
	break;
    }
  }
}

static void print_addr(Object arg)
{
  hprintf("<link cmd=\"!lisp.describe %x\">%08x</link>", (long)arg, (long)arg);
}

static void prints_ch(int ch)
{
  dprintf("%c", ch);
}

static void prints_character(Object c)
{
  int bits = ICHAR_BITS(c);
  int code = ICHAR_CODE(c);
  char buffer[256];
  char *p = buffer;

  p[0] = '\0';

  if (bits & ICHAR_CONTROL_BIT)
    strcat(p, "Control-");
  if (bits & ICHAR_META_BIT)
    strcat(p, "Meta-");
  if (bits & ICHAR_SUPER_BIT)
    strcat(p, "Super-");
  if (bits & ICHAR_HYPER_BIT)
    strcat(p, "Hyper-");

  p = &buffer[strlen(buffer)];
  // FIXME!
  // if (ichar_name(CHR(code), p) < 0)
  if(isprint(code)) {
     p[0] = code;
     p[1] = '\0';
  } else {
    sprintf(p, "c%2X", code);
  }
  prints_str(buffer, strlen(buffer));
}

static void prints_double(double darg)
{
  dprintf("%lf", darg);
}

static void prints_structure(Object arg)
{
  //  Object temp = SI_STRUCTURE_NAME(str);
  dprintf("#<Structure %x>", (long)arg);
}

static void prints_cons(Object arg)
{
  int i=0;
  prints_ch('(');
  while(CONSP(arg)) {
    if(CheckControlC()) break;
    prints(M_CAR(arg));
    if (M_CDR(arg) != NIL)
      prints_ch(' ');
    arg = M_CDR(arg);
    i++;
    if(i >= Max_length) break;
  }

  if(i >= Max_length)
    prints_string(" ... ");
  else if (arg != NIL) {
    prints_str(". ", 2);
    prints(arg);
  }
  prints_ch(')');
}

// FIXME: Use symbol's wide string if present. Or, how to decode
// unicode escapes in symbol name (See twrite-unicode-from-utf-G-encoded-string)
static void prints_symbol(Object arg)
{
  Object temp;

  switch (ISYMBOL_TYPE(arg)) {
   case USYMBOL_TYPE:
     temp = USYMBOL_NAME(arg);
     if (Print_escape)
       prints_str("#:", 2);
     prints_string(ISTRING(temp));
     break;
   case KEYWORD_TYPE:
   case MKEYWORD_TYPE:
     if (Print_escape)
       prints_ch(':');
     prints_string(isymbol_name(arg));
     break;
   default:
     prints_string(isymbol_name(arg));
     break;
  }
}



/*
 * G2-specific
 */

static BOOL wide_string_p(Object o)
{
  return ARRAYP(o) && SI_ARRAY_ETYPE(o) == 14;
}

static void print_wide_string(Object arg)
{
  // FIXME: Escape inner quotes. Convert Unicode newlines.
  dprintf("#w\"%mu\"", (ULONG)arg +  sizeof(SI_Primitive_vector));
}

static void princ_wide_string(Object arg)
{
  dprintf("%mu", (ULONG)arg +  sizeof(SI_Primitive_vector));
}

static void princ_text(Object arg)
{
  Object elt;
  for(; CONSP(arg); arg = M_CDR(arg)) {
    if(CheckControlC()) break;
    elt = M_CAR(arg);
    if(wide_string_p(elt)) {
      princ_wide_string(elt);
      dprintf(" ");
    }
  }
}

static BOOL available_frame_vector_p(Object arg)
{
  if(!VECTORP(arg)) return FALSE;

  if(ilength(arg) < 2) return FALSE;

  if(SI_ARRAY_ETYPE(arg) != A_T) return FALSE;

  Object o = aref(arg,1);
  if(!SYMBOLP(o)) return FALSE;

  return strcmp(isymbol_name(o), "AVAILABLE-FRAME-VECTOR") == 0;
}

static BOOL g2_structure_symbol_p(Object arg)
{
  if(!arg || !SYMBOLP(arg)) return FALSE;

  char *name = isymbol_name(arg);
  int n = strlen(name);
  char *tag = "-G2-STRUCT";
  int k = strlen(tag);

  return n>k && strcmp(name+n-k,tag)==0;
}

static char *g2_structure_name(Object arg)
{
  if(!SIMPLE_ARRAY_P(arg)) return NULL;
  if(SI_ARRAY_ETYPE(arg) != A_T) return NULL;

  Object elt = aref(arg,0);

  if(g2_structure_symbol_p(elt))
    return isymbol_name(elt);
  else
    return NULL;
}


static BOOL class_description_p(Object o)
{
  char *name = g2_structure_name(o);
  return name && !strcmp(name,"CLASS-DESCRIPTION-G2-STRUCT");
}

// slot-descriptions-internal
static void print_class_description(Object o)
{
  dprintf("#<Class-Description %s ", isymbol_name(aref(o,1)));
  print_addr(o);
  dprintf(">");
}


static BOOL slot_description_p(Object o)
{
  char *name = g2_structure_name(o);
  return name && !strcmp(name,"SLOT-DESCRIPTION-G2-STRUCT");
}

// slot-descriptions-internal
static void print_slot_description(Object o)
{
  dprintf("#<Slot-Description %s ", isymbol_name(aref(o,1)));
  print_addr(o);
  dprintf(">");
}


static BOOL frame_p(Object o)
{
  return VECTORP(o) &&
    ilength(o) > 2 &&
    SI_ARRAY_ETYPE(o) == A_T &&
    class_description_p(aref(o,1));
}

static char *frame_class_name(Object o)
{
  if(frame_p(o))
    return isymbol_name(aref(aref(o,1),1));
  else
    return "?";
}

static BOOL message_p(Object o)
{
  return !strcmp(frame_class_name(o),"MESSAGE");
}

static BOOL managed_float_p(Object o)
{
  return SIMPLE_ARRAY_P(o) && ilength(o) == 1 && SI_ARRAY_ETYPE(o) == A_DOUBLE_FLOAT;
}

static void print_managed_float(Object mf)
{
  dprintf("#<Managed-Float %lf ", aref_d(mf,0));
  print_addr(mf);
  dprintf(">");
}

static double managed_float_value(Object o)
{
  if(ARRAYP(o))
    return aref_d(o,0);
  else
    return -666.0;
}


static BOOL constant_queue_p(Object o)
{
  return (SIMPLE_ARRAY_P(o) && ilength(o) == 3) &&
    (SIMPLE_ARRAY_P(aref(o,0)) && ilength(aref(o,0)) == 3) &&
    (SIMPLE_ARRAY_P(aref(o,1)) && ilength(aref(o,1)) == 3);
}

static int constant_queue_length(Object q)
{
  Object e;
  int n=0;
  for(e=aref(q,0); e && e!=q; e=aref(e,0))
    n++;
  return n;
}

static void print_constant_queue(Object q)
{
  dprintf("#<Constant-Queue (%d) ", constant_queue_length(q));
  print_addr(q);
  dprintf(">");
}


// Try to recognize G2 structures and frames
static void prints_simple_vector(Object arg)
{
  Object elt = aref(arg, 0);
  char *type = "Simple-Vector";

  if(available_frame_vector_p(arg)) {
    type = "Available-Frame-Vector";

  } else if(constant_queue_p(arg)) {
    print_constant_queue(arg);
    return;

  } else if(class_description_p(arg)) {
    print_class_description(arg);
    return;

  } else if(slot_description_p(arg)) {
    print_slot_description(arg);
    return;

  } else if(managed_float_p(arg)) {
    print_managed_float(arg);
    return;

  } else if(g2_structure_symbol_p(elt)) { // Looks like a G2 structure
    type = strdup(isymbol_name(elt));
    char *p = strstr(type, "-G2-STRUCT");
    if(p) *p = 0;
    
  } else {
    Object cls = aref(arg, 1);	                 // Else element 1 is class-description
    if(ARRAYP(cls) && SYMBOLP(aref(cls,0)) && SYMBOLP(aref(cls,1)))
      type = isymbol_name(aref(cls,1));
  }

  dprintf("#<%s ", type);
  prints_string(array_element_type(arg));
  dprintf(" (%d) ", array_dimensions(arg));
  print_addr(arg);
  prints_string(">");
}

static void print_compiled_function(Object arg)
{
  ULONG funcPtr;
  CHAR sym[256];
  ULONG64 offset;

  // funcPtr = SI_FUNCTION_ENTRY(arg);
  ReadMemory((ULONG)arg + 4, &funcPtr, 4, NULL);// FIXME: hack

  sym[0] = 0;
  GetSymbol(funcPtr, sym, &offset);
  dprintf("#<Function %s", sym);
  if(offset != 0)
    dprintf("+%x", (long)offset);
  dprintf(" ");
  print_addr(arg);
  dprintf(">");
}

static void print_random_object(char *type, Object arg)
{
  dprintf("#<%s ", type);
  print_addr(arg);
  prints_ch('>');
}

static void prints(Object arg)
{
  long i, bitlen, arrlen;

  if (SI_IMMEDIATEP(arg)) {
    if (arg == NIL)
      prints_name("NIL", 3);
    else if (FIXNUMP(arg))
      prints_number(arg);
    else if (CHARACTERP(arg)) {
      if (Print_escape) {
	prints_str("#\\", 2);
	prints_character(arg);
      }
      else
	prints_ch(ICHAR_CODE(arg));
    } else if (arg == UNBOUND)
      prints_str("#<Unbound>", 10);
    else {
      dprintf("#<Immediate 0x%lx>", (long) arg);
    }
  }

  else if (ARRAYP(arg)) {
    if(wide_string_p(arg))
      print_wide_string(arg);

    else if (!VECTORP(arg)) {
      if (SIMPLE_ARRAY_P(arg))
	prints_str("#<Simple-Array ", 15);
      else
	prints_str("#<Array ", 8);
      prints_string(array_element_type(arg));
      dprintf(" (%d) ", array_dimensions(arg));
      print_addr(arg);
      prints_ch('>');

    } else if (STRINGP(arg)) {
      prints_ch('"');
      prints_string(ISTRING(arg));
      prints_ch('"');

    } else if (BIT_VECTOR_P(arg)) {
      prints_str("#*", 2);
      bitlen = ilength(arg);
      for (i = 0; i < bitlen; i++)
	prints(aref(arg, (i)));

    } else if (Print_array) {
      prints_str("#(", 2);
      arrlen = ilength(arg);
      for (i = 0; i < arrlen; i++) {
	if(CheckControlC()) break;
	prints(aref(arg, i));
	if (i < (arrlen-1))
	  prints_ch(' ');
      }
      prints_ch(')');

    } else {
      /* Simple-vector would be misleading, since that implies
	 element type T *** that's not correct (ex: fixnum) */
      if (SIMPLE_ARRAY_P(arg))
	prints_simple_vector(arg);
      else {
	prints_str("#<Vector ", 9);
	prints_string(array_element_type(arg));
	dprintf(" (%d) ", array_dimensions(arg));
	print_addr(arg);
	prints_string(">");
      }
    }

  } else if (SYMBOLP(arg)) {
    prints_symbol(arg);

  } else {
    switch(SI_STORED_OBJECT_TYPE(arg)) {
     case CONS_TYPE:
       prints_cons(arg);
       break;
     case OBIGNUM_TYPE:
       prints_number(arg);
       break;
     case DOUBLE_TYPE:
       prints_double(IDOUBLE(arg));
       break;
     case RATIO_TYPE:
       prints_number(RATIO_NUMERATOR(arg));
       prints_ch('/');
       prints_number(RATIO_DENOMINATOR(arg));
       break;
     case COMPLEX_TYPE:
       prints_str("#C(", 3);
       prints_number(COMPLEX_REAL(arg));
       prints_ch(' ');
       prints_number(COMPLEX_IMAG(arg));
       prints_ch(')');
       break;

     case SI_FUNCTION_TYPE:
       print_compiled_function(arg);
       break;

     case SI_STRUCTURE_TYPE:
       if(FALSE) {		// FOREIGN_TYPE_P(arg)) {
	 prints_str("#<Foreign-Type ", 15);
	 // prints(FOREIGN_TYPE_NAME(arg));
	 print_addr(arg);
	 prints_ch('>');
       }
       else
	 prints_structure(arg);
       break;
     case PACKAGE_TYPE:
       print_random_object("Package", arg);
       // prints_str(PACKAGE_NAME(arg), strlen(PACKAGE_NAME(arg)));
       break;
     case HASH_TABLE_TYPE:
       print_random_object("Hash-Table", arg);
       break;
     case RANDOM_STATE_TYPE:
       print_random_object("Random-State", arg);
       break;
     case READTABLE_TYPE:
       print_random_object("Readtable", arg);
       break;
     case PATHNAME_TYPE:
       print_random_object("Pathname", arg);
       break;
     case STREAM_TYPE:
       print_random_object("Stream", arg);
       break;
     case COBJECT_TYPE:
       print_random_object("Foreign-Pointer", arg);
       break;
     default:
       dprintf("#<Unknown-Object type=%d ", SI_STORED_OBJECT_TYPE(arg));
       print_addr(arg);
       prints_ch('>');
       break;
    }
  }
}



/*
 * Symbols
 */

static unsigned hash_string (char *name, Object pkg)
{
  /* compute hash value of a symbol */
  unsigned long hashval = 0;
  char *p = name;
  char current_char;

  while(current_char = *p) {
    hashval = ((hashval << 1) & 0xFFFF) + (hashval >> 15)
      + (unsigned long)current_char;
    p++;
  }
  hashval &= 0xFFFF;
  return ((HASH_ALLOC(pkg)==HASH_ALLOC_SMALL)?
	  (hashval % HASH_ALLOC_SMALL) :
	  (hashval % HASH_ALLOC_LARGE));
}

#define VALUE_INDICATOR	     	SI_MAKE_TOKEN(SI_TOKEN_ID_VALUE)
#define FUNCTION_INDICATOR     	SI_MAKE_TOKEN(SI_TOKEN_ID_FUNCTION)
#define SETF_FUNCTION_INDICATOR SI_MAKE_TOKEN(SI_TOKEN_ID_SETF_FUNCTION)
#define NAME_INDICATOR		SI_MAKE_TOKEN(SI_TOKEN_ID_NAME)

#define SEARCH_PLIST() \
      res = UNBOUND; \
      for (tail = SI_SYMBOL_PLIST(sym); CONSP(tail); tail = M_CDDR(tail)) \
        if (EQ(M_CAR(tail), key)) { res = M_CADR(tail); break; }

SI_Static_T  SI_T_untagged;

Object SI_symbol_field(Object sym, enum SI_Symbol_field field)
{
  Object res=UNBOUND, key, tail;

  if (sym == NIL)
    switch (field) {
     case SI_SymFn:		return UNBOUND;
     case SI_SymFbnd:		return NIL;
     case SI_SymSetfFn:	        return UNBOUND;
     case SI_SymSetfFbnd:	return NIL;
     case SI_SymVal:		return NIL;
     case SI_SymBnd:		return T;
     case SI_SymPlist: 	        return GetExpr("poi g2rtl_SI_Plist_of_nil");
    } else {

      if (field == SI_SymPlist) {
	for (tail = SI_SYMBOL_PLIST(sym); CONSP(tail); tail = M_CDDR(tail)) {
	  key = M_CAR(tail);
	  if (key != FUNCTION_INDICATOR &&
	      key != VALUE_INDICATOR &&
	      key != SETF_FUNCTION_INDICATOR &&	
	      key != NAME_INDICATOR)
	    break;
	}
	return tail;
      }

      switch (field) {
       case SI_SymFn:
       case SI_SymFbnd:
	 /* Currently, the function is always stored as a property. */
	 key = FUNCTION_INDICATOR;
	 break;
       case SI_SymVal:
       case SI_SymBnd:
	 /* Currently, the value is always stored as a property. */
	 key = VALUE_INDICATOR;
	 break;
       case SI_SymSetfFn:
       case SI_SymSetfFbnd:
	 key = SETF_FUNCTION_INDICATOR;
	 break;
       case SI_SymValLoc:
	 key = VALUE_INDICATOR;
	 SEARCH_PLIST();
	 if (res == UNBOUND) return NIL;
	 else if (VALUE_CELL_P(res)) return res;
	 else return M_CDR(tail);
       case SI_SymName:
	 if (USYMBOLP(sym)) return USYMBOL_NAME(sym);
	 else {
	   key = NAME_INDICATOR;
	   SEARCH_PLIST();
	   return res;
	 }
      }
      SEARCH_PLIST();
      if (VALUE_CELL_P(res)) res = *VALUE_CELL_LOCATION(res);
      return res;
    }
  return res;
}

static Object symbol_value(Object symbol)
{
  if (SELF_EVALUATING_SYMBOL_P(symbol))
    return symbol;
  return SI_symbol_field(symbol, SI_SymVal);
}



/*
 * Slot names for G2 structures
 */

#define SLOTNAMES_FILENAME "slotnames.txt"

typedef struct _SlotName {
  struct _SlotName *next;
  char *str;
} SlotName;

static SlotName *g_SlotNames[1000];

// The symbol path may include SRV*. We will simply not find a file there.
// eg: SRV*C:\Windows\symbols*http://msdl.microsoft.com/download/symbols;D:\Temp\screenshots
static char *find_slotnames_file()
{
  char path[1024];
  char *p, *part;
  static char pathname[256];

  ZeroMemory(path, sizeof(path));
  GetSetSympath(NULL, path, sizeof(path));

  for(p=path; *p; p++)		// Hack for SRV entries
    if(*p == '*') *p = ';';

  ZeroMemory(pathname, sizeof(pathname));
  if(SearchPath(path, SLOTNAMES_FILENAME, NULL, sizeof(pathname), pathname, &part))
    return pathname;

  MessageBeep(MB_ICONASTERISK);
  hprintf("<b>[Unable to find file \"%s\" on symbol path]\n\
You can load it explictly with the load_slotnames command.</b>\n",
	     SLOTNAMES_FILENAME);
  return NULL;
}

static void read_slotnames(const char *pathname)
{
  FILE *fd;
  char buf[256];
  int n = 0;
  SlotName *s, *t, *p;

  if(!pathname) return;

  ZeroMemory(g_SlotNames, sizeof(g_SlotNames));

  hprintf("<b>[Reading slotnames from \"%s\"]</b>\n", pathname);
  fd = fopen(pathname, "r");
  if(!fd) {
    hprintf("<b>[Failed. File not found]</b>\n");
    return;
  }
  while(fgets(buf, sizeof(buf), fd)) {
    if(buf[0] == '#') continue;
    buf[strlen(buf)-1] = 0;
    s = new SlotName;
    s->str = strdup(buf);
    s->next = NULL;
    g_SlotNames[n] = s;
    p = s;
    while(fgets(buf, sizeof(buf), fd)) {    
      if(buf[0] == '\n')
	break;
      buf[strlen(buf)-1] = 0;
      t = new SlotName;
      t->str = strdup(buf);
      t->next = NULL;
      p->next = t;
      p=t;
    }
    n++;
    if(n>=1000) break;
  }
  fclose(fd);
  hprintf("<b>[Done. Found %d structure types.]</b>\n", n);
}

static void ensure_slotnames(BOOL force_p)
{
  static int once = 0;

  if(once && !force_p) return;
  once = 1;
  read_slotnames(find_slotnames_file());
}

static SlotName *find_slotnames(Object o)
{
  char *type = g2_structure_name(o);
  SlotName *s;
  int i;

  if(!type) return NULL;

  ensure_slotnames(FALSE);

  for(i=0; g_SlotNames[i]; i++) {
    if(!strcmp(g_SlotNames[i]->str, type))
      return g_SlotNames[i]->next;
  }
  return NULL;
}



/*
 * Describe
 */

static const char *dots = "...........................................";

static void describe_float_array(Object arg)
{
  int i;
  int n = array_dimensions(arg);

  for(i=0; i<n; i++) {
    if(CheckControlC()) break;
    dprintf("[%2d] ", i);
    prints_double(aref_d(arg,i));
    terpri();
  }
}

static void print_value(Object val)
{
  print_addr(val);
  dprintf(" ");
  prints(val);
}

static void print_slot(char *name, Object val)
{
  int width = strlen(dots);

  if(!name)
    dprintf("%s ", dots);
  else if(strlen(name) >= width)
    dprintf("%s ", name);
  else
    dprintf("%s %s ", name, dots + strlen(name));

  print_value(val);
  terpri();
}

static void describe_anonymous_vector(Object arg)
{
  int i;
  Object elt;
  int n = array_dimensions(arg);

  for(i=0; i<n && i<Max_slots; i++) {
    if(CheckControlC()) break;
    dprintf("[%2d] ", i);
    elt = aref(arg, i);
    print_value(elt);
    terpri();
  }
}

static void describe_structure(SlotName *pSlots, Object arg)
{
  int i;
  Object elt;

  int n = array_dimensions(arg);

  for(i=0; i<n && i<Max_slots; i++) {
    if(CheckControlC()) break;

    elt = aref(arg, i);
    dprintf("[%2d] ", i);
    print_slot(pSlots->str,elt);
    pSlots = pSlots->next;
  }
}

// !lisp.describe d32cf50
// !lisp.describe 5b8670c -- prints as plain simple-vector. Should be LOGBOOK
static void describe_frame(Object arg)
{
  int i;
  Object elt;
  Object clas = aref(arg,1);
  Object slots = aref(clas,6);	// slot-descriptions-internal
  Object slot, index;
  char *str;

  int n = array_dimensions(arg);

  for(i=0; i<n && i<Max_slots; i++) {
    if(CheckControlC()) break;

    str = NULL;
    for(; slots; slots = M_CDR(slots)) {
      if(CheckControlC()) break;
      slot = M_CAR(slots);
      index = aref(slot,7);	            // vector-slot-index
      if(index && IFIX(index) == i) {
	str = downcase(isymbol_name(aref(slot,2))); // pretty-slot-name
	break;
      }
    }

    dprintf("[%2d] ", i);
    elt = aref(arg, i);
    print_slot(str, elt);
  }
}

static void describe_plist(Object plist)
{
  Object p,v;
  char *str;

  for(; plist; plist=M_CDDR(plist)) {
    if(CheckControlC()) break;
    p = M_CAR(plist);
    v = M_CADR(plist);

    str = isymbol_name(p);
    print_slot(str,v);
  }
}

static void describe_symbol(Object arg)
{
  print_slot("symbol-value", SYMBOL_VALUE(arg));
  print_slot("symbol-function", SYMBOL_FUNCTION(arg));
  print_slot("symbol-plist", SYMBOL_PLIST(arg));
}

static void describe_vector(Object arg)
{
  SlotName *pSlots = NULL;

  if(float_array_p(arg))
    describe_float_array(arg);

  else if (frame_p(arg))
    describe_frame(arg);

  else if((pSlots = find_slotnames(arg)))
    describe_structure(pSlots, arg);

  else
    describe_anonymous_vector(arg);
}

static void describe_cons(Object arg)
{
  int i=0;
  Object elt;

  while(CONSP(arg)) {
    if(CheckControlC()) break;

    elt = M_CAR(arg);
    dprintf("[%2d] ", i);
    print_addr(elt);
    dprintf(" ");
    prints(elt);
    arg = M_CDR(arg);
    terpri();
    i++;
  }

  if (arg != NIL) {
    dprintf("[%2d] ", i);
    print_addr(arg);
    dprintf(" . ");
    prints(arg);
  }
}

static void lisp_describe(Object arg)
{
  dprintf("%08x: ", (long)arg);
  prints(arg);
  dprintf(" is a %s\n",lisp_typeof(arg));

  if(wide_string_p(arg))
    print_wide_string(arg);

  else if (SYMBOLP(arg))
    describe_symbol(arg);

  else if (VECTORP(arg))
    describe_vector(arg);

  else if (CONSP(arg))
    describe_cons(arg);
}



/*
 * G2-specific routines
 */

static void print_task_queue(Object cq)
{
  Object elt, task;

  if(!ARRAYP(cq)) return;

  for(elt=aref(cq,0); elt && elt!=cq; elt=aref(elt,0)) {
    if(CheckControlC()) break;

    task = aref(elt,2);
    dprintf(" ");
    if(ARRAYP(task))
      prints(aref(task,8));	// schedule-task-function-name
    else
      prints(task);
    terpri();
  }
}

// cf: task-queue-descriptions
static void print_schedule(Object s)
{
  Object next, cq;
  double time;
  int n=0;

  if(!ARRAYP(s)) return;

  // Assuming s is a future-task-queue-holder structure
  for(; s; s=next) {
    if(CheckControlC()) break;

    next = aref(s,1);		// Next queue holder
    time = managed_float_value(aref(s,2)); // Managed-float time
    cq = aref(s,4);		// see twrite-schedule-task
    dprintf("[%2d] %12.3lf ", n, time);
    print_task_queue(cq);
    n++;
  }
}

static void print_messages(Object ws, int &n)
{
  Object sg, subblocks, msg;
  sg = aref(ws,9);		// Slot group is slot 9 in page
  subblocks = aref(sg,4);	// subblocks (messages, arrows, etc) in 4 of that.
  for(; subblocks && n>0; subblocks = M_CDR(subblocks)) {
    msg = M_CAR(subblocks);
    if(message_p(msg)) {
      prints(msg);
      dprintf(" ");
      princ_text(aref(msg,10));	// box-translation-and-text
      terpri();
      n--;
    }
  }
}



/*
 * Command Definer
 */

#define CMD(name) \
void Cmd_##name(PCSTR args); \
Export name(PDEBUG_CLIENT4 pClient, PCSTR args) \
{ \
  g_pClient = pClient; \
  Cmd_##name(args); \
  return S_OK; \
} \
void Cmd_##name(PCSTR args)



/*
 * Commands
 */

CMD(help)
{
  hprintf("<b>Chestnut RTL lisp object decoding $Revision: 1.13 $</b>\n");
  dprintf("\n");
  dprintf("To see structure slot names, the file \"slotnames.txt\" must be on your\n");
  hprintf("symbol path. Use the development lisp function <b>write-structure-slotnames</b>\n");
  dprintf("to create one for your G2 version.\n");
  dprintf("\n");
  hprintf("Note: you may need to dereference global object addresses with <b>poi</b>.\n");
  dprintf("If an object prints unexpectedly as a CONS whose is CDR is what you did expect,\n");
  dprintf("then that's probably the case. E.g., !print poi Current_logbook_qm .\n");
  dprintf("\n");
  dprintf("  sys                       -- print G2/TW/GSI system information\n");
  dprintf("  typeof   <address>        -- print the type of a lisp object\n");
  dprintf("  print    <address>        -- print a lisp object\n");
  dprintf("  describe <address>        -- describe a lisp object\n");
  dprintf("  sked                      -- print the G2 task schedule\n");
  dprintf("  queues                    -- print the G2 task queues\n");
  dprintf("  fsn                       -- print current FSN\n");
  dprintf("  wins                      -- print gensym-windows and workstations\n");
  dprintf("  logbook [n]               -- print N messages from logbook, default is all\n");
  dprintf("  msgboard [n]              -- print N messages from message board, default is all\n");
  dprintf("  print_text <address>      -- print a G2 text\n");
  dprintf("  load_slotnames <filename> -- load structure slotnames explicitly\n");
}

CMD(typeof)
{
  Object o = GetExpr(args);
  dprintf("TypeOf %08x = %s\n", (long)o, lisp_typeof(o));
}

CMD(sys)
{
  describe_plist(SYMBOL_PLIST(GetExpr("poi Current_system_name")));
}

CMD(print)
{
  Object o = GetExpr(args);
  dprintf("%08x (a %s): ", (long)o, lisp_typeof(o));
  prints(o);
  terpri();
}

CMD(describe)
{
  Object o = GetExpr(args);
  lisp_describe(o);
  terpri();
}

CMD(sked)
{
  Object o;

  o = GetExpr("poi immediate_task_queue");
  dprintf("Immediate tasks: ");
  prints(o); terpri();
  print_task_queue(o);

  o = GetExpr("poi future_real_time_tasks");
  dprintf("Real-time tasks: ");
  prints(o); terpri();
  print_schedule(o);

  o = GetExpr("poi future_g2_time_tasks");
  dprintf("G2-time tasks: ");
  prints(o); terpri();
  print_schedule(o);
}

CMD(queues)
{
  dprintf("Current_computation_frame  ");
  prints(GetExpr("poi g2!Current_computation_frame"));
  terpri();

  dprintf("Current_schedule_task      ");
  prints(GetExpr("poi g2!Current_schedule_task"));
  terpri();

  dprintf("Immediate_task_queue       ");
  prints(GetExpr("poi g2!Immediate_task_queue"));
  terpri();

  dprintf("Current_task_queue_vector  ");
  prints(GetExpr("poi g2!Current_task_queue_vector"));
  terpri();

  dprintf("Deferred_task_queue_vector ");
  prints(GetExpr("poi g2!Deferred_task_queue_vector"));
  terpri();

  dprintf("Future_real_time_tasks     ");
  prints(GetExpr("poi g2!Future_real_time_tasks"));
  terpri();

  dprintf("Future_g2_time_tasks       ");
  prints(GetExpr("poi g2!Future_g2_time_tasks"));
  terpri();
}

CMD(fsn)
{
  dprintf("*current-frame-serial-number* = ");
  prints(GetExpr("poi F000starcurrent_frame_serial_nu"));
  terpri();
}

CMD(wins)
{
  dprintf("workstations-in-service = ");
  prints(GetExpr("poi Workstations_in_service"));
  terpri();

  dprintf("system-window = ");
  prints(GetExpr("poi System_window"));
  terpri();
}

CMD(logbook)
{
  Object o = GetExpr("poi Current_logbook_qm");
  Object pages;
  int n = args ? atoi(args) : 0;

  dprintf("current-logbook? = ");
  prints(o);
  terpri();

  if(n<=0) n = 300;

  for(pages=aref(o,12); pages && n>0; pages=M_CDR(pages))
    print_messages(M_CAR(pages), n);
}

CMD(msgboard)
{
  Object o = GetExpr("poi Current_message_board_qm");
  int n = args ? atoi(args) : 0;

  dprintf("current-message-board? = ");
  prints(o);
  terpri();

  if(n<=0) n = 300;
  print_messages(o, n);
}

CMD(print_text)
{
  princ_text(GetExpr(args));
}

CMD(load_slotnames)
{
  read_slotnames(args);
}
