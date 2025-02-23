#pragma once


#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include "status.h"

class Far
{
private:
	Status* _status;

	std::string _currentDirectory;

	status::StatusCode SearchFileOrDirectory(std::string objectName, std::string pathToFind = "");
public:
	Far() : Far("/") {}

	Far(std::string currentDirectory);

	void PrintContentFromDirectory(std::string pathToDirectory = "");

	status::StatusCode CreateDirectory(std::string createDirectoryName, std::string pathToDirectory = "");

	status::StatusCode CreateFile(std::string fileName, std::string fileType, std::string pathToDirectory = "");
};

bool Delete(const std::string& path);