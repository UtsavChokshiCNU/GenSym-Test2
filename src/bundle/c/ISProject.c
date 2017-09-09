#include "StdAfx.h"
#include "ISProject.h"
#include <sys/stat.h>

static int iFileGroupNumber = 0;
static int iRegistrySetNumber = 0;
static int iShortcutNumber = 0;

// Some standard define, if needed:
#ifndef NUL
#define NUL 0
#endif

// TO DO: MAKE THE PASSWORD USED TO ENCRYPT RANDOM
#define FILENAME_FILEGROUP_FDF_FILE	"File Groups\\Default.FDF"
#define FILENAME_FILEGROUP_FGL_FILE	"File Groups\\%s.FGL"
#define FILENAME_REGISTRY_RGE_FILE	"Registry Entries\\DEFAULT.RGE"
#define FILENAME_SHORTCUTS_SHL_FILE	"Shell Objects\\DEFAULT.SHL"

#define SECTION_NAME_FILEGROUP_LIST "FileGroups"
#define KEY_NAME_FILEGROUP_IN_LIST  "group%d"
#define KEY_NAME_REG_SET_NUMBER   "Set%d"
#define KEY_NAME_REG_SET_NAME   "Registry Set-%d"

#define SECTION_NAME_LEN	128
#define KEY_NAME_LEN		128
#define VALUE_STRING_LEN    128

#define YES "Yes"
#define NO   "No"


/* backslashify_in_place is a routine to strip out forward slashes in directory
   names and replace with backslashes.  It replaces all of the forwardslash
   characters (/) in str with backslashes (\).  No useful value is returned.  */

void backslashify_in_place(char *str)
{
  char *szForwardSlash;
  
  while((szForwardSlash = strchr(str, '/')) != NUL)
    szForwardSlash[0] = '\\';
}


/*
** remove_trailing_slash_in_place
**
** Remove trailing forward or backward slash, if any, from the end of str by shortening
** the end by one (i.e., overwriting the slash with the null character).  Examples:
**
**   "filename/", "filename\", or "filename" => "filename"
*/
void remove_trailing_slash_in_place(char *str)
{
  char last_char;
  int string_length;

  string_length = strlen(str);

  if (string_length > 0) {
    last_char = str[(string_length - 1)];
    if ((last_char == '\\') || (last_char == '/'))
      str[(string_length - 1)] = NUL;
  }
}


/* rename_component_normalized_temp takes a component name string and copies a
"normalized" name into component_normalized_temp_buffer, a global,
null-terminates it, and returns a pointer to that buffer. When it's normalized,
it's in the form used by InstallShield for component even functions.
Specifically, spaces and hyphens are removed.  */

static char component_normalized_temp_buffer[MAX_PATH];

char *rename_component_normalized_temp(char *str)
{
  char *cpy = component_normalized_temp_buffer;
  
  while(*str != NUL) {
    if ((*str != ' ') && (*str != '-'))
      *cpy++ = *str;
    *str++;
  }
  *cpy = NUL;
  
  return(component_normalized_temp_buffer);
}


/*
** NullErrorOut
**
**   This routine exits if a routine returns a 0 or NULL result, and
** prints the passed in routine name as well as a status message.
**
**   If logging is turned on, it also logs success messages for each
** call.  */
void NullErrorOut (long error, char *szRoutine, char *szMessage)
{
	char szErrorString[1024];

	if (error == 0) {
		sprintf(szErrorString, "  Fatal Error: %d\n  Routine: %s\n  Message: %s\n\n", error, szRoutine, szMessage);
	    fprintf(stderr, szErrorString);
		if (FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                          NULL, GetLastError(),
                          MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                          szErrorString, 0, NULL ) != 0) {

			fprintf(stderr, szErrorString);
		} else {
			fprintf(stderr, "FormatError generated an error.");
		}
		exit(0);
	}

	// TO DO: Do I want to use a LOGGING def. here or some other mechanism?
#ifdef LOGGING 
	sprintf(szErrorString, "  Success.\n  Routine: %s\n  Message: %s\n\n", szRoutine, szMessage);
    printf(szErrorString);
#endif

}



