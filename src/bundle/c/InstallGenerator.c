// InstallGenerator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "ISProject.h"

// David's Family Descriptor File parsing functions. -- JW 7/13
extern int parse_family_file();
extern void reprint_the_family_data();

// Must define this to use in David's get_line function. -- JW 7/13
static FILE *fDescriptorFile;

// Extern references to functions in family-file-reader. -- JW 8/8
extern int parse_family_file (FAMILY_DESCRIPTOR *family);
extern FAMILY_DESCRIPTOR* new_family ();




/*
SYNTAX_ERROR get_line (char *buffer, int max_length)
{
  static int line_number;

  line_number++;
  if ( fgets( buffer, max_length, fDescriptorFile) )
    return ok;
  else
    return end_of_file;
}
*/


int get_line (char *buffer, int max_length)
{
  if ( fgets( buffer, max_length, fDescriptorFile) )
    return 2; /* punt on proper implementation */
  else
    return 0;
}


/* record_rename_data records cases where postprocessing needs to be done
   on certain files. Cases include:

   (a) renaming a file; and
   (b) unobfuscating a file

   For historical reasons the function name and data structures refer to
   "renaming" only.  This might have better been called record_file_data.  */

RenameContainer *record_rename_data (char *component_name,
				     FILE_DATA *file_data,
				     RenameContainer *rename_data)
{
  char *dest_name = file_data->fd_destination_name;
  char *dest_dir = file_data->fd_destination_directory;
  BOOL obfuscate = file_data->fd_obfuscate;
  RenameContainer *new_rename;
  
  if ((dest_name == NULL) && !obfuscate)
    return(rename_data);
  else
    {
      /* Replace / with \ in destination directory name. */
      if (dest_dir != NULL)
	backslashify_in_place(dest_dir);
      new_rename = malloc(sizeof(RenameContainer));
      new_rename->szTargetDir = dest_dir;
      new_rename->szSourceName = file_data->fd_source_name;
      new_rename->szTargetName = dest_name;
      new_rename->szComponentName = strdup(component_name);
      new_rename->obfuscate = obfuscate;
      if (rename_data == NULL)
	new_rename->next = NULL;
      else
	new_rename->next = rename_data;
      return(new_rename);
    }
}


ENV_VAR *record_environment_data (char *component_name,
				  PART *part,
				  ENV_VAR *environment_data)
{
  char *name_dup = strdup(component_name);
  ENV_VAR *result_ev_data;
  ENV_VAR *ev_1 = part->pt_first_env_var;
  ENV_VAR *ev;
  
  if (environment_data == NULL)
    result_ev_data = ev_1;
  else {
    result_ev_data = environment_data;
    for (ev = environment_data;
	 ev->ev_next_env_var != NULL;
	 ev = ev->ev_next_env_var)
      ;
    ev->ev_next_env_var = ev_1;
  }
  for (ev = ev_1; ev != NULL; ev = ev->ev_next_env_var)
    ev->ev_component_name = name_dup;
  return(result_ev_data);
}


#define MAIN_usage_text "Syntax: \n\n  InstallGenerator FamilyDescriptorFile TargetProject FilesRoot Edition\n\n\
   FamilyDescriptorFile - The full path to the family descriptor file.\n\n\
   TargetProject - The full path the InstallShield Pro 6.2 project file.\n\n\
   FilesRoot - The root directory in which all files and directories referenced in the \n\
               family descriptor file can be located.\n\n\
   Edition - std or ent (must in small case)\n\n"

#define main_szRoutine "main"
#define main_Emit(a, b, c, d, szTask) NullErrorOut(WritePrivateProfileString(a, b, c, d), main_szRoutine, szTask)
#define STANDIN_GUID "243d4bc1-9ee7-11d4-8111-00a02431d004"
#define guid_warning_format_string "WARNING: This family has no GUID.  A standin (%s) will be used.\n\
  THIS IS NOT ACCEPTABLE FOR FOR SHIPPING PRODUCTS.\n\
  Please register a GUID in tools/datafiles/families/guid.dat, and add a GUID for this family in your family file!\n"
