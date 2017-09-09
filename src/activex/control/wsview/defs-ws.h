// -*- Mode: C++ -*-

#if !defined(AFX_DEFS_WSV_H__INCLUDED_)
#define AFX_DEFS_WSV_H__INCLUDED_

// GWVC = Gensym Workspace View Control
#define IDS_GWVC                    1
#define IDB_GWVC                    1
#define WM_TELEWINDOWS_SESSION_ID   (WM_USER+3)

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#  ifndef APSTUDIO_READONLY_SYMBOLS
#    define _APS_NEXT_RESOURCE_VALUE        201
#    define _APS_NEXT_COMMAND_VALUE         32768
#    define _APS_NEXT_CONTROL_VALUE         202
#    define _APS_NEXT_SYMED_VALUE           101
#  endif
#endif


// Define these here in case we want to change to an earlier or later version
#define AXL_IFACE IG2Gateway4
#define AXL_IFACE_IID IID_IG2Gateway4
#define AXL_IFACE_NAME_AS_STRING "IG2Gateway4"

// The "secret" TW command line option that tells TW the handle to make its
// window a child of.
#define TW_WINDOWHANDLE_CMD TEXT("-WINDOWHANDLE")

// The name of the TW executable
#define TW_FILENAME         TEXT("tw.exe")
#define TW_NAME_LEN         _tcslen(TW_FILENAME)

// The environment variable to check for the location of TW
#define TW_AX_ENV_VAR       TEXT("TW_HOME_FOR_ACTIVEX")

// The names of the system procedures to call
#define TWAXL_WS_NAME_PROCEDURE L"TWAXL-SHOW-WORKSPACE-WITH-NAME"
#define TWAXL_WS_UUID_PROCEDURE L"TWAXL-SHOW-WORKSPACE-WITH-UUID"

// If we can't find TW in the registry, try this default path
#define TW_DEFAULT_EXE      TEXT("c:\\Program Files\\Gensym\\g2-2011\\g2\\tw.exe")

// The class of HWND which we expect to be embedded into our window, and which
// we are willing to "control".  If someone else embeds themselves in our
// window, they may not be fully functional.  This class name is defined in
// ext/c/msinits.c.  Now that we depend on it here, it should never change.
#define NAME_OF_WORKSPACE_VIEW_WINDOW TEXT("GensymWorkspaceViewClass")

// The length of the buffer needed to query the class name to verify that it's
// Telewindows.  Since we're only interested in yes or no, we don't have to use
// a big buffer, just one big enough to hold "GensymWorkspaceViewClass".
#define LENGTH_OF_TW_CLASSNAME 25

// Definition of properties -- these don't *have* to match up with the dispid's,
// but it's nice if they do.  dispid's apparently begin at 1, not zero, so use
// the same thing here.

#define GWVC_UNUSED_PROPERTY      0
#define GWVC_TW_LOCATION          1

#define GWVC_OPTIONAL_ARGS_BEGIN  2
#define GWVC_CL_WORKSPACE         2
#define GWVC_CL_WORKSPACE_UUID    3
#define GWVC_CL_USER_NAME         4
#define GWVC_CL_USER_MODE         5
#define GWVC_CL_PASSWORD          6
#define GWVC_CL_WINDOW_STYLE      7
#define GWVC_OPTIONAL_ARGS_END    7

#define GWVC_NUMBER_OF_PROPERTIES (GWVC_OPTIONAL_ARGS_END + 1)

#define GWVC_SHOW_BY_NAME       1
#define GWVC_SHOW_BY_UUID       2
#define GWVC_SHOW_BY_HANDLE     4
#define GWVC_SHOW_BY_REFERENCE  8

#define GWVC_NO_TW_SESSION           -1
#define GWVC_LOWEST_VALID_TW_SESSION  2

#define GWVC_NO_TW_PROCESS_ID         0


// Registry information
#define GWVC_TELEWINDOWS_KEY TEXT("SOFTWARE\\Gensym\\Telewindows")
#define GWVC_VERSION_KEY     TEXT("2011")
#define GWVC_DIR_VALUE       TEXT("installDir")

