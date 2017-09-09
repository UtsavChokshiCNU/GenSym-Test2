/*-*- Mode: c++ -*- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      sspi.c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):   Fred White
 +
 + Description: SSPI/Schannel wrapper for G2
 + 
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

// TODO:
//  - Handle EWOULDBLOCKs during handshake
//  - Remove unneeded memory copies
//  - Use fewer buffers
//  - Merge client&server handshake functions into one

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h> 
#include <winsock.h>
#include <wincrypt.h>

#ifndef ALG_SID_AES 
#pragma message(__FILE__ " : Warning: Could not find Platform SDK header files needed for SSL.")
#include "sslnoop.c"		/* Just no-op SSL in this case. */
#else

#include <wintrust.h>
#include <schannel.h>

#define SECURITY_WIN32
#include <security.h>
#include <sspi.h>

/*
 * Debugging and Tracing
 */
#define T_OFF 1 ? (void)0 : g2pvt_trace
#define T_ON g2pvt_trace

#define Trace T_OFF
#define Warn T_OFF
#define PRINTF T_ON


/*
 * Local Structures
 */
typedef struct {
  int count;			      // Fill pointer
  int length;			      // Allocated length.
  PBYTE pBuf;
} Buffer;

typedef struct {
  BOOL is_server;
  LPSTR serverName;
  SOCKET socket;
  BOOL handshakeNeeded;		// TRUE if handshake pending
  BOOL readNeeded;
  CtxtHandle hContext;
  SecPkgContext_StreamSizes sizes;
  char *protocol;		// "TLS1", etc.
  int nbits;			// Cipher strength
  char *cipher;			// Cipher name
  char *subject;		// CN of cert
  char *issuer;			// CN of issuer (signer)
  Buffer ibuf;			// Application data to read.
  Buffer ebuf;			// Leftover encrypted data
  Buffer obuf;			// Application data to write
  Buffer tbuf;			// Leftover encrypted data transmit
} SSL;

#define HEADER_SSL_H
#include "ssl.h"

/*
 * External References
 */
extern void g2pvt_enqueue_read_event(int sock);
extern void g2pvt_enqueue_write_event(int sock);
extern long g2ext_write_string_to_console(char *str);
extern void g2pvt_trace(const char *fmt, ...);
extern void g2pvt_vtrace(int flags, const char *fmt, va_list args);

/*
 * Forward References
 */
static SECURITY_STATUS sspi_CreateCredentials(BOOL is_server, LPCSTR serverName, PCredHandle phCreds);
static SECURITY_STATUS sspi_Handshake(G2SSL ssl);
static SECURITY_STATUS sspi_ClientHandshake(SSL *ssl, BOOL fDoInitialRead);
static SECURITY_STATUS sspi_ServerHandshake(SSL *ssl);
static SECURITY_STATUS sspi_VerifyServer(SSL *ssl);
static SECURITY_STATUS sspi_Close(SSL *ssl);
static void sspi_GetCertInfo(SSL *ssl, PCCERT_CONTEXT  pServerCert);
static char *sspi_CipherName(int aiCipher);
static char *sspi_CertError(DWORD Status);
static char *sspi_SecError(DWORD Status);
static char *sspi_ProtocolName(DWORD protocol);
static char *sspi_WinsockError(DWORD Status);
static void sspi_handshake_done(G2SSL ssl);

/*
 * Globals
 */
static BOOL g_ssl_initialized = FALSE;
static HMODULE g_hDLL = NULL;
static SecurityFunctionTable g_sft;
static HCERTSTORE g_hMyCertStore = NULL;
static CredHandle g_ClientCreds = {0};
static CredHandle g_ServerCreds = {0};
static G2SSL_CONNECTION_CALLBACK cb_connect = NULL;

/*
 * Defines
 */

// Flags for all calls to InitializeSecurityContext and AcceptSecurityContext
#define ISC_FLAGS ISC_REQ_SEQUENCE_DETECT | ISC_REQ_REPLAY_DETECT | ISC_REQ_CONFIDENTIALITY | \
                  ISC_RET_EXTENDED_ERROR | ISC_REQ_ALLOCATE_MEMORY | ISC_REQ_STREAM

#define ASC_FLAGS ASC_REQ_SEQUENCE_DETECT | ASC_REQ_REPLAY_DETECT | ASC_REQ_CONFIDENTIALITY | \
		  ASC_REQ_EXTENDED_ERROR | ASC_REQ_ALLOCATE_MEMORY | ASC_REQ_STREAM

#define IsCredHandle(hc) ((hc.dwLower|hc.dwUpper) != 0)

#define IBUF(ssl) (ssl->ibuf.pBuf)
#define EBUF(ssl) (ssl->ebuf.pBuf)
#define OBUF(ssl) (ssl->obuf.pBuf)
#define TBUF(ssl) (ssl->tbuf.pBuf)

// Large enough to hold the largest SSL record.
#define IO_BUFFER_SIZE 17000

// How long to sleep when we need to block during handshake TODO: don't block.
#define sspi_sleep() Sleep(50)



/*
 * Utility Functions
 */

static void sspi_vprintf(const char *prefix, const char *fmt, va_list args)
{
  char buf[512];
  strcpy(buf,prefix);
  _vsnprintf(buf+strlen(buf), sizeof(buf)-strlen(buf)-1, fmt, args);
  buf[sizeof(buf)-1] = '\0';
  g2ext_write_string_to_console(buf);
}

static void sspi_error(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  sspi_vprintf("ERROR: ",fmt,args);
  va_end(args);
}

static void sspi_printf(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  sspi_vprintf("",fmt,args);
  va_end(args);
}

static char *sspi_dll_name()
{
  OSVERSIONINFO VerInfo;

  VerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
  if (!GetVersionEx (&VerInfo))
    return NULL;

  if (VerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT && VerInfo.dwMajorVersion == 4)
    return "Security.dll";	// NT4

  else if (VerInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS ||
	   VerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT )
    return "Secur32.dll";	// NT5

  else
    return NULL;
}

static void g2ssl_free(G2SSL ssl)
{
  if(ssl->subject) free(ssl->subject);
  if(ssl->issuer) free(ssl->issuer);
  if(IBUF(ssl)) free(IBUF(ssl));
  if(EBUF(ssl)) free(EBUF(ssl));
  if(OBUF(ssl)) free(OBUF(ssl));
  if(TBUF(ssl)) free(TBUF(ssl));
  free(ssl);
}

static BOOL sspi_alloc_buffer(Buffer *buffer, int len)
{
  if(buffer->length >= len)
    return TRUE;

  buffer->pBuf = realloc(buffer->pBuf, len);
  if(!buffer->pBuf) {
    sspi_error("**** Out of memory allocating %d bytes", len);
    return FALSE;
  }

  buffer->length = len;
  return TRUE;
}

static void sspi_MoreToRead(G2SSL ssl)
{
  g2pvt_enqueue_read_event(ssl->socket);
}

static void sspi_MoreToWrite(G2SSL ssl)
{
  g2pvt_enqueue_write_event(ssl->socket);
}

static int sspi_recv(SOCKET s, char *buf, int len, int flags)
{
  int rc;

  rc = recv(s, buf, len, flags);
  //  PRINTF("Recv %d/%d bytes%s\n", rc, len, (WSAGetLastError()==WSAEWOULDBLOCK) ? " BLOCKED" : "");
  return rc;
}

static int sspi_send(SOCKET s, const char *buf, int len, int flags)
{
  int rc;

  rc = send(s, buf, len, flags);
  //  PRINTF("Send %d/%d bytes%s\n", rc, len, (WSAGetLastError()==WSAEWOULDBLOCK) ? " BLOCKED" : "");
  return rc;
}


/*
 * Exported Functions
 */

/*
 * Load appropriate security DLL, populate function table, create credentials.
 */
