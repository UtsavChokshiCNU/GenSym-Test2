#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "gsi_main.h"
#include "gsiaxlmisc.h"
#include <tchar.h>

/* GSI String Utilities: */

int gsirtl_strlen(gsi_char *str)
{
  int i = 0;
  while (*str != '\0') {
    str++;
    i++;
  }
  return i;
}



gsi_char *gsirtl_strcpy(gsi_char *dst, char *src)
{
  gsi_char *dstptr = dst;

  while (1) {
    if((*dstptr = *src) == (gsi_char)'\0')
      break;
    dstptr++;
    src++;
  }
  return dst;
}


gsi_char *gsirtl_strdup(char *str)
{
  gsi_char *copy = (gsi_char *)malloc(sizeof(gsi_char) * (strlen(str) + 1));

  return gsirtl_strcpy(copy, str);
}


int gsirtl_strcmp(gsi_char *str1, gsi_char *str2)
{
  int i;
  gsi_char c1, c2;
  gsi_char nul = (gsi_char)0;

  i = 0;
  while(1) {
    c1 = str1[i];
    c2 = str2[i];

    i++;
    
    if (c1 == nul)
      if (c2 == nul)
	return 0;
      else
	return (- i);
    else if (c2 == nul)
      return i;
    else if (c1 < c2)
      return (- i);
    else if (c1 > c2)
      return i;
  }
}


char *gsirtl_strcpy_gsi_char_to_char (char *dst, gsi_char *src)
{
  char *dstptr = dst;
  gsi_char c;

  while (1) {
    c = *src;

#ifdef GSI_USE_WIDE_STRING_API
    /* note: characters codes > 255 => '?'; Fine for Latin 1 text only, not
       great for others! */
    if (c > 0xFF)
      c = (gsi_char)'?';
#endif

    if((*dstptr = (char)c) == (char)'\0')
      break;
    dstptr++;
    src++;
  }
  return dst;
}


char *gsirtl_strdup_gsi_char_to_char (gsi_char *str)
{
  char *copy = (char *)malloc(sizeof(char) * (gsirtl_strlen(str) + 1));

  return gsirtl_strcpy_gsi_char_to_char(copy, str);
}

/* End of GSI String Utilities. */
      
    

  
void gsirtl_copy_item_or_value_1 
     GSI_MISC_PROTO((gsi_item arg, gsi_item duplicate, int xclu));

void gsirtl_copy_item_1 
     GSI_MISC_PROTO((gsi_int arg_type, gsi_item arg, gsi_item duplicate, int xclu));

void gsirtl_copy_array_1 
     GSI_MISC_PROTO((gsi_int arg_type, gsi_item arg, gsi_item duplicate, int xclu));

void gsirtl_copy_list_1 
     GSI_MISC_PROTO((gsi_int arg_type, gsi_item arg, gsi_item duplicate, int xclu));

void gsirtl_copy_sequence_1
     GSI_MISC_PROTO((gsi_item arg, gsi_item duplicate, int xclu));

void gsirtl_copy_structure_1
     GSI_MISC_PROTO((gsi_item arg, gsi_item duplicate, int xclu));

void gsirtl_copy_elements
     GSI_MISC_PROTO((gsi_int arg_type, gsi_item arg, gsi_item duplicate, int xclu));

void gsirtl_copy_attributes 
     GSI_MISC_PROTO(( gsi_item arg, gsi_item duplicate, int xclu));

void gsirtl_display_item_or_value_1 
     GSI_MISC_PROTO((gsi_item arg, gsi_int level, gsi_int display_mod));

void gsirtl_display_item_1 
     GSI_MISC_PROTO((gsi_int arg_type, 
		     gsi_item arg, gsi_int level, gsi_int display_mode));

void gsirtl_display_array_1 
     GSI_MISC_PROTO((gsi_int arg_type,
		     gsi_item arg, gsi_int level, gsi_int display_mode));

void gsirtl_display_list_1 
     GSI_MISC_PROTO((gsi_int arg_type,
		     gsi_item arg, gsi_int level, gsi_int display_mode));

void gsirtl_free_i_or_v_contents_1 
     GSI_MISC_PROTO((gsi_item arg, gsi_int reclaim));

struct item_flag {
  void *item;
  void *saved_user_data;
  void *flag;
};

#define ITEM_FLAG_ARRAY_SIZE 200

struct item_flag_block {
  struct item_flag_block *next;
  struct item_flag flag_array[ITEM_FLAG_ARRAY_SIZE];
  int count;
} *item_flag_first_block = 0;

void gsirtl_clear_item_flags(do_reset)
  int do_reset;
{
  struct item_flag_block *ifb, *next_ifb;
  int i;
  for (ifb = item_flag_first_block; 0 != ifb; ifb = next_ifb) {
    next_ifb = ifb->next;
    if (do_reset)
      for (i = 0; i < ifb->count; i++) {
	struct item_flag *flag = &(ifb->flag_array[i]);
	gsi_set_user_data(flag->item,flag->saved_user_data);
      }
    free(ifb);
  }
  item_flag_first_block = 0;
}

/* CAUTION! Make sure you REALLY need to use gsirtl_item_has_a_flag instead of
   gsirtl_get_item_flag because gsirtl_item_has_a_flag does a linear search over
   all the flags.  Usually gsirtl_get_item_flag is what you want which is much
   more efficient */
long gsirtl_item_has_a_flag(arg)
  gsi_item arg;
{
  struct item_flag_block *ifb;
  int i;
  for (ifb = item_flag_first_block; 0 != ifb; ifb = ifb->next) {
    for (i = 0; i < ifb->count; i++) {
      struct item_flag *flag = &(ifb->flag_array[i]);
      if (flag->item == arg)
	return TRUE;
    }
  }
  return FALSE;
}

struct item_flag *gsirtl_ensure_item_flag(arg, default_value)
  gsi_item arg;
  void *default_value;
{
  void *data = gsi_user_data_of(arg);
  struct item_flag_block *ifb;
  struct item_flag *flag;

  for (ifb = item_flag_first_block; 0 != ifb; ifb = ifb->next) {
    if ((void *)&(ifb->flag_array[0]) <= data &&
	data < (void *)&(ifb->flag_array[ifb->count]))
      return (struct item_flag *)data;
  }
  ifb = item_flag_first_block;
  if (0 == ifb || ifb->count == ITEM_FLAG_ARRAY_SIZE) {
    ifb = (struct item_flag_block *)malloc(sizeof(struct item_flag_block));
    ifb->next = item_flag_first_block;
    ifb->count = 0;
    item_flag_first_block = ifb;
  }
  flag = &(ifb->flag_array[ifb->count++]);
  flag->item = arg;
  flag->saved_user_data = data;
  flag->flag = default_value;
  gsi_set_user_data(arg,(void *)flag);
  return flag;
}

void *gsirtl_get_item_flag(arg, default_value)
  gsi_item arg;
  void *default_value;
{
  struct item_flag *flag = gsirtl_ensure_item_flag(arg, default_value);
  return flag->flag;
}

void gsirtl_set_item_flag(arg, value)
  gsi_item arg;
  void *value;
{
  gsirtl_ensure_item_flag(arg, 0)->flag = value;
}

/*****************************************
 *  Functions for duplicating GSI items  *
 *****************************************/

void gsirtl_copy_item_or_value(arg, duplicate, xclu)
  gsi_item arg;
  gsi_item duplicate;
  int     xclu ;
{
  gsirtl_copy_item_or_value_1(arg, duplicate, xclu);
  gsirtl_clear_item_flags(TRUE);
}

void gsirtl_copy_sequence(arg, duplicate, xclu)
  gsi_item arg;
  gsi_item duplicate;
  int     xclu ;
{
  gsirtl_copy_sequence_1(arg, duplicate, xclu);
  gsirtl_clear_item_flags(TRUE);
}

