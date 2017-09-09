/***************************************************************************
 * Module: family-file-reader.c
 * Copyright (C) 1986-2017 Gensym Corporation.
 *           All Rights Reserved
 *
 * Author(s): David McDonald
 *
 * Description: 
 *  This reads a Family File and renders it into data structures. The 'file'
 *  is actually an abstraction and could be a live stream or some portion
 *  of a larger file. Actual access to the 'file' is mediated by calls to
 *  parse_line in tag-value-parser, which uses get_line (define in glue code).
 *
 *  The entry point is parse_family_file. It takes an empty family_descriptor
 *  as its sole argument and populates it according to its calls to the
 *  tag-value-parser return.
 *
 * 2do:
 *  - promulgate UNKNOWN_VALUE
 *
 * Mark David, 12/5/00: added new fields to shortcut structure:
 * sc_subfolder and sc_subsubfolder.  This lets you have two more
 * levels of subfolder.  Three fixed levels is still not fully
 * general, but is a lot more practical and useful than one.  Family
 * file entries are: subfolder name: <display text> and subsubfolder
 * name: <display text>.  When an sc_subsubfolder is specified, the
 * sc_subfolder field must be specified. An sc_folder field is
 * required generally. Changes in ISProject.c and family-descriptor.h
 * accompany this change.  Also added new field to part for a line of InstallShield
 * code (Windows only) to be explicitly passed down.  Also added a new field to
 * family structure for a list of GUID and Version string pairs to be passed down for
 * previous-installation checking.
 *
 ***************************************************************************/

#ifdef WIN32

#include "StdAfx.h"

#else

#include <stdio.h>
#include <string.h>

#include "tag-value-parser.h"
#include "family-descriptor.h"
#include "codes.h"

#endif


/* externs in tag-value-parser.c */
extern void convert_to_lowercase (char *string);
extern char *error_symbol (int id);

/* where are these / should these go? */
#define TRUE 1
#define FALSE 0
#define BOOLEAN int

/* NO_STRSTR_MATCH is the result of the c strings.h library function strstr when
   it cannot find a match of its arguments, i.e., the "null pointer" result.  Same note
   about the definition of NULL as above. -mhd, 9/15/00 */

#define NO_STRSTR_MATCH 0L


/* Used by functions that decode values to indicate that it didn't
   recognize the value. This is an int I assume will never occur naturally. */
#define UNKNOWN_VALUE 10002

/* echos what came back from the tag-value line parser */
#define debug_parser FALSE

/* Permits printfs that indicate problems that are detected while the
 * family file is being read. Intended for debugging extensions to the
 * family file facilities and consequently only makes sense when
 * fail_on_first_error is false. Set to true when this file is part
 * of the serialize-family-file program.  */
int debug_family_files = FALSE;

/* Intended for production conditions when any error in a family file
 * is evidence of corruption or tampering. */
#define fail_on_first_error TRUE

/* for catching possible logic bugs in this code itself */
#define debug FALSE


/* DOCUMENTATION
 The steps you need to take to add field and have it recognized and
 filled in by this reader.

 This walks through all of the steps needed to add a 'watermark' field to
 components. The first part is the actual addition of the data structure in
 the family-descriptor.h file. It names a path so it is char *watermark.

 Next the initialization routine for components has to be updated. All of
 the structure initizers are in one section have names on the pattern:
 "new_XXX". They malloc a new struct; populated it, which typically means
 setting the field to NULL; and return it.

 Now you need to decide what tag should be used in the family files for
 assigning this field a value. We'll use "watermark". This operation has
 two parts. One is designating a new value for this in the TAG enum; we'll
 use 'watermark'. The list that makes up the enum is somewhat sorted, so we
 add it just after the only other component-level element at this time,
 index_number. 

 The other is defining the mapping between what is written in the family
 file and the 'tag' in the enum. Besides the brute fact that we have to
 make a transition from characters to integers, this mapping step also lets
 us use different names from the family file to the internal tag if we want
 to. Doing this entails adding another case in the if's in the function
 reify_tag_string.

 Note that the string compares there are case sensitive. This amounts to
 having a canonical form for tags since the tag-value-parser downcases tags
 before returning them. Values, on the other hand, are passed through
 without any case folding since they may represent case-sensitive
 filenames.

 Once the tag is in place, the next step is adding the check for the tag in
 the state machine that embodies the grammar of the family file. This is
 the function scan_family_file. It is organized as an infinite loop. The
 loop is exited normally by a return that is issued when the tag-value-
 parser indicates that the end of the file has been reached. There are also
 error returns that fire is the flag fail_on_first_error is up (true) and
 the debug_family_files flag is down, for example when an unknown tag is
 seen.

 Scan_family_file's loop starts by calling parse_line in the tag-value-
 parser to get its tag_string and value_string locals populated. After
 checking the status return from parse_line, it is just one big switch of
 switches -- a state machine.

 The outermost switch is a dispatch to the correct state. Its possible
 values are listed in the STATE enum and correspond to the section of the
 family file that we are reading. It starts out in the reading_family state
 and shifts to other states according to the tags is sees.

 Watermark is a property of a component, and we require it to be positioned
 in the family file somewhere between the tag that signals the start of a
 component and the first tag that indicates the start of one of the
 component's daughters. E.g.

     component: G2
       index: 1
       watermark: g2/g2.ok
       part: tw
        [ etc. ]

 This means that we will see the tag while in the reading_component
 state. This corresponds to the reading_component case in the outer
 switch. The body of this case (and virtually all the others) is just
 another switch expression. This time the dispatch is on the tag. What we
 have to do is add a case in this switch for the tag being 'watermark'.

 The code for entering a state calls the start_XXX function for the element
 the state corresponds to. For example when the earlier 'component: G2'
 line was seen, we moved into the reading_component state and executed the
 routine start_component. One of the things a start_XXX function does is
 bind a global variable to the new struct it creates. In this case the
 global variable component.

 When a watermark tag is seen, we have to assign the value that was passed
 in to the corresponding field in the component struct we are in the middle
 of assembling -- the one currently assigned to the global variable
 'component'. The value is in a local buffer, so we copy it out using the
 utility routine copy_string. We assign this to our global, add the break,
 and we're done with the parsing and data-structure assembly aspects of the
 work.

 The other work that could be done to install watermark is to extend the
 function that checks for semantic problems in the data structures. (All
 syntactic problems with the family file were checked in scan_family_file.)
 This is done by the function vet_family_descriptor, which basically walks
 down through the family-file struct that was populated by the scan and
 checks that necessary elements are present.

 Watermark is not a required element, so there it is not an absolute
 requirement that we check for it, however this function does additional
 duty when it is run from serialize-family-file and the -check option is
 given. This sets the flag 'readout', which is used to conditionalize a set
 of printf's that exhaustively report what is in the data structures. To
 that end we add a case within the section of vet_family_descriptor that is
 looking at the toplevel properties of components to look for whether the
 watermark field is non-NULL and printout its contents.


*/



/*****************************************************************
 * Global variables holding the data structures being accumulated
 * and other global aspects of the state.
 ****************************************************************/

FAMILY_DESCRIPTOR *family;
BUNDLE            *bundle;
COMPONENT         *component;
PART              *part;
FILE_DATA         *file;
SHORTCUT          *shortcut;
ENV_VAR           *environment_variable;
BUNDLE            *shared_components;
REGISTRATION      *registration;
PREV_VERSION      *prev_version;

int trace = FALSE;

int readout = FALSE; /* Set via command-line arg. in serialze-family-file. */



/*****************************************************************
 * This Reader is based on a state machine that tracks the kind
 * of object being read at the moment as indicated by the tags
 * in the family file. These are its possible states.
 *****************************************************************/

enum STATE {reading_family=1, reading_bundle=2, 
	    reading_component=3, reading_part=4,
            reading_shortcut=5, reading_registration=6
};

/* Inverse of the enum to provide something readable for traces. */
char* state_symbol (id)
int id;
{
  switch (id) {
  case 1:
    return "Family";
  case 2:
    return "Bundle";
  case 3:
    return "Component";
  case 4:
    return "Part";
  case 5:
    return "Shortcut";
  case 6:
    return "Registration";
  default:
    return "???";
  }
}



/*****************************************************************
 *              identifying problems
 *****************************************************************/

/* When the family file is read, there may be syntactic problems
   (listed in the SYNTAX_ERROR enum - see tag-value-parser.h) or
   identify-able probems in the values that are given. (Some problems
   cannot be recognized, such as giving an incorrect filename.)

   The possible problems with value or configuration are listed
   here in the FD_PROBLEMS enum. Most are noticed as part of the
   running the vet_family_descriptor function, a few are noticed
   during the scanning of the file.  */

enum FD_PROBLEMS { 
 family_is_null, 
 no_installer_version, 
 no_family_name, 
 no_family_id,
 no_directory_name, /* applies to both families and bundles */
 family_has_no_bundles,
 previous_version_guid_before_version,
 bundle_with_no_id, 
 bundle_with_no_name, 
 bundle_with_no_version, 
 bundle_with_no_components,
 component_with_no_name, 
 component_with_no_index, 
 component_with_no_parts,
 unknown_value_for_typical,
 unknown_value_for_optional,
 part_with_no_files, 
 shortcut_without_folder, 
 shortcut_without_display_name, 
 shortcut_without_directory,
 shortcut_without_target_name, 
 shortcut_without_icon_file,
 unknown_shortcut_type,
 unknown_shortcut_run_style,
 part_has_no_source, 
 directory_destination_without_a_source,
 no_destination_directory_but_no_file_named,
 file_destination_without_a_source,
 ev_var_with_no_name,
 ev_value_without_ev,
 ev_effect_without_ev,
 invalid_env_var_effect,
 ev_var_with_no_value,
 ev_var_with_no_effect,
 reg_with_no_path,
 reg_with_no_name,
 reg_with_no_value
};


