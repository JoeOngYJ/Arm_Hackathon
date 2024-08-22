#include "includes.h"
#define _CRT_SECURE_NO_WARNINGS

void remove_newlines(char* str);
void append_string(char** str, const char* addition);
const char* remove_newlines(const char* input);
bool isCd(const char* line);
void cdCommand(std::string& currentDirectory, const char* command);
int countSlashes(const std::string& path);
char* combineStrings(const char* str1, const char* str2);
CD_ITEM checkCd(const char* line);
FILE_DETAIL fileDetails[1024] = {};

int main() 
{
	//std::cout << "starting..." << std::endl;
	std::vector<std::string> data; 
	getFileContent2(&data);
	char* currPath = NULL;
	int dataSize = (int)data.size();
	//append_string(&currPath, "REEEEE");
	//append_string(&currPath, "MOREREEE");
	//std::cout << currPath;
	unsigned int file_count = 0;
	//std::cout << "[debug] datasize: " << dataSize;
	std::string currentDirectory;
	std::string deepest_file_dir;
	std::string deepest_file_name;
	int deepest_depth = -1;
	float total_depth = 0;
	for (int i = 0; i < dataSize; ++i)
	{
		if (isCd(data[i].c_str()))
		{
			cdCommand(currentDirectory, data[i].c_str() + 2);
			//std::cout << currentDirectory << std::endl;
		}
		else if (std::isdigit(static_cast<unsigned char>(data[i].c_str()[0])))
		{
			// is a file
			//fileDetails[file_count].file_name = data[i];
			int depth = countSlashes(currentDirectory) -1;
			if (depth > deepest_depth)
			{
				size_t spacePos = data[i].find(' ');
				if (spacePos)
				{
					deepest_file_name = data[i].substr(spacePos + 1);
				}
				//std::cout << deepest_file_name << std::endl;
				deepest_depth = depth;
				deepest_file_dir = currentDirectory;
				
			}
			file_count++;
			total_depth += depth;
		}	
	}
	float average_depth = total_depth / dataSize;
	std::cout << file_count << ",'" << deepest_file_dir << "/"  << "'," << average_depth << std::endl;
	std::cin.get(); //DELETE
}

int countSlashes(const std::string& path) 
{
	int slashCount = 0;
	for (char ch : path) {
		if (ch == '/') {
			++slashCount;
		}
	}
	return slashCount;
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

bool isCd(const char* line)
{
	CD_ITEM result = {};
	const char* prefix = "$ cd ";
	size_t prefixLength = std::strlen(prefix);
	if (std::strncmp(line, prefix, prefixLength) == 0)
	{
		return true;
	}
	return false;
}


char* combineStrings(const char* str1, const char* str2) 
{
	size_t length = strlen(str1) + strlen(str2) + 1;
	char* combined = new char[length];
	strcpy_s(combined, length, str1);
	strcat_s(combined, length, str2);
	return combined;
}
const char* remove_newlines(const char* input) 
{
	if (input == NULL) {
		return NULL;
	}
	size_t len = strlen(input);
	char* result = (char*)malloc(len + 1);
	if (result == NULL) {
		return NULL;
	}
	char* dst = result;
	for (const char* src = input; *src != '\0'; src++) {
		if (*src != '\n') {
			*dst++ = *src;
		}
	}
	*dst = '\0';
	return result;
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

void cdCommand(std::string& currentDirectory, const char* command) 
{
	std::string commandStr(command);
	std::istringstream ss(commandStr);
	std::string operation, directory;
	ss >> operation >> directory;

	if (operation == "cd") {
		if (directory == "..") {
			if (!currentDirectory.empty()) {
				size_t pos = currentDirectory.find_last_of('/');
				if (pos != std::string::npos) {
					currentDirectory = currentDirectory.substr(0, pos);
				}
				else {
					currentDirectory.clear();
				}
			}
		}
		else {
			if (!currentDirectory.empty()) {
				currentDirectory += "/" + directory;
			}
			else {
				currentDirectory = directory;
			}
		}
	}
}
