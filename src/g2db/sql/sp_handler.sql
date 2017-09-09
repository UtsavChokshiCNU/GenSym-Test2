create or replace procedure sp_handler (proc_name IN VARCHAR2, proc_args IN VARCHAR2, ret_val OUT VARCHAR2)
as begin

  -- call the stored procedure named :proc_name here with args :proc_args

  -- collect your return values and put them in a varchar2. You can use any delimiters you
  -- choose. When the varchar2 is returned to G2, you must decode it in your application.

  -- NOTE: The max length of the return value is 4000 characters

  ret_val := 'This is an example return value string,Here is another,Here is a 3rd';

end sp_handler;

