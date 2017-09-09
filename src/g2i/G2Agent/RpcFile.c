/***************************************************************************
 *
 *		Callbacks.c
 *
 *			Contains the required GSI RPC functions. 
 *
 *		Feel free to use this code as is, or modified to suit your needs.
 *		Although this software has been extensively tested, Gensym cannot
 *		guarantee error-free performance in all applications.  Accordingly,
 *		use of the software is at the customer's sole risk.
 *
 *		This file has been imported and converted from earlier an earlier
 *		version written in ANSI C.
 *
 ***************************************************************************/

#include	<windows.h>
#include	<direct.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<stdarg.h>
#include	<errno.h>
#include	<malloc.h>
#include	<math.h>
#include	<time.h>
#include	<string.h>

#include	<sys/types.h>
#include	<sys/stat.h>
#if !defined(WIN32)
#include	<sys/wait.h> 
#endif

#include	"G2Agent.h"


/*-------------------------------------------------------------------------*
 *
 *	Search next available file slot
 *
 *-------------------------------------------------------------------------*/

gsi_int get_next_file()
{
    gsi_int i;

    for (i = 0 ; i < MAX_FPTRS ; i++) {
        if (f_ptrs[i] == FILE_FREE)
            return(i);
	}

    //printf("\n Too Many files Opened ");
    return(MAX_FPTRS);

} 


/*-------------------------------------------------------------------------*
 *
 *	Open a file (append, read, read/write, write)
 *
 *-------------------------------------------------------------------------*/
void fopen_internal(gsi_char *fname, gsi_char *mode, gsi_char *modeText, call_identifier_type call_index)
{
    gsi_int       f_index;
    FILE         *fd;

	log_with_timestamp(LOG_MODE_DEBUG, "Opening file for %s: %s\n", modeText, fname);

    fflush(stdout);

#if defined(GSI_USE_WIDE_STRING_API)
	fd = *_wfopen(fname, mode);
#else
    fd = fopen(fname,mode);
#endif

    if (fd == BAD_OPEN) {

        set_int(local_gsi_itemP[0],OPEN_FAILED);
    	log_with_timestamp(LOG_MODE_DEBUG, "Opening file %s failed.\n", fname);

	} else {

        f_index = get_next_file();

        if (f_index == MAX_FPTRS)  { 

	    	log_with_timestamp(LOG_MODE_DEBUG, "Opening file %s failed. Too many open files.\n", fname);
            set_int(local_gsi_itemP[0],OPEN_FAILED);

        } else {

	    	log_with_timestamp(LOG_MODE_DEBUG, "Opening file %s success. Index %d.\n", fname, f_index);

            f_ptrs[f_index] = fd;
            set_int(local_gsi_itemP[0],f_index);
		}

    } /* end else */

    gsi_rpc_return_values(local_gsi_itemP,1,call_index,current_context);
}

void rpc_fopen_append(gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
    gsi_char         *fname;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_fopen_append().\n");

    fname = (char *) str_of(item_array[0]);
	fopen_internal(fname, "a+t", "append", call_index);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_fopen_append().\n\n");
}

void rpc_fopen_read(gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
    gsi_char         *fname;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_fopen_read().\n");

    fname = (char *) str_of(item_array[0]);
	fopen_internal(fname, "rt", "read", call_index);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_fopen_read().\n\n");
}

void rpc_fopen_read_write(gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
    gsi_char         *fname;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_fopen_read_write().\n");

    fname = (char *) str_of(item_array[0]);
	fopen_internal(fname, "w+t", "read/write", call_index);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_fopen_read_write().\n\n");
}

