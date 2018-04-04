#include "FileManager.h"

#include <fstream>

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
}

enum loadState { ATTRIBUTES, CONTENT };
int state;

void FileManager::LoadContent(const char* filename,
	std::vector<std::vector<std::string> >& attr,
	std::vector<std::vector<std::string> >& contents)
{
	attr.clear();
	contents.clear();

	std::ifstream openfile(filename);
	if (openfile)
	{
		while (!openfile.eof())
		{
			std::string line;
			std::getline(openfile, line);

			line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

			if (line.find("load=") != std::string::npos)
			{
				state = ATTRIBUTES;
				line.erase(0, line.find('=') + 1);
				tempAttr.clear();
			}
			else
			{
				state = CONTENT;
				tempContent.clear();
			}

			line.erase(std::remove(line.begin(), line.end(), '['), line.end());

			std::stringstream ss(line);

			while (ss)
			{
				std::getline(ss, line, ']');
				if (line != "")
				{
					std::cout << line << std::endl;
					if (state == ATTRIBUTES)
						tempAttr.push_back(line);
					else
						tempContent.push_back(line);
				}
			}

			if (state == CONTENT && tempContent.size() > 0)
			{
				attr.push_back(tempAttr);
				contents.push_back(tempContent);
			}
		}
	}
	else
	{
		std::cout << "Failed to open file " << filename << std::endl;
	}
}

void FileManager::LoadContent(const char* filename,
	std::vector<std::vector<std::string> >& attr,
	std::vector<std::vector<std::string> >& contents,
	std::string id)
{
	attr.clear();
	contents.clear();

	idFound = false;

	std::ifstream openfile(filename);
	if (openfile)
	{
		while (!openfile.eof())
		{
			std::string line;
			std::getline(openfile, line);

			line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

			if (line.find("start=[" + id + "]") != std::string::npos)
			{
				idFound = true;
				continue;
			}
			else if (line.find("end=") != std::string::npos && line.find(id) != std::string::npos)
			{
				idFound = false;
				continue;
			}

			if (idFound)
			{

				if (line.find("load=") != std::string::npos)
				{
					state = ATTRIBUTES;
					line.erase(0, line.find('=') + 1);
					tempAttr.clear();
				}
				else
				{
					state = CONTENT;
					tempContent.clear();
				}

				line.erase(std::remove(line.begin(), line.end(), '['), line.end());

				std::stringstream ss(line);

				while (ss)
				{
					std::getline(ss, line, ']');
					if (line != "")
					{
						//std::cout << line << std::endl;
						if (state == ATTRIBUTES)
							tempAttr.push_back(line);
						else
							tempContent.push_back(line);
					}
				}

				if (state == CONTENT && tempContent.size() > 0)
				{
					attr.push_back(tempAttr);
					contents.push_back(tempContent);
				}
			}
		}
	}
	else
	{
		std::cout << "Failed to open file " << filename << std::endl;
	}
}