void gsirtl_copy_structure(arg, duplicate, xclu)
  gsi_item arg;
  gsi_item duplicate;
  int     xclu ;
{
  gsirtl_copy_structure_1(arg, duplicate, xclu);
  gsirtl_clear_item_flags(TRUE);
}

void gsirtl_copy_item(arg_type, arg, duplicate, xclu)
  gsi_int arg_type;
  gsi_item arg;
  gsi_item duplicate;
  int     xclu ;
{
  gsirtl_copy_item_1(arg_type, arg, duplicate, xclu);
  gsirtl_clear_item_flags(TRUE);
}

void gsirtl_copy_array(arg_type, arg, duplicate, xclu)
  gsi_int arg_type;
  gsi_item arg;
  gsi_item duplicate;
  int     xclu ;
{
  gsirtl_copy_array_1(arg_type, arg, duplicate, xclu);
  gsirtl_clear_item_flags(TRUE);
}

void gsirtl_copy_list(arg_type, arg, duplicate, xclu)
  gsi_int arg_type;
  gsi_item arg;
  gsi_item duplicate;
  int     xclu ;
{
  gsirtl_copy_list_1(arg_type, arg, duplicate, xclu);
  gsirtl_clear_item_flags(TRUE);
}

void gsirtl_copy_item_or_value_1(arg, duplicate, xclu)
  gsi_item arg;
  gsi_item duplicate;
  int     xclu ;
{
  gsi_int   arg_type = type_of(arg);
  static gsi_char *originating_fn_desc = NULL;
  static gsi_char *user_msg_for_item = NULL;
  static gsi_char *user_msg_for_value = NULL;

  if (originating_fn_desc == NULL)
    originating_fn_desc = gsirtl_strdup("\ncopy_item_or_value");
  if (user_msg_for_item == NULL)
    user_msg_for_item
      = gsirtl_strdup("****  Error - Unknown type for item");
  if (user_msg_for_value == NULL)
    user_msg_for_value
      = gsirtl_strdup("****  Error - Unknown type for simple value");

  gsirtl_set_item_flag(arg, duplicate);
  if (is_item(arg)) {
    if (is_array_type(arg_type))
      gsirtl_copy_array_1(arg_type,arg,duplicate, xclu);
    else if (is_list_type(arg_type))
      gsirtl_copy_list_1(arg_type,arg,duplicate, xclu);
    else if (is_simple_value_type(arg_type) || (arg_type == NULL_TAG))
      gsirtl_copy_item_1(arg_type,arg,duplicate, xclu);
    else
      gsi_signal_error(originating_fn_desc, 1024, user_msg_for_item);
  }
  else
    switch(arg_type) {
    case NULL_TAG:
      set_type(duplicate,NULL_TAG);
      break;
    case INTEGER_TAG:
    case LOGICAL_TAG:
    case FLOAT64_TAG:
    case SYMBOL_TAG:
    case STRING_TAG:
    case UNSIGNED_SHORT_VECTOR_TAG:
      gsirtl_copy_simple_value(arg_type,arg,duplicate);
      break;
    case HANDLE_TAG:
      set_handle(duplicate,handle_of(arg));
      break;
    case SEQUENCE_TAG:
      gsirtl_copy_sequence_1(arg,duplicate, xclu);
      break;
    case STRUCTURE_TAG:
      gsirtl_copy_structure_1(arg,duplicate, xclu);
      break;
    default:
      gsi_signal_error(originating_fn_desc,1024, user_msg_for_value);
    } /* end switch */
  
} /* end gsirtl_copy_item_or_value */

void gsirtl_copy_sequence_1(arg, duplicate, xclu)
  gsi_item arg;
  gsi_item duplicate;
  int     xclu ;
{
  gsirtl_copy_elements(SEQUENCE_TAG, arg, duplicate, xclu);
}

void gsirtl_copy_structure_1(arg, duplicate, xclu) 
  gsi_item arg;
  gsi_item duplicate;
  int     xclu ;
{
  set_type(duplicate,STRUCTURE_TAG);
  gsirtl_copy_attributes(arg, duplicate, xclu);
}

void gsirtl_copy_elements(arg_type, arg, duplicate, xclu)
  gsi_int arg_type;
  gsi_item arg;
  gsi_item duplicate;
  int     xclu ;
{
  gsi_int   element_count = element_count_of(arg);
  gsi_item *item_array, *duplicate_item_array;
  long      i;
  
  if (element_count > 0) {
    item_array = elements_of(arg);
    duplicate_item_array = gsi_make_array(element_count);
  }
  set_elements(duplicate,duplicate_item_array,element_count, arg_type);
  for (i=0; i<element_count; i++) {
    gsi_item duplicate_item = gsirtl_get_item_flag(item_array[i], 0);
    if (0 == duplicate_item) {
      duplicate_item = gsi_make_item();
      gsirtl_set_item_flag(item_array[i], duplicate_item);
      gsirtl_copy_item_or_value_1(item_array[i],duplicate_item, xclu);
    }
    duplicate_item_array[i] = duplicate_item;
  }
}

void gsirtl_copy_attributes(arg, duplicate, xclu)
  gsi_item arg;
  gsi_item duplicate;
  int     xclu ;
{
    gsi_int     attr_count = attr_count_of(arg);
    gsi_int     new_count = attr_count ;
    gsi_int     ix ;
    gsi_attr    *attr_array;
    gsi_attr    *duplicate_attrs;
    gsi_symbol  attr_name;
    int i, j;
    gsi_item    uuid ;
    gsi_item    fca ;
    gsi_char    *pName ;
    gsi_item    duplicate_item ;
    HRESULT     hr ;

    if (xclu)
    {
#ifdef UNICODE
        hr = FindAttributeNamed(arg, L"UUID", &uuid) ;
        hr = FindAttributeNamed(arg, L"FOUNDATION-CLASS", &fca) ;
#else
        hr = FindAttributeNamed(arg,"UUID",&uuid) ;
        hr = FindAttributeNamed(arg,"FOUNDATION-CLASS",&fca) ;
#endif
        if (uuid) new_count-- ;
        if (fca) new_count-- ;
    }

    if (new_count > 0)
    {
        duplicate_attrs = gsi_make_attrs(new_count);
        set_attrs(duplicate,duplicate_attrs,new_count);
        attr_array = attrs_of(arg);
        for (i=0, j=0; i<attr_count; i++)
        {
            gsi_item    arg_item = item_of_attr(attr_array[i]);
            attr_name = attr_name_of(attr_array[i]);
            pName = gsi_symbol_name(attr_name) ;
            ix = gsi_type_of(attr_array[i]) ;

            if (xclu)
            {
#ifdef UNICODE 
                if (pName && !wcscmp(pName, L"UUID"))
                    continue ;
                if (pName && !wcscmp(pName, L"FOUNDATION-CLASS"))
                    continue ;
#else
                if (!strcmp(pName, "UUID"))
                    continue ;
                if (!strcmp(pName, "FOUNDATION-CLASS"))
                    continue ;
#endif
            }
            duplicate_item = gsirtl_get_item_flag(arg_item, 0);
            set_attr_name(duplicate_attrs[j],attr_name);
            if (0 == duplicate_item)
            {
                duplicate_item = gsi_make_item();
	            gsirtl_set_item_flag(arg_item, duplicate_item);
	            gsirtl_copy_item_or_value_1(arg_item, duplicate_item, xclu);
            }	
            set_attr_name(duplicate_attrs[j],attr_name);
            gsi_set_item_of_attr(duplicate_attrs[j], duplicate_item);
            j++ ;
    } /* end for */
  } /* end if */
}

