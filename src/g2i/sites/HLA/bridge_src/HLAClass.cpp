// HLAClass.cpp: implementation of the HLAClass class.
//
//////////////////////////////////////////////////////////////////////

#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<stdarg.h>
#include	<errno.h>
#include	<malloc.h>
#include	<math.h>
#include	<time.h>

#include	<RTI.hh>
#include	"G2Hla.h"

#include	"HLAClass.h"


extern RTI::RTIambassador		*rtiAmbP;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HLAClass::HLAClass(const char *nameP, RTI::ObjectClassHandle handle, BOOL isInteractiveClass)
{
	m_isInteractiveClass= isInteractiveClass;
	m_handle			= handle;

	strncpy(m_name, nameP, MAX_NAME_LENGTH);
	m_name[MAX_NAME_LENGTH - 1] = 0;

	m_masterG2ObjectP	= gsi_make_items(1);

	m_numAttrs			= 0;
	m_attrNamesP		= NULL;
	m_attrHandlesP		= NULL;

	m_numObjects		= 0;
	m_objectsP			= NULL;
}


HLAClass::~HLAClass()
{
	long	i;

	/*
	 *	Reset the entry
	 */
	m_handle  = NULL;
	m_name[0] = 0;

	/*
	 *	free any allocated memory
	 */
	::gsirtl_free_i_or_v_contents(m_masterG2ObjectP[0]);
	::gsi_reclaim_item(m_masterG2ObjectP);
	m_masterG2ObjectP	= NULL;



	if (m_attrNamesP != NULL) {

		for (i = 0 ; i < m_numAttrs ; i++)
			free( m_attrNamesP[i] );

		free( m_attrNamesP );
	}

	if (m_attrHandlesP != NULL)
		free( m_attrHandlesP );


	m_numAttrs			= 0;
	m_attrNamesP		= NULL;
	m_attrHandlesP		= NULL;


	if (m_objectsP != NULL)
		free(m_objectsP);

	m_numObjects		= 0;
	m_objectsP			= NULL;
}


//////////////////////////////////////////////////////////////////////
// Public methods
//////////////////////////////////////////////////////////////////////

const char *HLAClass::getName(void)
{
	return (const char *) m_name;
}


RTI::ObjectClassHandle HLAClass::getHandle(void)
{
	return m_handle;
}



BOOL HLAClass::isHLAClass(RTI::ObjectClassHandle handle)
{
	if (handle == m_handle)
		return TRUE;

	return FALSE;
}


BOOL HLAClass::isHLAClass(const char *nameP)
{
	if (strncmp(nameP, m_name, MAX_NAME_LENGTH) == 0)
		return TRUE;

	return FALSE;
}



void HLAClass::setMasterG2Object(gsi_item item)
{
	::gsirtl_free_i_or_v_contents( m_masterG2ObjectP[0] );
	::gsi_set_type( m_masterG2ObjectP[0] , GSI_NULL_TAG);

	::gsirtl_copy_item_or_value(item, m_masterG2ObjectP[0] );
}


void HLAClass::getG2Object(gsi_item item)
{
	::gsirtl_free_i_or_v_contents( item );
	::gsi_set_type(item , GSI_NULL_TAG);

	if (m_masterG2ObjectP != NULL)
		::gsirtl_copy_item_or_value(m_masterG2ObjectP[0], item);
}



void HLAClass::setHlaClassAttributes(long numAttrs, const char **attrNamesP)
{
	long			i, sz;
	RTI::Handle		h;


	/*
	 *	Free existing settings
	 */
	if (m_attrNamesP != NULL) {

		for (i = 0 ; i < m_numAttrs ; i++)
			free( m_attrNamesP[i] );

		free( m_attrNamesP );
	}

	if (m_attrHandlesP != NULL)
		free( m_attrHandlesP );


	m_numAttrs			= 0;
	m_attrNamesP		= NULL;
	m_attrHandlesP		= NULL;
	
	
	/*
	 *	Copy new settings
	 */
	m_attrNamesP	= (char **) malloc(numAttrs * sizeof(char *));
	if (m_attrNamesP == NULL)
		return;

	m_attrHandlesP	= (RTI::Handle *) malloc(numAttrs * sizeof(RTI::Handle));
	if (m_attrHandlesP == NULL) {
		free( m_attrNamesP );
		return;
	}


	m_numAttrs = numAttrs;

	for (i = 0 ; i < numAttrs ; i++) {

		sz = strlen(attrNamesP[i]) + 1;

		m_attrNamesP[i] = (char *) malloc(sz * sizeof(char));

		if (m_attrNamesP[i] != NULL) {

			strncpy(m_attrNamesP[i], attrNamesP[i], sz);

			try {
				if (m_isInteractiveClass == FALSE)
					h = rtiAmbP->getAttributeHandle((const char *) attrNamesP[i], m_handle);
				else
					h = rtiAmbP->getParameterHandle((const char *) attrNamesP[i], m_handle);
			}
			catch ( RTI::Exception& e )
			{
				log_with_timestamp(LOG_MODE_DEBUG,
						"Exception (%s, %s) while getting attribute handle for '%s'.\n",
						e._name, e._reason, attrNamesP[i]);

				h = NULL;
			}
			m_attrHandlesP[i] = h;


		}	else {

			m_attrHandlesP[i] = NULL;
		}
	}
}


