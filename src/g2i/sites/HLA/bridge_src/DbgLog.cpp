/***************************************************************************
 *
 *		DbgLog.cpp
 *
 *			Contains useful functions used for tracing and
 *			debugging purposes.
 *
 *		This file has been imported and converted from earlier an earlier
 *		version written in ANSI C.
 *
 ***************************************************************************/


#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<stdarg.h>
#include	<errno.h>
#include	<malloc.h>
#include	<math.h>
#include	<time.h>

#include	"G2Hla.h"




/*-------------------------------------------------------------------------*
 *
 *
 *-------------------------------------------------------------------------*/

#define	LOG_MAX_MSG_COUNT		50000
#define	LOG_FILE_TEMPLATE		"G2_HLA_"



/*-------------------------------------------------------------------------*
 *
 *
 *-------------------------------------------------------------------------*/

static void	_log_open_file(void);
static void	_log_close_file(void);
static void _GsiLog_display_item_or_value(gsi_item arg, gsi_int display_mode);
static void _GsiLog_display_array(gsi_int arg_type, gsi_item arg, gsi_int display_mode);
static void _GsiLog_display_list(gsi_int arg_type, gsi_item arg, gsi_int display_mode);
static void _GsiLog_display_item(gsi_int arg_type, gsi_item arg, gsi_int display_mode);
static void _GsiLog_display_simple_value(gsi_int arg_type, gsi_item arg, gsi_int display_mode);


/*-------------------------------------------------------------------------*
 *
 *
 *-------------------------------------------------------------------------*/

       long	log_indentation = 0;

static long	_log_mode		= 0;
static long	_log_msg_count	= 0;
static long	_log_file_idx	= 0;
static FILE	*_log_fileP		= NULL;



/*-------------------------------------------------------------------------*
 *
 *	Return as a string the value of a boolean variable
 *
 *-------------------------------------------------------------------------*/

char * bool_str_of(BOOL x)
{
	if (x == FALSE)
		return "FALSE";

	return "TRUE";
}

/*-------------------------------------------------------------------------*
 *
 *	Open a log file
 *
 *-------------------------------------------------------------------------*/
static void _log_open_file(void)
{
	long		i;
	char		*pszDateTime;
	char		logfile[256];


	/*
	 *	Get current time as a string and calculate relative
	 *	time since start of bridge process.
	 */
	pszDateTime = ctime( &Bridge_start_time );
	pszDateTime[24] = 0;


	/*
	 *	Build next log filename
	 */
	sprintf(logfile, "%s%s%s%s_%d.dat", ".", DIR_SEP, LOG_FILE_TEMPLATE, pszDateTime, _log_file_idx);
	for (i = 0 ; i < (long) strlen(logfile) ; i++) {

		if (logfile[i] == ' ')	logfile[i] = '_';
		if (logfile[i] == ':')	logfile[i] = '_';
	}
	_log_file_idx++;


	/*
	 *	Limit the number of files to be created
	 */
	if (_log_file_idx >= 200)
		_log_file_idx = 0;


	/*
	 *	Add next filename to current log file
	 */
	if (_log_fileP != NULL) {

		fprintf(_log_fileP, "\n\nLog file exceeded the maximum number of messages.\n");
		fprintf(_log_fileP, "Creating next log file: %s\n\n",	logfile);
	}

	_log_close_file();


	/*
	 *	Open the log file
	 */
	if (_log_mode & LOG_FILE) {


		printf("\n\n%s Creating new log file: %s\n",	pszDateTime, logfile);


		/*	Delete any existing file		*/
		unlink(logfile);


		/* and create a new one				*/
		if ((_log_fileP = (FILE *) fopen(logfile, "w")) == NULL) {

			printf("   Failed opening the file. Error number: %d.\n", errno);
		}
	}
}


/*-------------------------------------------------------------------------*
 *
 *	Close the current log file
 *
 *-------------------------------------------------------------------------*/

static void _log_close_file(void)
{
	if (_log_fileP != NULL)
		fclose(_log_fileP);

	_log_msg_count	= 0;
}


/*-------------------------------------------------------------------------*
 *
 *	Setup debugging and tracing modes
 *
 *-------------------------------------------------------------------------*/

