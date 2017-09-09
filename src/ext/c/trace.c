/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      trace.c
 +
 + CVS location: ext/c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):
 +   Rick Harris
 +
 + Description:  Backtraces from running G2s in production environments
 +
 + Key:
 +   (obsolete)
 +
 + File Organization:
 +   Section:      INCLUDE FILES
 +   Section:      DEFINES
 +   Section:      GLOBALS
 +   Section:      FUNCTION GROUP
 +
 + External Interface:
 +
 + Dependencies:
 +
 + Notes:
 +
 + Modifications:
 +   usage: All modifications to this file should be listed here, with most
 +          recent first. In general, modification comments should merely
 +          provide a reference to a detailed modification comment in the
 +          appropriate section/function header.
 +
 +   12/17/07,  jv: adding this comment header
 +
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* also defined in rtl/c/heap.c */
/* #define USE_BITMAP_FOR_CONS_TRACING */

#include "cprim.h"

#include "trace.h"

#include <signal.h>
#include <stdlib.h>
#include <string.h>

#if defined(WIN32)
#  include <windows.h>
#  include "msincls.h"
#endif

#if defined(unix)
#  include <sys/time.h> /* for timeout interrupts */
#  include <sys/signal.h>
#  include <sys/types.h>
#  ifdef __STDC__
#    include <unistd.h>
#  endif
#  include <stdarg.h>
#endif /* unix */

#include "networks.h"

#ifdef G2_51
#  include "netevent.h"
#endif


#define BACKTRACE_HASH_MASK 255
#define BACKTRACE_HASH_SIZE 256
#define CONS_BACKTRACE_SIZE 12
#define gsi_backtrace_array_size 25
#define NETWORK_IO_TRACE_BLOCK_SIZE (1024L * 1024L *sizeof(trace_block)/sizeof(trace_block))
#define NUMBER_OF_BACKTRACE_FRAMES 400
#define NUMBER_OF_BACKTRACE_FRAMES_SHORT 160

#ifdef FUNCTION_HISTORY
#  define FUNCTION_TRACE_HISTORY_SIZE 256
#endif

#ifdef USE_BITMAP_FOR_CONS_TRACING
#  define CONS_CHECKING_REGION_SIZE (256*1024*1024)
#  define CONS_CHECKING_BITMAP_SIZE (CONS_CHECKING_REGION_SIZE>>8)
#endif

#define TRACE_ENTRY             0L
#define TRACE_NOTE              1L
#define TRACE_READ_BEGIN        2L
#define TRACE_WRITE_BEGIN       3L
#define TRACE_READ_END          4L
#define TRACE_WRITE_END         5L
#define TRACE_BACKTRACE         6L
#define TRACE_BACKTRACE_CONS    7L
#define TRACE_BACKTRACE_RECLAIM 8L


#define TRACE_NOTE_STRING(trace) ((char *)(trace)+sizeof(trace_note))
#define TRACE_BACKTRACE_BUFFER(trace) (((trace_backtrace *)trace)->backtrace->backtrace)
#define TRACE_BUFFER(trace) ((char *)(trace)+sizeof(trace_io_end))
/* This works when the size of a pointer is 4 or 8 bytes */
#define TRACE_ENTRY_ALIGN(addr) \
  (char *)((((unsigned long)(addr)-1L)|((unsigned long)sizeof(trace_entry *)-1L))+1L)


typedef struct backtrace_list_struct
{
    void **backtrace;
    struct backtrace_list_struct *next;
    unsigned long sequence_number_of_most_recent_use;
    unsigned long timestamp_of_most_recent_use;
} backtrace_list;

typedef struct trace_block
{
   struct trace_block *tb_next;
   char *tb_free;
   char *tb_end;
} trace_block;

typedef struct trace_entry
{
   struct trace_entry *te_next;
   long te_dtime;
   long te_atime;
#ifdef WIN32
   long te_mtime;
#endif
   unsigned long te_sequence_number;
   long te_type;
} trace_entry;

typedef struct trace_note
{
   trace_entry entry;
} trace_note;

typedef struct trace_io_begin
{
   trace_entry entry;
   long handle;
   long fd;
   long length;
} trace_io_begin;

typedef struct trace_io_end
{
   trace_entry entry;
   long handle;
   long fd;
   long io_result;
   long buffer_size;
} trace_io_end;

typedef struct trace_backtrace
{
    trace_entry entry;
    struct trace_backtrace *previous_cons_backtrace;
    void *cons;
    backtrace_list *backtrace;
} trace_backtrace;


typedef void fn_type();
typedef unsigned int function_count_type;


/* external functions */
extern char *g2ext_current_time_no_newline();
extern int   g2ext_run_command_line(char *command_string);
extern Gensym_Long g2ext_g2_clock_ticks(Gensym_Long mask);
extern long  g2ext_write_string_to_console();
extern long  g2int_run_trace_function();
#ifndef WIN32
extern char *getenv();
#endif

/* forward declarations */
long g2ext_lookup_backtrace_frame_index();
void g2ext_print_all_backtraces();
static int process_trace_control_command();
static void write_cons_summary_internal_2();


static char *address_file = 0;
static int   automatic_trace_control_file = FALSE;
static void *backtrace_caller = 0;
static void *backtrace_cons = 0;
static int   backtrace_cons_reclaim = FALSE;
static char  backtrace_frame_full_name_buffer[64];
static long  backtrace_frames_to_skip = 4;
static int   backtrace_roots_written = FALSE;
static void *backtrace_second_caller = 0;
static void *backtrace_stack_pointer = 0;
static int   backtrace_summary_only_p = FALSE;
static int   backtrace_targets_written = FALSE;
static int   buffer_byte_use_decimal_p = TRUE;
static int   can_get_names = TRUE;
static char *executable_file = 0;
static int   function_address_table_size = 0; /* about 22000 in g2 */
static char *function_name_buffer = 0;
static int   have_names = FALSE;
static int   in_network_io_trace = FALSE;
static long  last_network_io_time = 0L;
static int   last_network_io_time_p = FALSE;
static int   network_io_backtrace_p = FALSE;
static int   network_io_time_p = TRUE;
static int   network_io_trace_backtrace_request = FALSE;
static int   print_cons_addresses_p = TRUE;
static int   processing_trace_control_commands = 0;
static int   reading_trace_control_string = FALSE;
static char  temp_checksum_line[30];
static char *tmp_backtrace_root_file = "/tmp/backtrace_root_file.lisp";
static char *tmp_backtrace_target_file = "/tmp/backtrace_target_file.lisp";
static long  total_number_of_backtraces = 0;
static int   trace_consing_p = FALSE;
static FILE *trace_control = 0;
static char *trace_control_file = 0;
static int   trace_control_file_index = 0;
static int   trace_control_last_char = 0;
static int   trace_control_line_number = 1;
static int   trace_control_next_char = 0;
static char *trace_control_string = 0;
static int   trace_control_string_length = 0;
static int   trace_control_string_wide_p = FALSE;
static int   trace_control_verbose = FALSE;
static char *trace_function_name = 0;
static int   trace_network_io_data_p = FALSE;
static FILE *trace_output = 0;
static char *trace_output_file_name;
static int   trace_output_width = 128;
static int   trace_reclaiming_p = FALSE;
static void *trace_write_single_cons = 0;
static int   use_lisp_names_when_possible = TRUE;
static int   write_network_data = TRUE;
static int  *x_fn_file_size_array;
static long  x_fn_trace_counter = 0; /* records the order in which fcns are called */
static long *x_fn_trace_count_array = 0;
static long *x_fn_trace_ecount_array = 0;
static int   x_fn_trace_size = 0;
static void *xxx_last_cons =  0;
static int   xxx_last_type = -1;

#ifndef WIN32
static long  first_network_io_time = 0;
static long  have_first_network_io_time = FALSE;
static long  total_network_io_time = 0;
#endif

#ifdef FUNCTION_HISTORY
static int   function_history_enabled = FALSE;
static int   x_fn_trace_index_history[FUNCTION_TRACE_HISTORY_SIZE] = {0};
static long  x_fn_trace_history_index = 0;
#endif

#ifdef USE_BITMAP_FOR_CONS_TRACING
static int  *consing_bitmap = 0;
static void *g2ext_cons_checking_region_start = 0;
#endif

static struct trace_backtrace **cons_backtrace_table = 0;
static char                   **x_fn_name_array;
static unsigned long            backtrace_sequence_number = 0;
static unsigned long            next_trace_entry_sequence_number = 0;
static backtrace_list         **backtrace_hash_table = 0;
static function_count_type     *function_count_table; /* short may overflow in 10 minutes or so */
static trace_backtrace         *last_cons_backtrace = 0;
static trace_backtrace         *last_free_cons_backtrace = 0;
static trace_block             *current_trace_block = (trace_block *)0;
static trace_block             *first_trace_block = (trace_block *)0;
static trace_entry             *first_trace_entry = (trace_entry *)0;
static trace_entry             *last_trace_entry = (trace_entry *)0;
static fn_type                **x_fn_array;

static struct address_name_struct
{
  unsigned long address;
  char *name;
} *function_address_table = 0;

static struct ci_struct
{
  function_count_type cnt;
  unsigned short idx;
} *g2ext_ci_array;

static char *trace_io_type_names[] =
{
  "Entry", "Note", "Begin Read", "Begin Write", "End Read", "End Write",
  "Backtrace", "Cons Backtrace", "Reclaim Backtrace", (char *)0
};



/* externally accessible global variables */
int       function_tracing_enabled = FALSE;
int       g2ext_gsi_print_backtrace_flag = FALSE;
int       g2ext_kept_cons_backtrace_limit = -1;
int       g2ext_network_io_backtrace_interval = 10;
int       g2ext_network_io_backtrace_used_p = FALSE;
int       g2ext_network_io_find_leaks = FALSE;
int       g2ext_network_io_one_line_backtrace_p = FALSE;
int       g2ext_network_io_trace_p = FALSE;
void     *g2ext_pc_at_c_gensym_signal_handler = 0;
void     *g2ext_saved_backtrace_array[SAVED_BACKTRACE_ARRAY_SIZE];
int       g2ext_saved_backtrace_array_fcount = 0;
int       g2ext_saved_backtrace_array_fsize = SAVED_BACKTRACE_ARRAY_SIZE;
int       g2ext_use_virtual_alarm_p = FALSE;






/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      FUNCTION GROUP -- Tracing Functions
%
% Description:
%
% Notes:
%
% Modifications:
%   usage: Modifications in this header should be restricted to mentioning
%      the addition or deletion of functions within this section. Actual
%      function changes should be commented in the specific function's
%      header.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

void g2ext_note_fn_table_size(size,fn_array,fn_name_array,fn_file_size_array)
  int size;
  fn_type *fn_array[];
  char *fn_name_array[];
  int fn_file_size_array[];
{
  if (size == 0) {
    function_tracing_enabled = FALSE;
    x_fn_trace_size = size;
    return;
  }
  function_tracing_enabled = TRUE;
  x_fn_trace_size = size;
  x_fn_trace_count_array = (long *)calloc(size,sizeof(long *));
#ifdef FUNCTION_TRACE_EXECUTION_COUNTS
  x_fn_trace_ecount_array = (long *)calloc(size,sizeof(long *));
#endif
  x_fn_array = fn_array;
  x_fn_name_array = fn_name_array;
  x_fn_file_size_array = fn_file_size_array;
#if defined(_IBMR2)
  {
    int i;
    for (i=0; i<size; i++)
      x_fn_array[i] = (fn_type *)*(void **)(x_fn_array[i]);
  }
#endif
}

