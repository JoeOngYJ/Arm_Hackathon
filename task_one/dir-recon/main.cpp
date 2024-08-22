#include "includes.h"

std::string enumLines(std::string line, std::string currPath);
const char* combine(const char* str1, const char* str2);

CD_ITEM checkCd(char* line);

void removeNewline(std::string& str);

int main() 
{

	std::cout << "starting..." << std::endl;
	std::vector<std::string> data;
	getFileContent2(&data);
	char* currPath;

	for (size_t i = 0; i < data.size(); i++)
	{
		std::cout << data[i] << std::endl;
		CD_ITEM result = checkCd(data[i].c_str());
		if (result.isCd)
		{	
			currPath = combine(currPath, result.dir);
		}
		std::cout << "current path: \n" << new_path << std::endl;
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
	}
	return result;
}

void removeNewline(std::string& str) 
{
	if (!str.empty() && str.back() == '\n') {
		str.erase(str.size() - 1);
	}
}

const char* combine(const char* str1, const char* str2) 
{
	size_t len1 = std::strlen(str1);
	size_t len2 = std::strlen(str2);
	char* result = new char[len1 + len2 + 1];
	std::strcpy(result, str1);
	std::strcat(result, str2);
	return result;
}