void log_setup(long __log_mode)
{
	long		mask = LOG_MODE_ENTRY_EXIT | LOG_MODE_IO_RCV | LOG_MODE_IO_SEND | LOG_MODE_DEBUG | LOG_MODE_ALARM_EVENT;
	struct {
		short	value1;
		long	value2;
	} test_struct;
	char		*p1, *p2;
	

	/*
	 *	Initialize default settings
	 */
	log_indentation		= 0;
	_log_mode			= 0;
	_log_msg_count		= 0;
	_log_file_idx		= 0;
	_log_fileP			= NULL;

	
	
	/*
	 *	Initialization as request by user
	 */
	_log_mode			= __log_mode;



	if ((_log_mode & mask) == 0) {

		/* close the current log file		*/
		_log_close_file();

	} else {

		/* only open it if not yet done		*/
		if (_log_fileP == NULL)
			_log_open_file();
	}

	
	log_with_timestamp(mask, "G2 HLA Bridge %s. Compiled %s, %s.\n\n",
			G2HLA_VERSION, __DATE__, __TIME__);

	log_indentation++;
	log_without_timestamp(mask, "Operation mode:\n");

	log_indentation += 4;
	log_without_timestamp(mask,"Entry/Exit  logging   : %s\n", bool_str_of(_log_mode & LOG_MODE_ENTRY_EXIT));
	log_without_timestamp(mask,"I/O Receive logging   : %s\n", bool_str_of(_log_mode & LOG_MODE_IO_RCV));
	log_without_timestamp(mask,"I/O Send    logging   : %s\n", bool_str_of(_log_mode & LOG_MODE_IO_SEND));
	log_without_timestamp(mask,"Debug       logging   : %s\n", bool_str_of(_log_mode & LOG_MODE_DEBUG));
	log_without_timestamp(mask,"Alarm Event logging   : %s\n", bool_str_of(_log_mode & LOG_MODE_ALARM_EVENT));
	log_without_timestamp(mask,"Log to file           : %s\n", bool_str_of(_log_mode & LOG_FILE));
	log_without_timestamp(mask,"Log to stdout         : %s\n", bool_str_of(_log_mode & LOG_STDERR));
	log_without_timestamp(mask,"\n");
	log_without_timestamp(mask,"Big Endian processor  : %s\n", bool_str_of(is_big_endian));
	log_without_timestamp(mask,"\n");

	log_indentation -= 5;

	if (sizeof(int) != sizeof(long)) {

		log_without_timestamp(mask, "\n");
		log_without_timestamp(mask, "ATTENTION: You are not running this bridge on a 32 bit plaform.\n");
		log_without_timestamp(mask, "The size of an integer value is not 32 bits, which may create\n");
		log_without_timestamp(mask, "problems when decoding messages (Message fields were specified\n");
		log_without_timestamp(mask, "using the C int data type!).\n");
		log_without_timestamp(mask, "\n");
	}

	p1	= (char *) &test_struct.value1 + sizeof(short);
	p2	= (char *) &test_struct.value2;

	if (p1 != p2) {

		log_without_timestamp(mask, "\n");
		log_without_timestamp(mask, "ATTENTION: The compiler re-aligned your message structures.\n");
		log_without_timestamp(mask, "Spaces have been added to message fields that were not properly\n");
		log_without_timestamp(mask, "aligned in the memory space. Ensure you messages are properly\n");
		log_without_timestamp(mask, "aligned to avoid decoding problems.\n");
		log_without_timestamp(mask, "\n");
	}

}


/*-------------------------------------------------------------------------*
 *
 *	Log message with a timestamp
 *
 *-------------------------------------------------------------------------*/

