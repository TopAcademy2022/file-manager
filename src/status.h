#pragma once


#include <iostream>
#include <fstream>
#include <boost/date_time.hpp>

/// <summary>
/// ������
/// </summary>
namespace status
{
	/// <summary>
	/// ��� �������
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
/// ����� ������
/// </summary>
class Status
{
private:
	/// <summary>
	/// ��� �������
	/// </summary>
	status::StatusCode _statusCode;
public:
	/// <summary>
	/// ����������� �� ��������� (�������������)
	/// </summary>
	Status() : Status(status::StatusCode::Status_AllGood){}

	/// <summary>
	/// ����������� � ����������
	/// </summary>
	/// <param name="statusCode">��� �������</param>
	Status(status::StatusCode statusCode);

	/// <summary>
	/// �������� ��� �������
	/// </summary>
	/// <returns>��� �������</returns>
	status::StatusCode GetStatusCode();

	/// <summary>
	/// ���������� ��� �������
	/// </summary>
	/// <param name="newStatusCode">����� ��� �������</param>
	void SetStatusCode(status::StatusCode newStatusCode);

	/// <summary>
	/// �������� ������� ������
	/// </summary>
	/// <returns>������� ������</returns>
	bool GetPresentError();

	/// <summary>
	/// ������� ��������� � �������
	/// </summary>
	/// <param name="addedMessage">����������� �����</param>
	void PrintMessage(std::string addedMessage = "");

	/// <summary>
	/// ������� �����
	/// </summary>
	/// <param name="logText">����� ������</param>
	void CreateLogFile(std::string logText);
};