BOOL g2pvt_ssl_initialize(char *certificate)
{
  INIT_SECURITY_INTERFACE pInit;
  PSecurityFunctionTable pSecurityFunc;
  char *libName;

  Trace("g2pvt_ssl_initialize cert:\"%s\"\n", certificate);

  if(g_ssl_initialized)
    return TRUE;

  libName = sspi_dll_name();
  if(!libName)
    return FALSE;

  g_hDLL = LoadLibrary(libName);
  if(g_hDLL == NULL) {
    sspi_error("Error 0x%x loading %s.\n", GetLastError(), libName);
    return FALSE;
  }

  pInit = (INIT_SECURITY_INTERFACE) GetProcAddress(g_hDLL,SECURITY_ENTRYPOINTA);
  
  if(pInit == NULL) {
    sspi_error("Error 0x%x reading InitSecurityInterface entry point.\n", GetLastError());
    return FALSE;
  }

  pSecurityFunc = pInit();

  if(pSecurityFunc == NULL) {
    sspi_error("Error 0x%x reading security interface.\n", GetLastError());
    return FALSE;
  }

  CopyMemory(&g_sft, pSecurityFunc, sizeof(g_sft));

  /* Create credentials. For a client, this is just some info about SSL versions
   * and supported algorithms. For the server, however, this must locate and
   * load a certificate, including a private key. */
  if (certificate && strlen(certificate) > 0)
    if(sspi_CreateCredentials(TRUE, certificate, &g_ServerCreds) != SEC_E_OK)
      return FALSE;

  if(sspi_CreateCredentials(FALSE, certificate, &g_ClientCreds) != SEC_E_OK)
    return FALSE;

  g_ssl_initialized = TRUE;
  return TRUE;
}

/*
 * Set callback for client handshake complete.
 */
int g2pvt_ssl_set_callback(G2SSL_CONNECTION_CALLBACK cb)
{
  cb_connect = cb;
  return 1;
}

/*
 * Unload SSL libraries.
 */
int g2pvt_ssl_destroy(void)
{
  if(IsCredHandle(g_ServerCreds))
    g_sft.FreeCredentialHandle(&g_ServerCreds);
  ZeroMemory(&g_ServerCreds,sizeof(g_ServerCreds));

  if(IsCredHandle(g_ClientCreds))
    g_sft.FreeCredentialHandle(&g_ClientCreds);
  ZeroMemory(&g_ClientCreds,sizeof(g_ClientCreds));

  if(g_hMyCertStore)
    CertCloseStore(g_hMyCertStore, 0);
  g_hMyCertStore = NULL;

  ZeroMemory(&g_sft,sizeof(g_sft));

  if(g_hDLL)
    FreeLibrary(g_hDLL);
  g_hDLL = NULL;

  g_ssl_initialized = FALSE;
  return 0;
}


int g2pvt_ssl_available(int server_p)
{
  return server_p ? IsCredHandle(g_ServerCreds) : IsCredHandle(g_ClientCreds);
}

/*
 * Create SSL wrapper for given socket.
 */
G2SSL g2pvt_ssl_securify(int sock, int is_server)
{
  SSL *ssl;

  ssl = (SSL *) calloc(1,sizeof(SSL));
  ssl->is_server = is_server;
  ssl->socket = sock;
  ssl->handshakeNeeded = TRUE;
  // TODO: serverName?

  sspi_alloc_buffer(&ssl->ibuf, IO_BUFFER_SIZE);
  sspi_alloc_buffer(&ssl->ebuf, IO_BUFFER_SIZE);
  sspi_alloc_buffer(&ssl->obuf, IO_BUFFER_SIZE);
  sspi_alloc_buffer(&ssl->tbuf, IO_BUFFER_SIZE);

  return ssl;
}

/*
 * Securify connection as a server.
 */
G2SSL g2pvt_ssl_accept(int sock)
{
  Trace("g2pvt_ssl_accept(%d)\n", sock);
  return g2pvt_ssl_securify(sock,TRUE);
}

/*
 * Securify connection as a client.
 */
G2SSL g2pvt_ssl_connect(int sock)
{
  Trace("g2pvt_ssl_connect(%d)\n", sock);
  return g2pvt_ssl_securify(sock,FALSE);
}

/*
 * Orderly SSL shutdown.
 */
int g2pvt_ssl_close(G2SSL ssl)
{
  Trace("g2pvt_ssl_close(%08x)\n", ssl);

  if(!ssl) return 0;
  
  sspi_Close(ssl);		// Send CLOSE_NOTIFY
  g_sft.DeleteSecurityContext(&ssl->hContext);

  g2ssl_free(ssl);
  return 1;
}

/*
 * Attempt to read and decrypt bytes.
 */
int g2pvt_ssl_read(G2SSL ssl, char *buf, int num)
{
  SecBufferDesc   Message;
  SecBuffer       Buffers[4];
  SecBuffer *     pDataBuffer;
  SecBuffer *     pExtraBuffer;
  Buffer *        ibuf = &ssl->ibuf;
  Buffer *        ebuf = &ssl->ebuf;
  SECURITY_STATUS Status;
  DWORD rc, nRet;
  int i;

  if(ssl->handshakeNeeded && (sspi_Handshake(ssl) != SEC_E_OK)) {
    WSASetLastError(WSAEPFNOSUPPORT); // Anything fatal will do.
    return -1;
  }

  //
  // Satisfy request from ibuf, if possible.
  //
  if(ibuf->count > 0) {
    nRet = min(num, ibuf->count);
    CopyMemory(buf, ibuf->pBuf, nRet);
    ibuf->count -= nRet;

    if(ibuf->count > 0)				  // Keep buffer left-justified. FIXME
      MoveMemory(ibuf->pBuf, ibuf->pBuf + nRet, ibuf->count);

    WSASetLastError(0);
    sspi_MoreToRead(ssl);
    return nRet;
  }

  //
  // Read from network into ebuf, if necessary.
  //
  if(ebuf->count == 0 || ssl->readNeeded) {
    rc = sspi_recv(ssl->socket, ebuf->pBuf + ebuf->count, ebuf->length - ebuf->count, 0);
    if(rc == SOCKET_ERROR || rc == 0) {
      ssl->readNeeded = TRUE;
      return -1;		// WSAEWOULDBLOCK or fatal error.
    }
    else {
      ebuf->count += rc;
    }
  } else {
    // Only if we didn't read from the network, do we need a synthetic read event.
    sspi_MoreToRead(ssl);
  }

  ssl->readNeeded = TRUE;

  // 
  // Decrypt the received data in ebuf.
  //
  Buffers[0].pvBuffer     = ebuf->pBuf;
  Buffers[0].cbBuffer     = ebuf->count;
  Buffers[0].BufferType   = SECBUFFER_DATA;

  Buffers[1].BufferType   = SECBUFFER_EMPTY;
  Buffers[2].BufferType   = SECBUFFER_EMPTY;
  Buffers[3].BufferType   = SECBUFFER_EMPTY;

  Message.ulVersion       = SECBUFFER_VERSION;
  Message.cBuffers        = 4;
  Message.pBuffers        = Buffers;

  Status = g_sft.DecryptMessage(&ssl->hContext, &Message, 0, NULL);

  switch(Status) {
   case SEC_E_OK:
     //
     // Locate decrypted data and leftover encrypted data, if any.
     //
     pDataBuffer  = NULL;
     pExtraBuffer = NULL;
     for(i = 1; i < 4; i++) {
       if(pDataBuffer == NULL && Buffers[i].BufferType == SECBUFFER_DATA)
	 pDataBuffer = &Buffers[i];
       if(pExtraBuffer == NULL && Buffers[i].BufferType == SECBUFFER_EXTRA)
	 pExtraBuffer = &Buffers[i];
     }

     //
     // Copy decrypted bytes into user buffer.
     //
     nRet = 0;
     if(pDataBuffer && pDataBuffer->cbBuffer>0) {
       nRet = min(num, (int)pDataBuffer->cbBuffer);
       CopyMemory(buf, pDataBuffer->pvBuffer, nRet);

       //
       // Save leftover decrypted bytes in ibuf.
       //
       if(nRet < pDataBuffer->cbBuffer) {
	 ibuf->count = pDataBuffer->cbBuffer - nRet;

	 if(ibuf->count > ibuf->length)
	   sspi_error("Out of buffer space in g2pvt_ssl_read!! %d %d\n", ibuf->count, ibuf->length);

	 CopyMemory(ibuf->pBuf, ((PBYTE)pDataBuffer->pvBuffer) + nRet, ibuf->count);
       }
     }

     //
     // Save leftover encrypted bytes in ebuf.
     //
     ebuf->count = 0;
     if(pExtraBuffer && pExtraBuffer->cbBuffer>0) {
       ebuf->count = pExtraBuffer->cbBuffer;
       MoveMemory(ebuf->pBuf, pExtraBuffer->pvBuffer, pExtraBuffer->cbBuffer);
       ssl->readNeeded = FALSE;
     }

     if(ebuf->count)
       sspi_MoreToRead(ssl);

     if(nRet == 0) {
       WSASetLastError(WSAEWOULDBLOCK);
       return -1;
     } else {
       WSASetLastError(0);
       return nRet;
     }
     break;

   case SEC_E_INCOMPLETE_MESSAGE:
     Warn("  SEC_E_INCOMPLETE_MESSAGE ibuf:%d ebuf:%d\n", ibuf->count, ebuf->count);
     sspi_MoreToRead(ssl);
     WSASetLastError(WSAEWOULDBLOCK);
     return -1;

   case SEC_I_CONTEXT_EXPIRED:
     Warn("g2pvt_ssl_read: SEC_I_CONTEXT_EXPIRED ibuf:%d ebuf:%d\n", ibuf->count, ebuf->count);
     WSASetLastError(WSAEPFNOSUPPORT); // Anything fatal
     return 0;			       // FIXME: EOF, but need to do some SSL stuff.

   case SEC_I_RENEGOTIATE:
     Warn("g2pvt_ssl_read: SEC_I_RENEGOTIATE ibuf:%d ebuf:%d\n", ibuf->count, ebuf->count);
     ssl->handshakeNeeded = TRUE;      // FIXME
     WSASetLastError(WSAEWOULDBLOCK);
     return -1;
     
   default:
     sspi_error("**** DecryptMessage failed 0x%x %s\n", Status, sspi_SecError(Status));
     WSASetLastError(WSAEPFNOSUPPORT); // Anything fatal
     return -1;
  }
}