void log_with_timestamp(long mode, char *fmt, ...)
{
	long		mask = LOG_MODE_ENTRY_EXIT | LOG_MODE_IO_RCV | LOG_MODE_IO_SEND | LOG_MODE_DEBUG | LOG_MODE_ALARM_EVENT;
	time_t		t = time(NULL);
	ulong		d;
	va_list		ap;
	char		*pszDateTime;

	/*
	 *	Ensure this type of logging is enabled
	 */

	if ((mode & _log_mode & mask) == 0)
		return;


	/*
	 *	Get current time as a string and calculate relative
	 *	time since start of bridge process.
	 */
	t = time(NULL);
	d = (ulong) t - (ulong) Bridge_start_time;

	pszDateTime = ctime( &t );
	pszDateTime[24] = 0;


	va_start(ap, fmt) ;


	/*
	 *	Ensure the file exists
	 */
	if (_log_msg_count >= LOG_MAX_MSG_COUNT || _log_fileP == NULL)
		_log_open_file();


	/*
	 *	Log information composed of one line with:
	 *		- timestamp as text
	 *		- user controllable identation
	 *		- user defined message
	 */

	if (_log_mode & LOG_FILE && _log_fileP != NULL) {

		/* 
		 *	Following line done to limit number of time stamps
		 *	and get an easier to read log file. Timestamp for
		 *	non LOG_MODE_ENTRY_EXIT messages is removed , if
		 *	LOG_MODE_ENTRY_EXIT logging mode is enabled.
		 */
		if ((_log_mode & LOG_MODE_ENTRY_EXIT) != 0 && mode != LOG_MODE_ENTRY_EXIT)
			fprintf(_log_fileP, "%25s", " ");
		else
			fprintf(_log_fileP, "%s ", pszDateTime);

		if (log_indentation > 0)
			fprintf(_log_fileP, "%*s", log_indentation, " ");

		vfprintf(_log_fileP, fmt, ap);
		fflush(_log_fileP);
	}

	if (_log_mode & LOG_STDERR) {

		if ((_log_mode & LOG_MODE_ENTRY_EXIT) != 0 && mode != LOG_MODE_ENTRY_EXIT)
			printf("%25s", " ");
		else
			printf("%s ", pszDateTime);

		if (log_indentation > 0)
			printf("%*s", log_indentation, " ");

		vprintf(fmt, ap);
	}

	_log_msg_count++;

	va_end (ap) ;
}


/*-------------------------------------------------------------------------*
 *
 *	Log message without a timestamp
 *
 *-------------------------------------------------------------------------*/

void log_without_timestamp(long mode, char *fmt, ...)
{
	long		mask = LOG_MODE_ENTRY_EXIT | LOG_MODE_IO_RCV | LOG_MODE_IO_SEND | LOG_MODE_DEBUG | LOG_MODE_ALARM_EVENT;
	va_list		ap;


	/*
	 *	Ensure this type of logging is enabled
	 */
	if ((mode & _log_mode & mask) == 0)
		return;


	va_start (ap, fmt) ;

	 
	/*
	 *	Ensure the file exists
	 */
	if (_log_msg_count >= LOG_MAX_MSG_COUNT || _log_fileP == NULL)
		_log_open_file();


	/*
	 *	Log information composed of one line with:
	 *		- identation as wide as a timestamp
	 *		- user controllable identation
	 *		- user defined message
	 */

	if (_log_mode & LOG_FILE && _log_fileP != NULL) {

		fprintf(_log_fileP, "%25s", " ");

		if (log_indentation > 0)
			fprintf(_log_fileP, "%*s", log_indentation, " ");

		vfprintf (_log_fileP, fmt, ap);
		fflush(_log_fileP);
	}

	if (_log_mode & LOG_STDERR) {

		printf("%25s", " ");

		if (log_indentation > 0)
			printf("%*s", log_indentation, " ");

		vprintf (fmt, ap);
	}

	_log_msg_count++;

	va_end (ap) ;
}
    

/*-------------------------------------------------------------------------*
 *
 *	Log message without a timestamp and without identation
 *
 *-------------------------------------------------------------------------*/

void log_without_identation(long mode, char *fmt, ...)
{
	long		mask = LOG_MODE_ENTRY_EXIT | LOG_MODE_IO_RCV | LOG_MODE_IO_SEND | LOG_MODE_DEBUG | LOG_MODE_ALARM_EVENT;
	va_list		ap;


	/*
	 *	Ensure this type of logging is enabled
	 */
	if ((mode & _log_mode & mask) == 0)
		return;


	va_start (ap, fmt) ;

	 
	/*
	 *	Ensure the file exists
	 */
	if (_log_msg_count >= LOG_MAX_MSG_COUNT || _log_fileP == NULL)
		_log_open_file();


	/*
	 *	Log information composed of one line with:
	 *		- user defined message
	 */
	if (_log_mode & LOG_FILE && _log_fileP != NULL) {

		vfprintf (_log_fileP, fmt, ap);
		fflush(_log_fileP);
	}

	if (_log_mode & LOG_STDERR)
		vprintf (fmt, ap);

	_log_msg_count++;

	va_end (ap) ;
}

