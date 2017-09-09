/******************************************************************************
 * Client for Gensym Licensing Server
 * Compile this:        gcc -o licensing-client licensing-client.c response-util.c
 * On Windows w/MSVC:   cl licensing-client.c response-util.c ws2_32.lib
 */

/***** Module Imports *****/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#if defined(_WIN32)
#  include <time.h>
#  include <winsock2.h>
#else
#  include <sys/time.h>
#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <netdb.h>
#endif

#include <errno.h>
#include <string.h>

#include "response-util.h"

#if defined(_WIN32)
  #define bzero(a, b) memset(a, 0x0, b)
#endif

/***** Module Locals State *****/

#define LS_SERVER_PORT "7535"
#define LS_SERVER_HOST "localhost"

int verbose = 0;
static int descriptor;
#define REPLY_MAX 4000
static char reply[REPLY_MAX];
static int reply_status;



/**** Module Local Subprograms ****/

static void trace(level,s,arg1,arg2,arg3)
  int level;
  char *s;
  int arg1, arg2, arg3;
{
   if(level<=verbose) printf(s,arg1,arg2,arg3);
}

static char *my_getenv(key,default_value)
   char *key, *default_value;
{
  char *result = getenv(key);
  char *result2 = (result?result:default_value);

  if(2<=verbose)
    printf("Using \"%s\" for %s from %s\n",
	   result2,
	   key,
	   (result?"environment":"defaults"));

  return result2;
}


static void await_reply(lastp)
  int lastp;
{
  int select_has_not_completed = 1;
  int frustrated = 0;
  char* reply_ptr = reply;
  char* reply_limit = &reply[REPLY_MAX];

  bzero(reply_ptr,REPLY_MAX);
  while ( 1 ){
    int select_result;
    fd_set readmask;

    {
      struct timeval tv;
      
      FD_ZERO(&readmask);
      FD_SET(descriptor, &readmask);
      tv.tv_sec = 4;
      tv.tv_usec = 0;
      select_result = select(descriptor+1,
			     &readmask,
			     (fd_set *) NULL,
			     (fd_set *) NULL,
			     &tv);}

    trace(3,"Select returned %d\n",select_result);

    if (select_result==0){
      trace(3,"\n Select timed out.\n");
      if ( reply_ptr == reply ) continue;
      break;}

    if (select_result < 0 && errno==EINTR){
      trace(3,"\n Select interrupted, retrying. \n");
      if(5<frustrated) break;
      frustrated++;
      continue;}

    if (select_result < 0) {
      perror("select");
      if(5<frustrated) break;
      frustrated++;
      continue;}

    if (!FD_ISSET(descriptor,&readmask)){
      trace(3,"Select did not mark any socket as having data?");
      if(5<frustrated) break;
      frustrated++;
      continue;
    }

    /* Otherwise ... eat data */
    {
      int accept = reply_limit-reply_ptr;
#if defined(_WINSOCKAPI_)
      int cnt = recv(descriptor, reply_ptr, accept, 0);
#else
      int cnt = read(descriptor,reply_ptr,accept);
#endif
      if(cnt<0){ 
	trace(0,"%d",errno);
	perror("ERROR: on a read from the server");
	reply_status = -1;
	break;};
      trace(3,"Attempted %d bytes read %d bytes.\n",accept, cnt );
      if(cnt==0)break;
      reply_ptr+=cnt;
      {  
	char *eom = strstr(reply,"\n<<<--GensymLicensing-->>>\n");

	if(eom){
	  reply_ptr = eom;
	  *reply_ptr = '\000';
	  reply_status = 1;
	  break;}}}

    if ( reply_limit<reply_ptr ) break;
  }
  if(frustrated>0) trace(2,"\nFrustrated: %d",frustrated);

  if (2<=verbose)
    printf("Server Say...\n%s\n...yeap that's what he said.\n",reply);

}



