
//
// This is a example of a C++ client.
// It runs with the feature.kb example
//

#define USE_IIOP

#include "CORBA.h"
#include "grid.hh"
#include <iostream.h>

void main(void) {

  // Get pointer to G2 object
  CORBA::Object_ptr objPtr = CORBA::Orbix.string_to_object("IOR:010000000d00000049444c3a677269643a312e3000000000010000000000000024000000010100000a0000006c6f63616c686f7374003a060c000000477269642053657276657200");
  grid_ptr myGridPtr = grid::_narrow(objPtr);

  // Now we have the reference, get the size of the grid
  int height = myGridPtr->height();
  int width = myGridPtr->width();
  int val = myGridPtr->fetch(3,4);
  cout << "Got G2 grid size: Width = " << width << " Height = " << height << " and fetch(3,4) = " << val << endl;

  // tidy up
  CORBA::release(myGridPtr);
}