/*-------------------------------------------------------------------------*
 *
 *	Log non zero terminated string
 *
 *-------------------------------------------------------------------------*/

void log_non_zero_terminated_string(long mode, char *sP, long sz)
{
	long	i;

	log_without_identation(mode, "'");

	for (i = 0 ; i < sz && sP[i] != '\0' ; i++)
		log_without_identation(mode, "%c", sP[i]);

	log_without_identation(mode, "'");
}

/*-------------------------------------------------------------------------*
 *
 *	Log a G2 object content
 *
 *-------------------------------------------------------------------------*/

void log_G2_object(long mode, gsi_item item)
{
	long		mask = LOG_MODE_ENTRY_EXIT | LOG_MODE_IO_RCV | LOG_MODE_IO_SEND | LOG_MODE_DEBUG | LOG_MODE_ALARM_EVENT;

	/*
	 *	Ensure this type of logging is enabled
	 */
	if ((mode & _log_mode & mask) == 0)
		return;

	/*
	 *	Generate the content of the object
	 */
	log_indentation++;

	_GsiLog_display_item_or_value(item, mode);

	log_indentation--;
}




/*-------------------------------------------------------------------------*
 *
 *  Functions for displaying G2/GSI items
 *
 *-------------------------------------------------------------------------*/


static void _GsiLog_display_item_or_value(gsi_item arg, gsi_int display_mode)
{
	gsi_int		arg_type = type_of(arg);
	gsi_int		element_count;
	gsi_item	*item_array;
	gsi_int		attr_count; 
	gsi_attr	*attr_array;
	gsi_char	*attr_name;
	int			i;

 
	log_indentation++;

	if (is_item(arg)) {

		if (is_array_type(arg_type))
			_GsiLog_display_array(arg_type,arg,display_mode);

		else if (is_list_type(arg_type))
			_GsiLog_display_list(arg_type,arg,display_mode);

		else if (is_simple_value_type(arg_type) || (arg_type == NULL_TAG))
			_GsiLog_display_item(arg_type,arg,display_mode);

		else
			log_without_timestamp(display_mode, 
				"\ndisplay_item_or_value ****  Error - Unknown type for item\n\n");

	}  else {

		switch(arg_type) {
			case NULL_TAG:
				log_without_timestamp(display_mode, "no value\n");
				break;

			case INTEGER_TAG:
			case LOGICAL_TAG:
			case FLOAT64_TAG:
			case SYMBOL_TAG:
			case STRING_TAG:
			case UNSIGNED_SHORT_VECTOR_TAG:
				_GsiLog_display_simple_value(arg_type,arg,display_mode);
				log_without_identation(display_mode,"\n");
				break;

			case HANDLE_TAG:
				log_without_timestamp(display_mode, "Item handle %d\n",handle_of(arg));
				break;

			case SEQUENCE_TAG: 
				element_count = gsi_element_count_of(arg);
				log_without_timestamp(display_mode, "");

				if (element_count > 0)
					item_array = elements_of(arg);

				for (i = 0 ; i < element_count ; i++)
					_GsiLog_display_item_or_value(item_array[i], display_mode);

				break;

			case STRUCTURE_TAG:
				attr_count = gsi_attr_count_of(arg); 

				if (attr_count > 0) {

					log_without_timestamp(display_mode, "and attributes...\n");
					attr_array = attrs_of(arg);

					for (i = 0 ; i < attr_count ; i++) {
						attr_name = attr_name_of(attr_array[i]);
						log_without_timestamp(display_mode,"%s: ",attr_name);

						_GsiLog_display_item_or_value(item_of_attr(attr_array[i]), display_mode);
					}
				}
				break;

			default:
				log_without_timestamp(display_mode, 
					"display_item_or_value  ****  Error - Unknown type for simple value\n\n");
		}
	}

	log_indentation--;
}





