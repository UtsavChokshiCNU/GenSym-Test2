
#include "stdafx.h"
//#include <malloc.h>
//#include <string.h>
//#include <stdlib.h>

#include "G2Container.h"
#include "RequestObj.h"

// Member Functions for G2OrbContainer class

// This code is not thread safe.  Instead, this depends on the using code to explicitly manage thread locking to insure that
// only one thread may be active at a time.
G2OrbContainer::G2OrbContainer(int size)
{
    Head = NULL;
    Tail = NULL;
    Count = 0;
    /* If the size of the Hash Table is 0, don't create it */
    if (size != 0)
    {
        HashSize = size;            // Save the size of the Hash Table
        HashArrayPtrs = new (G2OrbContained *[HashSize]);    // Allocate Hash Table to hold pointers to the Objects
        // Initialize all HashArray Pointers to NULL
        for (int i=0; i<HashSize; i++)
            HashArrayPtrs[i] = NULL;
    }
    else
        HashSize = 0;    /* Set it to 0, so we can check later */

}

G2OrbContainer::~G2OrbContainer()
{
    Gatekeeper          gk(&mLock) ;
    G2OrbContained      *ptr, *tmptr;

    ptr = Head;
    while (ptr)
    {
        tmptr = ptr->Next;
        delete(ptr);
        ptr = tmptr;
    }


    /* If the size of the Hash Table is 0, the Hash Table was not created */
    if (HashSize != 0)
        delete HashArrayPtrs;

}

unsigned short G2OrbContainer::calc_hash_from_string(TCHAR *ptrkey)
{
    if (!ptrkey)
        return 0;
    unsigned short val;
    for (val=0; *ptrkey; ptrkey++)
    {
        val = val << 1;
        val ^= *ptrkey;
    }

    return val;
}

unsigned short G2OrbContainer::calc_hash(gsi_int val)
{
    Gatekeeper          gk(&mLock) ;

    unsigned short sval;
    sval = ((unsigned short) val) % HashSize;
    return sval;
}

void G2OrbContainer::Add(G2OrbContained *ptr)
{
    Gatekeeper          gk(&mLock) ;

    ptr->isContained = 1;
    G2OrbContained *repptr;

    // First, lets add the new object to the linked list

    ptr->Next = NULL;                // Null the pointer to the next structure
    ptr->Prev = Tail;                // Point to the previous Structure

    if (!Head)                        // If this is the first, then point the head to the first
        Head = ptr;                    // Structure
    if (Tail)                        // If there was a structure there, point Next to the next
        Tail->Next = ptr;            // structure
    Tail = ptr;                        // Have Tail point to the next structure
    Count++;                        // Inc. Number of Objects in the Collection

    /* If the size of the Hash Table is 0, the Hash Table was not created */
    if (HashSize)
    {
        // Update the Hash Table

        // Check to see if the Count is equal or greater than the Max HashSize allocated
        if (Count >= HashSize)
        {
            // Delete the Hash Array Table after it has been copied and update it with the
            // new table pointer
            delete(HashArrayPtrs);
            HashSize = HashSize << 1;    // If it is, Double the size of the Hash Table
            ATLTRACE2(atrAxlMsgs,4,"Resizing hash table\n");
            // cout << "Resizing hash table to " << HashSize << "...";
            // Allocate a Temporary Hash Table to hold pointers to the Objects
            HashArrayPtrs = new (G2OrbContained *[HashSize]);
            // Initialize all the Temporary HashArray Pointers to NULL
            for (int i=0; i<HashSize; i++)
                HashArrayPtrs[i] = NULL;

            // Copy the old table to the new table
            for (repptr = Head; repptr; repptr = repptr->Next)
            {
                repptr->HashNext = NULL;
                repptr->HashPrev = NULL;
                unsigned HashIndexTmp = calc_hash(repptr->GetHash());// Calculate the Hash Value
                G2OrbContained *haptrtmp = HashArrayPtrs[HashIndexTmp];
                if (haptrtmp)
                {
                    repptr->HashNext = haptrtmp;    // Place the next at the head of the new list
                    haptrtmp->HashPrev = repptr;
                }
                HashArrayPtrs[HashIndexTmp] = repptr;
            }
        }
        else
        {
            // Don't do this if we resized
            unsigned HashIndex = calc_hash(ptr->GetHash());    // Calculate the Hash Value
            ptr->HashNext = NULL;
            ptr->HashPrev = NULL;

            G2OrbContained *haptr = HashArrayPtrs[HashIndex];

            if (haptr)
            {
                ptr->HashNext = haptr;    // Place the next at the head of the list
                haptr->HashPrev = ptr;
            }
            HashArrayPtrs[HashIndex] = ptr;
        }

    } /* End of if (size != 0) */

}



