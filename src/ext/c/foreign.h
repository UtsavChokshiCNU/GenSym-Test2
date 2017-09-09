/*************
 * foreign.h *
 *************/

/* Include file for foreign function server.

Legal Notice:            Copyright (C) 1986-2017 Gensym Corporation.,
                         125 CambridgePark Drive, Cambridge MA 02140
                         All rights reserved.
*/


#include "icp.h"

/* These declarations are used for optional version control.
-------------------------------------------------------------*/
#define FFE_INCLUDE_MAJ_VER_NUM       3L
#define FFE_INCLUDE_MIN_VER_NUM       2L


extern ffe_int ffe_include_file_major_version;
extern ffe_int ffe_include_file_minor_version;

#define FFE_SUCCESS  1L
#define FFE_FAILURE  0L

#define G2_INTEGER_TO_FOREIGN(param) \
 ((param).p_value.integer_p)

#define G2_REAL_TO_FOREIGN(param) \
 ((param).p_value.float_p)

#define G2_SYMBOL_TO_FOREIGN(param) \
 ((param).p_value.symbol_p)

#define G2_TEXT_TO_FOREIGN(param) \
 ((param).p_value.string_p)

#define FOREIGN_TO_G2_INTEGER(value, param) \
((param).p_type) = INTEGER_TAG; \
((param).p_value.integer_p) = (value);

#define FOREIGN_TO_G2_REAL(value, param) \
((param).p_type) = FLOAT64_TAG; \
((param).p_value.float_p) = (value);

#define FOREIGN_TO_G2_SYMBOL(value, param) \
((param).p_type) = SYMBOL_TAG; \
((param).p_value.symbol_p) = (value);

#define FOREIGN_TO_G2_TEXT(value, param) \
((param).p_type) = STRING_TAG; \
((param).p_value.string_p) = (value);
