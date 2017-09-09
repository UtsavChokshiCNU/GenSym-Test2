#ifndef _CONTAINER_H
#define _CONTAINER_H


// Contained Class

class Contained {

	public:
		Contained	*Next;					// Link to next Object in collection
		Contained  *Prev;					// Link to previous Object in collection
		Contained  *HashNext;
		Contained  *HashPrev;
		Contained *GetNext() {return Next;};// Return next member of linked list
		unsigned char isContained;
		virtual long GetHash(void);			// Returns Hash Code. Normally calls GetKey()
		virtual WCHAR *GetKey(void);			// Method to return key of the object as an
											// ASCIIZ string. Normally return NULL
		virtual ~Contained() {};			// Destructor for Contained
		Contained() {isContained = 0; Next = Prev = HashNext = HashPrev = NULL;};
};


// Container Class

class Container {


	public:
		Contained	*Head;					// Pointer to first Object in collection
		Contained  *Tail;					// Pointer to last object in collection
		Contained *(*HashArrayPtrs);		// Array of pointers to contained objects
		int HashSize;						// Size of Hash Table
		int Count;							// Number of object in collection
	
		Container(int Size = 100);			// Hash Table 
		~Container();						// Destructor to free the Hash Memory 
		static unsigned short calc_hash_from_string(WCHAR *);
		unsigned short calc_hash(long);
		void Add(Contained *);				// Adds the contained member to collection
		void Remove(Contained *);			// Removes the contained member of collection
		Contained *GetFirst(void) {return Head;};	// Return first member of list
		void Empty(void);					// Deletes every member of Hashtable
		Contained *FindObj(OLECHAR *);		    // Given the null terminated string, find the
											// member with this given object id, if any.
						 					// Returns a void reference if none is found.
											// The GetKey() method of the contained object
											// must match this value
		Contained *FindObj(long);      		// Given the int value, find the
											// member with this given object id, if any.
											// The GetHash() method of the contained object
											// must match this value
};

class NoHashContainer:public Container {
public:
	NoHashContainer(int Size = 0):Container(Size) {};
};


#endif