/*
** AddFileGroup
**
** This routine adds a file group to the InstallShield project in the 
** passed directory.
*/
BOOL AddFileGroup(char *szProjectPath,     // Path to the IS Pro Project
				  char *szFileGroupName,   // The name of the File Group
				  BOOL bSelfRegistering,   // Self registering files?
				  BOOL bIsDynamic,         // Dynamic or static file group?
				  BOOL bIsShared,          // Shared files?
				  BOOL bPotentiallyLocked, // Potentially Locked files?
				  char *szSourcePath,      // Source files directory for dynamic groups
				  char *szTargetPath)      // Target directory under primary directory
{
  char szFDFFileName[MAX_PATH], szFGLFileName[MAX_PATH];
  char szKeyName[KEY_NAME_LEN];
  char szKeyValue[VALUE_STRING_LEN];

  /*
  ** Construct the path to the FDF File which defines the file groups set
  */
  NullErrorOut((long) strcpy(szFDFFileName, szProjectPath), "AddFileGroup", "Copying Project Path String to FDF Filename path");
  NullErrorOut(PathAppend(szFDFFileName, FILENAME_FILEGROUP_FDF_FILE), "AddFileGroup", "Appending FDF Filename to Project Path String");
   
  /*
  ** Insert the necessary keys into the file
  */

  /*
  ** First make it one of the groups by inserting it into the group list.
  */
  sprintf(szKeyName, KEY_NAME_FILEGROUP_IN_LIST, iFileGroupNumber);
  NullErrorOut(WritePrivateProfileString(SECTION_NAME_FILEGROUP_LIST, szKeyName, szFileGroupName, szFDFFileName), "AddFileGroup", "Inserting New File Group Key to FDF File");

  /*
  ** Now insert the section for that group into the file.
  */ 
  if (bIsDynamic)
    NullErrorOut(WritePrivateProfileString(szFileGroupName, "LINKTYPE", "Dynamic Link", szFDFFileName), "AddFileGroup", "Setting Link Type for File Group to Dynamic Link");
  else
    NullErrorOut(WritePrivateProfileString(szFileGroupName, "LINKTYPE", "Static Link", szFDFFileName), "AddFileGroup", "Setting Link Type for File Group to Static Link");

  NullErrorOut(WritePrivateProfileString(szFileGroupName, "INFOTYPE", "Standard", szFDFFileName), "AddFileGroup", "Setting Info Type for File Group to Standard");
  NullErrorOut(WritePrivateProfileString(szFileGroupName, "UNINSTALLABLE", YES, szFDFFileName), "AddFileGroup", "Setting Uninstallable Property for File Group to Yes");
  NullErrorOut(WritePrivateProfileString(szFileGroupName, "UNINSTALLABLE", YES, szFDFFileName), "AddFileGroup", "Setting Uninstallable Property for File Group to Yes");
  if (bIsShared)
    NullErrorOut(WritePrivateProfileString(szFileGroupName, "FILETYPE", YES, szFDFFileName), "AddFileGroup", "Setting Shared Files Property for File Group to Yes");
  else
    NullErrorOut(WritePrivateProfileString(szFileGroupName, "FILETYPE", NO, szFDFFileName), "AddFileGroup", "Setting Shared Files Property for File Group to No");

  if (bPotentiallyLocked)
    NullErrorOut(WritePrivateProfileString(szFileGroupName, "POTENTIALLY", YES, szFDFFileName), "AddFileGroup", "Setting Potentially Locked Property for File Group to Yes");
  else
    NullErrorOut(WritePrivateProfileString(szFileGroupName, "POTENTIALLY", NO, szFDFFileName), "AddFileGroup", "Setting Potentially Locked Property for File Group to No");

  if (bSelfRegistering)
    NullErrorOut(WritePrivateProfileString(szFileGroupName, "SELFREGISTERING", YES, szFDFFileName), "AddFileGroup", "Setting self-registering Property for File Group to Yes");
  else
    NullErrorOut(WritePrivateProfileString(szFileGroupName, "SELFREGISTERING", NO, szFDFFileName), "AddFileGroup", "Setting self-registering Property for File Group to No");

  NullErrorOut(WritePrivateProfileString(szFileGroupName, "COMPRESS", YES, szFDFFileName), "AddFileGroup", "Setting Compressed Property for File Group to Yes");
  NullErrorOut(WritePrivateProfileString(szFileGroupName, "OPERATINGSYSTEM", "", szFDFFileName), "AddFileGroup", "Setting Operating System Property for File Group to Blank");
  NullErrorOut(WritePrivateProfileString(szFileGroupName, "LANGUAGE", "", szFDFFileName), "AddFileGroup", "Setting Language Property for File Group to Blank");
  NullErrorOut(WritePrivateProfileString(szFileGroupName, "COMMENT", "", szFDFFileName), "AddFileGroup", "Setting Comment Property for File Group to Blank");
  NullErrorOut(WritePrivateProfileString(szFileGroupName, "COMPRESSDLL", "", szFDFFileName), "AddFileGroup", "Setting Compression DLL Property for File Group to Blank");
  NullErrorOut(WritePrivateProfileString(szFileGroupName, "HTTPLOCATION", "", szFDFFileName), "AddFileGroup", "Setting HTTP Location Property for File Group to Blank");
  NullErrorOut(WritePrivateProfileString(szFileGroupName, "FTPLOCATION", "", szFDFFileName), "AddFileGroup", "Setting FTP Location Property for File Group to Blank");
  NullErrorOut(WritePrivateProfileString(szFileGroupName, "MISC", "", szFDFFileName), "AddFileGroup", "Setting Misc Property for File Group to Blank");
  NullErrorOut(WritePrivateProfileString(szFileGroupName, "INSTALLATION", "NEWERVERSION\\NEWERDATE", szFDFFileName), "AddFileGroup", "Setting Misc Property for File Group to Blank");

  /*
  ** NOTE: We are assuming a target directory at or under the primary application directory"
  */
  if (szTargetPath != NULL) {
    NullErrorOut(sprintf(szKeyValue, "<TARGETDIR>\\%s", szTargetPath), "AddFileGroup", "Setting up string for Target Directory");
  } else {
    strcpy(szKeyValue, "<TARGETDIR>");
  }
  NullErrorOut(WritePrivateProfileString(szFileGroupName, "TARGET", szKeyValue, szFDFFileName), "AddFileGroup", "Setting Target Directory Property for File Group");

  NullErrorOut(sprintf(szKeyValue, "General Application Destination\\%s", szTargetPath), "AddFileGroup", "Setting up string for Hidden Target Directory");
  NullErrorOut(WritePrivateProfileString(szFileGroupName, "TARGETHIDDEN", szKeyValue, szFDFFileName), "AddFileGroup", "Setting Hidden Target Directory Property for File Group");


  /*
  ** Now create the file group definition (.fgl) file for the group.
  */
  NullErrorOut((long) strcpy(szFGLFileName, szProjectPath), "AddFileGroup", "Copying Project Path String to FGL Filename path");
  NullErrorOut(PathAppend(szFGLFileName, "File Groups"), "AddFileGroup", "Appending File Groups directory to Project Path String");
  NullErrorOut(PathAppend(szFGLFileName, szFileGroupName), "AddFileGroup", "Appending File Group name to Project Path String");


  /* changed by MHD, 2/1/01 */
  if (PathAddExtension(szFGLFileName, ".FGL") == FALSE)
    printf("([call %d:] Path extension (%s) not added; this has one: %s?\n",
	   1, ".FGL", szFGLFileName);

  NullErrorOut(WritePrivateProfileString("General", "Type", "FILELIST", szFGLFileName), "AddFileGroup", "Adding Type Key to General Section of File Group File");
  NullErrorOut(WritePrivateProfileString("General", "Version", "1.10.000", szFGLFileName), "AddFileGroup", "Adding Version Key to General Section of File Group File");

  if (bIsDynamic) {
    NullErrorOut(WritePrivateProfileString("DYNAMIC", "FOLDER", szSourcePath, szFGLFileName), "AddFileGroup", "Adding Source Directory Key to Dynamic File Group Section of File Group File");
    NullErrorOut(WritePrivateProfileString("DYNAMIC", "INCLUDESUBDIR", YES, szFGLFileName), "AddFileGroup", "Adding Include Subdirectories Key to Dynamic File Group Section of File Group File");
    NullErrorOut(WritePrivateProfileString("DYNAMIC", "WILDCARD0", "*.*", szFGLFileName), "AddFileGroup", "Adding Wildcard Key to Dynamic File Group Section of File Group File");
  } 
	
  // *** NOTE: If it is not a dynamic file group, we don't add the files here, this is done using the 
  //			 AddFileToGroup function by whatever function is parsing the parts.  -- JW 7/20

  /*
  ** Increment the counter for the next file group.
  */
  return ++iFileGroupNumber;
	
}



/*
** InsertFileToFileGroup
**
**   This routine adds the passed file to to the named file group in the InstallShield 
** project in the passed directory.
*/
BOOL InsertFileToGroup(char *szProjectPath,    // Path to the IS Pro Project
					   char *szFileGroupName,  // The name of the File Group
				       char *szFileName,       // Name of the file to add
					   BOOL bStartGroup)       // First file in a new group?
{
  char szFGLFileName[MAX_PATH];
  char szKeyName[KEY_NAME_LEN];
  static int iFileNumber = 0;

  // NOTE: This is a kluge.  File groups start with file 0 and run to file n, 
  // and as long as we are calling this function n times for each group and 
  // then moving to the next, I can avoid writing the code to read in all the 
  // existing files to figure out where the counter stops, and instead just 
  // start from 0 when this flag is set, and have whatever function is calling 
  // us just reset the counter when it moves to each new group.  -- JW 7/20
  if (bStartGroup)
    iFileNumber = 0;

  // NOTE: We are not supporting subdirectory pickups in static file groups in this code
  //       because this is not supported in the current family file format anyway.  This 
  //       would be easy to implement however.  -- JW 7/20

  NullErrorOut((long) strcpy(szFGLFileName, szProjectPath), "InsertFileToGroup", "Copying Project Path String to FGL Filename path");
  NullErrorOut(PathAppend(szFGLFileName, "File Groups"), "InsertFileToGroup", "Appending File Groups directory to Project Path String");
  NullErrorOut(PathAppend(szFGLFileName, szFileGroupName), "InsertFileToGroup", "Appending File Group name to Project Path String");

  /* changed by MHD, 2/1/01 */
  if (PathAddExtension(szFGLFileName, ".FGL") == FALSE)
    printf("([call %d:] Path extension (%s) not added; this has one: %s?\n",
	   2, ".FGL", szFGLFileName);

  NullErrorOut(sprintf(szKeyName, "file%d", iFileNumber), "InsertFileToGroup", "Filling in File Number");
  NullErrorOut(WritePrivateProfileString("TopDir", szKeyName, szFileName, szFGLFileName), "InsertFileToGroup", "Adding File to File Group");
  return ++iFileNumber;
}


BOOL make_component_definition_path (char *path_string, char *project_path)
{
  strcpy(path_string, project_path);
  if (!PathAppend(path_string, "Component Definitions"))
    return FALSE;
  else
    return ((BOOL)PathAppend(path_string, "Default.cdf"));
}

BOOL make_component_internal_name (char *name_string, BUNDLE *bundle, COMPONENT *component)
{
  sprintf(name_string, "%s%d", bundle->bdl_name, component->cp_index);
  return(TRUE);
}


