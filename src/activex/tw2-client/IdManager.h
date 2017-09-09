

#ifndef IDMANAGER_H_INCLUDED
#define IDMANAGER_H_INCLUDED
#include "Container.h"

//
// This code is used to match connections indirect tags
// When there is a change of status, we need to update each registered object.
// We need to find the object and check its current status.
//

class IdUpdateCallback {
public:
	virtual void update_status(bool status) = 0;
};

class GatewayEntry;

class GatewayListClass : public Container {
public:
	void update_status(BSTR Id, bool status, void *ptr);
	void subscribe(BSTR Id, IdUpdateCallback *ptr);
	void unsubscribe(BSTR Id, IdUpdateCallback *ptr);
	void getUniqueName(WCHAR *buf);
	bool getStatus(BSTR Id);
private:
	GatewayEntry *Find(BSTR Id);
	void RemoveIfEmpty(BSTR Id);
};


class GatewayEntry : public Contained {
public:
	CComBSTR mName;
	bool status;
	void *obj;
	Container List;  // list of registred objects.
	WCHAR *GetKey(void);
};

class GatewayListEntry : public Contained {
public:
	IdUpdateCallback *ptr;
	long GetHash() {return (long) ptr;};
};

extern GatewayListClass GatewayList;  // global list of gateway entries
#endif