#define license_text_relative_dir_path "Setup Files\\Compressed Files\\Language Independent\\OS Independent"
#define license_text_standard_filename "license.txt"
#define splash_screen_relative_dir_path "Setup Files\\Uncompressed Files\\Language Independent\\OS Independent"
#define splash_screen_relative_english "Setup Files\\Uncompressed Files\\0009-English\\OS Independent"
/* The second (_english) path may be used; we're not totally sure when or which,
   and it's safest to copy to both, so we do. Conceivably, we could have
   localized installers, at which time we may wish to add localized
   splashscreens, or simply copy the standard splashscreen to all locals'
   folders. -mhd, 11/1/00 */

/* Storing the set of source bitmaps in Script Files is a somewhat arbitrary and
random.  It should be an out-of-the-way place, such that the files can be found
by InstallGenerator and such that the files won't end up on the media. */
#define splash_screen_relative_dir_src "Media"
#define splash_screen_standard_filename "setup.bmp"


/* readme.txt is similar to splash screen in that it's sourced from the Media
directory, and ends up at top-level on the CD uncompressed.  It's a bit
different in that it's a text file. */

#define readme_relative_dir_path "Setup Files\\Uncompressed Files\\Language Independent\\OS Independent"
#define readme_relative_english "Setup Files\\Uncompressed Files\\0009-English\\OS Independent"
#define readme_relative_dir_src "Media"
#define readme_standard_filename "readme.txt"

void copy_setup_file_if_any
    (char *src_name_or_null, char *description, char *project_path,
     char *src_dir, char *dst_dir, char *dst_name, char *dst_dir_2_or_null)
{
  if (src_name_or_null == NULL)
    printf("(%s: not specified)\n", description);
  else
    {
      char src_path[MAX_PATH];
      char dst_path[MAX_PATH];

      strcpy(src_path, project_path);
      PathAppend(src_path, src_dir);
      PathAppend(src_path, src_name_or_null);
      printf("%s:\n  %s\n", description, src_path);

      strcpy(dst_path, project_path);
      PathAppend(dst_path, dst_dir);
      PathAppend(dst_path, dst_name);
      if (CopyFile(src_path, dst_path, FALSE) == 0)
	printf("WARNING: %s %s could not be copied to %s\n", description, src_path, dst_path);

      if (dst_dir_2_or_null != NULL) {
	strcpy(dst_path, project_path);
	PathAppend(dst_path, dst_dir_2_or_null);
	PathAppend(dst_path, dst_name);
	if (CopyFile(src_path, dst_path, FALSE) == 0)
	printf("WARNING: %s %s could not be copied to %s\n", description, src_path, dst_path);
      }
    }
}