void gsirtl_copy_simple_value(arg_type, arg, duplicate)
  gsi_int arg_type;
  gsi_item arg;
  gsi_item duplicate;
{
  switch(arg_type) {
  case INTEGER_TAG:
    set_int(duplicate,int_of(arg));
    break;
  case LOGICAL_TAG:
    set_log(duplicate,log_of(arg));
    break;
  case FLOAT64_TAG:
    set_flt(duplicate,flt_of(arg));
    break;
  case SYMBOL_TAG:
    set_sym(duplicate,sym_of(arg));
    break;
  case STRING_TAG:
    set_str(duplicate,str_of(arg));
    break;
  case GSI_UNSIGNED_SHORT_VECTOR_TAG:
    gsi_set_usv(duplicate,usv_of(arg),usv_length_of(arg));
  } /* end switch */
  
} /* end gsirtl_copy_simple_value */


void gsirtl_copy_item_1(arg_type, arg, duplicate, xclu)
    gsi_int arg_type;
    gsi_item arg;
    gsi_item duplicate;
    int    xclu ;
{
  gsi_int   history_count = history_count_of(arg);
  gsi_int   history_type, max_count, max_age, min_interval;
  void     *values;
  gsi_item *mixed_values;
  void     *duplicate_values = 0;
  gsi_item *duplicate_mixed_values = 0;
  double   *timestamps;
  double   *duplicate_timestamps = 0;
  double    truncated_timestamp, timestamp_remainder;
  gsi_int   year, month, day, hour, minute, second;
  long      i;
  
  set_name(duplicate,name_of(arg));
  set_class_name(duplicate,class_name_of(arg));
  if (is_simple_value_type(arg_type))
    gsirtl_copy_simple_value(arg_type,arg,duplicate);
  gsirtl_copy_attributes(arg, duplicate, xclu);
  if (history_count == 0) {
    int history_type = gsi_history_type_of(arg);
    if (history_type != NULL_TAG)
      set_history_type(duplicate, history_type);
  }
  if (history_count > 0) {
    extract_history(arg,&values,&timestamps,&history_type);
    extract_history_spec(arg,&max_count,&max_age,&min_interval);
    switch(history_type) {
    case FLOAT64_TAG:
      duplicate_values = (void *)malloc(history_count*sizeof(double));
      break;
    case INTEGER_TAG:
    case LOGICAL_TAG:
      duplicate_values = (void *)malloc(history_count*sizeof(gsi_int));
      break;
    case SYMBOL_TAG:
    case STRING_TAG:
      duplicate_values = (void *)malloc(history_count+sizeof(void *));
      break;
    default:
      duplicate_mixed_values = gsi_make_array(history_count); }
    duplicate_timestamps = (double *)malloc(history_count*sizeof(double));
    for (i=0; i<history_count; i++) {
      timestamp_remainder = modf(timestamps[i],&truncated_timestamp);
      decode_timestamp(truncated_timestamp,
		       &year,&month,&day,&hour,&minute,&second);
      duplicate_timestamps[i] = timestamp_remainder +
	encode_timestamp(year,month,day,hour,minute,second);
      switch(history_type) {
      case INTEGER_TAG:
      case LOGICAL_TAG:
	( (gsi_int *)duplicate_values )[i] = ( (gsi_int *)values )[i];
	break;
      case FLOAT64_TAG:
	( (double *)duplicate_values )[i] = ( (double *)values )[i];
	break;
      case STRING_TAG:
      case SYMBOL_TAG:
	( (char **)duplicate_values )[i] = ( (char **)values )[i];
	break;
      case VALUE_TAG:
      case QUANTITY_TAG:
	duplicate_mixed_values[i] = gsi_make_item();
	mixed_values = (gsi_item *) values;
	switch(gsi_type_of(mixed_values[i])) {
	case INTEGER_TAG:
	  set_int(duplicate_mixed_values[i],int_of(mixed_values[i]));
	  break;
	case LOGICAL_TAG:
	  set_log(duplicate_mixed_values[i],log_of(mixed_values[i]));
	  break;
	case FLOAT64_TAG:
	  set_flt(duplicate_mixed_values[i],flt_of(mixed_values[i]));
	  break;
	case STRING_TAG:
	  set_str(duplicate_mixed_values[i],str_of(mixed_values[i]));
	  break;
	case SYMBOL_TAG:
	  set_sym(duplicate_mixed_values[i],sym_of(mixed_values[i]));
	} /* end switch */
      } /* end switch */
    } /* end for */
    if ((history_type == VALUE_TAG) || (history_type == QUANTITY_TAG))
      set_history(duplicate,duplicate_mixed_values,duplicate_timestamps,
		  history_count,history_type,max_count,max_age,min_interval);
    else {
      set_history(duplicate,duplicate_values,duplicate_timestamps,
		  history_count,history_type,max_count,max_age,min_interval);
      free(duplicate_values); }
    free(duplicate_timestamps);
  } /* end if */
  
} /* end gsirtl_copy_item */

void gsirtl_copy_array_1(arg_type, arg, duplicate, xclu)
  gsi_int arg_type;
  gsi_item arg;
  gsi_item duplicate;
  int      xclu ;
{
  gsi_int   element_count = element_count_of(arg);
  long     *long_array;
  double   *double_array;
  gsi_char **string_array;
  gsi_symbol *symbol_array;
  
  set_name(duplicate,name_of(arg));
  set_class_name(duplicate,class_name_of(arg));
  
  switch(arg_type) {
  case INTEGER_ARRAY_TAG:
    if (element_count > 0)
      long_array = int_array_of(arg);
    set_int_array(duplicate,long_array,element_count);
    break;
  case LOGICAL_ARRAY_TAG:
    if (element_count > 0)
      long_array = log_array_of(arg);
    set_log_array(duplicate,long_array,element_count);
    break;
  case FLOAT64_ARRAY_TAG:
    if (element_count > 0)
      double_array = flt_array_of(arg);
    set_flt_array(duplicate,double_array,element_count);
    break;
  case STRING_ARRAY_TAG:
    if (element_count > 0)
      string_array = str_array_of(arg);
    set_str_array(duplicate,string_array,element_count);
    break;
  case SYMBOL_ARRAY_TAG:
    if (element_count > 0)
      symbol_array = sym_array_of(arg);
    set_sym_array(duplicate,symbol_array,element_count);
    break;
  case VALUE_ARRAY_TAG:
  case QUANTITY_ARRAY_TAG:
  case ITEM_OR_VALUE_ARRAY_TAG:
  case ITEM_ARRAY_TAG:
    gsirtl_copy_elements(arg_type, arg, duplicate, xclu);
    break;
  } /* end switch */
  gsirtl_copy_attributes(arg, duplicate, xclu);
  
} /* end gsirtl_copy_array */

void gsirtl_copy_list_1(arg_type, arg, duplicate, xclu)
  gsi_int arg_type;
  gsi_item arg;
  gsi_item duplicate;
  int      xclu ;
{
  gsi_int   element_count = element_count_of(arg);
  long     *long_array;
  double   *double_array;
  gsi_char **string_array;
  gsi_symbol *symbol_array;
  
  set_name(duplicate,name_of(arg));
  set_class_name(duplicate,class_name_of(arg));
  
  switch(arg_type) {
  case INTEGER_LIST_TAG:
    if (element_count > 0)
      long_array = int_list_of(arg);
    set_int_list(duplicate,long_array,element_count);
    break;
  case LOGICAL_LIST_TAG:
    if (element_count > 0)
      long_array = log_list_of(arg);
    set_log_list(duplicate,long_array,element_count);
    break;
  case FLOAT64_LIST_TAG:
    if (element_count > 0)
      double_array = flt_list_of(arg);
    set_flt_list(duplicate,double_array,element_count);
    break;
  case STRING_LIST_TAG:
    if (element_count > 0)
      string_array = str_list_of(arg);
    set_str_list(duplicate,string_array,element_count);
    break;
  case SYMBOL_LIST_TAG:
    if (element_count > 0)
      symbol_array = sym_list_of(arg);
    set_sym_list(duplicate,symbol_array,element_count);
    break;
  case VALUE_LIST_TAG:
  case QUANTITY_LIST_TAG:
  case ITEM_OR_VALUE_LIST_TAG:
  case ITEM_LIST_TAG:
    gsirtl_copy_elements(arg_type, arg, duplicate, xclu);
    break;
  } /* end switch */
  gsirtl_copy_attributes(arg, duplicate, xclu); 
  
} /* end gsirtl_copy_list */

    FILE    *pfout ;

