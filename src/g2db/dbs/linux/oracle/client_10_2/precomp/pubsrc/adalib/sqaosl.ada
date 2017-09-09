--
--$Header: sqaosl.a.pp,v 1.2 1995/02/27 08:14:03 nikeda Exp $     
--
-- Copyright (c) 1995, 1997 by Oracle Corporation
--   NAME
--     sqaosl.a.pp - Ada interface to sqllib
--   DESCRIPTION
--     The definitions in this file enable Mod*Ada applications to use
--     sqllib instead of the traditional adalib.
--   RETURNS
-- 
--   NOTES
--     The front-end must be modified to use the new codegen in order to
--     use this "mini-Adalib."  This file must be pre-procedded prior to
--     compilation
--   MODIFIED   (MM/DD/YY)
--    nikeda     05/13/97 -  Add sql_date and sql_mlslabel
--    nikeda     05/06/97 -  Update for new 8.0 features
--    nikeda     04/24/97 -  Define type sql_cursor
--    nikeda     02/06/95 -  Creation

with system, sql_standard; 

with unchecked_conversion;

package oracle_sqllib is

--
-- Define the type we'll use for the c_pointers
--

type usl            is range       0..SYSTEM.MAX_INT;

for  usl'size       use            32;

subtype unsigned_long           is usl;
subtype c_pointer is unsigned_long;
subtype sql_context is unsigned_long;

null_c_pointer : constant c_pointer := 0;

--
-- Define the type used for cursor variables
--
type sql_cursor is record
  curocn : integer;
  ptr1   : c_pointer;
  ptr2   : c_pointer;
  mgcval : unsigned_long;
end record;
--
-- Additional types used for default with interface
--
type sql_mlslabel is array (positive range <>) of character;
type sql_date is array (positive range <>) of character;

--
-- Define the to_c_pointer function
--
subtype address is system.address;

function to_c_pointer is new
	unchecked_conversion (address, c_pointer);

pragma inline(to_c_pointer);

--
-- Define the interface routines to sqllib
--
procedure sqlaex(rcx : c_pointer; ctx : integer; 
		 stm : c_pointer; fpn : c_pointer);
pragma interface (C, sqlaex);

-- Routine to get the SQLSTATE value
procedure sqlgss(state : c_pointer);
pragma interface (C, sqlgss);

-- Function to obtain the number of rows processed 
function rows_processed(ctx : sql_context) return integer;
function rows_processed return integer;
 
-- Procedure to obtain the error message text from the last error encountered
procedure error_message_text(ctx : sql_context;
                             msg_buf : system.address;
                             buf_len : integer;
                             msg_len : out integer);
procedure error_message_text(msg_buf : system.address;
                             buf_len : integer;
                             msg_len : out integer);
 
-- Integer array types
type sql_int_arr is array (positive range <>) of sql_standard.int;
type sql_smallint_arr is array (positive range <>) of sql_standard.smallint;
type sql_real_arr is array (positive range <>) of sql_standard.real;
type sql_double_precision_arr is
        array (positive range <>) of sql_standard.double_precision;

end oracle_sqllib;