void G2OrbContainer::Add2(RequestObj *ptr)
{
    Gatekeeper          gk(&mLock) ;

    ptr->secondIsContained = 1;
    RequestObj *repptr;

    // First, lets add the new object to the linked list

    ptr->mpNext2 = NULL;              // Null the pointer to the next structure
    ptr->mpPrev2 = (RequestObj*)Tail; // Point to the previous Structure

    if (!Head)                        // If this is the first, then point the head to the first
        Head = ptr;                    // Structure
    if (Tail)                       // If there was a structure there, point Next to the next
        ((RequestObj*)Tail)->mpNext2 = ptr;   // structure
    Tail = ptr;                     // Have Tail point to the next structure
    Count++;                        // Inc. Number of Objects in the Collection

    /* If the size of the Hash Table is 0, the Hash Table was not created */
    if (HashSize)
    {
        // Update the Hash Table

        // Check to see if the Count is equal or greater than the Max HashSize allocated
        if (Count >= HashSize)
        {
            // Delete the Hash Array Table after it has been copied and update it with the
            // new table pointer
            delete(HashArrayPtrs);
            HashSize = HashSize << 1;    // If it is, Double the size of the Hash Table
            ATLTRACE2(atrAxlMsgs,4,"Resizing hash table\n");
            // cout << "Resizing hash table to " << HashSize << "...";
            // Allocate a Temporary Hash Table to hold pointers to the Objects
            HashArrayPtrs = new (G2OrbContained *[HashSize]);
            // Initialize all the Temporary HashArray Pointers to NULL
            for (int i=0; i<HashSize; i++)
                HashArrayPtrs[i] = NULL;

            // Copy the old table to the new table
            for (repptr = (RequestObj*)Head; repptr; repptr = repptr->mpNext2)
            {
                repptr->mpNextHash2 = NULL;
                repptr->mpPrevHash2 = NULL;
                unsigned HashIndexTmp = calc_hash(repptr->GetHash());// Calculate the Hash Value
                RequestObj *haptrtmp = (RequestObj*)HashArrayPtrs[HashIndexTmp];
                if (haptrtmp)
                {
                    repptr->mpNextHash2 = haptrtmp;    // Place the next at the head of the new list
                    haptrtmp->mpPrevHash2 = repptr;
                }
                HashArrayPtrs[HashIndexTmp] = repptr;
            }
        }
        else
        {
            // Don't do this if we resized
            unsigned HashIndex = calc_hash(ptr->GetHash());    // Calculate the Hash Value
            ptr->mpNextHash2 = NULL;
            ptr->mpPrevHash2 = NULL;

            RequestObj *haptr = (RequestObj*)HashArrayPtrs[HashIndex];

            if (haptr)
            {
                ptr->mpNextHash2 = haptr;    // Place the next at the head of the list
                haptr->mpPrevHash2 = ptr;
            }
            HashArrayPtrs[HashIndex] = ptr;
        }

    } /* End of if (size != 0) */

}

void G2OrbContainer::Remove(G2OrbContained *ptr)
{
    Gatekeeper          gk(&mLock) ;
    internalRemove(ptr, true) ;
}

void G2OrbContainer::RemoveOnly(G2OrbContained *ptr)
{
    Gatekeeper          gk(&mLock) ;
    internalRemove(ptr, false) ;
}

void G2OrbContainer::Remove2Only(RequestObj *pReq)
{
    Gatekeeper          gk(&mLock) ;
    internalRemove2(pReq, false) ;
}

void G2OrbContainer::internalRemove(G2OrbContained *ptr, bool deleteFlag)
{

    // First, lets remove the object from the linked list

    if (!ptr->isContained)
    {
        ATLTRACE2(atrAxlMsgs,4,"Removing object not in container.");
        return;
    }

    if (ptr->Next)
        (ptr->Next)->Prev = ptr->Prev;
    else
        Tail = ptr->Prev;

    if (ptr->Prev)
        (ptr->Prev)->Next = ptr->Next;
    else
        Head = ptr->Next;

    Count--;                        // Decrement Number of Objects in the Collection

    /* If the size of the Hash Table is 0, the Hash Table was not created */
    if (HashSize != 0)
    {

        if (ptr->HashNext)
            (ptr->HashNext)->HashPrev = ptr->HashPrev;

        if (ptr->HashPrev)
            (ptr->HashPrev)->HashNext = ptr->HashNext;
        else
        {
            unsigned HashIndex = calc_hash(ptr->GetHash());    // Calculate the Hash Value
            HashArrayPtrs[HashIndex] = ptr->HashNext;
        }

    } /* End of if (size != 0) */

    // Now free the list
    if (deleteFlag)
        delete (ptr);
	else
	{
		ptr->Prev = ptr->Next = ptr->HashPrev = ptr->HashNext = NULL ;
		ptr->isContained = 0 ;
	}
}