static void heapify_fn_table_array(i,s,key,index)
    int i,s;
    intptr_t *key;
    int *index;
{
  int l = (i<<1)+1;
  int r = l+1;
  int largest = (( (l <= s) && (key[index[l]] > key[index[i]]) ) ? l : i);
  if ( (r <= s) && (key[index[r]] > key[index[largest]]) ) largest = r;
  if ( largest != i ) {
    int saved_index = index[i];
    index[i] = index[largest];
    index[largest] = saved_index;
    heapify_fn_table_array(largest,s,key,index);
  }
}

static void sort_fn_table_array(size,key,index)
    int size;
    intptr_t *key;
    int *index;
{
  int i;
  for(i=0; i<size; i++) index[i] = i;
  for(i=(size>>1)-1; i>=0; i--) {
    heapify_fn_table_array(i,size-1,key,index);
  }
  for(i=size-1; i>=1; i--) {
    int largest_index = index[0];
    index[0] = index[i];
    index[i] = largest_index;
    heapify_fn_table_array(0,i-1,key,index);
  }
}

static void print_recent_fn_trace(limit)
  int limit;
{
  int i, size = x_fn_trace_size;
  int start = (limit<=0 || limit>=size)?size:(size-limit);
  int *index;
  FILE *out = trace_output?trace_output:stdout;

  if (x_fn_trace_counter==0 || size==0) return;
  index = (int *)malloc(size*sizeof(int));
  if (index == 0) return;
  sort_fn_table_array(x_fn_trace_size,x_fn_trace_count_array,index);
  fprintf(out,"\nRecently Called Functions:\n");
  for (i=size-1; i>=start; i--) {
    long count = x_fn_trace_count_array[index[i]];
    long ecount = x_fn_trace_ecount_array==0?0:x_fn_trace_ecount_array[index[i]];
    if (ecount>0)
      fprintf(out, "\n%8d  %8d  %s", (int) count, (int) ecount,
              x_fn_name_array[index[i]]);
    else if (count>0)
      fprintf(out, "\n%8d  %s", (int) count, x_fn_name_array[index[i]]);
  }
  fprintf(out,"\n\n");
  free(index);
}

static void print_recent_fn_trace_into_string(limit,buffer)
  int limit;
  char *buffer;
{
  int i, size = x_fn_trace_size;
  int start = (limit<=0 || limit>=size)?size:(size-limit);
  int *index;
  char *string = buffer;

  if (x_fn_trace_counter==0 || size==0) return;
  index = (int *)malloc(size*sizeof(int));
  if (index == 0) return;
  sort_fn_table_array(size,x_fn_trace_count_array,index);
  sprintf(string,"\nRecently Called Functions");
  string += strlen(string);
  for (i=size-1; i>=start; i--) {
    if (x_fn_trace_count_array[index[i]]>0) {
      sprintf(string, "\n  %s",x_fn_name_array[index[i]]);
      string += strlen(string);
    }
  }
  sprintf(string,"\n");
  free(index);
}

#ifdef FUNCTION_HISTORY
void print_fn_history()
{
  int history_index, line_index;
  FILE *out = trace_output?trace_output:stdout;

  if (!function_history_enabled) return;
  fprintf(out,"\nFunction Trace History\n");
  history_index = x_fn_trace_history_index;
  line_index = 0;
  do {
    int idx = x_fn_trace_index_history[history_index];
    if (idx != 0) {
      char *name = x_fn_name_array[idx];
      int name_len = strlen(name);
      if (line_index > 0) {
        if (line_index + name_len + 1 > 100) {
          fprintf(out,"\n");
          line_index = 0;
        } else {
          fprintf(out," ");
          line_index++;
        }
      }
      fprintf(out,"%s",name);
      line_index += name_len;
    }
    if (FUNCTION_TRACE_HISTORY_SIZE <= ++history_index) history_index = 0;
  } while (history_index != x_fn_trace_history_index);
  fprintf(out,"\n");
  fflush(out);
}
#endif

static void print_fn_trace()
{
  print_recent_fn_trace(0);
#ifdef FUNCTION_HISTORY
  print_fn_history();
#endif
}


static long network_io_get_dtime()
{
  long current_g2_time, dtime;
  if (!network_io_time_p) return 0L;
  current_g2_time = g2ext_g2_clock_ticks((1L << 30L) - 1L);
  if (!last_network_io_time_p) {
    last_network_io_time_p = TRUE;
    last_network_io_time = current_g2_time;
  }
  dtime = current_g2_time - last_network_io_time;
  if (dtime < 0L) dtime += (1L << 30L);
  last_network_io_time = current_g2_time;
#ifndef WIN32
  if (!have_first_network_io_time) {
    have_first_network_io_time = TRUE;
    first_network_io_time = current_g2_time;
  }
  {
    long ttime;
    ttime = current_g2_time - first_network_io_time;
    if (ttime < 0L) ttime += (1L << 30L);
    total_network_io_time = ttime;
  }
#endif
  return dtime;
}

static trace_block *new_trace_block()
{
  trace_block *block = (trace_block *)malloc(NETWORK_IO_TRACE_BLOCK_SIZE);
  if (block == 0) return 0;
  block->tb_next = (trace_block *)0;
  block->tb_free = TRACE_ENTRY_ALIGN((char *)block + sizeof(trace_block));
  block->tb_end = (char *)block + NETWORK_IO_TRACE_BLOCK_SIZE;
  return block;
}

static char *make_trace_entry(type,size)
   long type,size;
{
  char *free, *next;
  trace_entry *entry;
  if ((type==TRACE_BACKTRACE || type==TRACE_BACKTRACE_CONS || type==TRACE_BACKTRACE_RECLAIM) &&
      last_free_cons_backtrace) {
    entry = (trace_entry *)last_free_cons_backtrace;
    last_free_cons_backtrace = last_free_cons_backtrace->previous_cons_backtrace;
  } else {
    if (current_trace_block == (trace_block *)0) {
      first_trace_block = new_trace_block();
      if (first_trace_block == 0) return 0;
      current_trace_block = first_trace_block;
    }
    free = current_trace_block->tb_free;
    if ((next = free+size) >= current_trace_block->tb_end) {
      trace_block *next_block = current_trace_block->tb_next;
      if (next_block == (trace_block *)0) {
        next_block = new_trace_block();
        if (next_block == 0) return 0;
        current_trace_block->tb_next = next_block;
      }
      current_trace_block = next_block;
      free = current_trace_block->tb_free;
      next = free+size;
    }
    current_trace_block->tb_free = TRACE_ENTRY_ALIGN(next);
    entry = (trace_entry *)free;
    if (last_trace_entry == (trace_entry *)0)
      first_trace_entry = entry;
    else
      last_trace_entry->te_next = entry;
    last_trace_entry = entry;
    entry->te_next = (trace_entry *)0;
  }
  entry->te_dtime = network_io_get_dtime();
#ifdef WIN32
  entry->te_atime = GetTickCount() & 0x3fffffff;
  entry->te_mtime = GetMessageTime() & 0x3fffffff;
#else
  entry->te_atime = total_network_io_time;
#endif
  entry->te_sequence_number = next_trace_entry_sequence_number;
  next_trace_entry_sequence_number += 1;
  entry->te_type = type;
  return (char *)entry;
}

void g2ext_network_io_trace_begin(type,handle,fd,length)
    long type, handle, fd, length;
{
  trace_io_begin *trace;

  if (!g2ext_network_io_trace_p || in_network_io_trace ||
      trace_consing_p || trace_reclaiming_p) return;
  in_network_io_trace = TRUE;
  trace = (trace_io_begin *)make_trace_entry(type,sizeof(trace_io_begin));
  if (trace == 0) return;
  trace->handle = handle;
  trace->fd = fd;
  trace->length = length;
  in_network_io_trace = FALSE;
  if (network_io_trace_backtrace_request) g2ext_network_io_trace_backtrace();
}

void g2ext_network_io_trace_end(type,handle,fd,io_result,buffer)
    long type, handle, fd, io_result;
    char *buffer;
{
  int buffer_size;
  trace_io_end *trace;

  if (!g2ext_network_io_trace_p || in_network_io_trace ||
      trace_consing_p || trace_reclaiming_p) return;
  in_network_io_trace = TRUE;
  buffer_size = (trace_network_io_data_p && (io_result > 0)) ? io_result : 0;
  trace = (trace_io_end *)make_trace_entry(type,sizeof(trace_io_end)+buffer_size);
  if (trace == 0) return;
  trace->handle = handle;
  trace->fd = fd;
  trace->io_result = io_result;
  trace->buffer_size = buffer_size;
  if (0 < buffer_size) memcpy(TRACE_BUFFER(trace),buffer,buffer_size);
  in_network_io_trace = FALSE;
  if (network_io_trace_backtrace_request) g2ext_network_io_trace_backtrace();
}

static void write_network_io_trace_buffer(out,size,buffer)
    FILE *out;
    int size;
    char *buffer;
{
  int i;
  while (0 < size) {
    int bytes_per_line = 32;
    fprintf(out,"\n");
    for (i=bytes_per_line; (i>0) && (size>0); i--, size--, buffer++)
      fprintf(out, buffer_byte_use_decimal_p? "%3.3d " : "%2.2x ",
              (int)*(unsigned char *)buffer);
  }
  fprintf(out,"\n");
}

static char *network_io_trace_get_checksum(file)
    char *file;
{
#if defined(sparcsol) || defined(sun4)
  char name[L_tmpnam+1], command[80];
  FILE *f;
  if (0 == (f = GFOPEN(file,"r"))) {
    return 0;
  }
  GFCLOSE(f);
  tmpnam(name);
  sprintf(command, "sum %s > %s", file, name);
  g2ext_run_command_line(command);
  if (0 == (f = GFOPEN(name,"r"))) {
    return 0;
  }
  fgets(temp_checksum_line,30,f);
  GFCLOSE(f);
  return temp_checksum_line;
#else
  return 0;
#endif
}

static int read_function_address_file_1(file,expected_checksum_line)
    char *file;
    char *expected_checksum_line;
{
  int lines=0, characters=0, fat_index=0, ch;
  char *buffer, checksum_line[30];
  FILE *in = GFOPEN(file,"r");
  if (!in) return 0;
  fgets(checksum_line,30,in);
  if ((0 != expected_checksum_line) &&
      (0 != strcmp(checksum_line,expected_checksum_line))) {
    GFCLOSE(in);
    return 0;
  }
  while (EOF != (ch=fgetc(in))) {
    characters += 1;
    if ('\n' == ch) lines += 1;
  }
  GFCLOSE(in);
  if ((char *)0 != function_name_buffer) free(function_name_buffer);
  function_name_buffer = (char *)malloc(characters-lines*9);
  if (function_name_buffer == 0) {
    can_get_names = FALSE;
    return 0;
  }
  buffer = function_name_buffer;
  if ((struct address_name_struct *)0 != function_address_table)
    free(function_address_table);
  function_address_table
    = (struct address_name_struct *)malloc(lines*sizeof(struct address_name_struct));
  if (function_address_table == 0) {
    can_get_names = FALSE;
    return 0;
  }
  function_address_table_size = lines;
  in = GFOPEN(file,"r");
  fgets(checksum_line,30,in);
  while(0<fscanf(in,"%lx %s\n",&function_address_table[fat_index].address,buffer)) {
    int len = strlen(buffer);
    function_address_table[fat_index].name = buffer;
    buffer += 1+len;
    fat_index += 1; }
  GFCLOSE(in);
  have_names = 2 < lines;
  can_get_names = have_names;
  return 1;
}

