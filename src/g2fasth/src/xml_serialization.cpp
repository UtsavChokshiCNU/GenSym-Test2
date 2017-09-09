#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include "xml_serialization.hpp"

using namespace std;

/**
* XML Serialization namespace
*/
namespace xmls
{
/**
* Assign a value to the xint member
*/
void x_int::assign_value(int value)
{
    stringstream ss;
    ss << value;
    d_value = ss.str();
};

/**
* Returns the int-value of the xint member
* @return current value
*/
int x_int::value()
{
    stringstream ss(d_value);
    int value;
    if ((ss >> value).fail())
        return 0;
    return value;
};

/**
Returns the bool-value of the xbool member
@return	current value
*/
bool x_bool::value()
{
    bool value = false;
    string sHelp = d_value;
    transform(sHelp.begin(), sHelp.end(), sHelp.begin(), ::toupper);
    if (sHelp == "TRUE") return true;
    return value;
};

/**
* Assign a value to the xTime_t member
*/
void x_time_t::assign_value(const time_t value)
{
    stringstream ss;
    ss << value;
    d_value = ss.str();
};

/**
* Delete all (self created) collection-elements
*/
void collection_base::Clear()
{
    if (m_vCollection.size() > 0)
    {
        for (vector<serializable*>::iterator it = m_vCollection.begin(); it != m_vCollection.end(); ++it)
            if (m_mOwner.find(*it)->second)
                delete(*it);
        m_vCollection.clear();
        m_mOwner.clear();
    }
}

/**
* SerializableBase Constructor
*/
serializable::serializable()
{ }

/**
* SerializableBase Destructor
* Clean Collections, Mappings and Subclass-Mappings
*/
serializable::~serializable()
{
    if (d_subclass_collections.size() > 0)
    {
        for (CollectionIterator it_collection = d_subclass_collections.begin(); it_collection != d_subclass_collections.end(); ++it_collection)
            (*it_collection)->Clear();
        d_subclass_collections.clear();
    }
    if (d_subclass_mappings.size() > 0)
        for (ClassMappingIterator it_subClassMapping = d_subclass_mappings.begin(); it_subClassMapping != d_subclass_mappings.end(); ++it_subClassMapping)
            delete(*it_subClassMapping);

    if (d_field_mappings.size() > 0)
        for (FieldMappingIterator it_fieldMapping = d_field_mappings.begin(); it_fieldMapping != d_field_mappings.end(); ++it_fieldMapping)
            delete(*it_fieldMapping);

    d_subclass_collections.clear();
    d_subclass_mappings.clear();
    d_field_mappings.clear();
}

void serializable::register_type(string MemberName, member_base *Member, string DefaultValue)
{
    field_mapping *mapping = new field_mapping(MemberName, Member->get_string_ptr());
    *(Member->get_string_ptr()) = DefaultValue;
    d_field_mappings.push_back(mapping);
}

void serializable::register_type(string MemberName, serializable *Member)
{
    class_mapping *mapping = new class_mapping(MemberName, Member);
    d_subclass_mappings.push_back(mapping);
}

void serializable::register_type(string CollectionName, collection_base *SubclassCollection)
{
    SubclassCollection->setCollectionName(CollectionName);
    d_subclass_collections.push_back(SubclassCollection);
}

void serializable::serialize(tinyxml2::XMLDocument *classDoc, tinyxml2::XMLElement *rootNode)
{
    for (FieldMappingIterator it_member = d_field_mappings.begin(); it_member != d_field_mappings.end(); ++it_member)
    {
        rootNode->SetAttribute((*it_member)->getFieldName().c_str(), (*(*it_member)->getField()).c_str());
    }

    for (ClassMappingIterator it_subclass = d_subclass_mappings.begin(); it_subclass != d_subclass_mappings.end(); ++it_subclass)
    {
        serializable *sub_class = (*it_subclass)->getSubclass();
        tinyxml2::XMLElement *subClassNode = classDoc->NewElement(((*it_subclass)->getName()).c_str());
        rootNode->InsertEndChild(subClassNode);
        auto inner_text = (*it_subclass)->getSubclass()->get_inner_text();
        if (inner_text != "")
        {
            tinyxml2::XMLText* memberValue = classDoc->NewText(inner_text.c_str());
            subClassNode->InsertEndChild(memberValue);
        }
        sub_class->serialize(classDoc, subClassNode);
    }

    for (CollectionIterator it_collection = d_subclass_collections.begin(); it_collection != d_subclass_collections.end(); ++it_collection)
    {
        for (size_t c = 0; c < (*it_collection)->size(); c++)
        {
            serializable *item = (*it_collection)->getItem((int)c);
            tinyxml2::XMLElement *elementNode = classDoc->NewElement(item->get_class_name().c_str());
            auto inner_text = item->get_inner_text();
            if (inner_text != "")
            {
                tinyxml2::XMLText* memberValue = classDoc->NewText(inner_text.c_str());
                elementNode->InsertEndChild(memberValue);
            }
            item->serialize(classDoc, elementNode);
            rootNode->InsertEndChild(elementNode);
        }
    }
}

string serializable::to_xml(std::string file_name = "")
{
    tinyxml2::XMLDocument *classDoc = new tinyxml2::XMLDocument();
    tinyxml2::XMLElement *rootNode;
    rootNode = classDoc->NewElement(d_class_name.c_str());
    classDoc->InsertFirstChild(rootNode);
    serialize(classDoc, rootNode);
    if (!file_name.empty())
    {
        classDoc->SaveFile(file_name.c_str(), true);
    }
    tinyxml2::XMLPrinter printer;
    classDoc->Accept(&printer);
    string xmlResult = printer.CStr();
    classDoc->Clear();
    delete(classDoc);
    return xmlResult;
}
}