static void _GsiLog_display_array(gsi_int arg_type, gsi_item arg, gsi_int display_mode)
{
	gsi_int		attr_count		= attr_count_of(arg);
	gsi_int		element_count	= element_count_of(arg);
	char		*class_name		= class_name_of(arg);
	char		*name			= name_of(arg);
	char		*attr_name;
	long		*long_array;
	double		*double_array;
	char		**string_array;
	gsi_item	*item_array;
	gsi_attr	*attr_array;
	long		i;
  
	if (name == NULL)
		name = "";

	log_without_timestamp(display_mode, "%s, a %s with %d ",
		name, class_name, element_count);
	log_indentation++;
  
	switch(arg_type) {

		case INTEGER_ARRAY_TAG:
			log_without_identation(display_mode, "integer elements: ");

			if (element_count > 0) {
				long_array = int_array_of(arg);

				for (i = 0; i < (element_count - 1) ; i++) {
					log_without_identation(display_mode, "%d,",long_array[i]);
				}
				log_without_identation(display_mode, "%d\n",long_array[element_count-1]);
			}
			break;

		case LOGICAL_ARRAY_TAG:
			log_without_identation(display_mode, "logical elements: ");

			if (element_count > 0) {
				long_array = log_array_of(arg);

				for (i = 0; i < (element_count - 1) ; i++) {
					log_without_identation(display_mode, "%d,",long_array[i]);
				}
				log_without_identation(display_mode, "%d\n",long_array[element_count-1]);
			}
			break;

		case FLOAT64_ARRAY_TAG:
			log_without_identation(display_mode, "double elements: ");

			if (element_count > 0) {
				double_array = flt_array_of(arg);

				for (i = 0 ; i < (element_count - 1) ; i++) {
					log_without_identation(display_mode, "%4.4f,",double_array[i]);
				}
				log_without_identation(display_mode, "%4.4f\n",double_array[element_count-1]);
			}
			break;

		case STRING_ARRAY_TAG:
			log_without_identation(display_mode,"string elements: ");

			if (element_count > 0) {
				string_array = str_array_of(arg);

				for (i = 0 ; i < (element_count - 1) ; i++) {
					log_without_identation(display_mode,"%s,",string_array[i]);
				}
				log_without_identation(display_mode,"%s\n",string_array[element_count-1]);
			}
			break;

		case SYMBOL_ARRAY_TAG:
			log_without_identation(display_mode,"symbol elements: ");

			if (element_count > 0) {
				string_array = sym_array_of(arg);

				for (i = 0 ; i < (element_count - 1) ; i++) {
					log_without_identation(display_mode,"%s,",string_array[i]);
				}
				log_without_identation(display_mode,"%s\n",string_array[element_count-1]);
			}
			break;

		case VALUE_ARRAY_TAG:
		case ITEM_OR_VALUE_ARRAY_TAG:
		case ITEM_ARRAY_TAG:
		case QUANTITY_ARRAY_TAG:
			log_without_identation(display_mode,"mixed elements:\n");

			if (element_count > 0)
				item_array = elements_of(arg);

			for (i = 0; i < element_count; i++)
				_GsiLog_display_item_or_value(item_array[i],display_mode);
			break;
	}
  
	if (attr_count > 0) {

		log_without_timestamp(display_mode,"\nand attributes...\n");
		attr_array = attrs_of(arg);

		for (i = 0 ; i < attr_count ; i++)	{

			attr_name = attr_name_of(attr_array[i]);
			log_without_timestamp(display_mode,"%-30s: ",attr_name);

			_GsiLog_display_item_or_value(item_of_attr(attr_array[i]),display_mode);
		}

	}  else	{

		log_without_timestamp(display_mode,"\nand no attributes.\n");
	}
  
	log_indentation--;
}




