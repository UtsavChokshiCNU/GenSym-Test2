/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + File Name:   ssl.h
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):  Fred White
 +
 + Description: Generic SSL wrapper functions
 + 
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#ifdef HEADER_SSL_H
typedef SSL *G2SSL;
#else
typedef void *G2SSL;		/* External, opaque type. */
#endif

typedef void (*G2SSL_CONNECTION_CALLBACK)(G2SSL ssl, char *protocol, int nbits, char *cipher,
					  char *subject, char *issuer);

extern int g2pvt_ssl_initialize(char *certificate);

extern int g2pvt_ssl_set_callback(G2SSL_CONNECTION_CALLBACK cb);

extern int g2pvt_ssl_destroy(void);

extern G2SSL g2pvt_ssl_accept(int sock);

extern G2SSL g2pvt_ssl_connect(int sock);

extern int g2pvt_ssl_read(G2SSL ssl, char *buf, int num);

extern int g2pvt_ssl_write(G2SSL ssl, char *buf, int num);

extern int g2pvt_ssl_close(G2SSL ssl);

extern int g2pvt_ssl_available(int server_p);