/*****************************************
 *  Functions for displaying GSI items  *
 *****************************************/

void gsirtl_display_item_or_value(arg, level, display_mode)
  gsi_item arg;
  gsi_int level;
  gsi_int display_mode;
{

  gsirtl_display_item_or_value_1(arg, level, display_mode);
  gsirtl_clear_item_flags(TRUE);
}

void gsirtl_display_array(arg_type, arg, level, display_mode)
  gsi_int arg_type;
  gsi_item arg;
  gsi_int level;
  gsi_int display_mode;
{
  gsirtl_display_array_1(arg_type, arg, level, display_mode);
  gsirtl_clear_item_flags(TRUE);
}

void gsirtl_display_list(arg_type, arg, level, display_mode)
  gsi_int arg_type;
  gsi_item arg;
  gsi_int level;
  gsi_int display_mode;
{
  gsirtl_display_list_1(arg_type, arg, level, display_mode);
  gsirtl_clear_item_flags(TRUE);
}

void gsirtl_display_item(arg_type, arg, level, display_mode)
  gsi_int arg_type;
  gsi_item arg;
  gsi_int level;
  gsi_int display_mode;
{
  gsirtl_display_item_1(arg_type, arg, level, display_mode);
  gsirtl_clear_item_flags(TRUE);
}

void gsirtl_display_item_or_value_1(arg, level, display_mode)
  gsi_item arg;
  gsi_int level;
  gsi_int display_mode;
{
  gsi_int   arg_type = type_of(arg);
  static gsi_char *originating_fn_desc = NULL;
  static gsi_char *user_msg_for_item = NULL;
  static gsi_char *user_msg_for_value = NULL;

  if (originating_fn_desc == NULL)
    originating_fn_desc = gsirtl_strdup("\ndisplay_item_or_value");
  if (user_msg_for_item == NULL)
    user_msg_for_item
      = gsirtl_strdup("****  Error - Unknown type for item");
  if (user_msg_for_value == NULL)
    user_msg_for_value
      = gsirtl_strdup("****  Error - Unknown type for simple value");

  gsirtl_indented_display("");
  if (gsirtl_get_item_flag(arg, FALSE)) {
    gsirtl_display("<item has already been displayed>\n");
    return;
  }
  gsirtl_set_item_flag(arg, TRUE);

  if (is_item(arg)) {
    if (is_array_type(arg_type))
      gsirtl_display_array_1(arg_type,arg,level,display_mode);
    else if (is_list_type(arg_type))
      gsirtl_display_list_1(arg_type,arg,level,display_mode);
    else if (is_simple_value_type(arg_type) || (arg_type == NULL_TAG))
      gsirtl_display_item_1(arg_type,arg,level,display_mode);
    else
      gsi_signal_error(originating_fn_desc, 1024, user_msg_for_item);
  }
  else
    switch(arg_type) {
    case NULL_TAG:
      gsirtl_display("no value\n");
      break;
    case INTEGER_TAG:
    case LOGICAL_TAG:
    case FLOAT64_TAG:
    case SYMBOL_TAG:
    case STRING_TAG:
    case UNSIGNED_SHORT_VECTOR_TAG:
      gsirtl_display_simple_value(arg_type,arg,display_mode);
      gsirtl_display("\n");
      break;
    case HANDLE_TAG:
      gsirtl_display_1("Item handle %d\n",handle_of(arg));
      break;
    case SEQUENCE_TAG: 
      {
	gsi_int element_count = gsi_element_count_of(arg);
	gsi_item *item_array;
	int i;
	gsirtl_display_1("a sequence with %d elements\n",element_count);
	if (element_count > 0) {
	  gsirtl_indented_display("");
	  item_array = elements_of(arg);
	  for (i=0; i<element_count; i++)
	    gsirtl_display_item_or_value_1(item_array[i],level,display_mode);
	}
      }
      break;
    case STRUCTURE_TAG:
      {
	gsi_int attr_count = gsi_attr_count_of(arg); 
	gsi_attr *attr_array;
	gsi_symbol attr_name;
	char *copy;
	int i;
	if (attr_count > 0) {
	  gsirtl_indented_display("a structure with attributes...\n");
	  attr_array = attrs_of(arg);
	  for (i=0; i<attr_count; i++) {
	    attr_name = attr_name_of(attr_array[i]);
	    copy = gsirtl_strdup_gsi_char_to_char(gsi_symbol_name(attr_name));
	    gsirtl_indented_display_1("%s: ", copy);
	    free(copy);
	    gsirtl_display_item_or_value_1(item_of_attr(attr_array[i]),
					   (level + 1),
					   display_mode);
	  }
	}
      }
      break;

    default:
      gsi_signal_error(originating_fn_desc, 1024, user_msg_for_value);
    } /* end switch */
  
} /* end gsirtl_display_item_or_value */

void gsirtl_display_array_1(arg_type, arg, level, display_mode)
  gsi_int arg_type;
  gsi_item arg;
  gsi_int level;
  gsi_int display_mode;
{
  gsi_int   attr_count = attr_count_of(arg);
  gsi_int   element_count = element_count_of(arg);
  gsi_symbol class_name = class_name_of(arg);
  gsi_symbol name = name_of(arg);
  long     *long_array;
  double   *double_array;
  gsi_char **string_array;
  gsi_symbol *symbol_array;
  gsi_item *item_array;
  gsi_attr *attr_array;
  long      i;
  gsi_int   handle;
  
  if (name) {
    char *copy = gsirtl_strdup_gsi_char_to_char(gsi_symbol_name(name));

    gsirtl_display_1("%s, ", copy);
    free(copy);
  }
  {
    char *copy = gsirtl_strdup_gsi_char_to_char(gsi_symbol_name(class_name));
    
    gsirtl_display_2("a %s with %d ", copy, element_count);
    free(copy);
  }
    
  level += 1;
  
  switch(arg_type) {
  case INTEGER_ARRAY_TAG:
    gsirtl_display("integer elements: ");
    if (element_count > 0) {
      long_array = int_array_of(arg);
      for (i=0; i<(element_count - 1); i++) {
	gsirtl_display_1("%d,",long_array[i]); }
      gsirtl_display_1("%d\n",long_array[element_count-1]); }
    break;
  case LOGICAL_ARRAY_TAG:
    gsirtl_display("logical elements: ");
    if (element_count > 0) {
      long_array = log_array_of(arg);
      for (i=0; i<(element_count - 1); i++) {
	gsirtl_display_1("%d,",long_array[i]); }
      gsirtl_display_1("%d\n",long_array[element_count-1]); }
    break;
  case FLOAT64_ARRAY_TAG:
    gsirtl_display("double elements: ");
    if (element_count > 0) {
      double_array = flt_array_of(arg);
      for (i=0; i<(element_count - 1); i++) {
	gsirtl_display_1("%4.4f,",double_array[i]); }
      gsirtl_display_1("%4.4f\n",double_array[element_count-1]); }
    break;
  case STRING_ARRAY_TAG:
    gsirtl_display("string elements: ");
    if (element_count > 0) {
      string_array = str_array_of(arg);
      for (i=0; i<element_count; i++) {
	char *copy = gsirtl_strdup_gsi_char_to_char(string_array[i]);
	
	gsirtl_display_2("%s%s", copy, i < (element_count - 1) ? "," : "\n");
	free(copy);
      }
    }
    break;
  case SYMBOL_ARRAY_TAG:
    gsirtl_display("symbol elements: ");
    if (element_count > 0) {
      symbol_array = sym_array_of(arg);
      for (i=0; i<element_count; i++) {
	char *copy
	  = gsirtl_strdup_gsi_char_to_char(gsi_symbol_name(symbol_array[i]));
	
	gsirtl_display_2("%s%s", copy, i < (element_count - 1) ? "," : "\n");
	free(copy);
      }
    }
    break;
  case VALUE_ARRAY_TAG:
  case QUANTITY_ARRAY_TAG:
  case ITEM_OR_VALUE_ARRAY_TAG:
  case ITEM_ARRAY_TAG:
    gsirtl_display("mixed elements:\n");
    gsirtl_indented_display("");
    if (element_count > 0)
      item_array = elements_of(arg);
    for (i=0; i<element_count; i++)
      gsirtl_display_item_or_value_1(item_array[i],level,display_mode);
    break;
  } /* end switch */
  
  if (attr_count > 0) {
    gsirtl_indented_display("and attributes...\n");
    attr_array = attrs_of(arg);
    for (i=0; i<attr_count; i++) {
      gsi_symbol attr_name = attr_name_of(attr_array[i]);
      char *copy
	= gsirtl_strdup_gsi_char_to_char(gsi_symbol_name(attr_name));
      gsirtl_indented_display_1("%s: ", copy);
      free(copy);
      gsirtl_display_item_or_value_1(item_of_attr(attr_array[i]),
				     (level + 1),
				     display_mode);
    }
  }
  else
    gsirtl_indented_display("and no attributes.\n");
  if (0 != (handle = gsi_handle_of(arg)))
    gsirtl_indented_display_1("and with handle: %d\n",handle);
  
} /* end gsirtl_display_array */

