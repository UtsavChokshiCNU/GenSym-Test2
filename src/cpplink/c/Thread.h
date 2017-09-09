
/*----------------------------------------------------------------------
CLASS
    Thread

KEYWORDS
    LinkThread

AUTHOR
    Allan Scott

DESCRIPTION
    An abstract base class that is extended by objects that wish to
    run their own separate thread.  For example: LinkThread, TickleThread.
	
LAST MODIFIED
    
----------------------------------------------------------------------*/

#ifndef _CPP_LINK_THREAD_H
#define _CPP_LINK_THREAD_H

namespace CppLink
{

class Thread
{
public:
  Thread();
  ~Thread();
  virtual void start();
  virtual void run() = 0;
  virtual void stop();
protected:
  bool mStopFlag;
  virtual void kill();
};

}

#endif // ifndef _CPP_LINK_THREAD_H