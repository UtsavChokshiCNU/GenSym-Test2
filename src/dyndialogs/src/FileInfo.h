#pragma once

typedef struct tag_FileInfo
{
	int type;			// 1 = folder, 0 = other
	LPCSTR name;		// the file name not including the path
	long size;			// in bytes
	FILETIME time;		// modification time
} FileInfo;