/*
 * Attempt to encrypt and send bytes.
 */
int g2pvt_ssl_write(G2SSL ssl, char *buf, int num)
{
  SECURITY_STATUS Status;
  SecBufferDesc   Message;
  SecBuffer       Buffers[4];
  PBYTE pbMessage;
  DWORD cbMessage;
  int rc, len;
  Buffer *obuf = &ssl->obuf;
  Buffer *tbuf = &ssl->tbuf;

  // NOTE: Probably this belongs after the tbuf handling. Doesn't matter for now.
  if(ssl->handshakeNeeded && (sspi_Handshake(ssl) != SEC_E_OK)) {
    WSASetLastError(WSAEPFNOSUPPORT);
    return -1;
  }

  //
  // Write from buffered encrypted data, if any.
  //
  if(tbuf->count > 0) {
    rc = sspi_send(ssl->socket, tbuf->pBuf, tbuf->count, 0);
    if(rc == SOCKET_ERROR || rc == 0)
      return rc;
    tbuf->count -= rc;
    if(tbuf->count > 0) {
      Warn("**** Partial write %d of %d\n", rc,  tbuf->count);
      MoveMemory(tbuf->pBuf, tbuf->pBuf + rc, tbuf->count); // TODO: Avoid this copy.
    }
    sspi_MoreToWrite(ssl);
    WSASetLastError(WSAEWOULDBLOCK);
    return SOCKET_ERROR;
  }

  // Build up the header+data+trailer packet
  pbMessage = obuf->pBuf + ssl->sizes.cbHeader;
  //  ASSERT(ssl->obuf.count == 0);
  cbMessage = min(num, obuf->length); // obuf will always be empty here.
  CopyMemory(pbMessage, buf, cbMessage);

  //
  // Encrypt the bytes.
  //
  Buffers[0].pvBuffer     = obuf->pBuf;
  Buffers[0].cbBuffer     = ssl->sizes.cbHeader;
  Buffers[0].BufferType   = SECBUFFER_STREAM_HEADER;

  Buffers[1].pvBuffer     = pbMessage;
  Buffers[1].cbBuffer     = cbMessage;
  Buffers[1].BufferType   = SECBUFFER_DATA;

  Buffers[2].pvBuffer     = pbMessage + cbMessage;
  Buffers[2].cbBuffer     = ssl->sizes.cbTrailer;
  Buffers[2].BufferType   = SECBUFFER_STREAM_TRAILER;

  Buffers[3].pvBuffer     = NULL;
  Buffers[3].cbBuffer     = 0;
  Buffers[3].BufferType   = SECBUFFER_EMPTY;

  Message.ulVersion       = SECBUFFER_VERSION;
  Message.cBuffers        = 4;
  Message.pBuffers        = Buffers;

  Status = g_sft.EncryptMessage(&ssl->hContext, 0, &Message, 0);

  if(FAILED(Status)) {
    sspi_error("**** EncryptMessage failed: %lx %s\n", Status, sspi_SecError(Status));
    WSASetLastError(WSAEPFNOSUPPORT);
    return -1;
  }

  // 
  // Send the encrypted data.
  //
  len = Buffers[0].cbBuffer + Buffers[1].cbBuffer + Buffers[2].cbBuffer;
  rc = sspi_send(ssl->socket, Buffers[0].pvBuffer, len, 0);

  if((rc == SOCKET_ERROR && (WSAGetLastError() == WSAEWOULDBLOCK)) ||
     (rc > 0) && (rc < len)) {
    tbuf->count = (rc==SOCKET_ERROR) ? len : len - rc;
    CopyMemory(tbuf->pBuf, Buffers[0].pvBuffer, tbuf->count); // TODO: Avoid this copy
    return cbMessage;
  }

  if(rc == SOCKET_ERROR || rc==0)
    return rc;

  if((int)cbMessage < num)
    sspi_error("Warning: Partial Write %d of %d due to buffer size (not fatal)\n", cbMessage, num);
  WSASetLastError(0);
  return cbMessage;
}



/*
 * SSPI Helper Functions
 */


//Function to free allocated memory
void freeAllocatedMemory( char *cont, char *csp, PCRYPT_KEY_PROV_INFO key)
{
	free(cont);
	free(csp);
	free(key);
}