int g2ext_read_function_address_file(file)
    char *file;
{
  return read_function_address_file_1(file,0);
}

static int get_function_addresses_from_fn_table()
{
  int i, j, size = x_fn_trace_size;
  int *index;

  if (size==0) return 0;
  if (have_names) {
    for(i=0; i<size; i++) {
      j = g2ext_lookup_backtrace_frame_index(x_fn_array[i]);
      if ((j >= 0) &&
          (function_address_table[j].address == (unsigned long)x_fn_array[i]))
        function_address_table[j].name = x_fn_name_array[i];
    }
  } else {
    index = (int *)malloc(size*sizeof(int));
    if (index == 0) return 0;
    if ((struct address_name_struct *)0 != function_address_table)
      free(function_address_table);
    function_address_table
      = (struct address_name_struct *)malloc(size*sizeof(struct address_name_struct));
    if (function_address_table == 0) {
        free(index);
        return 0;
    }
    function_address_table_size = size;
    sort_fn_table_array(size,(intptr_t *)x_fn_array,index);
    for(i=0; i<size; i++) {
      function_address_table[i].address = (unsigned long)x_fn_array[index[i]];
      function_address_table[i].name = x_fn_name_array[index[i]];
    }
    have_names = TRUE;
    can_get_names = TRUE;
    free(index);
  }
  return 1;
}

static void get_names(file)
  char *file;
{
#if defined(sparcsol) || defined(sun4)
  char name[L_tmpnam+1], nm_command[400];
  FILE *f;
  if (!(file && can_get_names))return;
  if (0 == (f = GFOPEN(file,"r"))) {
    can_get_names = FALSE;
    return;
  }
  GFCLOSE(f);
  tmpnam(name);
  sprintf(nm_command,
#if defined(sparcsol)
          "( /usr/ucb/sum %s ; /usr/ccs/bin/nm -px %s | /usr/bin/grep -i ' t ' | /usr/bin/sed -e 's/ [tT] / /' | /usr/bin/sed -e 's/^0x//' | /usr/bin/sort ) > %s",
#endif
#if defined(sun4)
          "( /usr/bin/sum %s ; /usr/bin/nm -ap %s | /usr/bin/grep -i ' t ' | /usr/bin/grep -v '\\.' | /usr/bin/grep -v '__gnu_compiled_c' | /usr/bin/grep -v ' t noerr' | /usr/bin/sed -e 's/ [tT] _/ /' -e 's/ [tT] / /' | /usr/bin/sort ) > %s",
#endif
          file, file, name);
  g2ext_run_command_line(nm_command);
  if (0 == (f = GFOPEN(name,"r"))) {
    can_get_names = FALSE;
    return;
  }
  GFCLOSE(f);
  g2ext_read_function_address_file(name);
  sprintf(nm_command,"rm -f %s",name);
  g2ext_run_command_line(nm_command);
#else
  can_get_names = FALSE;
#endif
}

static int get_function_address_file()
{
  if (have_names) return TRUE;
  if (can_get_names) {
      if (!address_file)
          address_file = getenv("G2_FUNCTION_ADDRESS_FILE");
      if (!address_file ||
          !read_function_address_file_1(address_file,
                                        network_io_trace_get_checksum(executable_file)))
          get_names(executable_file);
  }
  if (!have_names || use_lisp_names_when_possible)
    get_function_addresses_from_fn_table();
  return have_names;
}

static char *lookup_backtrace_frame(frame,buffer,fn,frame_index,include_second_p)
    void *frame;
    char *buffer;
    unsigned long *fn;
    int frame_index;
    int include_second_p;
{
  unsigned long addr = (unsigned long)frame;
  unsigned long min = 0, max = function_address_table_size-1;
  unsigned long next, next_addr;
  int i;

  if (0 == function_address_table_size ||
      addr<function_address_table[min].address ||
      addr>=function_address_table[max].address) {
    fn[frame_index]=(unsigned long)(-1);
    if((char *)0 == buffer)return (char *)0;
    sprintf(buffer,"%08lx",(unsigned long)frame);
    return buffer; }
  while (max > min+1) {
    next = (max+min)>>1;
    next_addr = function_address_table[next].address;
    if (addr <= next_addr) max = next;
    if (addr >= next_addr) min = next;
  }
  fn[frame_index]=min;
  if (function_count_table) {
    for (i=0; i<frame_index; i++)
      if (((i!=1) || include_second_p) &&
          (fn[i]==min)) goto finish;
    function_count_table[min] += 1;
  }
finish:
  return function_address_table[min].name;
}

long g2ext_lookup_backtrace_frame_index(frame)
    void *frame;
{
  unsigned long addr = (unsigned long)frame;
  unsigned long min = 0, max = function_address_table_size-1;
  unsigned long next, next_addr;

  if (0 == function_address_table_size ||
      addr<function_address_table[min].address ||
      addr>=function_address_table[max].address)
    return -1;
  while (max > min+1) {
    next = (max+min)>>1;
    if (addr == (next_addr = function_address_table[next].address))
      return next;
    if (addr < next_addr) max = next;
    else min = next; }
  return min;
}

void *g2ext_backtrace_frame_base(index)
  long index;
{
  if (index<0)
    return 0;
  else
    return (void *)(function_address_table[index].address);
}

char *g2ext_backtrace_frame_name(index)
  long index;
{
  if (index<0)
    return 0;
  else
    return function_address_table[index].name;
}

char *g2ext_backtrace_frame_full_name(frame)
    void *frame;
{
  long index;
  void *base;
  char *name;
  unsigned long offset;

  if (!have_names) get_function_address_file();
  index = g2ext_lookup_backtrace_frame_index(frame);
  base = g2ext_backtrace_frame_base(index);
  name = g2ext_backtrace_frame_name(index);
  offset = (unsigned long)frame - (unsigned long)base;
  if (name == 0)
    sprintf(backtrace_frame_full_name_buffer,"0x%lx",offset);
  else if (offset == 0)
    sprintf(backtrace_frame_full_name_buffer,"%s",name);
  else
    sprintf(backtrace_frame_full_name_buffer,"%s+0x%lx",name,offset);
  return backtrace_frame_full_name_buffer;
}

long g2ext_get_name_for_function(buffer,addr)
  char *buffer;
  void *addr;
{
  char *name = g2ext_backtrace_frame_full_name(addr);
  strcpy(buffer,name);
  return strlen(name);
}

void g2ext_print_backtrace()
{
  void *backtrace_array[gsi_backtrace_array_size];
  int count = g2ext_save_backtrace_into_array(backtrace_array, gsi_backtrace_array_size,
                                              g2ext_gsi_print_backtrace_flag?2:1);
  int i;
  if (count==0) return;
  printf("Backtrace:\n");
  for (i=0; i<count; i++)
    printf("  %s\n", g2ext_backtrace_frame_full_name(backtrace_array[i]));
  printf("\n");
  fflush(stdout);
  print_recent_fn_trace(15);
}

long g2ext_print_backtrace_into_string(buffer, backtrace_array, frame_count)
  char *buffer;
  void **backtrace_array;
  int frame_count;
{
  char *string = buffer;
  int i;
  if (g2ext_pc_at_c_gensym_signal_handler != 0) {
    sprintf(string,"PC at error: %s\n",
            g2ext_backtrace_frame_full_name(g2ext_pc_at_c_gensym_signal_handler));
    string += strlen(string);
  }
  if (0 < frame_count) {
    sprintf(string,"Internal backtrace:\n");
    string += strlen(string);
    for (i=0; i<frame_count; i++) {
      sprintf(string,"  %s\n", g2ext_backtrace_frame_full_name(backtrace_array[i]));
      string += strlen(string);
    }
  }
  print_recent_fn_trace_into_string(15,string);
  return strlen(buffer);
}

void g2ext_network_io_print_backtrace()
{
  long count,desired_count,i;
  void *buffer[NUMBER_OF_BACKTRACE_FRAMES+1];

  desired_count = NUMBER_OF_BACKTRACE_FRAMES;
#if defined(sun4) || defined(sparcsol)
  if (backtrace_caller) {
    void *sp = backtrace_stack_pointer;
    buffer[0] = backtrace_caller;
    buffer[1] = backtrace_second_caller;
    for(count=1; (count<desired_count) && (sp != 0);) {
      buffer[++count] = ((void **)sp)[15];
      sp = ((void **)sp)[14];
    }
  } else
#endif
    count = g2ext_save_backtrace_into_array(&buffer[0],desired_count,backtrace_frames_to_skip);
  if (count==0) return;
  if (!have_names) get_function_address_file();
  printf("Backtrace:\n");
  for (i=0; i<count; i++)
    printf("  %s\n", g2ext_backtrace_frame_full_name(buffer[i]));
  printf("\n");
}

static int include_second_backtrace_frame(count,frame_buffer)
    int count;
    void **frame_buffer;
{
#if defined(sun4) || defined(sparcsol)
/* TRUE if the top function is not in a shared library,
           and the top function's first instruction is not a save instruction */
  unsigned int op;
  int i;
  if (backtrace_caller == 0) return TRUE;
  i = g2ext_lookup_backtrace_frame_index(frame_buffer[0]);
  if (i<0) return TRUE;
  op = *(unsigned int *)function_address_table[i].address;
  return
    ((((unsigned int)(frame_buffer[0])) & 0xff000000) != 0xef000000) &&
    !(((op & 0xc0000000) == 0x80000000) &&
      ((op & 0x01f80000) == 0x01e00000));
#else
  return TRUE;
#endif
}

static void write_network_io_trace_backtrace(out,count,frame_buffer)
    FILE *out;
    int count;
    void **frame_buffer;
{
  char btf[100];
  int i,pos=0,len;
  unsigned long fn[NUMBER_OF_BACKTRACE_FRAMES];
  int include_second_p = include_second_backtrace_frame(count,frame_buffer);

  if (!have_names) get_function_address_file();
  if (!include_second_p) frame_buffer[1] = 0;
  for (i = 0; i < count; i++)
    if (i != 1 || include_second_p) {
      char *name = lookup_backtrace_frame(frame_buffer[i],btf,fn,i,include_second_p);
      len=strlen(name);
      if ((!g2ext_network_io_one_line_backtrace_p)&&
          (pos==0||(pos+1+len)>trace_output_width)) {
        fprintf(out,"\n");
        pos = 5; }
      fprintf(out," %s",name);
      pos += 1+len; }
  if ((!g2ext_network_io_one_line_backtrace_p)&&(pos > 0)) fprintf(out,"\n");
}