/*
** AddComponent
**
**   This routine adds a component to the InstallShield project in the 
** passed directory.
*/
BOOL AddComponent(char *szProjectPath,    // Path to the IS Pro Project
				  char *szComponentName,  // Internal name of the component
				  char *szDisplayName,    // Display name of the component
				  char *szInstallText,    // Text to display while copying files
				  char *szDescription,    // Text to describe the component
				  BOOL bVisible,          // Component visible to the end user?
				  BOOL bDefaultSelected,  // Default status of the component
				  char *szPreInstallHandler,
				  char *szPostInstallHandler,
				  char *szPreUninstallHandler,
				  char *szPostUninstallHandler,
				  unsigned char familyID,
				  unsigned char bundleID,
				  unsigned char componentIndex,
				  BOOL bTypical)
{
	char szCDFFileName[MAX_PATH];
	char szKeyName[KEY_NAME_LEN];
	static int iComponentNumber = 0;
	char szComponentGUID[MAX_PATH];

	/*
	** Construct the name of the component definitions file Default.cdf
	*/
	NullErrorOut(make_component_definition_path(szCDFFileName, szProjectPath), "AddComponent", "Making CDF path");

	/*
	** Now first add the component to the numbered components and top components list
	*/
	NullErrorOut(sprintf(szKeyName, "component%d", iComponentNumber), "AddComponent", "Filling in Component Number");
	NullErrorOut(WritePrivateProfileString("Components", szKeyName, szComponentName, szCDFFileName), "AddComponent", "Adding Component to Components List");
	NullErrorOut(WritePrivateProfileString("TopComponents", szKeyName, szComponentName, szCDFFileName), "AddComponent", "Adding Component to Components List");


	/*
	** Now add the component section
	*/
	NullErrorOut(WritePrivateProfileString(szComponentName, "OBJECT", NO, szCDFFileName), "AddComponent", "Setting Component Object Property to False");
	NullErrorOut(WritePrivateProfileString(szComponentName, "DESCRIPTION", szDescription, szCDFFileName), "AddComponent", "Setting Component Description Property to False");
	NullErrorOut(WritePrivateProfileString(szComponentName, "STATUS", szInstallText, szCDFFileName), "AddComponent", "Setting Component Status Property (text to display while copying) to False");
	if (bVisible == TRUE) {
		NullErrorOut(WritePrivateProfileString(szComponentName, "VISIBLE", YES, szCDFFileName), "AddComponent", "Setting Component Visible Property to Yes");
	} else {
		NullErrorOut(WritePrivateProfileString(szComponentName, "VISIBLE", NO, szCDFFileName), "AddComponent", "Setting Component Visible Property to No");
	}
	NullErrorOut(WritePrivateProfileString(szComponentName, "DISK", "ANYDISK", szCDFFileName), "AddComponent", "Setting Component Disk Property to Any Disk");
	NullErrorOut(WritePrivateProfileString(szComponentName, "FILENEED", "STANDARD", szCDFFileName), "AddComponent", "Setting Component File Need Property to Standard");
	NullErrorOut(WritePrivateProfileString(szComponentName, "INCLUDEINBUILD", YES, szCDFFileName), "AddComponent", "Setting Component Include in Build Property to True");
	NullErrorOut(WritePrivateProfileString(szComponentName, "PASSWORD", "", szCDFFileName), "AddComponent", "Setting Component Password Property to Blank");
	NullErrorOut(WritePrivateProfileString(szComponentName, "ENCRYPT", YES, szCDFFileName), "AddComponent", "Setting Component Encryption Property to True");
	NullErrorOut(WritePrivateProfileString(szComponentName, "COMPRESSIFSEPARATE", NO, szCDFFileName), "AddComponent", "Setting Component Separate Compression (?) Property to True");
	NullErrorOut(WritePrivateProfileString(szComponentName, "UNINSTALLABLE", YES, szCDFFileName), "AddComponent", "Setting Component Uninstallable Property to True");
	NullErrorOut(WritePrivateProfileString(szComponentName, "COMMENT", "", szCDFFileName), "AddComponent", "Setting Component Comment Property to Blank");
	if (bDefaultSelected == TRUE) {
		NullErrorOut(WritePrivateProfileString(szComponentName, "DEFSELECTION", YES, szCDFFileName), "AddComponent", "Setting Component Default Property to Yes");
		NullErrorOut(WritePrivateProfileString(szComponentName, "SELECTED", YES, szCDFFileName), "AddComponent", "Setting Component Selected Property to Yes");

	} else {
		NullErrorOut(WritePrivateProfileString(szComponentName, "DEFSELECTION", NO, szCDFFileName), "AddComponent", "Setting Component Default Property to No");
		NullErrorOut(WritePrivateProfileString(szComponentName, "SELECTED", NO, szCDFFileName), "AddComponent", "Setting Component Selected Property to No");
	}
	NullErrorOut(WritePrivateProfileString(szComponentName, "IMAGE", "", szCDFFileName), "AddComponent", "Setting Component Image Property to Blank");
	NullErrorOut(WritePrivateProfileString(szComponentName, "TARGETDIRCDROM", "", szCDFFileName), "AddComponent", "Setting Component CD Target Dir Property to Blank");
	NullErrorOut(WritePrivateProfileString(szComponentName, "DISPLAYTEXT", szDisplayName, szCDFFileName), "AddComponent", "Setting Component Visible Name Property to Blank");
	NullErrorOut(WritePrivateProfileString(szComponentName, "HTTPLOCATION", "", szCDFFileName), "AddComponent", "Setting Component HTTP Location Property to Blank");
	NullErrorOut(WritePrivateProfileString(szComponentName, "FTPLOCATION", "", szCDFFileName), "AddComponent", "Setting Component FTP Location Property to Blank");
	NullErrorOut(WritePrivateProfileString(szComponentName, "MISC", "", szCDFFileName), "AddComponent", "Setting Component Misc Property to Blank");

	// Generate GUID for Component Here, we use a template guid and then uniquely identify it
	// by family ID and bundle ID -- JW 8/29/00
	sprintf(szComponentGUID, "52b77ae4-4d16-11d4-9b38-7059%.3d%.2d%.3d", (int) familyID, (int) bundleID, (int) componentIndex);
	NullErrorOut(WritePrivateProfileString(szComponentName, "GUID", szComponentGUID, szCDFFileName), "AddComponent", "Setting Component Misc Property to Blank");

	NullErrorOut(WritePrivateProfileString(szComponentName, "_SPLIT_BEFORE", "", szCDFFileName), "AddComponent", "Setting Component ____ Property to Blank");
	NullErrorOut(WritePrivateProfileString(szComponentName, "_SPLIT_AFTER", "", szCDFFileName), "AddComponent", "Setting Component ____ Property to Blank");
	NullErrorOut(WritePrivateProfileString(szComponentName, "_DATAASFILES", "", szCDFFileName), "AddComponent", "Setting Component ____ Property to Blank");
	NullErrorOut(WritePrivateProfileString(szComponentName, "_NO_SPLIT", "", szCDFFileName), "AddComponent", "Setting Component ____ Property to Blank");
	NullErrorOut(WritePrivateProfileString(szComponentName, "_NO_SPLIT_BEFORE", "", szCDFFileName), "AddComponent", "Setting Component ____ Property to Blank");
	NullErrorOut(WritePrivateProfileString(szComponentName, "VOLATILE", "", szCDFFileName), "AddComponent", "Setting Component ____ Property to Blank");

	NullErrorOut(WritePrivateProfileString(szComponentName, "HANDLERONInstalling", szPreInstallHandler, szCDFFileName), "AddComponent", "Setting Component Pre-install handler Property");
	NullErrorOut(WritePrivateProfileString(szComponentName, "HANDLERONInstalled", szPostInstallHandler, szCDFFileName), "AddComponent", "Setting Component Post-install handler Property");
	NullErrorOut(WritePrivateProfileString(szComponentName, "HANDLERONUnInstalling", szPreUninstallHandler, szCDFFileName), "AddComponent", "Setting Component Pre-uninstall handler Property");
	NullErrorOut(WritePrivateProfileString(szComponentName, "HANDLERONUnInstalled", szPostUninstallHandler, szCDFFileName), "AddComponent", "Setting Component Post-uninstall handler Property");

	/*
	** Now insert the component into the setup types
	*/
	NullErrorOut(sprintf(szKeyName, "item%d", iComponentNumber), "AddComponent", "Filling in Component Item Number For Setup Type");
	
	// Add to the custom type and to the typical if marked. -- JW 9/7
	NullErrorOut(WritePrivateProfileString("SetupTypeItem-Custom", szKeyName, szComponentName, szCDFFileName), "AddComponent", "Inserting Component into Setup Type Custom");
	if (bTypical == TRUE) {
		NullErrorOut(WritePrivateProfileString("SetupTypeItem-Typical", szKeyName, szComponentName, szCDFFileName), "AddComponent", "Inserting Component into Setup Type Typical");
	}

	iComponentNumber++;
	return TRUE;

}







BOOL AddFileGroupToComponent(char *szProjectPath,    // Path to the IS Pro Project
							 char *szComponentName,  // Name of the component
							 char *szFileGroupName,   // Name of the file
							 BOOL bStartComponent) 
{
	char szCDFFileName[MAX_PATH];
	char szKeyName[KEY_NAME_LEN];
	static int iGroupNumberInComponent = 0;

	/*
	** Construct the name of the component definitions file Default.cdf
	*/
	NullErrorOut((long) strcpy(szCDFFileName, szProjectPath), "AddComponent", "Copying Project Path String to CDF Filename path");
    NullErrorOut(PathAppend(szCDFFileName, "Component Definitions"), "AddComponent", "Appending Component Definitions directory to Project Path String");
    NullErrorOut(PathAppend(szCDFFileName, "Default.cdf"), "AddComponent", "Appending Components File name to Project Path String");


	/*
	** Add to filegroup numbered list for component in CDF File
	*/
	if (bStartComponent)
		iGroupNumberInComponent = 0;

	NullErrorOut(sprintf(szKeyName, "filegroup%d", iGroupNumberInComponent), "AddComponent", "Filling in Component Item Number For Setup Type");
	NullErrorOut(WritePrivateProfileString(szComponentName, szKeyName, szFileGroupName, szCDFFileName), "AddFileGroupToComponent", "Adding File Group To Component");

	return ++iGroupNumberInComponent;
}