static SECURITY_STATUS sspi_CreateCredentials(BOOL is_server, LPCSTR certName, PCredHandle phCreds)
{
  ALG_ID          keyExchangeAlgorithm = CALG_RSA_KEYX;
  TimeStamp       tsExpiry;
  SCHANNEL_CRED   SchannelCred;
  PCCERT_CONTEXT  pCertContext = NULL;
  DWORD dwFlags;
  SECURITY_STATUS Status;

  DWORD size = 0;
  PCRYPT_KEY_PROV_INFO key_info = NULL;
  HCRYPTPROV hCryptProv = 0;
  HCRYPTKEY hCertPubKey = 0; 
  DWORD sizeOfKey = 0;
  DWORD lenOfSizeOfKey = sizeof(DWORD);
  char *pszContainerName = NULL;
  char *pszProvName = NULL;
  size_t contBufLen = 0;
  size_t provBufLen = 0;
  size_t count = 0;

  Trace("sspi_CreateCredentials is_server=%d certName=\"%s\"\n", is_server, certName);

  // Open the "MY" certificate store if we are a server.
  // TODO: Want to read cert from file, but file needs to have private key.
  if(is_server) {
    if(g_hMyCertStore == NULL)
      g_hMyCertStore = CertOpenStore(CERT_STORE_PROV_SYSTEM,
				     X509_ASN_ENCODING,
				     0,
				     CERT_SYSTEM_STORE_LOCAL_MACHINE,
				     L"MY");
    if(!g_hMyCertStore) {
      sspi_error("CertOpenStore");
      return SEC_E_NO_CREDENTIALS;
    }
    Warn("CertOpenStore succeeded! %08x\n", g_hMyCertStore);

    // Find certificate. Note that this sample just searches for a certificate
    // that contains the server name somewhere in the subject name.  A real
    // application should be a bit less casual.
    // TODO: Use CERT_FIND_SUBJECT_CERT
    pCertContext = CertFindCertificateInStore(g_hMyCertStore, 
					      X509_ASN_ENCODING, 
					      0,
					      CERT_FIND_SUBJECT_STR_A,
					      certName,
					      NULL);
    if(pCertContext == NULL) {
      sspi_error("No server certificate found for \"%s\".", certName?certName:"");
      return SEC_E_NO_CREDENTIALS;
    }
    sspi_printf("Server certificate \"%s\" loaded successfully.\n", certName?certName:"");

	//Function retrieves the information contained in an extended property of a certificate context.
	 //First 'll get the buffer for key_info size into size variable   
    if(!CertGetCertificateContextProperty(
                                  pCertContext,
                                  CERT_KEY_PROV_INFO_PROP_ID ,
                                  NULL,
                                  &size
                                  ))
	{
		sspi_error("Can't get buffer size for certificate context property\n");
		return SEC_E_NO_CREDENTIALS;
	}
	sspi_printf("Buffer size for certificate context property received successfully\n");
    
	key_info = (PCRYPT_KEY_PROV_INFO) malloc(size);  	 
    
	if(!CertGetCertificateContextProperty(
                                  pCertContext,
                                  CERT_KEY_PROV_INFO_PROP_ID ,
                                  key_info,
                                  &size
                                  ))
	{
		sspi_error("Can't get certificate context property\n");
		free(key_info);
		return SEC_E_NO_CREDENTIALS;
    }
	sspi_printf("Certificate context property received successfully\n");

    //function is used to acquire a handle to a particular key container within a particular cryptographic service provider (CSP). 
	//This returned handle is used in calls to CryptoAPI functions that use the selected CSP.
	if (!CryptAcquireContext(
                     	&hCryptProv, 
	                    key_info->pwszContainerName, 
                        key_info->pwszProvName,  
	   	                key_info->dwProvType,                         
	                    0))
	{
		sspi_error("A cryptographic service handle could not be acquired.\n");
		//-------------------------------------------------------------------
        // If an error "0x80090019L - The requested provider does not exist"
		// the provider name of the CSP is converted to Unicode characters by 
		//using the MultiByteToWideChar function that is present in the 
		//kernel32.dll. The extended characters in the provider name may 
		//be lost during this conversion, and the provider name is converted 
		//incorrectly, there4 'll convert it back to multibyte characters.
		//If it fails can try Regsvr32.exe on CSP DLLs 
		//(Rsabase.dll or Rsaenh.dll) it may fix the problem.
		if (GetLastError() == NTE_KEYSET_NOT_DEF)
		{
			contBufLen = wcslen(key_info->pwszContainerName);
			provBufLen = wcslen(key_info->pwszProvName);
			pszContainerName = (char *)malloc(contBufLen + 1); 
			pszProvName = (char *)malloc(provBufLen + 1); 
			if(wcstombs(pszContainerName, key_info->pwszContainerName, contBufLen) == -1)
			{
				sspi_error("Can't convert key container name to multibyte chanracters\n");
				freeAllocatedMemory(pszContainerName, pszProvName, key_info); 
			    return SEC_E_NO_CREDENTIALS;
			}
			if(wcstombs(pszProvName, key_info->pwszProvName, provBufLen) == -1)
			{
				sspi_error("Can't convert key CSP name to multibyte chanracters\n");
				freeAllocatedMemory(pszContainerName, pszProvName, key_info); 
			    return SEC_E_NO_CREDENTIALS;
			}
			pszContainerName[contBufLen] = '\0';
			pszProvName[provBufLen] = '\0';
			if (!CryptAcquireContext(
                     	 &hCryptProv, 
	                     pszContainerName, 
                         pszProvName,  
	   					 key_info->dwProvType,                         
	                     0))
			{
				sspi_error("A cryptographic service handle could not be acquired. ");
				sspi_error("after conversion of key containter name and CSP into multibyte characters.\n");
      
	  //-------------------------------------------------------------------
      // If an error occurred in acquiring the context. This could mean  
      // that the key container requested does not exist. In this case,
      // the function can be called again to attempt to create a new key 
      // container. Error codes are defined in Winerror.h.
				if (GetLastError() == NTE_BAD_KEYSET)
				{
					if(!CryptAcquireContext(
                              &hCryptProv, 
	                          pszContainerName, 
                              pszProvName, 
	                          key_info->dwProvType, 
                              CRYPT_NEWKEYSET)) 
					{
						sspi_error("Could not create a new key container.\n");
						freeAllocatedMemory(pszContainerName, pszProvName, key_info); 
						return SEC_E_NO_CREDENTIALS;
					}
				sspi_printf("A new key container has been created sucessfully.\n");			
				}
			}
		}
    }
    sspi_printf("A cryptographic service handle has been created sucessfully.\n");
    freeAllocatedMemory(pszContainerName, pszProvName, key_info);     
  
	// function converts and imports the public key information into the provider and returns a handle of the public key. 
	if(!CryptImportPublicKeyInfo(
                    	 hCryptProv, 
                         X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, 
                         &pCertContext->pCertInfo->SubjectPublicKeyInfo, 
                         &hCertPubKey))
    {
		sspi_error("A handle of the public key could not be acquired.\n");
		 return SEC_E_NO_CREDENTIALS;
    }
	sspi_printf("A handle of the public key has been acquired. \n");

	//function retrieves data that governs the operations of a key.
	//Since KP_KEYLEN used the received data is the actual length of the key in bits.
	if(!CryptGetKeyParam(
						  hCertPubKey, 
						  KP_KEYLEN,
						  (BYTE*)(&sizeOfKey), 
						  &lenOfSizeOfKey,
						  0)) 	
    {
		sspi_error("The key lenghts could not be acquired.\n");
		return SEC_E_NO_CREDENTIALS;
    }
	sspi_printf("The key lenghts = %d bits has been acquired. \n", sizeOfKey);

    //The key lenghts should be restricted with 512 bits 
	if( sizeOfKey  > 512 ) 
	{
		sspi_error("The key lenghts = %d bits is not acceptable.\n", sizeOfKey);
		return SEC_E_NO_CREDENTIALS;
   	}		               

	//Function releases the handle of a cryptographic service provider (CSP) and a key container
	if (!CryptReleaseContext(hCryptProv, 0))
	{
		sspi_error("The handle of a CSP could not be released.\n");
		return SEC_E_NO_CREDENTIALS;
	}
	sspi_printf("he handle of a CSP successfully released.\n");

  }//end of if(is_server)

  // AUTHENTICATING THE SERVER
  // In Windows XP and Windows 2000, the default behavior of Schannel is to use the
  // WinVerifyTrust function to verify the integrity and ownership of the server
  // certificate. To disable this feature, specify ISC_REQ_MANUAL_CRED_VALIDATION
  // when calling the InitializeSecurityContext function. For more information, see
  // Manually Validating Schannel Credentials. On the Windows NT 4.0 and Windows Me
  // platforms, the server certificate is not automatically validated.

  ZeroMemory(&SchannelCred, sizeof(SchannelCred));
  SchannelCred.dwVersion = SCHANNEL_CRED_VERSION;
  if(is_server) {
    dwFlags = SECPKG_CRED_INBOUND;
    SchannelCred.grbitEnabledProtocols = SP_PROT_SSL3_SERVER | SP_PROT_SSL2_SERVER | SP_PROT_TLS1_SERVER;
    SchannelCred.cCreds = 1;
    SchannelCred.paCred = &pCertContext;
	SchannelCred.dwMaximumCipherStrength = 56;
  } else {
    dwFlags = SECPKG_CRED_OUTBOUND;
    SchannelCred.grbitEnabledProtocols = SP_PROT_TLS1_CLIENT | SP_PROT_SSL3_CLIENT;
    SchannelCred.cSupportedAlgs = 1;
    SchannelCred.palgSupportedAlgs = &keyExchangeAlgorithm;
    SchannelCred.dwFlags = SCH_CRED_NO_DEFAULT_CREDS | SCH_CRED_MANUAL_CRED_VALIDATION;
  }

  Status = g_sft.AcquireCredentialsHandleA(NULL,                   // Name of principal    
					   UNISP_NAME_A,           // Name of package (schannel)
					   dwFlags,                // Flags indicating use
					   NULL,                   // Pointer to logon ID
					   &SchannelCred,          // Package specific data
					   NULL,                   // Pointer to GetKey() func
					   NULL,                   // Value to pass to GetKey()
					   phCreds,                // (out) Cred Handle
					   &tsExpiry);             // (out) Lifetime (optional)
  if(Status != SEC_E_OK) {
    sspi_error("**** Error 0x%x returned by AcquireCredentialsHandle\n", Status);
    return Status;
  }

  //
  // Free the certificate context. Schannel has already made its own copy.
  //
  if(pCertContext)
    CertFreeCertificateContext(pCertContext);

  return SEC_E_OK;
}

