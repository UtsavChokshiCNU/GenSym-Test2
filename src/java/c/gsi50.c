
#define MAX_REGISTERED_REMOTE_PROCEDURES 50
#define MAX_CALL_INDEX 1000

#include "gsi50.h"

typedef struct _rpcuserdata {
  int handle;
  void* user_data;
} rpcuserdata;

static rpcuserdata RemoteCallData [MAX_REGISTERED_REMOTE_PROCEDURES];
static int number_of_registered_remote_procedures = 0;
static long outstanding_call_handle [MAX_CALL_INDEX];

void put_user_data_in_table (long handle, void* user_data) {
  int current_proc_index = number_of_registered_remote_procedures++;
  rpcuserdata* current_table_entry = RemoteCallData + current_proc_index;

  current_table_entry->handle = handle;
  current_table_entry->user_data = user_data;
  printf ("Putting (%d, %s) in table.\n", handle, user_data);
}


void* get_user_data_from_table (long handle) {
  int i;

  printf ("Getting user_data for %ld = ", handle);
  for (i=0; i<number_of_registered_remote_procedures; i++)
    if ((RemoteCallData[i]).handle == handle) {
      printf ("%s\n", (RemoteCallData[i]).user_data);
      return ((RemoteCallData[i]).user_data);
    }
  
  printf ("none!<<<<<<<<<\n");
  return 0;
}

extern int fulldebug;

void associate_thread_data_with_call_index (int index, long handle) {
  if (index >= MAX_CALL_INDEX)
    exit (-1);
  outstanding_call_handle [index] = handle;
  if (fulldebug) printf ("Saving thread data (%ld) for %d.\n",
			 outstanding_call_handle [index],
			 index);
}


long get_thread_data_from_call_index (int index) {
  if (fulldebug) printf ("Returning thread data (%ld) for %d.\n",
			 outstanding_call_handle [index],
			 index);
  return outstanding_call_handle [index];
}
