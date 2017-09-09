#include "Tickle.h"
#include "Synchronize.h"



namespace CppLink
{

/*----------------------------------------------------------------------
CONSTRUCTORS AND DESTRUCTORS    
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  Tickle constructor
	//
 Tickle::Tickle():
  mIn(-1),
  mOut(-1),
  mCount(0),
  mLocalPort(1025)
{
}

	///////////////////////////////////////////
	//
	//  Tickle destructor
	//


/*----------------------------------------------------------------------
STATIC MEMBERS
----------------------------------------------------------------------*/



/*----------------------------------------------------------------------
INSTANCE MEMBERS
----------------------------------------------------------------------*/

	///////////////////////////////////////////
	//
	//  initialize
	//
#ifdef WIN32

int Tickle::initialize()
{
  Synchronize sync = Synchronize(&mMutex);
  // FIND ME. Windows specific code
  // adapted from jni_gi.c
  int i,errcode;
  WSADATA data;

  if((errcode=WSAStartup(MAKEWORD(2,2),&data))!=0)
    return errcode;
  mListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
  
  mAddrIn.sin_family = AF_INET;
  mAddrIn.sin_addr.s_addr = htonl(INADDR_LOOPBACK); 
  mAddrIn.sin_port = htons (mLocalPort);
  for (i = mLocalPort; i < 65536; i++) {
    if (bind(mListenSocket, (const struct sockaddr *)&mAddrIn, sizeof mAddrIn)) {
      errcode = WSAGetLastError ();
      if ((errcode == WSAEADDRINUSE) || (errcode == WSAEACCES)) {
        mLocalPort++;
        mAddrIn.sin_port = htons(mLocalPort);
      }
      else return errcode;
    } else
      break;
  }
  errcode = listen(mListenSocket, 1);
  if (errcode) {
    return errcode;
  }
  
  mThread.initialize(this);
  return S_OK;
}

#else

// POSIX implementation here

#endif

	///////////////////////////////////////////
	//
	//  finalize
	//
#ifdef WIN32
int Tickle::finalize()
{
  unsigned long temp = 1;
  int addrlen = sizeof(mAddrIn);
  int error = 0;
  int tries=0;
  mThread.start();
  Sleep(10);
  mIn = accept(mListenSocket, (struct sockaddr *)&mAddrIn, &addrlen);
  if (mIn < 0)
      error = WSAGetLastError();
  if (ioctlsocket(mIn, FIONBIO, &temp)<0)
    error = WSAGetLastError();
  if (error) {
    return error;
  }
  return S_OK;
}
#else

// POSIX implementation here

#endif

	///////////////////////////////////////////
	//
	//  connectTickle
	//
#ifdef WIN32
int Tickle::connectTickle()
{
  Synchronize sync = Synchronize(&mMutex);
  struct sockaddr_in addr_out;
  struct hostent    *host = NULL;

  addr_out.sin_family = AF_INET;
  addr_out.sin_port = htons (mLocalPort);
  addr_out.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  if ((mOut = socket(AF_INET, SOCK_STREAM, 0))<0)
    return WSAGetLastError();
  if (connect(mOut, (const struct sockaddr *)&addr_out, sizeof addr_out)<0)
    return WSAGetLastError();

  return S_OK; 
}
#else

// POSIX implementation here
#endif


	///////////////////////////////////////////
	//
	//  tickle
	//
int Tickle::tickle()
{
  if (mOut != -1) { 
    send(mOut, "a", 1, 0);
  }
  return S_OK; 
}

	///////////////////////////////////////////
	//
	//  suckData
	//
void Tickle::suckData()
{
  int bytes = 0;

  /* The idea here is to only suck the tickle data out of the pipe
     occasionally, because it turns out to be slow. */
  if (mCount > 20) {
    mCount = 0;
    bytes = recv(mIn, mBuffer, 100, 0);
  } else {
    mCount++; 
 }
}

	///////////////////////////////////////////
	//
	//  getTickleFd
	//
int Tickle::getTickleFd()
{
  return mIn;
}


}