static void sspi_client_handshake_done(G2SSL ssl)
{
  SECURITY_STATUS Status;
  SecPkgContext_ConnectionInfo info;

  Status = g_sft.QueryContextAttributes(&ssl->hContext, SECPKG_ATTR_CONNECTION_INFO, (PVOID)&info);
  if(Status != SEC_E_OK) {
    sspi_error("Error 0x%x querying connection info: %s\n", Status, sspi_SecError(Status));
    return;
  }
  ssl->protocol = sspi_ProtocolName(info.dwProtocol);
  ssl->nbits = info.dwCipherStrength;
  ssl->cipher = sspi_CipherName(info.aiCipher);

  if(cb_connect)
    (*cb_connect) (ssl, ssl->protocol, ssl->nbits, ssl->cipher, ssl->subject, ssl->issuer);
}

static SECURITY_STATUS sspi_Handshake(G2SSL ssl)
{
  SECURITY_STATUS Status;

  Trace("sspi_Handshake\n");

  if(!ssl->handshakeNeeded)
    return SEC_E_OK;

  if(ssl->is_server) {
    Status = sspi_ServerHandshake(ssl);

  } else {
    Status = sspi_ClientHandshake(ssl, TRUE);
    if(Status == SEC_E_OK)
      Status = sspi_VerifyServer(ssl);
  }

  if(Status != SEC_E_OK)
    return Status;

  ssl->handshakeNeeded = FALSE;

  if(!ssl->is_server)
    sspi_client_handshake_done(ssl);

  //
  // Read header/trailer/message sizes. I think these are actually fixed for SSL.
  //
  Status = g_sft.QueryContextAttributes(&ssl->hContext, SECPKG_ATTR_STREAM_SIZES, &ssl->sizes);
  if(Status != SEC_E_OK) {
    sspi_error("Error reading SECPKG_ATTR_STREAM_SIZES\n");
    return Status;
  }

  return Status;
}

static SECURITY_STATUS sspi_SendClientHello(SSL *ssl)
{
  SecBufferDesc   OutBuffer;
  SecBuffer       OutBuffers[1];
  DWORD           dwSSPIOutFlags;
  TimeStamp       tsExpiry;
  SECURITY_STATUS Status;
  int rc;

  Trace("sspi_SendClientHello\n");

  //
  //  Create the ClientHello message as an opaque SSPI "security token"
  //
  OutBuffers[0].pvBuffer   = NULL;    // Buffer alloced by SSPI (since ISC_REQ_ALLOCATE_MEMORY)
  OutBuffers[0].BufferType = SECBUFFER_TOKEN;
  OutBuffers[0].cbBuffer   = 0;

  OutBuffer.cBuffers = 1;
  OutBuffer.pBuffers = OutBuffers;
  OutBuffer.ulVersion = SECBUFFER_VERSION;

  Status = g_sft.InitializeSecurityContextA(&g_ClientCreds,          // handle to the credentials
					    NULL,               // handle of partially formed context
					    ssl->serverName,	// name of the target of the context
					    ISC_FLAGS,		// required context attributes
					    0,			// reserved; must be zero
					    SECURITY_NATIVE_DREP,// data representation on the target
					    NULL,		// pointer to the input buffers
					    0,			// reserved; must be zero
					    &ssl->hContext,	// receives the new context handle
					    &OutBuffer,		// pointer to the output buffers
					    &dwSSPIOutFlags,	// receives context attributes
					    &tsExpiry);		// receives life span of the security context
  if(Status != SEC_I_CONTINUE_NEEDED) {
    sspi_error("**** Error %d returned by InitializeSecurityContext (1)\n", Status);
    return Status;
  }

  // Send constructed CLIENTHELLO msg to server.
  if(OutBuffers[0].cbBuffer != 0 && OutBuffers[0].pvBuffer != NULL) {
    rc = sspi_send(ssl->socket, OutBuffers[0].pvBuffer, OutBuffers[0].cbBuffer, 0);

    if(rc == SOCKET_ERROR || rc == 0) {
      Status = SEC_E_INTERNAL_ERROR;
      Warn("FAILED! Client hello not sent.\n");
    } else {
      Status = SEC_E_OK;
      Warn("Client hello sent!\n");
    }
    g_sft.FreeContextBuffer(OutBuffers[0].pvBuffer);		// Free output buffer.
    OutBuffers[0].pvBuffer = NULL;
  }

  return Status;
}

static SECURITY_STATUS sspi_ClientHandshake(SSL *ssl, BOOL fDoInitialRead)
{
  SecBufferDesc   InBuffer;
  SecBuffer       InBuffers[2];
  SecBufferDesc   OutBuffer;
  SecBuffer       OutBuffers[1];
  DWORD           dwSSPIOutFlags;
  TimeStamp       tsExpiry;
  SECURITY_STATUS Status;
  int rc;
  BOOL            fDoRead;
  Buffer *        ebuf = &ssl->ebuf;

  Trace("sspi_ClientHandshake\n");

  /* say hello */
  if(fDoInitialRead)
    if((Status=sspi_SendClientHello(ssl)) != SEC_E_OK)
      return Status;

  ebuf->count = 0;
  fDoRead = fDoInitialRead;
  Status = SEC_I_CONTINUE_NEEDED;

  // 
  // Loop until the handshake is finished or an error occurs.
  //
  while(Status == SEC_I_CONTINUE_NEEDED        ||
	Status == SEC_E_INCOMPLETE_MESSAGE     ||
	Status == SEC_I_INCOMPLETE_CREDENTIALS) {
    //
    // Read data from server if necessary.
    //
    if(0 == ebuf->count || Status == SEC_E_INCOMPLETE_MESSAGE) {
      if(fDoRead) {
	//
	// Duplicated code here
	//
	rc = sspi_recv(ssl->socket, ebuf->pBuf + ebuf->count, ebuf->length - ebuf->count, 0);
	if(rc == SOCKET_ERROR && WSAGetLastError() == WSAEWOULDBLOCK)
	  sspi_sleep();						// FIXME: Don't sleep !!
	else if(rc == SOCKET_ERROR || rc == 0)
	  return SEC_E_INTERNAL_ERROR;
	else
	  ebuf->count += rc;
      }
      fDoRead = TRUE;
    }

    if(ebuf->count > 0) {
      //
      // Set up the input buffers. Buffer 0 is used to pass in data
      // received from the server. Schannel will consume some or all
      // of this. Leftover data (if any) will be placed in buffer 1 and
      // given a buffer type of SECBUFFER_EXTRA.
      //
      InBuffers[0].pvBuffer   = ebuf->pBuf;
      InBuffers[0].cbBuffer   = ebuf->count;
      InBuffers[0].BufferType = SECBUFFER_TOKEN;

      InBuffers[1].pvBuffer   = NULL;
      InBuffers[1].cbBuffer   = 0;
      InBuffers[1].BufferType = SECBUFFER_EMPTY;

      InBuffer.cBuffers       = 2;
      InBuffer.pBuffers       = InBuffers;
      InBuffer.ulVersion      = SECBUFFER_VERSION;

      //
      // Set up the output buffers. These are initialized to NULL
      // so as to make it less likely we'll attempt to free random
      // garbage later.
      //
      OutBuffers[0].pvBuffer  = NULL;
      OutBuffers[0].BufferType= SECBUFFER_TOKEN;
      OutBuffers[0].cbBuffer  = 0;

      OutBuffer.cBuffers      = 1;
      OutBuffer.pBuffers      = OutBuffers;
      OutBuffer.ulVersion     = SECBUFFER_VERSION;

      Status = g_sft.InitializeSecurityContextA(&g_ClientCreds,
						&ssl->hContext,
						NULL,
						ISC_FLAGS,
						0,
						SECURITY_NATIVE_DREP,
						&InBuffer,
						0,
						NULL,
						&OutBuffer,
						&dwSSPIOutFlags,
						&tsExpiry);
    } else {
      Status = SEC_E_INCOMPLETE_MESSAGE;
      OutBuffers[0].cbBuffer  = 0;
      sspi_sleep();						// FIXME!!!
    }

    //
    // Send generated security token, if any.
    //
    if(OutBuffers[0].cbBuffer > 0 && OutBuffers[0].pvBuffer != NULL) {
      rc = sspi_send(ssl->socket, OutBuffers[0].pvBuffer, OutBuffers[0].cbBuffer, 0);
      if(rc == SOCKET_ERROR || rc == 0) {
	g_sft.FreeContextBuffer(OutBuffers[0].pvBuffer);
	return SEC_E_INTERNAL_ERROR;		  // FIXME: Not letting send block.
      }
      g_sft.FreeContextBuffer(OutBuffers[0].pvBuffer);
      OutBuffers[0].pvBuffer = NULL;
    }

    //
    // Copy any leftover encrypted data
    //
    if(Status == SEC_E_OK) {
      if(InBuffers[1].BufferType == SECBUFFER_EXTRA) {
	int cbBuffer = ebuf->count;
	ebuf->count = InBuffers[1].cbBuffer;
	MoveMemory(ebuf->pBuf, ebuf->pBuf + cbBuffer - ebuf->count, ebuf->count);
	Warn(" Client handshake: %d bytes left over\n", ebuf->count);
      } else {
	ebuf->count = 0;
      }
    } else
      ebuf->count = 0;

    switch(Status) {
     case SEC_E_OK:
       Warn("Client Handshake was successful!!\n");
       return Status;

       //
       // If InitializeSecurityContext returned SEC_E_INCOMPLETE_MESSAGE,
       // then we need to read more data from the server and try again.
       //
     case SEC_E_INCOMPLETE_MESSAGE:
       continue;

     case SEC_I_CONTINUE_NEEDED:
       continue;

       //
       // If InitializeSecurityContext returned SEC_I_INCOMPLETE_CREDENTIALS,
       // then the server just requested client authentication. 
       //
     case SEC_I_INCOMPLETE_CREDENTIALS:
       return Status;

     default:
       sspi_error("**** Error 0x%x returned by InitializeSecurityContext\n", Status);
       return Status;
    }
  }
  return Status;
}

