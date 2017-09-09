//
// Orbtype.h
//

#ifndef ORBTYPE_H
#define ORBTYPE_H

#include "gsi_main_cpp.h"
#include "G2ContainerClass.h"
#include "G2CorbaContainer.h"

class orbtype : public G2OrbContained {
public:
	G2String key;
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL) = 0;
	virtual char *GetKey() {return (char *) key;};
	orbtype(char *ptr) {key = ptr;};
	virtual int ItemType(void) = 0;
	virtual orbtype* getTrueType(void) { return this; };
};

class orbtype_void : public orbtype {
public:
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL) {return 0;};
	orbtype_void():orbtype("void") {};
	virtual int ItemType(void) {return 2;};
};


class orbtype_boolean : public orbtype {
public:
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	orbtype_boolean():orbtype("boolean") {};
	virtual int ItemType(void) {return 0;};

};

class orbtype_short : public orbtype {
public:
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	orbtype_short():orbtype("short") {};
	virtual int ItemType(void) {return 0;};

};

class orbtype_long : public orbtype {
public:
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	orbtype_long():orbtype("long") {};
	virtual int ItemType(void) {return 0;};
};

class orbtype_llong : public orbtype {
public:
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	orbtype_llong():orbtype("llong") {};
	virtual int ItemType(void) {return 0;};
};



class orbtype_ushort : public orbtype {
public:
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	orbtype_ushort():orbtype("ushort") {};
	virtual int ItemType(void) {return 0;};
};

class orbtype_ulong : public orbtype {
public:
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	orbtype_ulong():orbtype("ulong") {};
	virtual int ItemType(void) {return 0;};
};

class orbtype_ullong : public orbtype
{
public:
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	orbtype_ullong():orbtype("ullong") {};
	virtual int ItemType(void) {return 0;};
};

class orbtype_float : public orbtype {
public:
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	orbtype_float():orbtype("float") {};
	virtual int ItemType(void) {return 0;};
};

class orbtype_double : public orbtype {
public:
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	orbtype_double():orbtype("double") {};
	virtual int ItemType(void) {return 0;};
};

class orbtype_char : public orbtype {
public:
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	orbtype_char():orbtype("char") {};
	virtual int ItemType(void) {return 0;};
};

class orbtype_octet : public orbtype {
public:
	virtual int build_encodeable_object(gsi_item *args, int &argIndex, 
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	orbtype_octet():orbtype("octet") {};
	virtual int ItemType(void) {return 0;};
};

class orbtype_any : public orbtype {
public:
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	orbtype_any():orbtype("any") {};
	virtual int ItemType(void) {return 1;};
};

class orbtype_typecode : public orbtype {
public:
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	orbtype_typecode():orbtype("typecode") {};
	virtual int ItemType(void) {return 1;};
};

class orbtype_principal : public orbtype {
public:
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	orbtype_principal():orbtype("principal") {};
	virtual int ItemType(void) {return 0;};
};

class orbtype_objref : public orbtype {
public:
	gsi_item m_def; // check for NULL before using
	orbtype_objref(gsi_item def, char *id):orbtype(id) {m_def = def;};
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	virtual int ItemType(void) {return 0;};
};

class orbtype_struct : public orbtype {
public:
	gsi_item m_def;
	orbtype_struct(gsi_item def, char *id):orbtype(id) {m_def = def;};
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	virtual int ItemType(void) {return 1;};
};

class orbtype_union : public orbtype {
public:
	gsi_item m_def;
	orbtype_union(gsi_item def, char *id):orbtype(id) {m_def = def;};
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	virtual int ItemType(void) {return 1;};
};

class orbtype_enum : public orbtype {
public:
	gsi_item m_def;
	orbtype_enum(gsi_item def, char *id):orbtype(id) {m_def = def;};
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	virtual int ItemType(void) {return 0;};
};

class orbtype_string : public orbtype {
public:
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	orbtype_string():orbtype("string") {};
	virtual int ItemType(void) {return 0;};
};

class orbtype_sequence : public orbtype {
public:
	gsi_item m_def;
	orbtype_sequence(gsi_item def, char *id):orbtype(id) {m_def = def;};
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	virtual int ItemType(void) {return 1;};
};

class orbtype_array : public orbtype {
public:
	gsi_item m_def;
	orbtype_array(gsi_item def, char *id):orbtype(id) {m_def = def;};
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	virtual int ItemType(void) {return 1;};
};


class orbtype_alias : public orbtype {
public:
	gsi_item m_def;
	G2OrbContext *m_cObj;
	orbtype_alias(gsi_item def, char *id, G2OrbContext *cObj):orbtype(id) {m_def = def;m_cObj=cObj;};
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	virtual int ItemType(void);
	virtual orbtype *getTrueType();
};

class orbtype_stringdef : public orbtype {
public:
	gsi_item m_def;
	orbtype_stringdef(gsi_item def, char *id):orbtype(id) {m_def = def;};	
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	virtual int ItemType(void) {return 0;};
};
	
class orbtype_g2item : public orbtype {
public:
	gsi_item m_def;
	orbtype_g2item():orbtype("g2item") {};
	virtual int build_encodeable_object(gsi_item *args, int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *truetype = NULL);
	virtual int ItemType(void) {return 1;}
};


class orbtypePtr : public G2OrbContained {
public:
	orbtype *m_tObj;
	orbtypePtr(orbtype *tObj) {m_tObj = tObj;};
};


#endif

