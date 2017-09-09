// Lock.h: interface for the Lock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOCK_H__F11D8126_2FB7_4297_8E53_771436A5285D__INCLUDED_)
#define AFX_LOCK_H__F11D8126_2FB7_4297_8E53_771436A5285D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/* ========================================================================== */
/*                                                                            */
/*   Classes that are used to synchronize access to the methods of a class.   */
/*                                                                            */
/* ========================================================================== */


/* ========================================================================== */
/*                                                                            */
/* To control access to an object:                                            */
/* 1) include a Lock object as a member in its class definition.              */
/* 2) Any method that will access protected data should begin with            */
/*    Gatekeeper gk(pointer to Lock member) ;                                 */
/* 3) Only access the object with methods with a Gatekeeper.                  */
/*                                                                            */
/* Note that this method only works if the programmers follow thedr rules.    */
/* There is nothing in this code that enforces this behavior.                 */
/*                                                                            */
/* ========================================================================== */
class Lock  
{
public:
	Lock();
	virtual ~Lock();
    void enter() ;
    void leave() ;
private:
	CRITICAL_SECTION m_CriticalSection;
};


/* ========================================================================== */
/*                                                                            */
/* To access a class that has a Lock member, add a Gatekeeper object with the */
/* address of the Lock as its only parameter.  Other threads that use the     */
/* same procedure will be denied access to the class until you destroy the    */
/* Gatekeeper object.  This happens automatically when you exit the procedure.*/
/*                                                                            */
/* ========================================================================== */
class Gatekeeper  
{
public:
	Gatekeeper(Lock*);
	~Gatekeeper();
    void unLock() ;
private:
    Lock    *m_pLock ;
};

#endif // !defined(AFX_LOCK_H__F11D8126_2FB7_4297_8E53_771436A5285D__INCLUDED_)
