// gensym.h

//Prototypes for Common functions
prototype SetupScreen();
prototype InitializeGlobals();
prototype GetComponentSize(STRING);
prototype GetComponentSizeWithoutSubDirs(STRING);
prototype GetComponentSizeEx(STRING, BOOL);
prototype WelcomeStep();
prototype OldVersionStep(NUMBER, BYREF NUMBER, BYREF STRING, BYREF STRING,
                         BYREF STRING);
prototype OtherVersionInstalled(BYREF STRING, BYREF STRING, BYREF STRING,
                                BYREF STRING, BYREF STRING);
prototype LicenseStep(NUMBER, STRING);
prototype AllUsersStep(NUMBER, BYREF BOOL);
prototype OptionalComponentsStep(NUMBER, STRING);
prototype GetSunJDKVersion(BYREF STRING);
prototype GetSunJREVersion(BYREF STRING);
prototype IsAcrobatReaderInstalled();
prototype GetTargetDirStep(NUMBER, BYREF STRING, NUMBER);
prototype CheckTargetDir(STRING, NUMBER);
prototype SelectProgramFolderStep(NUMBER, BYREF STRING);
prototype JavaProductGetEnvModsStep(NUMBER, BYREF BOOL, BYREF BOOL);
prototype GetPropertiesOptionStep(NUMBER, STRING, BYREF NUMBER, BYREF STRING);
prototype JavaProductConfirmStep(NUMBER, NUMBER, STRING, STRING, STRING,
                                 STRING, BOOL, BOOL, NUMBER);
prototype JavaProductConfirmStep2(NUMBER, NUMBER, STRING, STRING, STRING,
                                 STRING, NUMBER);
prototype CommonProductConfirmStep(NUMBER, NUMBER, STRING, STRING, STRING,
                                 STRING, BOOL, BOOL, NUMBER, BOOL);
prototype EnoughDiskSpace(STRING, STRING, STRING, NUMBER, BYREF NUMBER);
prototype AddUpSelectedComponentSizes(STRING);
prototype SetupTargetStep(STRING, NUMBER, STRING, STRING, STRING,
                          BYREF STRING);
prototype PerformOtherVersionOption(NUMBER, STRING, STRING, STRING,
                                    STRING);
prototype UninstallOtherVersion(STRING, STRING);
prototype MakeDirNameUnique(STRING, BYREF STRING);
prototype MakeFileNameUnique(STRING, STRING, BYREF STRING);
prototype RenameDirectory(STRING, STRING);
prototype BeginUninstallLogging(STRING, BYREF STRING);
prototype CopyFilesStep(STRING, STRING, STRING, LIST, LIST);
prototype CopyComponentDirectory(STRING, STRING, STRING, STRING, BOOL);
prototype ProgramFolderStep(STRING, STRING, STRING, STRING);
prototype AddShortcutToFolder(STRING, STRING, STRING, STRING, STRING, STRING,
                              STRING);
prototype GetEnvVarDef(STRING, BYREF STRING);
prototype GetEnvVarDef95(STRING, BYREF STRING);
prototype GetEnvVarDefNT(STRING, BYREF STRING);
prototype HomeEnvVarStep(STRING);
prototype ReplaceEnvVar(STRING, STRING);
prototype ReplaceEnvVar95(STRING, STRING);
prototype ReplaceEnvVarNT(STRING, STRING);
prototype AppendPathToEnvVar(STRING, STRING);
prototype AppendPathToEnvVar95(STRING, STRING);
prototype AppendPathToEnvVarNT(STRING, STRING);
prototype AddToEndIfNotInList(LIST, STRING, BYREF STRING);
prototype IsInPath(STRING, STRING);
prototype CreateDirListFromPath(STRING);
prototype IsInList(LIST, STRING);
prototype InstallPropertiesStep(STRING, STRING, STRING, STRING, STRING,
                                NUMBER, STRING);
prototype InstallPropertiesFile(STRING, STRING, STRING, STRING, STRING,
                                NUMBER, STRING);
prototype FixupPropertiesFile(STRING, STRING, STRING, STRING, STRING);
prototype DoubleSlashify(STRING, BYREF STRING);
prototype WarnAndLog(STRING);
prototype MergePropertiesFiles(STRING, STRING, BYREF LIST);
prototype KeyInList(LIST, STRING);
prototype NoUninstallCopyFile(STRING, STRING, STRING, STRING);
prototype LoggingStep(STRING, STRING);
prototype WriteLinesOfText(STRING, STRING, LIST, BOOL, BOOL);
prototype OverwriteLinesOfText(STRING, STRING, LIST);
prototype IsBDK();
prototype ReadMeOrRebootStep(BYREF BOOL);
prototype ReadMeOrRebootWithMessageStep(BYREF BOOL, STRING);
prototype DisplayHtmlFile(STRING, STRING);
prototype FindFileOpenApp(STRING, BYREF STRING);
prototype AskDestPathWithoutCreate(STRING, STRING, BYREF STRING, NUMBER);
prototype GetAfterInstallOption(STRING, STRING, STRING, STRING);
prototype GetAfterInstallOptions(STRING, STRING, STRING, STRING);
prototype AfterInstallOptions(STRING, STRING, STRING, STRING, NUMBER);
prototype GetOptionsEx(STRING, STRING, STRING, STRING, BOOL, BOOL, STRING,
                       NUMBER);
