#pragma once


#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include "status.h"
/// <summary>
/// class Far
/// </summary>
class Far
{
private:
	Status* _status;///status

	std::string _currentDirectory;
	/// <summary>
	/// Search File Or Directory
	/// </summary>
	/// <param name="objectName">Name objects</param>
	/// <param name="pathToFind">Find to pash</param>
	/// <returns>Status Code</returns>
	status::StatusCode SearchFileOrDirectory(std::string objectName, std::string pathToFind = "");
public:
	Far() : Far("/") {}
	/// <summary>
	/// Constructor with parameter
	/// </summary>
	/// <param name="current Directory">current Directory</param>
	Far(std::string currentDirectory);

	/// <summary>
	/// Print Content From Directory
	/// </summary>
	/// <param name="path To Directory"></param>
	void PrintContentFromDirectory(std::string pathToDirectory = "");

	/// <summary>
	/// CreateDirectory
	/// </summary>
	/// <param name="create Directory Name">Name Directory</param>
	/// <param name="path To Directory">path To Directory</param>
	/// <returns>Status Code</returns>
	status::StatusCode CreateDirectory(std::string createDirectoryName, std::string pathToDirectory = "");

	/// <summary>
	/// Create File
	/// </summary>
	/// <param name="file Name">Name file</param>
	/// <param name="file Type">Type file</param>
	/// <param name="path To Directory">path To Directory</param>
	/// <returns>Status Code</returns>
	status::StatusCode CreateFile(std::string fileName, std::string fileType, std::string pathToDirectory = "");
};