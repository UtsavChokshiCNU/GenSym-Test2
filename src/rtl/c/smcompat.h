/* smcompat.h
 *
 * compatibility file for stonefly-specific runtime.
 */

/* Declarations for these constants in initvars.h is inhibited by
   the presence of :simple-p t in the database. */
#undef Array_dimension_limit
#undef Array_rank_limit
#undef Array_total_size_limit
#undef Boole_1
#undef Boole_2
#undef Boole_and
#undef Boole_andc1
#undef Boole_andc2
#undef Boole_c1
#undef Boole_c2
#undef Boole_clr
#undef Boole_eqv
#undef Boole_ior
#undef Boole_nand
#undef Boole_nor
#undef Boole_orc1
#undef Boole_orc2
#undef Boole_set
#undef Boole_xor
#undef ADD_PACKAGE_NICKNAME
#undef NEW_SYMBOL
#undef ADD_SHADOW
#undef ADD_PACKAGE_USE
#undef ADD_IMPORT

#define Array_dimension_limit   ARRAY_DIMENSION_LIMIT
#define Array_rank_limit        ARRAY_RANK_LIMIT
#define Array_total_size_limit  ARRAY_TOTAL_SIZE_LIMIT
#define Boole_1		        BOOLE_1
#define Boole_2		        BOOLE_2
#define Boole_and	        BOOLE_AND
#define Boole_andc1	        BOOLE_ANDC1
#define Boole_andc2	        BOOLE_ANDC2
#define Boole_c1	        BOOLE_C1
#define Boole_c2	        BOOLE_C2
#define Boole_clr	        BOOLE_CLR
#define Boole_eqv	        BOOLE_EQV
#define Boole_ior	        BOOLE_IOR
#define Boole_nand	        BOOLE_NAND
#define Boole_nor	        BOOLE_NOR
#define Boole_orc1	        BOOLE_ORC1
#define Boole_orc2	        BOOLE_ORC2
#define Boole_set	        BOOLE_SET
#define Boole_xor	        BOOLE_XOR
#define Call_arguments_limit    CALL_ARGUMENTS_LIMIT
#define Char_code_limit	        CHAR_CODE_LIMIT
/* #define Lambda_parameters_limit	LAMBDA_PARAMETERS_LIMIT  -- NYI */
#define Multiple_values_limit	MULTIPLE_VALUES_LIMIT

/* Temporary  */
#define result SI_First_value

#undef NOT
#define NOT(x) ((x) == NIL ? T : NIL)

/* Stonefly translator produces these */

#define ADD_PACKAGE_NICKNAME(pkg, name) SI_ADD_PACKAGE_NICKNAME(&pkg, name)
#define NEW_SYMBOL(pkg, name, externalp) SI_NEW_SYMBOL(&pkg, name, externalp)
#define ADD_SHADOW(pkg, symbol)  SI_ADD_SHADOW(&pkg, symbol)
#define ADD_PACKAGE_USE(pkg, use) SI_ADD_PACKAGE_USE(&pkg, &use)
#define ADD_IMPORT(pkg, symbol, ext) SI_ADD_IMPORT(&pkg, symbol, ext)

#define ENSURE_GLOBAL(location, pkg, name, externp) \
     SI_ENSURE_GLOBAL(&location, &pkg, name, externp)

#define ENSURE_GLOBAL_CONSTANT(value, pkg, name, externp) \
     SI_ENSURE_GLOBAL_CONSTANT(value, &pkg, name, externp)

/* Stonefly translator produces these; phase some of them out at some point */

#define BOX_INT(x)      	FIX(x)
#define UNBOX_INT(x)		IFIX(x)
#define BOX_CHAR(x)		CHR(x)
#define UNBOX_CHAR(x)		ICHAR_CODE(x)
#define BOX_BOOLEAN(x)   	((x) ? T : NIL)
#define UNBOX_BOOLEAN(x)	TRUEP(x)
#define BOX_DOUBLE(x)		cdouble_to_double(x)
#define UNBOX_DOUBLE(x)		IDOUBLE(x)
#define UNBOUND_MARKER		UNBOUND

#define DECLARE_SPECIAL       	Declare_special
#define DECLARE_CATCH		Declare_catch
#define DECLARE_AREA		Declare_area
#define DECLARE_FRONTIER        Declare_frontier
#define DECLARE_DYNAMIC_STATE() Declare_dynamic_state
#define DECLARE_PROTECT		Declare_protect
#define DECLARE_STACK_POINTER() Declare_stack_pointer