/* substitute_targetdir creates an InstallShield scripting language string
expression that corresponds to path, but with occurances of the string
<TARGETDIR> replaced by the global variable TARGETDIR.  This ultimately results
in a path value with the user-confirmed target directory substituted into the
resulting string.  Note that double-quotation marks are inserted as appropriate
but should not be in the argument path.  The matching on <TARGETDIR> is case
sensitive.

Examples:
   <TARGETDIR>x;<TARGETDIR>y
   => TARGETDIR + "x;" + TARGETDIR + "y"

   %SWING_HOME%\\swing.jar;<TARGETDIR>\\mhdtest1;\\foo\\bar\\<TARGETDIR>\\mhdtest2.baz;<TARGETDIR>
   => "%SWING_HOME%\\swing.jar;" + TARGETDIR + "\\mhdtest1;\\foo\\bar\\" + TARGETDIR + "\\mhdtest2.baz;" + TARGETDIR
   */

char *substitute_targetdir(char *path) 
{
  char target[] = "<TARGETDIR>";
  int target_length = strlen(target);
  char replacement[] = "TARGETDIR";
  char *result;
  char *remaining_path = path;
  char *position;

  if (path == "")
    return path;

  /* Note: result becomes garbage; 2X+1 here means: "more than enough space" */
  result = (char *)malloc(1 + (2 * strlen(path)));
  
  result[0] = NUL;
  while (position = strstr(remaining_path, target)) {
    if (position != path) {
      if (remaining_path != path)
	strcat(result, " + ");
      strcat(result, "\"");
      strncat(result, remaining_path, (position - remaining_path));
      strcat(result, "\" + ");
    }
    strcat(result, replacement);
    remaining_path = position + target_length;
  }
  if (remaining_path[0] != NUL) {
    if (remaining_path != path)
      strcat(result, " + ");
    strcat(result, "\"");
    strcat(result, remaining_path);
    strcat(result, "\"");
  }
  return(result);
}


void emit_one_env_var (FILE *scriptfile, ENV_VAR *env_var, char *key_var)
{
  int effect = env_var->ev_effect;
  char *function_name
    = ((effect == merge)
       ? "Create1EnvVarMergeStyle"
       : ((effect == append) ? "Create1EnvVarAppendStyle" : "Create1EnvVar"));
  
  fprintf(scriptfile, "  %s(%s, \"%s\", ", function_name, key_var, env_var->ev_component_name);
  fprintf(scriptfile, "\"%s\", ", env_var->ev_name);
  fprintf(scriptfile, "%s);\n", substitute_targetdir(env_var->ev_value));
}

/* Refer to bundle/tools/bundle.lisp, function make-obfuscation-seed-string.  Keep
   the following in synch with that. */

#define POSTINSTALL_OBFUSCATOR "set_log_file_info"
#define SEED_STRING_EXPRESSION "PRODUCT_GUID"
#define POSTINSTALL_TMP_STRING_VAR "TMP_STRING"


/* SEED_STRING_GLOBAL_VAR gives the name of an InstallShield global variable
   that is is declared in Setup.rul, initialized to the seed string in code
   emitted from here into BundleInfo.rul, and used in the code emitted below
   (into Renames.rul) for obfuscated files. */

#define SEED_STRING_GLOBAL_VAR "BUNDLE_OBFUSCATION_SEED_STRING"

void emit_one_rename (FILE *stream, RenameContainer *rename)
{
  char *target_dir = rename->szTargetDir;
  char *target_name = rename->szTargetName;
  char *source_name = rename->szSourceName;
  char source_path[MAX_PATH] = "";
  char target_path[MAX_PATH] = "";
  char format[MAX_PATH] = "";

  if (target_name != NULL) {
    strcpy(format, ((target_dir == NULL) ? "TARGETDIR^\"%s\"" : "TARGETDIR^\"%s\"^\"%s\""));
    if (target_dir != NULL) {
      sprintf(source_path, format, target_dir, source_name);
      sprintf(target_path, format, target_dir, target_name);
    } else {
      sprintf(source_path, format, source_name);
      sprintf(target_path, format, target_name);
    }
    strcpy(format, "  DeleteFile(%s);\n  RenameFile(%s, %s);\n");
    fprintf(stream, format, target_path, source_path, target_path);
  }
  if (rename->obfuscate)  {
    char *temp_string = NULL;
    if (target_name == NULL)
      temp_string = source_path;
    else
      temp_string = target_path;
    fprintf(stream, "  %s = %s;\n", POSTINSTALL_TMP_STRING_VAR, temp_string);
    fprintf(stream, "  %s(%s, %s);\n",
	    POSTINSTALL_OBFUSCATOR, POSTINSTALL_TMP_STRING_VAR, SEED_STRING_GLOBAL_VAR);
  }
}

/* get_component_rename finds the rename post-install function name, if any,
   associated with the component named by component_name.  If there is none, it
   returns the empty string ("").  The string returned when there's a match is
   freshly allocated (as by strdup), which the typical the caller should
   generally simply leak. */

char *get_component_rename(char *component_name, RenameContainer *pRenames)
{
  while (pRenames != NULL) {
    if (component_name == pRenames->szComponentName)
      return(strdup(rename_component_normalized_temp(pRenames->szComponentName)));
    pRenames = pRenames->next;
  }
  return("");
}



/*
** ComponentExists
**
** Check to see if the named component has already been created
** in the InstallShield project.
*/
BOOL ComponentExists(char *szProjectPath, char *szComponentName)
{
	char szCDFFileName[MAX_PATH];
	TCHAR szBuffer[20];

	/*
	** Construct the name of the component definitions file Default.cdf
	*/
	NullErrorOut((long) strcpy(szCDFFileName, szProjectPath), "ComponentExists", "Copying Project Path String to CDF Filename path");
    NullErrorOut(PathAppend(szCDFFileName, "Component Definitions"), "ComponentExists", "Appending Component Definitions directory to Project Path String");
    NullErrorOut(PathAppend(szCDFFileName, "Default.cdf"), "ComponentExists", "Appending Components File name to Project Path String");

	/*
	** Now see if the component section exists by seeing if we can read an entry from there.
	*/

	NullErrorOut(GetPrivateProfileString(szComponentName, "OBJECT", "TEST", szBuffer, 20, szCDFFileName), "ComponentExists", "Getting Component Object Property");

	if (strcmp(szBuffer, "TEST") == 0)
		return FALSE;
	else
		return TRUE;
	
}




