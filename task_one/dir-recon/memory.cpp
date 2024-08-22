#include "includes.h"





// char* file_buffer = new char[fileSize];

void getFileContent(char** pBuffer, SIZE_T* size)
{
	//std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
	std::ifstream file("test.txt", std::ios::in | std::ios::binary);
	if (!file)
	{
		printf("cant get file\n"); return;
	}
	file.seekg(0, std::ios::end);
	*size = file.tellg(); // size matters
	if (!*size || *size == (int)(-1))
	{
		return;
	}
	//printf("size: %d", *size);
	file.seekg(0, std::ios::beg);
	*pBuffer = new char[*size + 0x1];
	file.read(*pBuffer, *size);
	//*pBuffer[*size] = '\0';
}

void getFileContent2(std::vector<std::string>* pData)
{
	std::ifstream file("test.txt", std::ios::in | std::ios::binary);
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(file, line)) 
	{
		lines.push_back(line);
	}
	file.close();
	*pData = lines;
}

