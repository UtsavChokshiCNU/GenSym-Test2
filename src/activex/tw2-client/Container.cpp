
#include "stdafx.h"
#include "Container.h"

// Member Functions for Container class

// This code is not thread safe.  Instead, this depends on the using code to explicitly manage thread locking to insure that
// only one thread may be active at a time.  


Container::Container(int size) {

	Head = NULL;
	Tail = NULL;
	Count = 0;
	/* If the size of the Hash Table is 0, don't create it */
	if (size != 0){
		HashSize = size;			// Save the size of the Hash Table
		HashArrayPtrs = new (Contained *[HashSize]);	// Allocate Hash Table to hold pointers to the Objects
		// Initialize all HashArray Pointers to NULL
		for (int i=0; i<HashSize; i++)
			HashArrayPtrs[i] = NULL;
	}
	else
		HashSize = 0;	/* Set it to 0, so we can check later */

}

Container::~Container() {

	Contained	*ptr, *tmptr;

	ptr = Head;
	while (ptr){
			tmptr = ptr->Next;
			delete(ptr);
			ptr = tmptr;
	}
		

	/* If the size of the Hash Table is 0, the Hash Table was not created */
	if (HashSize != 0)
		delete HashArrayPtrs;
}

unsigned short Container::calc_hash_from_string(WCHAR *ptrkey){

	if (!ptrkey) return 0;
	unsigned short val;
	for (val=0; *ptrkey; ptrkey++){
		val ^= *ptrkey;
	}

	return val;
}

unsigned short Container::calc_hash(long val) {

	unsigned short sval;
	sval = ((unsigned short) val) % HashSize;
	return sval;
}

void Container::Add(Contained *ptr){

	ptr->isContained = 1;
	Contained *repptr;

	// First, lets add the new object to the linked list

	ptr->Next = NULL;				// Null the pointer to the next structure
	ptr->Prev = Tail;				// Point to the previous Structure

	if (!Head)						// If this is the first, then point the head to the first
		Head = ptr;					// Structure 
	if (Tail)						// If there was a structure there, point Next to the next 
		Tail->Next = ptr;			// structure
	Tail = ptr;						// Have Tail point to the next structure
	Count++;						// Inc. Number of Objects in the Collection

	/* If the size of the Hash Table is 0, the Hash Table was not created */
	if (HashSize){
		// Update the Hash Table
	
		// Check to see if the Count is equal or greater than the Max HashSize allocated
		if (Count >= HashSize)
		{	
			// Delete the Hash Array Table after it has been copied and update it with the
			// new table pointer
			delete(HashArrayPtrs);
			HashSize = HashSize << 1;	// If it is, Double the size of the Hash Table
			ATLTRACE("Resizing hash table\n");
			// cout << "Resizing hash table to " << HashSize << "...";
			// Allocate a Temporary Hash Table to hold pointers to the Objects
			HashArrayPtrs = new (Contained *[HashSize]);
			// Initialize all the Temporary HashArray Pointers to NULL
			for (int i=0; i<HashSize; i++)
				 HashArrayPtrs[i] = NULL;

			// Copy the old table to the new table
			for (repptr = Head; repptr; repptr = repptr->Next) {
				 repptr->HashNext = NULL;
				 repptr->HashPrev = NULL;
				 unsigned HashIndexTmp = calc_hash(repptr->GetHash());// Calculate the Hash Value
				 Contained *haptrtmp = HashArrayPtrs[HashIndexTmp];
				 if (haptrtmp) {
					 repptr->HashNext = haptrtmp;	// Place the next at the head of the new list
					 haptrtmp->HashPrev = repptr;
				 }
				 HashArrayPtrs[HashIndexTmp] = repptr;
			}	
			ATLTRACE("Done\n");
			//cout << "done." << endl;
		} else {
			// Don't do this if we resized
			unsigned HashIndex = calc_hash(ptr->GetHash());	// Calculate the Hash Value
			ptr->HashNext = NULL;
			ptr->HashPrev = NULL;

			Contained *haptr = HashArrayPtrs[HashIndex];

			if (haptr) {
				ptr->HashNext = haptr;	// Place the next at the head of the list
				haptr->HashPrev = ptr;
			}
			HashArrayPtrs[HashIndex] = ptr;
		}

	} /* End of if (size != 0) */
	
}

void Container::Remove(Contained *ptr){

	// First, lets remove the object from the linked list

	if (!ptr->isContained) {
		ATLTRACE("Removing object not in container!!!!");
		exit(1);
	}

	if (ptr->Next) 
		(ptr->Next)->Prev = ptr->Prev;
	else
		Tail = ptr->Prev;

	if (ptr->Prev)
		(ptr->Prev)->Next = ptr->Next;
	else
		Head = ptr->Next;

	Count--;						// Decrement Number of Objects in the Collection

	/* If the size of the Hash Table is 0, the Hash Table was not created */
	if (HashSize != 0){
	
		if (ptr->HashNext)
			(ptr->HashNext)->HashPrev = ptr->HashPrev;

		if (ptr->HashPrev)
			(ptr->HashPrev)->HashNext = ptr->HashNext;
		else {
			unsigned HashIndex = calc_hash(ptr->GetHash());	// Calculate the Hash Value
			HashArrayPtrs[HashIndex] = ptr->HashNext;
		}

	} /* End of if (size != 0) */

	// Now free the list
	delete (ptr);
	
}


void Container::Empty(){

	Contained	*ptr, *tmptr;

	ptr = Head;
	while (ptr){
			tmptr = ptr->Next;
			delete(ptr);
			ptr = tmptr;
	}
		
	/* If the size of the Hash Table is 0, the Hash Table was not created */
	if (HashSize)
		// Initialize all HashArray Pointers to NULL
		for (int i=0; i<HashSize; i++) HashArrayPtrs[i] = NULL; 

	Head = NULL;
	Tail = NULL;
}

	
Contained * Container::FindObj(WCHAR * str){

	/* If the size of the Hash Table is 0, the Hash Table was not created */
	if (HashSize != 0){
		unsigned HashIndex = calc_hash(calc_hash_from_string(str));	// Calculate the Hash Value
		for (Contained *ptr = HashArrayPtrs[HashIndex]; ptr; ptr = ptr->HashNext) {
			if (!wcscmp(str, ptr->GetKey())) return ptr;
		}
	}
	else
		ATLTRACE("Warning: This collection does not contain a Hash Table. An improper search was attempted");
		//cout << "Warning: This collection does not contain a Hash Table. An improper search was attempted";

	return NULL;
}


Contained * Container::FindObj(long val ){

	/* If the size of the Hash Table is 0, the Hash Table was not created */
	if (HashSize != 0){
		unsigned HashIndex = calc_hash(val);	// Calculate the Hash Value
		for (Contained *ptr = HashArrayPtrs[HashIndex]; ptr; ptr = ptr->HashNext) {
			if (val == ptr->GetHash()) return ptr;
		}
	}
	else
		ATLTRACE("Warning: This collection does not contain a Hash Table. An improper search was attempted\n");
		//cout << "Warning: This collection does not contain a Hash Table. An improper search was attempted";

	return NULL;
}


// Member Functions for Contained class


long Contained::GetHash(){

	unsigned short val = Container::calc_hash_from_string(GetKey());
	return val;
}
  
WCHAR * Contained::GetKey(){

	return NULL;
}
