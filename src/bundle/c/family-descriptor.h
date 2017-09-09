/***************************************************************************
 * Module: family-file-reader.c
 * Copyright (C) 1986-2017 Gensym Corporation.
 *           All Rights Reserved
 *
 * Author(s): David McDonald, Judy Anderson, Mark Staknis
 *
 * A Family Descriptor file is parsed to a FAMILY_DESCRIPTOR,
 * which is comprised of a installer_version and family_id with
 * some number of bundles. Bundles are comprised of components
 * which are comprised of parts where the parts give file or
 * directory locations and other information needed for installation.
 *
 * A bundle (of components) is a single product in the sense that
 * a user will get an id to install a single bundle. Bundles
 * come in families reflecting variations in what the customer
 * can purchase, e.g. development versus deployment.
 *
 * The components within a bundle are its different parts. Some
 * components may be shared between different bundles. In a
 * default installation all of the components in a bundle would
 * be included. A custom installation would offer to install some
 * or all, component by component.
 *
 * Ultimately a component is defined in terms of one or more
 * parts where the parts indicate where the files (or entire
 * directories) that comprise the part are located as well as
 * any other information that may be needed to properly install
 * them.
 ***************************************************************************/
#ifndef _FAMILY_DESCRIPTOR_H_INCLUDED_
#define _FAMILY_DESCRIPTOR_H_INCLUDED_

#ifdef WIN32
#define boolean BOOL
#else
typedef int boolean;
#endif



/* Installer Version:
   
   BUNDLE_INSTALLER_VERSION is a string of the form "<major>.<minor>
   Rev. <revision>".  It is to be updated by hand in a somewhat informal manner
   for now.  This defines the official version of the installer.

   NB: Not to be confused with INSTALLER_VERSION, q.v., in InstUtilDLL.h.
   
   Note that the FCS (first customer ship) version was "1.0 Rev. 0", though this
   variable was not here.  It just worked out that way. -mhd, 10/23/00

   => 1.0 Rev. 2 -mhd, 12/6/00
   => 1.0 Rev. 3 -css, 1/13/01
   => 1.0 Rev. 4 -yduJ, around March 01 (so tagged, but the string was never changed!)
   => 1.0 Rev. 5 -mhd, 4/23/01
   => 1.0 Rev. 6 -yduJ, 4/27/01
   => 1.0 Rev. 7 -mhd, 5/25/01
   => 1.0 Rev. 8 -yduj/mhd, 6/19/01
   => 1.0 Rev. 9 -mhd, 9/7/01
   => 1.0 Rev. 10 -mhd, 10/14/01
   => 1.0 Rev. 11 -mhd, 12/10/01
   => 1.0 Rev. 12 -yduJ, 6/5/03
   => 1.0 Rev. 13 -yduJ, 9/2/03
   => 1.0 Rev. 14 -yduJ, 6/2/04
   => 1.0 Rev. 15 -yduJ, 8/18/04
   => 1.1 Rev. 0 -yduJ, 10/12/04
   => 1.1 Rev. 1 -yduJ, 01/26/05
   => 1.1 Rev. 2 -yduJ, 02/18/05
   => 1.1 Rev. 3 -yduJ, 07/06/05
   => 1.1 Rev. 4 -yduJ, 10/14/05
   => 1.1 Rev. 5 -yduJ, 9/15/06
   => 1.2 Rev. 0 -binghe, 11/30/2015
   */

#define BUNDLE_INSTALLER_VERSION "1.2 Rev. 0"

typedef struct registration
{
  char* rg_path;
  char* rg_name;
  char* rg_key_name;
  char* rg_value;
  struct registration *rg_next_reg_object;
} REGISTRATION;


/* The elements in these enums are assigned numbers so that
   a different number can be used as a error-code when parsing
   these from a family descriptor file. */
typedef enum { normal = 1, minimized = 2
} SHORTCUT_RUN_STYLE;

typedef enum { common = 1, personal = 2, automatic = 3
} SHORTCUT_TYPE;

typedef struct shortcut
{
  char* sc_folder;
  char* sc_subfolder;
  char* sc_subsubfolder;
  char* sc_display_name;
  char* sc_directory;
  char* sc_target_name;
  char* sc_parameters;
  char* sc_icon_file;
  int sc_icon_index;
  SHORTCUT_TYPE sc_type;
  SHORTCUT_RUN_STYLE sc_run_style;
  struct shortcut *sc_next_shortcut;
} SHORTCUT;


typedef enum { new_var = 1, append = 2, replace = 3, merge = 4
} ENV_VAR_EFFECT;

typedef struct env_var
{
  char* ev_name;
  char* ev_value;
  ENV_VAR_EFFECT ev_effect;
  struct env_var *ev_next_env_var;
  char* ev_component_name;	/* only set by InstallGenerator.c, read by ISProject.c, only
				   initialized by fam. file reader */
} ENV_VAR;


typedef struct file_data
{
  char* fd_source_directory;
  char* fd_destination_directory;
  char* fd_source_name;
  char* fd_destination_name;
  struct file_data *fd_next_file_data;
  boolean fd_obfuscate;
} FILE_DATA;

typedef struct part
{
  char* pt_name;
  char *pt_postinstall_code;
  char *pt_preinstall_code;
  char *pt_uninstall_code;
  boolean pt_register;
  unsigned int pt_os_availability;
  struct registration *pt_first_reg_object;
  struct env_var *pt_first_env_var;
  struct shortcut *pt_first_shortcut;
  struct file_data *pt_first_file_data;  
  struct part *pt_next_part;
} PART;


typedef struct component
{
  unsigned char cp_index;
  char* cp_name;
  int cp_button_group;
  boolean cp_typical;
  boolean cp_optional;
  char* cp_watermark;
  char* cp_java_requirement;
  unsigned int cp_os_availability;
  struct part *cp_first_part;
  struct component *cp_next_component;
} COMPONENT;


typedef struct bundle
{
  unsigned char bdl_id;
  char* bdl_name;
  char* bdl_version;
  char* bdl_directory_name;
  boolean bdl_visible; /* defaults to true */
  unsigned int bdl_os_availability;
  struct component *bdl_first_component;
  struct bundle *bdl_next_bundle;
  boolean bdl_typical_only; /* defaults to false */
} BUNDLE;

typedef struct prev_version
{
  char *pv_guid;
  char *pv_version;
  struct prev_version *pv_next;
} PREV_VERSION;

typedef struct family_descriptor
{
  unsigned char fd_installer_version;
  char* fd_name;
  unsigned char fd_id;
  char* fd_splash_screen;  /* file name of splash screen bmp-format bitmap file in the bundle/ishield directory */
  char* fd_readme;         /* file name of readme.txt file in the bundle/ishield directory */
  char* fd_license_text;   /* file name of license.txt file in the bundle/ishield directory */
  char* fd_guid;           /* a GUID registered in tools/datafiles/families/guid.dat, looks like this: 5f736340-7ea5-11d4-9b74-ca6847000000 */
  char* fd_version;        /* should correspond to GUID registration in tools/datafiles/families/guid.dat */
  /* NOTE: it's clear we need a version for the family, not clear why we needed it for the bundle, but that's all we started with! -- mhd, 10/10/00 */ 
  char* fd_directory_name;
  unsigned int fd_os_availability;
  struct prev_version *fd_prev_versions;
  struct bundle *fd_first_bundle;
} FAMILY_DESCRIPTOR;

#endif 
