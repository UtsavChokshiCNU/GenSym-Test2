/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      ssl.c
 +
 + CVS location: ext/c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):   Fred White
 +
 + Description: OpenSSL wrapper for G2
 + 
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/rand.h>

#ifdef WIN32
#  include <windows.h>
#  include <winsock.h>
#  define EWOULDBLOCK WSAEWOULDBLOCK
#  define strcasecmp _stricmp
#else
#  include <unistd.h>
#  define TRUE 1
#  define FALSE 0
#endif

#include "ssl.h"

#if defined(sparcsol)
/* We have very old header files on Solaris.  They come from:
  /home/gnu-sol/lib/gcc-lib/sparc-sun-solaris2.5/2.7.2/include
  They don't match up exactly with the libraries we have installed.  Maybe we
  should have taken this more seriously than we have. In any case, make a
  prototype here since our <unistd.h> doesn't contain one, and we don't want
  to hear the compiler complain.  -jv, 12/18/07 */
extern int usleep();
#endif


extern void g2pvt_enqueue_read_event(int sock);
extern void g2pvt_enqueue_write_event(int sock);
extern long g2ext_write_string_to_console(char *str);
extern void g2pvt_trace(const char *fmt, ...);

/*
 * Debugging and Tracing
 */
#define T_OFF 1 ? (void)0 : g2pvt_trace
#define T_ON g2pvt_trace

#define Trace T_OFF
#define PRINTF T_OFF

#ifdef WIN32
#  define mssleep(ms) Sleep(ms)
#else
#  define mssleep(ms) usleep(1000*(ms))
#endif

static SSL_CTX *client_ctx = NULL;
static SSL_CTX *server_ctx = NULL;
static G2SSL_CONNECTION_CALLBACK cb_connect = NULL;

/*
 * Trusted CA
 */

/* This is the certificate for the only CA we trust, the Gensym Certificate
 * Authority. Clients will trust any server whose certificate has been signed by
 * the holder of the private key for this public key, namely Gensym. */

static char *cacert_gensym = "\n\
-----BEGIN CERTIFICATE-----\n\
MIID/TCCAuWgAwIBAgIJAMXc40I/9GfHMA0GCSqGSIb3DQEBBAUAMFwxCzAJBgNV\n\
BAYTAlVTMRYwFAYDVQQIEw1NYXNzYWNodXNldHRzMRMwEQYDVQQHEwpCdXJsaW5n\n\
dG9uMQ8wDQYDVQQKEwZHZW5zeW0xDzANBgNVBAMTBkdlbnN5bTAeFw0wNTA3MTQx\n\
OTUzNDNaFw0wNTA4MTMxOTUzNDNaMFwxCzAJBgNVBAYTAlVTMRYwFAYDVQQIEw1N\n\
YXNzYWNodXNldHRzMRMwEQYDVQQHEwpCdXJsaW5ndG9uMQ8wDQYDVQQKEwZHZW5z\n\
eW0xDzANBgNVBAMTBkdlbnN5bTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoC\n\
ggEBAKnUTXVSPldKZ8X6x0iE42YqfA+c5c9X2s1WfS54V0orwBbnKJDxpGVEsU77\n\
m6OPX//jta0VXqjp0t220pLkysThH+w+MzGa5rHXdXf5Cw3hFi52acGvPJMcED1w\n\
mRiuTnDxUU3Xd0UbPEN17dFL7Ve5/k4khGru3eekL75oSWBQhR0Du1b0BzSg/g0B\n\
KffzAWff8NkmV5HfvuJY7l/qfhNcLyMjNzq5F7mmjPgbjlDbOr4M6KmhdoMzmTF5\n\
aqoOzc95O0LQQ4ilc3swUJQn265RPnEsu9tUHU94UFb1/Lpxtyy9/fYzC+OXhz+F\n\
oe90zs7LZJ6RIldzNKIDcHyIsAECAwEAAaOBwTCBvjAdBgNVHQ4EFgQUKUbDStki\n\
GT/xcy/5gmBmx/+JPe4wgY4GA1UdIwSBhjCBg4AUKUbDStkiGT/xcy/5gmBmx/+J\n\
Pe6hYKReMFwxCzAJBgNVBAYTAlVTMRYwFAYDVQQIEw1NYXNzYWNodXNldHRzMRMw\n\
EQYDVQQHEwpCdXJsaW5ndG9uMQ8wDQYDVQQKEwZHZW5zeW0xDzANBgNVBAMTBkdl\n\
bnN5bYIJAMXc40I/9GfHMAwGA1UdEwQFMAMBAf8wDQYJKoZIhvcNAQEEBQADggEB\n\
AE66Yvlaj5U8ewcTDU8Ya8pAY9dNDdM3VNiih0AL+gkWuSebzgv0sgn1atdLpy+V\n\
Ognm0pv8kxiZWv45RXFel9zjxp07m4iREBauDdI/Ledk2DQvLqGYMKizyPvBokyh\n\
0eqMD/aiJRAT+tqrdFbZfyW8dGLRmzXDt6yFyyLsg7AyP2ywNFYPhaKEJ3gq8Tl5\n\
e4AuJaKUbgGm5ykyLOgFygM0PTPgbD41i0W3KywxfA9ggn6lQefaR0ZZVuQwTBuz\n\
v70AXB7qntEb8d2qpE58b694iQEs/7XC1HGGxwlXyWVjHqbc6sgWqlxqSsumi54K\n\
JrlRt4GMx6bksgllelr4ciE=\n\
-----END CERTIFICATE-----\n";

