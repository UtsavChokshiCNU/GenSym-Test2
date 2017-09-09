#pragma once
#ifndef INC_LIBG2FASTH_XML_SERIALIZATION_H
#define INC_LIBG2FASTH_XML_SERIALIZATION_H

#include <string>
#include <vector>
#include <map>
#include "tinyxml2.hpp"

/**
* Xml serialization base class.
* Every class that needs to be serialized should derive from this class.
*/
namespace xmls {
class serializable;

/**
* Serializable members base class.
* All types that need to be serialized should derive from this class.
*/
class member_base {
protected:
    std::string d_value;
public:
    virtual ~member_base() {};
    std::string toString() { return d_value; };
    const char* c_str() { return d_value.c_str(); };
    std::string *get_string_ptr() { return &d_value; };
};

/**
* Serializable string class.
*/
class x_string : public member_base {
private:
    void assign_value(const std::string value) { d_value = value; };
public:
    x_string() {};
    x_string(std::string value) { assign_value(value); };
    std::string value() { return d_value; };
    x_string operator=(const std::string value) { assign_value(value); return *this; };
    x_string operator=(const char* value) { assign_value(value); return *this; };
};

/**
* Serializable int class.
*/
class x_int : public member_base {
private:
    void assign_value(const int value);
public:
    x_int() { assign_value(0); };
    x_int(int value) { assign_value(value); };
    int value();
    x_int operator=(const int value) { assign_value(value); return *this; };
};

/**
* Serializable bool class.
*/
class x_bool : public member_base {
private:
    void assign_value(const bool value) { d_value = value ? "true" : "false"; };
public:
    x_bool() { assign_value(false); };
    x_bool(bool value) { assign_value(value); };
    bool value();
    x_bool operator=(const bool value) { assign_value(value); return *this; };
};

/**
* Serializable time_t class.
*/
class x_time_t : public member_base {
private:
    void assign_value(const time_t value);
public:
    x_time_t() { assign_value(0); };
    x_time_t(time_t value) { assign_value(value); };
    time_t value();
    x_time_t operator=(const time_t value) { assign_value(value); return *this; };
};

/**
* Member-Field mapping between type and string representation.
*/
class field_mapping;
typedef std::vector<field_mapping*>::iterator FieldMappingIterator;
class field_mapping {
public:
    std::string m_sFieldName;
    std::string *m_sField;
    field_mapping(std::string FieldName, std::string *Field) { m_sFieldName = FieldName; m_sField = Field; };
    std::string getFieldName() { return m_sFieldName; };
    std::string *getField() { return m_sField; };
};

/**
* Member-Class mapping between class and string representation.
*/
class class_mapping;
typedef std::vector<class_mapping*>::iterator ClassMappingIterator;
class class_mapping {
public:
    std::string m_sMemberName;
    serializable *m_cSubclass;
    class_mapping(std::string MemberName, serializable *subclass) { m_sMemberName = MemberName; m_cSubclass = subclass; };
    std::string getName() { return m_sMemberName; };
    serializable *getSubclass() { return m_cSubclass; };
};

/**
* Class-collection base, holds collection of children.
*/
class collection_base;
typedef std::vector<collection_base*>::iterator CollectionIterator;
class collection_base {
    friend class serializable;
private:
    std::string m_sCollectionName;
    std::string m_sCollectionClassType;
protected:
    collection_base() {};
    std::vector<serializable*> m_vCollection;
    std::map<serializable*, bool> m_mOwner;
    void setCollectionName(std::string value) { m_sCollectionName = value; };
    void setCollectionClassType(std::string value) { m_sCollectionClassType = value; };
    std::string getCollectionName() { return m_sCollectionName; };
    virtual serializable *new_element() = 0;
public:
    virtual ~collection_base() {};
    size_t size() { return m_vCollection.size(); };
    serializable *getItem(int itemID) { return m_vCollection.at(itemID); };
    void Clear();
};

/**
* Class-collection template, generic version of collection holding children.
*/
template <typename T>
class collection : public collection_base {
    friend class serializable;
public:
    ~collection() { Clear(); };
    T *new_element();
    void addItem(T *item) { m_vCollection.push_back(item); m_mOwner[item] = false; };
    T *getItem(int itemID) { return (T*)m_vCollection.at(itemID); };
};

/**
* Creates new element of type T
* @return empty object of type T
*/
template <typename T>
T* collection<T>::new_element()
{
    T* newItem = new T();
    m_vCollection.push_back(newItem);
    m_mOwner[newItem] = true;
    return newItem;
};

/**
* Serializeable base class.
* derive your serializable class from serializable
*/
typedef std::vector<serializable*>::iterator SerializableIterator;
class serializable {
    friend class collection_base;
private:
    serializable(serializable const &s) { }
    serializable operator=(serializable const &s) { return *this; };
protected:
    std::string d_xml;
    std::string d_class_name;
    std::string d_inner_text;
    std::vector<field_mapping*> d_field_mappings;
    std::vector<class_mapping*> d_subclass_mappings;
    std::vector<collection_base*> d_subclass_collections;
    serializable();
    virtual ~serializable();
    void set_class_name(std::string class_name) { d_class_name = class_name; };
	/**
	* Register a member
	* @MemberName XML-Description/Name for the member
	* @Member Member to register
	* @return void
	*/
	void register_type(std::string MemberName, member_base *Member, std::string DefaultValue = "");
	/**
	* Register a member-subclass
	* @MemberName XML-Description/Name for the member-class
	* @Member Member-class to register
	* @return void
	*/
	void register_type(std::string MemberName, serializable *Member);
	/**
	* Register a class-collection
	* @CollectionName XML-Description/Name for the collection
	* @SubclassCollection collection to register
	* @return void
	*/
    void register_type(std::string CollectionName, collection_base *SubclassCollection);
	/**
	* Perform serialization
	* @classDoc tinyxml Class Document
	* @rootNode tinyxml Element rootNode
	* @return void
	*/
    void serialize(tinyxml2::XMLDocument *classDoc, tinyxml2::XMLElement *rootNode);
public:
    /**
    * Gets class name of serializing entity.
	* @return class name
    */
    std::string get_class_name() { return d_class_name; };
    /**
    * Set inner text of the node.
    */
    void set_inner_text(std::string value) { d_inner_text = value; };
    /**
    * Gets inner text of the node.
	* @return inner text
    */
    std::string get_inner_text() { return d_inner_text; };
    /**
    * Serializes class to xml. If filepath is provided, it saves the generated xml.
	* @return XML-Data
    */
    std::string to_xml(std::string);
};
}

#endif // !INC_LIBG2FASTH_XML_SERIALIZATION_H