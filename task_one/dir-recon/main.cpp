#include "includes.h"

int main() 
{
	//SIZE_T size = NULL; char* fileBuffer = (char*)"hello";
	//getFileContent(&fileBuffer, &size);
	//std::cout << "file buffer: \n" << fileBuffer; //DELETE
	printf("starting.. team Cibai\n");
	std::vector<std::string> data;
	getFileContent2(&data);
	for (size_t i = 0; i < data.size(); ++i)
	{
		std::cout << "Line " << i + 1 << ": " << data[i];
		if (isCommand(data[i].c_str()))
		{
			std::cout << "command " << i + 1 << ": " << data[i] << std::endl;
		}
		else
		{
			std::cout << "content " << i + 1 << ": " << data[i] << std::endl;
		}
		if (isCommand(data[i].c_str()))
		{

		}
	}


	std::cin.get(); //DELETE
}