static SECURITY_STATUS sspi_ServerHandshake(SSL *ssl)
{
  TimeStamp            tsExpiry;
  SECURITY_STATUS      Status;
  SecBufferDesc        InBuffer;
  SecBufferDesc        OutBuffer;
  SecBuffer            InBuffers[2];
  SecBuffer            OutBuffers[1];
  int rc;
  BOOL                 fInitContext;
  DWORD                dwSSPIOutFlags;
  Buffer *ebuf = &ssl->ebuf;

  Trace("sspi_ServerHandshake\n");

  Status = SEC_I_CONTINUE_NEEDED;
  fInitContext = TRUE;
  rc = 0;

  ebuf->count = 0;
  while(Status == SEC_I_CONTINUE_NEEDED ||
	Status == SEC_E_INCOMPLETE_MESSAGE ||
	Status == SEC_I_INCOMPLETE_CREDENTIALS) {

    if(ebuf->count == 0 || Status == SEC_E_INCOMPLETE_MESSAGE) {
      //
      // Duplicated code here
      //
      rc = sspi_recv(ssl->socket, ebuf->pBuf + ebuf->count, ebuf->length - ebuf->count, 0);
      if(rc == SOCKET_ERROR && WSAGetLastError() == WSAEWOULDBLOCK)
	sspi_sleep();						// FIXME: Don't sleep !!
      else if(rc == SOCKET_ERROR || rc == 0)
	return SEC_E_INTERNAL_ERROR;
      else
	ebuf->count += rc;
    }

    Status = SEC_I_CONTINUE_NEEDED;
    if(ebuf->count > 0) {
      InBuffers[0].pvBuffer    = ebuf->pBuf;
      InBuffers[0].cbBuffer    = ebuf->count;
      InBuffers[0].BufferType  = SECBUFFER_TOKEN;

      InBuffers[1].pvBuffer    = NULL;
      InBuffers[1].cbBuffer    = 0;
      InBuffers[1].BufferType  = SECBUFFER_EMPTY;

      InBuffer.cBuffers        = 2;
      InBuffer.pBuffers        = InBuffers;
      InBuffer.ulVersion       = SECBUFFER_VERSION;

      OutBuffers[0].pvBuffer   = NULL;              // Allocated by schannel.
      OutBuffers[0].BufferType = SECBUFFER_TOKEN;
      OutBuffers[0].cbBuffer   = 0;

      OutBuffer.cBuffers = 1;
      OutBuffer.pBuffers = OutBuffers;
      OutBuffer.ulVersion = SECBUFFER_VERSION;

      Status = g_sft.AcceptSecurityContext(&g_ServerCreds,
					   fInitContext ? NULL : &ssl->hContext,
					   &InBuffer,
					   ASC_FLAGS,
					   SECURITY_NATIVE_DREP,
					   fInitContext ? &ssl->hContext : NULL,
					   &OutBuffer,
					   &dwSSPIOutFlags,
					   &tsExpiry);
      fInitContext = FALSE;
    }

    //
    // Send response if there is one
    //
    if ((Status == SEC_E_OK ||
	 Status == SEC_I_CONTINUE_NEEDED ||
	 (FAILED(Status) && (0 != (dwSSPIOutFlags & ISC_RET_EXTENDED_ERROR))))	&&
	(OutBuffers[0].cbBuffer != 0 && OutBuffers[0].pvBuffer != NULL))
      {
	rc = sspi_send(ssl->socket, OutBuffers[0].pvBuffer, OutBuffers[0].cbBuffer, 0);

	if((rc == SOCKET_ERROR && WSAGetLastError() == WSAEWOULDBLOCK)
	   || rc == 0)
	  sspi_error("Blocked sending handshake data");	// FIXME: Need to handle this.
	else if (rc == SOCKET_ERROR)
	  sspi_error("Error sending handshake data: %d\n",WSAGetLastError());

	g_sft.FreeContextBuffer(OutBuffers[0].pvBuffer);
	OutBuffers[0].pvBuffer = NULL;
      }

    //
    // Save leftover bytes which were read, but not part of the handshake.
    //
    if(Status == SEC_E_OK) {
      if(InBuffers[1].BufferType == SECBUFFER_EXTRA) {
	int cbBuffer = ebuf->count;
	ebuf->count = InBuffers[1].cbBuffer;
	MoveMemory(ebuf->pBuf, ebuf->pBuf + cbBuffer - ebuf->count, ebuf->count);
	Warn(" Server handshake: %d bytes left over\n", ebuf->count);
      } else {
	ebuf->count = 0;
      }
    } else
      ebuf->count = 0;

    //
    // Return now if OK or fatal error.
    //
    if (Status == SEC_E_OK)
      return Status;

    else if (FAILED(Status) && (Status != SEC_E_INCOMPLETE_MESSAGE)) {
      sspi_error("AcceptSecurityContext Failed: %lx %s\n", Status, sspi_SecError(Status));
      return Status;
    }
  }

  return Status;
}

