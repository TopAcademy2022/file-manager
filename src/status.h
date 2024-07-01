#pragma once


#include <iostream>
#include <fstream>
#include <boost/date_time.hpp>

/// <summary>
/// Status
/// </summary>
namespace status
{
	/// <summary>
	/// Status Code
	/// </summary>
	enum StatusCode
	{
		Status_AllGood = 0,
		Error_DirectoryNotFound = 1,
		Error_FileNotFound = 2,
		Status_DirectoryOrFileWasFound = 3,
		Status_DirectoryWasCreated = 4,
		Status_FileWasCreated = 5,
		Error_FileWasCreated = 6,
		Error_NoAccessRights = 7
	};
}

/// <summary>
/// class Status
/// </summary>
class Status
{
private:
	/// <summary>
	///Code status
	/// </summary>
	status::StatusCode _statusCode;
public:

	/// <summary>
	/// default constructor (delegation)
	/// </summary>
	Status() : Status(status::StatusCode::Status_AllGood){}

	/// <summary>
	/// Constructor with parameter
	/// </summary>
	/// <param name="status Code">Code status</param>
	Status(status::StatusCode statusCode);

	/// <summary>
	/// GetStatusCode
	/// </summary>
	/// <returns>Status Code</returns>
	status::StatusCode GetStatusCode();

	/// <summary>
	/// Set Status Code
	/// </summary>
	/// <param name="newStatusCode">new Status Codeà</param>
	void SetStatusCode(status::StatusCode newStatusCode);

	/// <summary>
	///  Get Present Error
	/// </summary>
	/// <returns>Present Error</returns>
	bool GetPresentError();

	/// <summary>
	/// Print Message
	/// </summary>
	/// <param name="addedMessage">added Message</param>
	void PrintMessage(std::string addedMessage = "");

	/// <summary>
	/// Create report File
	/// </summary>
	/// <param name="log Text">report text</param>
	void CreateLogFile(std::string logText);
};

