#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gencodes.h"

#define MAXLINE 256
char majvers[MAXLINE];

/*                                                                  */
/* gen_codes                                                        */
/*                                                                  */
/* If dates are OK, returns generated codes in a string pre-        */
/* allocated by this function's caller and pointed to by s_codes.   */
/* Inputted dates are in the format "29 FEB 72" or are blank for    */
/* permanent authorization.                                         */
/*                                                                  */

short int gen_codes(mach_id, prod, vers, start_date, end_date, s_codes)
     char *mach_id, *prod, *vers, *start_date, *end_date, *s_codes;
{
  long int gener_codes[5];
  register short int n;
  short int permanent;
  char c_start_day[30], c_start_month[30], c_start_year[30],
       c_end_day[30], c_end_month[30], c_end_year[30], extra[30];
  long int w_mach_id, w_prod, w_majvers, start_u_d, end_u_d;
  short int s_start_day, s_start_month, s_start_year,
           s_end_day, s_end_month, s_end_year;

  c_start_day[0] = c_start_month[0] = c_start_year[0] =
    c_end_day[0] = c_end_month[0] = c_end_year[0] = '\0';
  permanent = 0;

  gb_raise_to_uppercase (mach_id);
  remove_whitespace (mach_id);
  gb_raise_to_uppercase (prod);

  gb_raise_to_uppercase (vers);
  major_version(vers, majvers);
  gb_raise_to_uppercase (start_date);
  gb_raise_to_uppercase (end_date);

  if (((n = sscanf (start_date, "%s%s%s%s",
		    c_start_day, c_start_month, c_start_year, extra)) <= 2) &&
      (strlen (c_start_day) <= 2) &&
      (sscanf (end_date, "%s%s%s", c_end_day, c_end_month, c_end_year) <= 2) &&
      (strlen (c_end_day) <= 2)) {
    permanent = 1;
    s_start_day = s_start_month = s_start_year =
      s_end_day = s_end_month = s_end_year = 0;
  } else if (n != 3) {
    printf ("GSI Authorization: FROM date is in wrong format.\n");
    return ((short) FALSE);
  } else if ((n = sscanf (end_date, "%s%s%s%s",
			  c_end_day, c_end_month, c_end_year, extra)) != 3) {
    printf ("GSI Authorization: TO date is in wrong format.\n");
    return ((short) FALSE);
  }

  if ((!permanent) &&
      (verify_char_dates (c_start_day, c_start_month, c_start_year,
			  c_end_day, c_end_month, c_end_year,
			  &s_start_day, &s_start_month, &s_start_year,
			  &s_end_day, &s_end_month, &s_end_year) == NOT_OK))
    return ((short) FALSE);
  if (calc_universal_dates (s_start_day, s_start_month, s_start_year,
			    s_end_day, s_end_month, s_end_year,
			    &start_u_d, &end_u_d) == NOT_OK)
    return ((short) FALSE);

  f ((w_mach_id = weighted_value (mach_id)),
     (w_prod    = weighted_value (prod)),
     (w_majvers = weighted_value (majvers)),
     start_u_d,
     end_u_d,
     gener_codes);

  g (w_mach_id,
     w_prod,
     w_majvers,
     start_u_d,
     end_u_d,
     gener_codes);

  sprintf (s_codes, "%ld %ld %ld %ld %ld",
           gener_codes[0],
           gener_codes[1],
           gener_codes[2],
           gener_codes[3],
           gener_codes[4]);
  return ((short) TRUE);
}


long main()
{
  extern long g2ext_nsleep();
  char gMachineID[64];
  char gProduct[64];
  char gVersion[64];
  char gStartDate[64];
  char gEndDate[64];
  char gCodes[256];
  char buffer[256];

  //prod, vers, start_date, end_date, s_codes
  printf("========================================================\n");
  printf(" GENCODES VERSION 2\n");
  printf("========================================================\n\n");


  g2ext_nsleep ((char *) buffer);  /* get machine ID */

  do {
    printf("MachineID (%s): ",buffer);
    gets(gMachineID);
    if (*gMachineID == 0)
      strcpy(gMachineID,buffer);
  } while (*gMachineID == 0);

  do {
    printf("Product  \t\t: ");
    gets(gProduct);
  } while (*gProduct == 0);

  do {
    printf("Version  \t\t: ");
    gets(gVersion);
  } while (*gVersion == 0);

  printf("Start Date (d mmm yy)\t: ");
  gets(gStartDate);

  printf("End Date (d mmm yy)\t: ");
  gets(gEndDate);

  printf("\n");

  gen_codes(gMachineID,gProduct,gVersion,gStartDate,gEndDate,gCodes);

  printf("Codes:\n  %s\n\n",gCodes);

  if (*gStartDate == 0 || *gEndDate == 0)
	  printf("OK File Entry:\n  <name> %s %s %s %s\n",gMachineID,gProduct,majvers,gCodes);
  else
    printf("OK File Entry:\n  <name> %s %s %s from %s to %s %s\n",gMachineID,gProduct,majvers,gStartDate,gEndDate,gCodes);

  printf("\n\n<hit any key to exit>");
  getchar();

  return 0;
}