static SECURITY_STATUS sspi_VerifyServerCertificate(PCCERT_CONTEXT  pServerCert,
						    PSTR            pszServerName,
						    DWORD           dwCertFlags)
{
  CERT_CHAIN_POLICY_PARA   PolicyPara;
  CERT_CHAIN_POLICY_STATUS PolicyStatus;
  CERT_CHAIN_PARA          ChainPara;
  PCCERT_CHAIN_CONTEXT     pChainContext = NULL;
  DWORD   Status;

  Trace("sspi_VerifyServerCertificate\n");

  if(pServerCert == NULL)
    return SEC_E_WRONG_PRINCIPAL;

  //
  // Build certificate chain.
  //
  ZeroMemory(&ChainPara, sizeof(ChainPara));
  ChainPara.cbSize = sizeof(ChainPara);

  if(!CertGetCertificateChain(NULL,
			      pServerCert,
			      NULL,
			      pServerCert->hCertStore,
			      &ChainPara,
			      0,
			      NULL,
			      &pChainContext)) {
    Status = GetLastError();
    sspi_error("Error 0x%x returned by CertGetCertificateChain!\n", Status);
    goto cleanup;
  }

  //
  // Validate certificate chain.
  // 
  ZeroMemory(&PolicyPara, sizeof(PolicyPara));
  PolicyPara.cbSize  = sizeof(PolicyPara);
  PolicyPara.dwFlags = CERT_CHAIN_POLICY_ALLOW_UNKNOWN_CA_FLAG;	// TODO: other flags?

  ZeroMemory(&PolicyStatus,sizeof(PolicyStatus));
  PolicyStatus.cbSize = sizeof(PolicyStatus);

  if(!CertVerifyCertificateChainPolicy(CERT_CHAIN_POLICY_SSL,
				       pChainContext,
				       &PolicyPara,
				       &PolicyStatus)) {
    Status = GetLastError();
    sspi_error("Error 0x%x returned by CertVerifyCertificateChainPolicy!\n", Status);
    goto cleanup;
  }

  if(PolicyStatus.dwError) {
    Status = PolicyStatus.dwError;
    sspi_error("Error 0x%x (%s) returned by CertVerifyCertificateChainPolicy!\n",
	       Status, sspi_CertError(Status));
    goto cleanup;
  }

  Status = SEC_E_OK;

cleanup:

  if(pChainContext)
    CertFreeCertificateChain(pChainContext);

  return Status;
}

static SECURITY_STATUS sspi_VerifyServer(SSL *ssl)
{
  PCCERT_CONTEXT pCert = NULL;
  SECURITY_STATUS Status;

  Trace("sspi_VerifyServer\n");

  // Get server's certificate.
  Status = g_sft.QueryContextAttributes(&ssl->hContext, SECPKG_ATTR_REMOTE_CERT_CONTEXT, (PVOID)&pCert);
  if(Status != SEC_E_OK) {
    sspi_error("Error 0x%x querying remote certificate\n", Status);
    return FALSE;
  }

  sspi_GetCertInfo(ssl, pCert);

  // Attempt to validate server certificate.
  Status = sspi_VerifyServerCertificate(pCert, ssl->serverName, 0);
  if(Status != SEC_E_OK) {
    sspi_error("**** Error authenticating server credentials!\n");
    return SEC_E_INTERNAL_ERROR; // Random.
  }

  CertFreeCertificateContext(pCert);
  return Status;
}

static SECURITY_STATUS sspi_Close(SSL *ssl)
{
  DWORD           dwType;
  PBYTE           pbMessage;
  DWORD           cbMessage;
  SecBufferDesc   OutBuffer;
  SecBuffer       OutBuffers[1];
  DWORD           dwSSPIOutFlags;
  TimeStamp       tsExpiry;
  SECURITY_STATUS Status;
  int rc;

  Trace("sspi_Close\n");

  //
  // Notify schannel that we are about to close the connection.
  //
  dwType = SCHANNEL_SHUTDOWN;

  OutBuffers[0].pvBuffer   = &dwType;
  OutBuffers[0].BufferType = SECBUFFER_TOKEN;
  OutBuffers[0].cbBuffer   = sizeof(dwType);

  OutBuffer.cBuffers  = 1;
  OutBuffer.pBuffers  = OutBuffers;
  OutBuffer.ulVersion = SECBUFFER_VERSION;

  Status = g_sft.ApplyControlToken(&ssl->hContext, &OutBuffer);

  if(FAILED(Status)) {
    sspi_error("ApplyControlToken Failed: %lx %s\n", Status, sspi_SecError(Status));
    return Status;
  }

  //
  // Build an SSL close notify message.
  //
  OutBuffers[0].pvBuffer   = NULL;
  OutBuffers[0].BufferType = SECBUFFER_TOKEN;
  OutBuffers[0].cbBuffer   = 0;

  OutBuffer.cBuffers  = 1;
  OutBuffer.pBuffers  = OutBuffers;
  OutBuffer.ulVersion = SECBUFFER_VERSION;

  Status = g_sft.InitializeSecurityContextA(ssl->is_server ? &g_ServerCreds : &g_ClientCreds,
					    &ssl->hContext,
					    NULL,
					    ISC_FLAGS,
					    0,
					    SECURITY_NATIVE_DREP,
					    NULL,
					    0,
					    &ssl->hContext,
					    &OutBuffer,
					    &dwSSPIOutFlags,
					    &tsExpiry);
  if(FAILED(Status)) {
    sspi_error("InitializeSecurityContextA Failed: %lx %s\n", Status, sspi_SecError(Status));
    return Status;
  }

  pbMessage = OutBuffers[0].pvBuffer;
  cbMessage = OutBuffers[0].cbBuffer;

  //
  // Send the close notify message to the server.
  //
  if(pbMessage != NULL && cbMessage != 0) {
    rc = sspi_send(ssl->socket, pbMessage, cbMessage, 0);
    if(rc == SOCKET_ERROR || rc == 0)
      return SEC_E_INTERNAL_ERROR;

    Warn("Sent Close Notify %d bytes\n", rc);

    // Free output buffer.
    g_sft.FreeContextBuffer(pbMessage);
  }
  
  return SEC_E_OK;
}



/*
 * Informational Functions
 */

static void sspi_GetCertInfo(SSL *ssl, PCCERT_CONTEXT  pCert)
{
  char subject[128], issuer[128];

  ZeroMemory(subject,sizeof(subject));
  // display leaf name
  if(1==CertGetNameString(pCert, CERT_NAME_FRIENDLY_DISPLAY_TYPE, 
			  0, NULL, subject, sizeof(subject)-1)) {
    sspi_error("CertGetNameString for subject failed: %lx\n", GetLastError());
    return;
  }
  ssl->subject = strdup(subject);

  ZeroMemory(issuer,sizeof(issuer));
  if(1==CertGetNameString(pCert, CERT_NAME_FRIENDLY_DISPLAY_TYPE, 
			  CERT_NAME_ISSUER_FLAG, NULL, issuer, sizeof(issuer)-1)) {
    sspi_error("CertGetNameString for issuer failed: %lx\n", GetLastError());
    return;
  }
  ssl->issuer = strdup(issuer);
}

static char *sspi_CipherName(int aiCipher)
{
  switch(aiCipher) {
   case CALG_RC4: return "RC4";
   case CALG_3DES: return "3DES";
   case CALG_RC2: return "RC2";
   case CALG_DES:
   case CALG_CYLINK_MEK: return "DES";
   case CALG_AES_128:
   case CALG_AES_192:
   case CALG_AES_256:
   case CALG_AES: return "AES";
   case CALG_SKIPJACK: return "Skipjack";
   default: return "cipher";
  }
}

static char *sspi_CertError(DWORD Status)
{
  switch(Status) {
   case CERT_E_EXPIRED:                return "CERT_E_EXPIRED";
   case CERT_E_VALIDITYPERIODNESTING:  return "CERT_E_VALIDITYPERIODNESTING";
   case CERT_E_ROLE:                   return "CERT_E_ROLE";
   case CERT_E_PATHLENCONST:           return "CERT_E_PATHLENCONST";
   case CERT_E_CRITICAL:               return "CERT_E_CRITICAL";
   case CERT_E_PURPOSE:                return "CERT_E_PURPOSE";
   case CERT_E_ISSUERCHAINING:         return "CERT_E_ISSUERCHAINING";
   case CERT_E_MALFORMED:              return "CERT_E_MALFORMED";
   case CERT_E_UNTRUSTEDROOT:          return "CERT_E_UNTRUSTEDROOT";
   case CERT_E_CHAINING:               return "CERT_E_CHAINING";
   case TRUST_E_FAIL:                  return "TRUST_E_FAIL";
   case CERT_E_REVOKED:                return "CERT_E_REVOKED";
   case CERT_E_UNTRUSTEDTESTROOT:      return "CERT_E_UNTRUSTEDTESTROOT";
   case CERT_E_REVOCATION_FAILURE:     return "CERT_E_REVOCATION_FAILURE";
   case CERT_E_CN_NO_MATCH:            return "CERT_E_CN_NO_MATCH";
   case CERT_E_WRONG_USAGE:            return "CERT_E_WRONG_USAGE";
   default:                            return "(unknown)";
  }
}