/*****************************************************************
 *      copying out the char buffers that the parser fills
 ****************************************************************/

char* copy_string (old)
  char* old;
{
  char* new;

  new = (char *)malloc(strlen(old) * sizeof(char) + 1);
  strcpy(new, old);
  return new;
}


int convert_to_int (s)
char* s;
{
  return atoi(s);
}


int encode_boolean (s)
char* s;
{
  if ( strcmp(s, "true") == 0 )
    return TRUE;
  else if ( strcmp(s, "false") == 0 )
    return FALSE;
  else
    return UNKNOWN_VALUE;
}



/*****************************************************************
 *              Representing o/s specifity
 *****************************************************************/

enum KIND_OF_AVAILABILITY { only, all_but };

char* availability_type (type)
enum KIND_OF_AVAILABILITY type;
{
  switch (type) {
  case only: {
    return "only on";
  }
  case all_but: {
    return "on all but";
  }
  default: {
    if (debug)
      printf("\navailability_type: should not have gotten here.\n");
    return "unknown";
  }
  }
}


/* Initialize_availabilty is called from the various 'start' functions
   below. It's purpose is to copy down (inherit) the availability
   restrictions of higher elements onto lower elements. This is an aspect
   of initializing the element (family, bundle, etc). Tags read while the
   element is being populated make make the restriction on availability
   more restictive; they cannot make them more liberal. */

void initialize_availability (state)
{
  switch (state) {
  case reading_family:
    {
      family->fd_os_availability = 0;  /* available on every o/s */
      if (debug) printf("\nInitialized family os_availability.");
      break;
    }
  case reading_bundle:
    {
      bundle->bdl_os_availability = family->fd_os_availability;
      if (debug) printf("\nCopying familiy os_availability to bundle.");
      break;
    }
  case reading_component:
    {
      component->cp_os_availability = bundle->bdl_os_availability;
      if (debug) printf("\nCopying bundle os_availability to component.");
      break;
    }
  case reading_part:
    {
      part->pt_os_availability = component->cp_os_availability;
      if (debug) printf("\nCopying component os_availability to part.");
      break;
    }
  default:
    {
      if (debug)
	printf("Initialize_availability: should not have gotten here.");
      break;
    }
  }
}


/* Setting one of the bits in the mask to 1 indicates that the
 * corresponding operating system is not available. */

int set_bit (mask, bit_number)
int mask, bit_number;
{
  int bitmask = 1;
  bitmask <<= bit_number;
  mask |= bitmask;
  return mask;
}

/* Returns true (1) if the bit is set in the field. This indicates
   that the part this field belongs to is not available on the OS
   that the bit corresponds to. */

int check_bit (field, bit_number)
int field, bit_number;
{
  int bitmask = 1;
  bitmask <<= bit_number;
  return (field & bitmask);
}



/* Os_restriction is a boolean intended for quick checks of the mask. 
   It returns TRUE if any of the bits are set, and FALSE otherwise. */

int os_restriction (mask)
unsigned int mask;
{
  if (mask==0)
    return FALSE;
  else
    return TRUE;
}


/* Function for querying os_restrictions abstracted to the level
   of part.  It is the caller's responsibility to ensure that they
   are passing in a part and the appropriate mask.  If the bit in
   the part's availability field that corresponds to the single
   bit given in the mask is 0 then that part is avaiable on that
   os and the function returns TRUE (1). */

int available_on_os (part, os_mask)
PART *part;
unsigned int os_mask;
{
  if ( ! check_bit(part->pt_os_availability, os_mask) )
    return TRUE;
  else
    return FALSE;
}



int prepare_mask (operating_systems)
char* operating_systems;
{
  unsigned int mask = 0; /* i.e. available on every o/s */
  int character_count = 0;
  int os_count = 0;

  if ( strstr(operating_systems, "nt") != NO_STRSTR_MATCH ) {
    os_count++;
    mask = set_bit(mask, INTELNT_CODE);
    character_count += 2;
  }
  if ( strstr(operating_systems, "win64") != NO_STRSTR_MATCH ) {
    os_count++;
    mask = set_bit(mask, INTELNT_CODE);
    character_count += 9;
  }
  if ( strstr(operating_systems, "sparcsol") != NO_STRSTR_MATCH ) {
    os_count++;
    mask = set_bit(mask, SPARCSOL_CODE);
    character_count += 8;
  }
  if ( strstr(operating_systems, "aix") != NO_STRSTR_MATCH ) {
    os_count++;
    mask = set_bit(mask, RS6000_CODE);
    character_count += 3;
  }
  if ( strstr(operating_systems, "hpux") != NO_STRSTR_MATCH ) {
    os_count++;
    mask = set_bit(mask, HPUX_CODE);
    character_count += 4;
  }
  if ( strstr(operating_systems, "linux") != NO_STRSTR_MATCH ) {
    os_count++;
    mask = set_bit(mask, LINUX_CODE);
    character_count += 5;
  }
  if ( strstr(operating_systems, "linux64") != NO_STRSTR_MATCH ) {
    os_count++;
    mask = set_bit(mask, LINUX64_CODE);
    character_count += 7;
  }
  if ( strstr(operating_systems, "alphaosf") != NO_STRSTR_MATCH ) {
    os_count++;
    mask = set_bit(mask, ALPHAOSF_CODE);
    character_count += 8;
  }
  if ( strstr(operating_systems, "hpia64") != NO_STRSTR_MATCH ) {
    os_count++;
    mask = set_bit(mask, HPIA64_CODE);
    character_count += 6;
  }

  /* sanity checks */
  if (os_count==0) {
    if (debug_family_files) {
      printf("None of these operating system names were intelligible:\n");
      printf("  \"%s\"\n", operating_systems);
    }
    if (fail_on_first_error) {
      /* ?? start using throw's ?? */
    }
  }

  /* 2do:  A calculation off the accumulated character_count and
     knowledge of the correspondence between which bits were set
     and what their character count would be would tell us 
     whether all of the listed operating_systems where actually
     recognized (vs. one or more being misspelled. */

  return mask;
}


/* Decode_os_mask does printf's intended for human consumption
   in the context of the vet_family_descriptor function when the
   readout flag is up. It is called when a part has some os_restriction. */
void decode_os_mask (part)
PART *part;
{
  if (readout) {
    printf("    It is only available on:\n       ");
    if ( available_on_os(part, INTELNT_CODE) )
      printf("intelnt ");
    if ( available_on_os(part, WIN64_CODE) )
      printf("win64 ");
    if ( available_on_os(part, SPARCSOL_CODE) )
      printf("sparcsol ");
    if ( available_on_os(part, RS6000_CODE) )
      printf("aix ");
    if ( available_on_os(part, HPUX_CODE) )
      printf("hpux ");
    if ( available_on_os(part, LINUX_CODE) )
      printf("linux ");
    if ( available_on_os(part, LINUX64_CODE) )
      printf("linux64 ");
    if ( available_on_os(part, ALPHAOSF_CODE) )
      printf("alphaosf ");
    if ( available_on_os(part, HPIA64_CODE) )
      printf("hpia64 ");
    printf("\n");
  }
}

void decode_os_mask_negative_polarity (mask)
unsigned int mask;
{
  if (readout) {
    printf("    It is not available on:\n       ");
    if ( check_bit(mask, INTELNT_CODE) )
      printf("intelnt ");
    if ( check_bit(mask, WIN64_CODE) )
      printf("win64 ");
    if ( check_bit(mask, SPARCSOL_CODE) )
      printf("sparcsol ");
    if ( check_bit(mask, RS6000_CODE) )
      printf("aix ");
    if ( check_bit(mask, HPUX_CODE) )
      printf("hpux ");
    if ( check_bit(mask, LINUX_CODE) )
      printf("linux ");
    if ( check_bit(mask, LINUX64_CODE) )
      printf("linux64 ");
    if ( check_bit(mask, ALPHAOSF_CODE) )
      printf("alphaosf ");
    if ( check_bit(mask, HPIA64_CODE) )
      printf("alphaosf hpia64 ");
    printf("\n");
  }
}



/* Set_availability is the entry point from the state machine. It is
 * called when the 'only on' and 'on all but' tags are seen. The
 * operating_systems parameter is a string that can include several
 * operating system names. The names have to be correctly spelled and
 * lower case for them to be recognized. The type parameter reflects
 * which of the two tags this is. The operations for them are identical
 * except that 'on all but' results in the complement of what 'only on'
 * does.  */

void set_availability (operating_systems, reading_state, type)
char* operating_systems;
enum STATE reading_state;
enum KIND_OF_AVAILABILITY type;
{ 
  unsigned int field;
  unsigned int mask;

