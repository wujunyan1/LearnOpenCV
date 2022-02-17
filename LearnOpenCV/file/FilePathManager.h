#pragma once
#include <string>

class FilePathManager
{
public :
	static void setRootPath(char* path)
	{
		rootPath = path;
	}

	static char* getRootPath()
	{
		return rootPath;
	}

private:
	static char* rootPath;
};

