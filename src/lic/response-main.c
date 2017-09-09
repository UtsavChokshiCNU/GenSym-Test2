#include "response-util.h"

main(argc, argv)
  int argc; char *argv[];
{ char response[500];
  printf("%s\n", compute_response(response, atoi(argv[2]), argv[1] ));
  exit(0);}