void G2OrbContainer::internalRemove2(RequestObj *ptr, bool deleteFlag)
{

    // First, lets remove the object from the linked list

    if (!ptr->secondIsContained)
    {
        ATLTRACE2(atrAxlMsgs,4,"Cannot remove. RequestObj not in container!");
        return;
    }

    if (ptr->mpNext2)
        (ptr->mpNext2)->mpPrev2 = ptr->mpPrev2;
    else
        Tail = ptr->mpPrev2;

    if (ptr->mpPrev2)
        (ptr->mpPrev2)->mpNext2 = ptr->mpNext2;
    else
        Head = ptr->mpNext2;

    Count--;                        // Decrement Number of Objects in the Collection

    /* If the size of the Hash Table is 0, the Hash Table was not created */
    if (HashSize != 0)
    {

        if (ptr->mpNextHash2)
            (ptr->mpNextHash2)->mpPrevHash2 = ptr->mpPrevHash2;

        if (ptr->mpPrevHash2)
            (ptr->mpPrevHash2)->mpNextHash2 = ptr->mpNextHash2;
        else
        {
            unsigned HashIndex = calc_hash(ptr->GetHash());    // Calculate the Hash Value
            HashArrayPtrs[HashIndex] = ptr->mpNextHash2;
        }

    } /* End of if (size != 0) */

    // Now free the list
    if (deleteFlag)
        delete (ptr);
	else
	{
		ptr->mpPrev2 = ptr->mpNext2 = ptr->mpPrevHash2 = ptr->mpNextHash2 = NULL ;
		ptr->secondIsContained = 0 ;
	}
}


void G2OrbContainer::Empty()
{
    Gatekeeper          gk(&mLock) ;
    G2OrbContained      *ptr, *tmptr;

    ptr = Head;
    while (ptr)
    {
        tmptr = ptr->Next;
        delete(ptr);
        ptr = tmptr;
    }

    /* If the size of the Hash Table is 0, the Hash Table was not created */
    if (HashSize)
        // Initialize all HashArray Pointers to NULL
        for (int i=0; i<HashSize; i++)
            HashArrayPtrs[i] = NULL;

    Head = NULL;
    Tail = NULL;
}


G2OrbContained * G2OrbContainer::FindObj(TCHAR * str)
{
    Gatekeeper          gk(&mLock) ;

    /* If the size of the Hash Table is 0, the Hash Table was not created */
    if (HashSize != 0)
    {
        unsigned HashIndex = calc_hash(calc_hash_from_string(str));    // Calculate the Hash Value
        for (G2OrbContained *ptr = HashArrayPtrs[HashIndex]; ptr; ptr = ptr->HashNext)
        {
            if (!_tcscmp(str, ptr->GetKey()))
                return ptr;
        }
    }
    else
        ATLTRACE2(atrAxlMsgs,0,"Warning: This collection does not contain a Hash Table. An improper search was attempted");

    return NULL;
}


G2OrbContained * G2OrbContainer::FindObj(gsi_int val )
{
    Gatekeeper          gk(&mLock) ;

    /* If the size of the Hash Table is 0, the Hash Table was not created */
    if (HashSize != 0)
    {
        unsigned HashIndex = calc_hash(val);    // Calculate the Hash Value
        for (G2OrbContained *ptr = HashArrayPtrs[HashIndex]; ptr; ptr = ptr->HashNext)
        {
            if (val == ptr->GetHash())
                return ptr;
        }
    }
    else
        ATLTRACE2(atrAxlMsgs,0,"Warning: This collection does not contain a Hash Table. An improper search was attempted\n");

    return NULL;
}


// Member Functions for G2OrbContained class


gsi_int G2OrbContained::GetHash()
{

    unsigned short val = G2OrbContainer::calc_hash_from_string(GetKey());
    return val;
}

TCHAR * G2OrbContained::GetKey()
{

    return NULL;
}