static void initialize_backtrace_summary()
{
  int i;
  if ((function_count_type *)0 != function_count_table) {
    free(function_count_table);
    function_count_table = 0;
  }
  if (function_address_table_size > 0) {
    function_count_table
      = (function_count_type *)malloc(function_address_table_size*sizeof(function_count_type));
    if (function_count_table == 0) return;
  }
  for(i=0; i<function_address_table_size; i++) function_count_table[i]=0;
  total_number_of_backtraces = 0;
}

static void summarize_single_backtrace(buffer)
  void **buffer;
{
  int i;
  unsigned long fn[NUMBER_OF_BACKTRACE_FRAMES];
  int count = ((unsigned long *)buffer)[0];
  int include_second_p = include_second_backtrace_frame(count,&buffer[1]);

  if (!include_second_p) buffer[2] = 0;
  total_number_of_backtraces++;
  for (i = 0; i < count; i++)
    if (i != 1 || include_second_p)
      lookup_backtrace_frame(buffer[i+1],(char *)0,fn,i,include_second_p);
}

static void heapify_backtrace_summary_array(i,s)
    int i,s;
{
  int l = (i<<1)+1; int r = l+1; int largest;
  largest = (( l <= s && g2ext_ci_array[l].cnt > g2ext_ci_array[i].cnt ) ? l : i);
  if ( r <= s && g2ext_ci_array[r].cnt > g2ext_ci_array[largest].cnt ) largest = r;
  if ( largest != i ) {
    function_count_type tcnt = g2ext_ci_array[i].cnt;
    unsigned short tidx = g2ext_ci_array[i].idx;
    g2ext_ci_array[i].cnt = g2ext_ci_array[largest].cnt; g2ext_ci_array[largest].cnt = tcnt;
    g2ext_ci_array[i].idx = g2ext_ci_array[largest].idx; g2ext_ci_array[largest].idx = tidx;
    heapify_backtrace_summary_array(largest,s); }
}

static void write_backtrace_summary(out)
   FILE *out;
{
  int i,j,count=0;
  for(i=0; i<function_address_table_size; i++)
    if(function_count_table[i]>0)count += 1;
  if(count>0) {
    g2ext_ci_array = (struct ci_struct *)malloc(count*sizeof(struct ci_struct));
    if (g2ext_ci_array == 0) return;
    for(i=0,j=0; i<function_address_table_size; i++)
      if(function_count_table[i]>0) {
        g2ext_ci_array[j].cnt = function_count_table[i];
        g2ext_ci_array[j].idx = i;
        j++; }
    for(i=(count>>1)-1; i>=0; i--) heapify_backtrace_summary_array(i,count-1);
    fprintf(out,"\nFunction backtrace counts");
    fprintf(out,"\n %5d %s", (int) total_number_of_backtraces, "(total)");
    for(i=count-1; i>=1; i--) {
      char *fname = function_address_table[g2ext_ci_array[0].idx].name;
      fprintf(out,"\n %5d %s",g2ext_ci_array[0].cnt,(fname==0)?"(none)":fname);
      g2ext_ci_array[0].cnt = g2ext_ci_array[i].cnt;
      g2ext_ci_array[0].idx = g2ext_ci_array[i].idx;
      heapify_backtrace_summary_array(0,i-1); }}
}

static void write_network_io_backtrace_summary()
{
  FILE *out = trace_output;
  trace_entry *entry = first_trace_entry;
  if (0 == out) return;
  if (!backtrace_summary_only_p) {
    initialize_backtrace_summary();
    while (entry != (trace_entry *)0) {
      if ((entry->te_type != TRACE_BACKTRACE &&
           entry->te_type != TRACE_BACKTRACE_CONS &&
           entry->te_type != TRACE_BACKTRACE_RECLAIM ) ||
          !((trace_backtrace *)entry)->cons) {
        switch (entry->te_type) {
        case TRACE_BACKTRACE:
        case TRACE_BACKTRACE_CONS:
        case TRACE_BACKTRACE_RECLAIM: {
          summarize_single_backtrace(TRACE_BACKTRACE_BUFFER(entry));
          break;}}}
      entry = entry->te_next;}}
  if (0 < function_address_table_size) write_backtrace_summary(out);
  fprintf(out,"\n");
}

void g2ext_network_io_trace_note(note_string)
    char *note_string;
{
  long size;
  trace_note *note;

  if (!g2ext_network_io_trace_p || in_network_io_trace ||
      trace_consing_p || trace_reclaiming_p) return;
  in_network_io_trace = TRUE;
  size = sizeof(trace_note)+strlen(note_string)+1;
  note = (trace_note *)make_trace_entry(TRACE_NOTE,size);
  if (note == 0) return;
  strcpy(TRACE_NOTE_STRING(note),note_string);
  in_network_io_trace = FALSE;
  if (network_io_trace_backtrace_request) g2ext_network_io_trace_backtrace();
}

void g2ext_network_io_trace_note_d(note_string,arg)
    char *note_string;
    long arg;
{
  char buffer[128];

  if (!g2ext_network_io_trace_p || in_network_io_trace ||
      trace_consing_p || trace_reclaiming_p) return;
  sprintf(buffer,note_string,arg);
  g2ext_network_io_trace_note(buffer);
}

void g2ext_network_io_trace_note_dd(note_string,arg1,arg2)
    char *note_string;
    long arg1,arg2;
{
  char buffer[128];

  if (!g2ext_network_io_trace_p || in_network_io_trace ||
      trace_consing_p || trace_reclaiming_p) return;
  sprintf(buffer,note_string,arg1,arg2);
  g2ext_network_io_trace_note(buffer);
}

void g2ext_network_io_trace_note_ddd(note_string,arg1,arg2,arg3)
    char *note_string;
    long arg1,arg2,arg3;
{
  char buffer[128];

  if (!g2ext_network_io_trace_p || in_network_io_trace ||
      trace_consing_p || trace_reclaiming_p) return;
  sprintf(buffer,note_string,arg1,arg2,arg3);
  g2ext_network_io_trace_note(buffer);
}

void g2ext_network_io_trace_note_f(note_string,arg)
    char *note_string;
    double arg;
{
  char buffer[128];

  if (!g2ext_network_io_trace_p || in_network_io_trace ||
      trace_consing_p || trace_reclaiming_p) return;
  sprintf(buffer,note_string,arg);
  g2ext_network_io_trace_note(buffer);
}

void g2ext_network_io_trace_note_s(note_string,arg)
    char *note_string;
    char *arg;
{
  char buffer[128];

  if (!g2ext_network_io_trace_p || in_network_io_trace ||
      trace_consing_p || trace_reclaiming_p) return;
  sprintf(buffer,note_string,arg);
  g2ext_network_io_trace_note(buffer);
}

#ifdef G2_51
void g2ext_note_network_event(ecode,socket_handle)
    long ecode, socket_handle;
{
  char *event_name;
  NETWORK_INTERFACE *ni;
  int fd;

  if (!g2ext_network_io_trace_p || in_network_io_trace ||
      trace_consing_p || trace_reclaiming_p) return;
  if (ecode==scheduler_event) {
    g2ext_network_io_trace_note("Scheduler Event");
    return;
  } else if (ecode==display_event) {
    g2ext_network_io_trace_note("Display Event");
    return;
  } else if (ecode==error_event) {
    g2ext_network_io_trace_note("Error Event");
    return;
  }
  ni = (NETWORK_INTERFACE *) g2ext_map_g2pointer_to_cpointer(socket_handle);
  fd = (0==ni) ? -1 : ni->handle;
  if (ecode==read_event) event_name = "Read Event  Handle: %d, fd: %d";
  else if (ecode==read_and_block_event) event_name = "Read and Block Event  Handle: %d, fd: %d";
  else if (ecode==write_event) event_name = "Write Event  Handle: %d, fd: %d";
  else if (ecode==connect_event) event_name = "Connect Event  Handle: %d, fd: %d";
  else if (ecode==accept_event) event_name = "Accept Event  Handle: %d, fd: %d";
  else if (ecode==close_event) event_name = "Close Event  Handle: %d, fd: %d";
/*   else if (ecode==tw_req_event) event_name = "Connection Request Event  Handle: %d, fd: %d"; */
  else {
    g2ext_network_io_trace_note("Unknown Event");
    return;
  }
  g2ext_network_io_trace_note_dd(event_name, socket_handle, fd);
}
#endif

static backtrace_list *get_interned_backtrace()
{
  long count,desired_count,buffer_size;
  void *buffer[NUMBER_OF_BACKTRACE_FRAMES+1];
  backtrace_list *btl,*btl_prev;
  unsigned long hash = 0;
  int i;

  desired_count = (backtrace_cons?CONS_BACKTRACE_SIZE:
                   (backtrace_summary_only_p?NUMBER_OF_BACKTRACE_FRAMES:
                    NUMBER_OF_BACKTRACE_FRAMES_SHORT));
#if defined(sun4) || defined(sparcsol)
  if (backtrace_caller) {
    void *sp = backtrace_stack_pointer;
    buffer[1] = backtrace_caller;
    buffer[2] = backtrace_second_caller;
    for(count=2; count<desired_count && sp != 0;) {
      buffer[++count] = ((void **)sp)[15];
      sp = ((void **)sp)[14];
    }
  } else
    count = g2ext_save_backtrace_into_array(&buffer[1],desired_count,backtrace_frames_to_skip);
#else
  count = g2ext_save_backtrace_into_array(&buffer[1],desired_count,backtrace_frames_to_skip);
#endif
  if (backtrace_cons && count > CONS_BACKTRACE_SIZE)
    count = CONS_BACKTRACE_SIZE;
  ((unsigned long *)buffer)[0] = count;
  if (backtrace_summary_only_p) {
    summarize_single_backtrace(buffer);
    return 0;
  }
  for (i=1; i<=count; i++) hash ^= (unsigned long)(buffer[i]);
  hash = (hash >> 3) & BACKTRACE_HASH_MASK;
  if (!backtrace_hash_table) backtrace_hash_table = calloc(BACKTRACE_HASH_SIZE,sizeof(backtrace_list *));
  if (!backtrace_hash_table) return 0;
  for (btl = backtrace_hash_table[hash], btl_prev=0; btl!=0; btl_prev = btl, btl = btl->next) {
      for (i=0; i<=count; i++)
          if (btl->backtrace[i] != buffer[i])
              goto difference_found;
      break;
  difference_found:;
  }
  if (!btl) {
      btl = (backtrace_list *)malloc(sizeof(backtrace_list));
      if (!btl) return 0;
      buffer_size = (1+count)*sizeof(void *);
      btl->backtrace = (void **)malloc(buffer_size);
      memcpy(btl->backtrace, buffer, buffer_size);
      btl->next = backtrace_hash_table[hash];
      backtrace_hash_table[hash] = btl;
  } else if (btl_prev) {
      btl_prev->next = btl->next;
      btl->next = backtrace_hash_table[hash];
      backtrace_hash_table[hash] = btl;
  }
  btl->sequence_number_of_most_recent_use = backtrace_sequence_number++;
  btl->timestamp_of_most_recent_use = last_network_io_time;
  return btl;
}