prototype ChangeBoxesToButtons(HWND, NUMBER);
prototype InitOptions(STRING, NUMBER, STRING, NUMBER, HWND);

// Constant declarations. These are constants that should not have to change
// for different installs
#define COMPANY_NAME          "Gensym"

#define RAW_PROPERTIES_FILE   "rawprop.gen"
#define PROPERTIES_DIR        "classes"
#define PROPERTIES_FILE       ".com.gensym.properties"

#define COMPONENT_DIR         "components"

// constants needed for the common functions

// add extra space when checking for enough space for the product
#ifndef EXTRA_DISKSPACE
#define EXTRA_DISKSPACE 204800
#endif

#define README_FILE           "readme.html"

#define LOG_FILE_NAME         "installLog.txt"
#define LOG_HEADER_WARN       "Setup produced the following warnings:"

#define INSTALL_DIR_STRING     "installDir"
#define UNINSTALL_FILE_STRING  "dereg"
#define UNINSTALL_APP_STRING   "uninstallApp"
#define UNINSTALL_PARAM_STRING "uninstallParam"

#define ALL_USERS_STRING   "Install for all users"
#define SINGLE_USER_STRING "Install just for the current user"

#define NO_OTHER_VERSION         0
#define UNINSTALL_OTHER_VERSION  1
#define RENAME_OTHER_VERSION     2
#define DO_NOTHING_OTHER_VERSION 3

#define UNINSTALL_OPT_STRING "Uninstall the other version"
#define RENAME_OPT_STRING "Rename the directory of the other version if needed"
#define NOTHING_OPT_STRING "Do nothing with the other version (not recomended)"

#define MERGE_PROPS_STRING "Merge properties into the user properties file."

#define NO_PRODUCT_PROPS 0
#define NO_USER_HOME     1
#define ADD_USER_PROPS   2
#define MERGE_USER_PROPS 3
#define NO_USER_PROPS    4

#define AFTER_INSTALL_OPTIONS "afterInstallOptions"

#ifndef AFTER_INSTALL_OPTIONS_DEFINED
#define README_OPTION "I want to view the ReadMe file."
#define REBOOT_OPTION "I want to restart my computer to update the environment."
#define EXIT_OPTION   "I just want to exit now and update the environment later."
#define EXIT_OPTION_NO_REBOOT_NEEDED "I just want to exit."
#endif

#define BACKWARD -1
#define FOREWARD  1

#ifndef EXIT_STEP
#define EXIT_STEP  -1
#endif

// The following constants are here so steps that a particular install is
// not using will compile.

// The common functions assume the number of the steps
// determinines their order and that there are no gaps.
#ifndef WELCOME_STEP
#define WELCOME_STEP               -2
#endif
#ifndef LICENSE_STEP
#define LICENSE_STEP               -2
#endif
#ifndef ALL_USERS_STEP
#define ALL_USERS_STEP             -2
#endif
#ifndef OLD_VERSION_STEP
#define OLD_VERSION_STEP           -2
#endif
#ifndef OPT_COMPONENTS_STEP
#define OPT_COMPONENTS_STEP        -2
#endif
#ifndef REQUIREMENTS_STEP
#define REQUIREMENTS_STEP          -2
#endif
#ifndef GET_TARGET_DIR_STEP
#define GET_TARGET_DIR_STEP        -2
#endif
#ifndef SELECT_PROGRAM_FOLDER_STEP
#define SELECT_PROGRAM_FOLDER_STEP -2
#endif
#ifndef GET_ENV_MODS_STEP
#define GET_ENV_MODS_STEP          -2
#endif
#ifndef GET_PROPS_OPTION_STEP
#define GET_PROPS_OPTION_STEP      -2
#endif
#ifndef CONFIRM_STEP
#define CONFIRM_STEP               -2
#endif
#ifndef SETUP_TARGET_STEP
#define SETUP_TARGET_STEP          -2
#endif
#ifndef COPY_FILES_STEP
#define COPY_FILES_STEP            -2
#endif
#ifndef PROGRAM_FOLDER_STEP
#define PROGRAM_FOLDER_STEP        -2
#endif
#ifndef HOME_ENV_VAR_STEP
#define HOME_ENV_VAR_STEP          -2
#endif
#ifndef OPT_ENV_VAR_STEP
#define OPT_ENV_VAR_STEP           -2
#endif
#ifndef PROPERTIES_STEP
#define PROPERTIES_STEP            -2
#endif

// Global variable declarations for holding state.
BOOL globalIsWinNT;
BOOL globalIsWin95;
BOOL globalAutoexecLoaded;
BOOL globalIsAdmin;
BOOL globalAllUsersInstall;
BOOL globalUninstallInitialized;
BOOL globalRebootNeeded;
BOOL globalOverwriteExistingProduct;

// The global install log.
LIST globalLinesToLog;
LIST globalRequirementsLog;
LIST globalOptionsLog;
