#include "pch.h"
#include "StringUtils.h"

std::string StringUtils::GetDirectoryFromFilePath(std::string filePath)
{
	std::string directory;
	const size_t last_slash_idx = filePath.rfind('\\');
	if (std::string::npos != last_slash_idx)
	{
		directory = filePath.substr(0, last_slash_idx);
	}
	return directory;
}

std::string StringUtils::GetDirectoryFromFilePath(char* filePath)
{
	return GetDirectoryFromFilePath(std::string(filePath));
}