void g2ext_network_io_trace_backtrace()
{
  trace_backtrace *bt;
  long type;

  if (!network_io_backtrace_p) return;
  if (in_network_io_trace) {network_io_trace_backtrace_request = TRUE; return;}
  in_network_io_trace = TRUE;
  if (backtrace_cons)
    type = backtrace_cons_reclaim ? TRACE_BACKTRACE_RECLAIM : TRACE_BACKTRACE_CONS;
  else
    type = TRACE_BACKTRACE;
  if (backtrace_summary_only_p) {
    get_interned_backtrace();
    return;
  }
  bt = (trace_backtrace *)make_trace_entry(type,sizeof(trace_backtrace));
  if (bt == 0) return;
  bt->cons=backtrace_cons;
  bt->backtrace=get_interned_backtrace();
  if (backtrace_cons) {
    unsigned long hash;
    trace_backtrace *prev_bt;
    if (cons_backtrace_table == 0)
      cons_backtrace_table =
        (struct trace_backtrace **)calloc(4096, sizeof(struct trace_backtrace *));
    hash = 4095 & (((unsigned long)backtrace_cons) >> 3);
    prev_bt = cons_backtrace_table[hash];
    bt->previous_cons_backtrace = prev_bt;
    cons_backtrace_table[hash] = bt;
    if (!g2ext_network_io_find_leaks) {
      for (;prev_bt && prev_bt->cons != backtrace_cons; prev_bt = prev_bt->previous_cons_backtrace);
      if (prev_bt && bt->entry.te_type == prev_bt->entry.te_type) {
          trace_backtrace *tbt;
          for (tbt=bt; tbt; tbt=tbt->previous_cons_backtrace)
              if (tbt->cons == backtrace_cons)
                  write_cons_summary_internal_2(stdout,tbt);
          printf("\nall backtraces\n");
          g2ext_print_all_backtraces();
          trace_consing_p = FALSE;
          trace_reclaiming_p = FALSE;
      }
    }
  } else
    bt->previous_cons_backtrace = 0;
  in_network_io_trace = FALSE;
  network_io_trace_backtrace_request = FALSE;
}

/*
static int compare_return_addresses(b1i,b2i)
    void *b1i, *b2i;
{
  long idx1 = g2ext_lookup_backtrace_frame_index(b1i);
  char *n1 = g2ext_backtrace_frame_name(idx1);
  long idx2 = g2ext_lookup_backtrace_frame_index(b2i);
  char *n2 = g2ext_backtrace_frame_name(idx2);
  int res = ((n1 && n2) ? strcmp(n1,n2) :
             (n1 ? -1 : (n2 ? 1 : 0)));
  if (res == 0)
    res = (((unsigned long)b1i < (unsigned long)b2i) ? -1 :
           (((unsigned long)b1i > (unsigned long)b2i) ? 1 : 0));
  return res;
}
*/

static int compare_backtraces(b1,b2 /*,i1,i2,index */)
     backtrace_list *b1,*b2;
/*      int i1,i2; */
/*      int *index; */
{
    /*
    int count1 = (int)(b1->backtrace[0]);
    int count2 = (int)(b2->backtrace[0]);
    int i, res;
    for (i=1; i<=count1 && i<=count2; i++) {
      res = compare_return_addresses(b1->backtrace[i],b2->backtrace[i]);
      if (res != 0) return res;
    }
    if (count1 < count2) return -1;
    if (count1 > count2) return 1;
    return 0;
    */
    unsigned long seq1 = b1->sequence_number_of_most_recent_use;
    unsigned long seq2 = b2->sequence_number_of_most_recent_use;
    if (seq1 < seq2) return -1;
    if (seq1 > seq2) return 1;
    return 0;
}

static void heapify_backtrace_array(i,s,backtraces,index)
    int i,s;
    backtrace_list **backtraces;
    int *index;
{
  int l = (i<<1)+1;
  int r = l+1;
  int largest = (( l <= s &&
                   (0 < compare_backtraces(backtraces[index[l]],backtraces[index[i]])))
                  ? l : i);
  if ( r <= s &&
       (0 < compare_backtraces(backtraces[index[r]],backtraces[index[largest]])) )
      largest = r;
  if ( largest != i ) {
    int saved_index = index[i];
    index[i] = index[largest];
    index[largest] = saved_index;
    heapify_backtrace_array(largest,s,backtraces,index);
  }
}

static void sort_backtrace_array(size,backtraces,index)
    int size;
    backtrace_list **backtraces;
    int *index;
{
  int i;
  for(i=0; i<size; i++) index[i] = i;
  for(i=(size>>1)-1; i>=0; i--) {
    heapify_backtrace_array(i,size-1,backtraces,index);
  }
  for(i=size-1; i>=1; i--) {
    int largest_index;
    largest_index = index[0];
    index[0] = index[i];
    index[i] = largest_index;
    heapify_backtrace_array(0,i-1,backtraces,index);
  }
}

void g2ext_print_all_backtraces()
{
    int i, count = 0;
    unsigned long j;
    backtrace_list *btl;
    backtrace_list **backtraces;
    void **backtrace;
    int *sorted_indices;
    for (i=0; i<BACKTRACE_HASH_SIZE; i++)
        for (btl=backtrace_hash_table[i]; btl; btl=btl->next)
            count++;
    backtraces=(backtrace_list**)malloc(count*sizeof(backtrace_list*));
    sorted_indices=(int*)malloc(count*sizeof(int));
    j=0;
    for (i=0; i<BACKTRACE_HASH_SIZE; i++)
        for (btl=backtrace_hash_table[i]; btl; btl=btl->next)
            backtraces[j++]=btl;
    sort_backtrace_array(count, backtraces, sorted_indices);
    for (i=0; i<count; i++) {
        btl = backtraces[sorted_indices[i]];
        backtrace = btl->backtrace;
        printf("%8d %10d  ",
               (int) btl->sequence_number_of_most_recent_use,
               (int) btl->timestamp_of_most_recent_use);
        for (j = 1; j <= (unsigned long)backtrace[0]; j++) {
          char *name = g2ext_backtrace_frame_full_name(backtrace[j]);
          printf(" %s",name);
        }
        printf("\n");
    }
    free(sorted_indices);
    free(backtraces);
    fflush(stdout);
}

void g2ext_note_allocate_cons(void *cons, void *name)
{
#ifdef USE_BITMAP_FOR_CONS_TRACING
  int cons_offset;
  int index;
  unsigned int current;
  unsigned int bit_in_current;
  if (!trace_consing_p) return;
  xxx_last_cons = cons;
  xxx_last_type = 1;
  /* 3 is 8 byte aligned (double floats only) address to bit index */
  cons_offset = ((int)cons - (int)g2ext_cons_checking_region_start) >> 2;
  index = cons_offset >> 5; /* bit index to int array index */
  if (index<0 || index>CONS_CHECKING_BITMAP_SIZE) return;
  current = consing_bitmap[index];
  bit_in_current = 1 << (cons_offset & 0x1f);
  /* if (cons == watched_cons) note_watched_cons(cons,name,0); */
  if ((current & bit_in_current) != 0) {
    printf("*** already in use\n");
    g2ext_print_backtrace();
    fflush(stdout);
    g2ext_print_all_backtraces();
    trace_consing_p = FALSE;
  }
  consing_bitmap[index] = current | bit_in_current;
  {
    int old_backtrace_frames_to_skip = backtrace_frames_to_skip;
    backtrace_frames_to_skip = 2;
    last_network_io_time = g2ext_g2_clock_ticks((1L << 30L) - 1L);
    get_interned_backtrace();
    backtrace_frames_to_skip = old_backtrace_frames_to_skip;
  }
#else
  trace_backtrace *bt,*bt_last;
  intptr_t hash;
  int count, limit;

  if (!trace_consing_p) return;
  xxx_last_cons = cons;
  xxx_last_type = 1;
  if (!g2ext_network_io_find_leaks && g2ext_kept_cons_backtrace_limit>0) {
    if (cons_backtrace_table == 0)
      cons_backtrace_table =
        (struct trace_backtrace **)calloc(4096, sizeof(struct trace_backtrace *));
    hash = 4095 & (((intptr_t)cons) >> 3);
    limit = g2ext_kept_cons_backtrace_limit;
    for(bt_last=0,  bt=cons_backtrace_table[hash], count=0;
        bt;
        bt_last=bt, bt=bt->previous_cons_backtrace) {
      if (bt->cons==cons)
        if (limit < ++count) {
          bt->cons=0;
          if (bt_last) {
            bt_last->previous_cons_backtrace=bt->previous_cons_backtrace;
          } else
            cons_backtrace_table[hash]=bt->previous_cons_backtrace;
          bt->previous_cons_backtrace = last_free_cons_backtrace;
          last_free_cons_backtrace = bt;
          break;
        }
    }
  }
  {
    int old_trace_backtrace_p = network_io_backtrace_p;
    int old_backtrace_frames_to_skip = backtrace_frames_to_skip;
    backtrace_cons = cons;
    network_io_backtrace_p = TRUE;
    backtrace_frames_to_skip = 2;
    g2ext_network_io_trace_backtrace();
    backtrace_cons = 0;
    network_io_backtrace_p = old_trace_backtrace_p;
    backtrace_frames_to_skip = old_backtrace_frames_to_skip;
  }
#endif
}

/* I believe name is a pool name. See note-reclaim-cons in utilities0.lisp */
void g2ext_note_reclaim_cons(void *cons, void * name)
{
#ifdef USE_BITMAP_FOR_CONS_TRACING
  int cons_offset;
  int index;
  unsigned int current;
  unsigned int bit_in_current;
  if (!trace_consing_p) return;
  xxx_last_cons = cons;
  xxx_last_type = 0;
  /* 3 is 8 byte aligned (double floats only) address to bit index */
  cons_offset = ((int)cons - (int)g2ext_cons_checking_region_start) >> 2;
  index = cons_offset >> 5; /* bit index to int array index */
  if (index<0 || index>CONS_CHECKING_BITMAP_SIZE) return;
  current = consing_bitmap[index];
  bit_in_current = 1 << (cons_offset & 0x1f);
  /* if (cons == watched_cons) note_watched_cons(cons,name,1); */
  if ((current & bit_in_current) == 0) {
    printf("*** already free\n");
    g2ext_print_backtrace();
    fflush(stdout);
    g2ext_print_all_backtraces();
    trace_consing_p = FALSE;
  }
  consing_bitmap[index] = current & ~bit_in_current;
  {
    int old_backtrace_frames_to_skip = backtrace_frames_to_skip;
    backtrace_frames_to_skip = 2;
    last_network_io_time = g2ext_g2_clock_ticks((1L << 30L) - 1L);
    get_interned_backtrace();
    backtrace_frames_to_skip = old_backtrace_frames_to_skip;
  }
#else
  trace_backtrace *bt,*bt_last;
  intptr_t hash;
  int count, limit;

  if (!trace_reclaiming_p) return;
  xxx_last_cons = cons;
  xxx_last_type = 0;
  if (g2ext_network_io_find_leaks || g2ext_kept_cons_backtrace_limit>0) {
    if (cons_backtrace_table == 0)
      cons_backtrace_table =
        (struct trace_backtrace **)calloc(4096, sizeof(struct trace_backtrace *));
    hash = 4095 & (((intptr_t)cons) >> 3);
    limit = g2ext_network_io_find_leaks ? 0 : g2ext_kept_cons_backtrace_limit;
    for(bt_last=0,  bt=cons_backtrace_table[hash], count=0;
        bt;
        bt_last=bt, bt=bt->previous_cons_backtrace) {
      if (bt->cons==cons)
        if (limit < ++count) {
          bt->cons=0;
          if (bt_last) {
            bt_last->previous_cons_backtrace=bt->previous_cons_backtrace;
          } else
            cons_backtrace_table[hash]=bt->previous_cons_backtrace;
          bt->previous_cons_backtrace = last_free_cons_backtrace;
          last_free_cons_backtrace = bt;
          break;
        }
    }
  }
  if (!g2ext_network_io_find_leaks) {
    int old_trace_backtrace_p = network_io_backtrace_p;
    int old_backtrace_frames_to_skip = backtrace_frames_to_skip;
    backtrace_cons = cons;
    backtrace_cons_reclaim = TRUE;
    network_io_backtrace_p = TRUE;
    backtrace_frames_to_skip = 2;
    g2ext_network_io_trace_backtrace();
    backtrace_cons = 0;
    backtrace_cons_reclaim = FALSE;
    network_io_backtrace_p = old_trace_backtrace_p;
    backtrace_frames_to_skip = old_backtrace_frames_to_skip;
  }
#endif
}

