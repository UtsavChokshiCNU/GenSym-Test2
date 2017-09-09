// HLAClass.h: interface for the HLAClass class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _HLAClass_H_
#define	_HLAClass_H_


class HLAClass
{
public:
	HLAClass(const char *nameP, RTI::ObjectClassHandle handle, BOOL isInteractiveClass);
	virtual ~HLAClass();

	const char				*getName(void);
	RTI::ObjectClassHandle	getHandle(void);

	BOOL					isHLAClass(RTI::ObjectClassHandle handle);
	BOOL					isHLAClass(const char *nameP);

	void					setMasterG2Object(gsi_item item);
	void					getG2Object(gsi_item item);

	void					setHlaClassAttributes(long numAttrs, const char **attrNamesP);
	RTI::Handle				addHlaClassAttributes(const char *attrNameP);
	const char				*getHlaClassAttribute(RTI::Handle handle);
	RTI::Handle				getHlaClassAttribute(const char * nameP);

	void					addHlaObject(RTI::ObjectHandle objectHandle);
	void					removeHlaObject(RTI::ObjectHandle objectHandle);
	BOOL					findHlaObject(RTI::ObjectHandle objectHandle);

	long					getAttributeList(char ***attrNamesP, RTI::Handle **attrHandlesP);

	BOOL					isInteractiveClass(void);

private:
	BOOL					m_isInteractiveClass;
	char					m_name[MAX_NAME_LENGTH];
	RTI::ObjectClassHandle	m_handle;

	gsi_item				*m_masterG2ObjectP;

	long					m_numAttrs;
	char					**m_attrNamesP;
	RTI::Handle				*m_attrHandlesP;

	long					m_numObjects;
	RTI::ObjectHandle		*m_objectsP;
};

#endif
