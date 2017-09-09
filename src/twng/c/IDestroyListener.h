#pragma once

class IDestroyListener  
{
public:
  virtual ~IDestroyListener() {}
  virtual void fire() = 0;
};