void g2ext_reset_network_io_trace()
{
  trace_block *block = first_trace_block;
  current_trace_block = block;
  while (block != (trace_block *)0) {
    block->tb_free = TRACE_ENTRY_ALIGN((char *)block + sizeof(trace_block));
    block = block->tb_next;
  }
  first_trace_entry = (trace_entry *)0;
  last_trace_entry = (trace_entry *)0;
  if (cons_backtrace_table) {
    free(cons_backtrace_table);
    cons_backtrace_table = 0;
  }
  last_cons_backtrace = 0;
  last_free_cons_backtrace = 0;
}

void g2ext_save_network_io_trace(file)
   char *file;
{
  /* save trace in binary format */
}

static void write_network_io_trace_internal()
{
  int size,i;
  FILE *out = trace_output;
  trace_entry *entry = first_trace_entry;
  if (0 == out) return;
  fprintf(out,"Begin Network Input/Output Trace\n");
  if ((function_count_type *)0 != function_count_table) {
    free(function_count_table);
    function_count_table = 0;
  }
  if (function_address_table_size > 0) {
    function_count_table
      = (function_count_type *)malloc(function_address_table_size*sizeof(function_count_type));
    if (function_count_table == 0) return;
  }
  for(i=0; i<function_address_table_size; i++) function_count_table[i]=0;
  while (entry != (trace_entry *)0) {
    if ((entry->te_type != TRACE_BACKTRACE &&
         entry->te_type != TRACE_BACKTRACE_CONS &&
         entry->te_type != TRACE_BACKTRACE_RECLAIM ) ||
        !((trace_backtrace *)entry)->cons) {
      fprintf(out,"\n%9d %18s  Time: %4d",
              (int) entry->te_sequence_number,
              trace_io_type_names[entry->te_type],
              (int)entry->te_dtime);
#ifdef WIN32
      fprintf(out," [%8d  %5d]",
              entry->te_atime,entry->te_mtime);
#else
      fprintf(out," [%8d]",
              (int) entry->te_atime);
#endif
      switch (entry->te_type) {
      case TRACE_ENTRY:       break;
      case TRACE_NOTE:        fprintf(out,"  %s",TRACE_NOTE_STRING(entry)); break;
      case TRACE_READ_BEGIN:
      case TRACE_WRITE_BEGIN: fprintf(out,"  Handle: %d, fd: %d, Length: %d",
                                      (int) ((trace_io_begin *)entry)->handle,
                                      (int) ((trace_io_begin *)entry)->fd,
                                      (int) ((trace_io_begin *)entry)->length);
      break;
      case TRACE_READ_END:
      case TRACE_WRITE_END:   fprintf(out,"  Handle: %d, fd: %d, Result: %d",
                                      (int) ((trace_io_end *)entry)->handle,
                                      (int) ((trace_io_end *)entry)->fd,
                                      (int) ((trace_io_end *)entry)->io_result);
      if (write_network_data && (0 < (size = ((trace_io_end *)entry)->buffer_size)) )
        write_network_io_trace_buffer(out,size,TRACE_BUFFER(entry));
      break;
      case TRACE_BACKTRACE:
      case TRACE_BACKTRACE_CONS:
      case TRACE_BACKTRACE_RECLAIM: {
        void **buffer = TRACE_BACKTRACE_BUFFER(entry);
        write_network_io_trace_backtrace(out,((unsigned long *)buffer)[0],&buffer[1]);
        break;
      }
      }
    }
    entry = entry->te_next;
  }
  fprintf(out,"\n\nEnd Network Input/Output Trace\n");
}

void g2ext_write_network_io_trace(file)
   char *file;
{
  FILE *out = trace_output;
  trace_output = GFOPEN(file,"w");
  if (trace_output) {
    write_network_io_trace_internal();
    GFCLOSE(trace_output);
  }
  trace_output = out;
}

static void write_cons_summary_internal_2(out,entry)
  FILE *out;
  trace_entry *entry;
{
  trace_backtrace *bt;
  void **buffer;

  switch (entry->te_type) {
    case TRACE_BACKTRACE_CONS:
    case TRACE_BACKTRACE_RECLAIM:
      bt = (trace_backtrace *)entry;
      if (bt->cons == 0 ||
          (trace_write_single_cons != 0 &&
           trace_write_single_cons != bt->cons))
        return;
      buffer = TRACE_BACKTRACE_BUFFER(entry);
      fprintf(out,"\n");
      if (g2ext_network_io_one_line_backtrace_p && !g2ext_network_io_find_leaks)
        fprintf(out," %x  %9d  ",
                (unsigned int) ((trace_backtrace *)entry)->cons,
                (int) entry->te_sequence_number);
      if (g2ext_network_io_one_line_backtrace_p)
        write_network_io_trace_backtrace(out,((unsigned long *)buffer)[0],&buffer[1]);
      if (g2ext_network_io_find_leaks) {
        fprintf(out,"  %9d", (int) entry->te_sequence_number);
        if (print_cons_addresses_p)
          fprintf(out,"  %x",
                  (unsigned int) ((trace_backtrace *)entry)->cons);
      } else if (g2ext_network_io_one_line_backtrace_p) {
        fprintf(out,"  %s",
                (entry->te_type==TRACE_BACKTRACE_CONS)?"allocate":"reclaim ");
      } else
        fprintf(out,"  %9d  %x  %s",
                (int)entry->te_sequence_number,
                (unsigned int) ((trace_backtrace *)entry)->cons,
                (entry->te_type==TRACE_BACKTRACE_CONS)?"allocate":"reclaim ");
    }
}

static void write_cons_summary_internal()
{
  FILE *out = trace_output;
  trace_entry *entry;

  if (0 == out) return;
  if (!have_names) get_function_address_file();
  for(entry=first_trace_entry; entry; entry=entry->te_next)
    write_cons_summary_internal_2(out,entry);
  fprintf(out,"\n");
}

void g2ext_write_cons_summary(file)
   char *file;
{
  FILE *out = trace_output;
  trace_output = GFOPEN(file,"w");
  if (trace_output) {
    write_cons_summary_internal();
    GFCLOSE(trace_output);
  }
  trace_output = out;
}

void g2ext_enable_network_io_trace()
{
  char *current_time = g2ext_current_time_no_newline();

  g2ext_network_io_trace_p = TRUE;
  trace_network_io_data_p = TRUE;
  g2ext_network_io_trace_note_s("Enabling network io tracing at %s",current_time);
}

void g2ext_enable_consing_trace()
{
  trace_consing_p = TRUE;
  trace_reclaiming_p = TRUE;
}

void g2ext_disable_consing_trace()
{
  trace_consing_p = FALSE;
}

#if defined(sun4)

void g2ext_gensym_SIGVTALRM_handler(signal_number,signal_code,scp,addr)
    int signal_number, signal_code;
    struct sigcontext *scp;
    char *addr;
{
  backtrace_caller = (void *)(scp->sc_pc);
  backtrace_stack_pointer = (void *)(scp->sc_sp);
  g2ext_network_io_trace_backtrace();
}

#else

#  if defined(sparcsol)
#  include "ucontext.h"

void g2ext_gensym_SIGVTALRM_handler(signal_code, sip, uap)
   int signal_code;
   siginfo_t *sip;
   ucontext_t *uap;
{
  backtrace_caller = (void *)(uap->uc_mcontext.gregs[REG_PC]);
  backtrace_stack_pointer = (void *)(uap->uc_mcontext.gregs[REG_O6]); /* REG_SP */
  backtrace_second_caller = (void *)(uap->uc_mcontext.gregs[REG_O7]);
  g2ext_network_io_trace_backtrace();
}

#  else

void g2ext_gensym_SIGVTALRM_handler(signal_number)
    int signal_number;
{g2ext_network_io_trace_backtrace();}

#endif
#endif

void g2ext_enable_network_io_backtrace()
{
#if defined(POSIX) && defined(unix)
  struct itimerval internal_timer;
  struct sigaction siga, old_siga;
  long seconds;
  network_io_backtrace_p = TRUE;
  g2ext_network_io_backtrace_used_p = TRUE;
  if (backtrace_summary_only_p) {
    if (!have_names) get_function_address_file();
    initialize_backtrace_summary();}
  sigemptyset(&siga.sa_mask);
  siga.sa_flags = 0;
#  ifdef SA_RESTART
  siga.sa_flags |= SA_RESTART;
#  endif
#  if defined(sparcsol) /* provides platform-specific extra args to the signal handler */
  siga.sa_sigaction = g2ext_gensym_SIGVTALRM_handler;
  siga.sa_flags |= SA_SIGINFO;
#  else
  siga.sa_handler = g2ext_gensym_SIGVTALRM_handler;
#  endif
  sigaction(g2ext_use_virtual_alarm_p?SIGVTALRM:SIGPROF, &siga, &old_siga);
  internal_timer.it_value.tv_sec = internal_timer.it_interval.tv_sec =
    seconds = g2ext_network_io_backtrace_interval / 1000;
  internal_timer.it_value.tv_usec = internal_timer.it_interval.tv_usec =
    1000 * (g2ext_network_io_backtrace_interval - seconds * 1000);
  setitimer(g2ext_use_virtual_alarm_p?ITIMER_VIRTUAL:ITIMER_PROF, &internal_timer, NULL);
#endif
}

void g2ext_disable_network_io_trace()
{
  g2ext_network_io_trace_p = FALSE;
  network_io_backtrace_p = FALSE;
#if defined(unix)
  {struct itimerval internal_timer;
  internal_timer.it_value.tv_sec = 0;
  internal_timer.it_value.tv_usec = 0;
  internal_timer.it_interval.tv_sec = 0;
  internal_timer.it_interval.tv_usec = 0;
  setitimer(g2ext_use_virtual_alarm_p?ITIMER_VIRTUAL:ITIMER_PROF, &internal_timer, NULL);}
#endif
  trace_consing_p = FALSE;
  trace_reclaiming_p = FALSE;
}

