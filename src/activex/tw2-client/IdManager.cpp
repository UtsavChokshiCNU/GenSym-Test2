
#include "stdafx.h"
#include "AXClient.h"
#include "IdManager.h"
#include "stdio.h"

GatewayListClass GatewayList;  // global list of id's

// Find the entry for this id or create one.
GatewayEntry *GatewayListClass::Find(BSTR Id) {
	ATLTRACE("Finding %ws\n", Id);
	GatewayEntry *entry = Id ? (GatewayEntry *) FindObj(Id) : NULL;
	if (!entry) { // add one to the list
		entry = new GatewayEntry;
		entry->mName = Id;
		entry->status = false;
		entry->obj = NULL;
		Add(entry);
	}
	return entry;
}

// Remove a entry if it has not subscribers
void GatewayListClass::RemoveIfEmpty(BSTR Id) {
	GatewayEntry *entry = Find(Id);
	if (!entry->List.Count) { // empty, nuke it
		Remove(entry);
	}
}


// find the entry for this id and call the update method of each subscriber
void GatewayListClass::update_status(BSTR Id, bool status, void *objptr) 
{
	ATLTRACE("Updating status %ws\n", Id);
	GatewayEntry *entry = Find(Id);

	// Got the entry, now run through each member
	entry->status = status;
	entry->obj = objptr;
	GatewayListEntry *ptr;
	for (ptr = (GatewayListEntry *) entry->List.GetFirst(); ptr; ptr = (GatewayListEntry *) ptr->GetNext()) {
		ptr->ptr->update_status(status);
	}
}

// Add a subscription
void GatewayListClass::subscribe(BSTR Id, IdUpdateCallback *ptr) 
{
	ATLTRACE("Subscribing to %ws\n", Id);
	GatewayEntry *entry = Find(Id);
	GatewayListEntry *listEntry = (GatewayListEntry *) entry->List.FindObj((long) ptr);
	if (!listEntry) { // create one 
		listEntry = new GatewayListEntry;
		listEntry->ptr = ptr;
		entry->List.Add(listEntry);
	}
}

// remove a subscription
// automaticly removes if empty
void GatewayListClass::unsubscribe(BSTR Id, IdUpdateCallback *ptr)
{
	ATLTRACE("Unsubscribe to %ws\n", Id);
	GatewayEntry *entry = Find(Id);
	GatewayListEntry *listEntry = (GatewayListEntry *) entry->List.FindObj((long) ptr);
	if (listEntry) {
		entry->List.Remove(listEntry);
		if (!entry->List.Count) {  // remove if empty
			Remove(entry);
		}
	}
}

bool GatewayListClass::getStatus(BSTR Id) 
{
	GatewayEntry *entry = Find(Id);
	return entry->status;
}

void GatewayListClass::getUniqueName(WCHAR *buf) 
{
	long count;
	GatewayEntry *entry;
	for (count = 1; 1; count++) {  // keep looking until we get a new one
		swprintf(buf, L"g2-%d", count);
		entry = (GatewayEntry *) FindObj(buf);
		if (!entry)	{  // add entry to reserve
//			entry = new GatewayEntry;  // now we subscribe
//			USES_CONVERSION;
//			entry->mName = A2W(buf);
//			entry->status = false;
//			Add(entry);
			ATLTRACE("Got unique name:%ws\n", buf);
			return; // got it
		}
	}
}


WCHAR *GatewayEntry::GetKey(void) {
	return (BSTR) mName;
}