static char *sspi_SecError(DWORD Status)
{
  switch(Status) {
   case SEC_E_BAD_PKGID: return "SEC_E_BAD_PKGID";
   case SEC_E_BUFFER_TOO_SMALL: return "SEC_E_BUFFER_TOO_SMALL";
   case SEC_E_CANNOT_INSTALL: return "SEC_E_CANNOT_INSTALL";
   case SEC_E_CANNOT_PACK: return "SEC_E_CANNOT_PACK";
   case SEC_E_CONTEXT_EXPIRED: return "SEC_E_CONTEXT_EXPIRED";
   case SEC_E_INCOMPLETE_CREDENTIALS: return "SEC_E_INCOMPLETE_CREDENTIALS";
   case SEC_E_INCOMPLETE_MESSAGE: return "SEC_E_INCOMPLETE_MESSAGE";
   case SEC_E_INSUFFICIENT_MEMORY: return "SEC_E_INSUFFICIENT_MEMORY";
   case SEC_E_INTERNAL_ERROR: return "SEC_E_INTERNAL_ERROR";
   case SEC_E_INVALID_HANDLE: return "SEC_E_INVALID_HANDLE";
   case SEC_E_INVALID_TOKEN: return "SEC_E_INVALID_TOKEN";
   case SEC_E_LOGON_DENIED: return "SEC_E_LOGON_DENIED";
   case SEC_E_MESSAGE_ALTERED: return "SEC_E_MESSAGE_ALTERED";
   case SEC_E_NOT_OWNER: return "SEC_E_NOT_OWNER";
   case SEC_E_NO_AUTHENTICATING_AUTHORITY: return "SEC_E_NO_AUTHENTICATING_AUTHORITY";
   case SEC_E_NO_CREDENTIALS: return "SEC_E_NO_CREDENTIALS";
   case SEC_E_NO_IMPERSONATION: return "SEC_E_NO_IMPERSONATION";
   case SEC_E_OK: return "SEC_E_OK";
   case SEC_E_OUT_OF_SEQUENCE: return "SEC_E_OUT_OF_SEQUENCE";
   case SEC_E_QOP_NOT_SUPPORTED: return "SEC_E_QOP_NOT_SUPPORTED";
   case SEC_E_SECPKG_NOT_FOUND: return "SEC_E_SECPKG_NOT_FOUND";
   case SEC_E_TARGET_UNKNOWN: return "SEC_E_TARGET_UNKNOWN";
   case SEC_E_UNKNOWN_CREDENTIALS: return "SEC_E_UNKNOWN_CREDENTIALS";
   case SEC_E_UNSUPPORTED_FUNCTION: return "SEC_E_UNSUPPORTED_FUNCTION";
   case SEC_E_WRONG_PRINCIPAL: return "SEC_E_WRONG_PRINCIPAL";
   case SEC_I_COMPLETE_AND_CONTINUE: return "SEC_I_COMPLETE_AND_CONTINUE";
   case SEC_I_COMPLETE_NEEDED: return "SEC_I_COMPLETE_NEEDED";
   case SEC_I_CONTINUE_NEEDED: return "SEC_I_CONTINUE_NEEDED";
   case SEC_I_INCOMPLETE_CREDENTIALS: return "SEC_I_INCOMPLETE_CREDENTIALS";
   case SEC_I_LOCAL_LOGON: return "SEC_I_LOCAL_LOGON";
   case SEC_I_RENEGOTIATE: return "SEC_I_RENEGOTIATE";
   default: return "(unknown)";
  }
}

static char *sspi_ProtocolName(DWORD protocol)
{
  switch(protocol) {
   case SP_PROT_TLS1_CLIENT:
   case SP_PROT_TLS1_SERVER:
     return "TLS1";
   case SP_PROT_SSL3_CLIENT:
   case SP_PROT_SSL3_SERVER:
     return "SSL3";
   case SP_PROT_SSL2_CLIENT:
   case SP_PROT_SSL2_SERVER:
     return "SSL2";
   default:
     return "?";
  }
}

static char *sspi_WinsockError(DWORD Status)
{
  switch(Status) {
   case WSAEINTR: return "WSA EINTR";
   case WSAEBADF: return "WSA EBADF";
   case WSAEACCES: return "WSA EACCES";
   case WSAEFAULT: return "WSA EFAULT";
   case WSAEINVAL: return "WSA EINVAL";
   case WSAEMFILE: return "WSA EMFILE";
   case WSAEWOULDBLOCK: return "WSA EWOULDBLOCK";
   case WSAEINPROGRESS: return "WSA EINPROGRESS";
   case WSAEALREADY: return "WSA EALREADY";
   case WSAENOTSOCK: return "WSA ENOTSOCK";
   case WSAEDESTADDRREQ: return "WSA EDESTADDRREQ";
   case WSAEMSGSIZE: return "WSA EMSGSIZE";
   case WSAEPROTOTYPE: return "WSA EPROTOTYPE";
   case WSAENOPROTOOPT: return "WSA ENOPROTOOPT";
   case WSAEPROTONOSUPPORT: return "WSA EPROTONOSUPPORT";
   case WSAESOCKTNOSUPPORT: return "WSA ESOCKTNOSUPPORT";
   case WSAEOPNOTSUPP: return "WSA EOPNOTSUPP";
   case WSAEPFNOSUPPORT: return "WSA EPFNOSUPPORT";
   case WSAEAFNOSUPPORT: return "WSA EAFNOSUPPORT";
   case WSAEADDRINUSE: return "WSA EADDRINUSE";
   case WSAEADDRNOTAVAIL: return "WSA EADDRNOTAVAIL";
   case WSAENETDOWN: return "WSA ENETDOWN";
   case WSAENETUNREACH: return "WSA ENETUNREACH";
   case WSAENETRESET: return "WSA ENETRESET";
   case WSAECONNABORTED: return "WSA ECONNABORTED";
   case WSAECONNRESET: return "WSA ECONNRESET";
   case WSAENOBUFS: return "WSA ENOBUFS";
   case WSAEISCONN: return "WSA EISCONN";
   case WSAENOTCONN: return "WSA ENOTCONN";
   case WSAESHUTDOWN: return "WSA ESHUTDOWN";
   case WSAETOOMANYREFS: return "WSA ETOOMANYREFS";
   case WSAETIMEDOUT: return "WSA ETIMEDOUT";
   case WSAECONNREFUSED: return "WSA ECONNREFUSED";
   case WSAELOOP: return "WSA ELOOP";
   case WSAENAMETOOLONG: return "WSA ENAMETOOLONG";
   case WSAEHOSTDOWN: return "WSA EHOSTDOWN";
   case WSAEHOSTUNREACH: return "WSA EHOSTUNREACH";
   case WSAENOTEMPTY: return "WSA ENOTEMPTY";
   case WSAEPROCLIM: return "WSA EPROCLIM";
   case WSAEUSERS: return "WSA EUSERS";
   case WSAEDQUOT: return "WSA EDQUOT";
   case WSAESTALE: return "WSA ESTALE";
   case WSAEREMOTE: return "WSA EREMOTE";
   case WSAEDISCON: return "WSA EDISCON";
   case WSASYSNOTREADY: return "WSA SYSNOTREADY";
   case WSAVERNOTSUPPORTED: return "WSA VERNOTSUPPORTED";
   case WSANOTINITIALISED: return "WSA NOTINITIALISED";
   default: return "(unknown)";
  }
}

#endif   // of ALG_SID_AES 