static void _GsiLog_display_list(gsi_int arg_type, gsi_item arg, gsi_int display_mode)
{
	gsi_int		attr_count = attr_count_of(arg);
	gsi_int		element_count = element_count_of(arg);
	char		*class_name = class_name_of(arg);
	char		*name = name_of(arg);
	char		*attr_name;
	long		*long_array;
	double		*double_array;
	char		**string_array;
	gsi_item	*item_array;
	gsi_attr	*attr_array;
	long		i;
  
	if (name == NULL)
		name = "";

	log_without_timestamp(display_mode, "%s, a %s with %d ",
		name, class_name, element_count);
	log_indentation++;


	switch(arg_type) {
		case INTEGER_LIST_TAG:
			log_without_identation(display_mode,"integer elements: ");

			if (element_count > 0) {
				long_array = int_list_of(arg);

				for (i = 0 ; i < (element_count - 1) ; i++) {
					log_without_identation(display_mode,"%d,",long_array[i]);
				}
				log_without_identation(display_mode,"%d\n",long_array[element_count-1]);
			}
			break;

		case LOGICAL_LIST_TAG:
			log_without_identation(display_mode,"logical elements: ");

			if (element_count > 0) {
				long_array = log_list_of(arg);

				for (i = 0 ; i < (element_count - 1) ; i++) {
					log_without_identation(display_mode,"%d,",long_array[i]);
				}
				log_without_identation(display_mode,"%d\n",long_array[element_count-1]);
			}
			break;

		case FLOAT64_LIST_TAG:
			log_without_identation(display_mode,"double elements: ");

			if (element_count > 0) {
				double_array = flt_list_of(arg);

				for (i = 0 ; i < (element_count - 1) ; i++) {
					log_without_identation(display_mode,"%4.4f,",double_array[i]);
				}
				log_without_identation(display_mode,"%4.4f\n",double_array[element_count-1]);
			}
			break;

		case STRING_LIST_TAG:
			log_without_identation(display_mode,"string elements: ");

			if (element_count > 0) {
				string_array = str_list_of(arg);

				for (i = 0; i < (element_count - 1) ; i++) {
					log_without_identation(display_mode,"%s,",string_array[i]);
				}
				log_without_identation(display_mode,"%s\n",string_array[element_count-1]);
			}
			break;

		case SYMBOL_LIST_TAG:
			log_without_identation(display_mode,"symbol elements: ");

			if (element_count > 0) {
				string_array = sym_list_of(arg);

				for (i = 0 ; i < (element_count - 1) ; i++) {
					log_without_identation(display_mode,"%s,",string_array[i]);
				}
				log_without_identation(display_mode,"%s\n",string_array[element_count-1]);
			}
			break;

		case VALUE_LIST_TAG:
		case QUANTITY_LIST_TAG:
		case ITEM_OR_VALUE_LIST_TAG:
		case ITEM_LIST_TAG:
			log_without_identation(display_mode,"mixed elements:\n");

			if (element_count > 0)
				item_array = elements_of(arg);

			for (i = 0 ; i < element_count ; i++)
				_GsiLog_display_item_or_value(item_array[i], display_mode);

			break;
	}
  
	if (attr_count > 0) {

		log_without_timestamp(display_mode,"\nand attributes...\n");

		attr_array = attrs_of(arg);

		for (i = 0; i < attr_count ; i++) {

			attr_name = attr_name_of(attr_array[i]);
			log_without_timestamp(display_mode,"%-30s: ",attr_name);

			_GsiLog_display_item_or_value(item_of_attr(attr_array[i]), display_mode);
		}

	} else {

		log_without_timestamp(display_mode,"\nand no attributes.\n");
	}

	log_indentation--;
}




