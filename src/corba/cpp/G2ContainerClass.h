#ifndef CONTAINERH
#define CONTAINERH

#include <iostream_ver.h>
#include "gsi_main_cpp.h"


// Contained Class

class G2OrbContained {

	public:
		G2OrbContained	*Next;					// Link to next Object in collection
		G2OrbContained  *Prev;					// Link to previous Object in collection
		G2OrbContained  *HashNext;
		G2OrbContained  *HashPrev;
		G2OrbContained *GetNext() {return Next;};	// Return next member of linked list
		unsigned char isContained;
		virtual gsi_int GetHash();				// Returns Hash Code. Normally calls GetKey()
		virtual char *GetKey();					// Method to return key of the object as an
												// ASCIIZ string. Normally return NULL
		virtual ~G2OrbContained() {};			// Destructor for G2OrbContained
		G2OrbContained() {isContained = 0; Next = Prev = HashNext = HashPrev = NULL;};
};


// Container Class

class G2OrbContainer {

	enum boolean {T, F};

	public:
		G2OrbContained	*Head;					// Pointer to first Object in collection
		G2OrbContained  *Tail;					// Pointer to last object in collection
		G2OrbContained *(*HashArrayPtrs);		// Array of pointers to contained objects
		int HashSize;							// Size of Hash Table
		int Count;								// Number of object in collection
	
		G2OrbContainer(int Size = 100);			// Hash Table 
		~G2OrbContainer();						// Destructor to free the Hash Memory 
		static unsigned short calc_hash_from_string(char *);
		unsigned short calc_hash(gsi_int);
		void Add(G2OrbContained *);				// Adds the contained member to collection
		void Remove(G2OrbContained *);			// Removes the contained member of collection
		G2OrbContained *GetFirst() {return Head;};	// Return first member of list
		void Empty();							// Deletes every member of Hashtable
		G2OrbContained *FindObj(char *);		// Given the null terminated string, find the
												//   member with this given object id, if any.
						 						//   Returns a void reference if none is found.
												//   The GetKey() method of the contained object
												//   must match this value
		G2OrbContained *FindObj(gsi_int);		// Given the int value, find the
												//   member with this given object id, if any.
												//   The GetHash() method of the contained object
												//   must match this value
		void ExplicitInit(int Size);			// Global constructors do not
												//   fire when code is compiled
												//   with g++ on HP-UX. This
												//   gives us a way to call it
												//   explicitly.
};

class NoHashContainer:public G2OrbContainer {
public:
	NoHashContainer(int Size = 0):G2OrbContainer(Size) {};
};


#endif