  if (debug)
    printf("\nstate = %s, os = '%s', type = %s\n", 
	   state_symbol(reading_state), operating_systems, 
	   availability_type(type));

  mask = prepare_mask(operating_systems);
  if (debug)
    printf("mask = %d  ", mask);

  switch (reading_state) {
  case reading_family:
    {
      field = family->fd_os_availability;
      if (type==only)
	mask = ~mask;
      field |= mask;
      family->fd_os_availability = field;
      break;
    }
  case reading_bundle:
    {
      field = bundle->bdl_os_availability;
      if (type==only)
	mask = ~mask;
      field |= mask;
      bundle->bdl_os_availability = field;
      break;
    }
  case reading_component:
    {
      field = component->cp_os_availability;
      if (type==only)
	mask = ~mask;
      field |= mask;
      component->cp_os_availability = field;
      break;
    }
  case reading_part:
    {
      field = part->pt_os_availability;
      if (type==only)
	mask = ~mask;
      field |= mask;
      part->pt_os_availability = field;
      break;
    }
  default:
    {
      if (debug)
	printf("\nset_availability: Should not have gotten here\n");
      if (fail_on_first_error) {
	/* throw */
      }
      break;
    }
  }
  if (debug)
    printf("field = %d\n", field);
}


/*****************************************************************
 *   Decoders and encoders for symbolic shortcut information
 *****************************************************************/

int encode_shortcut_run_style (name)
char* name;
{
  if ( !strcmp(name, "normal") )
    return normal;
  else if ( !strcmp(name, "minimized") )
    return minimized;
  else
    return 0; /* Noticed during the scan phase. */
}

char* decode_shortcut_run_style (enum_element)
int enum_element;
{
  switch (enum_element) {
  case normal:
    return "normal";
  case minimized:
    return "minimized";
  default:
    return "unknown";
  }
}

int encode_shortcut_type (name)
char* name;
{
  if ( !strcmp(name, "common") )
    return common;
  else if ( !strcmp(name, "personal") )
    return personal;
  else if ( !strcmp(name, "automatic") )
    return automatic;
  else
    return 0; /* Noticed during the scan phase. */
}

char* decode_shortcut_type (enum_element)
int enum_element;
{
  switch (enum_element) {
  case common:
    return "common";
  case personal:
    return "personal";
  case automatic:
    return "automatic";
  default:
    return "unknown";
  }
}


/*****************************************************************
 *  Decoders and encoders for environment variable types (effects)
 *****************************************************************/

int encode_environent_variable_effect (name)
char* name;
{
  if ( !strcmp(name, "new") )
    return new_var;
  else if ( !strcmp(name, "append") )
    return append;
  else if ( !strcmp(name, "merge") )
    return merge;
  else if ( !strcmp(name, "replace") )
    return replace;
  else
    return 0;
}

char* decode_environment_variable_effect (enum_element)
int enum_element;
{
  switch (enum_element) {
  case new_var:
    return "new";
  case append:
    return "append";
  case merge:
    return "merge";
  case replace:
    return "replace";
  default:
    return "unknown";
  }
}



/*****************************************************************
 *                  Basic constructors
 ****************************************************************/

/* The 'new' functions create empty structures with default values.
 * They are called from the 'start' functions. */

FAMILY_DESCRIPTOR* new_family ()
{
  FAMILY_DESCRIPTOR* family;
  family = (FAMILY_DESCRIPTOR*)malloc (sizeof (FAMILY_DESCRIPTOR));
  family->fd_installer_version = 127; /* outside a plausible range */
  family->fd_name = NULL;
  family->fd_id = (unsigned char)NULL;
  family->fd_splash_screen = NULL;
  family->fd_readme = NULL;
  family->fd_license_text = NULL;
  family->fd_guid = NULL;
  family->fd_version = NULL;
  family->fd_directory_name = NULL;
  family->fd_prev_versions = NULL;
  family->fd_first_bundle = NULL;
  return family;
}

BUNDLE* new_bundle ()
{
  BUNDLE* return_bundle;
  return_bundle = (BUNDLE*)malloc (sizeof (BUNDLE));
  return_bundle->bdl_id= 0xff;
  return_bundle->bdl_name = NULL;
  return_bundle->bdl_version = NULL;
  return_bundle->bdl_visible = TRUE;
  return_bundle->bdl_directory_name = NULL;
  return_bundle->bdl_first_component = NULL;
  return_bundle->bdl_next_bundle = NULL;
  return_bundle->bdl_typical_only = FALSE;
  return return_bundle;
}

COMPONENT* new_component ()
{
  COMPONENT* return_component;
  return_component = (COMPONENT*)malloc (sizeof (COMPONENT));
  return_component->cp_index = 200; /* max. is 60 */
  return_component->cp_button_group = 0;
  return_component->cp_typical = TRUE;
  return_component->cp_optional = FALSE;
  return_component->cp_watermark = NULL;
  return_component->cp_java_requirement = NULL;
  return_component->cp_first_part =  NULL;
  return_component->cp_next_component = NULL;
  return return_component;
}

PART* new_part ()
{
  PART* return_part;
  return_part = (PART*)malloc (sizeof (PART));
  return_part->pt_name = NULL;
  return_part->pt_postinstall_code = NULL;
  return_part->pt_preinstall_code = NULL;
  return_part->pt_uninstall_code = NULL;
  return_part->pt_register = FALSE;
  return_part->pt_first_shortcut = NULL;
  return_part->pt_first_env_var = NULL;
  return_part->pt_first_file_data = NULL;
  return_part->pt_first_reg_object = NULL;
  return_part->pt_next_part = NULL;
  return return_part;
}

FILE_DATA* new_file_data ()
{
  FILE_DATA* new_fd;
  new_fd = (FILE_DATA*)malloc (sizeof (FILE_DATA));
  new_fd->fd_source_directory = NULL;
  new_fd->fd_destination_directory = NULL;
  new_fd->fd_source_name = NULL;
  new_fd->fd_destination_name = NULL;
  new_fd->fd_obfuscate = FALSE;
  new_fd->fd_next_file_data = NULL;
  return new_fd;
}

SHORTCUT* new_shortcut ()
{
  SHORTCUT* sc;
  sc = (SHORTCUT*)malloc (sizeof (SHORTCUT));
  sc->sc_folder = NULL;
  sc->sc_subfolder = NULL;
  sc->sc_subsubfolder = NULL;
  sc->sc_display_name = NULL;
  sc->sc_directory = NULL;
  sc->sc_target_name = NULL;
  sc->sc_parameters = NULL;
  sc->sc_icon_file = NULL;
  sc->sc_icon_index = 0;
  sc->sc_type = automatic;
  sc->sc_run_style = normal;
  sc->sc_next_shortcut = NULL;
  return sc;
}

ENV_VAR* new_env_var ()
{
  ENV_VAR* new_ev;
  new_ev = (ENV_VAR*)malloc (sizeof (ENV_VAR));
  new_ev->ev_name = NULL;
  new_ev->ev_value = NULL;
  new_ev->ev_effect = 200;
  new_ev->ev_next_env_var = NULL;
  new_ev->ev_component_name = NULL;
  return new_ev;
}

REGISTRATION* new_registration ()
{
  REGISTRATION* new_rg = (REGISTRATION*)malloc(sizeof(REGISTRATION));
  new_rg->rg_path = NULL;
  new_rg->rg_name = NULL;
  new_rg->rg_key_name = NULL;
  new_rg->rg_value = NULL;
  new_rg->rg_next_reg_object = NULL;
  return new_rg;
}

PREV_VERSION *new_prev_version ()
{
  PREV_VERSION *return_prev_version;
  return_prev_version
    = (PREV_VERSION*)malloc(sizeof (PREV_VERSION));

  return_prev_version->pv_guid = NULL;
  return_prev_version->pv_version = NULL;
  return_prev_version->pv_next = NULL;
  return return_prev_version;
}



/* The 'add' functions presume that the global variable that holds
 * the next higher-up structure has a value (i.e. add_bundle_to_family
 * _file assumes that family has a proper value) and extend their
 * linked lists. They are called from the 'start' functions. */

void add_bundle_to_family_file (new_bundle)
BUNDLE *new_bundle;
{
  BUNDLE *next_bundle;
  if ( family->fd_first_bundle == NULL )
    family->fd_first_bundle = new_bundle;
  else {
    next_bundle = family->fd_first_bundle;
    for (;;) {
      if ( next_bundle->bdl_next_bundle == NULL ) {
	next_bundle->bdl_next_bundle = new_bundle;
	return;
      } else
	next_bundle = next_bundle->bdl_next_bundle;
    } 
  }
}

void add_env_var_to_part (new_ev)
ENV_VAR* new_ev;
{
  ENV_VAR *next_env_var;
  if ( part->pt_first_env_var == NULL )
    part->pt_first_env_var = new_ev;
  else {
    next_env_var = part->pt_first_env_var;
    for (;;) {
      if ( next_env_var->ev_next_env_var == NULL ) {
	next_env_var->ev_next_env_var = new_ev;
	return;
      } else
	next_env_var = next_env_var->ev_next_env_var;
    }
  }
}

void add_component_to_bundle (new_component)
COMPONENT *new_component;
{
  COMPONENT *next_component;
  if ( bundle->bdl_first_component == NULL )
    bundle->bdl_first_component = new_component;
  else {
    next_component = bundle->bdl_first_component;
    for (;;) {
      if ( next_component->cp_next_component == NULL ) {
	next_component->cp_next_component = new_component;
	return;
      } else
	next_component = next_component->cp_next_component;
    }
  }
}