/*
 * Utility Functions
 */

static void openssl_error(char *msg, ...)
{
  unsigned long e;
  char err[120];

  va_list ap;

  va_start (ap, msg);
  vsprintf(err, msg, ap);
  va_end(ap);

  g2ext_write_string_to_console(err);
  while(e=ERR_get_error()) {
    err[0] = ' ';
    ERR_error_string(e,err+1);
    g2ext_write_string_to_console(err);
  }
}

static int load_trusted_cert(SSL_CTX *ctx, char *cert)
{
  BIO *bio;
  X509 *x;
  X509_STORE *xs;

  bio = BIO_new_mem_buf(cert, -1);
  if(bio == NULL)
    return 0;

  x = PEM_read_bio_X509(bio, NULL, 0, NULL);
  BIO_free(bio);

  if (x == NULL)
    return 0;

/*   PRINTF("Issuer certificate:\n"); */
/*   X509_print_fp(stdout,x); */

  xs = SSL_CTX_get_cert_store(ctx);
  if(!xs)
    return 0;

  return X509_STORE_add_cert(xs,x);
}


static int verify_callback(int ok, X509_STORE_CTX *ctx)
{
  X509 *cert;
  int err, depth;
  char buf[256];

  cert = X509_STORE_CTX_get_current_cert(ctx);
  err = X509_STORE_CTX_get_error(ctx);
  depth = X509_STORE_CTX_get_error_depth(ctx);

  X509_NAME_oneline(X509_get_subject_name(cert), buf, sizeof(buf));
  PRINTF("Depth=%d Subject=%s\n", depth, buf);

  X509_NAME_oneline(X509_get_issuer_name(cert), buf, sizeof(buf));
  PRINTF("Issuer= %s\n", buf);

  /* Getting: X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY */

  if(ok)
    PRINTF("Certificate OK.\n");
  else
    PRINTF("verify error: num=%d %s\n", err, X509_verify_cert_error_string(err));
  return ok;
}



/*
 * Exported Functions
 */



/* Steal a little code from the bundle installer.  We need a file full of random
   bits, and a system command such as tar is likely to always exist.  In fact,
   in order to have installed the bundle, it has to have existed!  But, it might
   be in different places. */

static char *likely_tar_locations[] = { "/usr/bin/tar",
                                        "/sbin/tar",
                                        "/usr/sbin/tar",
                                        "/bin/tar",
                                        NULL };
static char *random_seed_file()
{
  struct stat sb;
  char **sptr = likely_tar_locations;

  do {
    if (!stat(*sptr, &sb))
      return *sptr;
  } while (*sptr++ != NULL);
  /* Didn't find one, sadly, punt.  This is extremely unlikely. */
  return NULL;
}


int g2pvt_ssl_initialize(char *certificate)
{
  SSL_CTX *server, *client;
  static int once=1;
  char* seed_file;

  if(once) {
    SSL_library_init();                              /* Initialize the library */
    SSL_load_error_strings();                      /* Load readable error messages. */
    if(RAND_status() == 0) {
      seed_file = random_seed_file();
      if (seed_file) {
        g2ext_write_string_to_console("SSL: /dev/random not found:  using file for entropy.");
        RAND_load_file(seed_file, 3000);
        } else
          openssl_error("Can't find random seed file.");
    }
    once=0;
  }

  if(strlen(certificate) > 0) {        /* SERVER: Load certificate and private key. */
    server = SSL_CTX_new(SSLv23_method()); /* TLSv1_method SSLv23_method SSLv3_method */

    if(!server) {
      openssl_error("Can't create SSL server context.");
      return 0;
    }

    PRINTF("Loading server cert from %s\n", certificate);

    if(!SSL_CTX_use_certificate_file(server, certificate, SSL_FILETYPE_PEM)) {
      SSL_CTX_free(server);
      openssl_error("Can't read server certificate.");
      return 0;
    }
    if(!SSL_CTX_use_PrivateKey_file(server, certificate, SSL_FILETYPE_PEM)) {
      SSL_CTX_free(server);
      openssl_error("Can't read private key.");
      return 0;
    }
    if(!SSL_CTX_check_private_key(server)) {
      SSL_CTX_free(server);
      openssl_error("Private key does not match the certificate public key.");
      return 0;
    }
    server_ctx = server;
  }
  /* CLIENT: Load hardwired trusted CA certificate. */
  client = SSL_CTX_new(SSLv3_method()); /* TLSv1_method SSLv23_method SSLv3_method */
  
  if(!client) {
    openssl_error("Can't create SSL client context.");
    return 0;
  }
  
  if(!load_trusted_cert(client, cacert_gensym)) {
    SSL_CTX_free(client);
    openssl_error("Can't load Gensym CA certificate.");
    return 0;
  }
/*  Might be nice to do certificate verification, but at present we are turning
    this off in order to allow self-signed certificate use.

  SSL_CTX_set_verify(client, SSL_VERIFY_PEER, verify_callback);
*/
  
  /* Load further trusted CAs */
  /*   if(!SSL_CTX_load_verify_locations(ctx, CERTFILE, NULL)) { */
  /*     SSL_CTX_free(ctx); */
  /*     openssl_error("Can't read CA list"); */
  /*     return 0; */
  /*   } */
  client_ctx = client;

  return 1;
}
     