/*
** 
*/
int main(int argc, char* argv[])
{
  char szDescriptorFile[MAX_PATH], szProjectFile[MAX_PATH], szRootDir[MAX_PATH];
  char szStringTableFile[MAX_PATH], szComponentName[MAX_PATH], szProjectPath[MAX_PATH];
  char szFileSourcePath[MAX_PATH], szStaticFileLinkName[MAX_PATH];
  FILE *fProjectFile;
  FAMILY_DESCRIPTOR *family;
  BUNDLE *bundle;
  COMPONENT *component;
  PART *part;
  FILE_DATA *file_data;
  RenameContainer *rename_data;
  BOOL bStartComponent, bStartFileGroup;
  ENV_VAR *environment_data;
  WatermarkContainer *currentWatermark, *watermark_data;
  BOOL bCreateFiles;
  char szSystemID[MAX_PATH]; // "std" or "ent"
  int system_id;             // 0 (INTELNT_CODE) or 8 (WIN64_CODE)

  /*
  ** First check arguments.
  */
  if (argc != 5) {
    printf("Bundle Installer %s\n", BUNDLE_INSTALLER_VERSION);
    printf("%s", MAIN_usage_text);
    exit(0);
  } 

  /* 
  ** Arguments ok, so now load up the family descriptor file using David McDonald's
  ** code.
  */

  rename_data = NULL; environment_data = NULL;
  currentWatermark = NULL; watermark_data = NULL;

  strcpy(szDescriptorFile, argv[1]);
  strcpy(szProjectFile, argv[2]);
  strcpy(szRootDir, argv[3]);

  /* Setting up system ID from command line arguments. */
  strcpy(szSystemID, argv[4]);
  if (!strcmp(szSystemID, "ent"))
      system_id = WIN64_CODE;
  else
      system_id = INTELNT_CODE;

  remove_trailing_slash_in_place(szRootDir);
 
  fDescriptorFile = fopen(szDescriptorFile, "r");
  if (fDescriptorFile == NULL) {
    fprintf(stderr, "Error opening Family Descriptor File %s", szDescriptorFile);
    exit(0);
  }

  family = new_family();
  parse_family_file(family);
  /* reprint_the_family_data(); // For testing/logging purposes -- JW 7/13 */
  fclose(fDescriptorFile);

  /*
  ** Ok, we've now loaded the Family Descriptor into memory, so time to process 
  ** this into an InstallShield project.
  */ 
  fProjectFile = fopen(szProjectFile, "r");
  if (fProjectFile == NULL) {
    fprintf(stderr, "Error opening InstallShield Project File %s", szProjectFile);
    exit(0);
  }

  /*
  ** TO DO: Modify any directory settings in the base project file? -- 8/4
  */
  fclose(fProjectFile); /* We aren't actually doing anything with this file right */
  /* now, just opening to ensure it is in the right place.  */
  /*                   -- JW 7/13 */

  NullErrorOut((long) strcpy(szProjectPath, szProjectFile), "main", "Copying project file location string");
  NullErrorOut(PathRemoveFileSpec(szProjectPath), "main", "Removing project file name from path string.");

  NullErrorOut((long) strcpy(szStringTableFile, szProjectPath), "main", "Copying Project Path String to String Table Filename path");
  NullErrorOut(PathAppend(szStringTableFile, "String Tables\\0009-English\\Value.shl"), "main", "Appending String Table directory to Project Path String");

  /* Write out the family name as the product name to the string table and Project Files. */
  main_Emit("Data", "PRODUCT_NAME", family->fd_name, szStringTableFile, "Setting App Name to Family Name in String Table");
  main_Emit("Data", "ProductName", family->fd_name, szProjectFile, "Setting App Name to Family Name in Project File");

  {
    char *version = "";
    BUNDLE *b;

    /* Set version to the first bundle's version that's not the empty string
       ("").  In practice, all bundles should have non-empty versions, and they
       should all be the same.  To do: get rid of the version at the bundle
       level; it should only be at the family level! (MHD 1/17/01) */

    for (b = family->fd_first_bundle; b != NULL; b = b->bdl_next_bundle)
      if ((version = b->bdl_version) != "") break;

    /* We now assume we have the product (family) version. Store it.  Note:
       previously we stored the bundle installer version here.  Changing that
       convention, and the corresponding Ishield code, for Bundle Installer 1.0
       Rev. 3. (MHD 1/18/01) */
    
    main_Emit("Data","PRODUCT_VERSION", version, szStringTableFile,
	      "Setting Version Bundle INSTALLER version in String Table");
    main_Emit("Data", "Version", version, szProjectFile,
	      "Setting Version Bundle INSTALLER version");
  }

  /* Write out the Family's globally unique ID (GUID) in the Project file. */
  /* For now, be willing to not have a GUID and supply a standin, but only
     grudgingly.  Note that the standin is stable and known to be globally
     unique.  -mhd, 10/11/00*/
  {
    char *guid = family->fd_guid;
    if (guid == NULL) {
      guid = STANDIN_GUID;
      printf(guid_warning_format_string, guid);
    }
    printf("GUID: %s\n", guid);
    main_Emit("Data", "InstallationGUID", guid, szProjectFile, "Putting GUID in Project File");
  }

  /* Use the family's license.txt file, if specified. */
  copy_setup_file_if_any
    (family->fd_license_text, "License text file",
     szProjectPath,
     license_text_relative_dir_path,
     license_text_relative_dir_path, license_text_standard_filename,
     NULL);
  /* Use the family's setup.bmp file, if specified. */
  copy_setup_file_if_any
    (family->fd_splash_screen, "Splash screen file",
     szProjectPath,
     splash_screen_relative_dir_src,
     splash_screen_relative_dir_path, splash_screen_standard_filename,
     splash_screen_relative_english);
  /* Use the family's readme.txt file, if specified. */
  copy_setup_file_if_any
    (family->fd_readme, "Readme file",
     szProjectPath,
     readme_relative_dir_src,
     readme_relative_dir_path, readme_standard_filename,
     readme_relative_english);

  /* Correct the project path in the project file. */
  main_Emit("Data", "InstallRoot", szProjectPath, szProjectFile, "Setting Project Path in Project File to passed path");

  /* TO DO: Write out the family ID into the code as a constant and check this in the  */
  /*        license key check code? -- JW 8/4 */
  /* printf("\n\n%d ", family->fd_id);   */

  bundle = family->fd_first_bundle;
  while (bundle != NULL) {
    if (!(bundle->bdl_os_availability & (0x1))) {
      /*
      ** TO DO: What to do with bundle name and version?  -- JW 8/4
      ** PROPOSED SOLUTION: Write these out as defines.  Then in the Init
      **    section where the default directory is set, reg entries specified,
      **    etc., instead make a call to a routine which knows which bundle 
      **    is being installed based on the bundle ID and makes the calls to
      **    the appropriate initialization functions, etc. based on that! -- JW 8/15
      */
      /* printf("\n( \"%s\" ", bundle->bdl_name); */
      /* printf("\"%s\" ", bundle->bdl_version); */

      /*
      ** Now cycle through the components and add then as InstallShield components.
      */
      component = bundle->bdl_first_component;
      while (component != NULL) {
	NullErrorOut(make_component_internal_name(szComponentName, bundle, component),
		     "main", "Appending component index to bundle name string");

	/* TO DO: Check for component display name rather than index!  BOOKMARK! */
	if ( (ComponentExists(szProjectPath, szComponentName) == FALSE) &&
	     (!(component->cp_os_availability & (0x1))))
	  {
	    NullErrorOut(
			 AddComponent(szProjectPath,           /* Path to the IS Pro Project */
				      szComponentName,                  /* Internal name of the component, just a number */
				      component->cp_name,               /* Display name of the component */
				      component->cp_name,               /* Text to display while copying files */
				      component->cp_name,               /* Text to describe the component */
				      TRUE,                            /* Component visible to the end user? */
				      /* component->cp_include_by_default, // Default status of the component */
				      TRUE,
				      "", 
				      "", /* postinstall handler, now set by RenameFiles. -mhd, 10/28/00 */
				      "",
				      "",
				      family->fd_id,
				      bundle->bdl_id,
				      component->cp_index,
				      component->cp_typical),
			 "main",
			 "Adding component");


	    part = component->cp_first_part;
	    bStartComponent=TRUE;
	    while (part != NULL) {

	      if (!(part->pt_os_availability & (0x1))) {
            						
		NullErrorOut((long) strcpy(szFileSourcePath, szRootDir), "main", "Copying Files Root Dir to File Group Source Path");
		if (part->pt_first_file_data->fd_destination_directory != NULL) {
		  NullErrorOut(PathAppend(szFileSourcePath, part->pt_first_file_data->fd_destination_directory), "main", "Appending File Group subdirectory to source path for group creation");
		}

		/* Strip out forward slashes in directory names and replace with backslashes */
		backslashify_in_place(szFileSourcePath);

		/* Strip out forward slashes in directory names and replace with backslashes */
		if (part->pt_first_file_data->fd_destination_directory != NULL) {
		  backslashify_in_place(part->pt_first_file_data->fd_destination_directory);
		    }


		if (part->pt_first_file_data->fd_source_name == NULL) {  

		  /*
		  ** If no source/dest file name, it is a dynamic file group
		  */
		  if (FileGroupExists(szProjectPath, part->pt_name) == FALSE) {
		    AddFileGroup(szProjectPath,     /* Path to the IS Pro Project */
				 part->pt_name,              /* The name of the File Group, */
				 part->pt_register,          /* Self registering? */
				 TRUE,                       /* Dynamic or static file group? */
				 part->pt_register,          /* Shared files?  We say yes if self-registering, no otherwise. */
				 part->pt_register,           /* Potentially Locked files?  We say yes if self-registering, no otherwise. */
				 szFileSourcePath,            /* Source files directory for dynamic groups */
				 part->pt_first_file_data->fd_destination_directory);     /* Target directory under primary directory */

		    /* Create shortcuts. */
		    if (part->pt_first_shortcut != NULL) {
		      AddShortcuts(szProjectPath, part->pt_name, part->pt_first_shortcut);
		    }

		    /* Create registry entries. */
		    if (part->pt_first_reg_object != NULL) {
		      AddRegistryEntries(szProjectPath, part);
		    }


		  }
		} else {
										
		  /*
		  ** This is not a dynamic group, so we need to cycle through and add
		  ** the files individually.  -- JW 8/4
		  */
										
		  if (FileGroupExists(szProjectPath, part->pt_name) == FALSE) {

		    AddFileGroup(szProjectPath,     /* Path to the IS Pro Project */
				 part->pt_name,              /* The name of the File Group, */
				 part->pt_register,          /* Self registering? */
				 FALSE,                       /* Dynamic or static file group? */
				 part->pt_register,          /* Shared files?  We say yes if self-registering, no otherwise. */
				 part->pt_register,           /* Potentially Locked files?  We say yes if self-registering, no otherwise. */
				 szFileSourcePath,            /* Source files directory for dynamic groups */
				 part->pt_first_file_data->fd_destination_directory);     /* Target directory under primary directory */
											
		    /* Create shortcuts. */
		    if (part->pt_first_shortcut != NULL) {
		      AddShortcuts(szProjectPath, part->pt_name, part->pt_first_shortcut);
		    }

		    /* Create registry entries. */
		    if (part->pt_first_reg_object != NULL) {
		      AddRegistryEntries(szProjectPath, part);
		    }
		    bCreateFiles = TRUE;

		  } else {
		    bCreateFiles = FALSE;
		  }
										
		  NullErrorOut((file_data = part->pt_first_file_data) != NULL, "main", "Inserting first file to group.");
		  bStartFileGroup = TRUE;

		  while(file_data != NULL) {
		    strcpy(szStaticFileLinkName, szFileSourcePath);
		    NullErrorOut(PathAppend(szStaticFileLinkName, file_data->fd_source_name), "main", "Constructing static file link");
		    backslashify_in_place(szStaticFileLinkName);

		    if (bCreateFiles == TRUE) {
		      NullErrorOut(InsertFileToGroup(szProjectPath, part->pt_name, szStaticFileLinkName, bStartFileGroup), "main", "Inserting file to group.");
		    }
											
		    rename_data = record_rename_data(szComponentName, file_data, rename_data);
		    bStartFileGroup = FALSE;
		    file_data = file_data->fd_next_file_data;
		  }


		} /* end if/else for dynamic/static file group addition */
								

		NullErrorOut(AddFileGroupToComponent(szProjectPath, szComponentName, part->pt_name, bStartComponent), "main", "Adding File Group To Component");

		/* Add any environment variables for the part to the global list. */
		if (part->pt_first_env_var != NULL)
		  environment_data = record_environment_data(szComponentName, part, environment_data);

		bStartComponent = FALSE;

                                
	      } /*  end if for test for part availability on NT */

	      part = part->pt_next_part;

	    }

	    if (component->cp_watermark != NULL) {
	      if (currentWatermark == NULL) {
		currentWatermark = (WatermarkContainer*) malloc(sizeof(WatermarkContainer));
		watermark_data = currentWatermark;
		currentWatermark->szWatermarkFile = component->cp_watermark;
		currentWatermark->szComponentName = (char*) malloc(MAX_PATH);
		strcpy(currentWatermark->szComponentName, szComponentName);
		currentWatermark->next = NULL;
	      } else {
		currentWatermark->next = (WatermarkContainer*) malloc(sizeof(WatermarkContainer));
		currentWatermark = currentWatermark->next;
		currentWatermark->szWatermarkFile = component->cp_watermark;
		currentWatermark->szComponentName = (char*) malloc(MAX_PATH);
		strcpy(currentWatermark->szComponentName, szComponentName);
		currentWatermark->next = NULL;
	      }
	    }
	  } /* end if for test for component availability on NT and already existing */
        				
	component = component->cp_next_component;
	bStartComponent = TRUE;
        				
      }
    } /*  end if for test for bundle availability on NT */
    bundle = bundle->bdl_next_bundle;


  }

  write_postinstall_per_component(szProjectPath, family, rename_data, environment_data);

  write_preinstall_per_component(szProjectPath, family);

  write_uninstall_per_component(szProjectPath, family);
  /*
  ** Write out any bundle resolution information (target directory, etc.)
  */
  WriteBundleInfo(szProjectPath, family, system_id);

  MakeWatermarks(szProjectPath, watermark_data);
			

  /*
  ** All done!  
  */

  printf("Successful completion.\n\n");
  return 0;
}

#undef MAIN_usage_text
#undef main_szRoutine
#undef main_Emit
#undef STANDIN_GUID
#undef license_text_relative_dir_path
#undef license_text_standard_filename
#undef splash_screen_relative_dir_path
#undef splash_screen_standard_filename

