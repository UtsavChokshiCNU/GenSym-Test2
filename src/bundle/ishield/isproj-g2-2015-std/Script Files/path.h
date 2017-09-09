
//Path.h


prototype FreeSpaceMB (STRING, BYREF STRING, BYREF NUMBER);//(svPath,szAvailSpace)// returns size in MB and is not Limited to 2 gig
prototype ConvertByteToMB(BYREF NUMBER,NUMBER); // (nSpaceMB,nSpace)

prototype GetPrimaryAndChildPath(STRING,BYREF STRING,BYREF STRING);
prototype SetPrimaryPath(STRING,BYREF STRING);
prototype SetChildPath(STRING, BYREF STRING);
prototype GetCompletePath (BYREF STRING,STRING,STRING);//(szCompletePath,szPrimaryPath,szChildPath
prototype ResetWinPlayerDirs(STRING,STRING);
prototype GetParentDirectory (STRING,BYREF STRING); // returns the parent directory
prototype GetParentAndChildDirectory(STRING,BYREF STRING, BYREF STRING);







// MHD, 10/2/00: The following just keeps us from getting warnings
// about some functions not used now. 

prototype path_gag_is_compiler();
function path_gag_is_compiler()
STRING by_ref_string, by_ref_string2;
BOOL by_ref_bool;
BOOL by_ref_number;
LIST some_list, by_ref_list;
begin
 GetPrimaryAndChildPath("",by_ref_string,by_ref_string2);
 SetPrimaryPath("",by_ref_string);
 SetChildPath("", by_ref_string);
 GetCompletePath (by_ref_string,"","");
 GetParentDirectory ("",by_ref_string);
 GetParentAndChildDirectory("",by_ref_string, by_ref_string2);
 path_gag_is_compiler();
end;