void gsirtl_display_list_1(arg_type, arg, level, display_mode)
  gsi_int arg_type;
  gsi_item arg;
  gsi_int level;
  gsi_int display_mode;
{
  gsi_int   attr_count = attr_count_of(arg);
  gsi_int   element_count = element_count_of(arg);
  gsi_symbol class_name = class_name_of(arg);
  gsi_symbol name = name_of(arg);
  long     *long_array;
  double   *double_array;
  gsi_char **string_array;
  gsi_symbol *symbol_array;
  gsi_item *item_array;
  gsi_attr *attr_array;
  long      i;
  gsi_int   handle;
  
  if (name) {
    char *copy = gsirtl_strdup_gsi_char_to_char(gsi_symbol_name(name));

    gsirtl_display_1("%s, ", copy);
    free(copy);
  }
  {
    char *copy = gsirtl_strdup_gsi_char_to_char(gsi_symbol_name(class_name));
    
    gsirtl_display_2("a %s with %d ", copy, element_count);
    free(copy);
  }
  level += 1;
  
  switch(arg_type) {
  case INTEGER_LIST_TAG:
    gsirtl_display("integer elements: ");
    if (element_count > 0) {
      long_array = int_list_of(arg);
      for (i=0; i<(element_count - 1); i++) {
	gsirtl_display_1("%d,",long_array[i]); }
      gsirtl_display_1("%d\n",long_array[element_count-1]); }
    break;
  case LOGICAL_LIST_TAG:
    gsirtl_display("logical elements: ");
    if (element_count > 0) {
      long_array = log_list_of(arg);
      for (i=0; i<(element_count - 1); i++) {
	gsirtl_display_1("%d,",long_array[i]); }
      gsirtl_display_1("%d\n",long_array[element_count-1]); }
    break;
  case FLOAT64_LIST_TAG:
    gsirtl_display("double elements: ");
    if (element_count > 0) {
      double_array = flt_list_of(arg);
      for (i=0; i<(element_count - 1); i++) {
	gsirtl_display_1("%4.4f,",double_array[i]); }
      gsirtl_display_1("%4.4f\n",double_array[element_count-1]); }
    break;
  case STRING_LIST_TAG:
    gsirtl_display("string elements: ");
    if (element_count > 0) {
      string_array = str_list_of(arg);
      for (i=0; i<element_count; i++) {
	char *copy = gsirtl_strdup_gsi_char_to_char(string_array[i]);

	gsirtl_display_2("%s%s", copy, i < (element_count - 1) ? "," : "\n");
	free(copy);
      }
    }
    break;
  case SYMBOL_LIST_TAG:
    gsirtl_display("symbol elements: ");
    if (element_count > 0) {
      symbol_array = sym_list_of(arg);
      for (i=0; i<element_count; i++) {
	char *copy = gsirtl_strdup_gsi_char_to_char(gsi_symbol_name(symbol_array[i]));

	gsirtl_display_2("%s%s", copy, i < (element_count - 1) ? "," : "\n");
	free(copy);
      }
    }
    break;
  case VALUE_LIST_TAG:
  case QUANTITY_LIST_TAG:
  case ITEM_OR_VALUE_LIST_TAG:
  case ITEM_LIST_TAG:
    gsirtl_display("mixed elements:\n");
    gsirtl_indented_display("");
    if (element_count > 0)
      item_array = elements_of(arg);
    for (i=0; i<element_count; i++)
      gsirtl_display_item_or_value_1(item_array[i],
				     level,
				     display_mode);
    break;
  } /* end switch */
  
  if (attr_count > 0) {
    gsirtl_indented_display("and attributes...\n");
    attr_array = attrs_of(arg);
    for (i=0; i<attr_count; i++) {
      gsi_symbol attr_name = attr_name_of(attr_array[i]);
      char *copy = gsirtl_strdup_gsi_char_to_char(attr_name);
      gsirtl_indented_display_1("%s: ", copy);
      free(copy);
      gsirtl_display_item_or_value_1(item_of_attr(attr_array[i]),
				     (level + 1),
				     display_mode);
    }
  }
  else {
    gsirtl_indented_display("and no attributes.\n"); }

  if (0 != (handle = gsi_handle_of(arg)))
    gsirtl_indented_display_1("and with handle: %d\n",handle);
} /* end gsirtl_display_list */

