//====================================================================
// gsi_initialize_context
//   - called whenever a connection is made to process
//====================================================================

gsi_int gsi_initialize_context (remote_process_init_string, length)
{

  /* 
  Mark, in GSI, we typically perform an authorization check whenever
   a connection is established to the bridge i.e. periodic. Once a user
   is connected, authorization is never again checked. 
  */ 


  /*** Check Authorization ***/
  if (periodic() != TRUE) {
    printf("\n===============================================\n");
    printf(" G2-Database Bridge Authorization has EXPIRED!\n");
    printf(" Please contact Gensym at %s\n",GENSYM_PHONE);
    printf("===============================================\n\n");
    fflush(NULL);
    exit(1);
  }

}


//====================================================================
// main
//====================================================================

int main(argc, argv)
    int   argc;
    char *argv[];
{   
  char    bridge_ver[20];   // e.g. V6.0 (only V6 is checked)
  char    bridge_name[15];  // e.g. g2-oracle (don't think this is used for anything)


  /*
   *  Check Authorization (one time check when process starts)
   */
      if (stage1(bridge_name,bridge_ver) != TRUE)
        exit(1);
      if (stage2() != TRUE)
        exit(1);


  return 0;

}