void add_prev_version_to_family (new_prev)
PREV_VERSION *new_prev;
{
  PREV_VERSION *next_prev;
  if (family->fd_prev_versions == NULL)
    family->fd_prev_versions = new_prev;
  else {
    next_prev = family->fd_prev_versions;
    for (;;) {
      if ( next_prev->pv_next == NULL ) {
	next_prev->pv_next = new_prev;
	return;
      } else
	next_prev = next_prev->pv_next;
    }
  }
}

void check_null_field(char *field, char* containername, char* prettyname)
{
  if (field == NULL || strcmp(field,"") == 0)
    printf("WARNING:  %s has no %s entry.  Visual Basic interface to InstallShield will have problems.\n",containername, prettyname);
}

void add_shortcut_to_part (new_shortcut)
SHORTCUT *new_shortcut;
{
  SHORTCUT *next_sc;
  if ( part->pt_first_shortcut == NULL )
    part->pt_first_shortcut = new_shortcut;
  else {
    next_sc = part->pt_first_shortcut;
    for (;;) {
      if ( next_sc->sc_next_shortcut == NULL ) {
	next_sc->sc_next_shortcut = new_shortcut;
	check_null_field(next_sc->sc_display_name, "Shortcut", "DISPLAY NAME");
	return;
      } else
	next_sc = next_sc->sc_next_shortcut;
    }
  }
}

void add_part_to_component (new_part)
PART *new_part;
{
  PART *next_part;
  if ( component->cp_first_part == NULL )
    component->cp_first_part = new_part;
  else {
    next_part = component->cp_first_part;
    for (;;) {
      if ( next_part->pt_next_part == NULL ) {
	next_part->pt_next_part = new_part;
	return;
      } else
	next_part = next_part->pt_next_part;
    }
  }
}

void add_file_to_part (new_file_data)
FILE_DATA *new_file_data;
{
  FILE_DATA *next_fd;
  if ( part->pt_first_file_data == NULL )
    part->pt_first_file_data = new_file_data;
  else {
    next_fd = part->pt_first_file_data;
    for (;;) {
      if ( next_fd->fd_next_file_data == NULL ) {
	next_fd->fd_next_file_data = new_file_data;
	check_null_field(next_fd->fd_source_name,"File Data","SOURCE");
	return;
      } else
	next_fd = next_fd->fd_next_file_data;
    }
  }
}
 

void add_registration_to_part (new_reg)
REGISTRATION *new_reg;
{
  REGISTRATION *next_reg;
  if ( part->pt_first_reg_object == NULL )
    part->pt_first_reg_object = new_reg;
  else {
    next_reg = part->pt_first_reg_object;
    for (;;) {
      if ( next_reg->rg_next_reg_object == NULL ) {
	next_reg->rg_next_reg_object = new_reg;
	return;
      } else
	next_reg = next_reg->rg_next_reg_object;      
    }
  }
}
   

/* The 'start' functions are called from the state machine when the
 * beginning of a new object has been detected. */


void start_bundle (name)
char* name;
{
  bundle = new_bundle();
  initialize_availability(reading_bundle);
  bundle->bdl_name = name;
  check_null_field(name,"Bundle","NAME");
  add_bundle_to_family_file(bundle);
}

void start_component (name)
char* name;
{
  /* COMPONENT *shared; */
  component = new_component();
  initialize_availability(reading_component);
  component->cp_name = name;
  check_null_field(name,"Component","NAME");
  add_component_to_bundle(component);
  /*  if ( is_a_shared_component(shared, name) ) {
    component->cp_include_by_default = shared->cp_include_by_default;
    component->cp_first_part = shared->cp_first_part; 
  } */
}

void start_prev_version (version)
char* version;
{
  prev_version = new_prev_version();
  prev_version->pv_version = version;
  check_null_field(version,"Previous Version","VERSION");
  add_prev_version_to_family(prev_version);
}

void start_part (name)
char* name;
{
  part = new_part();
  initialize_availability(reading_part);
  part->pt_name = name;
  check_null_field(name,"Part","NAME");
  add_part_to_component(part);
}

void start_file_data ()
{
  file = new_file_data();
  add_file_to_part(file);
}


void copy_ongoing_file_data ( already_copied_filename )
char* already_copied_filename;
{
  FILE_DATA *new_fd;
  new_fd = new_file_data();
  new_fd->fd_source_directory = file->fd_source_directory;
  new_fd->fd_destination_directory = file->fd_destination_directory;
  new_fd->fd_source_name = already_copied_filename;
  add_file_to_part(new_fd);
  file = new_fd;
}

void start_shortcut ()
{
  shortcut = new_shortcut();
  add_shortcut_to_part(shortcut);
}


void start_environment_variable (name)
char* name;
{
  environment_variable = new_env_var();
  environment_variable->ev_name = name;
  check_null_field(name,"Env Var","NAME");
  add_env_var_to_part(environment_variable);
}

void set_environment_variable_value (value)
char* value;
{
  environment_variable->ev_value = value;
  /* printf("\n\nvalue = %s\n\n", value); */
}

void set_environment_variable_effect (enum_value)
int enum_value;
{
  environment_variable->ev_effect = enum_value;
  /*environment_variable = NULL; */
  /* Resetting the global lets us make sure that the right
     values and effects go with the right variables by
     ensuring that these little sections that
     define environment variables always start with the
     name of the variable -- see state machine. */
}

void start_registration (name)
char* name;
{
  registration = new_registration();
  registration->rg_name = name;
  check_null_field(name,"Registration","NAME");
  add_registration_to_part(registration);
}



/* The notion of a shared component is still being debugged. It will
 * be a component that is included in several bundles. Listing its
 * parts once at the beginnin of the file should make them easier to
 * maintain. They wil be indicated by a special tag: 'shared_component'. */

void initialize_bundle_of_shared_components ()
{
  if (shared_components == NULL) {
    bundle = new_bundle();
    bundle->bdl_name = "Shared Components";
    shared_components = bundle;
  }
}

int is_a_shared_component (shared, name)
COMPONENT *shared;
char *name;
{
  COMPONENT *c;
  if (shared_components!=NULL) {
    c = shared_components->bdl_first_component;
    if (!strcmp( c->cp_name, name)) {
      shared = c;
      return TRUE;
    } 
    else {
      for (;;) {
	if (c->cp_next_component == NULL)
	  return FALSE;
	else {
	  c = c->cp_next_component;
	  if (!strcmp( c->cp_name, name)) {
	    shared = c;
	    return TRUE;
	  }
	}
      }
    }
  }
  else
    return FALSE; /* error case! */
}




/*****************************************************************
 *      The set of tags this reader understands
 ****************************************************************/

/* The symbols in the enum are what the massive switch statement
 * in parse_family_file (our state machine) dispatches off of.
 * What actually appears as the tag in the family descriptor file
 * is often different since we allow interior whitespace in the
 * tags. The correspondence is determined by reify_tag_string.
 */

enum TAG {
  /* family level (top level) 
   * Also includes 'index', which at this level is the id of the
   * family file per se. */
  syntax_version,
  family_name,
  splash_screen,
  readme,
  license_text,
  guid,
  previous_version,
  previous_version_guid,
  fd_version,
  directory_name,
  shared_component,

  /* bundle level */
  bundle_name,
  id,
  version,
  component_name,
  typical_only,

  /* component level */
  index_number,
  button_group,
  watermark,
  java_requirement,
  typical,
  optional,

  /* part level */
  part_name,
  postinstall_code,
  preinstall_code,
  uninstall_code,
  register_it,
  beginning_of_shortcut,
  env_var,
  env_var_value,
  env_var_effect,

  /* file_data level (within parts) */
  source_directory,
  destination_directory,
  filename,
  new_filename,
  obfuscate,

  /* all levels */
  only_on,
  on_all_but,

  /* shortcuts */
  sc_folder,
  sc_subfolder,
  sc_subsubfolder,
  sc_display_name,
  sc_directory,
  sc_target_name,
  sc_parameters,
  sc_icon_file,
  sc_icon_index,
  sc_type,
  sc_run_style,
  
  /* registration */
  registration_start,
  rg_path,
  rg_key_name,
  rg_name,
  rg_value,

  unknown_tag
};

