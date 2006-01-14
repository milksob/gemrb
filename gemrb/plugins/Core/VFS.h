/* GemRB - Infinity Engine Emulator
 * Copyright (C) 2003 The GemRB Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header: /data/gemrb/cvs2svn/gemrb/gemrb/gemrb/plugins/Core/VFS.h,v 1.15 2006/01/14 17:16:42 avenger_teambg Exp $
 *
 */

/**
 * @file VFS.h
 * Compatibility layer for file and dir access functions on Un*x and MS Win
 * @author The GemRB Project
 */

#ifndef VFS_H
#define VFS_H

#ifdef WIN32
#include <io.h>
#include <windows.h>
#include <direct.h>
#else
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fnmatch.h>
#include <dlfcn.h>
#endif

#ifdef WIN32
#define _MAX_PATH 260
#else
#define _MAX_PATH FILENAME_MAX
#endif

//#ifndef S_ISDIR
//#define S_ISDIR(x) ((x) & S_IFDIR)
//#endif

#ifndef S_ISDIR
#define S_ISDIR(mode) (((mode) & S_IFMT) == S_IFDIR)
#endif


#ifdef WIN32

#ifdef GEM_BUILD_DLL
#define GEM_EXPORT __declspec(dllexport)
#else
#define GEM_EXPORT __declspec(dllimport)
#endif

#else
#define GEM_EXPORT
#endif

#ifdef WIN32

#define R_OK 04

typedef struct DIR {
	char path[_MAX_PATH];
	bool is_first;
	struct _finddata_t c_file;
	long hFile;
} DIR;

typedef struct dirent {
	char d_name[_MAX_PATH];
} dirent;

DIR* opendir(const char* filename);
dirent* readdir(DIR* dirp);
void closedir(DIR* dirp);

typedef struct _FILE {
	HANDLE hFile;
} _FILE;

GEM_EXPORT _FILE* _fopen(const char* filename, const char* mode);
GEM_EXPORT size_t _fread(void* ptr, size_t size, size_t n, _FILE* stream);
GEM_EXPORT size_t _fwrite(const void* ptr, size_t size, size_t n,
	_FILE* stream);
GEM_EXPORT size_t _fseek(_FILE* stream, long offset, int whence);
GEM_EXPORT int _fgetc(_FILE* stream);
GEM_EXPORT long int _ftell(_FILE* stream);
GEM_EXPORT int _feof(_FILE* stream);
GEM_EXPORT int _fclose(_FILE* stream);
#define mkdir(path, rights)  _mkdir(path)
#define ResolveFilePath(p)

#else  // ! WIN32

#define _FILE FILE
#define _fopen fopen
#define _fread fread
#define _fwrite fwrite
#define _fseek fseek
#define _fgetc fgetc
#define _ftell ftell
#define _feof feof
#define _fclose fclose

void ResolveFilePath(char* FilePath);

#endif  // ! WIN32

GEM_EXPORT char* FindInDir(const char* Dir, const char* Filename, bool wildcard=false);
GEM_EXPORT bool dir_exists(const char* path);

GEM_EXPORT char* PathAppend (char* target, char* dir);
GEM_EXPORT char* PathJoin (char* target, ...);
GEM_EXPORT void FixPath (char *path, bool needslash);

#endif  // !VFS_H