static void _GsiLog_display_item(gsi_int arg_type, gsi_item arg, gsi_int display_mode)
{
	char		*class_name		= class_name_of(arg);
	char		*name			= name_of(arg);
	gsi_int		attr_count		= attr_count_of(arg);
	gsi_int		history_count	= history_count_of(arg);
	gsi_int		history_type,
				max_count,
				min_interval;
	gsi_int		max_age;
	gsi_attr	*attr_array;
	char		*attr_name;
	void		*values;
	gsi_item	*mixed_values;
	double		*timestamps;
	double		truncated_timestamp,
				timestamp_remainder;
	gsi_int		year, month, day, hour, minute, second;
	long		i;
  
	if (name == NULL)
	  name = "";

	log_without_timestamp(display_mode,"%s, a %s with ", name, class_name);
	log_indentation++;

	if (is_simple_value_type(arg_type)) {

		_GsiLog_display_simple_value(arg_type,arg,display_mode);
		log_without_identation(display_mode,", and ");
	}

	if (attr_count > 0) {

		log_without_identation(display_mode,"attributes...\n");
		attr_array = attrs_of(arg);

		for (i = 0; i < attr_count; i++) {

			attr_name = attr_name_of(attr_array[i]);
			log_without_timestamp(display_mode," %-30s: ",attr_name);

			_GsiLog_display_item_or_value(item_of_attr(attr_array[i]), display_mode);
		}

	}  else {

		log_without_identation(display_mode,"no attributes.\n");
	}
  
	if (history_count > 0) {

		extract_history(arg, &values, &timestamps,&history_type);
		extract_history_spec(arg, &max_count, &max_age, &min_interval);

		log_without_timestamp(display_mode,"\n%d values currently in history whose spec permits them", history_count);
		log_without_identation(display_mode," at intervals of %d milliseconds or greater and allows for ", min_interval);

		if (max_count) {

			log_without_identation(display_mode, "%d historical values",max_count);

			if (max_age) {

				log_without_identation(display_mode," no more than %d seconds old.  ",max_age);

			} else {

				log_without_identation(display_mode,".  ");
			}

		}	else	{

			log_without_identation(display_mode,"historical values no more than %d seconds old.  ",max_age);
		}

		log_without_timestamp(display_mode,"\nCurrent contents of history are...\n");

		for (i = 0 ; i < history_count ; i++) {

			timestamp_remainder = modf(timestamps[i],&truncated_timestamp);
			decode_timestamp(truncated_timestamp, &year,&month,&day,&hour,&minute,&second);

			log_without_timestamp(display_mode," %d/%d/%d %d:%d:%d  ", month,day,year,hour,minute,second);

			switch(history_type) {
				case INTEGER_TAG:
				case LOGICAL_TAG:
					log_without_identation(display_mode," %d\n",((gsi_int *)values)[i]);
					break;
				case FLOAT64_TAG:
					log_without_identation(display_mode," %4.4f\n",((double *)values)[i]);
					break;
				case STRING_TAG:
				case SYMBOL_TAG:
					log_without_identation(display_mode," %s\n",((char **)values)[i]);
					break;
				case VALUE_TAG:
				case QUANTITY_TAG:
					mixed_values = (gsi_item *) values;
					switch(gsi_type_of(mixed_values[i])) {
						case INTEGER_TAG:
							log_without_identation(display_mode," %d\n", gsi_int_of(mixed_values[i]));
							break;
						case LOGICAL_TAG:
							log_without_identation(display_mode," %d\n", gsi_log_of(mixed_values[i]));
							break;
						case FLOAT64_TAG:
							log_without_identation(display_mode," %4.4f\n", gsi_flt_of(mixed_values[i]));
							break;
						case STRING_TAG:
							log_without_identation(display_mode," %s\n", gsi_str_of(mixed_values[i]));
							break;
						case SYMBOL_TAG:
							log_without_identation(display_mode," %s\n", gsi_sym_of(mixed_values[i]));
							break;
					}
					break;

			} /* end switch */
		} /* end for */
	} /* end if */

	log_indentation--;
}



static void _GsiLog_display_simple_value(gsi_int arg_type, gsi_item arg, gsi_int display_mode)
{
	int				i, len;
	unsigned short	*usv;
	unsigned short	element;

	switch(arg_type) {
		case INTEGER_TAG:
			log_without_identation(display_mode,"(integer value) : %d",gsi_int_of(arg));
			break;
		case LOGICAL_TAG:
			log_without_identation(display_mode,"(logical value) : %d",gsi_log_of(arg));
			break;
		case FLOAT64_TAG:
			log_without_identation(display_mode,"(double  value) : %4.4f",gsi_flt_of(arg));
			break;
		case SYMBOL_TAG:
			log_without_identation(display_mode,"(symbol  value) : %s",gsi_sym_of(arg));
			break;
		case STRING_TAG:
			log_without_identation(display_mode,"(string  value) : %s",gsi_str_of(arg));
			break;
		case UNSIGNED_SHORT_VECTOR_TAG:
			log_without_identation(display_mode,"(unsigned short vector value) : ");
			len = usv_length_of(arg);

			usv = usv_of(arg);

			for ( i = 0 ; i < len ; i++) {
				element = usv[i];

				log_without_identation(display_mode,"%x%x%x%x",
					element >> 12, (element>>8) & 0xf, (element>>4) & 0xf, element & 0xf);
			}
			break;
	}
}


