//tools.h 

prototype GetInformation ();


//End of DLL prototypes

prototype SplitStr(STRING, STRING, BYREF STRING, BYREF STRING); //(ToSplit,Find,First,Last)
prototype SplitStr2(STRING, STRING, BYREF STRING, BYREF STRING); //(ToSplit,Find,First,Last) returns full string if can't find svFind
prototype GetItemBetween(STRING, STRING,BYREF STRING);//(ToSplit,Find,ReturnItem)
prototype GetOptionsForThisDialog ( STRING, STRING, BYREF STRING);
prototype IsDefualt (BYREF STRING, BYREF BOOL);
prototype GetNextItem (BYREF STRING, BYREF BOOL, BYREF STRING);
prototype CountItems (STRING, STRING);//(string, delimiter)
prototype GetPathAndDrive(STRING, BYREF STRING, BYREF STRING); //(orginalpath, path, drive)

prototype ClearStringList(BYREF LIST);
prototype ClearNumberList( BYREF LIST);
prototype ListGetLastItem (LIST , BYREF NUMBER);
prototype ListPopLastItem (BYREF LIST, BYREF NUMBER); 

prototype ShowList (BYREF LIST, STRING);
prototype ShowListStr (BYREF LIST, STRING);

prototype TestMessage (STRING);
prototype WriteVerboseLog(STRING, STRING);
prototype SetShortCut_WinPlayer ();
prototype ValidateIconTag(BYREF STRING);
prototype ReplaceChar(BYREF STRING,STRING,STRING);
prototype AddLastSlash(STRING,BYREF STRING);
prototype WriteKeyToTextFile(STRING,STRING,STRING); //FileName and path, key, data
prototype GetKeyFromTextFile(STRING,STRING,BYREF STRING); //FileName and path, key, data
prototype GetGlobalInfoFromCFGFile_WP(STRING, BYREF NUMBER,STRING);
prototype GetLastDirectoryInPath(STRING,BYREF STRING);//returnDir, FullPath


prototype CompareVersion (STRING, STRING); //(szInstalledVersion,szVersionToInstall)
prototype CompareLanguages(LIST,LIST,BYREF NUMBER);
prototype CopyListToList(BYREF LIST,LIST); //(List returned, list to copy from
prototype WriteTranslationLog(LIST);
prototype SupportMessage(STRING, STRING); //(nvDebug, svLevel, svMsg) Level is ERROR or STEP
prototype ABS_SupportMessage(NUMBER,BOOL, STRING, STRING); //(nvDebug, svLevel, svMsg) Level is ERROR or STEP
prototype GetDebugSetting(); // Simple abstract function to get global setting
prototype GetDebugFileName(BYREF STRING);// Simple abstract function to get global setting
prototype InitLogs(BYREF STRING); 
prototype GetVerbose(BYREF BOOL); 


//Bundle tools
prototype InitBundleList (BYREF LIST); 
prototype GetListOfBundles(BYREF STRING, BYREF LIST); //(library, ItemList)


//Component tools
prototype BuildComponentList   (BYREF STRING, LIST); //(sLibrary, lListToAdd);
prototype AddComponentToList   (BYREF STRING, LIST); //(sLibrary, lListToAdd);  
prototype DeleteItemsComponent (BYREF STRING, LIST); //(sLibrary, lListToDelete);  
prototype WriteLogEntry(STRING);//The string you want entered into your log
prototype ABS_WriteLogEntry(STRING, STRING); //(filename, entry)
prototype GetLogname(BYREF STRING);
prototype BuildBundleList (STRING, BYREF LIST); //(szRegNumber,lBundleList);
prototype SetMediaElements (STRING,BYREF STRING);//(svSerial, svMedia);

//Serial Number tools
//prototype VerifySerialNumber ( STRING ); 

prototype BuildMedia(STRING);
prototype TestDll();
prototype IsLetters (STRING);



// MHD, 10/2/00:
prototype load_gensym_dll();
prototype unload_gensym_dll();
prototype list_components_on_media();
prototype preselect_components_and_check_for_maintenance(BYREF LIST);

// MHD, 10/13/00
prototype previous_install_is_present (STRING, STRING, BYREF STRING);
prototype remove_previous_install_per_guid (STRING, STRING);
prototype disallow_previous_install(STRING, STRING, STRING, STRING);

// Keeping a global list of previously installed components for maintenance:
// MHD, 12/6/00
LIST maintenance_previously_installed_list;
prototype copy_string_list(BYREF LIST, LIST);
prototype set_up_maintenance_previously_installed_list();


// MHD, 10/2/00: The following just keeps us from getting warnings
// about some functions not used now.

// MHD, 10/20/00: from ISProject.c/Environment.rul (Previously installgenerator generated this code
// out of string constants.)
prototype RejectEnvVar(STRING);
prototype Create1EnvVarAppendStyle(STRING, STRING, STRING, STRING);
prototype Create1EnvVarMergeStyle(STRING, STRING, STRING, STRING);
prototype Create1EnvVar(STRING, STRING, STRING, STRING);
prototype set_environment_registry_key(BYREF STRING);
prototype set_env_var(STRING, STRING, STRING, BOOL);

