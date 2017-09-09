#include "runtime.h"

void g2ext_heap_command_line(int argc, char *argv[]) {}

void g2ext_print_backtrace() {}

long g2ext_write_string_to_console() { return 0;}

Object Gensym_error_message_buffer = 0;

Object g2int_error_handler() { return 0;}

Object g2_region_memory_usage(Object region_number) { return 0;}
