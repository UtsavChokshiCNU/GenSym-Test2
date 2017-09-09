// HLAClassContainer.cpp: implementation of the HLAClassContainer class.
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
#include	"HLAClassContainer.h"




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HLAClassContainer::HLAClassContainer()
{
	m_numClasses = 0;
	m_classListP = NULL;
}


HLAClassContainer::~HLAClassContainer()
{
	this->empty();
}


//////////////////////////////////////////////////////////////////////
// Public methods
//////////////////////////////////////////////////////////////////////


void HLAClassContainer::empty(void)
{
	long	i;

	for (i = 0 ; i < m_numClasses ; i++)
		delete m_classListP[i];

	if (m_classListP != NULL)
		free(m_classListP);

	m_numClasses = 0;
	m_classListP = NULL;
}


void HLAClassContainer::add(HLAClass *classP)
{
	RTI::ObjectClassHandle handle = classP->getHandle();

	if (this->find(handle) != NULL)
		return;

	m_numClasses++;
	m_classListP = (HLAClass **) realloc(m_classListP, m_numClasses * sizeof(HLAClass *));

	m_classListP[m_numClasses - 1] = classP;
}

void HLAClassContainer::remove(HLAClass *classP)
{
	long	i, j;

	for (i = 0 ; i < m_numClasses ; i++) {

		if (m_classListP[i] == classP) {

			delete classP;

			for (j = i + 1 ; j < m_numClasses ; j++, i++)
				m_classListP[i] = m_classListP[j];

			m_numClasses--;
			m_classListP = (HLAClass **) realloc(m_classListP, m_numClasses * sizeof(HLAClass *));

			return;
		}
	}
}


HLAClass *HLAClassContainer::find(const char *nameP)
{
	long	i;

	for (i = 0 ; i < m_numClasses ; i++) {

		if (m_classListP[i]->isHLAClass(nameP) == TRUE)
			return m_classListP[i];
	}
	return NULL;
}

HLAClass *HLAClassContainer::find(RTI::ObjectClassHandle handle)
{
	long	i;

	for (i = 0 ; i < m_numClasses ; i++) {

		if (m_classListP[i]->isHLAClass(handle) == TRUE)
			return m_classListP[i];
	}
	return NULL;
}

HLAClass *HLAClassContainer::findHlaObjectClassForObject(RTI::ObjectHandle ObjectHandle)
{
	long	i;

	for (i = 0 ; i < m_numClasses ; i++) {

		if (m_classListP[i]->findHlaObject(ObjectHandle) == TRUE)
			return m_classListP[i];
	}
	return NULL;
}
