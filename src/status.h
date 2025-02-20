#pragma once


#include <iostream>
#include <fstream>
#include <boost/date_time.hpp>
#include <status_code.h>

/// <summary>
/// ������
/// </summary>

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

