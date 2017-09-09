#include <stdio.h>
#include <stdlib.h>

#ifndef TRUE
#define TRUE  1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define BRIDGE_NAME    "G2-ORACLE"
#define BRIDGE_VER     "V6"

long main()
{

  extern short stage1(),stage2(),periodic();

  
  /*
   *  Check Authorization
   */

  // STAGE1: Get machine ID, verify ok file entry exists for this machine
  // and product/version in question
  if (stage1(BRIDGE_NAME,BRIDGE_VER) != TRUE) {
    printf("Failed STAGE1 authorization check\n");
    goto FAILED;
  }

//printf("SITE: %s\n",ok.machine_id);

  // STAGE2: Verify OK file codes against this machine/product/version
  if (stage2() != TRUE) {
    printf("Failed STAGE2 authorization check\n");
    goto FAILED;
  }

  // PERIODIC: Update code check usually performed during G2-to-GSI
  // connection (i.e. initialize_context);
  if (periodic() != TRUE) {
    printf("Failed PERIODIC authorization check\n");
    goto FAILED;
  }

  printf("\nAuthorization PASSED \n");
  getchar();
  return 0;

FAILED:
  printf("\nAuthorization FAILED \n");
  getchar();
  return 1;
}