/*
** AddRegistryEntries
**
**   This routine adds registry entries to the named file group in the 
** InstallShield project in the passed directory.
** 
** 
** Note that if we want to include the installation target location,
** we go back and fix it up later.  See tools.rul, function CorrectRegistryEntry
** The user should say "%ROOTDIR%" for their key value.
*/
BOOL AddRegistryEntries(char *szProjectPath,     // Path to the IS Pro Project
						PART *pPart)
{
	char szRGEFileName[MAX_PATH];
	char szKeyName[KEY_NAME_LEN];
	char szKeyValue[VALUE_STRING_LEN];
	char szSectionName[MAX_PATH];
	char *szTemp;
	int HKLM = 0, HKCU = 0, HKUS = 0, HKCR = 0;

	REGISTRATION *pRegEntries = pPart->pt_first_reg_object;
	/*
	** Construct the path to the FDF File which defines the file groups set
	*/
	NullErrorOut((long) strcpy(szRGEFileName, szProjectPath), "AddRegistryEntries", "Copying Project Path String to FDF Filename path");
    NullErrorOut(PathAppend(szRGEFileName, FILENAME_REGISTRY_RGE_FILE), "AddRegistryEntries", "Appending RGE Filename to Project Path String");
   
	/*
	** First make it one of the groups by inserting it into the group list and then add the generic
	** comment tag and the file group association.
	*/
	sprintf(szKeyName, KEY_NAME_REG_SET_NUMBER, iRegistrySetNumber);
	NullErrorOut(WritePrivateProfileString("Data", szKeyName, pRegEntries->rg_name, szRGEFileName), "AddRegistryEntries", "Inserting Registry Set Name To RGE File");
	NullErrorOut(WritePrivateProfileString(pRegEntries->rg_name, "---Comment---", "Automated", szRGEFileName), "AddRegistryEntries", "Inserting Registry Value To RGE File");
	NullErrorOut(WritePrivateProfileString(pRegEntries->rg_name, "---FileGroup0---", pPart->pt_name, szRGEFileName), "AddRegistryEntries", "Inserting Registry Value To RGE File");

	/*
	** Now all the one time entries are there, put in user entries.
	*/
	while (pRegEntries != NULL) {

		/*
		** Now write out the first registry section
		*/
		if ((szTemp = strstr(pRegEntries->rg_path, "HKEY_LOCAL_MACHINE\\")) != NULL) {
		  //Now adjust szTemp by the length of the key, as we don't include the toplevel key.
		  szTemp+=strlen("HKEY_LOCAL_MACHINE\\");
			strcpy(szKeyValue, szTemp);
			sprintf(szKeyName, "HKLM%d", HKLM);
			HKLM++;
			sprintf(szSectionName, "%s:%s:%s", pRegEntries->rg_name, "HKLM", szKeyValue);
		} else if ((szTemp = strstr(pRegEntries->rg_path, "HKEY_CURRENT_USER\\")) != NULL) {
		  szTemp+=strlen("HKEY_CURRENT_USER\\");
			strcpy(szKeyValue, szTemp);
			sprintf(szKeyName, "HKCU%d", HKCU);
			HKCU++;
			sprintf(szSectionName, "%s:%s:%s", pRegEntries->rg_name, "HKCU", szKeyValue);
		} else if ((szTemp = strstr(pRegEntries->rg_path, "HKEY_USERS\\")) != NULL) {
		  szTemp+=strlen("HKEY_USERS\\");
			strcpy(szKeyValue, szTemp);
			sprintf(szKeyName, "HKUS%d", HKUS);
			HKUS++;
			sprintf(szSectionName, "%s:%s:%s", pRegEntries->rg_name, "HKUS", szKeyValue);
		} else { //Defaulting to HKEY_CLASSES_ROOT.
		  szTemp+=strlen("HKEY_CLASSES_ROOT\\");
			strcpy(szKeyValue, szTemp);
			sprintf(szKeyName, "HKCR%d", HKCR);
			HKCR++;
			sprintf(szSectionName, "%s:%s:%s", pRegEntries->rg_name, "HKCR", szKeyValue);
		}
		NullErrorOut(WritePrivateProfileString(pRegEntries->rg_name, szKeyName, szKeyValue, szRGEFileName), "AddRegistryEntries", "Inserting Registry Value To RGE File");

		NullErrorOut(WritePrivateProfileString(szSectionName, "---Shared---", NO, szRGEFileName), "AddRegistryEntries", "Inserting Registry Value To RGE File");
		NullErrorOut(WritePrivateProfileString(szSectionName, "---Comment---", "Automated", szRGEFileName), "AddRegistryEntries", "Inserting Registry Value To RGE File");
		NullErrorOut(WritePrivateProfileString(szSectionName, "(Default)", "S,", szRGEFileName), "AddRegistryEntries", "Inserting Registry Value To RGE File");
		sprintf(szKeyValue, "S,%s", pRegEntries->rg_value);
		NullErrorOut(WritePrivateProfileString(szSectionName, pRegEntries->rg_key_name, szKeyValue, szRGEFileName), "AddRegistryEntries", "Inserting Registry Value To RGE File");

		pRegEntries = pRegEntries->rg_next_reg_object;
	}

	++iRegistrySetNumber;
	return TRUE;
}


/*
** AddShortcuts
**
**   This routine adds registry entries to the named file group in the 
** InstallShield project in the passed directory.
*/

/* To avoid complications with double quotes and/or bugs in IS, for the
   forseeable future, we will live with the constraint that spaces may not be
   used in our directory or file names, at least those used in shortcuts. It is
   fine if they exist within <TARGETDIR> -- IS handles that. -mhd, 9/13/00 */

/* Note: icon file name must be absolute in IS, but we make it relative to the
   working directory, since that should be most convenient for our
   purposes. -mhd, 9/24/00 */

/* mhd, 12/3/00 - variable name changes:
   szSHLFileName => shell_file_name
   szKeyName => key_name
   szKeyValue => key_value
   szFolderName => folder_name
   szShortcutName => shortcut_name
*/

#define AS_szRoutine "AddShortcuts"
#define AS_Emit(a, b, c, szTask) NullErrorOut(WritePrivateProfileString(a, b, c, shell_file_name), AS_szRoutine, szTask)

/* Note: the value of the following constant is based on the current
   internal format of the InstallShield 6.x Default.shl file, based on
   inspection. */
#define PROGRAMS_SC_FOLDER "Folder2"


/* create_sc_folder_if_nec sets key_name have the text of the key name
   corresponding to the program folder the shortcuts to into.  The arg
   superfolder_or_null should be NULL if this goes at "top level" in
   the IS Programs shell object; otherwise, the name of the folder
   this goes under.  This has no value, and is called for side effect
   on the project file shell_file_name, and for setting the contents
   of character setring key_name. */

void create_sc_folder_if_nec(char *key_name, char *superfolder_name,
			     char *display_text, SHORTCUT *sc,
			     char *shell_file_name)
{
  char key_value[VALUE_STRING_LEN];
  char folder_name[MAX_PATH];
  int i;
  BOOL folder_set = FALSE;
  
  for (i = 1; folder_set == FALSE; i++) {
    sprintf(key_name, "Folder%d", i);
    GetPrivateProfileString("Data", key_name, "NOVAL", key_value, VALUE_STRING_LEN, shell_file_name);
    if (strcmp(key_value, "NOVAL") == 0) {
      sprintf(key_value, "%s\\%s", superfolder_name, display_text);
      AS_Emit("Data", key_name, key_value, "Adding New Folder to Shortcuts");
      AS_Emit(key_name, "Comments", "", "Adding comments to Shortcuts Folder");
      AS_Emit(key_name, "DisplayText", display_text, "Adding display text to Shortcuts Folder");
      AS_Emit(key_name, "Shared", NO, "Adding Shared property to Shortcuts Folder");
      folder_set = TRUE;
    } else {				
      sprintf(folder_name, "%s\\%s", superfolder_name, display_text);
      if ( (strcmp (key_value, folder_name) == 0) ||  
	   (strcmp(key_value, display_text) == 0) ) {
	folder_set = TRUE;
      }
    }
  }
}

/* get_next_shortcut_key_name fills in key_name with the desired next
available shortcut name, i.e., the first one of Shortcut0, Shortcut1,
etc., that does not yet exist.  This will then be used to associate
various data with the shortcut. This returns no value; it's just
called to set the characters in argument key_name. */

void get_next_shortcut_key_name(char *key_name, SHORTCUT *sc, char *shell_file_name)
{
  char key_value[VALUE_STRING_LEN];
  int i = 0;
  BOOL shortcut_set = FALSE;
  while (shortcut_set == FALSE) {
    sprintf(key_name, "Shortcut%d", i);
    GetPrivateProfileString("Data", key_name, "NOVAL", key_value, VALUE_STRING_LEN, shell_file_name);
    if (strcmp (key_value, "NOVAL") == 0)
      shortcut_set = TRUE;
    else
      i++;
  }
}