int reify_tag_string (symbolic_tag)
char* symbolic_tag;
{
  enum TAG tag;
  convert_to_lowercase(symbolic_tag);

  if (!strcmp(symbolic_tag, "family file syntax version"))
    tag = syntax_version;
  else if (!strcmp(symbolic_tag, "only on"))
    tag = only_on;
  else if (!strcmp(symbolic_tag, "on all but"))
    tag = on_all_but;
  else if (!strcmp(symbolic_tag, "family"))
    tag = family_name;
  else if (!strcmp(symbolic_tag, "version"))
    tag = version;
  else if (!strcmp(symbolic_tag, "splash screen"))
    tag = splash_screen;
  else if (!strcmp(symbolic_tag, "readme"))
    tag = readme;
  else if (!strcmp(symbolic_tag, "license text"))
    tag = license_text;
  else if (!strcmp(symbolic_tag, "guid"))
    tag = guid;
  else if (!strcmp(symbolic_tag, "previous version"))
    tag = previous_version;
  else if (!strcmp(symbolic_tag, "previous version guid"))
    tag = previous_version_guid;
  else if (!strcmp(symbolic_tag, "family version"))  /* require "family "  to distinguish from bundle version. -mhd */
    tag = fd_version;
  else if (!strcmp(symbolic_tag, "directory name"))
    tag = directory_name;
  else if (!strcmp(symbolic_tag, "env variable"))
    tag = env_var;
  else if (!strcmp(symbolic_tag, "env value"))
    tag = env_var_value;
  else if (!strcmp(symbolic_tag, "env effect"))
    tag = env_var_effect;
  else if (!strcmp(symbolic_tag, "shared component"))
    tag = shared_component;
  else if (!strcmp(symbolic_tag, "bundle"))
    tag = bundle_name;
  else if (!strcmp(symbolic_tag, "component"))
    tag = component_name;
  else if (!strcmp(symbolic_tag, "typical only"))
    tag = typical_only;
  else if (!strcmp(symbolic_tag, "id"))
    tag = index_number;
  else if (!strcmp(symbolic_tag, "index"))
    tag = index_number;
  else if (!strcmp(symbolic_tag, "watermark"))
    tag = watermark;
  else if (!strcmp(symbolic_tag, "java requirement"))
    tag = java_requirement;
  else if (!strcmp(symbolic_tag, "radio button group index"))
    tag = button_group;
  else if (!strcmp(symbolic_tag, "typical"))
    tag = typical;
  else if (!strcmp(symbolic_tag, "optional"))
    tag = optional;
  else if (!strcmp(symbolic_tag, "part"))
    tag = part_name;
  else if (!strcmp(symbolic_tag, "postinstall code"))
    tag = postinstall_code;
  else if (!strcmp(symbolic_tag, "preinstall code"))
    tag = preinstall_code;
  else if (!strcmp(symbolic_tag, "uninstall code"))
    tag = uninstall_code;
  else if (!strcmp(symbolic_tag, "sourcedir"))
    tag = source_directory;
  else if (!strcmp(symbolic_tag, "destdir"))
    tag = destination_directory;
  else if (!strcmp(symbolic_tag, "filename"))
    tag = filename;
  else if (!strcmp(symbolic_tag, "new filename"))
    tag = new_filename;
  else if (!strcmp(symbolic_tag, "obfuscate"))
    tag = obfuscate;
  else if (!strcmp(symbolic_tag, "register"))
    tag = register_it;
  else if (!strcmp(symbolic_tag, "shortcut"))
    tag = beginning_of_shortcut;
  else if (!strcmp(symbolic_tag, "folder name"))
    tag = sc_folder;
  else if (!strcmp(symbolic_tag, "subfolder name"))
    tag = sc_subfolder;
  else if (!strcmp(symbolic_tag, "subsubfolder name"))
    tag = sc_subsubfolder;
  else if (!strcmp(symbolic_tag, "application display name"))
    tag = sc_display_name;
  else if (!strcmp(symbolic_tag, "application directory"))
    tag = sc_directory;
  else if (!strcmp(symbolic_tag, "target name"))
    tag = sc_target_name;
  else if (!strcmp(symbolic_tag, "parameters"))
    tag = sc_parameters;
  else if (!strcmp(symbolic_tag, "run style"))
    tag = sc_run_style;
  else if (!strcmp(symbolic_tag, "icon file"))
    tag = sc_icon_file;
  else if (!strcmp(symbolic_tag, "icon index"))
    tag = sc_icon_index;
  else if (!strcmp(symbolic_tag, "type"))
    tag = sc_type;
  else if (!strcmp(symbolic_tag, "registry entry"))
    tag = registration_start;
  else if (!strcmp(symbolic_tag, "key path"))
    tag = rg_path;
  else if (!strcmp(symbolic_tag, "key name"))
    tag = rg_key_name;
  else if (!strcmp(symbolic_tag, "key value"))
    tag = rg_value;
  /*
  else if (!strcmp(symbolic_tag, ""))
    tag = ;
  */

  else  
    tag = unknown_tag;

  return tag;
}



/*****************************************************************
 *   The state machine that drives the whole operation
 *****************************************************************/

/* Parse_family_file returns 0 if no syntactic problems were detected
 * and a positive integer otherwise. For 'semantic' problems see
 * vet_family_descriptor. */

