#include "includes.h"
#define _CRT_SECURE_NO_WARNINGS

void remove_newlines(char* str);
void append_string(char** str, const char* addition);

char* combineStrings(const char* str1, const char* str2);
CD_ITEM checkCd(const char* line);

int main() 
{

	std::cout << "starting..." << std::endl;
	std::vector<std::string> data;
	getFileContent2(&data);
	char* currPath = NULL;

	for (int i = 0; i < data.size(); i++)
	{
		CD_ITEM result = checkCd(data[i].c_str());
		if (result.isCd)
		{
			std::cout << data[i] << std::endl;
			append_string(&currPath, result.dir);
			std::cout << "current path: " << currPath << std::endl << std::endl;
		}
	}
	std::cin.get(); //DELETE
}


CD_ITEM checkCd(const char* line)
{
	CD_ITEM result = {};
	const char* prefix = "$ cd ";
	size_t prefixLength = std::strlen(prefix);
	if (std::strncmp(line, prefix, prefixLength) == 0)
	{
		result.isCd = true;
		result.dir = line + prefixLength;
		//std::cout << "cd: " << result.dir << std::endl;
	}
	return result;
}

char* combineStrings(const char* str1, const char* str2) 
{
	size_t length = strlen(str1) + strlen(str2) + 1;
	char* combined = new char[length];
	strcpy_s(combined, length, str1);
	strcat_s(combined, length, str2);
	return combined;
}
void remove_newlines(char* str) 
{
	char* src = str;
	char* dst = str;

	while (*src != '\0') {
		if (*src != '\n') {
			*dst = *src;
			dst++;
		}
		src++;
	}
	*dst = '\0';
}
void append_string(char** str, const char* addition) 
{
	size_t len = *str ? strlen(*str) : 0;
	size_t addition_len = strlen(addition);
	*str = (char*)realloc(*str, len + addition_len + 1);
	if (*str == NULL)
		return;
	strcpy_s(*str + len, addition_len + 1, addition);
}