int g2pvt_ssl_set_callback(G2SSL_CONNECTION_CALLBACK cb)
{
  cb_connect = cb;
  return 1;
}

int g2pvt_ssl_destroy()
{
  if(server_ctx)
    SSL_CTX_free(server_ctx);
  server_ctx = NULL;
  if(client_ctx)
    SSL_CTX_free(client_ctx);
  client_ctx = NULL;
  return 1;
}

int g2pvt_ssl_available(int server_p)
{
  return server_p ? (server_ctx != 0) : (client_ctx != 0);
}

G2SSL g2pvt_ssl_securify(int sock, int server_p)
{
  SSL *ssl;
  BIO *bio;

  if(!(server_p ? server_ctx : client_ctx))
    return NULL;

  bio = BIO_new_socket(sock, BIO_NOCLOSE);
  ssl = SSL_new(server_p ? server_ctx : client_ctx);
  SSL_set_bio(ssl, bio, bio);

  if(server_p)
    SSL_set_accept_state(ssl);
  else
    SSL_set_connect_state(ssl);
  return (G2SSL)ssl;
}

G2SSL g2pvt_ssl_accept(int sock)
{
  return g2pvt_ssl_securify(sock, TRUE);
}

G2SSL g2pvt_ssl_connect(int sock)
{
  return g2pvt_ssl_securify(sock, FALSE);
}

int g2pvt_ssl_close(G2SSL ssl)
{
  int shutdown_mode;
  if(ssl) {
    shutdown_mode = SSL_get_shutdown(ssl);
    if(shutdown_mode == 0 || shutdown_mode == SSL_RECEIVED_SHUTDOWN)
      SSL_shutdown(ssl);
    SSL_free(ssl);
  }
  return 0;
}

int g2pvt_ssl_check_cert(G2SSL ssl, char *host)
{
  X509 *x;
  char CN_peer[256];
  
  if(SSL_get_verify_result(ssl) != X509_V_OK) {
    openssl_error("Certificate doesn't verify");
    return 0;
  }

  if(host == NULL)
    return 1;

  x = SSL_get_peer_certificate(ssl);
  X509_NAME_get_text_by_NID(X509_get_subject_name(x), NID_commonName, CN_peer, sizeof(CN_peer));
  X509_free(x);

  PRINTF("host %s peer %s\n", host, CN_peer);

  if(strcasecmp(CN_peer, host)) {
    openssl_error("Common name doesn't match host name");
    return 0;
  }
  return 1;
}

/* Trigger code above us to do another read. */
static void note_more_data_to_read(G2SSL ssl)
{
  BIO *bio = SSL_get_rbio(ssl);
  int sock = bio ? BIO_get_fd(bio,NULL) : -1;
  if(sock != -1)
    g2pvt_enqueue_read_event(sock);
}

/* "Use SSL_pending() to see whether there are still data available inside */
/* the SSL and/or underlying BIO. Only try to select() on the read (write) event */
/* if the call to SSL_read()/SSL_get_error() returns the WANT_READ or WANT_WRITE */
/* condition." */

