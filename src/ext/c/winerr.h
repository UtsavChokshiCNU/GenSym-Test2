/* From Microsoft Developer Studio, Book "Win32SDK : Internet", Name "Error Codes" */

#include <windows.h>

struct win32internet_error_code_struct {
  int code;
  char *name;
} win32internet_error_code_table [] =
  {
    WSAEACCES,"Permission denied.",
    WSAEADDRINUSE,"Address already in use.",
    WSAEADDRNOTAVAIL,"Cannot assign requested address.",
    WSAEAFNOSUPPORT,"Address family not supported by protocol family.",
    WSAEALREADY,"Operation already in progress.",
    WSAECONNABORTED,"Software caused connection abort.",
    WSAECONNREFUSED,"Connection refused.",
    WSAECONNRESET,"Connection reset by peer.",
    WSAEDESTADDRREQ,"Destination address required.",
    WSAEFAULT,"Bad address.",
    WSAEHOSTDOWN,"Host is down.",
    WSAEHOSTUNREACH,"No route to host.",
    WSAEINPROGRESS,"Operation now in progress.",
    WSAEINTR,"Interrupted function call.",
    WSAEINVAL,"Invalid argument.",
    WSAEISCONN,"Socket is already connected.",
    WSAEMFILE,"Too many open files.",
    WSAEMSGSIZE,"Message too long.",
    WSAENETDOWN,"Network is down.",
    WSAENETRESET,"Network dropped connection on reset.",
    WSAENETUNREACH,"Network is unreachable.",
    WSAENOBUFS,"No buffer space available.",
    WSAENOPROTOOPT,"Bad protocol option.",
    WSAENOTCONN,"Socket is not connected.",
    WSAENOTSOCK,"Socket operation on non-socket.",
    WSAEOPNOTSUPP,"Operation not supported.",
    WSAEPFNOSUPPORT,"Protocol family not supported.",
    WSAEPROCLIM,"Too many processes.",
    WSAEPROTONOSUPPORT,"Protocol not supported.",
    WSAEPROTOTYPE,"Protocol wrong type for socket.",
    WSAESHUTDOWN,"Cannot send after socket shutdown.",
    WSAESOCKTNOSUPPORT,"Socket type not supported.",
    WSAETIMEDOUT,"Connection timed out.",
    WSAEWOULDBLOCK,"Resource temporarily unavailable.",
    WSAHOST_NOT_FOUND,"Host not found.",
    /* WSA_INVALID_HANDLE,"Specified event object handle is invalid.", */
    /* WSA_INVALID_PARAMETER,"One or more parameters are invalid.", */
    /* WSAINVALIDPROCTABLE,"Invalid procedure table from service provider.", */
    /* WSAINVALIDPROVIDER,"Invalid service provider version number.", */
    /* WSA_IO_PENDING,"Overlapped operations will complete later.", */
    /* WSA_IO_INCOMPLETE,"Overlapped I/O event object not in signaled state.", */
    /* WSA_NOT_ENOUGH_MEMORY,"Insufficient memory available.", */
    WSANOTINITIALISED,"Successful WSAStartup not yet performed.",
    WSANO_DATA,"Valid name, no data record of requested type.",
    WSANO_RECOVERY,"This is a non-recoverable error.",
    /* WSAPROVIDERFAILEDINIT,"Unable to initialize a service provider.", */
    /* WSASYSCALLFAILURE,"System call failure.", */
    WSASYSNOTREADY,"Network subsystem is unavailable.",
    WSATRY_AGAIN,"Non-authoritative host not found.",
    WSAVERNOTSUPPORTED,"WINSOCK.DLL version out of range.",
    WSAEDISCON,"Graceful shutdown in progress.",
    /* WSA_OPERATION_ABORTED,"Overlapped operation aborted.", */
    0, ""
  };


