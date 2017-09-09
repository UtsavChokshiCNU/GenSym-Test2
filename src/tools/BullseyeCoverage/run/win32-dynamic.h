// $Revision: 10767 $ $Date: 2010-01-20 14:15:27 -0800 (Wed, 20 Jan 2010) $
// Copyright (c) Bullseye Testing Technology
// This source file contains confidential proprietary information.
// Do not modify this source file.  If you need changes, contact Technical Support.
// Modification is likely to break functionality and interfere with upgrading to a future release.
//
// This file contains declarations shared between the static and dynamic run-time libraries.

typedef void (__cdecl* AtexitParameter)(void);
typedef int (__stdcall* Atexit)(AtexitParameter);

// An open file
// A POSIX file descriptor is an index into an array of this structure
typedef struct {
	HANDLE handle;
	// Set to 0 if this file descriptor is available, otherwise 1
	long lock;
} FileDescriptor;

// The size of the array of FileDescriptor
enum { fileListSize = 4 };

// Interface for the static run-time linked with each image (DLL or EXE)
typedef struct {
	unsigned magic;
	int (__cdecl* covWrite)(void);
	FileDescriptor* fileList;
	volatile long* covWriteLock;
	AtexitParameter exeAtexitParameter;
	unsigned long threadId;
} StaticImage;

// Interface for the dynamic run-time
typedef struct {
	void (__stdcall* createAutoSave)(void);
	int (__stdcall* staticImageAdd)(StaticImage*);
	void (__stdcall* staticImageRemove)(StaticImage*);
} Dynamic;