int g2ext_network_io_trace_enabled_p()
{
  return g2ext_network_io_trace_p;
}

static void make_backtrace_report(trace_output_file,report_output_file)
  char *trace_output_file;
  char *report_output_file;
{
  char buffer[250];
  sprintf(buffer, "make-backtrace-report %s %s %s %s",
          tmp_backtrace_root_file, tmp_backtrace_target_file,
          trace_output_file, report_output_file);
  g2ext_run_command_line(buffer);
}

static void copy_file_to_trace_output(file)
    char *file;
{
  if (trace_output) {
    FILE *copy_in = GFOPEN(file,"r");
    int ch;
    if (copy_in) {
      while (EOF != (ch = getc(copy_in))) {
        putc(ch,trace_output);
      }
      GFCLOSE(copy_in);
    }
  }
}

static void maybe_get_next_trace_input_file(open_p)
    int open_p;
{
  if (trace_control_file == 0) return;
  if (open_p) {
    if (trace_control != 0) return;
    trace_control = GFOPEN(trace_control_file,"r");
    if (trace_control == 0) return;
#ifdef POSIX
    if (automatic_trace_control_file)
      if (-1 == unlink(trace_control_file)) {
        GFCLOSE(trace_control);
        trace_control = 0;
        return;
      }
#endif
    trace_control_file_index++;
    trace_control_line_number = 1;
  }
  if (!automatic_trace_control_file) {
    free(trace_control_file);
    trace_control_file = 0;
  }
}

static void process_trace_control_commands()
{
  do {
    while (process_trace_control_command())
      trace_control_line_number++;
  } while (0 < --processing_trace_control_commands);
}

static void c_gensym_SIGUSR1_handler(signal_code)
  int     signal_code;
{
  processing_trace_control_commands++;
  if (1 == processing_trace_control_commands)
    process_trace_control_commands();
}

void g2ext_start_trace_control_handler(argv0)
   char *argv0;
{
  char *tcf = getenv("G2_TRACE_CONTROL_FILE");
#ifdef POSIX
  {
    struct sigaction siga, old_siga;
    long pid = getpid();
    char tcf_name[100];
    if (tcf == 0) {
      sprintf(tcf_name,"g2_trace_control_for_%d", (int) pid);
      tcf = tcf_name;
      automatic_trace_control_file = TRUE;
    }
    sigemptyset(&siga.sa_mask);
    siga.sa_flags = 0;
#  ifdef SA_RESTART
    siga.sa_flags |= SA_RESTART;
#  endif
    siga.sa_handler = c_gensym_SIGUSR1_handler;
    sigaction(SIGUSR1, &siga, &old_siga);

  }
#endif
  if (tcf != 0) {
    trace_control_file = malloc(strlen(tcf)+1);
    if (trace_control_file == 0) return;
    strcpy(trace_control_file,tcf);
  }
  executable_file = argv0;
  processing_trace_control_commands++;
  process_trace_control_commands();
}

void g2ext_finish_trace_control_handler()
{
  processing_trace_control_commands++;
  process_trace_control_commands();
}

long g2ext_run_trace(string,length,widep)
  char *string;
  int length, widep;
{
  reading_trace_control_string = TRUE;
  trace_control_string = string;
  trace_control_string_length = length;
  trace_control_string_wide_p = widep;
  processing_trace_control_commands++;
  process_trace_control_commands();
  reading_trace_control_string = FALSE;
  return TRUE;
}

static void echo(string)
  char *string;
{
  if (trace_control_verbose)
    g2ext_write_string_to_console(string);
}

static void echof1(string,arg)
  char *string;
  char *arg;
{
  if (trace_control_verbose) {
    char message[100];
    sprintf(message,string,arg);
    g2ext_write_string_to_console(message);
  }
}

static void trace_control_error(char *message,int close_input)
{
  if (message && trace_output) {
    char buffer[250];
    sprintf(buffer,"Error on line %d: %s\n",
            trace_control_line_number,message);
    echo(buffer);
    fprintf(trace_output,"%s",buffer);
    fflush(trace_output);
  }
  if (close_input) {
    trace_control_next_char = 0;
    if (reading_trace_control_string)
      trace_control_string = 0;
    else {
      GFCLOSE(trace_control);
      trace_control = 0;
      maybe_get_next_trace_input_file(message == 0);
    }
  }
}

long g2ext_get_trace_function_name(buffer)
  char *buffer;
{
  if (trace_function_name == 0) return -1;
  strcpy(buffer, trace_function_name);
  return strlen(trace_function_name);
}

static void call_trace_function(name)
   char *name;
{
  trace_function_name = name;
  if (0 == g2int_run_trace_function()) {
    char msg[200];
    sprintf(msg,"The trace function %s was not found.",name);
    trace_control_error(msg,FALSE);
  }
  trace_function_name = 0;
}

static int trace_control_getc()
{
  int ch = EOF;
  if (trace_control_next_char) {
    ch = trace_control_next_char;
    trace_control_next_char = 0;
    return ch;
  }
  if (reading_trace_control_string) {
    ch = ((trace_control_string && 0<trace_control_string_length--) ?
          (trace_control_string_wide_p ?
           *(*(short **)&trace_control_string)++ :
           *trace_control_string++)
          : 0);
    if (ch == 0) {
      trace_control_string = 0;
      ch = EOF;
    } else if (ch == 8232)
      ch = '\n';
  } else
    while (trace_control && (EOF == (ch = getc(trace_control))))
      trace_control_error(0,TRUE);
  if (ch == EOF && trace_control_last_char != '\n') {
    trace_control_next_char = EOF;
    ch = '\n';
  }
  trace_control_last_char = ch;
  return ch;
}

static int trace_control_skip_whitespace(skip_to_end_of_line)
    int skip_to_end_of_line;
{
  int ch;
  do {ch = trace_control_getc();}
  while (ch == ' ' || ch == '\t' || ch == '\r');
  if (ch != '#' && ch != '\n' && skip_to_end_of_line) {
    char message[80],str[2];
    str[0]=ch; str[1]=0;
    sprintf(message,"unexpected input found at end of line: '%s'",str);
    trace_control_error(message,FALSE);
  }
  if (ch == '#')
    skip_to_end_of_line = TRUE;
  if (skip_to_end_of_line)
    while (ch != '\n' && ch != EOF) {
      ch = trace_control_getc();
    }
  return ch;
}

static int get_trace_control_token(buffer,size,quote_allowed,last_on_line)
    char *buffer;
    int size,quote_allowed,last_on_line;
{
  int ch, i=0, first=TRUE, quote=FALSE, quote_one=FALSE;
  ch = trace_control_skip_whitespace(FALSE);
  if (ch == '\n') {
    buffer[0]=0;
    return 1;
  } else if (ch == EOF) {
    return -1;
  }
  do {
    if (first) {
      if (ch == '"') {
        quote = TRUE;
        ch = trace_control_getc();
      }
    } else if (quote && !quote_one && (ch == '"'))
      break;
    if ((!quote && (ch == ' ' || ch == '\t' || ch == '\r')) ||
        ch == '\n' || ch == EOF)
      break;
    if (!quote) ch = tolower(ch);
    if (quote && !quote_one && ch == '%') {
      sprintf(&buffer[i],"%d",trace_control_file_index);
      i += strlen(&buffer[i]);
    } else if (!quote || quote_one || ch != '\\')
      buffer[i++] = ch;
    if (quote_one)
      quote_one = FALSE;
    else if (quote && ch == '\\')
      quote_one = TRUE;
    first = FALSE;
    ch = trace_control_getc();
  } while (i < size-1);
  if (i == size-1) {
    trace_control_error("token exceeds 128 characters",FALSE);
    last_on_line = TRUE;
  }
  if (last_on_line && ch !='\n')
    ch = trace_control_skip_whitespace(TRUE);
  /*
  if (ch == EOF) {
    trace_control_error("last line not terminated with newline",TRUE);
    return -1;
  }
  */
  buffer[i]=0;
  if (quote && !quote_allowed) {
    trace_control_error("unexpected quoted string seen", TRUE);
    return -1;
  }
  return quote?2:((ch == '\n')?1:0);
}