void gsirtl_display_item_1(arg_type, arg, level, display_mode)
  gsi_int arg_type;
  gsi_item arg;
  gsi_int level;
  gsi_int display_mode;
{
  gsi_symbol class_name = class_name_of(arg);
  gsi_symbol name = name_of(arg);
  gsi_int   attr_count = attr_count_of(arg);
  gsi_int   history_count = history_count_of(arg);
  gsi_int   history_type, max_count, max_age, min_interval;
  gsi_attr *attr_array;
  void     *values;
  gsi_item *mixed_values;
  double   *timestamps;
  double    truncated_timestamp, timestamp_remainder;
  gsi_int   year, month, day, hour, minute, second;
  long      i;
  gsi_int   handle;
  
  if (name) {
    char *copy = gsirtl_strdup_gsi_char_to_char(gsi_symbol_name(name));

    gsirtl_display_1("%s, ", copy);
    free(copy);
  }
  {
    char *copy = gsirtl_strdup_gsi_char_to_char(gsi_symbol_name(class_name));
    
    gsirtl_display_1("a %s with ", copy);
    free(copy);
  }
  if (is_simple_value_type(arg_type)) {
    gsirtl_display_simple_value(arg_type,arg,display_mode);
    gsirtl_display(", and "); 
    if ((arg_type == INTEGER_TAG || arg_type == FLOAT64_TAG) &&
	gsi_history_type_of(arg) == QUANTITY_TAG)
      gsirtl_display("quantity type, and ");
  } else if (arg_type == NULL_TAG) {
    int history_type = gsi_history_type_of(arg);
    char *type_name = 0;
    switch (history_type) {
    case INTEGER_TAG:  type_name = "integer"; break;
    case LOGICAL_TAG:  type_name = "logical"; break;
    case FLOAT64_TAG:  type_name = "float"; break;
    case STRING_TAG:   type_name = "string"; break;
    case SYMBOL_TAG:   type_name = "symbol"; break;
    case QUANTITY_TAG: type_name = "quantity"; break;
    }
    if (type_name)
      gsirtl_display_1("no value, and %s type, and ",type_name);
  }
  if (attr_count > 0) {
    gsirtl_display("attributes...\n");
    attr_array = attrs_of(arg);
    for (i=0; i<attr_count; i++) {
      gsi_symbol attr_name = attr_name_of(attr_array[i]);
      char *copy
	= gsirtl_strdup_gsi_char_to_char(gsi_symbol_name(attr_name));

      gsirtl_indented_display_1(" %s: \n", copy);
      free(copy);
      gsirtl_display_item_or_value_1(item_of_attr(attr_array[i]),
				     (level+1),
				     display_mode);
    }
  }
  else {
    gsirtl_display("no attributes.\n"); }
  
  if (history_count > 0) {
    extract_history(arg,&values,&timestamps,&history_type);
    extract_history_spec(arg,&max_count,&max_age,&min_interval);
    gsirtl_indented_display_1("%d values currently in history whose spec permits them",history_count);
    gsirtl_display_1(" at intervals of %d milliseconds or greater and allows for ",min_interval);
    if (max_count) {
      gsirtl_display_1("%d historical values",max_count);
      if (max_age) {
	gsirtl_display_1(" no more than %d seconds old.  ",max_age); }
      else {
	gsirtl_display(".  "); } } 
    else {
      gsirtl_display_1("historical values no more than %d seconds old.  ",max_age); }
    gsirtl_indented_display("\nCurrent contents of history are...\n");
    for (i=0; i<history_count; i++) {
      timestamp_remainder = modf(timestamps[i],&truncated_timestamp);
      decode_timestamp(truncated_timestamp,
		       &year,&month,&day,&hour,&minute,&second);
      gsirtl_indented_display_6(" %d/%d/%d %d:%d:%d",
				month,day,year,hour,minute,second);
      switch(history_type) {
      case INTEGER_TAG:
      case LOGICAL_TAG:
	gsirtl_display_1(" %d\n",((gsi_int *)values)[i]);
	break;
      case FLOAT64_TAG:
	gsirtl_display_1(" %4.4f\n",((double *)values)[i]);
	break;
      case STRING_TAG:
	{
	  char *copy = gsirtl_strdup_gsi_char_to_char(((gsi_char **)values)[i]);

	  gsirtl_display_1(" %s\n", copy);
	  free(copy);
	}
	break;
      case SYMBOL_TAG:
	{
	  char *copy
	    = gsirtl_strdup_gsi_char_to_char(gsi_symbol_name(((gsi_symbol *)values)[i]));

	  gsirtl_display_1(" %s\n", copy);
	  free(copy);
	}
	break;
      case VALUE_TAG:
      case QUANTITY_TAG:
	mixed_values = (gsi_item *) values;
	switch(gsi_type_of(mixed_values[i])) {
	case INTEGER_TAG:
	  gsirtl_display_1(" %d\n",int_of(mixed_values[i]));
	  break;
	case LOGICAL_TAG:
	  gsirtl_display_1(" %d\n",log_of(mixed_values[i]));
	  break;
	case FLOAT64_TAG:
	  gsirtl_display_1(" %4.4f\n",flt_of(mixed_values[i]));
	  break;
	case STRING_TAG:
	  {
	    char *copy = gsirtl_strdup_gsi_char_to_char(str_of(mixed_values[i]));

	    gsirtl_display_1(" %s\n", copy);
	    free(copy);
	  }
	  break;
	case SYMBOL_TAG:
	  {
	    char *copy = gsirtl_strdup_gsi_char_to_char(gsi_symbol_name(sym_of(mixed_values[i])));

	    gsirtl_display_1(" %s\n", copy);
	    free(copy);
	  }
	  break;
	} /* end switch */
      } /* end switch */
    } /* end for */
  } /* end if */

  if (0 != (handle = gsi_handle_of(arg)))
    gsirtl_indented_display_1("and with handle: %d\n",handle);
} /* end gsirtl_display_item */


void gsirtl_display_simple_value(arg_type, arg, display_mode)
  gsi_int arg_type;
  gsi_item arg;
  gsi_int display_mode;
{
  switch(arg_type) {
  case INTEGER_TAG:
    gsirtl_display_1("integer value %d",int_of(arg));
    break;
  case LOGICAL_TAG:
    gsirtl_display_1("logical value %d",log_of(arg));
    break;
  case FLOAT64_TAG:
    gsirtl_display_1("double value %4.4f",flt_of(arg));
    break;
  case SYMBOL_TAG:
    {
      char *copy = gsirtl_strdup_gsi_char_to_char(gsi_symbol_name(sym_of(arg)));

      gsirtl_display_1("symbol value %s", copy);
      free(copy);
    }
    break;
  case STRING_TAG:
    {
      char *copy = gsirtl_strdup_gsi_char_to_char(str_of(arg));

      gsirtl_display_1("string value %s", copy);
      free(copy);
    }
    break;
  case UNSIGNED_SHORT_VECTOR_TAG:
    gsirtl_display("unsigned short vector value ");
    {
      int i, len = usv_length_of(arg);
      unsigned short *usv = usv_of(arg);
      for(i=0; i<len; i++) {
	unsigned short element = usv[i];
	gsirtl_display_4("%x%x%x%x",
			 element>>12,(element>>8)&0xf,
			 (element>>4)&0xf,element&0xf);
      }
    }
    break;
  }
} /* end gsirtl_display_simple_value */


void gsirtl_display_buffer(buffer, mode)
  gsi_char *buffer;
  long int mode;
{
  char *copy = gsirtl_strdup_gsi_char_to_char(buffer);
/*
 *  Mode is currently ignored and output is
 *  unconditionally directed to stdout.
 */
  printf("%s", copy);
  free(copy);
}

/************************************************************
 *  Functions for freeing memory associated with GSI items  *
 ************************************************************/

void gsirtl_free_i_or_v_contents(arg)
  gsi_item arg;
{
  gsirtl_free_i_or_v_contents_1(arg,FALSE);
  gsirtl_clear_item_flags(FALSE); /* FALSE because we are reclaiming so we don't
				     need to put the user_data back */
}

void gsirtl_free_array_memory(arg_type, arg)
  gsi_int arg_type;
  gsi_item arg;
{
  gsi_int   attr_count = attr_count_of(arg);
  gsi_int   element_count = element_count_of(arg);
  gsi_item *item_array;
  gsi_attr *attr_array;
  long      i;
  
  switch(arg_type) {
  case INTEGER_ARRAY_TAG:
    break;
  case LOGICAL_ARRAY_TAG:
    break;
  case FLOAT64_ARRAY_TAG:
    break;
  case STRING_ARRAY_TAG:
    break;
  case SYMBOL_ARRAY_TAG:
    break;
  case VALUE_ARRAY_TAG:
  case QUANTITY_ARRAY_TAG:
  case ITEM_OR_VALUE_ARRAY_TAG:
  case ITEM_ARRAY_TAG:
    if (element_count > 0) {
      item_array = elements_of(arg);
      for (i=0; i<element_count; i++)
	gsirtl_free_i_or_v_contents_1(item_array[i],TRUE);
      gsi_reclaim_array(item_array); }
    break;
  } /* end switch */
  
  if (attr_count > 0) {
    attr_array = attrs_of(arg);
    for (i=0; i<attr_count; i++)
      gsirtl_free_i_or_v_contents_1(item_of_attr(attr_array[i]),TRUE);
    gsi_reclaim_attrs(attr_array); }
  
} /* end gsirtl_free_array_memory */


