#include <iostream>
#include <fstream>
#include <boost/date_time.hpp>
#include "status_code.h"

/// <summary>
/// Status
/// </summary>
namespace status
{
	/// <summary>
	/// Status code
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
/// Status class
/// </summary>
class Status
{
private:
	/// <summary>
	/// Status code
	/// </summary>
	status::StatusCode _statusCode;
public:
	/// <summary>
	/// Default constructor (delegation)
	/// </summary>
	Status() : Status(status::StatusCode::Status_AllGood){}

	/// <summary>
	/// Constructor with parameter
	/// </summary>
	/// <param name="statusCode">Status code</param>
	Status(status::StatusCode statusCode);

	/// <summary>
	/// Get status code
	/// </summary>
	/// <returns>Status code</returns>
	status::StatusCode GetStatusCode();

	/// <summary>
	/// Set status code
	/// </summary>
	/// <param name="newStatusCode">New status code</param>
	void SetStatusCode(status::StatusCode newStatusCode);

	/// <summary>
	/// Check if there is an error
	/// </summary>
	/// <returns>Presence of error</returns>
	bool GetPresentError();

	/// <summary>
	/// Print message to console
	/// </summary>
	/// <param name="addedMessage">Additional text</param>
	void PrintMessage(std::string addedMessage = "");

	/// <summary>
	/// Create a log file
	/// </summary>
	/// <param name="logText">Log text</param>
	void CreateLogFile(std::string logText);
};