#pragma once
#include "IDestroyListener.h"

class MockDestroyListener : public IDestroyListener  
{
public:
  MockDestroyListener(): called(false) {}

  bool wasCalled()
  {
    return called;
  }

  virtual void fire() 
  {
    called = true;
  }

private:
  bool called;
};