void gsirtl_free_list_memory(arg_type, arg)
  gsi_int arg_type;
  gsi_item arg;
{
  gsi_int   attr_count = attr_count_of(arg);
  gsi_int   element_count = element_count_of(arg);
  gsi_item *item_array;
  gsi_attr *attr_array;
  long      i;
  
  switch(arg_type) {
  case INTEGER_LIST_TAG:
    break;
  case LOGICAL_LIST_TAG:
    break;
  case FLOAT64_LIST_TAG:
    break;
  case STRING_LIST_TAG:
    break;
  case SYMBOL_LIST_TAG:
    break;
  case VALUE_LIST_TAG:
  case QUANTITY_LIST_TAG:
  case ITEM_OR_VALUE_LIST_TAG:
  case ITEM_LIST_TAG:
    if (element_count > 0) {
      item_array = elements_of(arg);
      for (i=0; i<element_count; i++)
	gsirtl_free_i_or_v_contents_1(item_array[i],TRUE);
      gsi_reclaim_array(item_array); }
    break;
  } /* end switch */
  
  if (attr_count > 0) {
    attr_array = attrs_of(arg);
    for (i=0; i<attr_count; i++)
      gsirtl_free_i_or_v_contents_1(item_of_attr(attr_array[i]),TRUE);
    gsi_reclaim_attrs(attr_array); }
  
} /* end gsirtl_free_list_memory */


void gsirtl_free_item_memory(arg)
  gsi_item arg;
{
  gsi_int   attr_count = attr_count_of(arg);
  gsi_int   history_count = history_count_of(arg);
  gsi_int   history_type;
  void     *values;
  double   *timestamps;
  gsi_attr *attr_array;
  long      i;
  
  if (attr_count > 0) {
    attr_array = attrs_of(arg);
    for (i=0; i<attr_count; i++)
      gsirtl_free_i_or_v_contents_1(item_of_attr(attr_array[i]),TRUE);
    gsi_reclaim_attrs(attr_array); }
  if (history_count > 0) {
    extract_history(arg,&values,&timestamps,&history_type);
    if((history_type == VALUE_TAG) || (history_type == QUANTITY_TAG))
      gsi_reclaim_items((gsi_item *)values); }
  
} /* end gsirtl_free_item_memory */


void gsirtl_free_i_or_v_contents_1(arg, reclaim)
  gsi_item arg;
  gsi_int reclaim;
{
  gsi_int   arg_type;
  static gsi_char *originating_fn_desc = NULL;
  static gsi_char *user_msg_for_item = NULL;

  if (originating_fn_desc == NULL)
    originating_fn_desc = gsirtl_strdup("\nfree_i_or_v_contents");
  if (user_msg_for_item == NULL)
    user_msg_for_item
      = gsirtl_strdup("****  Error - Unknown type for item");
  
  if (gsirtl_get_item_flag(arg, FALSE)) return;
  gsirtl_set_item_flag(arg, TRUE);

  if (gsi_owner_of(arg) != GSI_OWNER_IS_USER) return;
  
  arg_type = type_of(arg);
  if (is_item(arg)) {
    if (is_array_type(arg_type))
      gsirtl_free_array_memory(arg_type,arg);
    else if (is_list_type(arg_type))
      gsirtl_free_list_memory(arg_type,arg);
    else if (is_simple_value_type(arg_type) || (arg_type == NULL_TAG))
      gsirtl_free_item_memory(arg);
    else
      gsi_signal_error(originating_fn_desc, 1024, user_msg_for_item);
  }
  else if (arg_type == SEQUENCE_TAG)
    {
      int element_count = gsi_element_count_of(arg);
      gsi_item *item_array;
      int i;
      if (element_count > 0) {
	item_array = elements_of(arg);
	for (i=0; i<element_count; i++)
	  gsirtl_free_i_or_v_contents_1(item_array[i],TRUE);
	gsi_reclaim_array(item_array);
      }
    }
  else if (arg_type == STRUCTURE_TAG)
    {
      int attr_count = gsi_attr_count_of(arg);
      gsi_attr *attr_array;
      int i;
     
      if (attr_count > 0) {
	attr_array = attrs_of(arg);
	for (i=0; i<attr_count; i++)
	  gsirtl_free_i_or_v_contents_1(gsi_item_of_attr(attr_array[i]),TRUE);
	gsi_reclaim_attrs(attr_array);
      }
    }
  if (reclaim)
    gsi_reclaim_item(arg);
  else
    gsi_clear_item(arg);
  
  
} /* end gsirtl_free_i_or_v_contents */


/******************************************
 *  Functions for viewing GSI structures  *
 ******************************************/

