/*
**  This file contains the definitions for routines and constants used to
** modify the InstallShield Pro 6.2 project files.  The routines herein 
** will be called in the course of walking the family descriptor tree to
** create an InstallShield project from the family description. 
**                                             -- Jim Wright, 7/11/00
*/

#include "family-file-reader.h"

typedef struct RenameContainer {
	char *szTargetDir;
	char *szSourceName;
	char *szTargetName;
	char *szComponentName;
        BOOL obfuscate;
	struct RenameContainer *next;
} RenameContainer;

typedef struct WatermarkContainer {
	char *szWatermarkFile;
	char *szComponentName;
	struct WatermarkContainer *next;
} WatermarkContainer;

/*
** AddComponent - Add a component to the InstallShield project.
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
				  BOOL bTypical);


/*
** AddFileGroup - Add a File Group to the InstallShield project.
*/ 
BOOL AddFileGroup(char *szProjectPath,     // Path to the IS Pro Project
				  char *szFileGroupName,   // The name of the File Group
				  BOOL bSelfRegistering,   // Self registering files?
				  BOOL bIsDynamic,         // Dynamic or static file group?
				  BOOL bIsShared,          // Shared files?
				  BOOL bPotentiallyLocked, // Potentially Locked files?
				  char *szSourcePath,      // Source files directory for dynamic groups
				  char *szTargetPath);     // Target directory under primary directory



/*
** InsertFileToGroup - Add a File to the named static File Group in the 
** InstallShield project.
*/ 
BOOL InsertFileToGroup(char *szProjectPath,    // Path to the IS Pro Project
					   char *szFileGroupName,  // The name of the File Group
				       char *szFileName,       // Name of the file to add
					   BOOL bStartGroup);      // First file in a new group?





/*
** AddFileGroupToComponent - Include the given File Group in the given 
** Component in InstallShield project in the current directory.
*/ 
BOOL AddFileGroupToComponent(char *szProjectPath,    // Path to the IS Pro Project
							 char *szComponentName,  // Name of the component
							 char *szFileGroupName,  // Name of the file
							 BOOL bStartComponent);  // Starting a new list of file groups for the component?


/*
** backslashify_in_place
**
** Change / to \ in str.
*/
void backslashify_in_place(char *str);

/*
** remove_trailing_slash_in_place
**
** Remove trailing forward or backward slash, if any, from the end of str:
**   filename/, filename\, or filename => filename
*/
void remove_trailing_slash_in_place(char *str);

/*
** NullErrorOut 
**
** Error out if the value of error is 0.
*/
void NullErrorOut (long error, char *szRoutine, char *szMessage);

/*
** ComponentExists
**
** Check to see if the named component has already been created
** in the InstallShield project.
*/
BOOL ComponentExists(char *szProjectPath, char *szComponentName);


/*
** AddRegistryEntries
**
**   This routine adds registry entries to the named file group in the 
** InstallShield project in the passed directory.
*/
BOOL AddRegistryEntries(char *szProjectPath,         // Path to the IS Pro Project
		PART *pPart);  // Registry entries list


/*
** AddShortcuts
**
**   This routine adds registry entries to the named file group in the 
** InstallShield project in the passed directory.
*/
BOOL AddShortcuts(char *szProjectPath,         // Path to the IS Pro Project
				  char *szFileGroup,		   // File Group Name
				  SHORTCUT *pShortcuts);       // Shortcuts list

/*
** WriteBundleInfo
**
**
*/
BOOL WriteBundleInfo(char *szProjectPath,	   // Path to the IS Pro Project
		     FAMILY_DESCRIPTOR *family,    // the family
		     int system_id);		   // the system ID (0 or 8 on Windows)


/*
** MakeWatermarks
**
** Create an InstallScript routine called "DoWatermarks" in the watermarks.rul
** file to create the watermarks after installing.
*/
BOOL MakeWatermarks(char *szProjectPath,
					WatermarkContainer *pWatermarks);

/*
** FileGroupExists
**
** Check to see if the named File Group has already been created
** in the InstallShield project.
*/
BOOL FileGroupExists(char *szProjectPath, char *szFileGroupName);


/* write_...install_per_component ...*/
void write_postinstall_per_component(char *project_path, FAMILY_DESCRIPTOR *family, RenameContainer *rename_data, ENV_VAR *environment_data);
void write_preinstall_per_component(char *project_path, FAMILY_DESCRIPTOR *family);
void write_uninstall_per_component(char *project_path, FAMILY_DESCRIPTOR *family);

/* make_component_internal_name ... */
BOOL make_component_internal_name (char *name_string, BUNDLE *bundle, COMPONENT *component);