void link_in_shortcut (char *folder_name, char *key_name,
		       SHORTCUT *sc, char *shell_file_name,
		       char *szFileGroup)     
{
  BOOL http_shortcut = FALSE;
  char shortcut_name[MAX_PATH],
    szDirectory[MAX_PATH], szShortcutPath[MAX_PATH], szParameters[MAX_PATH],
    szIconPath[MAX_PATH], szIconIndex[MAX_PATH];

  sprintf(shortcut_name, "%s\\%s", folder_name, sc->sc_display_name);
  AS_Emit("Data", key_name, shortcut_name, "Adding Shortcut to Shortcuts Folder");

  AS_Emit(key_name, "DisplayText", sc->sc_display_name, "Adding Shortcut display name to Shortcut");

  backslashify_in_place(sc->sc_directory);

  sprintf(szDirectory, ((sc->sc_directory == "") ? "<TARGETDIR>" : "<TARGETDIR>\\%s"),
	  sc->sc_directory);
  /* Bit of a kluge here, checking for http, but we don't want to prepend the
     target dir if so. */
  if (strncmp(sc->sc_target_name, "http://",7) != 0) {
    sprintf(szShortcutPath, ((sc->sc_target_name == "") ? "%s" : "%s\\%s"),
	    szDirectory, sc->sc_target_name);
  } else {
    sprintf(szShortcutPath, "%s", sc->sc_target_name);
    http_shortcut = TRUE;
  }
  sprintf(szParameters, "%s", ((sc->sc_parameters != NULL) ? sc->sc_parameters : ""));
    
  AS_Emit(key_name, "StartIn", szDirectory, "Adding Shortcut startup dir to Shortcut");
  AS_Emit(key_name, "Target", szShortcutPath, "Adding Shortcut target to Shortcut");    
  AS_Emit(key_name, "Parameters", szParameters, "Adding Parameters to Shortcut");
    
  AS_Emit(key_name, "ShortcutKey", "", "Adding Shortcut key to Shortcut");
  AS_Emit(key_name, "Run",
	  ((sc->sc_run_style == minimized) ? "Minimized Window" : "Normal Window"),
	  "Adding Run Style (Minimized or Normal) to Shortcut");

  if (sc->sc_icon_file != NULL) {
    sprintf(szIconPath, "%s\\%s", szDirectory, sc->sc_icon_file);
    sprintf(szIconIndex, "%d", sc->sc_icon_index);
  }
  else
    strcpy(szIconIndex, strcpy(szIconPath, ""));
  AS_Emit(key_name, "IconFile", szIconPath, "Adding Shortcut icon file to Shortcut");
  AS_Emit(key_name, "IconIndex", szIconIndex, "Adding Shortcut icon index to Shortcut");
    
  AS_Emit(key_name, "Replace", YES, "Adding Shortcut replace property to Shortcut");
  AS_Emit(key_name, "SeparateMemorySpace", NO, "Adding Shortcut separate memory space flag to Shortcut");
  if (http_shortcut)
    AS_Emit(key_name, "InternetShortcut", YES, "Adding Shortcut internet shortcut flag (yes) to Shortcut");
  else
    AS_Emit(key_name, "InternetShortcut", NO, "Adding Shortcut internet shortcut flag (no) to Shortcut");
  AS_Emit(key_name, "Uninstall", YES, "Adding Shortcut uninstall flag to Shortcut");
  AS_Emit(key_name, "Type",
	  ((sc->sc_type == common)
	   ? "Common" : ((sc->sc_type == personal) ? "Personal" : "Automatic")),
	  "Adding Shortcut flag (Common, Personal, or Automatic) to Shortcut");
  AS_Emit(key_name, "Comments", "", "Adding Shortcut comments to Shortcut");
  AS_Emit(key_name, "FileGroup0", szFileGroup, "Adding Shortcut File Group Association to Shortcut");
}


/* add_one_shortcut: create the folder if necessary, or figure out
   which folder number it is in the file if it was already created.
   If there's a subfolder, then make it the subfolder of the folder.
   If there's a subsubfolder, then make it the subfolder of the
   subfolder.  I.e., there are at most three levels, but that's about
   the most you'd ever want.  Then get the next key_name available to
   link in this shortcut.  Then link in the shortcut. */

void add_one_shortcut (SHORTCUT *sc, char *shell_file_name, char *szFileGroup)
{
  char folder_name[MAX_PATH], key_name[KEY_NAME_LEN],
    superfolder_name[MAX_PATH];
  
  create_sc_folder_if_nec(folder_name, PROGRAMS_SC_FOLDER, sc->sc_folder,
			  sc, shell_file_name);
  if (sc->sc_subfolder != NULL) {
    strcpy(superfolder_name, folder_name);
    create_sc_folder_if_nec(folder_name, superfolder_name,
			    sc->sc_subfolder, sc, shell_file_name);
  }
  if (sc->sc_subsubfolder != NULL) {
    strcpy(superfolder_name, folder_name);
    create_sc_folder_if_nec(folder_name, superfolder_name,
			    sc->sc_subsubfolder, sc, shell_file_name);
  }
  get_next_shortcut_key_name(key_name, sc, shell_file_name);
  link_in_shortcut(folder_name, key_name, sc, shell_file_name, szFileGroup);
}


BOOL AddShortcuts(char *szProjectPath,  /* Path to the IS Pro Project */
		  char *szFileGroup,    /* File Group Name */
		  SHORTCUT *pShortcuts)	/* Shortcuts linked list */
{
  char shell_file_name[MAX_PATH];
  SHORTCUT *sc;
  
  /* Construct the path to the FDF File which defines the file groups
  set. */
  NullErrorOut((long) strcpy(shell_file_name, szProjectPath), AS_szRoutine,
	       "Copying Project Path String to SHL Filename path");
  NullErrorOut(PathAppend(shell_file_name, FILENAME_SHORTCUTS_SHL_FILE), AS_szRoutine,
	       "Appending SHL Filename to Project Path String");

  for (sc = pShortcuts; sc != NULL; sc = sc->sc_next_shortcut)
    add_one_shortcut (sc, shell_file_name, szFileGroup);

  return TRUE;
}

#undef AS_Emit
#undef AS_szRoutine
#undef PROGRAMS_SC_FOLDER

void generate_check_for_previous_installations (FILE *fScriptFile, FAMILY_DESCRIPTOR *family)
{
  PREV_VERSION *pv;
  fprintf(fScriptFile, "\n\nfunction generated_check_for_previous_installations ()\nbegin\n");
  for (pv = family->fd_prev_versions; pv != NULL; pv = pv->pv_next)
    fprintf(fScriptFile,
	    "  disallow_previous_install(\"%s\", \"*\", @PRODUCT_NAME, \"%s\");\n",
	    pv->pv_guid, pv->pv_version);
  fprintf(fScriptFile, "end;\n");
}


BOOL WriteBundleInfo(char *szProjectPath, FAMILY_DESCRIPTOR *family, int system_id)
{
	char szScriptFileName[MAX_PATH], szLine[1024];
	FILE *fScriptFile;
	char *szFamilyDir = family->fd_directory_name;
	BUNDLE *pBundles = family->fd_first_bundle;

	/*
	** First create the bundle dir and version resolution script file.
	*/
	NullErrorOut((long) strcpy(szScriptFileName, szProjectPath), "WriteBundleDirs", "Copying Project Path String to Script Filename path");
	NullErrorOut(PathAppend(szScriptFileName, "Script Files"), "WriteBundleDirs", "Appending Scripts directory to Project Path String");
	NullErrorOut(PathAppend(szScriptFileName, "BundleInfo.rul"), "WriteBundleDirs", "Appending Script File name to Project Path String");

	NullErrorOut( ((fScriptFile = fopen(szScriptFileName, "wt")) != 0), "WriteBundleDirs", "Creating new script file");

	/* write out init_bundle_installer_version:  (New. -mhd, 1/19/01)
	 -- added seed string. -mhd, 5/23/01 */
	fprintf(fScriptFile,
		"\nfunction init_bundle_installer_version()\nbegin\n  BUNDLE_INSTALLER_VERSION = \"%s\";\n  BUNDLE_FAMILY_ID = %d;\n  BUNDLE_SYSTEM_ID = %d;\n  %s = %s;\nend;\n\n",
		BUNDLE_INSTALLER_VERSION,
		family->fd_id,
		system_id, /* now we write system ID (0 or 8 on Windows) to IS project. --binghe, 2015/11/30 */
		SEED_STRING_GLOBAL_VAR, SEED_STRING_EXPRESSION);

	NullErrorOut( ((fprintf(fScriptFile, "function SetBundleDirAndVersion(BundleID)\nbegin\n")) > 0), "WriteBundleDirs", "Writing initial function section");

	NullErrorOut( ((fprintf(fScriptFile, "  switch(BundleID)\n")) > 0), "WriteBundleDirs", "Writing switch statement");
	while (pBundles != NULL) {
		if (!(pBundles->bdl_os_availability && INTELNT_CODE)) {
			sprintf(szLine, "   case %d:\n", (int)(pBundles->bdl_id));
			NullErrorOut( ((fprintf(fScriptFile, szLine)) > 0), "WriteBundleDirs", "Writing bundle case");
			sprintf(szLine, "    if (!MAINTENANCE) then TARGETDIR = PROGRAMFILES^\"Gensym\"^\"%s\"; endif;\n",
				szFamilyDir);
			NullErrorOut( ((fprintf(fScriptFile, szLine)) > 0), "WriteBundleDirs", "Writing bundle install dir");
			sprintf(szLine, "    BUNDLEVERSION = \"%s\";\n", pBundles->bdl_version);
			NullErrorOut( ((fprintf(fScriptFile, szLine)) > 0), "WriteBundleDirs", "Writing bundle version");
			sprintf(szLine, "    BUNDLENAME = \"%s\";\n", pBundles->bdl_name);
			NullErrorOut( ((fprintf(fScriptFile, szLine)) > 0), "WriteBundleDirs", "Writing bundle version");
			sprintf(szLine, "    BUNDLE_TYPICAL_ONLY = %s;\n", (pBundles->bdl_typical_only ? "TRUE" : "FALSE"));
			NullErrorOut( ((fprintf(fScriptFile, szLine)) > 0), "WriteBundleDirs", "Writing BUNDLE_TYPICAL_ONLY setter");
		}
		pBundles = pBundles->bdl_next_bundle;
	}

	sprintf(szLine, "   default: TARGETDIR = PROGRAMFILES^\"Gensym\"^\"%s\";\n", szFamilyDir);
	NullErrorOut( ((fprintf(fScriptFile, szLine)) > 0), "WriteBundleDirs", "Writing default install dir");
	NullErrorOut( ((fprintf(fScriptFile, "    BUNDLEVERSION = \"1.0\";\n")) > 0), "WriteBundleDirs", "Writing default bundle version");
        sprintf(szLine, "    BUNDLENAME = \"%s\";\n", "default");
        NullErrorOut( ((fprintf(fScriptFile, szLine)) > 0), "WriteBundleDirs", "Writing bundle version");

	
	NullErrorOut( ((fprintf(fScriptFile, "    BUNDLE_TYPICAL_ONLY = FALSE;\n")) > 0), "WriteBundleDirs", "Writing default BUNDLE_TYPICAL_ONLY");

	NullErrorOut( ((fprintf(fScriptFile, "  endswitch;\n")) > 0), "WriteBundleDirs", "Writing initial function section");
	
	NullErrorOut( ((fprintf(fScriptFile, "end;\n")) > 0), "WriteBundleDirs", "Writing initial function section");
	
	generate_check_for_previous_installations(fScriptFile, family);

	fclose(fScriptFile);


	return TRUE;
}