void gsirtl_view_gsi_item(item)
  gsi_item item;
{
  gsi_symbol symbol_temp;
  gsi_int   value_type = type_of(item);
  gsi_int   history_count = history_count_of(item);
  gsi_int   history_type, max_count, max_age, min_interval;
  void     *values;
  double   *times;
  double    timestamp;

  printf("\nItem at 0x%x:",item);
  symbol_temp = class_name_of(item);
  if (symbol_temp) {
    char *copy = gsirtl_strdup_gsi_char_to_char(gsi_symbol_name(symbol_temp));
    printf("\n  class: %s", copy);
    free(copy);
  }
  else
     printf("\n  class: NULL_PTR");
  symbol_temp = name_of(item);
  if (symbol_temp) {
    char *copy = gsirtl_strdup_gsi_char_to_char(gsi_symbol_name(symbol_temp));
    printf("\n  name: %s", copy);
    free(copy);
  }
  else
     printf("\n  name: NULL_PTR");
  printf("\n  value type: %d ",value_type);
  switch(value_type) {
    case NULL_TAG: printf("(NULL_TAG)"); break;
    case GSI_INTEGER_TAG: printf("(GSI_INTEGER_TAG)"); break;
    case GSI_SYMBOL_TAG: printf("(GSI_SYMBOL_TAG)"); break;
    case GSI_STRING_TAG: printf("(GSI_STRING_TAG)"); break;
    case GSI_LOGICAL_TAG: printf("(GSI_LOGICAL_TAG)"); break;
    case GSI_FLOAT64_TAG: printf("(GSI_FLOAT64_TAG)"); break;
    case GSI_UNSIGNED_SHORT_VECTOR_TAG: printf("(GSI_UNSIGNED_SHORT_VECTOR_TAG)"); break;
    case GSI_VALUE_TAG: printf("(GSI_VALUE_TAG)"); break;
    case GSI_HANDLE_TAG: printf("(GSI_HANDLE_TAG)"); break;
    case GSI_INTEGER_ARRAY_TAG: printf("(GSI_INTEGER_ARRAY_TAG)"); break;
    case GSI_SYMBOL_ARRAY_TAG: printf("(GSI_SYMBOL_ARRAY_TAG)"); break;
    case GSI_STRING_ARRAY_TAG: printf("(GSI_STRING_ARRAY_TAG)"); break;
    case GSI_LOGICAL_ARRAY_TAG: printf("(GSI_LOGICAL_ARRAY_TAG)"); break;
    case GSI_FLOAT64_ARRAY_TAG: printf("(GSI_FLOAT64_ARRAY_TAG)"); break;
    case GSI_ITEM_ARRAY_TAG: printf("(GSI_ITEM_ARRAY_TAG)"); break;
    case GSI_ITEM_OR_VALUE_ARRAY_TAG: printf("(GSI_ITEM_OR_VALUE_ARRAY_TAG)"); break;
    case GSI_QUANTITY_ARRAY_TAG: printf("(GSI_QUANTITY_ARRAY_TAG)"); break;
    case GSI_VALUE_ARRAY_TAG: printf("(GSI_VALUE_ARRAY_TAG)"); break;
    case GSI_INTEGER_LIST_TAG: printf("(GSI_INTEGER_LIST_TAG)"); break;
    case GSI_SYMBOL_LIST_TAG: printf("(GSI_SYMBOL_LIST_TAG)"); break;
    case GSI_STRING_LIST_TAG: printf("(GSI_STRING_LIST_TAG)"); break;
    case GSI_LOGICAL_LIST_TAG: printf("(GSI_LOGICAL_LIST_TAG)"); break;
    case GSI_FLOAT64_LIST_TAG: printf("(GSI_FLOAT64_LIST_TAG)"); break;
    case GSI_ITEM_LIST_TAG: printf("(GSI_ITEM_LIST_TAG)"); break;
    case GSI_ITEM_OR_VALUE_LIST_TAG: printf("(GSI_ITEM_OR_VALUE_LIST_TAG)"); break;
    case GSI_QUANTITY_LIST_TAG: printf("(GSI_QUANTITIY_LIST_TAG)"); break;
    case GSI_VALUE_LIST_TAG: printf("(GSI_VALUE_LIST_TAG)"); break; }
  printf("\n  value count: %d",element_count_of(item));
  printf("\n  value(s):");
  switch(value_type) {
    case NULL_TAG: printf("? (NULL_TAG)"); break;
    case GSI_INTEGER_TAG: printf("%d",int_of(item)); break;
    case GSI_SYMBOL_TAG: printf("%s",sym_of(item)); break;
    case GSI_STRING_TAG: printf("%s",str_of(item)); break;
    case GSI_LOGICAL_TAG: printf("%d",log_of(item)); break;
    case GSI_FLOAT64_TAG: printf("%f",flt_of(item)); break;
    case GSI_UNSIGNED_SHORT_VECTOR_TAG: 
    {
      int i, len = usv_length_of(item);
      unsigned short *usv = usv_of(item);
      for(i=0; i<len; i++) {
	unsigned short element = usv[i];
	printf("%x%x%x%x",
	       element>>12,(element>>8)&0xf,
	       (element>>4)&0xf,element&0xf);
      }
    }
    break;
    case GSI_VALUE_TAG: printf("invalid embedding"); break;
    case GSI_QUANTITY_TAG: printf("invalid embedding"); break;
    case GSI_HANDLE_TAG: printf("%d",handle_of(item)); break;
    case GSI_INTEGER_ARRAY_TAG: printf("0x%x",int_array_of(item)); break;
    case GSI_SYMBOL_ARRAY_TAG: printf("0x%x",sym_array_of(item)); break;
    case GSI_STRING_ARRAY_TAG: printf("0x%x",str_array_of(item)); break;
    case GSI_LOGICAL_ARRAY_TAG: printf("0x%x",log_array_of(item)); break;
    case GSI_FLOAT64_ARRAY_TAG: printf("0x%x",flt_array_of(item)); break;
    case GSI_INTEGER_LIST_TAG: printf("0x%x",int_list_of(item)); break;
    case GSI_SYMBOL_LIST_TAG: printf("0x%x",sym_list_of(item)); break;
    case GSI_STRING_LIST_TAG: printf("0x%x",str_list_of(item)); break;
    case GSI_LOGICAL_LIST_TAG: printf("0x%x",log_list_of(item)); break;
    case GSI_FLOAT64_LIST_TAG: printf("0x%x",flt_list_of(item)); break;
    case GSI_ITEM_ARRAY_TAG: 
    case GSI_VALUE_ARRAY_TAG:
    case GSI_ITEM_LIST_TAG: 
    case GSI_ITEM_OR_VALUE_LIST_TAG: 
    case GSI_QUANTITY_LIST_TAG:
    case GSI_VALUE_LIST_TAG: printf("0x%x",elements_of(item)); break; }
  printf("\n  attribute count: %d",attr_count_of(item));
  printf("\n  attribute(s): 0x%x",attrs_of(item));
  gsi_set_option(GSI_SUPPRESS_OUTPUT);
  timestamp = timestamp_of(item);
  printf("\n  timestamp: ");
  if (gsi_last_error() == GSI_TIMESTAMP_NOT_FOUND)
    printf("none");
  else
    printf("%9.2f",timestamp);
  gsi_reset_option(GSI_SUPPRESS_OUTPUT);
  if (history_count) {
    extract_history(item,&values,&times,&history_type);
    extract_history_spec(item,&max_count,&max_age,&min_interval);
    printf("\n  history type: %d ",history_type);
    switch(value_type) {
      case GSI_INTEGER_TAG: printf("(GSI_INTEGER_TAG)"); break;
      case GSI_SYMBOL_TAG: printf("(GSI_SYMBOL_TAG)"); break;
      case GSI_STRING_TAG: printf("(GSI_STRING_TAG)"); break;
      case GSI_LOGICAL_TAG: printf("(GSI_LOGICAL_TAG)"); break;
      case GSI_FLOAT64_TAG: printf("(GSI_FLOAT64_TAG)"); break;
      case GSI_VALUE_TAG: printf("(GSI_VALUE_TAG)"); break;
      case GSI_QUANTITY_TAG: printf("(GSI_QUANTITY_TAG)"); break; }
    printf("\n  history count: %d",history_count);
    printf("\n  history value(s): 0x%x",values);
    printf("\n  history timestamp(s): 0x%x",times);
    printf("\n  history min interval: %d",min_interval);
    printf("\n  history max count: %d",max_count);
    printf("\n  history max age: %d",max_age); }
  else
    printf("\n  no history info");
  printf("\n");

} /* end gsirtl_view_gsi_item */


/* ------------------------------------------------------------------------- */
/*                                                                           */
/*       Remove the attribute with the specified name from the gsi_item      */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void gsirtl_remove_attribute(gsi_item item2mod, gsi_char *attrName)
{

    gsi_int     count = gsi_attr_count_of(item2mod) ;
    long    lX, idx2 ;

    if (count)
    {
        // Get the array of attributes of the item to modify
        //--------------------------------------------------
        gsi_attr    *pAttrs = gsi_attrs_of(item2mod) ;

        // Get a new array of attributes which we will attach
        // to the item to modify it.
        // --------------------------------------------------
        gsi_attr    *newAttr = NULL ;     
        if (count > 1) 
            newAttr = gsi_make_attrs(count-1) ;


        // Loop through the attributes looking for the one we wish to drop
        // ---------------------------------------------------------------
        for (lX = 0, idx2 = 0 ; lX < count ; lX++)
        {
            gsi_item    i2k = gsi_item_of_attr(pAttrs[lX]) ;
            gsi_symbol  nameOfAttr = gsi_attr_name_of(pAttrs[lX]) ;
            gsi_char    *pgstName = gsi_symbol_name(nameOfAttr) ;

            // If this is the attribute we want to drop, free the memory it is using
            // ---------------------------------------------------------------------
#ifdef GSI_USE_WIDE_STRING_API
            if (wcscmp(pgstName, attrName) == 0)
#else
            if (strcmp(pgstName, attrName) == 0)
#endif
            {
                gsi_reclaim_item(i2k) ;
            }

            // If we want to keep this attribute, name the attribute in the array of
            // new attributes and attach its item to the new attribute
            // ---------------------------------------------------------------------
            else
            {
                if (idx2 < count-1)
                {
                    gsi_set_attr_name(newAttr[idx2], nameOfAttr) ;
                    gsi_set_item_of_attr(newAttr[idx2], i2k) ;
                }
                idx2++ ;
            }
        }

        // If we dropped an attribute, attach the new array of attributes to the item.
        // Then attach a bogus item to each of the original attributes (so gsi_reclaim_attrs
        // won't zap the attributes we are keeping) and free the memory allocated to the
        // original array by calling gsi_reclaim_attrs.
        // ---------------------------------------------------------------------------------
        if (idx2 < count)
        {
            gsi_set_attrs(item2mod, newAttr, idx2) ;
            for (lX = 0 ; lX < count ; lX++)
                gsi_set_item_of_attr(pAttrs[lX], gsi_make_item()) ;
            gsi_reclaim_attrs(pAttrs) ;
        }

        // We didn't drop anything.  Free up the memory that we used.
        // ---------------------------------------------------------
        else
        {
            gsi_reclaim_attrs(newAttr) ;
        }
        return ;
    }
}