static void connect_to_server()
{
  struct sockaddr_in sa, server_addr;
  struct hostent *host_info = gethostbyname(my_getenv("LS_SERVER_HOST",LS_SERVER_HOST));
  int server_listener_port = atoi(my_getenv("LS_SERVER_PORT",LS_SERVER_PORT));

  if(1<=verbose) printf("Connecting to %s.%d...",
		     host_info->h_name, 
		     server_listener_port);

  /* create a socket */
  descriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (descriptor < 0) {
    perror("socket");
    exit (1);
  }

/*  Still have not proved this to be necessary...
    { 
    int option_value = 1;
    setsockopt (descriptor, 
		SOL_SOCKET, SO_KEEPALIVE, 
		(char *) &option_value, sizeof(int));} */


  /* bind my address */
  sa.sin_family = AF_INET;
  sa.sin_port = 0;
  sa.sin_addr.s_addr = htonl(INADDR_ANY);
  if(bind(descriptor, (struct sockaddr*) &sa, sizeof sa) <0) {
    perror("bind");
    exit (1);
  }
  
  /* connect to the server. */
  server_addr.sin_family = host_info->h_addrtype;
  memcpy((char *) &server_addr.sin_addr, 
	 (char *) host_info->h_addr, 
	 sizeof(server_addr.sin_addr));
  server_addr.sin_port = htons(server_listener_port);
  if (connect(descriptor, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
    perror("connect");
    exit (1);
  }

  trace(3,"(descriptor number is %d).\n", descriptor);
  await_reply(0);
  if(reply_status<0) exit(101);
}

static void tell_server(q)
  char *q;
{
  if (1<=verbose)
    printf("Tell Server: %s\n",q);
#if defined(_WINSOCKAPI_)
  send(descriptor, q, strlen(q), 0);
#else
  write(descriptor,q,strlen(q));
#endif
}

static int
  socket_data_available_p(int sock)
{
  fd_set readmask;
  struct timeval timeout;
  /* int rc; */

  timeout.tv_sec = 0;
  timeout.tv_usec = 0;

  FD_ZERO(&readmask);
  FD_SET(sock,&readmask);

  select(1 + sock, &readmask, NULL, NULL, &timeout);
  if (FD_ISSET(sock,&readmask))
    return 1;
  else
    return 0;
}









/******* Module Exports *****/

main (argc, argv)
 int argc;
 char *argv[];
{
  char *ls_password = my_getenv("LS_PASSWORD","");
  char *ls_user = my_getenv("LS_USER","");
  char *ls_command = "";


#ifdef _WIN32
    /* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSADATA wsaData;
    int err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }
#endif

  { /* Argument Binding */
    int ok=0;
    {  /* Pick the apart */
      int i;
      
      for( i=1;i<argc; i++) {
	if      ( 0==strcmp("-v",argv[i]) ) verbose++;
	else if ( 0==strcmp("-p",argv[i]) ) ls_password = argv[++i];
	else if ( 0==strcmp("-u",argv[i]) ) ls_user = argv[++i];
	else {
	  ls_command = argv[i];
	  ok=1;
	  break;
	}}}
    { /* Validate 'em */
      if( !( strlen(ls_command)>0 && strlen(ls_password)>0 && strlen(ls_user)>0 )){
	if ( ! strlen(ls_command)>0 ) trace(1,"No command.");
	if ( ! strlen(ls_password)>0 ) trace(1,"No user.");
	if ( ! strlen(ls_user)>0 ) trace(1,"No password.");
	trace(0,"ERROR: Malformed arguments or wrong environment.\n");
	exit(100);}}}

  { /* The Body */
    connect_to_server();
    
    { /* Send the user's question. */
      char cmd[1000];
      
      sprintf(cmd,"(do-for-me %s (%s))",ls_user,ls_command);
      tell_server(cmd);
      await_reply(0);
      if(reply_status<0) exit(102);}
    
    { /* Respond to the challenge */
      int challenge = atoi(&reply[strlen("Challenge: ")]);
      char response_buffer1[100];
      char response_buffer2[100];
      if(!strstr(reply,"Challenge: ")){
	trace(1,"No challenge?");
	exit(104);}
      trace(1,"We have been challenged with: %d\n",challenge);
      compute_response(response_buffer1,challenge,ls_password);
      sprintf(response_buffer2,"(response \"%s\")",response_buffer1);
      tell_server(response_buffer2);
      await_reply(1);}
    
    { /* Print the reply */
      printf("%s",reply);}
    
    { /* That's all folks */
      trace(1,"Shutdown\n",0);
#if defined(_WINSOCKAPI_)
      closesocket(descriptor);
#else
      close(descriptor);
#endif
      exit(0);}}}
