// HLAClassContainer.h: interface for the HLAClass class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _HLAClassContainer_H_
#define	_HLAClassContainer_H_


#include	"HLAClass.h"


class HLAClassContainer
{
public:
	HLAClassContainer();
	virtual ~HLAClassContainer();

	void		empty(void);
	void		add(HLAClass *classP);
	void		remove(HLAClass *classP);
	HLAClass	*find(const char *nameP);
	HLAClass	*find(RTI::ObjectClassHandle handle);
	HLAClass	*findHlaObjectClassForObject(RTI::ObjectHandle ObjectHandle);

private:
	long		m_numClasses;
	HLAClass	**m_classListP;
};

#endif