int scan_family_file (family_to_populate)
FAMILY_DESCRIPTOR *family_to_populate;
{
  enum STATE state;
  enum TAG tag;
  SYNTAX_ERROR status;
  char tag_string[MAX_TAG_LENGTH];
  char value_string[MAX_VALUE_LENGTH];
  int decoded_value;
  int line_number = 0;

  /* 'family' is global in this file and is referenced in the
   * add routines. */
  family = family_to_populate;
  initialize_availability(reading_family);

  state = reading_family;

  for (;;) {

    status = parse_line(tag_string, value_string);
    line_number++;

    if (debug_parser)
      printf("\nLine %d: parser returned '%s'", 
	     line_number, error_symbol(status));

    /* check error returns */
    switch (status) {
    case ok: 
      break;
    case content_line_without_colon:
      {
	/* Presently hits on blank lines. Has to be refined. */
	continue;
      }
    case no_value:
      {
	if ((strcmp(tag_string, "part")!=0)
	    || (strcmp(tag_string, "register")!=0)) {
	  if (debug_family_files)
	    printf("\n Error line %d: no value given for the tag %s",
		   line_number, tag_string);
	  return no_value;
	}
      }
    case end_of_file:
      {
	return 0;
      }
    default:
      {
	if (debug_family_files)
	    printf("\nUnspecified notational problem, line %d", line_number);
	return status;
      }
    }

    if (trace)
      printf("\nline %d: Q: %s  \"%s\" : \"%s\"",
	     line_number, state_symbol(state), tag_string, value_string);

    tag = reify_tag_string(tag_string);

    switch (state) {
    case reading_family:
      {  
	switch (tag) {
	case syntax_version:
	  {
	    family->fd_installer_version = convert_to_int(value_string);
	    break;
	  }
	case family_name: 
	  {
	    family->fd_name = copy_string(value_string);
	    break;
	  }
	case index_number:
	  {
	    family->fd_id = convert_to_int(value_string);
	    break;
	  }
	case splash_screen:
	  {
	    family->fd_splash_screen = copy_string(value_string);
	    break;
	  }
	case readme:
	  {
	    family->fd_readme = copy_string(value_string);
	    break;
	  }
	case license_text:
	  {
	    family->fd_license_text = copy_string(value_string);
	    break;
	  }
	case guid:
	  {
	    family->fd_guid = copy_string(value_string);
	    break;
	  }
	case previous_version:
	  {
	    /* This, previous_version, must come in a pair with the following,
	     previous_version_guid, this must come first.  */	    
	    start_prev_version(copy_string(value_string));
	    break;
	  }
	case previous_version_guid:
	  {
	    if (family->fd_prev_versions == NULL) {
	      /* Note: this just catches the problem of the first guid coming
		 before the first version.  Other cases, sadly, will just lead
		 to corrupted previous installs; this should be checked in the
		 resulting generated installshield setups. */
	      if (debug_family_files)
		printf("\nLine %d: 'previous version guid' must come after 'previous version': '%s'\n",
		       line_number, value_string);
	      return previous_version_guid_before_version;
	    }
	    prev_version->pv_guid = copy_string(value_string);
	    break;
	  }
	case fd_version:
	  {
	    family->fd_version = copy_string(value_string);
	    break;
	  }
	case directory_name:
	  {
	    family->fd_directory_name = copy_string(value_string);
	    break;
	  }
	case only_on:
	  {
	    set_availability(copy_string(value_string), state, only);
	    break;
	  }
	case on_all_but:
	  {
	    set_availability(copy_string(value_string), state, all_but);
	    break;
	  }
	case shared_component:
	  {
	    initialize_bundle_of_shared_components();
	    state = reading_component;
	    if (trace)
	      printf("\n Q -> Component");
	    start_component( copy_string(value_string) );
	    break;
	  }


	/* Once all the data about the family proper has been collected,
	   we expect to see the start of a bundle. This is the only
	   legal state-transition out of reading_family. */
	case bundle_name:
	  {
	    state = reading_bundle;
	    if (trace)
	      printf("\n  Q -> Bundle");
	    start_bundle( copy_string(value_string) );
	    break;
	  }

	case unknown_tag:
	  {
	    if (debug_family_files)
	      printf("\nLine %d: Family level unknown tag \"%s\"", 
		     line_number, tag_string);
	    break;
	  }
	default:
	  {
	    if (debug_family_files)
	      printf("\nLine %d, Q = reading_family  Unexpected tag: %s\n", 
		     line_number, tag_string);
	    break;
	  }
	}
	break;
      }


    case reading_bundle:
      {
	switch (tag) {
	case index_number:
	  {
	    bundle->bdl_id = convert_to_int(value_string);
	    break;
	  }
	case version:
	  {
	    bundle->bdl_version = copy_string(value_string);
	    break;
	  }
	case only_on:
	  {
	    set_availability(copy_string(value_string), state, only);
	    break;
	  }
	case on_all_but:
	  {
	    set_availability(copy_string(value_string), state, all_but);
	    break;
	  }
	case directory_name:
	  {
	    bundle->bdl_directory_name = copy_string(value_string);
	    break;
	  }

	case typical_only:
	  {
	    bundle->bdl_typical_only = encode_boolean(value_string);
	    break;
	  }	    


	/* The only legal transition out of reading bundle-proper
	   information is the start of a component. A bundle without
	   components is undefined. */
	case component_name:
	  {
	    state = reading_component;
	    if (trace)
	      printf("\n Q -> Component");
	    start_component( copy_string(value_string) );
	    break;
	  }

	case unknown_tag:
	  {
	    if (debug_family_files)
	      printf("\nLine %d: Bundle level unknown tag \"%s\"", 
		     line_number, tag_string);
	    break;
	  }
	default:
	  {
	    if (debug_family_files)
	      printf("\nLine %d, Q = reading_bundle  Unexpected tag: %s\n", 
		     line_number, tag_string);
	    break;
	  }
	}
	break;
      }


    case reading_component:
      {
	switch (tag) {
	case index_number:
	  {
	    component->cp_index = convert_to_int(value_string);
	    break;
	  }
	case watermark:
	  {
	    component->cp_watermark = copy_string(value_string);
	    break;
	  }
	case button_group:
	  {
	    component->cp_button_group = convert_to_int(value_string);
	    break;
	  }
	case java_requirement:
	  {
	    component->cp_java_requirement = copy_string(value_string);
	    break;
	  }
	case typical:
	  {
	    decoded_value = encode_boolean(value_string);
	    if ((decoded_value == UNKNOWN_VALUE)
		&& (fail_on_first_error)) {
	      if (debug_family_files)
		printf("\nLine %d: Unexpected value of typical tag: '%s'\n",
		       line_number, value_string);
	      return unknown_value_for_typical;
	    }
	    else
	      component->cp_typical = decoded_value;
	    break;
	  }
	case optional:
	  {
	    decoded_value = encode_boolean(value_string);
	    if ((decoded_value == UNKNOWN_VALUE)
		&& (fail_on_first_error)) {
	      if (debug_family_files)
		printf("\nLine %d: Unexpected value of optional tag: '%s'\n",
		       line_number, value_string);
	      return unknown_value_for_optional;
	    }
	    else
	      component->cp_optional = decoded_value;
	    break;
	  }
	case only_on:
	  {
	    set_availability(copy_string(value_string), state, only);
	    break;
	  }
	case on_all_but:
	  {
	    set_availability(copy_string(value_string), state, all_but);
	    break;
	  }
	case component_name:
	  {
	    state = reading_component;
	    if (trace)
	      printf("\n Q -> Component");
	    start_component( copy_string(value_string) );
	    break;
	  }
	case bundle_name:
	  {
	    state = reading_bundle;
	    if (trace)
	      printf("\n Q -> Bundle");
	    start_bundle( copy_string(value_string) );
	    break;
	  }
	case part_name:
	  {
	    state = reading_part;
	    if (trace)
	      printf("\n Q -> Part");
	    start_part( copy_string(value_string) );
	    break;
	  }

	case unknown_tag:
	  {
	    if (debug_family_files)
	      printf("\nLine %d: Component level unknown tag \"%s\"", 
		     line_number, tag_string);
	    break;
	  }
	default:
	  {
	    if (debug_family_files)
	      printf("\nLine %d, Q = reading_component  Unexpected tag: %s\n", 
		     line_number, tag_string);
	    break;
	  }
	}
	break;
      }


    case reading_shortcut:
      {
	switch (tag) {
	case sc_folder:
	  {
	    shortcut->sc_folder = copy_string(value_string);
	    break;
	  }
	case sc_subfolder:
	  {
	    shortcut->sc_subfolder = copy_string(value_string);
	    break;
	  }
	case sc_subsubfolder:
	  {
	    shortcut->sc_subsubfolder = copy_string(value_string);
	    break;
	  }
	case sc_display_name:
	  {
	    shortcut->sc_display_name = copy_string(value_string);
	    break;
	  }
	case sc_directory:
	  {
	    shortcut->sc_directory = copy_string(value_string);
	    break;
	  }
	case sc_target_name:
	  {
	    shortcut->sc_target_name = copy_string(value_string);
	    break;
	  }
	case sc_parameters:
	  {
	    shortcut->sc_parameters = copy_string(value_string);
	    break;
	  }
	case sc_icon_file:
	  {
	    shortcut->sc_icon_file = copy_string(value_string);
	    break;
	  }
	case sc_icon_index:
	  {
	    shortcut->sc_icon_index = convert_to_int(value_string);
	    break;
	  }
	case sc_type:
	  {
	    decoded_value = encode_shortcut_type(value_string);
	    if ((decoded_value == 0)
		&& (fail_on_first_error)) {
	      if (debug_family_files)
		printf("\nLine %d: Unexpected value for 'type' tag %s\n",
		       line_number, value_string);
	      shortcut->sc_type = decoded_value;
	      return unknown_shortcut_type;
	    }
	    else
	      shortcut->sc_type = decoded_value;
	    break;
	  }
	case sc_run_style:
	  {
	    decoded_value = encode_shortcut_run_style(value_string);
	    if ((decoded_value == 0)
		&& (fail_on_first_error)) {
	      if (debug_family_files)
		printf("\nLine %d: Unexpected value for 'style' tag %s\n",
		       line_number, value_string);
	      shortcut->sc_run_style = decoded_value;
	      return unknown_shortcut_run_style;
	    }
	    else
	      shortcut->sc_run_style = decoded_value;
	    break;
	  }

	/* Shortcut has ended and another element has begun. */
	case beginning_of_shortcut:
	  {
	    state = reading_shortcut;
	    start_shortcut();
	    break;
	  }
	case env_var:
	  {
	    state = reading_part;
	    start_environment_variable( copy_string(value_string) );
	    break;
	  }
	case part_name:
	  {
	    state = reading_part;
	    if (trace)
	      printf("\n Q -> Part");
	    start_part( copy_string(value_string) );
	    break;
	  }
	case postinstall_code:
	  {
	    state = reading_part;
	    part->pt_postinstall_code = copy_string(value_string);
	    break;
	  }	  
	case preinstall_code:
	  {
	    state = reading_part;
	    part->pt_preinstall_code = copy_string(value_string);
	    break;
	  }	  
	case uninstall_code:
	  {
	    state = reading_part;
	    part->pt_uninstall_code = copy_string(value_string);
	    break;
	  }	  
	case component_name:
	  {
	    state = reading_component;
	    if (trace)
	      printf("\n Q -> Component");
	    start_component( copy_string(value_string) );
	    break;
	  }
	case bundle_name:
	  {
	    state = reading_bundle;
	    if (trace)
	      printf("\n Q -> Bundle");
	    start_bundle( copy_string(value_string) );
	    break;
	  }

	case unknown_tag:
	  {
	    if (debug_family_files)
	      printf("\nLine %d: Unknown tag see while reading shortcut \"%s\"", 
		     line_number, tag_string);
	    break;
	  }
	default:
	  {
	    if (debug_family_files)
	      printf("\nLine %d, Q = reading_component  Unexpected tag: %s\n", 
		     line_number, tag_string);
	    break;
	  }
	}
	break;
      }


    case reading_part:
      {
	switch (tag) {
	case env_var:
	  {
	    start_environment_variable( copy_string(value_string) );
	    break;
	  }
	case env_var_value:
	  {
	    if ( environment_variable == NULL ) {
	      /* It would be nice if this check acutally worked.  But if you
                 have had an environment variable in the past and now you're
                 starting a new one badly, what you'll do is clobber the first
                 one instead of noticing the error. */
	      if (fail_on_first_error) {
		if (debug_family_files)
		  printf("\nLine %d: Environment var. value out of scope.\n",
			 line_number);
		return ev_value_without_ev;
	      }
	    } else
	      set_environment_variable_value( copy_string(value_string) );
	    break;
	  }
	case env_var_effect:
	  {
	    if ( environment_variable == NULL ) {
	      if (fail_on_first_error) {
		if (debug_family_files)
		  printf("\nEnv.var. effect see outside scope of active environment variable definition\n");
		return ev_effect_without_ev;
	      }
	    } else {
	      decoded_value = encode_environent_variable_effect(value_string);
	      if ((decoded_value == 0)
		  && (fail_on_first_error)) {
		if (debug_family_files)
		  printf("\nUnknown environment variable effect: \"%s\"\n", value_string);
		return invalid_env_var_effect;
	      }
	      else
		set_environment_variable_effect(decoded_value);
	    }
	    break;
	  }

	case source_directory:
	  {
	    start_file_data();
	    file->fd_source_directory = copy_string(value_string);
	    break;
	  }
	case destination_directory:
	  {
	    file->fd_destination_directory = copy_string(value_string);
	    break;
	  }
	case filename:
	  {
	    if (file->fd_source_name != NULL) {
	      copy_ongoing_file_data( copy_string(value_string) );
	    }
	    else {
	      file->fd_source_name = copy_string(value_string);
	    }
	    break;
	  }
	case new_filename:
	  {
	    file->fd_destination_name = copy_string(value_string);
	    break;
	  }
	case obfuscate:
	  {
	    file->fd_obfuscate = encode_boolean(value_string);
	    break;
	  }
	case register_it:
	  {
	    part->pt_register = TRUE;
	    break;
	  }
	case only_on:
	  {
	    set_availability(copy_string(value_string), state, only);
	    break;
	  }
	case on_all_but:
	  {
	    set_availability(copy_string(value_string), state, all_but);
	    break;
	  }
	case beginning_of_shortcut:
	  {
	    state = reading_shortcut;
	    start_shortcut();
	    break;
	  }

	case bundle_name:
	  {
	    state = reading_bundle;
	    if (trace)
	      printf("\n Q -> Bundle");
	    start_bundle( copy_string(value_string) );
	    break;
	  }
	case component_name:
	  {
	    state = reading_component;
	    if (trace)
	      printf("\n Q -> Component");
	    start_component( copy_string(value_string) );
	    break;
	  }
	case shared_component:
	  {
	    /* Shared components must preceed everything else in the
	     * family file. The initialize routine set the global
	     * 'bundle' variable to a dummy that will serve as the
	     * collector for these components and make their processing
	     * transparent. */
	    if ((bundle!=NULL)
		&& (strcmp( bundle->bdl_name, "Shared Components"))) {
	      if (debug)
		printf("\n\n!!! Line %d: A shared component appears after the bundle definitions have begun.\nThe structure of this family descriptor file is invalid\nFurther processing has been aborted", line_number);
	      return -1;
	    }
	    state = reading_component;
	    if (trace)
	      printf("\n Q -> Component");
	    start_component( copy_string(value_string) );
	    break;
	  }
	case part_name:
	  {
	    state = reading_part;
	    if (trace)
	      printf("\n  Starting a new part");
	    start_part( copy_string(value_string) );
	    break;
	  }
	case postinstall_code:
	  {
	    state = reading_part;
	    part->pt_postinstall_code = copy_string(value_string);
	    break;
	  }	  
	case preinstall_code:
	  {
	    state = reading_part;
	    part->pt_preinstall_code = copy_string(value_string);
	    break;
	  }	  
	case uninstall_code:
	  {
	    state = reading_part;
	    part->pt_uninstall_code = copy_string(value_string);
	    break;
	  }	  
	case registration_start:
	  {
	    state = reading_registration;
	    start_registration( copy_string(value_string) );
	    break;
	  }
	case unknown_tag:
	  {
	    if (debug_family_files)
	      printf("\nLine %d: Part level unknown tag \"%s\"", 
		     line_number, tag_string);
	    break;
	  }
	default:
	  {
	    if (debug_family_files)
	      printf("\nLine %d, Q = reading_part  Unexpected tag: %s\n", 
		     line_number, tag_string);
	    break;
	  }
	}
	break;
      }

    case reading_registration:
      {
	switch(tag) {
	case rg_path:
	  {
	    registration->rg_path = copy_string(value_string);
	    break;
	  }
	case rg_key_name:
	  {
	    registration->rg_key_name = copy_string(value_string);
	    break;
	  }
	case rg_value:
	  {
	    registration->rg_value = copy_string(value_string);
	    break;
	}
	  
	case registration_start:
	  {
	    start_registration( copy_string(value_string) );
	    break;
	  }
	/* Registry entry has ended and another element has begun.  Code copied from 
	   reading_shortcut. 
	   See HQ-4711519 State machine in family file reader too complex and buggy */
	case beginning_of_shortcut:
	  {
	    state = reading_shortcut;
	    start_shortcut();
	    break;
	  }
	case env_var:
	  {
	    state = reading_part;
	    start_environment_variable( copy_string(value_string) );
	    break;
	  }
	case part_name:
	  {
	    state = reading_part;
	    if (trace)
	      printf("\n Q -> Part");
	    start_part( copy_string(value_string) );
	    break;
	  }
	case postinstall_code:
	  {
	    state = reading_part;
	    part->pt_postinstall_code = copy_string(value_string);
	    break;
	  }	  
	case preinstall_code:
	  {
	    state = reading_part;
	    part->pt_preinstall_code = copy_string(value_string);
	    break;
	  }	  
	case uninstall_code:
	  {
	    state = reading_part;
	    part->pt_uninstall_code = copy_string(value_string);
	    break;
	  }	  
	case component_name:
	  {
	    state = reading_component;
	    if (trace)
	      printf("\n Q -> Component");
	    start_component( copy_string(value_string) );
	    break;
	  }
	case bundle_name:
	  {
	    state = reading_bundle;
	    if (trace)
	      printf("\n Q -> Bundle");
	    start_bundle( copy_string(value_string) );
	    break;
	  }


	case unknown_tag:
	  {
	    if (debug_family_files)
	      printf("\nLine %d: Registration level unknown tag \"%s\"", 
		     line_number, tag_string);
	    break;
	  }
	default:
	  {
	    if (debug_family_files)
	      printf("\nLine %d, Q = reading_registration  Unexpected tag: %s\n", 
		     line_number, tag_string);
	    break;
	  }
	}
	break;
      }

    default:
      {
	if (debug)
	  printf("\nUnknown state %d\n", state);
      }

    } /* end state-dispatch switch */
  } /* end infinite loop */
}