/*
** MakeWatermarks
**
** Create an InstallScript routine called "DoWatermarks" in the watermarks.rul
** file to create the watermarks after installing.
*/
BOOL MakeWatermarks(char *szProjectPath,
					WatermarkContainer *pWatermarks)
{
	char szScriptFileName[MAX_PATH];
	FILE *fScriptFile;
	char szLine[MAX_PATH];

    /*
	** First create the script file and begin the function.
	*/
	NullErrorOut((long) strcpy(szScriptFileName, szProjectPath), "MakeWatermarks", "Copying Project Path String to Script Filename path");
    NullErrorOut(PathAppend(szScriptFileName, "Script Files"), "MakeWatermarks", "Appending Scripts directory to Project Path String");
    NullErrorOut(PathAppend(szScriptFileName, "Watermarks.rul"), "MakeWatermarks", "Appending Script File name to Project Path String");

	NullErrorOut( ((fScriptFile = fopen(szScriptFileName, "wt")) != 0), "MakeWatermarks", "Creating new script file");
	NullErrorOut( ((fprintf(fScriptFile, "function DoWatermarks()\n  STRING szOKFile,szTemp;\nbegin\n  VarSave(SRCTARGETDIR);\n\n")) > 0), "MakeWatermarks", "Writing initial function section");

	
	sprintf(szLine,"%s","    Sprintf(szOKFile,\"%s\", TARGETDIR);\n");
	NullErrorOut( ((fprintf(fScriptFile,"%s", szLine)) > 0), "MakeWatermarks", "Writing out watermark file path with delimiter");
	/*now and code to test if there is a \\ at the end of the target directory, add one if not.*/
	NullErrorOut( ((fprintf(fScriptFile,"  StrSub(szTemp,szOKFile, StrLength(szOKFile) - 1, 1);\n")) > 0), "MakeWatermarks", "Writing check for directory delimiter");

	NullErrorOut( ((fprintf(fScriptFile,"  if (StrCompare(\"\\\\\", szTemp)!= 0) then\n")) > 0), "MakeWatermarks", "Writing check for directory delimiter");


	sprintf(szLine,"%s", "    szOKFile = szOKFile + \"\\\\\";\n");
	NullErrorOut( ((fprintf(fScriptFile,"%s", szLine)) > 0), "MakeWatermarks", "Writing out watermark file path");

	NullErrorOut( ((fprintf(fScriptFile, "  endif;\n")) > 0), "MakeWatermarks", "Writing endif for directory delimiter check");


	NullErrorOut( ((fprintf(fScriptFile, "  make_watermark_file(szOKFile, BUNDLENAME, sgName, sgCompany, sgRegNumber);\n\n")) > 0), "RenameFiles", "Writing out watermark call");

	/*
	** Now cycle through all the watermark ok files 
	*/
	while (pWatermarks!= NULL) {

		NullErrorOut( ((fprintf(fScriptFile, "  if ComponentIsItemSelected(MEDIA, \"%s\") then\n", pWatermarks->szComponentName)) > 0), "MakeWatermarks", "Writing out component conditional watermark (if)");
		sprintf(szLine, "    szOKFile = TARGETDIR ^ \"%s\";\n", pWatermarks->szWatermarkFile);
		NullErrorOut( ((fprintf(fScriptFile, szLine)) > 0), "MakeWatermarks", "Writing out watermark file path");
		NullErrorOut( ((fprintf(fScriptFile, "    add_watermark_to_ok_file(szOKFile, BUNDLENAME, sgName, sgCompany, sgRegNumber);\n")) > 0), "RenameFiles", "Writing out watermark call");
		NullErrorOut( ((fprintf(fScriptFile, "  endif;\n\n")) > 0), "RenameFiles", "Writing out endif");
		pWatermarks = pWatermarks->next;
	};

	NullErrorOut( ((fprintf(fScriptFile, "end;\n\n")) > 0), "MakeWatermarks", "Writing end of function section");
	NullErrorOut( (fclose(fScriptFile) == 0), "MakeWatermarks", "Closing Script File");
	return(TRUE);
}




/*
** FileGroupExists
**
** Check to see if the named File Group has already been created
** in the InstallShield project.
*/
BOOL FileGroupExists(char *szProjectPath, char *szFileGroupName)
{
	char szFDFFileName[MAX_PATH];
	char szKeyValue[VALUE_STRING_LEN];

	/*
	** Construct the path to the FDF File which defines the file groups set
	*/
	NullErrorOut((long) strcpy(szFDFFileName, szProjectPath), "AddFileGroup", "Copying Project Path String to FDF Filename path");
    NullErrorOut(PathAppend(szFDFFileName, FILENAME_FILEGROUP_FDF_FILE), "AddFileGroup", "Appending FDF Filename to Project Path String");
   
	/*
	** Now try to read from the section for that group in the file.
	*/ 
	GetPrivateProfileString(szFileGroupName, "LINKTYPE", "TEST", szKeyValue, VALUE_STRING_LEN, szFDFFileName);
	if (strcmp(szKeyValue, "TEST") == 0) {
		return FALSE;
	} else {
		return TRUE;
	}
}












FILE *begin_postinstall_scriptfile(char *project_path)
{
  char file_name[MAX_PATH];
  FILE *scriptfile;
  struct stat     s;
  int file_exists;

  strcpy(file_name, project_path);
  PathAppend(file_name, "Script Files");
  PathAppend(file_name, "renames.rul");



  file_exists = stat(file_name,&s);
  scriptfile =  fopen(file_name, "at");
  if (scriptfile != NULL && file_exists == -1)
    fprintf(scriptfile,
	    "// This script file was generated by the Gensym Install Generator.\n// It does file-renaming and environment-variable-setting as required per component.\n");
  return(scriptfile);
}


void end_postinstall_scriptfile(FILE *scriptfile)
{
  fclose(scriptfile);
}





char install_function_name_buffer[MAX_PATH] = "";

typedef enum {POST,PRE,UN} INSTALLMODIFIER;

