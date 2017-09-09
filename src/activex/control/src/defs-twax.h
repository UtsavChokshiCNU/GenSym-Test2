// -*- Mode: C++ -*-

#if !defined(AFX_DEFS_TWAX_H__INCLUDED_)
#define AFX_DEFS_TWAX_H__INCLUDED_

#define IDS_TWAX                    1
#define IDB_TWAX                    1
#define IDS_TWAX_PPG                2
#define IDS_TWAX_PPG_CAPTION        200
#define IDD_PROPPAGE_TWAX           200
#define IDC_CHECK1                  201

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


// Registry information
#define TW_AX_TELEWINDOWS_KEY _T("SOFTWARE\\Gensym\\Telewindows")
#define TW_AX_VERSION_KEY     _T("2011")
#define TW_AX_DIR_VALUE       _T("installDirClassic")

// Miscellaneous constants
#define GUID_STRING_LENGTH 39

// The "secret" TW command line option that tells TW the handle to make its
// window a child of.
#define TW_WINDOWHANDLE_CMD _T("-WINDOWHANDLE")

// The name of the TW executable
#define TW_FILENAME         _T("tw.exe")
#define TW_NAME_LEN         _tcslen(TW_FILENAME)


// If we can't find TW in the registry, try this default path
#define TW_DEFAULT_EXE      _T("c:\\Program Files\\Gensym\\g2-2011\\g2\\tw.exe")

// The environment variable to check for the location of TW
#define TW_AX_ENV_VAR       _T("TW_HOME_FOR_ACTIVEX")

// The class of HWND which we expect to be embedded into our window, and which
// we are willing to "control".  If someone else embeds themselves in our
// window, they may not be fully functional.  This class name is defined in
// ext/c/windows.c.  Now that we depend on it here, it should never change.
#define NAME_OF_TELEWINDOWS_WINDOW _T("GensymTelewindowClass")

// The length of the buffer needed to query the class name to verify that it's
// Telewindows.  Since we're only interested in yes or no, we don't have to use
// a big buffer, just one big enough to hold "GensymTelewindowClass".
#define LENGTH_OF_TW_CLASSNAME 22

// Definition of properties -- these don't *have* to match up with the dispid's,
// but it's nice if they do.  dispid's apparently begin at 1, not zero, so use
// the same thing here.

#define TW_AX_UNUSED_PROPERTY      0
#define TW_AX_TW_LOCATION          1
#define TW_AX_CL_HOST              2
#define TW_AX_CL_PORT              3

#define TW_AX_OPTIONAL_ARGS_BEGIN  4
#define TW_AX_CL_USER_NAME         4
#define TW_AX_CL_USER_MODE         5
#define TW_AX_CL_PASSWORD          6
#define TW_AX_CL_BACKGROUND        7
#define TW_AX_CL_INIT_STRING       8
#define TW_AX_CL_SPLASHTIME        9
#define TW_AX_CL_UI_MODE          10
#define TW_AX_CL_WINDOW_STYLE     11
#define TW_AX_CL_WORKSPACE        12
#define TW_AX_CL_WORKSPACE_UUID   13
// id 14 is not used for a property; it belongs to the method ConnectToG2
#define TW_AX_CL_LOGFILE          15
#define TW_AX_OPTIONAL_ARGS_END   15

#define TW_AX_NUMBER_OF_PROPERTIES (TW_AX_OPTIONAL_ARGS_END + 1)


// TW has these default values for connecting to a G2 when the host and port
// are not specified, but prior to 7.0, TW only used its defaults if *no*
// other command line options were given.  Since the control always needs
// to specify -windowhandle, at least, that can never be the case.  Therefore,
// we need to know about the defaults here.
#define DEFAULT_G2_HOST _T("localhost")

// This should be a string, not an integer.  Make sure to use quotes.
#define DEFAULT_G2_PORT _T("1111")


// Useful for various C/C++ files
extern void dprintf (short debug_level, char *format_string, ...);

// Codes for use with dprintf to control output verbosity
#define ALWAYS    0
#define DERROR   10
#define PROGRESS 20
#define DETAIL   30
#define DUMP     40
#define TOFILE   50

// Version information
//
// This control is a separate product, which does not link with any other Gensym
// code.  Successive versions of the control, of course, contain bug fixes and
// improvements, so it must be versioned.  Although the control should and
// probably does work with any version of TW that supports the -windowhandle
// command, to reduce confusion it should stay in synch with the version of TW
// it ships with.

// This needs to be either kept up to date with, or replaced by, the version
// info in resources.rc  -- jv, 5/1/02

// I had initially made commercial release be zero, and make the numbers be
// larger the further we were from release, but that doesn't fit with the model
// of Microsoft's versioning.  7,0,16,0 is defined to be newer than 7,0,0,0, so
// I had to reverse the order.  So the commercial release of 7.0r0 will be
// 7,0,128,0.  That may be suboptimal in theory, but I think it's the best fit
// for how the versioning works in Microsoft's world.  Users will very likely
// be able to use 7,0,0,0 for their HTML as long as they don't have any Alpha
// or Beta versions laying around on their file system.   - jv, 10/21/02

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

// strings; this gets updated by the build-preparation script
#define TW_AX_CONTROL_BUILD_ID_STRING   _T("NH30")

// should be of the format " (patch #n)" or the like.  Having the leading
// space here means that when we're not a patch, we don't need to worry
// about having a space in the format string.
#define TW_AX_CONTROL_PATCH_STRING      _T("")


// Error message if we can't open the logfile
#define NO_LOGFILE_MSG _T("Gensym's TW ActiveX control could not open stream for logfile")

// Error message if we can't allocate enough memory
#define OUT_OF_MEMORY_MSG _T("Gensym's TW Plugin could obtain sufficient memory")

// Where to write the logfile if the system doesn't tell us
#define DEFAULT_LOGFILE_DIRECTORY _T(".")

#define PATH_SEPARATOR_AS_CHAR   '\\'
#define PATH_SEPARATOR_AS_STRING "\\"

#ifndef S_ISDIR
#  define S_ISDIR(mode)  (((mode) & _S_IFDIR) == _S_IFDIR)
#endif

#endif // !defined(AFX_DEFS_TWAX_H__INCLUDED_)