/*****************************************************************
 *    Sanity checking the data structures after the parse
 *****************************************************************/

/* Vet_family_descriptor checks that the data structure produced by
 * parse_family_file actually has some content, e.g. that there is at least
 * one bundle, with components, with files. It is not in a position to
 * check whether the values make any sense, only that they are there.  This
 * return 0 if none of the elements in the descriptor are vacuous and all
 * required elements are present.  Otherwise it returns a positive integer
 * according to the FD_PROBLEMS enum. It fails on the first instance where
 * there is a problem rather than attempting to explore the entire data
 * structure. */

int vet_family_descriptor (family)
FAMILY_DESCRIPTOR *family;
{
  BUNDLE *bundle;
  COMPONENT *component;
  SHORTCUT *shortcut;
  PART *part;
  FILE_DATA *fd;
  ENV_VAR *env_var;
  REGISTRATION *reg;
  unsigned int os_mask;

  if ( family == NULL ) {
    if (debug_family_files)
      printf("Did not see a family.\n");
    return family_is_null;
  }

  if ( family->fd_installer_version == 200 ) {
    if (debug_family_files)
      printf("No installer version.\n");
    return no_installer_version;
  }
  else if (readout)
    printf("\nInstaller version %d\n", family->fd_installer_version);


  if ( family->fd_name == NULL ) {
    if (debug_family_files)
      printf("No family name.\n");
    return no_family_name;
  }
  else if (readout)
    printf("Family: %s\n", family->fd_name);


  if ( family->fd_id == (unsigned char)NULL ) {
    if (debug_family_files)
      printf("No family id.\n");
    return no_family_id;
  }
  else if (readout)
    printf("  id: %d\n", family->fd_id);


  if ( family->fd_directory_name == NULL ) {
    if (debug_family_files)
      printf("No name given to use for the family's directory");
    return no_directory_name;
  }
  else if (readout)
    printf("  Directory: %s\n", family->fd_directory_name);


  if ( family->fd_first_bundle == NULL ) {
    if (debug_family_files)
      printf("The %s family has no bundles.\n",
	     family->fd_name);
    return family_has_no_bundles;
  }


  bundle = family->fd_first_bundle;
  do {
    if ( bundle->bdl_name == NULL ) {
      if (debug_family_files)
	printf("Bundle with no name.\n");
      return bundle_with_no_name;
    }
    else if (readout)
      printf("\n\nBundle: %s\n", bundle->bdl_name);


    if ( bundle->bdl_id == (unsigned char)NULL ) {
      if (debug_family_files)
	printf("The %s bundle has no id.\n",
	       bundle->bdl_name);
      return bundle_with_no_id;
    }
    else if (readout)
      printf("  id: %d\n", bundle->bdl_id);


    if ( bundle->bdl_version == NULL ) {
      if (debug_family_files)
	printf("No version given for the %s bundle.\n",
	       bundle->bdl_name);
      return bundle_with_no_version;
    }
    else if (readout)
      printf("  version: %s\n", bundle->bdl_version);


    /* OBSOLETE! (MHD/YDUJ 1/11/01)
    if ( bundle->bdl_directory_name == NULL ) {
      if (debug_family_files)
	printf("No name given to use for the bundle's directory");
      return no_directory_name;
    }
    else if (readout)
      printf("  Directory: %s\n", bundle->bdl_directory_name);

      */
    


    if ( bundle->bdl_first_component == NULL ) {
      if (debug_family_files)
	printf("The %s bundle has no components.\n",
	       bundle->bdl_name);
      return bundle_with_no_components;
    }


    component = bundle->bdl_first_component;
    do {
      if ( component->cp_name == NULL ) {
	if (debug_family_files)
	  printf("Component without a name.\n");
	return component_with_no_name;
      }
      else if (readout)
	printf("\nComponent: %s\n", component->cp_name);

      if ( component->cp_index == 200 ) {
	if (debug_family_files)
	  printf("The %s component does not have an index.\n",
		 component->cp_name);
	return component_with_no_index;
      }
      else if (readout)
	printf("  index: %d\n", component->cp_index);

      if (readout) {
	if ( component->cp_typical == TRUE )
	  printf("  Included in typical installations.\n");
	else
	  printf ("  Only included in custom installations.\n");
      }

      if (readout) {
	if ( component->cp_optional == TRUE )
	  printf("  Optional element of the bundle.\n");
	else
	  printf("  Standard element of the bundle.\n");
      }

      if (readout) {
	if ( component->cp_watermark != NULL )
	  printf("  It has a watermark flag: %s\n", component->cp_watermark);
	else
	  printf("  It does not indicate that it should be watermarked.\n");
      }

      if (readout) {
	if ( component->cp_java_requirement != NULL)
	  printf("  It will require Java version %s\n", component->cp_java_requirement);
	else
	  printf("  No Java requirement.\n");
      }

      if (readout) {
	if ( component->cp_button_group != 0 ) /* 0 = not part of a group */
	  printf("  It is part of Button Group %d\n", component->cp_button_group);
	else
	  printf("  It is not part of a button group.\n");
      }



      if ( component->cp_first_part == NULL ) {
	if (debug_family_files)
	  printf("The %s component has no parts.\n",
		 component->cp_name);
	return component_with_no_parts;
      }
      
      part = component->cp_first_part;
      do {
	if (readout)
	  printf("\n  Part: ");
	if (readout) {
	  if ( part->pt_name != NULL )
	    printf("%s\n", part->pt_name);
	  else
	    printf("\n");
	}

	if (readout) {
	  os_mask = part->pt_os_availability;
	  if ( ! os_restriction(os_mask) )
	    printf("    It is available on all platforms.\n");
	  else
	    decode_os_mask(part); /* does the printfs */
	}


	if ( part->pt_first_file_data == NULL ) {
	  if (debug_family_files) {
	    if ( part->pt_name != NULL )
	      printf("No files in part: %s\n", part->pt_name);
	    else
	      printf("Part without any files (no name for the part).\n");
	  }
	  return part_with_no_files;
	}
	    
	fd = part->pt_first_file_data;
	do {
	  if ( fd->fd_source_directory == NULL ) {
	    if (debug_family_files)
	      printf("Part without a source.\n");
	    return part_has_no_source;
	  }
	  else if (readout)
	    printf("    source: %s\n", fd->fd_source_directory);

	  if (readout) {
	    if ( fd->fd_destination_directory == NULL )
	      printf("    Destination is the same as the source.\n");
	    else
	      printf("    destination: %s\n", fd->fd_destination_directory);
	  }

	  if ((fd->fd_source_directory == NULL)
	      && (fd->fd_destination_directory != NULL)) {
	    if (debug_family_files)
	      printf("Part has a destination directory but no source.\n");
	    return directory_destination_without_a_source;
	  }

	  if ((fd->fd_destination_directory == NULL)
	      && (fd->fd_source_name == NULL)) {
	    if (debug_family_files)
	      printf("Part %s has no destination directory but does not specify any specific files", part->pt_name);
	    return no_destination_directory_but_no_file_named;
	  }

	  if (readout) {
	    if ( fd->fd_source_name == NULL )
	      printf("    The entire directory is used.\n");
	    else
	      printf("    file name: %s\n", fd->fd_source_name);
	  }

	  if ((fd->fd_source_name == NULL)
	      && (fd->fd_destination_name != NULL)) {
	    if (debug_family_files)
	      printf("Part has a file destination name but no source name.\n");
	    return file_destination_without_a_source;
	  }

	  if ((readout)
	      && (fd->fd_source_name!=NULL)) {
	    if ( fd->fd_destination_name == NULL )
	      printf("    The file's name is not changed.\n");
	    else
	      printf("    renamed to: %s\n", fd->fd_destination_name);
	  }

	  if (readout) {
	    if ( part->pt_register != FALSE )
	      printf("    It is registered.\n");
	    else
	      printf("    not registered.\n");
	  }

	} while ( fd = fd->fd_next_file_data );



	if ( part->pt_first_shortcut != NULL ) {
	  shortcut = part->pt_first_shortcut;
	  do {
	    if (readout)
	      printf("    Shortcut:\n");
	    if ( shortcut->sc_folder == NULL ) {
	      if (debug_family_files)
		printf("Shortcut without a folder.\n");
	      return shortcut_without_folder;
	    }
	    else if (readout)
	      printf("      folder: %s\n", shortcut->sc_folder);

	    if ( shortcut->sc_subfolder == NULL ) {
	      /* note: it's fine for there to be no subfolder as long
                 as there's no subsubfolder. */
	      if (shortcut->sc_subsubfolder != NULL) {
		if (debug_family_files)
		  printf("Shortcut without a subfolder.\n");
		return shortcut_without_folder; /* overloaded */
	      }
	    }
	    else if (readout)
	      printf("      subfolder: %s\n", shortcut->sc_subfolder);

	    if ( shortcut->sc_subsubfolder == NULL ) {
	      /* note: it's fine for there to be no subsubfolder. */
	    }
	    else if (readout)
	      printf("      subsubfolder: %s\n", shortcut->sc_subsubfolder);

	    if ( shortcut->sc_display_name == NULL ) {
	      if (debug_family_files)
		printf("Shortcut without a display name.\n");
	      return shortcut_without_display_name;
	    }
	    else if (readout)
	      printf("      display_name: %s\n", shortcut->sc_display_name);
	    
	    if ( shortcut->sc_directory == NULL ) {
	      if (debug_family_files)
		printf("Shortcut without a directory.\n");
	      return shortcut_without_directory;
	    }
	    else if (readout)
	      printf("      directory: %s\n", shortcut->sc_directory);

	    if ( shortcut->sc_target_name == NULL ) {
	      if (debug_family_files)
		printf("Shortcut without a target name.\n");
	      return shortcut_without_target_name;
	    }
	    else if (readout) {
	      printf("      target_name: %s\n", shortcut->sc_target_name);
	    }

	    if (readout)
	      if (shortcut->sc_parameters != NULL)
		printf("      parameters: %s\n", shortcut->sc_parameters);
	    
	    if ((readout)
		&& (shortcut->sc_icon_file != NULL))
	      printf("      icon_file: %s\n", shortcut->sc_icon_file);

	    if ((readout)
		/* Initialized to 0. Only report it if it's relevant. */
		&& (shortcut->sc_icon_file != NULL))
	      printf("      icon_index: %d\n", shortcut->sc_icon_index);
	    
	    if (readout)
	      printf("      type: %s\n", 
		     decode_shortcut_type(shortcut->sc_type));

	    if (readout)
	      printf("      runstyle: %s\n", 
		     decode_shortcut_run_style(shortcut->sc_run_style));
	    
	  } while ( shortcut = shortcut->sc_next_shortcut );
	}
	else if (readout)
	  printf("    No shortcuts.\n");



	if ( part->pt_first_env_var != NULL ) {
	  env_var = part->pt_first_env_var;
	  do {
	    /* if they didn't have names they wouldn't have been created. */
	   if (readout)
	      printf("    Environment variable: %s\n", env_var->ev_name);

	   if ( env_var->ev_value == NULL ) {
	      if (debug_family_files)
		printf("Environment variable %s has no value.\n", env_var->ev_name);
	      return ev_var_with_no_value;
	    }
	    else if (readout)
	      printf("      value: %s\n", env_var->ev_value);

	    if ( env_var->ev_effect == 200 ) {
	      if (debug_family_files)
		printf("Environment variable %s doesn't state its effect", 
		       env_var->ev_name);
	      return ev_var_with_no_effect;
	    }
	    else if (readout)
	      printf("      effect: %s\n",
		     decode_environment_variable_effect(env_var->ev_effect));

	  } while ( env_var = env_var->ev_next_env_var );
	}
	else if (readout)
	  printf("    No environment variables.\n");



	if ( part->pt_first_reg_object != NULL ) {
	  reg = part->pt_first_reg_object;
	  do {
	    if (readout) {
	      printf("    Registration:");
	      if ( reg->rg_name != NULL )
		printf("%s\n", reg->rg_name);
	      else
		printf("\n");
	    }
	    if ( reg->rg_path == NULL ) {
	      if (debug_family_files)
		printf("Registration without a path.\n");
	      return reg_with_no_path;
	    } else if (readout)
	      printf("      path: %s\n", reg->rg_path);

	    if ( reg->rg_key_name == NULL ) {
	      if (debug_family_files)
		printf("Registration with no name.\n");
	      return reg_with_no_name;
	    } else if (readout)
	      printf("      key name: %s\n", reg->rg_key_name);

	    if ( reg->rg_value == NULL ) {
	      if (debug_family_files)
		printf("Registration without a value.\n");
	      return reg_with_no_value;
	    } else if (readout)
	      printf("      value: %s\n", reg->rg_value);

	  } while ( reg = reg->rg_next_reg_object );
	}
	else if (readout)
	  printf("    No registrations.\n");



      } while ( part = part->pt_next_part );	

    } while ( component = component->cp_next_component );

  } while ( bundle = bundle->bdl_next_bundle );

  return 0;
}


/*****************************************************************
 *                  Primary entry point
 *****************************************************************/

int parse_family_file (family)
FAMILY_DESCRIPTOR *family;
{
  SYNTAX_ERROR syntactic_status;
  enum FD_PROBLEMS consistency_status;

  syntactic_status = scan_family_file(family);
  if (fail_on_first_error)
    if (syntactic_status != 0)
      return syntactic_status;

  consistency_status = vet_family_descriptor(family);
  return consistency_status;
}