/* g2ext_network_io_find_leaks */
/* g2ext_kept_cons_backtrace_limit */
static int process_trace_control_command()
{
  char token[128];
  int type;
  maybe_get_next_trace_input_file(TRUE);
  if (-1 == (type = get_trace_control_token(token,128,FALSE,FALSE))) return FALSE;
  if (0 == strcmp(token,""))
    return TRUE;
  else if (0 == strcmp(token,"continue")) {
    echo("continue");
    /* continue */
    return FALSE;
  } else if (0 == strcmp(token,"set")) {
    if (-1 == (type = get_trace_control_token(token,128,FALSE,FALSE))) return FALSE;
    if (0 == strcmp(token,"output")) {
      if (-1 == (type = get_trace_control_token(token,128,TRUE,TRUE))) return FALSE;
      if (2 != type) {
        trace_control_error("set output not followed by a quoted string",FALSE);
        return FALSE;
      }
      echof1("set output \"%s\"",token);
      /* set output "file" */
      if (trace_output) {
        GFCLOSE(trace_output);
        trace_output = 0;
      }
      trace_output_file_name = (char *)malloc(strlen(token)+1);
      if (trace_output_file_name == 0) return FALSE;
      strcpy(trace_output_file_name,token);
      trace_output = GFOPEN(trace_output_file_name,"w");
    } else if (0 == strcmp(token,"next")) {
      if (-1 == (type = get_trace_control_token(token,128,FALSE,FALSE))) return FALSE;
      if (0 == strcmp(token,"input")) {
        if (-1 == (type = get_trace_control_token(token,128,TRUE,TRUE))) return FALSE;
        if (2 != type) {
          trace_control_error("set next input not followed by a quoted string",FALSE);
          return FALSE;
        }
        echof1("set next input \"%s\"",token);
        if (trace_control_file != 0) free(trace_control_file);
        trace_control_file = (char *)malloc(strlen(token)+1);
        if (trace_control_file == 0) return FALSE;
        strcpy(trace_control_file,token);
      } else {
      }
    } else if (0 == strcmp(token,"backtrace")) {
      if (-1 == (type = get_trace_control_token(token,128,FALSE,FALSE))) return FALSE;
      if (0 == strcmp(token,"type")) {
        if (-1 == (type = get_trace_control_token(token,128,FALSE,TRUE))) return FALSE;
        if (0 == strcmp(token,"virtual")) {
          echo("set backtrace type virtual");
          g2ext_use_virtual_alarm_p = TRUE;
        } else if (0 == strcmp(token,"prof")) {
          echo("set backtrace type prof");
          g2ext_use_virtual_alarm_p = FALSE;
        } else {
        }
      } else if (0 == strcmp(token,"roots")) {
        /* set backtrace roots "root1" "root2" ... */
        FILE *brf = GFOPEN(tmp_backtrace_root_file,"w");
        echo("set backtrace roots...");
        if (brf) {
          putc('(',brf);
          do {
            if (-1 == (type = get_trace_control_token(token,128,TRUE,FALSE))) return FALSE;
            if (2 == type) fprintf(brf,"|%s| ",token);
            else {
              if (0 == type) trace_control_skip_whitespace(TRUE);
              break;
            }
          } while (TRUE);
          putc(')',brf); putc('\n',brf);
          GFCLOSE(brf);
          backtrace_roots_written = TRUE;
        }
      } else if (0 == strcmp(token,"targets")) {
        /* set backtrace targets "target1" "target2" ... */
        FILE *brf = GFOPEN(tmp_backtrace_target_file,"w");
        echo("set backtrace targets...");
        if (brf) {
          putc('(',brf);
          do {
            if (-1 == (type = get_trace_control_token(token,128,TRUE,FALSE))) return FALSE;
            if (2 == type) fprintf(brf,"|%s| ",token);
            else {
              if (0 == type) trace_control_skip_whitespace(TRUE);
              break;
            }
          } while (TRUE);
          putc(')',brf); putc('\n',brf);
          GFCLOSE(brf);
          backtrace_targets_written = TRUE;
        }
      } else if (0 == strcmp(token,"one")) {
        if (-1 == (type = get_trace_control_token(token,128,FALSE,TRUE))) return FALSE;
        if (0 == strcmp(token,"line")) {
          echo("set backtrace one line");
          g2ext_network_io_one_line_backtrace_p = TRUE;
        } else {
        }
      } else if (0 == strcmp(token,"summary")) {
        if (-1 == (type = get_trace_control_token(token,128,FALSE,TRUE))) return FALSE;
        if (0 == strcmp(token,"only")) {
          echo("set backtrace summary only");
          backtrace_summary_only_p = TRUE;
        } else {
        }
      } else {
      }
    } else if (0 == strcmp(token,"width")) {
      echo("set width");
      /* set width <integer> */
    } else if (0 == strcmp(token,"executable")) {
      echof1("set executable \"%s\"",token);
      /* set executable "executable_file" */
      if (-1 == (type = get_trace_control_token(token,128,TRUE,TRUE))) return FALSE;
      if (2 == type) {
        executable_file = (char *)malloc(strlen(token)+1);
        if (executable_file == 0) return FALSE;
        strcpy(executable_file, token);
      } else {
      }
    } else if (0 == strcmp(token,"address")) {
      echof1("set address \"%s\"",token);
      /* set address "address_file" */
      if (-1 == (type = get_trace_control_token(token,128,TRUE,TRUE))) return FALSE;
      if (2 == type) {
        address_file = (char *)malloc(strlen(token)+1);
        if (address_file == 0) return FALSE;
        strcpy(address_file, token);
      } else {
      }
    } else if (0 == strcmp(token,"find")) {
      echo("set find leaks");
      if (-1 == (type = get_trace_control_token(token,128,FALSE,FALSE))) return FALSE;
      if (0 == strcmp(token,"leaks")) {
        g2ext_network_io_find_leaks = TRUE;
      } else {
      }
    } else if (0 == strcmp(token,"verbose")) {
      trace_control_verbose = TRUE;
      echo("set verbose");
    } else if (0 == strcmp(token,"cons")) {
      /* set cons backtrace count number */
      if (-1 == (type = get_trace_control_token(token,128,FALSE,FALSE))) return FALSE;
      if (0 == strcmp(token,"backtrace")) {
      } else {
      }
    } else {
    }
  } else if (0 == strcmp(token,"close")) {
    if (-1 == (type = get_trace_control_token(token,128,FALSE,TRUE))) return FALSE;
    if (0 == strcmp(token,"output")) {
      echo("close output");
      if (trace_output) {
        GFCLOSE(trace_output);
        trace_output = 0;
      }
    } else
      trace_control_error("\"close\" not followed by \"output\"",FALSE);
  } else if (0 == strcmp(token,"start")) {
      if (-1 == (type = get_trace_control_token(token,128,FALSE,FALSE))) return FALSE;
      if (0 == strcmp(token,"tracing")) {
        if (-1 == (type = get_trace_control_token(token,128,FALSE,TRUE))) return FALSE;
        if ((0 == strcmp(token,"")) ||
            (0 == strcmp(token,"all"))) {
          echo("start tracing all");
          g2ext_enable_network_io_trace();
          g2ext_enable_network_io_backtrace();
        } else if (0 == strcmp(token,"network")) {
          echo("start tracing network");
          g2ext_enable_network_io_trace();
          trace_network_io_data_p = FALSE;
        } else if (0 == strcmp(token,"network_data")) {
          echo("start tracing network_data");
          g2ext_enable_network_io_trace();
        } else if (0 == strcmp(token,"backtrace")) {
          echo("start tracing backtrace");
          g2ext_enable_network_io_backtrace();
        } else if (0 == strcmp(token,"consing")) {
          echo("start tracing consing");
          g2ext_enable_consing_trace();
        } else if (0 == strcmp(token,"functions")) {
          echo("start tracing functions");
          if (x_fn_trace_size>0) function_tracing_enabled = TRUE;
        } else
          trace_control_error("start tracing not followed by [ { network | network_data | backtrace | consing | all } ]", FALSE);
        /* start tracing [ { network | network_data | backtrace | consing | all } ] */
      } else
      trace_control_error("\"start\" not followed by \"tracing\"",FALSE);
  } else if (0 == strcmp(token,"stop")) {
      if (-1 == (type = get_trace_control_token(token,128,FALSE,FALSE))) return FALSE;
      if (0 == strcmp(token,"tracing")) {
        token[0]=0;
        if ((0 == type) &&
            (-1 == (type = get_trace_control_token(token,128,FALSE,TRUE)))) return FALSE;
        if ((0 == strcmp(token,"")) ||
            (0 == strcmp(token,"all"))) {
          echo("stop tracing");
          g2ext_disable_network_io_trace();
        } else if (0 == strcmp(token,"consing")) {
          echo("stop tracing consing");
          g2ext_disable_consing_trace();
        }
      } else
      trace_control_error("\"stop\" not followed by \"tracing\"",FALSE);
  } else if (0 == strcmp(token,"clear")) {
      if (-1 == (type = get_trace_control_token(token,128,FALSE,TRUE))) return FALSE;
      if (0 == strcmp(token,"tracing")) {
        echo("clear tracing");
        g2ext_reset_network_io_trace();
      } else
      trace_control_error("\"clear\" not followed by \"tracing\"",FALSE);
  } else if (0 == strcmp(token,"write")) {
      if (-1 == (type = get_trace_control_token(token,128,FALSE,FALSE))) return FALSE;
      if (0 == strcmp(token,"trace")) {
        echo("write trace");
        if (g2ext_network_io_backtrace_used_p)
          get_function_address_file();
        write_network_io_trace_internal();
        if (0 == type) trace_control_skip_whitespace(TRUE);
      } else if (0 == strcmp(token,"unreclaimed")) {
        if (-1 == (type = get_trace_control_token(token,128,FALSE,TRUE))) return FALSE;
        if (0 == strcmp(token,"conses")) {
          echo("write unreclaimed conses");
          get_function_address_file();
          write_cons_summary_internal();
        }
      } else if (0 == strcmp(token,"backtrace")) {
        if (-1 == (type = get_trace_control_token(token,128,FALSE,TRUE))) return FALSE;
        if (0 == strcmp(token,"summary")) {
          echo("write backtrace summary");
          get_function_address_file();
          write_network_io_backtrace_summary();
        } else if (0 == strcmp(token,"tree")) {
          /* write backtrace tree */
          FILE *saved_trace_output = trace_output;
          trace_output = GFOPEN("/tmp/trace_output","w");
          if (trace_output) {
            if (!backtrace_roots_written) {
              FILE *brf = GFOPEN(tmp_backtrace_root_file,"w");
              if (brf) {
                fprintf(brf,"()\n");
                GFCLOSE(brf);
                backtrace_roots_written = TRUE;
              }
            }
            if (!backtrace_targets_written) {
              FILE *brf = GFOPEN(tmp_backtrace_target_file,"w");
              if (brf) {
                fprintf(brf,"()\n");
                GFCLOSE(brf);
                backtrace_targets_written = TRUE;
              }
            }
            get_function_address_file();
            write_network_data = FALSE;
            write_network_io_trace_internal();
            write_network_data = TRUE;
            make_backtrace_report("/tmp/trace_output","/tmp/report_output.txt");
            g2ext_run_command_line("rm -f /tmp/trace_output");
            trace_output = saved_trace_output;
            fprintf(trace_output,"\n\n");
            copy_file_to_trace_output("/tmp/report_output.txt");
            g2ext_run_command_line("rm -f /tmp/report_output.txt");
          } else
            trace_output = saved_trace_output;
        } else {
        }
      } else if (0 == strcmp(token,"recent")) {
        if (-1 == (type = get_trace_control_token(token,128,FALSE,TRUE))) return FALSE;
        if (0 == strcmp(token,"functions")) {
          echo("write recent functions");
          print_fn_trace();
        }
      }
  } else if (0 == strcmp(token,"call")) {
    if (-1 == (type = get_trace_control_token(token,128,FALSE,TRUE))) return FALSE;
    call_trace_function(token);
  } else if (0 == strcmp(token,"note")) {
    /* echo("note"); */
    if (-1 == (type = get_trace_control_token(token,128,TRUE,TRUE))) return FALSE;
      if (2 == type) {
        g2ext_network_io_trace_note(token);
      } else {
      }
  } else {
    char buffer[100];
    sprintf(buffer,"unrecognized command: \"%s\"",token);
    trace_control_error(buffer,FALSE);
  }
  return TRUE;
}

/*
 * Yet Another Tracing Facility
 */

void g2pvt_vtrace(int flags, const char *fmt, va_list args)
{
  char buf[512];
  static int n = 0;

  if(flags&1) {
    sprintf(buf,"[%03d] ", ++n);
    g2pvt_puts(buf);
  }

  buf[0] = 0;
#if defined(WIN32)
  _vsnprintf(buf, sizeof(buf), fmt, args);
#else
  vsnprintf(buf, sizeof(buf), fmt, args);
#endif
  buf[sizeof(buf)-1] = 0;

  if (flags&2)
    g2ext_write_string_to_console(buf);
  else
    g2pvt_puts(buf);
}

void g2pvt_traceEx(int flags, const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  g2pvt_vtrace(flags,fmt,args);
  va_end(args);
}

void g2pvt_trace(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  g2pvt_vtrace(1,fmt,args);
  va_end(args);
}

void g2pvt_printf(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  g2pvt_vtrace(0,fmt,args);
  va_end(args);
}

void g2pvt_notify_user(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  g2pvt_vtrace(2,fmt,args);
  va_end(args);
}

void g2pvt_puts(const char *str)
{
#if defined(WIN32) && defined(_DEBUG)
  OutputDebugString(str);        /* Visual Studio Debug build */
#else
  fputs(str,stderr);                /* All other platforms. */
  fflush(stderr);
#endif
}

void g2pvt_output_debug_string(char *str)
{
#if defined(WIN32) && defined(_DEBUG)
  OutputDebugString(str);
#endif
}
