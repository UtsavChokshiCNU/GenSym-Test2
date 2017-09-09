/*
 * packages.c - LISPTOC packages functions (includes intern, find_symbol)
 * Copyright (c) 1987-1991 Chestnut Software, Inc.  All rights reserved.
 *
 */ 
 
#include "runtime.h"

extern TLS SI_Area *Current_area;
extern char *Initial_symbol_names[];
extern Object Kexternal;
extern Object Kinherited;
extern Object Kinternal;
extern Object List_of_packages;
DECLARE_VARIABLE(Package);
extern Object Pcl_user;
extern Object *SI_cached_frontier;
extern Object *SI_cached_limit;
extern SI_Area Static_area;
extern SI_Area Dynamic_area;
extern TLS Object Values[];
extern Object eql(Object, Object);
extern Object SI_cons(void);

#if SI_USE_PROTOTYPES

extern void SI_add_external_root(Object *p);
extern Object SI_alloc_primitive_vector(SI_Dimension numelems, enum SI_gcls etype);
extern Object SI_alloc(SI_Size_type size, int align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern char *SI_istring(Object o);
extern Object SI_set_symbol_field(Object sym, Object value, enum SI_Symbol_field field);
extern void SI_set_symbol_value_location(Object symbol, Object *address);
extern Object (*SI_warn_fptr) (long n, char *lstr, ...);
extern Object STATIC_FUNCTION1(Object (*entry) (), Object env, long variadicp, long nreq, long npos);
extern Object cons(Object,Object);
extern Object istring_to_string(char *istring);
extern char *isymbol_name(Object sym);
extern Object length(Object);
extern Object make_string(Object size, Object initial_element);
extern Object member_eql(Object item, Object list);
extern Object member_eq(Object item, Object list);
extern Object member(Object item, Object list, Object test, Object test_not, Object key);
extern Object ncons(Object a);
extern Object nreverse(Object);
extern Object string_eq(Object string1, Object string2, Object start1, Object end1, Object start2, Object end2);
extern Object string(Object);
extern Object find_package(Object pkg_name);
extern Object ifind_package(char *name);
extern Object intern(Object str, Object pkg);
extern Object iintern(char *name, Object pkg);
extern Object use_package(Object packages_to_use, Object pkg);
extern Object find_symbol(Object str, Object pkg);
extern Object ifind_symbol(char *name, Object pkg);
extern void SI_bind_symbols();
extern Object SI_cons();

#else

extern void SI_add_external_root();
extern Object SI_alloc_primitive_vector();
extern Object SI_alloc();
extern Object (*SI_error_fptr) ();
extern char *SI_istring();
extern Object SI_set_symbol_field();
extern void SI_set_symbol_value_location();
extern Object (*SI_warn_fptr) ();
extern Object STATIC_FUNCTION1();
extern Object cons();
extern Object istring_to_string();
extern char *isymbol_name();
extern Object length();
extern Object make_string();
extern Object member_eql();
extern Object member_eq();
extern Object member();
extern Object ncons();
extern Object nreverse();
extern Object string_eq();
extern Object string();
extern Object find_package();
extern Object ifind_package();
extern Object intern();
extern Object iintern();
extern Object use_package();
extern Object find_symbol();
extern Object ifind_symbol();
extern void SI_bind_symbols();

#endif



typedef unsigned short USHORT;
typedef USHORT HASHTAB[100];

extern void SI_INIT_standard_packages();
extern Object SI_Initial_packages;

static int init_packages_flag = FALSE;
static void init_packages();
static Object G2_symbols_pool = Nil;

#define INIT_PACKAGES() \
     if (init_packages_flag != TRUE) { \
         init_packages_flag = TRUE; \
         init_packages(); \
     } else init_packages_flag = init_packages_flag


#define ENSURE_PACKAGE(var) \
    (PACKAGEP(var) ? (var) : ((var) = ensure_package(var)))

#define REINDIRECT(i)    (SI_INDIRECTP(i) ? INDIRECT_SYMBOL(i) : i)

/* symbol search flags */
#define EXTERNAL_SYM  TRUE
#define PRESENT_SYM    FALSE

static Object g2_ab_package = NIL;

extern int g2rtl_current_system_is_g2;

/* Amount of memory to allocate for hash table (mhashtab) */
/* Note that HASH_ALLOC_LARGE must be a multiple of HASH_ALLOC_SMALL */
#define HASH_ALLOC_SMALL  2000
#define HASH_ALLOC_LARGE 80000
#define HASH_ALLOC(pkg) ((SI_Dimension)((pkg==g2_ab_package)?HASH_ALLOC_LARGE:HASH_ALLOC_SMALL))

#define NOT_A_SYMBOL ZERO

static Object The_keyword_package = NIL;
#define THE_KEYWORD_PACKAGE \
    (The_keyword_package == NIL ? \
     (The_keyword_package = ifind_package("KEYWORD")) : \
     The_keyword_package)

static Object The_lisp_package = NIL;
#define THE_LISP_PACKAGE \
    (The_lisp_package == NIL ? \
     (The_lisp_package = ifind_package("LISP")) : \
     The_lisp_package)

FORWARD_STATIC unsigned hash_string();
FORWARD_STATIC Object find_present_symbol(), find_inherited_symbol();
FORWARD_STATIC Object find_initial_entry(), find_noninitial_entry();
FORWARD_STATIC Object iintern_msymbol();
FORWARD_STATIC void iintern_indirect();
FORWARD_STATIC Object make_nicknames();
FORWARD_STATIC Object make_use_list();
FORWARD_STATIC Object ensure_package();
FORWARD_STATIC Object *get_package_mhashtab();
FORWARD_STATIC void init_hashtab ();

Object make_package (pkg_name, nicknames, use)
    Object pkg_name, nicknames, use;
{
    Object pkg;
    char *name;
    Declare_stack_pointer;
    DECLARE_AREA(save);

    SAVE_STACK();
    PROTECT_3(pkg_name,nicknames,use);

    if (SI_Initial_packages == UNBOUND)
	SI_Initial_packages = List_of_packages;

    pkg_name = STRING(pkg_name);

    SAVE_CURRENT_AREA(save);
    SET_CURRENT_AREA(Static_area);
    /* Now we don't have to worry about potential GC's */

    if (find_package(pkg_name) != NIL)
	pkg_name = warn(2, "Package exists: ~s", pkg_name);

    nicknames = SUPPLIEDP(nicknames) ? make_nicknames(nicknames) : NIL;
    use = SUPPLIEDP(use) ? make_use_list(use) : NIL;

    pkg = SI_ALLOC(SI_Package, PACKAGE_TYPE, SI_INSTANCE_TAG, SI_UGLY);
    SI_SET_WRAPPER(pkg, SI_WRAPPER_package);
    name = ISTRING(make_string(length(pkg_name), KOPT));
    (void)strcpy(name, ISTRING(pkg_name));
    PACKAGE_NAME(pkg) = name;
    PACKAGE_NICKNAMES(pkg) = nicknames;
    PACKAGE_USE_LIST(pkg) = use;
    PACKAGE_USED_BY_LIST(pkg) = NIL;
    PACKAGE_SHADOWING_SYMBOLS(pkg) = NIL;
    PACKAGE_SYMTAB(pkg) = NULL;
    PACKAGE_HASHTAB(pkg) = NULL; /* A fresh package has no isymbols */
    PACKAGE_MHASHTAB(pkg) = NULL;
    PACKAGE_SYMBOL_COUNT(pkg) = 0;

    List_of_packages = cons(pkg, List_of_packages); /* static */

    RESTORE_CURRENT_AREA(save);
    RESTORE_STACK();
    if (g2rtl_current_system_is_g2 && (0 == strcmp("AB",name)))
      g2_ab_package = pkg;
    return VALUES_1(pkg);
}

static Object make_nicknames (nicks)
    Object nicks;
{
    Object nicknames = NIL;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(nicks,nicknames);
    while (TRUEP(nicks)) {
	nicknames = cons(STRING(M_CAR(nicks)), nicknames);
	nicks = M_CDR(nicks);
    }
    RESTORE_STACK();
    return nreverse(nicknames);
}

static Object make_use_list (uses)
    Object uses;  /* list of packages, pkg names, or single pkg/name */
{
    Object use_list = NIL, pkg, temp;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(uses,use_list);
    PROTECTI_1(pkg);

    if (!SUPPLIEDP(uses)) {
	temp = THE_LISP_PACKAGE;
	if (temp != NIL)
	    use_list = LIST_1(temp);
	else
	    use_list = NIL;
    } else if (CONSP(uses))
	while(TRUEP(uses)) {
	    pkg = M_CAR(uses);
	    use_list = cons(ENSURE_PACKAGE(pkg), use_list);
	    uses = M_CDR(uses);
	}
    else if (TRUEP(uses))
	use_list = LIST_1(ENSURE_PACKAGE(uses));
    RESTORE_STACK();
    return VALUES_1(use_list);
}

Object in_package (pkg_name, nicknames, uses)
    Object pkg_name, nicknames, uses;
{
    Object onicks, nick, ouses, use;
    SI_Declare_static_constant(FP_STRING_EQ, dummy,
	STATIC_FUNCTION(string_eq, NIL, FALSE, 2, 6));
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_3(pkg_name,nicknames,uses);
    PROTECTI_4(onicks,nick,ouses,use);
    if ((Package = find_package(pkg_name)) != NIL) {
	onicks = PACKAGE_NICKNAMES(Package);
	nicknames = make_nicknames(nicknames);
	while (TRUEP(nicknames)) {
	    nick = M_CAR(nicknames);
	    if (member(nick, onicks, FP_STRING_EQ, KOPT, KOPT))
		onicks = cons(nick, onicks);
	    nicknames = M_CDR(nicknames);
	}
	PACKAGE_NICKNAMES(Package) = onicks;
	ouses = PACKAGE_USE_LIST(Package);
	uses = make_use_list(uses);
	while (TRUEP(uses)) {
	    use = M_CAR(uses);
	    if (member(use, ouses, KOPT, KOPT, KOPT))
		ouses = cons(use, ouses);
	    uses = M_CDR(uses);
	}
	PACKAGE_USE_LIST(Package) = ouses;
    }
    else {
	Package = make_package(pkg_name, nicknames, uses);
    }
    RESTORE_STACK();
    return VALUES_1(Package);    
}

static Object ensure_package (pkg_name)
    Object pkg_name;
{
    Object pkg;

    pkg = find_package(pkg_name);
    if (pkg == NIL)
	error(2, "No such package - ~S", pkg_name);
    return pkg;
}

Object find_package (pkg_name)
    Object pkg_name;
{
    Object result;

    INIT_PACKAGES(); /* provide init for ensure_package() */
    if (PACKAGEP(pkg_name))
	result = pkg_name;
    else if (SYMBOLP(pkg_name))
	result = ifind_package(isymbol_name(pkg_name));
    else if (STRINGP(pkg_name))
	result = ifind_package(ISTRING(pkg_name));
    else 
	error(2, "find_package: invalid argument - ~S", pkg_name);
    return VALUES_1(result);
}

Object ifind_package (name)
    char *name;
{
    Object temp, pkg, nicks;

    INIT_PACKAGES();
    for (temp = List_of_packages; TRUEP(temp); temp = M_CDR(temp)) {
	pkg = M_CAR(temp);
	if (!strcmp(name, PACKAGE_NAME(pkg)))
	    return VALUES_1(pkg);
	nicks = PACKAGE_NICKNAMES(pkg);
	while (TRUEP(nicks)) {
	    if (!strcmp(ISTRING(M_CAR(nicks)), name))
		return VALUES_1(pkg);
	    nicks = M_CDR(nicks);
	}
    }
    return VALUES_1(NIL);  /* package not found */
}

Object package_name (pkg)
    Object pkg;
{
    ENSURE_PACKAGE(pkg);
    return istring_to_string(PACKAGE_NAME(pkg));
}

Object package_nicknames (pkg)
    Object pkg;
{
    ENSURE_PACKAGE(pkg);
    return VALUES_1(PACKAGE_NICKNAMES(pkg));
}

Object package_use_list (pkg)
    Object pkg;
{
    ENSURE_PACKAGE(pkg);
    return VALUES_1(PACKAGE_USE_LIST(pkg)); 
}

Object package_used_by_list (pkg)
    Object pkg;
{
    ENSURE_PACKAGE(pkg);
    return VALUES_1(PACKAGE_USED_BY_LIST(pkg));
}

Object package_shadowing_symbols (pkg)
    Object pkg;
{
    ENSURE_PACKAGE(pkg);
    return VALUES_1(PACKAGE_SHADOWING_SYMBOLS(pkg));
}

Object rename_package (pkg, new_name, new_nicknames)
    Object pkg;
    Object new_name, new_nicknames;
{
    ENSURE_PACKAGE(pkg);
    if (UNSUPPLIED_P(new_nicknames))
	new_nicknames = NIL;
    /* Error if a package with new_name already exists... */
    PACKAGE_NAME(pkg) = ISTRING(new_name);
    PACKAGE_NICKNAMES(pkg) = new_nicknames;
    return VALUES_1(pkg);
}

Object list_all_packages ()
{
    return VALUES_1(List_of_packages);
}

Object symbol_package (sym)
    Object sym;
{
    Object result;

    if (sym == NIL)
	result = THE_LISP_PACKAGE;
    else
        /* --- implementation ----------------------- */
	switch (ISYMBOL_TYPE(sym)) {
	case SYMBOL_TYPE:
	case ESYMBOL_TYPE:
	case KEYWORD_TYPE:
	    /* If initial symbol, go backwards through symbol table.  The
	     * first entry in the table is a special COBJECT pointing to
	     * the package is encountered.  Cf. any initsyms.c file. */
	    do
		sym = PREVIOUS_ISYMBOL(sym);
	    while (ISYMBOL_TYPE(sym) != SI_PRECEDES_ISYMBOLS);
	    result = SI_SYMBOL_PLIST(sym);
	    break;
	case MSYMBOL_TYPE:
	case EMSYMBOL_TYPE:
	case MKEYWORD_TYPE:
	    /* If dynamically-interned ("memory") symbol, traverse "next"
	       link until package is reached. */
	    do
		sym = MSYMBOL_NEXT(sym);
	    while (!PACKAGEP(sym));
	    result = sym;
	    break;
	case USYMBOL_TYPE:
	    /* If uninterned symbol, it has no package. */
	    result = NIL;
	    break;
	default:
	    error(2, "symbol_package: not a symbol - ~S", sym);
	}
        /* ------------------------------------- */
    return VALUES_1(result);
}

Object defpackage_intern (str, pkg)
    Object str, pkg;
{
    intern(str,pkg);
    return VALUES_1(NIL);
}

Object intern (str, pkg)
    Object str, pkg;
{

    /* intern a symbol into the pkg package symbol table */
    if (!STRINGP(str)) {
	error(2, "intern: invalid argument - ~S", str);
	return VALUES_2(NIL, NIL);
    }
    if (UNSUPPLIED_P(pkg)) pkg = Package;
    ENSURE_PACKAGE(pkg);

    return iintern(ISTRING(str), pkg);
}

Object find_symbol (str, pkg)
    Object str, pkg;
{
    if (UNSUPPLIED_P(pkg)) pkg = Package;
    ENSURE_PACKAGE(pkg);

    return ifind_symbol(ISTRING(str), pkg); /* two values */
}

Object RTL_cons_pool = Nil;
/*ARGSUSED*/
Object get_cons()
{
    Object new_cons;
    Declare_area(area);
    new_cons = RTL_cons_pool;
    if (new_cons) {
        RTL_cons_pool = M_CDR(new_cons);
    }
    else {
        SAVE_CURRENT_AREA(area);
        SET_CURRENT_AREA(Dynamic_area);
        new_cons = SI_cons();
        RESTORE_CURRENT_AREA(area);
    }
    return new_cons;
}

Object init_g2_symbol(symbol, size, align, type, tag, gcls)
    Object symbol;
    SI_Size_type size;
    long align;
    enum SI_type type;
    enum SI_tag tag;
    enum SI_gcls gcls;
{
    Object result;
    align = (align > sizeof(Object));

    result = SI_SET_TAG(symbol, tag);
    SI_INIT_HEADER(result, type, 0, gcls,
		   align ? SI_GC_ALIGNED : SI_GC_UNALIGNED);

    return result;
}

Object obtain_g2_symbol(length)
    SI_Size_type length;
{
    Object result, pool_cons, length_cons, chain_cons, temp;

    if (TRUEP(G2_symbols_pool)) {
        for (pool_cons = G2_symbols_pool; pool_cons != Nil; pool_cons = CDR(pool_cons)) {
            length_cons = CAR(pool_cons);
            if (EQL(CAR(length_cons), FIX(length))) {
                chain_cons = CDR(length_cons); 
                if (TRUEP(chain_cons)) {
                    result = CAR(chain_cons);
                    M_CDR(length_cons) = CDR(chain_cons);
                    temp = RTL_cons_pool;
                    M_CDR(chain_cons) = temp;
                    RTL_cons_pool = chain_cons;
                    return result;
                }
                else
                    return Nil;  //chain was found but empty, do not need to continue process
            }
        }
    }
    return Nil;
}

Object reclaim_g2_symbol(symbol)
    Object symbol;
{
    Object temp, pool_cons, length_cons;
    Object new_pool_cons, new_length_cons, new_chain_cons;
    size_t symbol_len;

    symbol_len = sizeof(SI_Noninitial_symbol) + strlen(MSYMBOL_NAME(symbol)) + 1;
    if (TRUEP(G2_symbols_pool)) {
        for (pool_cons = G2_symbols_pool; pool_cons != Nil; pool_cons = CDR(pool_cons)) {
            length_cons = CAR(pool_cons);
            if (EQL(CAR(length_cons), FIX(symbol_len))) {    //chain was found
                if (CDR(length_cons) != Nil)
                    for (temp = CDR(length_cons); CDR(temp) != Nil; temp = CDR(temp)){} //go to last element of chain
                else
                    temp = length_cons;

                new_chain_cons = get_cons();
                M_CAR(new_chain_cons) = symbol;          
                M_CDR(new_chain_cons) = Nil;
                M_CDR(temp) = new_chain_cons; //put new element to the end of chain
                return T;
            }
        }
    }

    // chain was not found or pool is empty
    new_pool_cons = get_cons();
    new_length_cons = get_cons();
    new_chain_cons = get_cons();

    M_CAR(new_chain_cons) = symbol;
    M_CDR(new_chain_cons) = Nil;

    M_CAR(new_length_cons) = FIX(symbol_len);
    M_CDR(new_length_cons) = new_chain_cons;

    M_CAR(new_pool_cons) = new_length_cons;
    M_CDR(new_pool_cons) = G2_symbols_pool;
    G2_symbols_pool = new_pool_cons;
}

long find_and_unintern(symbol, hash_value, pkg, type)
 Object symbol, pkg;
 long type;
 unsigned int hash_value;
{
    Object* mhash_table;
    Object sym, true_sym;

    mhash_table = PACKAGE_MHASHTAB(pkg);
    if (mhash_table != NULL) {
		Object parent = mhash_table[hash_value];
        for (sym = mhash_table[hash_value] ; sym != pkg; sym = MSYMBOL_NEXT(sym)) {
            if (type == EXTERNAL_SYM && !SI_EXTERNALP(sym)) continue;
	        if (SI_INDIRECTP(sym))
    		    true_sym = INDIRECT_SYMBOL(sym);
	        else
    		    true_sym = sym;
	        if (!strcmp(isymbol_name(symbol), isymbol_name(true_sym))) {
				if (true_sym != mhash_table[hash_value]) 
					MSYMBOL_NEXT(parent) = MSYMBOL_NEXT(true_sym);
				else
					//Gensym-426, after symbol reclaimed, mhash_table should refer to its next symbol
					//mhash_table[hash_value] = pkg;
					mhash_table[hash_value] = MSYMBOL_NEXT(true_sym);
					//Gensym-426
                //put to pool
				reclaim_g2_symbol(true_sym);
                return TRUE;
	        }
			parent = sym;
	    }
    }
    return FALSE;
}

Object unintern (symbol, pkg)
    Object symbol, pkg;
{
    Object use_list;
    unsigned int hash_value;

    if (UNSUPPLIED_P(pkg)) pkg = Package;
    ENSURE_PACKAGE(pkg);

    hash_value = hash_string(MSYMBOL_NAME(symbol),pkg);
    if (find_and_unintern(symbol, hash_value, pkg, PRESENT_SYM))
        return T;

    for (use_list = PACKAGE_USE_LIST(pkg); TRUEP(use_list); use_list = M_CDR(use_list)) {
        int use_hashval = ((HASH_ALLOC(pkg) > HASH_ALLOC(M_CAR(use_list))) ? (hash_value % HASH_ALLOC_SMALL) : hash_value);
        if (find_and_unintern(symbol, use_hashval, M_CAR(use_list), EXTERNAL_SYM))
            return T;
    }

    return Nil;
}


Object defpackage_use_package (pack_to_use, pkg)
    Object pack_to_use, pkg;
{
    use_package(pack_to_use,pkg);
    return VALUES_1(NIL);
}

Object use_package (packages_to_use, pkg)
    Object packages_to_use, pkg;
{
    Object ouses, uses, use, another, how;
    Object sym, entry;
    SI_Initial_symbol *symtab;
    Object *htable;
    long amount, i, fine = TRUE;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_2(packages_to_use,pkg);
    PROTECTI_2(ouses, uses);

    if (UNSUPPLIED_P(pkg)) pkg = Package;
    ENSURE_PACKAGE(pkg);

    ouses = PACKAGE_USE_LIST(pkg);
    packages_to_use = make_use_list(packages_to_use);

    /* reduce uses list if possible befor */
    for (uses = NIL; TRUEP(packages_to_use);
	 packages_to_use = M_CDR(packages_to_use)) {
	use = M_CAR(packages_to_use);
	if (use == THE_KEYWORD_PACKAGE)
	    error(1, "use-package: cannot use KEYWORD package");

	if (!TRUEP(member_eql(use, ouses))) {
	    uses = cons(use, uses);
	}
    }
    while (TRUEP(uses)) {
	use = M_CAR(uses);
	if ((amount = PACKAGE_SYMBOL_COUNT(use))) {
	    symtab = PACKAGE_SYMTAB(use);
	    for (i = 1; i <= amount; i++) {
		sym = TAG_ISYMBOL(symtab, i);
		if (!SI_EXTERNALP(sym)) continue;
		sym  =  REINDIRECT(sym);
		MVS_2(ifind_symbol(ISYMBOL_NAME(sym), pkg), another, how);
		if (how != NIL && sym != another) {
		    fine = FALSE; /* at least one name conflict is found */
		    warn(4, "use_package: name conflict in package ~s with package ~s ,symbol ~s ", pkg, use, sym);
		}
	    }
	}
	if ((htable = PACKAGE_MHASHTAB(use)) != NULL) {
	    int size = HASH_ALLOC(use);
	    for (i = 0; i < size; i++) {
		for (entry = htable[i];
		     entry != use;
		     entry = MSYMBOL_NEXT(entry)) {
		    if (!SI_EXTERNALP(entry)) continue;
		    sym = REINDIRECT(entry);
		    MVS_2(ifind_symbol(MSYMBOL_NAME(sym), pkg),
			  another,
			  how);
		    if (how != NIL && sym != another) {
			fine = FALSE; /* at least one name conflict is found */
			warn(4, "use_package: name conflict in package ~s with package ~s ,symbol ~s ", pkg, use, sym);
		    }
		}
	    }
	}
	ouses = cons(use, ouses);
	/* another is used here as temp */
	another = cons(pkg, PACKAGE_USED_BY_LIST(use));
	PACKAGE_USED_BY_LIST(use) = another;
	uses = M_CDR(uses);
    }
    if (!fine)
	error(1, "use_package: application fail on the name conflicts");
    PACKAGE_USE_LIST(pkg) = ouses;
    RESTORE_STACK();
    return VALUES_1(T);
}

FORWARD_STATIC int SI_export_1();

Object defpackage_export(name, pkg)
    Object name, pkg;
{
    Object symbol;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(pkg);

    symbol = intern(name, pkg);
    SI_export_1(symbol, pkg);
    RESTORE_STACK();
    return VALUES_1(NIL);
}

Object export (symbols, pkg)
    Object symbols, pkg;
{
    Object sym;
    unsigned int fine;

    if (UNSUPPLIED_P(pkg)) pkg = Package;
    ENSURE_PACKAGE(pkg);

    if (SYMBOLP(symbols))	/**** but what to do about NIL? */
	fine = SI_export_1(symbols, pkg);
    else {
	fine = TRUE;
	for (; TRUEP(symbols); symbols = M_CDR(symbols)) {
	    sym = M_CAR(symbols);
	    fine = fine && SI_export_1(sym, pkg);
	}
    }
    if (!fine)
	error(1, "export: name conflicts have been detected");
    return VALUES_1(T);
}

static int SI_export_1 (sym, pkg)
    Object sym, pkg;
{
    Object e = NOT_A_SYMBOL, another, used, list, how;
    unsigned int hashval, fine = TRUE;
    char *name;

    /* *** NIL is special */
    if (sym == NIL)
	return TRUE;		
    hashval = hash_string(name = isymbol_name(sym),pkg);

    /* check whether it is present */
    if ((another = find_initial_entry(&e,name,hashval,pkg,NIL)) == NOT_A_SYMBOL)
	another  = find_noninitial_entry(&e,name,hashval,pkg,NIL);
    if (another != NOT_A_SYMBOL) {
	if (another == sym) 
	    switch (ISYMBOL_TYPE(e)) {
	    case SYMBOL_TYPE: 
		SET_ISYMBOL_TYPE(e,ESYMBOL_TYPE); break;
	    case INDIRECT_TYPE:
		SET_ISYMBOL_TYPE(e,EINDIRECT_TYPE); break;
	    case MSYMBOL_TYPE:
		SET_ISYMBOL_TYPE(e,EMSYMBOL_TYPE); break;
	    case KEYWORD_TYPE:
		break;
	    default:
		if (!SI_EXTERNALP(e))
		    error(2, "export: unexportable symbol - ~S", e);
		break;
	    }
	else {
	    warn(3, "export: conflict with name '~S' in package ~S ",
		 sym, pkg);
	    return FALSE;
	}
    }
    /* check whether it is accessible */
    else if ((another = find_inherited_symbol(name,hashval, pkg))
	     == NOT_A_SYMBOL) {
	warn(3, "export: symbol ~S not accessible in package ~S", sym, pkg);

	return FALSE;
    }	
    /* check for inheritance conflict */
    else if (another != sym) {
	warn(3, "export: inheritance conflict with name '~S' in package ~S ",
	     sym, pkg);
	return FALSE;
    }
    /* sym is consistent with the package; now check dependents */

    for (list = PACKAGE_USED_BY_LIST(pkg);
	 TRUEP(list); list = M_CDR(list)) { 
	used = M_CAR(list);
	MVS_2(ifind_symbol(name, used), another, how);
	if (how != NIL && another != sym) {
	    fine = FALSE;
	    warn(4, "export: conflict with name '~S' in package ~S used by ~S",
		 sym, pkg, used);
	}
    }
    if (fine)			/* now just intern the symbol */
	iintern_indirect(sym, hashval, pkg, EXTERNAL_SYM);
    return fine;
}

FORWARD_STATIC int SI_import_1();

Object defpackage_import_from (name, from, pkg)
    Object name, from, pkg;
{
    Object sym, how;
    
    MVS_2(find_symbol(name, from), sym, how);

    if (!TRUEP(how))
	error(3, "defpackage: no symbol with name ~S in package ~S",
	      name, from);
    else if (!(SI_import_1(sym, pkg)))
	error(3, "defpackage: imported name ~S in conflict with package ~S",
	      sym, pkg);
    return VALUES_1(NIL);
}

Object import (symbols, pkg)
    Object symbols, pkg;
{
    Object sym;
    unsigned int fine;

    if (UNSUPPLIED_P(pkg)) pkg = Package;
    ENSURE_PACKAGE(pkg);

    if (SYMBOLP(symbols))
	fine = SI_import_1(symbols, pkg);
    else {
	fine = TRUE;
	for (; TRUEP(symbols); symbols = M_CDR(symbols)) {
	    sym = M_CAR(symbols);
	    fine == fine && SI_import_1(sym, pkg);
	}
    }
    if (!fine)
	error(1, "import: name conflicts. execution aborted");
    return VALUES_1(T);
}

static int SI_import_1(sym, pkg)
    Object sym, pkg;
{
    Object another, e = NOT_A_SYMBOL;
    unsigned int hashval, fine = TRUE;
    char *name;

    /* *** NIL is special */
    if (sym == NIL) return TRUE;
    hashval = hash_string(name = isymbol_name(sym),pkg);
    /* check whether it is present */
    if ((another = find_initial_entry(&e,name,hashval,pkg,NIL)) == NOT_A_SYMBOL)
	another = find_noninitial_entry(&e,name,hashval,pkg,NIL);
    if (another != NOT_A_SYMBOL) {
	if (another != sym) {
	    fine = FALSE;
	    warn(3, "import: conflict with name '~S' in package ~S ",
		 sym,pkg);
	}
	/* else just leave it */
    }
    /* check whether it is accessible */
    else if ((another = find_inherited_symbol(name,hashval,
					      pkg)) != NOT_A_SYMBOL
	     && another != sym) {
	fine = FALSE;
	warn(3, "import: inheritance conflict with name '~S' in package ~S ",
	     sym,pkg);
    }
    else 
	/* now just intern the symbol */
	iintern_indirect(sym, hashval, pkg, PRESENT_SYM);
    return fine;
}

/* ------------------------------------------------------------------------*/

Object iintern (name, pkg)
    char *name;
    Object pkg;
{
    unsigned int hashval;
    Object sym, use_list, ptype;
    
    INIT_PACKAGES();

    if (UNSUPPLIED_P(pkg)) pkg = Package;
    ENSURE_PACKAGE(pkg);

    /* changed per R. Harris 6/29/94 */
    if (name[0] == 'N' && name[1] == 'I' && name[2] == 'L' && !name[3] &&
	(pkg == THE_LISP_PACKAGE ||
	 TRUEP((Object)member_eq(THE_LISP_PACKAGE,PACKAGE_USE_LIST(pkg))))) {
	ptype = (pkg == THE_LISP_PACKAGE) ? Kexternal : Kinherited;
	return VALUES_2(NIL,ptype);
    }

    hashval = hash_string(name,pkg);
    if ((sym = find_present_symbol(name, hashval, pkg, PRESENT_SYM)) != NOT_A_SYMBOL)
	return sym;  /* find_present_symbol returns 2 values? */
    for (use_list = PACKAGE_USE_LIST(pkg); TRUEP(use_list);
	 use_list = M_CDR(use_list)) {
        int use_hashval = ((HASH_ALLOC(pkg) > HASH_ALLOC(M_CAR(use_list)))?
			   (hashval % HASH_ALLOC_SMALL) : hashval);
	if ((sym = find_present_symbol(name, use_hashval, M_CAR(use_list), EXTERNAL_SYM))
	    != NOT_A_SYMBOL)
	    return sym;
    }
    return iintern_msymbol(name, hashval, pkg);
}

/* find a symbol accessible from a package */
Object ifind_symbol (name, pkg)
    char *name;
    Object pkg;
{
    unsigned int hashval;
    Object sym, ptype;

    if (UNSUPPLIED_P(pkg)) pkg = Package;
    ENSURE_PACKAGE(pkg);

    /* changed per R. Harris 6/29/94 */
    if (name[0] == 'N' && name[1] == 'I' && name[2] == 'L' && !name[3] &&
	(pkg == THE_LISP_PACKAGE ||
	 TRUEP((Object)member_eq(THE_LISP_PACKAGE,PACKAGE_USE_LIST(pkg))))) {
	ptype = (pkg == THE_LISP_PACKAGE) ? Kexternal : Kinherited;
	return VALUES_2(NIL,ptype);
    }

    hashval = hash_string(name,pkg);
    if ((sym = find_present_symbol(name, hashval, pkg, PRESENT_SYM)) != NOT_A_SYMBOL) 
	return sym;  /* find_present_symbol returns 2 values */
    if ((sym = find_inherited_symbol(name,hashval,pkg)) != NOT_A_SYMBOL)
	return VALUES_2(sym, Kinherited);
    return VALUES_2(NIL, NIL);
}

/* find a symbol present in a package */
static Object find_present_symbol (name, hashval, pkg, type)
    char *name;
    unsigned int hashval;
    Object pkg;
    int type;
{
    Object e = NOT_A_SYMBOL;
    Object sym;

    if ((sym = find_initial_entry(&e,name,hashval,pkg,type)) == NOT_A_SYMBOL)
	 sym = find_noninitial_entry(&e,name,hashval,pkg,type);
    if (sym == NOT_A_SYMBOL)
	return VALUES_2(sym, NIL);
    if (sym == NIL) {
	if (pkg == THE_LISP_PACKAGE)
	    return VALUES_2(NIL, Kexternal);
	else
	    return VALUES_2(NIL, Kinherited);
    }
    return VALUES_2(sym, SI_EXTERNALP(e) ? Kexternal : Kinternal);
}
    
/* find a specified entry in a package's static symbol table */
static Object find_initial_entry (entry, name, hashval, pkg, type)
    Object *entry;
    char *name;
    unsigned int hashval;
    Object pkg;
    int type;
{
    unsigned int pos;
    short *hash_table;
    SI_Initial_symbol *symtab;
    Object sym = NOT_A_SYMBOL;

    /* --- implementation --------------------- */
    hash_table = PACKAGE_HASHTAB(pkg);
    if (hash_table != NULL) {
	symtab = PACKAGE_SYMTAB(pkg);
	for (pos = hash_table[hashval]; pos; pos = symtab[pos].next) {
	    *entry = sym = TAG_ISYMBOL(symtab, pos);
	    if (type == EXTERNAL_SYM && !SI_EXTERNALP(sym)) continue;
	    if (SI_INDIRECTP(sym))
		sym = INDIRECT_SYMBOL(sym);
	    if (!strcmp(name, ISYMBOL_NAME(sym)))
		return sym;
	}
    }
    return NOT_A_SYMBOL;
}

/* find a specified entry in a package's dynamic symbol table */
static Object find_noninitial_entry (entry, name, hashval, pkg, type)
    Object *entry;
    char *name;
    unsigned int hashval;
    Object pkg;
    int  type;
{
    Object sym, true_sym, *mhashtab;

    /* --- implementation ----------------- */
    if ((mhashtab = PACKAGE_MHASHTAB(pkg)) != NULL) {
	for (sym = mhashtab[hashval] ; sym != pkg; sym = MSYMBOL_NEXT(sym)) {
	    if (type == EXTERNAL_SYM && !SI_EXTERNALP(sym)) continue;
	    if (SI_INDIRECTP(sym))
		true_sym = INDIRECT_SYMBOL(sym);
	    else
		true_sym = sym;
	    if (!strcmp(name, isymbol_name(true_sym))) {
		*entry = sym;
		return true_sym;
	    }
	}
    }
    /* -----------------------------------  */
    return NOT_A_SYMBOL;
}

/* find an inherited symbol */

static Object find_inherited_symbol (name, hashval, pkg)
    char *name;
    unsigned int hashval;
    Object pkg;
{
    Object use_list, sym;

    for (use_list = PACKAGE_USE_LIST(pkg); TRUEP(use_list);
	 use_list = M_CDR(use_list)) {
        int use_hashval = ((HASH_ALLOC(pkg) > HASH_ALLOC(M_CAR(use_list)))?
			   (hashval % HASH_ALLOC_SMALL) : hashval);
	if ((sym = find_present_symbol(name,use_hashval,
				       M_CAR(use_list),
				       EXTERNAL_SYM))
	    != NOT_A_SYMBOL)
	    return sym;
    }
    return NOT_A_SYMBOL;
}


static void iintern_indirect (sym, hashval, pkg, type)
    Object sym;
    unsigned int hashval;
    Object pkg;
    int type;
{
    Declare_stack_pointer;
    Object newsym, *mhashtab;

    SAVE_STACK();
    PROTECT_2(pkg, sym);
    /* --- implementation -------------------------- */
    mhashtab = get_package_mhashtab(pkg);
    /* sym should be a symbol */
    /*intern the symbol */
    if (USYMBOLP(sym))
	error(1, "intern uninterned symbol: not supported yet");
    else {
	newsym = SI_ALLOC(SI_Noninitial_symbol,
			  (type == EXTERNAL_SYM
			   ? EINDIRECT_TYPE
			   : INDIRECT_TYPE),
			  SI_SYMBOL_TAG,
			  SI_NORMAL);
	INDIRECT_SYMBOL(newsym) = sym;   /* = SYMBOL_PLIST(newsym) - yuck */
    }
    MSYMBOL_NEXT(newsym) = mhashtab[hashval];
    mhashtab[hashval] = newsym;
    /* --------------------------------------------- */
    RESTORE_STACK();
    return /* VALUES_2(newsym, type) */;
}

static Object iintern_msymbol (name, hashval, pkg)
    char *name;
    unsigned int hashval;
    Object pkg;
{
    Object newsym, *mhashtab;
    size_t nextlen;
    DECLARE_AREA(save);

    SAVE_CURRENT_AREA(save);
    SET_CURRENT_AREA(Static_area);
    mhashtab = get_package_mhashtab(pkg);
    /* implementation ------------------------------- */
    nextlen = sizeof(SI_Noninitial_symbol) + strlen(name) + 1;
    newsym = obtain_g2_symbol(nextlen);
    if (TRUEP(newsym))
        newsym = init_g2_symbol(newsym,
                        nextlen,
                       SI_ALIGNMENT_FOR(SI_Noninitial_symbol),
		               (pkg == THE_KEYWORD_PACKAGE? MKEYWORD_TYPE : MSYMBOL_TYPE),
		                SI_SYMBOL_TAG,
		                SI_UGLY);
    else
    newsym = SI_alloc(nextlen,
		      SI_ALIGNMENT_FOR(SI_Noninitial_symbol),
		      (pkg == THE_KEYWORD_PACKAGE
		       ? MKEYWORD_TYPE
		       : MSYMBOL_TYPE),
		      SI_SYMBOL_TAG,
		      SI_UGLY);

    (void)strcpy(MSYMBOL_NAME(newsym), name);
    /* ------------------------------------------- */
    SI_SYMBOL_PLIST(newsym) = NIL;
    MSYMBOL_NEXT(newsym) = mhashtab[hashval];
    mhashtab[hashval] = newsym;
    RESTORE_CURRENT_AREA(save);
    return VALUES_2(newsym, Kinternal);
}

/* The hash table for non-initial symbols is allocated in the static
   area the first time such a symbol is interned. */

static Object *get_package_mhashtab (pkg)
    Object pkg;
{
    Object *mhashtab = PACKAGE_MHASHTAB(pkg);
    Declare_area(save);
    Object v;
    int i;

    if (mhashtab == NULL) {
	SAVE_CURRENT_AREA(save);
	SET_CURRENT_AREA(Static_area);
	v = SI_alloc_primitive_vector(HASH_ALLOC(pkg), A_T);
	for (i = HASH_ALLOC(pkg)-1; i >= 0; --i)
	    SI_ISVREF(v, i) = pkg;
	mhashtab = &SI_ISVREF(v, 0); /* UCK UCK */
	PACKAGE_MHASHTAB(pkg) = mhashtab;
	RESTORE_CURRENT_AREA(save);
    }
    return mhashtab;
}

/* The hash_string function must agree with what the translator's
   initsyms.c generator does. */

static unsigned hash_string (name,pkg)
    char *name;
    Object pkg;
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

/* remember define using next_prime() */
#define COMPUTE_HASHTAB_SIZE(size)  (100)

/* should be invoked BEFORE heap initialization ! */
static void init_hashtab (pkg, size)
    Object pkg;
    SI_Long  size;
{
    SI_Initial_symbol  *symtab;
    USHORT hashval, *hashtab, index, link, i;
    
    i = COMPUTE_HASHTAB_SIZE(size);
    hashtab = (USHORT *) malloc(i * sizeof(USHORT));


    symtab = PACKAGE_SYMTAB(pkg);
    for (i = 1; i <= size; i++) {
	hashval = hash_string(isymbol_name(*(Object *)&symtab[i]),pkg);
	link = hashtab[hashval];
	if (!link) hashtab[hashval] = i;
	else {
	    while (index = symtab[link].next) link = index;
	    symtab[link].next  = i;
	}
    }
    PACKAGE_HASHTAB(pkg) = (short *) hashtab;
 }

/* -------------------------------------------------------------------- */
/* The following are called from initsyms.c                             */
/* -------------------------------------------------------------------- */

Object set_use_list (pkg, use_list)
    Object pkg, use_list;
{
    PACKAGE_USE_LIST(pkg) = use_list;
    return VALUES_1(use_list);
}

Object set_used_by_list (pkg, used_by_list)
    Object pkg, used_by_list;
{
    PACKAGE_USED_BY_LIST(pkg) = used_by_list;
    return VALUES_1(used_by_list);
}

Object set_nicknames (pkg, nicknames)
    Object pkg, nicknames;
{
    PACKAGE_NICKNAMES(pkg) = nicknames;
    return VALUES_1(nicknames);
}

Object set_shadowing_symbols (pkg, shadowing_symbols)
    Object pkg, shadowing_symbols;
{
    PACKAGE_SHADOWING_SYMBOLS(pkg) = shadowing_symbols;
    return VALUES_1(shadowing_symbols);
}


/* ------------------------------------------------------------------ */
/* Initialization interface from initsyms.c for V3+ */
/* ------------------------------------------------------------------ */


Object NEW_PACKAGE (name)
    char *name;
{
    INIT_PACKAGES();

#if SI_SUPPORT_MF
    {
    Object probe;
    probe = ifind_package(name);
    if (TRUEP(probe))
	return probe;
    }
#endif
    return make_package(istring_to_string(name), KOPT, KOPT);
}

void SI_ADD_PACKAGE_NICKNAME (package_ptr, nick)
    Object *package_ptr;
    char *nick;
{
    Declare_stack_pointer;
    Object package;

    SAVE_STACK();
    PROTECT_1(package);
    
    INIT_PACKAGES();
    package = *package_ptr;

    /* Ought to avoid duplicating nicknames if SI_SUPPORT_MF */
    PACKAGE_NICKNAMES(package) =
	cons(istring_to_string(nick), PACKAGE_NICKNAMES(package));
    RESTORE_STACK();
}

void ADD_PACKAGE_NICKNAME (package, nick)
    Object package;
    char *nick;
{
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(package);
    /* Ought to avoid duplicating nicknames if SI_SUPPORT_MF */
    PACKAGE_NICKNAMES(package) =
	cons(istring_to_string(nick), PACKAGE_NICKNAMES(package));
    RESTORE_STACK();
}

Object SI_NEW_SYMBOL (package_ptr, name, externalp)
    Object *package_ptr;
    char *name;
    int externalp;
{
    Object package;
    Object sym;
    INIT_PACKAGES();
    package = *package_ptr;
    sym = iintern(name, package);
    if (externalp)
#if SI_SUPPORT_MF
	/* Symbol might already exist as initial */
	(void)SI_export_1(sym, package);
#else
	SI_SET_STORED_OBJECT_TYPE(sym, EMSYMBOL_TYPE);
#endif
    return sym;
}

Object NEW_SYMBOL (package, name, externalp)
    Object package;
    char *name;
    int externalp;
{

    Object sym = iintern(name, package);
    if (externalp)
#if SI_SUPPORT_MF
	/* Symbol might already exist as initial */
	(void)SI_export_1(sym, package);
#else
	SI_SET_STORED_OBJECT_TYPE(sym, EMSYMBOL_TYPE);
#endif
    return sym;
}

/* in Static area context */
Object SI_ENSURE_GLOBAL(location, pkgptr, name, externp) 
    Object *location, *pkgptr;
    char *name;
    int externp;
{
    Object sym;

    sym = SI_NEW_SYMBOL(pkgptr, name, externp);
    SI_add_external_root(location);
    SI_set_symbol_value_location(sym, location);
    return sym;
}

Object SI_ENSURE_GLOBAL_CONSTANT(value, pkgptr, name, externp) 
    Object value, *pkgptr;
    char *name;
    int externp;
{
    Object sym;

    sym = SI_NEW_SYMBOL(pkgptr, name, externp);
    SET_SYMBOL_VALUE(sym,value);
    return sym;
}

void SI_ADD_SHADOW(package_ptr, symbol) Object *package_ptr, symbol;
{ error(1, "ADD_SHADOW: not implemented yet"); }

void ADD_SHADOW(package, symbol) Object package, symbol;
{ error(1, "ADD_SHADOW: not implemented yet"); }

void SI_ADD_PACKAGE_USE (ppackage, ppackage_to_use)
    Object *ppackage, *ppackage_to_use;
{
    Object ouses, gc_temp, package_to_use, package;

    INIT_PACKAGES();
    package = *ppackage;
    package_to_use = *ppackage_to_use;
    ouses = PACKAGE_USE_LIST(package);

#if SI_SUPPORT_MF
    if (member(package_to_use, ouses, KOPT, KOPT, KOPT) != NIL)
	return;
#endif
    gc_temp = cons(package, PACKAGE_USED_BY_LIST(package_to_use));
    PACKAGE_USED_BY_LIST(package_to_use) = gc_temp;
    gc_temp = cons(package_to_use, ouses);
    PACKAGE_USE_LIST(package) = gc_temp;
}

void ADD_PACKAGE_USE (package, package_to_use)
    Object package, package_to_use;
{
    Object ouses = PACKAGE_USE_LIST(package), gc_temp;

#if SI_SUPPORT_MF
    if (member(package_to_use, ouses, KOPT, KOPT, KOPT) != NIL)
	return;
#endif
    gc_temp = cons(package, PACKAGE_USED_BY_LIST(package_to_use));
    PACKAGE_USED_BY_LIST(package_to_use) = gc_temp;
    gc_temp = cons(package_to_use, ouses);
    PACKAGE_USE_LIST(package) = gc_temp;
}

void SI_ADD_IMPORT (package_ptr, symbol, externalp)
    Object *package_ptr, symbol;
    int externalp;
{
    Object package;

    INIT_PACKAGES();
    package = *package_ptr;

#if SI_SUPPORT_MF
    (void)SI_import_1(symbol, package);
    if (externalp)
	(void)SI_export_1(symbol, package);
#else
    iintern_indirect(symbol, hash_string(isymbol_name(symbol),pkg),
		     package, externalp);
#endif
}

void ADD_IMPORT (package, symbol, externalp)
    Object package, symbol;
    int externalp;
{
#if SI_SUPPORT_MF
    (void)SI_import_1(symbol, package);
    if (externalp)
	(void)SI_export_1(symbol, package);
#else
    iintern_indirect(symbol, hash_string(isymbol_name(symbol),pkg),
		     package, externalp);
#endif
}

/*
 * DUMPED_HASH_CHAINS  = 1: translation-time hash table chains computation
 * DUMPED_HASH_CHAINS  = 0:     startup-time hash table chains computation
 */

#define DUMPED_HASH_CHAINS 0

#if 0 /* obsolete in 3.1 */

void INIT_STATIC_PACKAGE(pkg)
    Object pkg;
{
    SI_Initial_symbol  *symtab;
    SI_Symbol *header;
    SI_Long  *inittab, first;
    SI_Long n, i;
    
    symtab = PACKAGE_SYMTAB(pkg);
    header = &symtab->header;

    /* trick: the size is stored in 'mhashtab' field */
    inittab = (SI_Long *) PACKAGE_MHASHTAB(pkg);
    PACKAGE_MHASHTAB(pkg) = NULL;

    /*initialize the dummy */
    SI_INIT_SYMBOL_RELOCATION_WORD(symtab);
    SI_INIT_SYMBOL_HEADER(header, SI_PRECEDES_ISYMBOLS, pkg);

    /* store the size of the table in the dummy  entry [who knows] */
    symtab->next =  n = *inittab++;

    for (i = 0; i < n;) {
	symtab++;
	SI_INIT_SYMBOL_RELOCATION_WORD(symtab);
	header = &symtab->header;
	first = inittab[i++];
	symtab->name_offset = (short)
	    ((first >> SI_SYMNAME_OFFSET_SHIFT) & SI_SYMNAME_OFFSET_MASK);
	symtab->name_index = (short)
	    (first >> SI_SYMNAME_INDEX_SHIFT);
	SI_INIT_SYMBOL_HEADER
	    (header,
	     ((unsigned)(first & SI_TYPE_MASK)), NULL);
	/* the following for the case when INIT_SYMBOL provides it */
    }
    /* init hash chains */
    init_hashtab (pkg,  n);

    if (!CONSP(List_of_packages)) List_of_packages = NIL;
    List_of_packages = cons(pkg, List_of_packages);

}

#endif /* obsolete in 3.1 */

/* Package system sturtup/lazy initialization */


void SI_insert_T ()
{
    Object pkg, sym, *mhashtab;
    unsigned int hashval;

    sym = T;
    pkg = ifind_package("COMMON-LISP");
    hashval  = hash_string("T",pkg);
    mhashtab = get_package_mhashtab(pkg);
    MSYMBOL_NEXT(sym) = mhashtab[hashval];
    mhashtab[hashval] = sym;
}

extern Object Pkeyword;

static void init_packages()
{
    Declare_area(a);
    
    SAVE_CURRENT_AREA(a);
    SET_CURRENT_AREA(Static_area);

    /* Create standard packages and insert the RTL core symbols.*/

    SI_INIT_standard_packages(); /* create empty packages */
    SI_insert_T();  
    Kexternal = iintern("EXTERNAL",Pkeyword);
    Kinherited = iintern("INHERITED",Pkeyword);
    Kinternal = iintern("INTERNAL",Pkeyword);        
    SI_bind_symbols();       /* create symbols bound by the RTL */
    Package = Pcl_user;      /* the default package */

    RESTORE_CURRENT_AREA(a);
}

void SI_INIT_packages() {
    INIT_PACKAGES();
}