int g2pvt_ssl_read(G2SSL ssl, char *buf, int num)
{
  int rc, err;
  /*   PRINTF("  g2pvt_ssl_read buf=%08x num=%d)\n", buf, num); */

  do {
    rc = SSL_read(ssl, buf, num);
    
    err = SSL_get_error(ssl,rc);

    switch(err) {
     case SSL_ERROR_NONE:
       note_more_data_to_read(ssl);
       return rc;

     case SSL_ERROR_ZERO_RETURN:              /* SSL shutdown. */
       PRINTF("SSL_shutdown by peer.\n");
       SSL_shutdown(ssl);
       return 0;                              /* EOF */

     case SSL_ERROR_WANT_READ:
/*        PRINTF("  SSL_ERROR_WANT_READ buf=%08x num=%d\n", buf, num); */
       errno = EWOULDBLOCK;        /* Ineffective */
       return -1;
       
     case SSL_ERROR_WANT_WRITE:
       PRINTF("g2pvt_ssl_read: READ wants WRITE buf=%08x n=%d\n", buf, num);
       mssleep(50);                /* Waiting for a write_event */
     case SSL_ERROR_WANT_CONNECT:
     case SSL_ERROR_WANT_ACCEPT:
       break;

     case SSL_ERROR_SYSCALL:
/* This case gets triggered when the other end terminates abruptly.  It would be
   nice to have some better error case, as it also gets triggered by myserious
   cases I had during initial debugging.  Leaving this quiet for now.
       openssl_error("SSL read SSL_ERROR_SYSCALL, errno=%d",errno);
*/
       return -1;

     case SSL_ERROR_SSL:
       openssl_error("SSL read SSL_ERROR_SSL");
       return -1;

     case SSL_ERROR_WANT_X509_LOOKUP:
       openssl_error("SSL read SSL_ERROR_WANT_X509_LOOKUP");
       return -1;

     default:
       openssl_error("SSL read problem: rc = %d, errcode = %d",rc,err);
       return -1;
    }
  } while (1);
  /* return -1; */
}

int g2pvt_ssl_write(G2SSL ssl, char *buf, int num)
{
  int rc;
/*   PRINTF("  g2pvt_ssl_write buf=%08x num=%d)\n", buf, num); */
  do {
    rc = SSL_write(ssl, buf, num);
    
    switch(SSL_get_error(ssl,rc)) {
     case SSL_ERROR_NONE:
       return rc;

     case SSL_ERROR_WANT_WRITE:
/*        PRINTF("  SSL_ERROR_WANT_WRITE buf=%08x num=%d\n", buf, num); */
       errno = EWOULDBLOCK;        /* Ineffective */
       return -1;

     case SSL_ERROR_WANT_READ:
       PRINTF("  g2pvt_ssl_write: WRITE wants READ buf=%08x n=%d\n", buf, num);
       mssleep(50);                /* Waiting for a read_event */
     case SSL_ERROR_WANT_CONNECT:
     case SSL_ERROR_WANT_ACCEPT:
       break;

     case SSL_ERROR_SYSCALL:
       openssl_error("SSL_ERROR_SYSCALL in write");
       return -1;

     case SSL_ERROR_SSL:
     default:
       openssl_error("SSL_ERROR in write"); /* Eg, cert verify failed. */
       return -1;
    }
  } while(1);
  /* return -1; */
}

int g2pvt_ssl_print_session(G2SSL ssl)
{
  SSL_CIPHER *c;
  int nbits=0;
  char buf[512];

  c = SSL_get_current_cipher(ssl);

  SSL_CIPHER_get_bits(c,&nbits);
  sprintf(buf, "SSL: version %s, Cipher %s %d bits\n",
          SSL_CIPHER_get_version(c),
          SSL_CIPHER_get_name(c),
          nbits);
  g2ext_write_string_to_console(buf);
  return nbits;
}

long g2ext_ssl_print_server_stats()
{
  if(!server_ctx)
    return 0;

  printf("%4ld items in the session cache\n", SSL_CTX_sess_number(server_ctx));
  printf("%4d client connects (SSL_connect())\n", SSL_CTX_sess_connect(server_ctx));
  printf("%4d client renegotiates (SSL_connect())\n", SSL_CTX_sess_connect_renegotiate(server_ctx));
  printf("%4d client connects that finished\n", SSL_CTX_sess_connect_good(server_ctx));
  printf("%4d server accepts (SSL_accept())\n", SSL_CTX_sess_accept(server_ctx));
  printf("%4d server renegotiates (SSL_accept())\n", SSL_CTX_sess_accept_renegotiate(server_ctx));
  printf("%4d server accepts that finished\n", SSL_CTX_sess_accept_good(server_ctx));
  printf("%4d session cache hits\n",SSL_CTX_sess_hits(server_ctx));
  printf("%4d session cache misses\n",SSL_CTX_sess_misses(server_ctx));
  printf("%4d session cache timeouts\n",SSL_CTX_sess_timeouts(server_ctx));
  printf("%4d callback cache hits\n",SSL_CTX_sess_cb_hits(server_ctx));
  printf("%4d cache full overflows (%d allowed)\n",
         SSL_CTX_sess_cache_full(server_ctx), SSL_CTX_sess_get_cache_size(server_ctx));
  return 1;
}