// MHD, 10/18/00: from java/.../gensym.h
prototype AddToEndIfNotInList(LIST, STRING, BYREF STRING);
prototype AddToEndIfNotInListForSubEnv(LIST, STRING, STRING, BYREF STRING);
prototype IsInPath(STRING, STRING);
prototype CreateDirListFromPath(STRING);
prototype IsInList(LIST, STRING);
prototype FixupPropertiesFile(STRING, STRING, STRING, STRING, STRING);
prototype DoubleSlashify(STRING, BYREF STRING);
prototype OverwriteLinesOfText(STRING, STRING, LIST);
prototype GetEnvVarDef95(STRING, BYREF STRING);
prototype ReplaceEnvVar95(STRING, STRING);
prototype AppendPathToEnvVar95(STRING, STRING);

// MHD, 10/20/00: Envvar handling stuff, including globals to hold state:
prototype system_subject_to_large_system_environment_variable_limit ();
prototype install_subject_to_large_system_environment_variable_limit ();
prototype over_limit_for_environment_size (NUMBER, STRING);
BOOL global_system_envvar_problem_warning_issued;
BOOL global_system_envvar_changes_require_reboot;

// MHD, 12/10/01: function to write batfile to set an environment variable to point to TARGETDIR:
prototype write_basedir_batfile(STRING, STRING);
// MHD, 12/10/01: function to write a batfile to launch a GSI bridge:
prototype write_gsi_launch_batfile(STRING, STRING);
// MHD, 12/10/01: function to replace %ROOTDIR% with TARGETDIR, e.g., in a batfile:
prototype replace_rootdir(STRING, STRING);
prototype CorrectRegistryEntry(NUMBER,STRING);
// yduJ, Aug 2004, function to pop up a warning message if a DLL isn't up to snuff.
prototype VerifyDLLVersion(STRING,NUMBER,NUMBER,STRING,STRING);
// yduJ, Aug 2004, for HQ-4697334
prototype BOOL HasNonASCII (STRING);
// yduJ, Apr 2005, for gdiplus.dll, which we only need if it isn't already there
prototype DeleteDLLIfNotNeeded(STRING,NUMBER,NUMBER,STRING);


// by William Morris, 6/27/01: Stuff needed for Integrity/Optegrity:
///////////////////////////////////////////////
// Integrity additions
/////////////////////////////////////////////// 
prototype integrityCopyPropertyFiles (STRING);
prototype integrityInstallProperties (STRING);
prototype integrityModifyPropFile (STRING);
prototype integrityCopyGensymPropertyFile (STRING);
prototype integrityPostInstall (STRING);


prototype tools_gag_is_compiler();
function tools_gag_is_compiler()
STRING by_ref_string, by_ref_string2;
BOOL by_ref_bool;
LIST some_list, by_ref_list;
NUMBER by_ref_number;
begin
	SplitStr2("", "", by_ref_string, by_ref_string2);
	GetItemBetween("", "", by_ref_string);
	GetOptionsForThisDialog("", "", by_ref_string);
	GetNextItem(by_ref_string, by_ref_bool, by_ref_string2);
	CountItems("", "");
	GetPathAndDrive("", by_ref_string, by_ref_string2);
        ClearStringList(by_ref_list);
        ClearNumberList(by_ref_list);
        ListGetLastItem (some_list, by_ref_number);
        ListPopLastItem (by_ref_list, by_ref_number);
	ShowList(by_ref_list, "");
	ShowListStr(by_ref_list, "");
	TestMessage("");
	ValidateIconTag(by_ref_string);
	AddLastSlash("", by_ref_string);
	GetKeyFromTextFile("", "", by_ref_string);
	GetLastDirectoryInPath("", by_ref_string);
	CopyListToList(by_ref_list, some_list);
	InitLogs(by_ref_string);
	InitBundleList(by_ref_list);
        GetListOfBundles(by_ref_string, by_ref_list);
	BuildComponentList(by_ref_string, some_list);
	AddComponentToList(by_ref_string, some_list);
	DeleteItemsComponent(by_ref_string, some_list);
	BuildBundleList("", by_ref_list);
	TestDll();
	IsLetters("");
        disallow_previous_install("", "", "", "");

         RejectEnvVar("");
         Create1EnvVarAppendStyle("", "", "", "");
         Create1EnvVarMergeStyle("", "", "", "");
         Create1EnvVar("", "", "", "");
         set_environment_registry_key(by_ref_string);
         set_env_var("", "", "", FALSE);
         over_limit_for_environment_size(0, "");
         system_subject_to_large_system_environment_variable_limit();
         install_subject_to_large_system_environment_variable_limit();
         previous_install_is_present ("", "", by_ref_string);
         remove_previous_install_per_guid ("", "");
         disallow_previous_install("", "", "", "");
     
         AddToEndIfNotInList(some_list, "", by_ref_string);
         IsInPath("", "");
         CreateDirListFromPath("");
         IsInList(some_list, "");
         FixupPropertiesFile("", "", "", "", "");
         DoubleSlashify("", by_ref_string);
         OverwriteLinesOfText("", "", some_list);
         GetEnvVarDef95("", by_ref_string);
         ReplaceEnvVar95("", "");
         AppendPathToEnvVar95("", "");

         write_basedir_batfile("", "");
         write_gsi_launch_batfile("", "");
         replace_rootdir("", "");
         CorrectRegistryEntry(0,"");
         DeleteDLLIfNotNeeded("",0,0,"");

         integrityCopyPropertyFiles ("");
         integrityInstallProperties ("");
         integrityModifyPropFile ("");
         integrityPostInstall ("");


        copy_string_list(by_ref_list, some_list);
        set_up_maintenance_previously_installed_list();

        tools_gag_is_compiler();
end;

