#pragma once

#ifdef __cplusplus
extern "C" {
#endif

long g2ext_g2_stream_open(char* pathname_string, long open_mode);
long g2ext_g2_stream_open_s16(char* pathname_string, long open_mode);
long g2ext_str_close (long stream_index);

#ifdef __cplusplus
}
#endif