// Miscellaneous constants
#define GUID_STRING_LENGTH   39

#define MAX_REGKEY_LEN 255 // per SDK docs


// TW has these default values for connecting to a G2 when the host and port
// are not specified, but prior to 7.0, TW only used its defaults if *no*
// other command line options were given.  Since the control always needs
// to specify -windowhandle, at least, that can never be the case.  Therefore,
// we need to know about the defaults here.
#define DEFAULT_G2_HOST TEXT("localhost")

// This should be a string, not an integer.  Make sure to use quotes.
#define DEFAULT_G2_PORT TEXT("1111")


// Useful for various C/C++ files
extern void dprintf (short debug_level, char *format_string, ...);
extern void set_debug_level (short debug_level);
extern void set_minimum_debug_level (short debug_level);


// Codes for use with dprintf to control output verbosity
#define ALWAYS    0
#define DERROR   10
#define PROGRESS 20
#define DETAIL   30
#define DUMP     40
#define TOFILE   50

// Version information
//
// The ActiveX controls are separate product, which don't link with any other
// Gensym code.  Successive versions of the controls, of course, contain bug
// fixes and improvements, so they must be versioned.  Although the Workspace
// View control should work with any version of TW, 8.0a0 or greater, to reduce
// confusion it should stay in synch with the version of TW it ships with.

// This needs to be either kept up to date with, or replaced by, the version
// info in resources.rc  -- jv, 5/1/02

// It may seem natural to make commercial release be zero, and make the numbers
// be larger the further we are from release, but that doesn't fit with the
// model of Microsoft's versioning.  7,0,16,0 is defined to be newer than
// 7,0,0,0, so we have to reverse the order.  So the commercial release of 7.0r0
// will be 7,0,128,0.  That may be suboptimal in theory, but I think it's the
// best fit for how the versioning works in Microsoft's world.  Users will very
// likely be able to use 7,0,0,0 for their HTML as long as they don't have any
// Alpha or Beta versions laying around on their file system.  - jv, 10/21/02

// integers
#define TW_AX_CONTROL_PRERELEASE        8
#define TW_AX_CONTROL_ALPHA            16
#define TW_AX_CONTROL_BETA             32
#define TW_AX_CONTROL_PATCH            64
#define TW_AX_CONTROL_CRELEASE        128

#define TW_AX_CONTROL_MAJOR_VERSION     2011
#define TW_AX_CONTROL_MINOR_VERSION     0
#define TW_AX_CONTROL_RELEASE_QUALITY   TW_AX_CONTROL_CRELEASE
#define TW_AX_CONTROL_REVISION_NUMBER   0

// strings; this needs to be updated by hand until we put it into build-prep
#define TW_AX_CONTROL_BUILD_ID_STRING   TEXT("NH30")

// should be of the format " (patch #n)" or the like.  Having the leading
// space here means that when we're not a patch, we don't need to worry
// about having a space in the format string.
#define TW_AX_CONTROL_PATCH_STRING      TEXT("")


// Error message if we can't open the logfile
#define NO_LOGFILE_MSG TEXT("Gensym's Workspace View control could not open stream for logfile")

// Error message if we can't allocate enough memory
#define OUT_OF_MEMORY_MSG TEXT("Gensym's Workspace View control could not obtain sufficient memory")

// Error message if we can't allocate enough memory
#define NOT_AN_HWND_MSG TEXT("Error: value obtained for HWND in ShowWorkspace is not a window!")

// Where to write the logfile if the system doesn't tell us
#define DEFAULT_LOGFILE_DIRECTORY TEXT(".")

#define PATH_SEPARATOR_AS_CHAR   '\\'
#define PATH_SEPARATOR_AS_STRING "\\"

#ifndef S_ISDIR
#  define S_ISDIR(mode)  (((mode) & _S_IFDIR) == _S_IFDIR)
#endif

#endif // !defined(AFX_DEFS_WSV_H__INCLUDED_)
