#pragma once


#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include "status.h"
#include "status_code.h"

class Far
{
private:
	Status* _status;

	std::string _currentDirectory;

	status::StatusCode SearchFileOrDirectory(std::string objectName, std::string pathToFind = "");
public:
	Far() : Far("/") {}

	Far(std::string currentDirectory);

	/*!
	* @brief Print all files from folder.
	* @param[in] pathToDirectory - Path to folder was printing.
	*/
	void PrintContentFromDirectory(std::string pathToDirectory = "");

	/*!
	* @brief Print all files from folder.
	* @param[in] createDirectoryName - Dir name was created.
	* @param[in] pathToDirectory - Path to folder.
	* @return status::StatusCode - status of operation.
	*/
	status::StatusCode CreateDirectory(std::string createDirectoryName, std::string pathToDirectory = "");
	/*!
	* @brief Creating a file with a specified type, name and directory.
	* @param[in] fileName - Name of file.
	* @param[in] fileType - Type of file.
	* @param[in] pathToDirectory - File path
	* @return status::StatusCode - status of file operation
	*/
	status::StatusCode CreateFile(std::string fileName, std::string fileType, std::string pathToDirectory = "");
};