RTI::Handle HLAClass::addHlaClassAttributes(const char *attrNameP)
{
	long			i, sz;
	RTI::Handle		h;


	i = m_numAttrs;
	m_numAttrs++;
	
	/*
	 *	Copy new settings
	 */
	m_attrNamesP	= (char **) realloc(m_attrNamesP, m_numAttrs * sizeof(char *));
	if (m_attrNamesP == NULL)
		return NULL;

	m_attrHandlesP	= (RTI::Handle *) realloc(m_attrHandlesP, m_numAttrs * sizeof(RTI::Handle));
	if (m_attrHandlesP == NULL) {
		free( m_attrNamesP );

		m_attrNamesP = NULL;
		m_numAttrs = 0;

		return NULL;
	}


	sz = strlen(attrNameP) + 1;
	m_attrNamesP[i] = (char *) malloc(sz * sizeof(char));

	if (m_attrNamesP[i] != NULL) {

		strncpy(m_attrNamesP[i], attrNameP, sz);

		try {
			if (m_isInteractiveClass == FALSE)
				h = rtiAmbP->getAttributeHandle((const char *) m_attrNamesP[i], m_handle);
			else
				h = rtiAmbP->getParameterHandle((const char *) m_attrNamesP[i], m_handle);
		}
		catch ( RTI::Exception& e )
		{
			log_with_timestamp(LOG_MODE_DEBUG,
					"Exception (%s, %s) while getting attribute handle for '%s'.\n",
					e._name, e._reason, attrNameP);

			h = NULL;
		}
		m_attrHandlesP[i] = h;


	}	else {

		m_attrHandlesP[i] = NULL;
	}

	return m_attrHandlesP[i];
}

const char * HLAClass::getHlaClassAttribute(RTI::Handle handle)
{
	long	i;

	if (m_attrNamesP != NULL && m_attrHandlesP != NULL) {

		for (i = 0 ; i < m_numAttrs ; i++) {

			if (m_attrHandlesP[i] == handle) 
				return m_attrNamesP[i];
		}
	}

	return NULL;
}

RTI::Handle HLAClass::getHlaClassAttribute(const char * nameP)
{
	long	i;

	if (m_attrNamesP != NULL && m_attrHandlesP != NULL) {

		for (i = 0 ; i < m_numAttrs ; i++) {

			if (strcmp(m_attrNamesP[i], nameP) == 0) 
				return m_attrHandlesP[i];
		}
	}

	return addHlaClassAttributes(nameP);
}




void HLAClass::addHlaObject(RTI::ObjectHandle objectHandle)
{
	if (this->findHlaObject(objectHandle) == TRUE)
		return;

	m_numObjects++;
	m_objectsP = (RTI::ObjectHandle *) realloc(m_objectsP, m_numObjects * sizeof(RTI::ObjectHandle));

	m_objectsP[m_numObjects - 1] = objectHandle;
}


void HLAClass::removeHlaObject(RTI::ObjectHandle objectHandle)
{
	long	i, j;

	for (i = 0 ; i < m_numObjects ; i++) {

		if (m_objectsP[i] == objectHandle) {

			for (j = i + 1 ; j < m_numObjects ; j++, i++)
				m_objectsP[i] = m_objectsP[j];

			m_numObjects--;
			m_objectsP = (RTI::ObjectHandle *) realloc(m_objectsP, m_numObjects * sizeof(RTI::ObjectHandle));

			return;
		}
	}
}

BOOL HLAClass::findHlaObject(RTI::ObjectHandle objectHandle)
{
	long	i;

	if (m_isInteractiveClass == TRUE &&	m_handle == objectHandle)
		return TRUE;

	for (i = 0 ; i < m_numObjects ; i++) {

		if (m_objectsP[i] == objectHandle)
			return TRUE;
	}
	return FALSE;
}


long HLAClass::getAttributeList(char ***attrNamesP, RTI::Handle **attrHandlesP)
{
	*attrNamesP   = m_attrNamesP;
	*attrHandlesP = m_attrHandlesP;

	return m_numAttrs;
}


BOOL HLAClass::isInteractiveClass(void)
{
	return m_isInteractiveClass;
}