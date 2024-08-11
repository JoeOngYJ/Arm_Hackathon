#pragma once
#include <stdio.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>  // C++17 and above

typedef unsigned long       DWORD;
typedef unsigned long       ULONG;
typedef long long			SIZE_T;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef void*				PVOID;

void getFileContent(char** pBuffer, SIZE_T* size);
void getFileContent2(std::vector<std::string>* pData);
extern "C" bool isCommand(const char* line);

typedef struct CD_ITEM
{
	bool isCd;
	const char* dir;
};

typedef struct FILE_DETAIL
{
	std::string file_name;
	std::string dir;
	int dir_depth;
};