void rpc_fopen_write(gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
    gsi_char         *fname;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_fopen_write().\n");

    fname = (char *) str_of(item_array[0]);
	fopen_internal(fname, "wt", "write", call_index);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_fopen_write().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	Close a file
 *
 *-------------------------------------------------------------------------*/

void rpc_fclose(gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
    FILE        *fd = FILE_FREE;
	gsi_int		f_index; 
	int			ret = -1;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_fclose().\n");

	f_index = int_of(item_array[0]);
	if (f_index >= 0 || f_index < MAX_FPTRS)
		fd = f_ptrs[f_index];


	if (fd != FILE_FREE) {
	    ret = fclose(f_ptrs[f_index]);
	    f_ptrs[f_index] = FILE_FREE;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "Closing file at index %d. Result: %d\n", f_index, ret);

	if (ret == 0) 
		set_log(local_gsi_itemP[0], GSI_TRUE);
	else
		set_log(local_gsi_itemP[0], GSI_FALSE);

    gsi_rpc_return_values(local_gsi_itemP,1,call_index,current_context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_fclose().\n\n");
}



/*-------------------------------------------------------------------------*
 *
 *	Close all files
 *
 *-------------------------------------------------------------------------*/

void rpc_fclose_all (gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
    gsi_int		i;
	int			n, ret;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_fclose_all().\n");

	ret = GSI_TRUE;

    for (i = 0 ; i < MAX_FPTRS ; i++) {

        if (f_ptrs[i] != FILE_FREE) {

			n = fclose(f_ptrs[i]);
	        f_ptrs[i] = FILE_FREE;

			if (n != 0)
				ret = GSI_FALSE;
		}
	}

	set_log(local_gsi_itemP[0], ret);

    gsi_rpc_return_values(local_gsi_itemP,1,call_index,current_context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_fclose_all().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	Read from a file
 *
 *-------------------------------------------------------------------------*/

void rpc_fread(gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
	gsi_int		f_index; 
    FILE        *fd = FILE_FREE;
    int			nb_char, read_count;
    gsi_int		status = -1;
	gsi_int		ret = GSI_FALSE;
    gsi_char	str_value[STRSZ];

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_fread().\n");

	f_index = int_of(item_array[0]);
	if (f_index >= 0 || f_index < MAX_FPTRS)
		fd = f_ptrs[f_index];

	nb_char = int_of(item_array[1]);
	if (nb_char < 0 || nb_char >= STRSZ)
		nb_char = STRSZ - 1;

	str_value[0] = 0;

	if (fd != FILE_FREE) {

		read_count = fread(str_value, sizeof(gsi_char), nb_char, fd);
		str_value[STRSZ - 1] = 0;

		if (read_count > 0) {
			str_value[read_count] = 0;
			ret = GSI_TRUE;
		}

		log_with_timestamp(LOG_MODE_DEBUG, "Reading (result: %d, %d): %s\n", read_count, ret, str_value);
	}

    set_log(local_gsi_itemP[0], ret);
    set_str (local_gsi_itemP[1], str_value);

    gsi_rpc_return_values(local_gsi_itemP,2, call_index, current_context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_fread().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	Read a line from a file
 *
 *-------------------------------------------------------------------------*/

void rpc_freadline(gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
	gsi_int		f_index, n; 
	gsi_int		ret = GSI_FALSE;
    FILE        *fd = FILE_FREE;
    gsi_char	str_value[STRSZ], *sP;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_fread().\n");

	f_index = int_of(item_array[0]);
	if (f_index >= 0 || f_index < MAX_FPTRS)
		fd = f_ptrs[f_index];

	str_value[0] = 0;

	if (fd != FILE_FREE) {

#if defined(GSI_USE_WIDE_STRING_API)
		status = fgetws(fd,"%s", str_value);
#else
		sP = fgets(str_value, STRSZ, fd);
#endif

		n = strlen(str_value);
		if (sP != NULL && n > 0) {

			while (n > 0 && (str_value[n - 1] == '\n' || str_value[n - 1] == '\r')) {
				str_value[n - 1] = 0; 
				n--;
			}
		}

		if (sP != NULL)
			ret = GSI_TRUE;

		log_with_timestamp(LOG_MODE_DEBUG, "Reading (result: %d): %s\n", ret, str_value);
	}

    set_log(local_gsi_itemP[0], ret);
    set_str (local_gsi_itemP[1], str_value);

    gsi_rpc_return_values(local_gsi_itemP,2, call_index, current_context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_fread().\n\n");
}

/*-------------------------------------------------------------------------*
 *
 *	Write a line
 *
 *-------------------------------------------------------------------------*/

void rpc_fwrite(gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
    FILE        *fd = FILE_FREE;
	gsi_char	*strP;
	gsi_int		f_index; 
    gsi_int		status = -1;
	gsi_int		flush = GSI_FALSE;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_fwrite().\n");

	f_index = int_of(item_array[0]);
	strP = str_of(item_array[1]);
	flush = log_of(item_array[2]);

	if (f_index >= 0 || f_index < MAX_FPTRS)
		fd = f_ptrs[f_index];

	if (fd != FILE_FREE) {

#if defined(GSI_USE_WIDE_STRING_API)
		status = fwrite(strP, sizeof(gsi_char), wcslen(strP), fd);
#else
		status = fwrite(strP, sizeof(gsi_char), strlen(strP), fd);
#endif
		if (flush == GSI_TRUE)
			fflush(fd);

		log_with_timestamp(LOG_MODE_DEBUG, "Writing: (status: %d): %s\n", status, strP);
	}

    set_int(local_gsi_itemP[0], status);

    gsi_rpc_return_values(local_gsi_itemP,1,call_index,current_context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_fwrite().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	Seek to a position
 *
 *-------------------------------------------------------------------------*/

void rpc_fseek(gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
    FILE        *fd = FILE_FREE;
	gsi_int		f_index;
	double		pos;
    gsi_int		status = -1;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_fseek().\n");

	f_index = int_of(item_array[0]);
	pos = flt_of(item_array[1]);

	if (f_index >= 0 || f_index < MAX_FPTRS)
		fd = f_ptrs[f_index];

	if (fd != FILE_FREE) {

		status = fseek(fd, (long) pos, SEEK_SET);
		log_with_timestamp(LOG_MODE_DEBUG, "Seek to position: (status: %d): %d\n", status, pos);
	}

	if (status == 0)
	    set_log(local_gsi_itemP[0], GSI_TRUE);
	else
	    set_log(local_gsi_itemP[0], GSI_FALSE);


    gsi_rpc_return_values(local_gsi_itemP,1,call_index,current_context);

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_fseek().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	Check for file existence
 *
 *-------------------------------------------------------------------------*/

void rpc_fstats (gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
	gsi_char		*fname;
	int				ret = GSI_FALSE;
	int				rc;
	double			sz = 0.0;
	double			ctime, atime, mtime;
	struct _stat	buf[1];

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_fstats().\n");

    fname = str_of(item_array[0]);

#if defined(GSI_USE_WIDE_STRING_API)
	rc = _wstat (fname, buf);
#else
	rc = _stat (fname, buf);
#endif

	if (rc < 0 || !(buf[0].st_mode & _S_IFREG) ) {
		
		ret = GSI_FALSE;
		sz = 0.0;
		ctime = 0.0;
		atime = 0.0;
		mtime = 0.0;

	} else {

		ret = GSI_TRUE;
		sz = 1.0 * buf[0].st_size;
		ctime = 1.0 * buf[0].st_ctime;
		atime = 1.0 * buf[0].st_atime;
		mtime = 1.0 * buf[0].st_mtime;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "Stats of filename: %s, Ret: %d, size %g, ctime: %g, atime: %g, mtime: %g\n", fname, ret, sz, ctime, atime, mtime);

	set_log (local_gsi_itemP[0], ret);
	set_flt (local_gsi_itemP[1], sz);
	set_flt (local_gsi_itemP[2], ctime);
	set_flt (local_gsi_itemP[3], atime);
	set_flt (local_gsi_itemP[4], mtime);

	gsi_rpc_return_values (local_gsi_itemP, 5, call_index, gsi_current_context());

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_fstats().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	Delete a file
 *
 *-------------------------------------------------------------------------*/

void rpc_fdelete (gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
	gsi_char	*fname;
	int			ret;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_fdelete().\n");

    fname = (char *) str_of(item_array[0]);

#if defined(GSI_USE_WIDE_STRING_API)
	ret = _wunlink (fname);
#else
	ret = unlink (fname);
#endif

	log_with_timestamp(LOG_MODE_DEBUG, "Deleting file (result: %d): %s\n", ret, fname);

	if (ret == 0)
		set_log (local_gsi_itemP[0], GSI_TRUE);
	else
		set_log (local_gsi_itemP[0], GSI_FALSE);

	gsi_rpc_return_values (local_gsi_itemP, 1, call_index, gsi_current_context());

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_fdelete().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	Rename a file
 *
 *-------------------------------------------------------------------------*/

void rpc_frename (gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
    gsi_char    *old_fname, *new_fname;
	int			ret;

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_frename().\n");

    old_fname = (char *) str_of(item_array[0]);
    new_fname = (char *) str_of(item_array[1]);

#if defined(GSI_USE_WIDE_STRING_API)
	ret = _wrename(old_fname, new_fname);
#else
	ret = rename(old_fname, new_fname);
#endif

	log_with_timestamp(LOG_MODE_DEBUG, "Renaming file (result: %d) '%s' to '%s'\n", ret, old_fname, new_fname);

	if (ret == 0)
		set_log (local_gsi_itemP[0], GSI_TRUE);
	else
		set_log (local_gsi_itemP[0], GSI_FALSE);

	gsi_rpc_return_values (local_gsi_itemP, 1, call_index, gsi_current_context());

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_frename().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	Create a directory
 *
 *-------------------------------------------------------------------------*/

void rpc_create_directory (gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
	gsi_char		*directory;
	gsi_int			ret = GSI_FALSE;
	int				n;
#if defined(WIN32)
	int				rc;
	struct _stat	buf[1];
#else
	struct stat		statbuffer;
	long			status;
	mode_t			mask;
#endif

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_create_directory().\n");

    directory = (char *) str_of(item_array[0]);

	log_with_timestamp(LOG_MODE_DEBUG, "Create directory: %s\n", directory);

	/*
	 *	Create the directory
	 */
#if defined(WIN32)

#if defined(GSI_USE_WIDE_STRING_API)
	rc = _wstat (directory, buf);
#else
	rc = _stat (directory, buf);
#endif

	if (rc < 0 || !(buf[0].st_mode & _S_IFDIR) ) {

#if defined(GSI_USE_WIDE_STRING_API)
		n = _wmkdir(directory);
#else
		n = _mkdir(directory);
#endif

		if (n == 0)
			ret = GSI_TRUE;
		else if (errno == EEXIST)
			ret = GSI_TRUE;
		else
			ret = GSI_FALSE;
	
	} else {

		ret = GSI_TRUE;
	}


#else

	if (stat(directory, &statbuffer) == 0) {

		if (statbuffer.st_mode & S_IFDIR)
			ret = GSI_TRUE;/* File found and was a directory. */
		else
			ret = GSI_FALSE;  /* File found but not a directory.  Fail. */

	} else {

		if (errno == ENOENT) { /* Stat failed because file not there.  Create. */

			status = mkdir(directory, mask);

			if (status != 0)
				ret = GSI_FALSE; /* Directory creation failed */
			else
				ret = GSI_TRUE;

		} else { /* Stat failed for some other reason.  Fail. */

			ret = GSI_TRUE;
		}
	}

#endif

	set_log (local_gsi_itemP[0], ret);
	gsi_rpc_return_values (NULL_PTR, 1, call_index, gsi_current_context());

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_create_directory().\n\n");
}


/*-------------------------------------------------------------------------*
 *
 *	Check if a directtory exist
 *
 *-------------------------------------------------------------------------*/

void rpc_directory_exists (gsi_item item_array[], gsi_int count, call_identifier_type call_index)
{
	gsi_char		*directory;
	int				ret = GSI_FALSE;
	int				rc;
	struct _stat	buf[1];

	log_indentation = 0;
	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Entering rpc_directory_exists().\n");

    directory = str_of(item_array[0]);

	/*
	 *	Check if directory exists
	 */
#if defined(GSI_USE_WIDE_STRING_API)
	rc = _wstat (directory, buf);
#else
	rc = _stat (directory, buf);
#endif

	if (rc < 0 || !(buf[0].st_mode & _S_IFDIR) ) {
		ret = GSI_FALSE;
	} else {
		ret = GSI_TRUE;
	}

	log_with_timestamp(LOG_MODE_DEBUG, "Does directory exist: %s, Result: %d\n", directory, ret);

	set_log (local_gsi_itemP[0], ret);
	gsi_rpc_return_values (NULL_PTR, 1, call_index, gsi_current_context());

	log_with_timestamp(LOG_MODE_ENTRY_EXIT, "Leaving  rpc_directory_exists().\n\n");
}
