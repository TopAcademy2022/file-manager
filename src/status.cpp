#include "status.h"
#include "status_code.h"

Status::Status(status::StatusCode statusCode)
{
	this->_statusCode = statusCode;
}

status::StatusCode Status::GetStatusCode()
{
	return this->_statusCode;
}

void Status::SetStatusCode(status::StatusCode newStatusCode)
{
	this->_statusCode = newStatusCode;
}

bool Status::GetPresentError()
{
	bool result = true;

	if (this->_statusCode == status::StatusCode::Status_AllGood ||
		this->_statusCode == status::StatusCode::Status_DirectoryOrFileWasFound ||
		this->_statusCode == status::StatusCode::Status_DirectoryWasCreated || 
		this->_statusCode == status::StatusCode::Status_FileWasCreated)
	{
		result = false;
	}

	return result;
}

void Status::PrintMessage(std::string addedMessage)
{
	switch (this->_statusCode)
	{
	case status::StatusCode::Status_AllGood:
		std::cout << "No errors." << std::endl;
		break;
	case status::StatusCode::Error_DirectoryNotFound:
		std::cout << "The specified directory was not found." << std::endl;
		break;
	case status::StatusCode::Error_FileNotFound:
		std::cout << "The specified file was not found." << std::endl;
		break;
	case status::StatusCode::Status_DirectoryOrFileWasFound:
		std::cout << "The directory or file was found." << std::endl;
		break;
	case status::StatusCode::Status_DirectoryWasCreated:
		std::cout << "The directory was successfully created." << std::endl;
		break;
	case status::StatusCode::Status_FileWasCreated:
		std::cout << "The file was successfully created." << std::endl;
		break;
	case status::StatusCode::Error_FileWasCreated:
		std::cout << "Error: The file already exists." << std::endl;
		break;
	case status::StatusCode::Error_NoAccessRights:
		std::cout << "Error: Insufficient access rights." << std::endl;
		break;
	}

	std::cout << addedMessage << std::endl;
}

void Status::CreateLogFile(std::string logText)
{
	const std::string DEFAULT_LOG_FILE_DIRECTORY = "./";
	const std::string DEFAULT_LOG_FILE_NAME = "errors";
	const std::string DEFAULT_LOG_FILE_TYPE = ".log";

	std::ofstream logFile;

	try {
		logFile.open(DEFAULT_LOG_FILE_DIRECTORY + DEFAULT_LOG_FILE_NAME + DEFAULT_LOG_FILE_TYPE, std::ios::app);
	}
	catch {
		std::cerr << "Error: Failed to open log file." << std::endl;
	}

	boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();
	auto date = timeLocal.date();
	auto timeOfDay = timeLocal.time_of_day();

	std::string dayAsString = std::to_string(date.day());
	if (dayAsString.size() == 1) dayAsString.insert(0, "0");

	std::string monthAsString = std::to_string(date.month());
	if (monthAsString.size() == 1) monthAsString.insert(0, "0");

	std::string currentDateAsString = "Date: " + dayAsString + '.' + monthAsString + '.' + std::to_string(date.year()) + '\n';

	std::string hoursAsString = std::to_string(timeOfDay.hours());
	if (hoursAsString.size() == 1) hoursAsString.insert(0, "0");

	std::string minutesAsString = std::to_string(timeOfDay.minutes());
	if (minutesAsString.size() == 1) minutesAsString.insert(0, "0");

	std::string secondsAsString = std::to_string(timeOfDay.seconds());
	if (secondsAsString.size() == 1) secondsAsString.insert(0, "0");

	std::string currentTimeAsString = "Time: " + hoursAsString + ':' + minutesAsString + ':' + secondsAsString + '\n';

	logText.insert(0, currentDateAsString + currentTimeAsString);
	logText.append("\n");

	logFile.write(logText.c_str(), logText.size());
	logFile.close();
}