char *install_function_name(char *component_name, INSTALLMODIFIER how)
{
  char *comp = rename_component_normalized_temp(component_name);

  install_function_name_buffer[0] = NUL;
  switch (how) {
    case POST:
      sprintf(install_function_name_buffer, "%s_Installed", comp);
      break;
    case PRE:
      sprintf(install_function_name_buffer, "%s_Installing", comp);
      break;
    case UN:
      sprintf(install_function_name_buffer, "%s_UnInstalling", comp);
      break;
  }
  return(install_function_name_buffer);
}





void begin_install_function(FILE *scriptfile, char *cdf_path, char *component_name,
				BUNDLE *bundle, COMPONENT *component, char *key_var, INSTALLMODIFIER how)
{
  char *function_name = install_function_name(component_name,how);
  
  switch (how) {
    case POST:
      WritePrivateProfileString(component_name, "HANDLERONInstalled", function_name, cdf_path);
      break;
    case PRE:
      WritePrivateProfileString(component_name, "HANDLERONInstalling", function_name, cdf_path);
      break;
    case UN:
      WritePrivateProfileString(component_name, "HANDLERONUnInstalling", function_name, cdf_path);
      break;
  }
  
  fprintf(scriptfile,
	  "\n// %s: %s (%d)\nexport prototype %s();\nfunction %s()\n",
	  bundle->bdl_name, component->cp_name, component->cp_index,
	  function_name, function_name);
  fprintf(scriptfile, "STRING %s;\n", POSTINSTALL_TMP_STRING_VAR);
  fprintf(scriptfile, ((key_var == NULL) ? "begin\n" : "STRING %s;\nbegin\n"), key_var);
}

void end_install_function (FILE *scriptfile, char *component_name, INSTALLMODIFIER how)
{
  char *function_name = install_function_name(component_name,how);
  
  fprintf(scriptfile, "end;  // %s\n\n", function_name);
}

char * DoubleSlashify(char * input)
{
  int i,o,len;
  char * output;

  len = strlen(input);

  output = (char *)malloc(len*2+1);

  o = 0;
  for (i = 0; i < len; i++) {
    output[o] = input[i];
    o++;
    if (input[i] == '\\') {
      output[o] = '\\';
      o++;
    }
  }
  output[o]='\0';
  return output;
}


void write_postinstall_per_component(char *project_path, FAMILY_DESCRIPTOR *family,
				     RenameContainer *rename_data,
				     ENV_VAR *environment_data)
{
  BUNDLE *b;
  COMPONENT *c;
  FILE *scriptfile;
  char cdf_path[MAX_PATH];
  

  scriptfile = begin_postinstall_scriptfile(project_path);
  make_component_definition_path(cdf_path, project_path);
  for (b = family->fd_first_bundle; b != NULL; b = b->bdl_next_bundle)
    if (!(b->bdl_os_availability & (0x1)))
      for (c = b->bdl_first_component; c != NULL; c = c->cp_next_component) {
	BOOL function_is_started = FALSE;
	BOOL envvars_started = FALSE;
	char *key_var = "key";
	ENV_VAR *ev;
	RenameContainer *r;
	char component_name[MAX_PATH];
	    
	make_component_internal_name(component_name, b, c);
	for (ev = environment_data; ev != NULL; ev = ev->ev_next_env_var)
	  if (!(strcmp(ev->ev_component_name, component_name))) {
	    if (!function_is_started) {
	      begin_install_function(scriptfile, cdf_path, component_name, b, c, key_var, POST);
	      function_is_started = TRUE;
	    }
	    if (!envvars_started) {
	      fprintf(scriptfile, "  set_environment_registry_key(%s);\n", key_var);
	      envvars_started = TRUE;
	    }
	    emit_one_env_var(scriptfile, ev, key_var);
	  }
	for (r = rename_data; r != NULL; r = r->next)
	  if (!(strcmp(r->szComponentName, component_name))) {
	    if (!function_is_started) {
	      begin_install_function(scriptfile, cdf_path, component_name, b, c, NULL, POST);
	      function_is_started = TRUE;
	    }
	    emit_one_rename(scriptfile, r);
	  }
	{
	  /* loop over the parts of component, dumping out any of the
	     (rare) postinstall code, each of which must be one or
	     more statements on a single (separated by ;'s) */
	  PART *p;
	  for (p = c->cp_first_part; p != NULL; p = p->pt_next_part) {
	    if (((p->pt_postinstall_code != NULL) || p->pt_first_reg_object != NULL) && available_on_os(p, INTELNT_CODE)) {
	      if (!function_is_started) {
		begin_install_function(scriptfile, cdf_path, component_name, b, c, NULL, POST);
		function_is_started = TRUE;
	      }
	      if (p->pt_postinstall_code != NULL)
		fprintf(scriptfile, "  %s\n", p->pt_postinstall_code);
	      if (p->pt_first_reg_object != NULL) {
		REGISTRATION *pRegEntries = p->pt_first_reg_object;
		char * szTemp;
		while (pRegEntries != NULL) {
		  if ((szTemp = strstr(pRegEntries->rg_path, "HKEY_LOCAL_MACHINE\\")) != NULL) {
		    //Now adjust szTemp by the length of the key, as we don't include the toplevel key.
		    szTemp+=strlen("HKEY_LOCAL_MACHINE\\");
		    fprintf(scriptfile, "  CorrectRegistryEntry(HKEY_LOCAL_MACHINE,\"%s\");\n", DoubleSlashify(szTemp));
		  }
		  pRegEntries = pRegEntries->rg_next_reg_object;
		}
	      }
	    }
	  }
	}
	    
	if (function_is_started)
	  end_install_function(scriptfile, component_name, POST);
      }
  end_postinstall_scriptfile(scriptfile);
}


void write_preinstall_per_component(char *project_path, FAMILY_DESCRIPTOR *family)
{
  BUNDLE *b;
  COMPONENT *c;
  PART *p;
  FILE *scriptfile;
  char cdf_path[MAX_PATH];

  scriptfile = begin_postinstall_scriptfile(project_path);
  make_component_definition_path(cdf_path, project_path);
  for (b = family->fd_first_bundle; b != NULL; b = b->bdl_next_bundle)
    if (!(b->bdl_os_availability & (0x1)))
      for (c = b->bdl_first_component; c != NULL; c = c->cp_next_component) {
	BOOL function_is_started = FALSE;
	char component_name[MAX_PATH];
	make_component_internal_name(component_name, b, c);
	/* loop over the parts of component, dumping out any of the
	   (very rare) preinstall code, each of which must be one or
	   more statements on a single (separated by ;'s) */
	for (p = c->cp_first_part; p != NULL; p = p->pt_next_part) {
	  if ((p->pt_preinstall_code != NULL) && available_on_os(p, INTELNT_CODE)) {
	    if (!function_is_started) {
	      begin_install_function(scriptfile, cdf_path, component_name, b, c, NULL, PRE);
	      function_is_started = TRUE;
	    }
	    if (p->pt_preinstall_code != NULL)
	      fprintf(scriptfile, "  %s\n", p->pt_preinstall_code);
	  }
	}
	if (function_is_started)
	  end_install_function(scriptfile, component_name, PRE);
      }
  end_postinstall_scriptfile(scriptfile);
}


void write_uninstall_per_component(char *project_path, FAMILY_DESCRIPTOR *family)
{
  BUNDLE *b;
  COMPONENT *c;
  FILE *scriptfile;
  PART *p;
  char cdf_path[MAX_PATH];

  scriptfile = begin_postinstall_scriptfile(project_path);
  make_component_definition_path(cdf_path, project_path);
  for (b = family->fd_first_bundle; b != NULL; b = b->bdl_next_bundle)
    if (!(b->bdl_os_availability & (0x1)))
      for (c = b->bdl_first_component; c != NULL; c = c->cp_next_component) {
	BOOL function_is_started = FALSE;
	char component_name[MAX_PATH];
	make_component_internal_name(component_name, b, c);
	/* loop over the parts of component, dumping out any of the
	   (very rare) uninstall code, each of which must be one or
	   more statements on a single (separated by ;'s) */
	for (p = c->cp_first_part; p != NULL; p = p->pt_next_part) {
	  if ((p->pt_uninstall_code != NULL) && available_on_os(p, INTELNT_CODE)) {
	    if (!function_is_started) {
	      begin_install_function(scriptfile, cdf_path, component_name, b, c, NULL, UN);
	      function_is_started = TRUE;
	    }
	    if (p->pt_uninstall_code != NULL)
	      fprintf(scriptfile, "  %s\n", p->pt_uninstall_code);
	  }
	}
	if (function_is_started)
	  end_install_function(scriptfile, component_name, UN);
      }
  end_postinstall_scriptfile(scriptfile);
}
